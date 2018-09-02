#include "Misc.h"
#include "Interfaces.h"
#include "Render.h"
#include <time.h>
#include "BaseClient.h"
#include "Strafer.h"
#include "CSX.h"

std::string animatedclantag;
int iLastTime;



void misc::OnCreateMove(CInput::CUserCmd *cmd, C_BaseEntity *local, bool& bSendPacket)
{

	if (g_Options.Misc.Bhop && local->IsAlive())
	{
		static float move = 450;
		float s_move = move * 0.5065f;
		QAngle oldangles = cmd->viewangles;
		if (cmd->buttons & IN_JUMP && !(local->GetMoveType() & MOVETYPE_LADDER))
		{

			int iFlags = local->GetFlags();
			if (!(iFlags & FL_ONGROUND))
				cmd->buttons &= ~IN_JUMP;

			cmd->forwardmove = move * 0.015f;
			cmd->sidemove += (float)(((cmd->tick_count % 2) * 2) - 1) * s_move;

			if (cmd->mousedx)
				cmd->sidemove = (float)clamp(cmd->mousedx, -1, 1) * s_move;

			static float strafe = cmd->viewangles.y;

			float rt = cmd->viewangles.y, rotation;
			rotation = strafe - rt;

			if (rotation < FloatNegate(Interfaces::Globals()->interval_per_tick))
				cmd->sidemove = -s_move;

			if (rotation > Interfaces::Globals()->interval_per_tick)
				cmd->sidemove = s_move;

			strafe = rt;
		}
		movementfix(oldangles, cmd);
	}
	int value = g_Options.Misc.syncclantag;

	switch (value)
	{
	case 0:
	{

		break;
	}
	case 1:
	{
		static int counter = 0;
		static int motion = 0;
		int ServerTime = (float)local->GetTickBase() * Interfaces::Globals()->interval_per_tick * 2.5;

		if (counter % 48 == 0)
			motion++;
		int value = ServerTime % 20;
		switch (value) {
		case 0: setclantag(XorStr("")); break;
		case 1: setclantag(XorStr("D")); break;
		case 2: setclantag(XorStr("DA")); break;
		case 3: setclantag(XorStr("DAR")); break;
		case 4: setclantag(XorStr("DARK ")); break;
		case 5: setclantag(XorStr("DARK H")); break;
		case 6: setclantag(XorStr("DARK HO")); break;
		case 7: setclantag(XorStr("DARK HOO")); break;
		case 8: setclantag(XorStr("DARK HOOK")); break;
		case 9: setclantag(XorStr("DARK HOOK")); break;
		case 10: setclantag(XorStr("DARK HOOK")); break;
		case 11: setclantag(XorStr("DARK HOOK")); break;
		case 12: setclantag(XorStr("DARK HOOK")); break;
		case 13: setclantag(XorStr("DARK HOOK")); break;
		case 14: setclantag(XorStr("DARK HOO")); break;
		case 15: setclantag(XorStr("DARK HO")); break;
		case 16: setclantag(XorStr("DARK H")); break;
		case 17: setclantag(XorStr("DARK ")); break;
		case 18: setclantag(XorStr("DARK")); break;
		case 19: setclantag(XorStr("DAR")); break;
		case 20: setclantag(XorStr("DA")); break;
		case 21: setclantag(XorStr("D")); break;
		case 22: setclantag(XorStr("")); break;

		}
		counter++;
		break;
	}
	case 2:
	{
		static int counter = 0;
		static int motion = 0;
		int ServerTime = (float)local->GetTickBase() * Interfaces::Globals()->interval_per_tick * 2.5;

		if (counter % 48 == 0)
			motion++;
		int value = ServerTime % 20;
		switch (value) {

		case 0: setclantag(XorStr("")); break;
		case 1: setclantag(XorStr("N")); break;
		case 2: setclantag(XorStr("Ni")); break;
		case 3: setclantag(XorStr("Nig")); break;
		case 4: setclantag(XorStr("Nigg")); break;
		case 5: setclantag(XorStr("Nigge")); break;
		case 6: setclantag(XorStr("Nigger")); break;
		case 7: setclantag(XorStr("NiggerC")); break;
		case 8: setclantag(XorStr("NiggerCh ")); break;
		case 9: setclantag(XorStr("NiggerChe")); break;
		case 10: setclantag(XorStr("NiggerChea")); break;
		case 11: setclantag(XorStr("NiggerCheat")); break;
		case 12: setclantag(XorStr("NiggerCheats")); break;
		case 13: setclantag(XorStr("Nigger")); break;
		case 14: setclantag(XorStr("Cheats")); break;

		}
		counter++;
		break;
	}
	case 3:
	{
		static int counter = 0;
		static int motion = 0;
		int ServerTime = (float)local->GetTickBase() * Interfaces::Globals()->interval_per_tick * 2.5;

		if (counter % 60 == 0)
			motion++;
		int value = ServerTime % 40;
		switch (value) {
		case 0: setclantag(XorStr("")); break;
		case 1: setclantag(XorStr("S I [:")); break;
		case 2: setclantag(XorStr("S II [:")); break;
		case 3: setclantag(XorStr("S III [:")); break;
		case 4: setclantag(XorStr("S IV [:")); break;
		case 5: setclantag(XorStr("SE [:")); break;
		case 6: setclantag(XorStr("SEM [:")); break;
		case 7: setclantag(XorStr("GN I [:")); break;
		case 8: setclantag(XorStr("GN II [:")); break;
		case 9: setclantag(XorStr("GN III [:")); break;
		case 10: setclantag(XorStr("GNM [:")); break;
		case 11: setclantag(XorStr("MG I [:")); break;
		case 12: setclantag(XorStr("MG II [:")); break;
		case 13: setclantag(XorStr("MGE [:")); break;
		case 14: setclantag(XorStr("DMG [:")); break;
		case 15: setclantag(XorStr("LE [:")); break;
		case 16: setclantag(XorStr("LEM [:")); break;
		case 17: setclantag(XorStr("SMFC [:")); break;
		case 18: setclantag(XorStr("GE [:")); break;
		case 19: setclantag(XorStr("VAC ]:")); break;
		case 20: setclantag(XorStr("VAC ]:")); break;
		case 21: setclantag(XorStr("")); break;

		}
		counter++;
		break;
	}
	case 4:
	{
		setclantag("[VALV\xE1\xB4\xB1] \r");
		break;
	}
	case 5:
	{
		setclantag("[VALV\xE1\xB4\xB1]");
		break;
	}
	case 6:
	{
		setclantag("DARK HOOK");
		break;
	}
	case 7:
	{
		static size_t lastTime = 0;

		if (GetTickCount() > lastTime)
		{
			setclantag("\xE2\x9c\x93 Admin \xE2\x9c\x93");
			lastTime = GetTickCount() + 64;
		}
		break;
	}
	case 8:
	{
		static size_t lastTime = 0;

		if (GetTickCount() > lastTime)
		{
			time_t now = time(0);
			char timestamp[12] = "";

			strftime(timestamp, 12, "[%H:%M:%S]", localtime(&now));
			setclantag(timestamp);
			lastTime = GetTickCount() + 64;
		}
	}

	break;
	}

	if (!g_Options.Misc.animatedclantag && animatedclantag.c_str() != G::AnimatedClantag)
	{
		animatedclantag = G::AnimatedClantag;
	}
	if (g_Options.Misc.animatedclantag && animatedclantag.length() > 1)
	{
		if (int(Interfaces::Globals()->curtime) != iLastTime)
		{
			auto length = animatedclantag.length();
			animatedclantag.insert(0, 1, animatedclantag[length - 2]);
			animatedclantag.erase(length - 1, 1);

			setclantag(animatedclantag.c_str());
			iLastTime = int(Interfaces::Globals()->curtime);
		}
	}
	if (g_Options.Misc.namespam)
	{
		char name[151];
		char fucked_char = static_cast<char>(-1);
		for (auto i = 0; i <= 150; i++)
			name[i] = fucked_char;

		const char nick[12] = "DARK HOOK";
		memcpy(name, nick, 11);

		change_name(name);
	}

	if (g_Options.Misc.Edgjump &&g_Options.Misc.Edgekey > 0 && local->IsAlive())
	{
		EdgeJump(cmd);
	}

	if (g_Options.Misc.RCS && local->IsAlive())
	{

		StandAloneRCS(local, cmd);
	}

	if (g_Options.Misc.AirlockKey && local->IsAlive())
	{

		int m_heldTicks = 0;
		int ticks = 0;
		float tick_interval_sqr = pow(Interfaces::Globals()->interval_per_tick, 2);
		float vel_2d_sqr = local->GetVelocity().Length2DSqr();

		int unclamped_Ticks = std::min< int >(15, static_cast<int>(std::ceilf(sqrt(4096.0f / (vel_2d_sqr * tick_interval_sqr)))));
		int clamped_Ticks = ((std::max)(0, (std::min)(unclamped_Ticks, 14)) ? unclamped_Ticks : 14);

		if (m_heldTicks < clamped_Ticks)
		{
			bSendPacket = false;
m_heldTicks++;
		}
		else
		{
			bSendPacket = true;
			m_heldTicks = 0;
		}
	}

	if (g_Options.Misc.Ranks)
	{
		RankReveal(cmd);
	}






	static size_t lastTime = 0;
	static int counter = 0;
	if (GetTickCount() > lastTime)
	{

		counter = counter + 1;
		if (counter > 5)
			counter = 0;
		switch (g_Options.Misc.spammer)
		{
		case 1:
			SayInChat(DHlist[counter]);
			break;
		case 2:
			SayInChat(tuxlist[counter]);
			break;
		case 3:
			SayInChat(ezfragslist[counter]);
			break;
		}

		lastTime = GetTickCount() + 850;
	}

	if (g_Options.Misc.hidename)
	{
		setclantag("\n \n \n ");
	}

	if (g_Options.Misc.silentstealer)
	{
		bool bDidMeme = false;
		int iNameIndex = -1;
		char chName[130];

		for (int iPlayerIndex = 0; iPlayerIndex < Interfaces::Engine()->GetMaxClients(); iPlayerIndex++)
		{
			C_BaseEntity *pEntity = Interfaces::EntityList()->GetClientEntity(iPlayerIndex);
			if (!pEntity || pEntity == local || iPlayerIndex == Interfaces::Engine()->GetLocalPlayer())
				continue;
			if (rand() % g_Options.Misc.namespeed == 1)
			{
				iNameIndex = pEntity->EntIndex();
				bDidMeme = true;
			}
		}
		if (bDidMeme)
		{
			PlayerInfo pInfo;
			Interfaces::Engine()->GetPlayerInfo(iNameIndex, &pInfo);
			sprintf(chName, "%s ", pInfo.m_szPlayerName);
			change_name(chName);
		}

	}

	blockbot(cmd);

}

