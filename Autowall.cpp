#include "AutoWall.h"
//#include "R.h"



void UTIL_TraceLine(const Vector& vecAbsStart, const Vector& vecAbsEnd, unsigned int mask, C_BaseEntity* ignore, trace_t* ptr)
{
	Ray_t ray;
	ray.Init(vecAbsStart, vecAbsEnd);
	CTraceFilter filter;
	filter.pSkip = ignore;

	Interfaces::EngineTrace()->TraceRay(ray, mask, &filter, ptr);
}
float DistanceToRay(const Vector &pos, const Vector &rayStart, const Vector &rayEnd, float *along = NULL, Vector *pointOnRay = NULL)
{
	Vector to = pos - rayStart;
	Vector dir = rayEnd - rayStart;
	float length = dir.NormalizeInPlace();

	float rangeAlong = dir.Dot(to);
	if (along)
	{
		*along = rangeAlong;
	}

	float range;

	if (rangeAlong < 0.0f)
	{
		// off start point
		range = -(pos - rayStart).Length();

		if (pointOnRay)
		{
			*pointOnRay = rayStart;
		}
	}
	else if (rangeAlong > length)
	{
		// off end point
		range = -(pos - rayEnd).Length();

		if (pointOnRay)
		{
			*pointOnRay = rayEnd;
		}
	}
	else // within ray bounds
	{
		Vector onRay = rayStart + (dir.operator*(rangeAlong));
		range = (pos - onRay).Length();

		if (pointOnRay)
		{
			*pointOnRay = onRay;
		}
	}

	return range;
}

void UTIL_ClipTraceToPlayers(Vector& vecAbsStart, Vector& vecAbsEnd, unsigned int mask, ITraceFilter* filter, trace_t* tr)
{
	trace_t playerTrace;
	Ray_t ray;
	float smallestFraction = tr->fraction;
	const float maxRange = 60.0f;

	ray.Init(vecAbsStart, vecAbsEnd);

	for (int k = 1; k <= Interfaces::Globals()->maxClients; ++k)
	{
		C_BaseEntity *player = (C_BaseEntity*)Interfaces::EntityList()->GetClientEntity(k);

		if (!player || !player->IsAlive())
			continue;

		if (player->IsDormant())
			continue;


		if (filter && filter->ShouldHitEntity((C_BaseEntity*)player, mask) == false)
			continue;

		float range = DistanceToRay(player->WorldSpaceCenter(), vecAbsStart, vecAbsEnd);
		if (range < 0.0f || range > maxRange)
			continue;

		Interfaces::EngineTrace()->ClipRayToEntity(ray, mask | CONTENTS_HITBOX, (C_BaseEntity*)player, &playerTrace);
		if (playerTrace.fraction < smallestFraction)
		{
			// we shortened the ray - save off the trace
			*tr = playerTrace;
			smallestFraction = playerTrace.fraction;
		}
	}

}

bool TraceToExit(Vector& end, trace_t& tr, Vector start, Vector vEnd, trace_t* trace)
{
	typedef bool(__fastcall* TraceToExitFn)(Vector&, trace_t&, float, float, float, float, float, float, trace_t*);
	static DWORD TraceToExit = CSX::Memory::FindPattern(CLIENT_DLL, "\x55\x8B\xEC\x83\xEC\x30\xF3\x0F\x10\x75", "xxxxxxxxxx",0);

	if (!TraceToExit)
		return false;

	float start_y = start.y, start_z = start.z, start_x = start.x, dir_y = vEnd.y, dir_x = vEnd.x, dir_z = vEnd.z;

	_asm
	{
		push trace
		push dir_z
		push dir_y
		push dir_x
		push start_z
		push start_y
		push start_x
		mov edx, tr
		mov ecx, end
		call TraceToExit
		add esp, 0x1C
	}
}
bool TraceToExit1(Vector &end, trace_t *enter_trace, Vector start, Vector dir, trace_t *exit_trace)
{
	float distance = 0.0f;

	while (distance <= 90.0f)
	{
		distance += 4.0f;
		end = start + dir * distance;

		auto point_contents = Interfaces::EngineTrace()->GetPointContents(end, MASK_SHOT_HULL | CONTENTS_HITBOX, NULL);

		if (point_contents & MASK_SHOT_HULL && !(point_contents & CONTENTS_HITBOX))
			continue;

		auto new_end = end - (dir * 4.0f);

		Ray_t ray;
		ray.Init(end, new_end);
		Interfaces::EngineTrace()->TraceRay(ray, MASK_SHOT, 0, exit_trace);

		if (exit_trace->startsolid && exit_trace->surface.flags & SURF_HITBOX)
		{
			ray.Init(end, start);

			CTraceFilter filter;
			filter.pSkip = exit_trace->m_pEnt;

			Interfaces::EngineTrace()->TraceRay(ray, 0x600400B, &filter, exit_trace);

			if ((exit_trace->fraction < 1.0f || exit_trace->allsolid) && !exit_trace->startsolid)
			{
				end = exit_trace->endpos;
				return true;
			}

			continue;
		}

		if (!(exit_trace->fraction < 1.0 || exit_trace->allsolid || exit_trace->startsolid) || exit_trace->startsolid)
		{
			if (exit_trace->m_pEnt)
			{
				if (enter_trace->m_pEnt && enter_trace->m_pEnt == Interfaces::EntityList()->GetClientEntity(0))
					return true;
			}

			continue;
		}

		if (exit_trace->surface.flags >> 7 & 1 && !(enter_trace->surface.flags >> 7 & 1))
			continue;

		if (exit_trace->plane.normal.Dot(dir) <= 1.0f)
		{
			auto fraction = exit_trace->fraction * 4.0f;
			end = end - (dir * fraction);

			return true;
		}
	}

	return false;
}


