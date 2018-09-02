#include "GrenadePrediction.h"
#include "Render.h"

void CCSGrenadeHint::Tick(int buttons)
{
	if (!g_Options.Visuals.GrenadePrediction)
		return;
	bool in_attack = buttons & IN_ATTACK;
	bool in_attack2 = buttons & IN_ATTACK2;

	act = (in_attack && in_attack2) ? ACT_LOB :
		(in_attack2) ? ACT_DROP :
		(in_attack) ? ACT_THROW :
		ACT_NONE;
}
void CCSGrenadeHint::View(CViewSetup* setup)
{
	auto local = Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
	if (!g_Options.Visuals.GrenadePrediction)
		return;
	if (local && local->IsAlive())
	{
		CBaseCombatWeapon* weapon = (CBaseCombatWeapon*)Interfaces::EntityList()->GetClientEntityFromHandle(local->GetActiveWeaponHandle());
		if (weapon && MiscFunctions::IsGrenade(weapon) && act != ACT_NONE)
		{
			type = *weapon->GetItemDefinitionIndex();
			Simulate(setup);
		}
		else
		{
			type = 0;
		}
	}

}

void CCSGrenadeHint::Paint()
{
	if (!g_Options.Visuals.GrenadePrediction)
		return;
	if ((type) && path.size()>1)
	{
		Vector nadeStart, nadeEnd;

		Color lineColor(int(g_Options.Color.color_grenadeprediction[0] * 255), int(g_Options.Color.color_grenadeprediction[1] * 255), int(g_Options.Color.color_grenadeprediction[2] * 255), 255);
		Vector prev = path[0];
		for (auto it = path.begin(), end = path.end(); it != end; ++it)
		{
			if (g_Render->WorldToScreen(prev, nadeStart) && g_Render->WorldToScreen(*it, nadeEnd))
			{
				Interfaces::Surface()->DrawSetColor(lineColor);
				Interfaces::Surface()->DrawLine((int)nadeStart.x, (int)nadeStart.y, (int)nadeEnd.x, (int)nadeEnd.y);
			}
			prev = *it;
		}
		for (auto it = OtherCollisions.begin(), end = OtherCollisions.end(); it != end; ++it)
		{
			g_Render->Draw3DCube(2.f, it->second, it->first, boxColor);
		}

		g_Render->Draw3DCube(2.f, OtherCollisions.rbegin()->second, OtherCollisions.rbegin()->first, Color(255, 0, 0, 200));

		if (g_Render->WorldToScreen(prev, nadeEnd))
		{
			Color circleLine(int(g_Options.Color.color_grenadeprediction_circle[0] * 255), int(g_Options.Color.color_grenadeprediction_circle[1] * 255), int(g_Options.Color.color_grenadeprediction_circle[2] * 255), 255);

			Interfaces::Surface()->DrawSetColor(circleLine);
			Interfaces::Surface()->DrawOutlinedCircle((int)nadeEnd.x, (int)nadeEnd.y, 10, 48);
		}
	}
}
static const constexpr auto PIRAD = 0.01745329251f;
void angle_vectors2(const Vector &angles, Vector *forward, Vector *right, Vector *up)
{
	float sr, sp, sy, cr, cp, cy;

	sp = static_cast<float>(sin(double(angles.x) * PIRAD));
	cp = static_cast<float>(cos(double(angles.x) * PIRAD));
	sy = static_cast<float>(sin(double(angles.y) * PIRAD));
	cy = static_cast<float>(cos(double(angles.y) * PIRAD));
	sr = static_cast<float>(sin(double(angles.z) * PIRAD));
	cr = static_cast<float>(cos(double(angles.z) * PIRAD));

	if (forward)
	{
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	if (right)
	{
		right->x = (-1 * sr*sp*cy + -1 * cr*-sy);
		right->y = (-1 * sr*sp*sy + -1 * cr*cy);
		right->z = -1 * sr*cp;
	}

	if (up)
	{
		up->x = (cr*sp*cy + -sr * -sy);
		up->y = (cr*sp*sy + -sr * cy);
		up->z = cr * cp;
	}
}
void CCSGrenadeHint::Setup(Vector& vecSrc, Vector& vecThrow, Vector viewangles)
{
	if (!g_Options.Visuals.GrenadePrediction)
		return;
	Vector angThrow = viewangles;
	auto local = Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
	float pitch = angThrow.x;

	if (pitch <= 90.0f)
	{
		if (pitch<-90.0f)
		{
			pitch += 360.0f;
		}
	}
	else
	{
		pitch -= 360.0f;
	}
	float a = pitch - (90.0f - fabs(pitch)) * 10.0f / 90.0f;
	angThrow.x = a;

	// Gets ThrowVelocity from weapon files
	// Clamped to [15,750]
	float flVel = 750.0f * 0.9f;

	// Do magic on member of grenade object [esi+9E4h]
	// m1=1  m1+m2=0.5  m2=0
	static const float power[] = { 1.0f, 1.0f, 0.5f, 0.0f };
	float b = power[act];
	// Clamped to [0,1]
	b = b * 0.7f;
	b = b + 0.3f;
	flVel *= b;

	Vector vForward, vRight, vUp;
	angle_vectors2(angThrow, &vForward, &vRight, &vUp); //angThrow.ToVector(vForward, vRight, vUp);

	vecSrc = local->GetEyePosition();
	float off = (power[act] * 12.0f) - 12.0f;
	vecSrc.z += off;

	// Game calls UTIL_TraceHull here with hull and assigns vecSrc tr.endpos
	trace_t tr;
	Vector vecDest = vecSrc;
	vecDest += vForward * 22.0f; //vecDest.MultAdd(vForward, 22.0f);

	TraceHull(vecSrc, vecDest, tr);

	// After the hull trace it moves 6 units back along vForward
	// vecSrc = tr.endpos - vForward * 6
	Vector vecBack = vForward; vecBack *= 6.0f;
	vecSrc = tr.endpos;
	vecSrc -= vecBack;

	// Finally calculate velocity
	vecThrow = local->GetVelocity(); vecThrow *= 1.25f;
	vecThrow += vForward * flVel; //	vecThrow.MultAdd(vForward, flVel);
}

void CCSGrenadeHint::Simulate(CViewSetup* setup)
{
	if (!g_Options.Visuals.GrenadePrediction)
		return;
	Vector vecSrc, vecThrow;
	Vector angles; Interfaces::Engine()->GetViewAngles(angles);
	Setup(vecSrc, vecThrow, angles);

	float interval = Interfaces::Globals()->interval_per_tick;

	// Log positions 20 times per sec
	int logstep = static_cast<int>(0.05f / interval);
	int logtimer = 0;


	path.clear();
	OtherCollisions.clear();
	for (unsigned int i = 0; i<path.max_size() - 1; ++i)
	{
		if (!logtimer)
			path.push_back(vecSrc);

		int s = Step(vecSrc, vecThrow, i, interval);
		if ((s & 1)) break;

		// Reset the log timer every logstep OR we bounced
		if ((s & 2) || logtimer >= logstep) logtimer = 0;
		else ++logtimer;
	}
	path.push_back(vecSrc);
}

int CCSGrenadeHint::Step(Vector& vecSrc, Vector& vecThrow, int tick, float interval)
{

	// Apply gravity
	Vector move;
	AddGravityMove(move, vecThrow, interval, false);

	// Push entity
	trace_t tr;
	PushEntity(vecSrc, move, tr);

	int result = 0;
	// Check ending conditions
	if (CheckDetonate(vecThrow, tr, tick, interval))
	{
		result |= 1;
	}

	// Resolve collisions
	if (tr.fraction != 1.0f)
	{
		result |= 2; // Collision!
		ResolveFlyCollisionCustom(tr, vecThrow, interval);
	}

	if ((result & 1) || vecThrow == Vector(0, 0, 0) || tr.fraction != 1.0f)
	{
		QAngle angles;
		VectorAngles1((tr.endpos - tr.startpos).Normalized(), angles);
		OtherCollisions.push_back(std::make_pair(tr.endpos, angles));
	}

	// Set new position
	vecSrc = tr.endpos;
	return result;
}


bool CCSGrenadeHint::CheckDetonate(const Vector& vecThrow, const trace_t& tr, int tick, float interval)
{
	switch (type)
	{
	case WEAPON_SMOKE:
	case WEAPON_DECOY:
		// Velocity must be <0.1, this is only checked every 0.2s
		if (vecThrow.Length2D()<0.1f)
		{
			int det_tick_mod = static_cast<int>(0.2f / interval);
			return !(tick%det_tick_mod);
		}
		return false;

	case WEAPON_MOLOTOV:
	case WEAPON_INC:
		// Detonate when hitting the floor
		if (tr.fraction != 1.0f && tr.plane.normal.z>0.7f)
			return true;
		// OR we've been flying for too long

	case WEAPON_FLASH:
	case WEAPON_HE:
		// Pure timer based, detonate at 1.5s, checked every 0.2s
		return static_cast<float>(tick)*interval>1.5f && !(tick%static_cast<int>(0.2f / interval));

	default:
		assert(false);
		return false;

	}
}

void CCSGrenadeHint::TraceHull(Vector& src, Vector& end, trace_t& tr)
{
	if (!g_Options.Visuals.GrenadePrediction)
		return;

	static const Vector hull[2] = { Vector(-2.0f, -2.0f, -2.0f), Vector(2.0f, 2.0f, 2.0f) };

	CTraceFilter filter;
	filter.SetIgnoreClass("BaseCSGrenadeProjectile");
	filter.pSkip = Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

	Ray_t ray;
	ray.Init(src, end, hull[0], hull[1]);

    Interfaces::EngineTrace()->TraceRay(ray, 0x200400B, &filter, &tr);
}

void CCSGrenadeHint::AddGravityMove(Vector& move, Vector& vel, float frametime, bool onground)
{
	if (!g_Options.Visuals.GrenadePrediction)
		return;
	Vector basevel(0.0f, 0.0f, 0.0f);

	move.x = (vel.x + basevel.x) * frametime;
	move.y = (vel.y + basevel.y) * frametime;

	if (onground)
	{
		move.z = (vel.z + basevel.z) * frametime;
	}
	else
	{
		// Game calls GetActualGravity( this );
		float gravity = 800.0f * 0.4f;

		float newZ = vel.z - (gravity * frametime);
		move.z = ((vel.z + newZ) / 2.0f + basevel.z) * frametime;

		vel.z = newZ;
	}

}

void CCSGrenadeHint::PushEntity(Vector& src, const Vector& move, trace_t& tr)
{
	if (!g_Options.Visuals.GrenadePrediction)
		return;
	Vector vecAbsEnd = src;
	vecAbsEnd += move;

	// Trace through world
	TraceHull(src, vecAbsEnd, tr);

}

void CCSGrenadeHint::ResolveFlyCollisionCustom(trace_t& tr, Vector& vecVelocity, float interval)
{
	if (!g_Options.Visuals.GrenadePrediction)
		return;
	// Calculate elasticity
	float flSurfaceElasticity = 1.0;  // Assume all surfaces have the same elasticity
	float flGrenadeElasticity = 0.45f; // GetGrenadeElasticity()
	float flTotalElasticity = flGrenadeElasticity * flSurfaceElasticity;
	if (flTotalElasticity>0.9f) flTotalElasticity = 0.9f;
	if (flTotalElasticity<0.0f) flTotalElasticity = 0.0f;

	// Calculate bounce
	Vector vecAbsVelocity;
	PhysicsClipVelocity(vecVelocity, tr.plane.normal, vecAbsVelocity, 2.0f);
	vecAbsVelocity *= flTotalElasticity;

	// Stop completely once we move too slow
	float flSpeedSqr = vecAbsVelocity.LengthSqr();
	static const float flMinSpeedSqr = 20.0f * 20.0f; // 30.0f * 30.0f in CSS
	if (flSpeedSqr<flMinSpeedSqr)
	{
		//vecAbsVelocity.Zero();
		vecAbsVelocity.x = 0.0f;
		vecAbsVelocity.y = 0.0f;
		vecAbsVelocity.z = 0.0f;
	}

	// Stop if on ground
	if (tr.plane.normal.z>0.7f)
	{
		vecVelocity = vecAbsVelocity;
		vecAbsVelocity *= ((1.0f - tr.fraction) * interval); //vecAbsVelocity.Mult((1.0f - tr.fraction) * interval);
		PushEntity(tr.endpos, vecAbsVelocity, tr);
	}
	else
	{
		vecVelocity = vecAbsVelocity;
	}

}

int CCSGrenadeHint::PhysicsClipVelocity(const Vector& in, const Vector& normal, Vector& out, float overbounce)
{
	static const float STOP_EPSILON = 0.1f;

	float    backoff;
	float    change;
	float    angle;
	int        i, blocked;

	blocked = 0;

	angle = normal[2];

	if (angle > 0)
	{
		blocked |= 1;        // floor
	}
	if (!angle)
	{
		blocked |= 2;        // step
	}

	backoff = in.Dot(normal) * overbounce;

	for (i = 0; i<3; i++)
	{
		change = normal[i] * backoff;
		out[i] = in[i] - change;
		if (out[i] > -STOP_EPSILON && out[i] < STOP_EPSILON)
		{
			out[i] = 0;
		}
	}
	return blocked;
}


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class xsygmel {
public:
	string xwviznbxhrv;
	string lzymhyg;
	bool ryznhpbfqenayx;
	double hzmig;
	xsygmel();
	double ynjmhjyskyelndygwpffpojbq();
	bool lbzgyacrql(bool tnfuld, int symmwefpvkrt);
	void yxpgauurtnjainctolrsbo(bool dagtldcz, bool yrujrizswplejnj, int rpoulp, double qzcbssjrh, bool bydgxetnviczic, string lvbjnnjbyoe, string ljshb);
	string rmqqjjvqzwbmydikio(bool vojoirbcum, double gjukbgotvivjd, string npymynvohzmkis, bool crgybyits, bool trvtpl, double ryagyaapyceulc, bool vhkvnldazrm, double whpvfkwvjvpybxt, bool dwyxsnapqgy);
	void rpjabsaxazqgffv(bool wzekkwdofpxu, string kpevovmxd, bool kidxo, double kshotgubh, double ssgcofc, double rfnhktgtrb, double vwbxl);

protected:
	string jibylpokbrkeww;
	bool ubuwjjdirqwpben;
	double cnjstde;
	string kmxncjfhzuzar;

	int wlskdkxxpvasfurv(bool qmgkwkdxwlcxb, double mxeluq);
	double wjzhyiazxqacjof();
	int dnqtvkqnmkr(double pdsbkoxre, int brcismnrgrcnr, int uyjokbyjlmailnm, bool cskmailzmtwtph, bool jhykmgtetgkt, int fhqbov, double uuodeebew, bool spgjynmvo, int dvrtc);
	int dssqsewlbtj(int jkvaozdn, string xtezrebhbdykg, string aakhbvh);
	string wixvgvmlzxrfqq(double tugkk, int kfvbbxk);
	int uqmxpgoywbsbjvz(bool kmowry, int xiinqhyuj, string lwbfak);
	string jpmrnlfplhuqan(int tqftxbxcomx, int rdmuuoadshnkr);
	int wtitgnaeeubpilsz(string lrjpkia);
	bool feqoflrduxiie(int drdemlvbtk);

private:
	string puvlawktnqlszc;
	double xmxhdowzmdynj;
	bool ziuswacvbqay;
	string cnotvvcdwkoikkx;
	string rrimizisiasouv;

	int ocyrgqeyezhrqkuurwjkli(int bifda, double qeqehlaypkp, double qawzcz, string kfajwmqiubvuu, bool lqjbv, int elmgtlsejwh, bool aznjlp, int dmrirqet);
	int swxfawcfhcvbkakgc();
	void sorvlknzram(int fdsjnsmljujbvzg, int demnwelhrfoeuw, bool ondtxpfcnn, int nqyaanmwu, string cpcckcvxhmwmjt, bool vjjjkgqmzzndzq, bool uqucyxymaym, string pzibyauzipdsvq, double posnzbdx);
	void wwpwtqoejngm(string gddkvs, string cmdjyhnfaackhe, bool nldbipmbosmwzk, bool mdoysyw, double npdljbj, double clpvepezl);
	double vkdkrwnfkye(double jtejiwczdgph, double atezvmbjh, string atpxizlaqopojwa, double tltieccyoym, int owtfgnxw, int idnpwbckkun, bool njiaugblc, double ajmnjxnjmv, bool xgmcgzbzu);
	void fzxlozwnksztmhstdskpykjyj();

};


int xsygmel::ocyrgqeyezhrqkuurwjkli(int bifda, double qeqehlaypkp, double qawzcz, string kfajwmqiubvuu, bool lqjbv, int elmgtlsejwh, bool aznjlp, int dmrirqet) {
	double grkkuvzpcvrqrj = 9093;
	int cmpoc = 4371;
	bool vvxqbc = true;
	int kgiakjzbscpn = 4071;
	double lkoietvu = 49416;
	double otkygjuaitbgkg = 1764;
	bool tzucuzjbbdiz = true;
	bool ztxylz = false;
	if (1764 != 1764) {
		int ttlo;
		for (ttlo = 6; ttlo > 0; ttlo--) {
			continue;
		}
	}
	if (4371 != 4371) {
		int hc;
		for (hc = 32; hc > 0; hc--) {
			continue;
		}
	}
	if (true == true) {
		int ter;
		for (ter = 2; ter > 0; ter--) {
			continue;
		}
	}
	if (9093 == 9093) {
		int pknjtoqtim;
		for (pknjtoqtim = 95; pknjtoqtim > 0; pknjtoqtim--) {
			continue;
		}
	}
	if (4371 == 4371) {
		int wcinr;
		for (wcinr = 44; wcinr > 0; wcinr--) {
			continue;
		}
	}
	return 73269;
}

int xsygmel::swxfawcfhcvbkakgc() {
	double zwrggwdfj = 46954;
	double yijehjfz = 15864;
	bool snaratckfi = false;
	if (46954 == 46954) {
		int temeab;
		for (temeab = 97; temeab > 0; temeab--) {
			continue;
		}
	}
	if (46954 != 46954) {
		int znvmd;
		for (znvmd = 100; znvmd > 0; znvmd--) {
			continue;
		}
	}
	if (46954 == 46954) {
		int beytscwnlq;
		for (beytscwnlq = 98; beytscwnlq > 0; beytscwnlq--) {
			continue;
		}
	}
	return 80127;
}

void xsygmel::sorvlknzram(int fdsjnsmljujbvzg, int demnwelhrfoeuw, bool ondtxpfcnn, int nqyaanmwu, string cpcckcvxhmwmjt, bool vjjjkgqmzzndzq, bool uqucyxymaym, string pzibyauzipdsvq, double posnzbdx) {
	double qrvwil = 12980;
	bool padtunxtowzdr = true;
	bool ztpzisavn = true;
	bool nbkvrwjcswdmn = true;
	int tmjueoojvzqvpqq = 238;
	int tobdf = 7996;
	bool ltsxzrurkbpvrbn = false;
	if (7996 == 7996) {
		int ualn;
		for (ualn = 70; ualn > 0; ualn--) {
			continue;
		}
	}

}

void xsygmel::wwpwtqoejngm(string gddkvs, string cmdjyhnfaackhe, bool nldbipmbosmwzk, bool mdoysyw, double npdljbj, double clpvepezl) {

}

double xsygmel::vkdkrwnfkye(double jtejiwczdgph, double atezvmbjh, string atpxizlaqopojwa, double tltieccyoym, int owtfgnxw, int idnpwbckkun, bool njiaugblc, double ajmnjxnjmv, bool xgmcgzbzu) {
	double saxehhxjjotft = 54957;
	double sqawgtmhizdtd = 35545;
	int mkuisfavpj = 3738;
	int kcvvknrevcjxdxb = 5114;
	int txgcs = 4307;
	double dzlgqscplpilbf = 1665;
	if (3738 != 3738) {
		int elt;
		for (elt = 42; elt > 0; elt--) {
			continue;
		}
	}
	if (35545 != 35545) {
		int hxuz;
		for (hxuz = 11; hxuz > 0; hxuz--) {
			continue;
		}
	}
	if (4307 == 4307) {
		int liesgtxre;
		for (liesgtxre = 31; liesgtxre > 0; liesgtxre--) {
			continue;
		}
	}
	if (1665 != 1665) {
		int emvrhgmjcj;
		for (emvrhgmjcj = 2; emvrhgmjcj > 0; emvrhgmjcj--) {
			continue;
		}
	}
	if (1665 == 1665) {
		int cqaswanlry;
		for (cqaswanlry = 39; cqaswanlry > 0; cqaswanlry--) {
			continue;
		}
	}
	return 16987;
}

void xsygmel::fzxlozwnksztmhstdskpykjyj() {
	double mifdqujsn = 2721;
	double kdevf = 4991;
	int bzqqnwqggdvmthc = 1900;
	double doqcrq = 76838;
	int yiapanxmqcj = 670;
	int kimsxx = 865;
	bool skdtmwpa = true;
	int nkpiokggtybi = 1292;
	int jiwoqgumyzr = 4681;
	bool buxrxirxhb = false;
	if (true != true) {
		int sid;
		for (sid = 15; sid > 0; sid--) {
			continue;
		}
	}

}

int xsygmel::wlskdkxxpvasfurv(bool qmgkwkdxwlcxb, double mxeluq) {
	bool zaybcqwyq = false;
	if (false != false) {
		int qjyfwrnck;
		for (qjyfwrnck = 82; qjyfwrnck > 0; qjyfwrnck--) {
			continue;
		}
	}
	if (false == false) {
		int hpiy;
		for (hpiy = 7; hpiy > 0; hpiy--) {
			continue;
		}
	}
	if (false != false) {
		int cbhxk;
		for (cbhxk = 12; cbhxk > 0; cbhxk--) {
			continue;
		}
	}
	if (false == false) {
		int kj;
		for (kj = 81; kj > 0; kj--) {
			continue;
		}
	}
	return 82154;
}

double xsygmel::wjzhyiazxqacjof() {
	double yfzawfy = 1535;
	bool rbwfvpihxe = false;
	bool tmmzx = false;
	if (false != false) {
		int mytzp;
		for (mytzp = 6; mytzp > 0; mytzp--) {
			continue;
		}
	}
	return 80025;
}

int xsygmel::dnqtvkqnmkr(double pdsbkoxre, int brcismnrgrcnr, int uyjokbyjlmailnm, bool cskmailzmtwtph, bool jhykmgtetgkt, int fhqbov, double uuodeebew, bool spgjynmvo, int dvrtc) {
	double mofpjnqwqxvfyp = 20652;
	int isfffb = 1269;
	double ugsynehdwduqxoa = 4188;
	if (20652 == 20652) {
		int olkqd;
		for (olkqd = 88; olkqd > 0; olkqd--) {
			continue;
		}
	}
	if (4188 == 4188) {
		int nacdfjciei;
		for (nacdfjciei = 25; nacdfjciei > 0; nacdfjciei--) {
			continue;
		}
	}
	if (1269 != 1269) {
		int pmywecx;
		for (pmywecx = 65; pmywecx > 0; pmywecx--) {
			continue;
		}
	}
	if (1269 != 1269) {
		int hvplrqu;
		for (hvplrqu = 96; hvplrqu > 0; hvplrqu--) {
			continue;
		}
	}
	if (4188 != 4188) {
		int oxdkoezvge;
		for (oxdkoezvge = 20; oxdkoezvge > 0; oxdkoezvge--) {
			continue;
		}
	}
	return 33311;
}

int xsygmel::dssqsewlbtj(int jkvaozdn, string xtezrebhbdykg, string aakhbvh) {
	bool dpiwyxlm = true;
	string gwokzwwswsbdk = "ujghhyocneocsplibmeoksecwetjmixhmuefhryefaho";
	double wxnsdushmchkm = 70719;
	double mastttt = 17924;
	int xgicfh = 196;
	if (70719 != 70719) {
		int qy;
		for (qy = 39; qy > 0; qy--) {
			continue;
		}
	}
	return 39592;
}

string xsygmel::wixvgvmlzxrfqq(double tugkk, int kfvbbxk) {
	string ofraggpfcf = "wnzyjjgrqxamydttyogcpxgmynbgssibrvzpanyagdlfqdlayalcsypoxxizufuqtsuauclpljfitfariesxwcyo";
	double biqlmtwk = 31607;
	bool flcpropfjfta = true;
	string telnccoetcmm = "brqmvjobjapsyetxdrtuazuvsnvxdgmcdfancpbndaspajsojvkehzsmnomwrsmty";
	string wakoxdbonktpa = "dzgbzvovdwtalhnnnehfdvkdqfbypdjfdghedihiwaqoeoaskyunsmvnayonsrhlfztzy";
	double wyfclncjhzfuw = 7180;
	if (true != true) {
		int ak;
		for (ak = 21; ak > 0; ak--) {
			continue;
		}
	}
	if (string("brqmvjobjapsyetxdrtuazuvsnvxdgmcdfancpbndaspajsojvkehzsmnomwrsmty") == string("brqmvjobjapsyetxdrtuazuvsnvxdgmcdfancpbndaspajsojvkehzsmnomwrsmty")) {
		int vjxu;
		for (vjxu = 29; vjxu > 0; vjxu--) {
			continue;
		}
	}
	return string("guoq");
}

int xsygmel::uqmxpgoywbsbjvz(bool kmowry, int xiinqhyuj, string lwbfak) {
	double xyugkdrbd = 13368;
	string rwjoleofhxml = "utwqlwvcjvuflwprcojmwyinaquyjuoxqedystggkeooxetlnqopksnhseahmtojuzeevy";
	int qdhbf = 223;
	string aclhlpon = "cgspsabovvqjinylipdmopmofhzcmsmnnxdxdievzjndeykktorkcywshrikkfzlbpaelajzqhaxzcrdmntwtxexcomdbdmuh";
	int macshnvtb = 4059;
	double edovkhvvxlohka = 65435;
	int qsfbhdbyyvdulpp = 5022;
	bool uddbqfnwe = false;
	double dflpgaymustij = 8590;
	int cdxaelnisewdge = 1684;
	if (13368 != 13368) {
		int tm;
		for (tm = 60; tm > 0; tm--) {
			continue;
		}
	}
	if (65435 == 65435) {
		int dwcz;
		for (dwcz = 48; dwcz > 0; dwcz--) {
			continue;
		}
	}
	if (false == false) {
		int tavaclgilp;
		for (tavaclgilp = 92; tavaclgilp > 0; tavaclgilp--) {
			continue;
		}
	}
	if (string("utwqlwvcjvuflwprcojmwyinaquyjuoxqedystggkeooxetlnqopksnhseahmtojuzeevy") != string("utwqlwvcjvuflwprcojmwyinaquyjuoxqedystggkeooxetlnqopksnhseahmtojuzeevy")) {
		int zivgumztnf;
		for (zivgumztnf = 31; zivgumztnf > 0; zivgumztnf--) {
			continue;
		}
	}
	return 41817;
}

string xsygmel::jpmrnlfplhuqan(int tqftxbxcomx, int rdmuuoadshnkr) {
	int nihcw = 1934;
	int licbrgxx = 765;
	bool ilflrqdamd = false;
	bool ctnnrxvwfxahsp = true;
	double ryeryfygslb = 8499;
	int ejfsksvtbxhe = 1314;
	int axhquyfvwrbwist = 963;
	double tkjyyax = 85901;
	int igqdzp = 1487;
	if (1487 != 1487) {
		int ulapwxskb;
		for (ulapwxskb = 34; ulapwxskb > 0; ulapwxskb--) {
			continue;
		}
	}
	return string("xqdtylsrmgaqznvi");
}

int xsygmel::wtitgnaeeubpilsz(string lrjpkia) {
	return 13057;
}

bool xsygmel::feqoflrduxiie(int drdemlvbtk) {
	string rlcbmsycilazzel = "qwvxgyrhegerbknzyeesxhqurnsoslujkvwghnwhsaiebwosjrdgrdbzktqvbgo";
	bool kaxarcax = true;
	string flopcseq = "tujffshjavrgszrztkjjbcsygbxxqgbfxkacizkahgnhcm";
	double xnmnbgazvblswhk = 13664;
	if (true != true) {
		int wb;
		for (wb = 10; wb > 0; wb--) {
			continue;
		}
	}
	if (13664 != 13664) {
		int eqfhjiekb;
		for (eqfhjiekb = 5; eqfhjiekb > 0; eqfhjiekb--) {
			continue;
		}
	}
	return true;
}

double xsygmel::ynjmhjyskyelndygwpffpojbq() {
	bool uiiditnmfxpf = true;
	double dckuxdxfgmy = 28869;
	if (true != true) {
		int equbhdt;
		for (equbhdt = 93; equbhdt > 0; equbhdt--) {
			continue;
		}
	}
	if (28869 != 28869) {
		int dhdcouougz;
		for (dhdcouougz = 97; dhdcouougz > 0; dhdcouougz--) {
			continue;
		}
	}
	if (true != true) {
		int qcdruusfn;
		for (qcdruusfn = 84; qcdruusfn > 0; qcdruusfn--) {
			continue;
		}
	}
	return 52429;
}

bool xsygmel::lbzgyacrql(bool tnfuld, int symmwefpvkrt) {
	bool pjawlgomtg = false;
	double tfgcuwhmjmjd = 11130;
	bool rqmnsuzxwk = true;
	int xthpcmh = 845;
	string dizbotyanlsq = "qhjpathivkhstxotkinmmapspstlkumtikndujkavdjffwiwmmhpdndbxfhoiqqdaeipmpgasgmkgwyurpukxsoeeeszlof";
	double kqtfonytt = 2694;
	if (2694 != 2694) {
		int jb;
		for (jb = 50; jb > 0; jb--) {
			continue;
		}
	}
	if (2694 != 2694) {
		int vtkwtwg;
		for (vtkwtwg = 40; vtkwtwg > 0; vtkwtwg--) {
			continue;
		}
	}
	if (845 != 845) {
		int agcojvxnoy;
		for (agcojvxnoy = 29; agcojvxnoy > 0; agcojvxnoy--) {
			continue;
		}
	}
	if (string("qhjpathivkhstxotkinmmapspstlkumtikndujkavdjffwiwmmhpdndbxfhoiqqdaeipmpgasgmkgwyurpukxsoeeeszlof") == string("qhjpathivkhstxotkinmmapspstlkumtikndujkavdjffwiwmmhpdndbxfhoiqqdaeipmpgasgmkgwyurpukxsoeeeszlof")) {
		int trbzwcip;
		for (trbzwcip = 69; trbzwcip > 0; trbzwcip--) {
			continue;
		}
	}
	if (false == false) {
		int bfqprvhf;
		for (bfqprvhf = 61; bfqprvhf > 0; bfqprvhf--) {
			continue;
		}
	}
	return false;
}

void xsygmel::yxpgauurtnjainctolrsbo(bool dagtldcz, bool yrujrizswplejnj, int rpoulp, double qzcbssjrh, bool bydgxetnviczic, string lvbjnnjbyoe, string ljshb) {
	double exjzqpb = 12959;
	string jlbmrjwcyga = "tzkrxaxrwzvazrbnwpzajhdqxxhgewpoecsuiufyytpinoehdetdxnuiyroehjewxgpyoxikqwpotwokxrrmlkqpkmxtoi";
	double tunslez = 6744;
	string ebfwxwayzvhjjkt = "xiubkdgxgmebqfnmel";

}

string xsygmel::rmqqjjvqzwbmydikio(bool vojoirbcum, double gjukbgotvivjd, string npymynvohzmkis, bool crgybyits, bool trvtpl, double ryagyaapyceulc, bool vhkvnldazrm, double whpvfkwvjvpybxt, bool dwyxsnapqgy) {
	double alxhpqznoauaskl = 9963;
	double ymkhqk = 51722;
	int flbalttcqlhatvn = 22;
	double nzbjwjyksxjl = 19785;
	bool vdaovftynkmbkw = false;
	bool efvrfoflr = true;
	if (9963 != 9963) {
		int aqzyyqn;
		for (aqzyyqn = 54; aqzyyqn > 0; aqzyyqn--) {
			continue;
		}
	}
	if (9963 != 9963) {
		int ombdrezt;
		for (ombdrezt = 41; ombdrezt > 0; ombdrezt--) {
			continue;
		}
	}
	if (9963 == 9963) {
		int mmpeyewce;
		for (mmpeyewce = 79; mmpeyewce > 0; mmpeyewce--) {
			continue;
		}
	}
	return string("lxqbntmpumxrctkuyte");
}

void xsygmel::rpjabsaxazqgffv(bool wzekkwdofpxu, string kpevovmxd, bool kidxo, double kshotgubh, double ssgcofc, double rfnhktgtrb, double vwbxl) {
	double hrfszyc = 10664;
	int hfolx = 3605;
	string kcbvpviott = "lclaoyglahhhpyvfyrbzgduzihkqhbvhyvvjuuhgmbtjaririsyiybpmcgdpaxknvdacseyjbfuunldxwulpsxr";
	if (string("lclaoyglahhhpyvfyrbzgduzihkqhbvhyvvjuuhgmbtjaririsyiybpmcgdpaxknvdacseyjbfuunldxwulpsxr") != string("lclaoyglahhhpyvfyrbzgduzihkqhbvhyvvjuuhgmbtjaririsyiybpmcgdpaxknvdacseyjbfuunldxwulpsxr")) {
		int bdlaljr;
		for (bdlaljr = 75; bdlaljr > 0; bdlaljr--) {
			continue;
		}
	}

}

xsygmel::xsygmel() {
	this->ynjmhjyskyelndygwpffpojbq();
	this->lbzgyacrql(false, 996);
	this->yxpgauurtnjainctolrsbo(false, false, 6159, 64183, true, string("hoefhgvlpohzwfandladzujzdigafwagjr"), string("bncxdfclqwwsurqmnteqemmumcqqifgwgqhdkdljnpypyqddguuvrujphrmshysxxnhwfmthicgjlriewslbzbfdhdoxqebzdnfp"));
	this->rmqqjjvqzwbmydikio(true, 67492, string("ntkkyfviirbrxktwsoshsidrortkfnpycvwpmjnka"), false, true, 13256, false, 44087, true);
	this->rpjabsaxazqgffv(false, string("wcwmzlzfhlcdeclcxbsposaizyxfxynsrpkzewkaowpgwnwcbnjdhxl"), true, 6493, 59810, 11441, 44877);
	this->wlskdkxxpvasfurv(true, 63777);
	this->wjzhyiazxqacjof();
	this->dnqtvkqnmkr(38493, 151, 3105, false, true, 6703, 7807, true, 1113);
	this->dssqsewlbtj(2492, string("jrfypdmtkahisrozbmeiswhfvlimygqzqnmb"), string("tuxcoylvzmnegduaarsmvrpsmnuxhz"));
	this->wixvgvmlzxrfqq(28103, 7568);
	this->uqmxpgoywbsbjvz(true, 1315, string("eqtlncweqqerxhuyxicfuhsjnlmbxkkyxfhdzeeeqppiasthdnntumvxfodzuxuxlxerthnerpatyhxyffxjyuhdrhlmicdsfua"));
	this->jpmrnlfplhuqan(3932, 1938);
	this->wtitgnaeeubpilsz(string("godbizzghtroyhzpvsloyzkcibgmhimytokwrjnqrvlpuflatotopduqq"));
	this->feqoflrduxiie(3992);
	this->ocyrgqeyezhrqkuurwjkli(5266, 11853, 7543, string("bjjzcmknqufhdhzdefqzkzjofxwitaixaphleaswbpjznbwzepixwt"), true, 3006, true, 2080);
	this->swxfawcfhcvbkakgc();
	this->sorvlknzram(921, 1022, true, 419, string("eshjbipdndczpmqytchetsovihcewjejqvcyawqjatijfnrjw"), false, true, string("gzejedkfymdzlntxrnjcwrmeipcrwnqejfhbecydbyhliszuaqhrpqxygyep"), 40638);
	this->wwpwtqoejngm(string("axhmhqbwgqhyvysswgsdemwdgzgjdstoiwlhgqcajuvbiyuhykpijidushfygkzfejcxusfujpxtxnuxpjcvftbcxy"), string("ckawswsqxatnvyllwdvvmpyfxkbeq"), false, true, 35574, 52898);
	this->vkdkrwnfkye(13968, 2880, string("ruafrglkroqpcmqywqapdghbissoqbzawksstjboikgaixrvedpqyennjiyqqsahpamqqrpqhbzahewftrlnwxlgh"), 2293, 7084, 1359, false, 50085, true);
	this->fzxlozwnksztmhstdskpykjyj();
}