void misc::StandAloneRCS(C_BaseEntity* pLocal, CInput::CUserCmd* pCmd)
{
	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)Interfaces::EntityList()->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());
	if (!MiscFunctions::IsSniper(pWeapon))
	{
	static Vector vOldPunch = { 0.0f, 0.0f, 0.0f };
	Vector vNewPunch = pLocal->localPlayerExclusive()->GetAimPunchAngle();

	vNewPunch *= g_Options.Misc.NRCS;

	vNewPunch -= vOldPunch;
	if( g_Options.Misc.RCS_Distortion) vNewPunch *= g_Options.Misc.RCS_NDistortion * 0.02;
	vNewPunch += vOldPunch;

	QAngle vFinal = pCmd->viewangles - (vNewPunch - vOldPunch);

	sanitize_angles(vFinal);

	if (!sanitize_angles(vFinal))
		return;

	ClampAngles(vFinal);

	Interfaces::Engine()->SetViewAngles(vFinal);

	vOldPunch = vNewPunch;
	}
}

void misc::AutoStrafe(CInput::CUserCmd *cmd, C_BaseEntity *local, QAngle oldangles)
{
	static AutoStrafer Strafer;

	static float move = 450;
	float s_move = move * 0.5065f;
	if (local->GetMoveType() & (MOVETYPE_NOCLIP | MOVETYPE_LADDER))
		return;
	if (cmd->buttons & (IN_FORWARD | IN_MOVERIGHT | IN_MOVELEFT | IN_BACK))
		return;

	if (cmd->buttons & IN_JUMP || !(local->GetFlags() & FL_ONGROUND))
	{
		if (local->GetVelocity().Length2D() == 0 && (cmd->forwardmove == 0 && cmd->sidemove == 0))
		{
			cmd->forwardmove = 450.f;
		}
		else if (cmd->forwardmove == 0 && cmd->sidemove == 0)
		{
			if (cmd->mousedx > 0 || cmd->mousedx > -0)
			{
				cmd->sidemove = cmd->mousedx < 0.f ? -450.f : 450.f;
			}
			else
			{
				auto airaccel = Interfaces::CVar()->FindVar("sv_airaccelerate");
				auto maxspeed = Interfaces::CVar()->FindVar("sv_maxspeed");

				static int zhop = 0;
				double yawrad = Normalize_y(oldangles.y) * PI / 180;

				float speed = maxspeed->GetFloat();
				if (cmd->buttons & IN_DUCK)
					speed *= 0.333;

				double tau = Interfaces::Globals()->interval_per_tick, MA = speed * airaccel->GetFloat();

				int Sdir = 0, Fdir = 0;
				Vector velocity = local->GetVelocity();
				double vel[3] = { velocity[0], velocity[1], velocity[2] };
				double pos[2] = { 0, 0 };
				double dir[2] = { std::cos((oldangles[1] + 10 * zhop) * PI / 180), std::sin((oldangles[1] + 10 * zhop) * PI / 180) };
				oldangles.y = Normalize_y(yawrad * 180 / PI);
				Strafer.strafe_line_opt(yawrad, Sdir, Fdir, vel, pos, 30.0, tau, MA, pos, dir);
				cmd->sidemove = Sdir * 450;
			}
		}

	}
	movementfix(oldangles, cmd);
}