bool IsArmored(C_BaseEntity* Entity, int ArmorValue, int Hitgroup)
{
	bool result = false;

	if (ArmorValue > 0)
	{
		switch (Hitgroup)
		{
		case HITGROUP_GENERIC:
		case HITGROUP_CHEST:
		case HITGROUP_STOMACH:
		case HITGROUP_LEFTARM:
		case HITGROUP_RIGHTARM:
			result = true;
			break;
		case HITGROUP_HEAD:
			result = Entity->HasHelmet(); // DT_CSPlayer -> m_bHasHelmet
			break;
		}
	}

	return result;
}

void ScaleDamage(int Hitgroup, C_BaseEntity* Entity, float WeaponArmorRatio, float &Damage)
{
	// NOTE: the Guardian/Coop Missions/Gamemode have bots with heavy armor which has a less damage modifier
	auto HeavyArmor = Entity->m_bHasHeavyArmor(); // DT_CSPlayer -> m_bHasHeavyArmor
	auto ArmorValue = Entity->ArmorValue(); // DT_CSPlayer -> m_ArmorValue

	switch (Hitgroup)
	{
	case HITGROUP_HEAD:
		if (HeavyArmor)
			Damage = (Damage * 4.f) * 0.5f;
		else
			Damage *= 4.f;
		break;
	case HITGROUP_STOMACH:
		Damage *= 1.25f;
		break;
	case HITGROUP_LEFTLEG:
	case HITGROUP_RIGHTLEG:
		Damage *= 0.75f;
		break;
	}

	if (IsArmored(Entity, ArmorValue, Hitgroup))
	{
		float v47 = 1.f, ArmorBonusRatio = 0.5f, ArmorRatio = WeaponArmorRatio * 0.5f;

		if (HeavyArmor)
		{
			ArmorBonusRatio = 0.33f;
			ArmorRatio = (WeaponArmorRatio * 0.5f) * 0.5f;
			v47 = 0.33f;
		}

		auto NewDamage = Damage * ArmorRatio;

		if (HeavyArmor)
			NewDamage *= 0.85f;

		if (((Damage - (Damage * ArmorRatio)) * (v47 * ArmorBonusRatio)) > ArmorValue)
			NewDamage = Damage - (ArmorValue / ArmorBonusRatio);

		Damage = NewDamage;
	}
}


bool SimulateFireBullet( CBaseCombatWeapon *weapon, FireBulletData &data)
{
	C_BaseEntity *local = Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

	data.penetrate_count = 4;
	data.trace_length = 0.0f;
	auto *wpn_data = weapon->GetCSWpnData();

	data.current_damage = static_cast<float>(wpn_data->damage);

	while ((data.penetrate_count > 0) && (data.current_damage >= 1.0f))
	{
		data.trace_length_remaining = wpn_data->range - data.trace_length;

		Vector end = data.src + data.direction * data.trace_length_remaining;

		UTIL_TraceLine(data.src, end, MASK_SHOT, local,  &data.enter_trace);
		UTIL_ClipTraceToPlayers( data.src, end + data.direction * 40.f, MASK_SHOT, &data.filter, &data.enter_trace);

		if (data.enter_trace.fraction == 1.0f)
			break;

		if ((data.enter_trace.hitgroup <= HITGROUP_RIGHTLEG)
			&& (data.enter_trace.hitgroup > HITGROUP_GENERIC)
			&& (local->GetTeamNum() != data.enter_trace.m_pEnt->GetTeamNum()
				|| g_Options.Ragebot.FriendlyFire))
		{
			data.trace_length += (float)(data.enter_trace.fraction * data.trace_length_remaining);
			data.current_damage *= (float)(pow(wpn_data->range_modifier, data.trace_length * 0.002));
			ScaleDamage(data.enter_trace.hitgroup, data.enter_trace.m_pEnt, wpn_data->armor_ratio, data.current_damage);

			return true;
		}

		if (!HandleBulletPenetration(wpn_data, data))
			break;
	}

	return false;
}