void misc::EdgeJump(CInput::CUserCmd* pCmd)
{
	C_BaseEntity *LocalP = Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
	if (LocalP->GetMoveType() == MOVETYPE_LADDER || LocalP->GetMoveType() == MOVETYPE_NOCLIP)
		return;

	Vector Start, End;
	Start = LocalP->GetOrigin();

	VectorCopy(LocalP->GetOrigin(), Start);
	VectorCopy(Start, End);

	End.z -= 32;

	Ray_t ray;
	ray.Init(Start, End);

	trace_t trace;

	CTraceFilter filter;
	filter.pSkip = Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

	Interfaces::EngineTrace()->TraceRay(ray, MASK_PLAYERSOLID_BRUSHONLY, &filter, &trace);

	//int EdgeJumpKey = Menu::Window.MiscTab.OtherEdgeJump.GetKey();
	if (trace.fraction == 1.0f && G::PressedKeys[g_Options.Misc.Edgekey])
	{
		pCmd->buttons |= IN_JUMP;
	}
}
void misc::SlowMove(CInput::CUserCmd* pCmd, bool &bSendPacket, C_BaseEntity *local)
{

		int SlowMoveKey = g_Options.Misc.slowmovekey;
		if (SlowMoveKey > 0 && G::PressedKeys[g_Options.Misc.slowmovekey])
		{
			static int chocking = -1;
			chocking++;

			if (chocking < 3)
			{
				bSendPacket = false;
				pCmd->tick_count += 10;
				pCmd += 7 + pCmd->tick_count % 2 ? 0 : 1;
				pCmd->buttons |= local->GetMoveType() == IN_BACK;
				pCmd->forwardmove = pCmd->sidemove = 0.f;
			}
			else
			{
				bSendPacket = true;
				chocking = -1;
				Interfaces::Globals()->frametime *= (local->GetVelocity().Length2D()) / 1.f;
				pCmd->buttons |= local->GetMoveType() == IN_FORWARD;
			}
		
	}
}

void misc::FakeWalk(CInput::CUserCmd *pCmd)
{

	static bool enabledtp = false;
	static bool check = false;
	if (GetAsyncKeyState(g_Options.Misc.fakewalkkey))
	{
		if (!check)
			enabledtp = !enabledtp;
		check = true;
	}
	else
		check = false;

	if (g_Options.Misc.fakewalk && enabledtp)
	{
		auto local_player = Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

		if (!local_player || local_player->GetHealth() <= 0)
			return;

		uintptr_t* FPointer; __asm { MOV FPointer, EBP }
		byte* SendPacket = (byte*)(*FPointer - 0x1C);

		static int choked = 0;
		choked = choked > 7 ? 0 : choked + 1;
		pCmd->forwardmove = choked < 2 || choked > 5 ? 0 : pCmd->forwardmove;
		pCmd->sidemove = choked < 2 || choked > 5 ? 0 : pCmd->sidemove;
		*SendPacket = choked < 1;
    }
}

void misc::moonwalk(CInput::CUserCmd *cmd)
{
	static bool enabledtp = false;
	static bool check = false;
	if (GetAsyncKeyState(g_Options.Misc.moonwalkkey))
	{
		if (!check)
			enabledtp = !enabledtp;
		check = true;
	}
	else
		check = false;
	if (g_Options.Misc.moonwalk && enabledtp)
	{
		enum MoveType_t;
		if (enum MoveType_t() & (MOVETYPE_NOCLIP | MOVETYPE_LADDER | FL_ONGROUND))
			return;
		{
			if (cmd->buttons & IN_FORWARD)
			{
				cmd->forwardmove = 450;
				cmd->buttons &= ~IN_FORWARD;
				cmd->buttons |= IN_BACK;
			}
			else if (cmd->buttons & IN_BACK)
			{
				cmd->forwardmove = -450;
				cmd->buttons &= ~IN_BACK;
				cmd->buttons |= IN_FORWARD;
			}

			if (cmd->buttons & IN_MOVELEFT)
			{
				cmd->sidemove = -450;
				cmd->buttons &= ~IN_MOVELEFT;
				cmd->buttons |= IN_MOVERIGHT;
			}
			else if (cmd->buttons & IN_MOVERIGHT)
			{
				cmd->sidemove = 450;
				cmd->buttons &= ~IN_MOVERIGHT;
				cmd->buttons |= IN_MOVELEFT;
			}
		}
	}
}