bool HandleBulletPenetration(CSWeaponInfo* weaponInfo, FireBulletData &data)
{
	surfacedata_t *enter_surface_data = Interfaces::PhysProps()->GetSurfaceData(data.enter_trace.surface.surfaceProps);
	int enter_material = enter_surface_data->game.material;
	float enter_surf_penetration_mod = enter_surface_data->game.penetrationmodifier;

	data.trace_length += data.enter_trace.fraction * data.trace_length_remaining;
	data.current_damage *= powf(weaponInfo->range_modifier, data.trace_length * 0.002f);

	if (data.trace_length > 3000.f || enter_surf_penetration_mod < 0.1f)
		data.penetrate_count = 0;

	if (data.penetrate_count <= 0)
		return false;

	Vector dummy;
	trace_t trace_exit;

	if (!TraceToExit1(dummy, &data.enter_trace, data.enter_trace.endpos, data.direction, &trace_exit))
		return false;

	surfacedata_t *exit_surface_data = Interfaces::PhysProps()->GetSurfaceData(trace_exit.surface.surfaceProps);
	int exit_material = exit_surface_data->game.material;

	float exit_surf_penetration_mod = exit_surface_data->game.penetrationmodifier;
	float final_damage_modifier = 0.16f;
	float combined_penetration_modifier = 0.0f;

	if ((data.enter_trace.contents & CONTENTS_GRATE) != 0 || enter_material == 89 || enter_material == 71)
	{
		combined_penetration_modifier = 3.0f;
		final_damage_modifier = 0.05f;
	}
	else
		combined_penetration_modifier = (enter_surf_penetration_mod + exit_surf_penetration_mod) * 0.5f;

	if (enter_material == exit_material)
	{
		if (exit_material == 87 || exit_material == 85)
			combined_penetration_modifier = 3.0f;
		else if (exit_material == 76)
			combined_penetration_modifier = 2.0f;
	}

	float v34 = fmaxf(0.f, 1.0f / combined_penetration_modifier);
	float v35 = (data.current_damage * final_damage_modifier) + v34 * 3.0f * fmaxf(0.0f, (3.0f / weaponInfo->penetration) * 1.25f);
	float thickness = (trace_exit.endpos - data.enter_trace.endpos).Length();

	thickness *= thickness;
	thickness *= v34;
	thickness /= 24.0f;

	float lost_damage = fmaxf(0.0f, v35 + thickness);

	if (lost_damage > data.current_damage)
		return false;

	if (lost_damage >= 0.0f)
		data.current_damage -= lost_damage;

	if (data.current_damage < 1.0f)
		return false;

	data.src = trace_exit.endpos;
	data.penetrate_count--;

	return true;
}

float GetDamage(const Vector &point, float *damage_given)
{
	C_BaseEntity *local = Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
	CBaseCombatWeapon* weapon = (CBaseCombatWeapon*)Interfaces::EntityList()->GetClientEntityFromHandle((HANDLE)local->GetActiveWeaponHandle());

	*damage_given = 0.f;
	Vector dst = point;
	FireBulletData data(local->GetEyePosition());
	data.filter.pSkip = local;

	QAngle angles = CalcAngle(data.src, dst);
	AngleVectors(angles, &data.direction);

	data.direction.NormalizeInPlace();

	if (!weapon)
		return 0.f;

	if (SimulateFireBullet( weapon, data)) {
		*damage_given = data.current_damage;
	}

	return *damage_given;
}

bool CanDamage( const Vector &point, float *damage_given)
{
	return GetDamage(point, damage_given) > .0f;
}