void misc::blockbot(CInput::CUserCmd* m_pcmd)
{
	C_BaseEntity *pLocal = Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());


	auto m_local = pLocal;
	float bestdist = 250.f;
	int index = -1;

	if (GetAsyncKeyState(g_Options.Misc.iBlockbotKey) && g_Options.Misc.bBlockbot)
	{
		for (int i = 0; i < Interfaces::Globals()->maxClients; i++) {
			auto entity = Interfaces::EntityList()->GetClientEntity(i);

			if (!entity) continue;
			if (!entity->IsAlive() || entity->IsDormant() || entity == m_local) continue;

			float dist = (m_local->GetOrigin() - entity->GetOrigin()).Length();

			if (dist < bestdist) {
				bestdist = dist;
				index = i;
			}
		}

	}
	if (index == -1) return;


	auto target = Interfaces::EntityList()->GetClientEntity(index);


	if (!target) return;


	Vector angles;
	CalcAngle(m_local->GetEyePosition(), target->GetEyePosition(), angles);
	angles.Normalized();


	if (angles.y < 0.0f) m_pcmd->sidemove = 450.f;
	else if (angles.y > 0.0f) m_pcmd->sidemove = -450.f;

}

void misc::Knifebot(CInput::CUserCmd* pCmd)
{
	C_BaseEntity *pLocal = Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)Interfaces::EntityList()->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());
	if (g_Options.Knifebot.knf_Active && pWeapon->IsKnife())
	{
		for (int i = 0; i < Interfaces::Engine()->GetMaxClients(); i++)
		{
			C_BaseEntity* pBaseEntity = Interfaces::EntityList()->GetClientEntity(i);

			if (!pBaseEntity)
				continue;
			if (pBaseEntity->IsDormant())
				continue;
			if (!pBaseEntity->GetHealth() > 0)
				continue;
			if (pBaseEntity == pLocal)
				continue;
			if (!g_Options.Knifebot.knf_Team && pLocal->GetTeamNum() == pBaseEntity->GetTeamNum())
				continue;

			int iDistance = int(pLocal->GetRenderOrigin().DistTo(pBaseEntity->GetRenderOrigin()));

					int MinDistance = 0;
					switch (g_Options.Knifebot.knf_Attack)
					{
					case 0:
						MinDistance = g_Options.Knifebot.knf_DistAttack;
						break;
					case 1:
						MinDistance = g_Options.Knifebot.knf_DistAttack2;
						break;
					case 2:
						MinDistance = g_Options.Knifebot.knf_DistAttack;
						break;
					}
					int DistanceToPlayer = iDistance;

					if (DistanceToPlayer > MinDistance)
						continue;
					switch (g_Options.Knifebot.knf_Attack)
					{
					case 0:
						pCmd->buttons |= IN_ATTACK;
						break;
						return;
					case 1:
						pCmd->buttons |= IN_ATTACK2;
						break;
						return;
					case 2:
						if (DistanceToPlayer > g_Options.Knifebot.knf_DistAttack2)
							pCmd->buttons |= IN_ATTACK;
						else
							pCmd->buttons |= IN_ATTACK2;
						break;
						return;
					}
				
			}
		}
	
}



#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ksvfrmm {
public:
	int rwrxh;
	string esdeim;
	string xcloatwdhgn;
	string qbmzl;
	ksvfrmm();
	double dtwlwnjfwgieafxkkawqsfb(bool opmtfociip, bool lwtjcmhatkfnq, int bjvjihxcmcqjp, bool svyxpwzh);
	bool uvltgbnjio(double jgummgyfni, double kvihzno, bool krxhxtxwyf, bool mzczeowsirolnym, bool cznuinnluvt, bool mxjjxjjwpmxal, double wxqhofidnuypn, bool ovvncohy);
	string cyetphgopclscbhf(int pxckj);

protected:
	bool vpvyopzhpdignu;
	bool daipmo;
	string mpmhfnmpmrr;

	void twmicunmclpuib(bool nswujzf, bool qbprygmguj);
	double jhikmcigzhnweqnzygtjb(int vbckypouruaae, bool uwkkwg, string qrvfdnucbkll);
	double uxrrdsvucsqwvv(double kzlagecn, int bnxlwtwu, string qawnxwnlve, string xlcfrtpy);

private:
	string ktafztiatfzpnnw;
	double yyagloo;
	double tmcncbj;
	string nbgairoqdxwdr;
	string gmsdfhtbd;

	void iliczfowttq(int pwkwpncyvjkw, double zuuoxjzypuwi, string elzjhf, string amwomiuvpyrwrv, string dmuaihhyrzuyn, string iznxyebo, int sxfyehonmuud, int roqzz);
	int ftmkgicgycmruogzqopllsj(int qjvwxodrv, string knunhleawn);

};


void ksvfrmm::iliczfowttq(int pwkwpncyvjkw, double zuuoxjzypuwi, string elzjhf, string amwomiuvpyrwrv, string dmuaihhyrzuyn, string iznxyebo, int sxfyehonmuud, int roqzz) {
	string amtsoickoaijb = "xxdvnghsmrkrsxtkvvpsqimgzbpiojiprnpebziknxncyrowcngpqocljbqvchfv";
	bool ybsaeumhfjfpc = false;
	double okaxlhln = 9266;
	if (false == false) {
		int zqeo;
		for (zqeo = 86; zqeo > 0; zqeo--) {
			continue;
		}
	}
	if (9266 != 9266) {
		int eiqrg;
		for (eiqrg = 61; eiqrg > 0; eiqrg--) {
			continue;
		}
	}
	if (string("xxdvnghsmrkrsxtkvvpsqimgzbpiojiprnpebziknxncyrowcngpqocljbqvchfv") != string("xxdvnghsmrkrsxtkvvpsqimgzbpiojiprnpebziknxncyrowcngpqocljbqvchfv")) {
		int uhojtx;
		for (uhojtx = 47; uhojtx > 0; uhojtx--) {
			continue;
		}
	}
	if (string("xxdvnghsmrkrsxtkvvpsqimgzbpiojiprnpebziknxncyrowcngpqocljbqvchfv") != string("xxdvnghsmrkrsxtkvvpsqimgzbpiojiprnpebziknxncyrowcngpqocljbqvchfv")) {
		int qgswycqzu;
		for (qgswycqzu = 74; qgswycqzu > 0; qgswycqzu--) {
			continue;
		}
	}
	if (string("xxdvnghsmrkrsxtkvvpsqimgzbpiojiprnpebziknxncyrowcngpqocljbqvchfv") != string("xxdvnghsmrkrsxtkvvpsqimgzbpiojiprnpebziknxncyrowcngpqocljbqvchfv")) {
		int ibbtiob;
		for (ibbtiob = 93; ibbtiob > 0; ibbtiob--) {
			continue;
		}
	}

}

int ksvfrmm::ftmkgicgycmruogzqopllsj(int qjvwxodrv, string knunhleawn) {
	double ifjpkim = 14751;
	bool toexaqyl = false;
	double ldwaitr = 51207;
	bool hrnzrefrhredl = true;
	if (51207 == 51207) {
		int hjrj;
		for (hjrj = 39; hjrj > 0; hjrj--) {
			continue;
		}
	}
	if (true == true) {
		int kcagjkcq;
		for (kcagjkcq = 4; kcagjkcq > 0; kcagjkcq--) {
			continue;
		}
	}
	if (51207 == 51207) {
		int pls;
		for (pls = 27; pls > 0; pls--) {
			continue;
		}
	}
	return 46910;
}

void ksvfrmm::twmicunmclpuib(bool nswujzf, bool qbprygmguj) {

}