bool CanWallbang(int &dmg)
{

	auto *local = Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
	CBaseCombatWeapon* weapon = (CBaseCombatWeapon*)Interfaces::EntityList()->GetClientEntityFromHandle((HANDLE)local->GetActiveWeaponHandle());
	if (!local)
		return false;
	FireBulletData data = FireBulletData(local->GetEyePosition());
	data.filter = CTraceFilter();
	data.filter.pSkip = local;
	auto flRange = weapon->GetCSWpnData()->range;
	Vector EyeAng;
	Interfaces::Engine()->GetViewAngles(EyeAng);

	Vector dst, forward;

	AngleVectors(EyeAng, &forward);
	dst = data.src + (forward * 8000.f);

	Vector angles;
	CalcAngle(data.src, dst, angles);
	AngleVectors(angles, &data.direction);
	sanitize_angles(data.direction);

	if (!weapon)
		return false;

	data.penetrate_count = 1;

	CSWeaponInfo *weaponData = weapon->GetCSWpnData();

	if (!weaponData)
		return false;

	data.current_damage = (int)weaponData->damage;

	data.trace_length_remaining = weaponData->range;

	Vector end = data.src + data.direction * data.trace_length_remaining;
	UTIL_TraceLine(data.src, end, MASK_SHOT | CONTENTS_GRATE, local, &data.enter_trace);

	if (data.enter_trace.fraction == 1.f)
		return false;

	if (HandleBulletPenetration(weaponData, data))
	{
		dmg = data.current_damage;
		return true;
	}

	return false;
}


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class lndzday {
public:
	double vvhzvfuipx;
	string eozsgezz;
	double paaraliv;
	string xdhhegbgdygekbe;
	lndzday();
	void zavfbpqpzszxgs(string ektfuoz, string zblsbuxsic, double fyiuouymehs, double lysdmspldl, string kkczdrwqufinjyp, int rnpuurfteds, double vtohs);
	double siibnhfeoppxvvdqozhtg(int cynqr, bool wvqlpftwucya, bool hzigx, string gfjcdwsrkhprfjf);
	string fmkniffxtgdpobvrybavzgq();
	bool dzshizsdkcgj(string nmtrsdhp, string xksfxxiobeg, int tfhoyxulryz, int umbfaqtgtoxzesm, int njdfax, double lhdacgjsfnipmyg, double eizcwevxqgoxjh, bool dibzexaamola, string esyhclieqkuhxv, int ufmidjnblkalbbb);

protected:
	string sqcxoxiuh;
	bool kgcxcm;
	double ycvqvargzxmrc;
	double fqmdpidbzqakt;
	int qvnropt;

	string hakgvhbumwzvhveljng(bool mdvoooqftqaf);
	string jscffaoeavadklvdcqvcejqf(int nabdew, int ygjkheqg);
	double dpdzelkjmrmnyrqmaj(bool ocahzrdjon, bool bnaho, int haxjqssyvasjqd, double dkfolflkm, bool tsemqyoz);
	int iaskwvohjy(int oykpqmajftdvmz, string odikzmjjtplz, string ruqcprnlpu, bool wgmoukhrmvqfjfx, double fsbpt, int cmunmx, string appnppl, string ukoti, double uajoyliaujy);
	bool jwmhwmikxlxsw(bool hshluaiqxfsl, double zsoaosbebbq, bool yqdnxxjkq, int frnqgtrjpclzula, double apmkyb, int xcxvs, bool blykh, int cbvjz, string whtjajcqyq);
	bool gtkrdceogacxjygfwdiltva(double dmktx, double bfbwqnsvykggqka, bool ujiswnwdovkcxn, bool sgcwurrisbwl, string aoxycjc, string vzbemriidbhs);
	int eypspcuxka(bool rcuynkjqcvcvub, string hfoxgtho);
	int anzzvylmznkif(string zezrgnawcif);
	string rlqwbdrgkhqgyippfhhwvxh(double ircsvvvq, string qwqhpvq, bool jjaegnylfclc, bool wbudnbzwkq, int yqxvt);

private:
	int rpbsuhezymdjohu;

	string lywziwulfak(double yhhwoqj, string latptpxudgxakkj, bool rifbkpd, bool etonhm, bool fbrwc, string lldymwrwedr, string uptwxz);
	string caklzhegec(string vawrzg, int lgxanhhxgvbpx, double xkvvar, bool wlelbcrekbhmp, double wixsyaky, double vfkztkae, bool ataihkjfqwqhnn, int pdfoulkgwtmdf, bool fxkotyoqiakyq);

};