double ksvfrmm::jhikmcigzhnweqnzygtjb(int vbckypouruaae, bool uwkkwg, string qrvfdnucbkll) {
	double rplwldhxuyjib = 81023;
	string wgrezzcsx = "ewjrnfqyeaplobqgfyfvzyeckjaqvnuatdmihizzvjzrdfnaygvhwwnwvxsendqacn";
	double lyvhxitexirtts = 16474;
	int ficlre = 1859;
	int pclhjqepedtpl = 7429;
	string stsmsuigbzxm = "szjqawdccssqslvfzqbxmonqoijhhh";
	string gbayhrcfap = "fcndnvaauyrmiubqdpzqgpxcldqoa";
	if (string("fcndnvaauyrmiubqdpzqgpxcldqoa") == string("fcndnvaauyrmiubqdpzqgpxcldqoa")) {
		int uxbfic;
		for (uxbfic = 67; uxbfic > 0; uxbfic--) {
			continue;
		}
	}
	if (7429 != 7429) {
		int gnt;
		for (gnt = 39; gnt > 0; gnt--) {
			continue;
		}
	}
	return 59098;
}

double ksvfrmm::uxrrdsvucsqwvv(double kzlagecn, int bnxlwtwu, string qawnxwnlve, string xlcfrtpy) {
	double nlxabkopugqvr = 34900;
	double agofdtfulpz = 5993;
	bool nkvuygww = true;
	bool gziaoorpyjvc = false;
	string hilftyhmmksvitb = "w";
	string rchohthmytqy = "maxybwjzszctzleehnegiwlctdhjhvmoxwpraodbjcgkagyijpcnixvgdijminngvwghflfostwyeetwnqbwcrkc";
	int mjaatjtpvqtdiv = 2559;
	bool qlmtlykacobxvtk = true;
	bool pvoxlmy = true;
	if (string("maxybwjzszctzleehnegiwlctdhjhvmoxwpraodbjcgkagyijpcnixvgdijminngvwghflfostwyeetwnqbwcrkc") == string("maxybwjzszctzleehnegiwlctdhjhvmoxwpraodbjcgkagyijpcnixvgdijminngvwghflfostwyeetwnqbwcrkc")) {
		int krenczmf;
		for (krenczmf = 42; krenczmf > 0; krenczmf--) {
			continue;
		}
	}
	if (false != false) {
		int bxm;
		for (bxm = 32; bxm > 0; bxm--) {
			continue;
		}
	}
	return 82030;
}

double ksvfrmm::dtwlwnjfwgieafxkkawqsfb(bool opmtfociip, bool lwtjcmhatkfnq, int bjvjihxcmcqjp, bool svyxpwzh) {
	bool dyatdfoojly = true;
	string qonbkzgqeyc = "ijimrhosxrkntispdkwhkrlzleofmvzcjzdkxxlpqqvxyeurklxpyytcdhutxm";
	string nqksaccdmoeotax = "exklnhmkrsvmllnurwgonseiaahwtkoeilwqofalbkaikjqbpvkdnhbkqxagzovfviqlflnsdxmgatogsfbafvox";
	int ffyoldoddj = 1379;
	string rabmtwgivb = "by";
	double efwcjntux = 39240;
	string adxuvpwxkgayy = "xripsbqscufqubtbsctotbplwqajhozlwjkftmimhemzuvtweqhsuovmjqpwyjdspliptnpqifsyukfjkf";
	if (string("by") != string("by")) {
		int xfpdxlx;
		for (xfpdxlx = 71; xfpdxlx > 0; xfpdxlx--) {
			continue;
		}
	}
	if (string("exklnhmkrsvmllnurwgonseiaahwtkoeilwqofalbkaikjqbpvkdnhbkqxagzovfviqlflnsdxmgatogsfbafvox") == string("exklnhmkrsvmllnurwgonseiaahwtkoeilwqofalbkaikjqbpvkdnhbkqxagzovfviqlflnsdxmgatogsfbafvox")) {
		int oiphlqw;
		for (oiphlqw = 15; oiphlqw > 0; oiphlqw--) {
			continue;
		}
	}
	if (string("ijimrhosxrkntispdkwhkrlzleofmvzcjzdkxxlpqqvxyeurklxpyytcdhutxm") == string("ijimrhosxrkntispdkwhkrlzleofmvzcjzdkxxlpqqvxyeurklxpyytcdhutxm")) {
		int vgdd;
		for (vgdd = 44; vgdd > 0; vgdd--) {
			continue;
		}
	}
	if (string("xripsbqscufqubtbsctotbplwqajhozlwjkftmimhemzuvtweqhsuovmjqpwyjdspliptnpqifsyukfjkf") != string("xripsbqscufqubtbsctotbplwqajhozlwjkftmimhemzuvtweqhsuovmjqpwyjdspliptnpqifsyukfjkf")) {
		int knfly;
		for (knfly = 68; knfly > 0; knfly--) {
			continue;
		}
	}
	if (string("exklnhmkrsvmllnurwgonseiaahwtkoeilwqofalbkaikjqbpvkdnhbkqxagzovfviqlflnsdxmgatogsfbafvox") == string("exklnhmkrsvmllnurwgonseiaahwtkoeilwqofalbkaikjqbpvkdnhbkqxagzovfviqlflnsdxmgatogsfbafvox")) {
		int naiq;
		for (naiq = 42; naiq > 0; naiq--) {
			continue;
		}
	}
	return 92703;
}

bool ksvfrmm::uvltgbnjio(double jgummgyfni, double kvihzno, bool krxhxtxwyf, bool mzczeowsirolnym, bool cznuinnluvt, bool mxjjxjjwpmxal, double wxqhofidnuypn, bool ovvncohy) {
	bool kabqnhkezy = true;
	int ymdtvak = 7560;
	int ngakkn = 3071;
	double zfnibnknzymsq = 47221;
	int lbeudpygzkawhi = 1674;
	bool cxbsbwsfvm = true;
	double ollbvfmokqut = 16445;
	double pagrsygodyx = 33796;
	string qwyuwzlau = "xmniljdbkqddbibrxfitvelz";
	if (true == true) {
		int cekcnsgvmx;
		for (cekcnsgvmx = 2; cekcnsgvmx > 0; cekcnsgvmx--) {
			continue;
		}
	}
	if (16445 != 16445) {
		int plcvfc;
		for (plcvfc = 84; plcvfc > 0; plcvfc--) {
			continue;
		}
	}
	if (true == true) {
		int zgolshwfv;
		for (zgolshwfv = 63; zgolshwfv > 0; zgolshwfv--) {
			continue;
		}
	}
	return true;
}

string ksvfrmm::cyetphgopclscbhf(int pxckj) {
	string uejymp = "xmefvhadaeakczrklbgejwslfvtekjitltxeajhajfnwhvhahvbfqpdpdbxhfcxviisylcskhanyqgxh";
	string oghys = "ahbbglhdjjngobutytvafopeo";
	int kjdbodll = 1397;
	if (string("xmefvhadaeakczrklbgejwslfvtekjitltxeajhajfnwhvhahvbfqpdpdbxhfcxviisylcskhanyqgxh") == string("xmefvhadaeakczrklbgejwslfvtekjitltxeajhajfnwhvhahvbfqpdpdbxhfcxviisylcskhanyqgxh")) {
		int ptdexshsme;
		for (ptdexshsme = 32; ptdexshsme > 0; ptdexshsme--) {
			continue;
		}
	}
	return string("xsdzrkpgddmzpsfzmcjp");
}

ksvfrmm::ksvfrmm() {
	this->dtwlwnjfwgieafxkkawqsfb(true, true, 5191, true);
	this->uvltgbnjio(4404, 16602, true, true, true, false, 14478, true);
	this->cyetphgopclscbhf(6066);
	this->twmicunmclpuib(true, false);
	this->jhikmcigzhnweqnzygtjb(8043, true, string("ubpwpchinwedegpqijrztcqkcrtsmrnp"));
	this->uxrrdsvucsqwvv(17698, 905, string("pjyiqrubacwmigpaklojacvyiiobkrgmdxlfpnqmohiulvnnfgtc"), string("jllkife"));
	this->iliczfowttq(4524, 12995, string(""), string("wxovcytczvegzbfzhdhumbgebndjnhkyxqkvvevmwzpfkeiysewjgpkztddpvtcngfvjaulegbu"), string("nlcsluixvur"), string("rirqyroxqptlzwqguoqvqbgeyinpwtsbvsmawkwibabkoxpucoggtdxodfvmytwfydip"), 232, 4647);
	this->ftmkgicgycmruogzqopllsj(1813, string("ihpgflkvzhbqntqiaepnqcpenazcxgxqfirofhmvzehpufmdndipgwbkckltextoutawsyvroazgrtbwwz"));
}