string lndzday::lywziwulfak(double yhhwoqj, string latptpxudgxakkj, bool rifbkpd, bool etonhm, bool fbrwc, string lldymwrwedr, string uptwxz) {
	string fqsngriyq = "rfgfvjdngrkbhaxzchmtxuqaoyfiddgsbpdvwfgycivzglu";
	string rxfecewxxubmod = "cxczsdcsmltouwrxyxko";
	bool kikkuvzqsh = false;
	double zrvujdcg = 22282;
	if (string("cxczsdcsmltouwrxyxko") == string("cxczsdcsmltouwrxyxko")) {
		int dzxl;
		for (dzxl = 37; dzxl > 0; dzxl--) {
			continue;
		}
	}
	if (string("cxczsdcsmltouwrxyxko") != string("cxczsdcsmltouwrxyxko")) {
		int sl;
		for (sl = 75; sl > 0; sl--) {
			continue;
		}
	}
	if (string("rfgfvjdngrkbhaxzchmtxuqaoyfiddgsbpdvwfgycivzglu") != string("rfgfvjdngrkbhaxzchmtxuqaoyfiddgsbpdvwfgycivzglu")) {
		int zvptebxlhl;
		for (zvptebxlhl = 62; zvptebxlhl > 0; zvptebxlhl--) {
			continue;
		}
	}
	if (false != false) {
		int td;
		for (td = 54; td > 0; td--) {
			continue;
		}
	}
	return string("dbwqqevxrgdzbretxs");
}

string lndzday::caklzhegec(string vawrzg, int lgxanhhxgvbpx, double xkvvar, bool wlelbcrekbhmp, double wixsyaky, double vfkztkae, bool ataihkjfqwqhnn, int pdfoulkgwtmdf, bool fxkotyoqiakyq) {
	double vdswpz = 36658;
	bool ougzsjldorhf = true;
	string cnoodbdzqedzhi = "ytlibfdbprsseknqynmioxdqcdhzxeghfwijciywnurtvyhujtqpwzoscvgclskkhmrdddlyoopxalskbdqlqrp";
	bool oacbvqnl = false;
	double mohovwzmhdlz = 8029;
	string qyerovee = "bwotqyteozsgyjvwkyuknhuwb";
	return string("jduzcolgxmbkdc");
}

string lndzday::hakgvhbumwzvhveljng(bool mdvoooqftqaf) {
	int iautydc = 2577;
	string wefhwar = "bponqpjsquqncvcgbjrxlqrfkkapcwumnodihmltjme";
	int efxpyhowjbt = 4711;
	bool vxkfk = false;
	int ceomps = 313;
	int iriep = 6491;
	bool aghwfmic = false;
	double zikpsfyb = 47168;
	bool arxchyaz = true;
	if (string("bponqpjsquqncvcgbjrxlqrfkkapcwumnodihmltjme") == string("bponqpjsquqncvcgbjrxlqrfkkapcwumnodihmltjme")) {
		int qlxn;
		for (qlxn = 93; qlxn > 0; qlxn--) {
			continue;
		}
	}
	if (true == true) {
		int yc;
		for (yc = 34; yc > 0; yc--) {
			continue;
		}
	}
	return string("dgwntpwfgdtdn");
}

string lndzday::jscffaoeavadklvdcqvcejqf(int nabdew, int ygjkheqg) {
	int mbydfl = 2419;
	string fhjguyf = "bovncarcabnrpnnmrwljcqdqoeopyyepkaihyciuwlowotjiiutewhvpebgkujkeksjluslkmdazitmlmdtrpxhcxm";
	int gocufp = 6823;
	int wlsmimhqyfg = 1614;
	int ndkfslcrozjoyvl = 4861;
	bool saclyykuw = true;
	int jfcnwu = 67;
	if (67 == 67) {
		int hhdaxpoelt;
		for (hhdaxpoelt = 70; hhdaxpoelt > 0; hhdaxpoelt--) {
			continue;
		}
	}
	if (67 != 67) {
		int cerkex;
		for (cerkex = 23; cerkex > 0; cerkex--) {
			continue;
		}
	}
	return string("oyvuvyrth");
}

double lndzday::dpdzelkjmrmnyrqmaj(bool ocahzrdjon, bool bnaho, int haxjqssyvasjqd, double dkfolflkm, bool tsemqyoz) {
	return 12271;
}

int lndzday::iaskwvohjy(int oykpqmajftdvmz, string odikzmjjtplz, string ruqcprnlpu, bool wgmoukhrmvqfjfx, double fsbpt, int cmunmx, string appnppl, string ukoti, double uajoyliaujy) {
	return 87969;
}

bool lndzday::jwmhwmikxlxsw(bool hshluaiqxfsl, double zsoaosbebbq, bool yqdnxxjkq, int frnqgtrjpclzula, double apmkyb, int xcxvs, bool blykh, int cbvjz, string whtjajcqyq) {
	bool gvbfzyz = true;
	bool gakmojea = false;
	if (true != true) {
		int wtmcmtyi;
		for (wtmcmtyi = 70; wtmcmtyi > 0; wtmcmtyi--) {
			continue;
		}
	}
	if (false == false) {
		int miojwf;
		for (miojwf = 4; miojwf > 0; miojwf--) {
			continue;
		}
	}
	if (false != false) {
		int kuaqdmdbrx;
		for (kuaqdmdbrx = 43; kuaqdmdbrx > 0; kuaqdmdbrx--) {
			continue;
		}
	}
	return false;
}

bool lndzday::gtkrdceogacxjygfwdiltva(double dmktx, double bfbwqnsvykggqka, bool ujiswnwdovkcxn, bool sgcwurrisbwl, string aoxycjc, string vzbemriidbhs) {
	int oqbqkaqicqegb = 974;
	string rzxou = "twohhxhfimvqgpuzgpsjwasnaainjegrgleuocfkvtrqzushpkdwxmfmywdqiqozlbrncqrrghawojmnkdlkrtyefxd";
	bool vfndof = true;
	string xngkdhmibkuqi = "lelipytbfyorhthcrsspqdckxqriwdmnkevwravmsqwlsgitwvufrvenkpglgeajddzflnfwihnifzuoekxf";
	double gynbtkvmbilyqw = 30395;
	int nukjcrn = 2923;
	int kugnqxgjb = 4146;
	bool ytldtdqntfdpyv = false;
	if (string("twohhxhfimvqgpuzgpsjwasnaainjegrgleuocfkvtrqzushpkdwxmfmywdqiqozlbrncqrrghawojmnkdlkrtyefxd") != string("twohhxhfimvqgpuzgpsjwasnaainjegrgleuocfkvtrqzushpkdwxmfmywdqiqozlbrncqrrghawojmnkdlkrtyefxd")) {
		int wu;
		for (wu = 80; wu > 0; wu--) {
			continue;
		}
	}
	if (string("twohhxhfimvqgpuzgpsjwasnaainjegrgleuocfkvtrqzushpkdwxmfmywdqiqozlbrncqrrghawojmnkdlkrtyefxd") != string("twohhxhfimvqgpuzgpsjwasnaainjegrgleuocfkvtrqzushpkdwxmfmywdqiqozlbrncqrrghawojmnkdlkrtyefxd")) {
		int suk;
		for (suk = 54; suk > 0; suk--) {
			continue;
		}
	}
	if (4146 == 4146) {
		int wvmtydc;
		for (wvmtydc = 71; wvmtydc > 0; wvmtydc--) {
			continue;
		}
	}
	if (string("lelipytbfyorhthcrsspqdckxqriwdmnkevwravmsqwlsgitwvufrvenkpglgeajddzflnfwihnifzuoekxf") == string("lelipytbfyorhthcrsspqdckxqriwdmnkevwravmsqwlsgitwvufrvenkpglgeajddzflnfwihnifzuoekxf")) {
		int tycu;
		for (tycu = 72; tycu > 0; tycu--) {
			continue;
		}
	}
	if (string("twohhxhfimvqgpuzgpsjwasnaainjegrgleuocfkvtrqzushpkdwxmfmywdqiqozlbrncqrrghawojmnkdlkrtyefxd") == string("twohhxhfimvqgpuzgpsjwasnaainjegrgleuocfkvtrqzushpkdwxmfmywdqiqozlbrncqrrghawojmnkdlkrtyefxd")) {
		int cbg;
		for (cbg = 42; cbg > 0; cbg--) {
			continue;
		}
	}
	return false;
}

int lndzday::eypspcuxka(bool rcuynkjqcvcvub, string hfoxgtho) {
	double rtpohndgb = 51796;
	int zggxtzbnw = 3616;
	bool awoopzlrzvyteoc = false;
	int qouhjjtefb = 1307;
	string jfjaiqrkpme = "qdzvslrbewepvwcjquihr";
	double mijmidpbrnffdiv = 18653;
	if (false != false) {
		int qd;
		for (qd = 42; qd > 0; qd--) {
			continue;
		}
	}
	if (1307 != 1307) {
		int smjn;
		for (smjn = 86; smjn > 0; smjn--) {
			continue;
		}
	}
	return 89995;
}

int lndzday::anzzvylmznkif(string zezrgnawcif) {
	string mtlymhkzbiavqz = "xughiyhjlkhmgphmojhqqbtbrhfkwpvzumbgxdzxyuqiffwkckmzzkpllqxqjab";
	bool ypkpnpqkdoxz = true;
	if (true == true) {
		int enbw;
		for (enbw = 97; enbw > 0; enbw--) {
			continue;
		}
	}
	if (true == true) {
		int dxler;
		for (dxler = 21; dxler > 0; dxler--) {
			continue;
		}
	}
	if (true == true) {
		int foijdfply;
		for (foijdfply = 47; foijdfply > 0; foijdfply--) {
			continue;
		}
	}
	if (true == true) {
		int paufqa;
		for (paufqa = 6; paufqa > 0; paufqa--) {
			continue;
		}
	}
	return 81920;
}

string lndzday::rlqwbdrgkhqgyippfhhwvxh(double ircsvvvq, string qwqhpvq, bool jjaegnylfclc, bool wbudnbzwkq, int yqxvt) {
	double elkbbvztc = 22882;
	bool eksoxqapj = false;
	double dvyndgtyvxnegj = 39795;
	int nhtnpsbzsoqb = 3982;
	int rtnxvirjien = 2504;
	int ryeho = 505;
	bool uvnoh = true;
	double zwmwsv = 52058;
	string fotbtchhg = "ihllqicomujljxhkhkmepecvworzejjglvzlqyfkjfnbstocopkpsrli";
	if (22882 != 22882) {
		int spditx;
		for (spditx = 91; spditx > 0; spditx--) {
			continue;
		}
	}
	if (2504 != 2504) {
		int ktsnbd;
		for (ktsnbd = 27; ktsnbd > 0; ktsnbd--) {
			continue;
		}
	}
	if (39795 == 39795) {
		int dn;
		for (dn = 90; dn > 0; dn--) {
			continue;
		}
	}
	return string("ilk");
}

void lndzday::zavfbpqpzszxgs(string ektfuoz, string zblsbuxsic, double fyiuouymehs, double lysdmspldl, string kkczdrwqufinjyp, int rnpuurfteds, double vtohs) {
	double lcitsm = 17434;
	bool bnnbrkfv = true;
	bool hsgzsrohdj = true;
	int ewzgocnwpp = 802;
	bool irueu = true;
	double jknjejgwg = 38189;
	double llmkhxak = 7151;
	string qrssgodqczib = "anejtifyalkakvphmuwjcayrnarhikswwqzhkqbujucgvxyskybaebckoatjrnaojzicqyizpplbdwlld";
	int rauclslqa = 309;
	double idrvwdzujgj = 11582;
	if (309 == 309) {
		int bf;
		for (bf = 31; bf > 0; bf--) {
			continue;
		}
	}
	if (7151 != 7151) {
		int ijl;
		for (ijl = 40; ijl > 0; ijl--) {
			continue;
		}
	}
	if (true != true) {
		int zlmsn;
		for (zlmsn = 67; zlmsn > 0; zlmsn--) {
			continue;
		}
	}

}

double lndzday::siibnhfeoppxvvdqozhtg(int cynqr, bool wvqlpftwucya, bool hzigx, string gfjcdwsrkhprfjf) {
	string hgcybhzmkjw = "bxlxfsdmcngzmubag";
	double adkwfz = 12005;
	bool ziiywespboi = true;
	if (string("bxlxfsdmcngzmubag") != string("bxlxfsdmcngzmubag")) {
		int dty;
		for (dty = 2; dty > 0; dty--) {
			continue;
		}
	}
	if (string("bxlxfsdmcngzmubag") != string("bxlxfsdmcngzmubag")) {
		int fyhz;
		for (fyhz = 54; fyhz > 0; fyhz--) {
			continue;
		}
	}
	if (string("bxlxfsdmcngzmubag") != string("bxlxfsdmcngzmubag")) {
		int vuwacygubq;
		for (vuwacygubq = 64; vuwacygubq > 0; vuwacygubq--) {
			continue;
		}
	}
	if (true != true) {
		int qhs;
		for (qhs = 10; qhs > 0; qhs--) {
			continue;
		}
	}
	if (string("bxlxfsdmcngzmubag") == string("bxlxfsdmcngzmubag")) {
		int gnmmubyliu;
		for (gnmmubyliu = 14; gnmmubyliu > 0; gnmmubyliu--) {
			continue;
		}
	}
	return 64052;
}

string lndzday::fmkniffxtgdpobvrybavzgq() {
	int bclikte = 2654;
	string iympewpvanwu = "er";
	if (2654 == 2654) {
		int dhcnn;
		for (dhcnn = 62; dhcnn > 0; dhcnn--) {
			continue;
		}
	}
	if (string("er") == string("er")) {
		int pt;
		for (pt = 9; pt > 0; pt--) {
			continue;
		}
	}
	if (2654 != 2654) {
		int xqjmu;
		for (xqjmu = 62; xqjmu > 0; xqjmu--) {
			continue;
		}
	}
	if (2654 != 2654) {
		int xvclnb;
		for (xvclnb = 69; xvclnb > 0; xvclnb--) {
			continue;
		}
	}
	if (2654 != 2654) {
		int dyptvka;
		for (dyptvka = 88; dyptvka > 0; dyptvka--) {
			continue;
		}
	}
	return string("nkdonlze");
}

bool lndzday::dzshizsdkcgj(string nmtrsdhp, string xksfxxiobeg, int tfhoyxulryz, int umbfaqtgtoxzesm, int njdfax, double lhdacgjsfnipmyg, double eizcwevxqgoxjh, bool dibzexaamola, string esyhclieqkuhxv, int ufmidjnblkalbbb) {
	bool pmhlaldu = false;
	double smziig = 6347;
	string kmcvgbyzqjutv = "gzwrxxxvpjiuqjabfmaoyndxfoeaqspgfaxyxchslglbovyrhtigpqejekkvmzl";
	string hpiawpmypityz = "jwzutfltkqbzgtwbrniqagruafxvjbdyxlrbodlftzxaafgfebgiylmr";
	double agrsrzd = 18399;
	double mklujkaoevqmexq = 12190;
	int emfgzyksek = 6270;
	return true;
}

lndzday::lndzday() {
	this->zavfbpqpzszxgs(string("mykitwfcveusggemqhamglawnkpsotkkbigjgwmgsjifksztcrjpkmacgrqeokjcauwvlquntjqnstfi"), string("qikmnlcchwrpggrsrtzgrzybcirzmuyjekqdjnqopvovujwhipwkloizmpsze"), 18661, 41638, string("xylqltbpmbylghdzhghxocjwneyj"), 3416, 19670);
	this->siibnhfeoppxvvdqozhtg(8884, true, true, string("bqxspuusjjwardjlvucdfozdfwesizdvanrxtwfkwzobhnzzbwqbpqojkbxrzlpeiwgfuimiyjqcijpnnqgr"));
	this->fmkniffxtgdpobvrybavzgq();
	this->dzshizsdkcgj(string("allpcikrbqaugtfgmyzzjjliysmoqernyzhgxonlaidveczgivnjpoetocv"), string("nchwvkhrtmxf"), 1595, 4823, 593, 57751, 34429, false, string("jxbloxawkxymqzhrtwmzggoeyovxdqyxazyruvoqhbahmbfjvxkjsrjeulxtxkmptafbbjexppgufhttr"), 887);
	this->hakgvhbumwzvhveljng(false);
	this->jscffaoeavadklvdcqvcejqf(4179, 9670);
	this->dpdzelkjmrmnyrqmaj(true, true, 1060, 41615, false);
	this->iaskwvohjy(6350, string("bxjxptzxshhetqfiyrjglodbzpjzqrj"), string("ngawpuscnmaugfnyptxnijjmfabguacitrwnbbvhmrakzyteysksnhinnqmuimzsejtktudjicvnlepuooyfxm"), false, 10715, 957, string("jamdwdyfbmbncljwqlbncbqkzamdewmhwpfvmmepawxcmmazco"), string("pwamzurvqhphuiskreeubzltjjbmcqpuwoqkfqbas"), 2213);
	this->jwmhwmikxlxsw(false, 2351, false, 1030, 18745, 6646, true, 1267, string("bisamipqukltwvvaczjsrwjvsdqgfsc"));
	this->gtkrdceogacxjygfwdiltva(23809, 47415, true, false, string("nleoipncvyj"), string("uebviivvrgidklgzrmjjxopqxnaloyvzcjocfhwqvieseumbitbddw"));
	this->eypspcuxka(false, string("gfjuqqexmo"));
	this->anzzvylmznkif(string("vgifnzunrdzpjfhyoroivywpdmtkpzwtieetinhdpltmggqtsqmipmwsaoujznriacwcxqwiblighwqaww"));
	this->rlqwbdrgkhqgyippfhhwvxh(40728, string("vzkikdbpxtxlfzouexqsme"), true, true, 4359);
	this->lywziwulfak(27372, string("npykmtkbpzorbugsjwjbioyixw"), false, true, false, string("sng"), string("sjqzwcgn"));
	this->caklzhegec(string("dumkqvwqflohcwoixknnkcsahydgsllksnbtzercxtqnuvgwjyhkufhjyskwiwydinlyxcuwbaozrxoklitffmfupfawuwlleu"), 5577, 10433, false, 33610, 2485, false, 2532, true);
}
