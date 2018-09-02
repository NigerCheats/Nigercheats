
#include "LegitBot.h"
#include "Ragebot.h"
#include "Render.h"
#include "SDK.h"
#include "EnginePrediction.h"
#include "Global.h"
#define NOMINMAX
#include <Windows.h>
#include <stdio.h>
#include <random>
#include <string>
#include <vector>

legitbot::legitbot()
{
	best_target = -1;
	view_angle = QAngle(0.0f, 0.0f, 0.0f);
	aim_angle = QAngle(0.0f, 0.0f, 0.0f);
	hitbox_position = Vector(0.0f, 0.0f, 0.0f);

	aim_key = 0;
	aim_smooth = 1.f;
	aim_fov = 0;
	aim_rcs = 0;
	aim_rcstype = 0;
	shoot = false;
	fakelag = false;
}
float get_fov(const QAngle &viewAngles, const QAngle &aimAngles)
{
	Vector ang, aim;
	AngleVectors(viewAngles, &aim);
	AngleVectors(aimAngles, &ang);

	return RAD2DEG(acos(aim.Dot(ang) / aim.LengthSqr()));
}

bool shoot;
static int custom_delay = 0;

void legitbot::OnCreateMove(CInput::CUserCmd *pCmd, C_BaseEntity *local, bool& bSendPacket)
{

	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)Interfaces::EntityList()->GetClientEntityFromHandle(local->GetActiveWeaponHandle());

	if (local && local->IsAlive() && pWeapon)
	{
		if (g_Options.Legitbot.MainSwitch)
		{ 

		do_aimbot(local, pWeapon, pCmd);

	    if(fakelag)	FakeLag(local,pCmd, bSendPacket);

		if (!g_Options.Misc.RCS) RCS(local, pCmd, pWeapon);

		if (g_Options.Legitbot.Aimbot.AutoPistol) AutoPistol(pCmd, local, pWeapon);

		if (g_Options.Legitbot.Aimbot.fastzoom) FastZoom(pCmd, local, pWeapon);

		LegitAA(local, pWeapon,pCmd, bSendPacket);

		AimSniper(local);
		}
	if (g_Options.Legitbot.TriggerbotSwitch)
		if ((G::PressedKeys[TriggerbotKey] || Triggerbot_AutoFire) && Triggerbot) triggerbot(pCmd, local, pWeapon);
	


	}
}

void legitbot::triggerbot(CInput::CUserCmd *cmd, C_BaseEntity* local, CBaseCombatWeapon* weapon)
{
	typedef bool(__cdecl* GoesThroughSmoke)(Vector, Vector);

	static uint32_t GoesThroughSmokeOffset = (uint32_t)CSX::Memory::NewPatternScan(GetModuleHandleW(L"client_panorama.dll"), ("55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0"));
	static GoesThroughSmoke GoesThroughSmokeFunction = (GoesThroughSmoke)GoesThroughSmokeOffset;

	Vector ang;
	ang[0] = local->GetEyePosition().x;
	ang[1] = local->GetEyePosition().y;
	ang[2] = local->GetEyePosition().z;


	if (!local->IsAlive())
		return;

	if (weapon) {
		if (weapon->ammo() == 0)
			return;
		if (MiscFunctions::IsKnife(weapon) || MiscFunctions::IsGrenade(weapon)) return;
		if (*weapon->GetItemDefinitionIndex() == 64) return;
	}



	QAngle ViewAngles = cmd->viewangles + local->localPlayerExclusive()->GetAimPunchAngle();


	Vector CrosshairForward;
	AngleVectors(ViewAngles, &CrosshairForward);
	CrosshairForward *= weapon->GetCSWpnData()->range;


	Vector TraceSource = local->GetEyePosition();
	Vector TraceDestination = TraceSource + CrosshairForward;

	Ray_t Ray;
	trace_t Trace;
	CTraceFilter Filter;

	Filter.pSkip = local;

	Ray.Init(TraceSource, TraceDestination);
	Interfaces::EngineTrace()->TraceRay(Ray, MASK_SHOT, &Filter, &Trace);

	if (!Trace.m_pEnt)
		return;
	if (!Trace.m_pEnt->IsAlive())
		return;
	if (Trace.m_pEnt->HasGunGameImmunity())
		return;


	if (local->GetTeamNum() == Trace.m_pEnt->GetTeamNum())
		return;

	if (!hit_chance(local, cmd, weapon, Trace.m_pEnt))
		return;

	bool didHit = false;
	if ((Triggerbot_Filter.Head && Trace.hitgroup == 1)
		|| (Triggerbot_Filter.Chest && Trace.hitgroup == 2)
		|| (Triggerbot_Filter.Stomach && Trace.hitgroup == 3)
		|| (Triggerbot_Filter.Arms && (Trace.hitgroup == 4 || Trace.hitgroup == 5))
		|| (Triggerbot_Filter.Legs && (Trace.hitgroup == 6 || Trace.hitgroup == 7)))
	{
		didHit = true;
	}

	if (g_Options.Legitbot.checksmoke && GoesThroughSmokeFunction(ang, CrosshairForward))
		return;

	if (TriggerbotDelay >= 1)
	{
		if (custom_delay >= TriggerbotDelay / 30)
		{
			if (didHit)
			{
				custom_delay = 0;
				shoot = true;
				cmd->buttons |= IN_ATTACK;
			}
		}
		else
		{
			custom_delay++;
		}
	}

}

void legitbot::LegitAA(C_BaseEntity* local, CBaseCombatWeapon* weapon, CInput::CUserCmd *pCmd, bool& bSendPacket)
{
	
	if (g_Options.Legitbot.Aimbot.EnableLegitAA)
	{
		if (!local) return;
		if (pCmd->buttons & IN_ATTACK || pCmd->buttons & IN_USE || local->GetMoveType() & MOVETYPE_LADDER) return;
		if (MiscFunctions::IsGrenade(weapon)) return;
		{
			static int ChokedPackets = -1;
			ChokedPackets++;
			if (ChokedPackets < 1)
			{
				bSendPacket = true;
			}
			else
			{
				bSendPacket = false;
				pCmd->viewangles.y -= g_Options.Legitbot.Aimbot.AAAngle;
				ChokedPackets = -1;
			}
		}
	}

}

void legitbot::FakeLag(C_BaseEntity* pLocal, CInput::CUserCmd *pCmd, bool& bSendPacket)
{

	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)Interfaces::EntityList()->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());


	if (pCmd->buttons & IN_ATTACK && CanAttack())
		return;
	if ((pCmd->buttons & IN_USE))
		return;
	if (pLocal->GetMoveType() == MOVETYPE_LADDER)
		return;

	if (pWeapon)
	{
		CSWeaponInfo* pWeaponInfo = pWeapon->GetCSWpnData();
		CCSGrenade* csGrenade = (CCSGrenade*)pWeapon;

		if (csGrenade->GetThrowTime() > 0.f)
			return;
		if (MiscFunctions::IsKnife(pWeapon))
			return;
	}

	int amount = nfakelag;
	
	if (fakelag_mode == 0)
	{
		static	int choke = -1;
		choke++;
		if (choke <= amount && choke > -1)
		{
			bSendPacket = false;
		}
		else
		{
			bSendPacket = true;
			choke = -1;
		}
	}
	if (fakelag_mode == 1)
	{
		if (pLocal->m_iShotsFired())
		{
			static int choke = -1;
			choke++;
			if (choke <= amount && choke > -1)
			{
				bSendPacket = false;
			}
			else
			{
				bSendPacket = true;
				choke = -1;
			}
		}

	}
	
}
void legitbot::AutoPistol(CInput::CUserCmd *cmd, C_BaseEntity* local, CBaseCombatWeapon* weapon)
{

	if (MiscFunctions::IsPistol(weapon))
	{
		if (cmd->buttons & IN_ATTACK)
		{
			float flCurTime = (float)local->GetTickBase() * Interfaces::Globals()->interval_per_tick;
			float flNextAttack = weapon->GetNextPrimaryAttack();

			if (flNextAttack > flCurTime)
			{
				cmd->buttons &= ~IN_ATTACK;
				cmd->buttons |= IN_ATTACK;
				cmd->buttons &= ~IN_ATTACK;
			}
		}
	}
}
void legitbot::FastZoom(CInput::CUserCmd *cmd, C_BaseEntity* local, CBaseCombatWeapon* weapon)
{
	if (cmd->buttons & IN_ATTACK)
	{
		if (MiscFunctions::IsSniper(weapon)) {
			if (!local->IsScoped())
			{
				cmd->buttons &= ~IN_ATTACK;
				cmd->buttons |= IN_ZOOM;
			}

			if ((cmd->buttons & IN_ATTACK) && g_Options.Legitbot.Aimbot.fastzoomswitch) {
				Interfaces::Engine()->ClientCmd_Unrestricted2("lastinv");
			}
		}
	}
}

void  legitbot::AimSniper(C_BaseEntity *local)
{
	if (g_Options.Legitbot.Aimbot.AimSniper && local->IsAlive())
	{
		ConVar* crosshair1 = Interfaces::CVar()->FindVar("weapon_debug_spread_show");
		crosshair1->SetValue(1);
		ConVar* crosshair2 = Interfaces::CVar()->FindVar("weapon_debug_spread_gap");
		crosshair2->SetValue(999999999);
	}
	else
	{
		ConVar* crosshair1 = Interfaces::CVar()->FindVar("weapon_debug_spread_show");
		crosshair1->SetValue(0);
		ConVar* crosshair2 = Interfaces::CVar()->FindVar("weapon_debug_spread_gap");
		crosshair2->SetValue(0);
	}

}
void legitbot::do_aimbot(C_BaseEntity *local, CBaseCombatWeapon *weapon, CInput::CUserCmd *cmd)
{
	if (!g_Options.Legitbot.MainSwitch)
		return;

	if (!weapon)
		return;

	if (!local)
		return;
	if (!cmd)
		return;

	if (!local->IsAlive())
		return;

	if (!weapon->ammo() > 0)
		return;


	if (weapon->ammo() == 0)
		return;

	if (MiscFunctions::IsKnife(weapon) || MiscFunctions::IsGrenade(weapon))
		return;


	weapon_settings(weapon);

	if (!aim_key)
		return;

	if (!((AutoLock) || (G::PressedKeys[aim_key])))
		return;

	best_target = get_target(local, weapon, cmd, hitbox_position);


	if (best_target == -1)
		return;
	C_BaseEntity* entity = (C_BaseEntity*)Interfaces::EntityList()->GetClientEntity(best_target);
	if (!entity)
		return;



	if (get_distance(local->GetEyePosition(), hitbox_position) > 8192.0f)
		return;

	if (!hitbox_position.IsValid())
		return;

	VectorAngles1(hitbox_position - local->GetEyePosition(), aim_angle);

	float fSmooth = 10.f;

	fSmooth = aim_smooth;

	AngleNormalize(aim_angle);

	if (fSmooth < 10.f)
		fSmooth = 10.f;

	fSmooth = fSmooth / 10.f;

	SmoothAngles(view_angle, aim_angle, vSmoothAimAngle, fSmooth);


	if (Silent)
	{
		if (CanAttack()) {
			cmd->viewangles = vSmoothAimAngle;
		}
	}
	else
	{
	cmd->viewangles = vSmoothAimAngle;
	Interfaces::Engine()->SetViewAngles(cmd->viewangles);
	}
}
void legitbot::RCS(C_BaseEntity* local, CInput::CUserCmd* cmd, CBaseCombatWeapon* weapon)
{

	float MulVar = aim_rcs * 0.02f;
	
	switch (aim_rcstype)
	{
	case 0:
		cmd->viewangles -= local->localPlayerExclusive()->GetAimPunchAngle() * MulVar;
		break;
	case 1:
		cmd->viewangles -= (local->localPlayerExclusive()->GetViewPunchAngle() + local->localPlayerExclusive()->GetAimPunchAngle()) * MulVar;
		break;
	case 2:
		cmd->viewangles -= (local->localPlayerExclusive()->GetViewPunchAngle() + (local->localPlayerExclusive()->GetAimPunchAngle() * 2 * 0.5f)) * MulVar;
		break;
	case 3:
		if (!MiscFunctions::IsSniper(weapon))
		{
			static Vector vOldPunch = { 0.0f, 0.0f, 0.0f };
			Vector vNewPunch = local->localPlayerExclusive()->GetAimPunchAngle();

			vNewPunch *=  MulVar;

			vNewPunch -= vOldPunch;
			vNewPunch += vOldPunch;

			QAngle vFinal = cmd->viewangles - (vNewPunch - vOldPunch);

			sanitize_angles(vFinal);

			ClampAngles(vFinal);

			Interfaces::Engine()->SetViewAngles(vFinal);

			vOldPunch = vNewPunch;
		}
		break;
	default:
		break;
	}

}
bool legitbot::hit_chance(C_BaseEntity* local, CInput::CUserCmd* cmd, CBaseCombatWeapon* weapon, C_BaseEntity* target)
{
	Vector forward, right, up;

	constexpr auto max_traces = 150;

	AngleVectors(cmd->viewangles, &forward, &right, &up);

	int total_hits = 0;
	int needed_hits = static_cast<int>(max_traces * (Triggerbot_hitchance / 100.f));

	weapon->UpdateAccuracyPenalty(weapon);

	auto eyes = local->GetEyePosition();
	auto flRange = weapon->GetCSWpnData()->range;

	for (int i = 0; i < max_traces; i++) {
		float RandomA = RandomFloat(0.0f, 1.0f);
		float RandomB = 1.0f - RandomA * RandomA;

		RandomA = RandomFloat(0.0f, M_PI_F * 2.0f);
		RandomB *= weapon->GetInaccuracy();

		float SpreadX1 = (cos(RandomA) * RandomB);
		float SpreadY1 = (sin(RandomA) * RandomB);

		float RandomC = RandomFloat(0.0f, 1.0f);
		float RandomF = RandomF = 1.0f - RandomC * RandomC;

		RandomC = RandomFloat(0.0f, M_PI_F * 2.0f);
		RandomF *= weapon->GetSpread();

		float SpreadX2 = (cos(RandomC) * RandomF);
		float SpreadY2 = (sin(RandomC) * RandomF);

		float fSpreadX = SpreadX1 + SpreadX2;
		float fSpreadY = SpreadY1 + SpreadY2;

		Vector vSpreadForward;
		vSpreadForward[0] = forward[0] + (fSpreadX * right[0]) + (fSpreadY * up[0]);
		vSpreadForward[1] = forward[1] + (fSpreadX * right[1]) + (fSpreadY * up[1]);
		vSpreadForward[2] = forward[2] + (fSpreadX * right[2]) + (fSpreadY * up[2]);
		vSpreadForward.NormalizeInPlace();

		QAngle qaNewAngle;
		VectorAngles1(vSpreadForward, qaNewAngle);
		AngleNormalize(qaNewAngle);

		QAngle vEnd;
		AngleVectors(qaNewAngle, &vEnd);

		vEnd = eyes + (vEnd * flRange);

		trace_t tr;
		Ray_t ray;
		ray.Init(eyes, vEnd);

		Interfaces::EngineTrace()->ClipRayToEntity(ray, MASK_SHOT | CONTENTS_GRATE, target, &tr);


		if (tr.m_pEnt == target)
			total_hits++;

		if (total_hits >= needed_hits)
			return true;

		if ((max_traces - i + total_hits) < needed_hits)
			return false;
	}

	return false;
}

void legitbot::weapon_settings(CBaseCombatWeapon* weapon)
{
	if (!weapon)
		return;


	if (MiscFunctions::IsSniper(weapon))
	{
		aim_key = g_Options.Legitbot.SniperKey;
		aim_smooth = g_Options.Legitbot.Sniper_Smooth;
		aim_fov = g_Options.Legitbot.Sniperfov;
		draw_fov = g_Options.Legitbot.Sniper_drawfov;
		fakelag_mode = g_Options.Legitbot.Sniper_fakelag_mode;
		nfakelag = g_Options.Legitbot.Sniper_fakelag_value;
		fakelag = g_Options.Legitbot.Sniper_fakelag;
		hitboxpon = g_Options.Legitbot.hitboxsniper;
		aim_rcs = g_Options.Legitbot.sniper_rcs;
		aim_rcstype = g_Options.Legitbot.sniper_RcsType;
		Silent = g_Options.Legitbot.sniper_Silent;
		AutoLock = g_Options.Legitbot.sniper_AutoLock;
		Triggerbot = g_Options.Legitbot.sniper_Triggerbot;
		TriggerbotKey = g_Options.Legitbot.sniper_TriggerbotKey;
		Triggerbot_AutoFire = g_Options.Legitbot.sniper_Triggerbot_AutoFire;
		TriggerbotDelay = g_Options.Legitbot.sniper_TriggerbotDelay;
		Triggerbot_hitchance = g_Options.Legitbot.sniper_Triggerbot_hitchance;
		Triggerbot_Filter.Arms = g_Options.Legitbot.sniper_TriggerbotFilter.Arms;
		Triggerbot_Filter.Chest = g_Options.Legitbot.sniper_TriggerbotFilter.Chest;
		Triggerbot_Filter.Head = g_Options.Legitbot.sniper_TriggerbotFilter.Head;
		Triggerbot_Filter.Legs = g_Options.Legitbot.sniper_TriggerbotFilter.Legs;
		Triggerbot_Filter.Stomach = g_Options.Legitbot.sniper_TriggerbotFilter.Stomach;
	}
	else if (MiscFunctions::IsPistol(weapon))
	{
		aim_key = g_Options.Legitbot.PistolKey;
		aim_smooth = g_Options.Legitbot.Pistol_Smooth;
		aim_fov = g_Options.Legitbot.Pistolfov;
		draw_fov = g_Options.Legitbot.Pistol_drawfov;
		fakelag_mode = g_Options.Legitbot.Pistol_fakelag_mode;
		nfakelag = g_Options.Legitbot.Pistol_fakelag_value;
		fakelag = g_Options.Legitbot.Pistol_fakelag;
		hitboxpon = g_Options.Legitbot.hitboxpistol;
		aim_rcs = g_Options.Legitbot.Pistol_rcs;
		aim_rcstype = g_Options.Legitbot.Pistol_RcsType;
		Silent = g_Options.Legitbot.Pistol_Silent;
		AutoLock = g_Options.Legitbot.Pistol_AutoLock;
		Triggerbot = g_Options.Legitbot.Pistol_Triggerbot;
		TriggerbotKey = g_Options.Legitbot.Pistol_TriggerbotKey;
		Triggerbot_AutoFire = g_Options.Legitbot.Pistol_Triggerbot_AutoFire;
		TriggerbotDelay = g_Options.Legitbot.Pistol_TriggerbotDelay;
		Triggerbot_hitchance = g_Options.Legitbot.Pistol_Triggerbot_hitchance;
		Triggerbot_Filter.Arms = g_Options.Legitbot.Pistol_TriggerbotFilter.Arms;
		Triggerbot_Filter.Chest = g_Options.Legitbot.Pistol_TriggerbotFilter.Chest;
		Triggerbot_Filter.Head = g_Options.Legitbot.Pistol_TriggerbotFilter.Head;
		Triggerbot_Filter.Legs = g_Options.Legitbot.Pistol_TriggerbotFilter.Legs;
		Triggerbot_Filter.Stomach = g_Options.Legitbot.Pistol_TriggerbotFilter.Stomach;
	}
	else if (MiscFunctions::IsHeavy(weapon))
	{
		aim_key = g_Options.Legitbot.heavyKey;
		aim_smooth = g_Options.Legitbot.heavy_Smooth;
		aim_fov = g_Options.Legitbot.heavyfov;
		draw_fov = g_Options.Legitbot.heavy_drawfov;
		fakelag_mode = g_Options.Legitbot.heavy_fakelag_mode;
		nfakelag = g_Options.Legitbot.heavy_fakelag_value;
		fakelag = g_Options.Legitbot.heavy_fakelag;
		hitboxpon = g_Options.Legitbot.hitboxheavy;
		Triggerbot = g_Options.Legitbot.heavy_Triggerbot;
		aim_rcs = g_Options.Legitbot.heavy_rcs;
		aim_rcstype = g_Options.Legitbot.heavy_RcsType;
		Silent = g_Options.Legitbot.heavy_Silent;
		AutoLock = g_Options.Legitbot.heavy_AutoLock;
		TriggerbotKey = g_Options.Legitbot.heavy_TriggerbotKey;
		Triggerbot_AutoFire = g_Options.Legitbot.heavy_Triggerbot_AutoFire;
		TriggerbotDelay = g_Options.Legitbot.heavy_TriggerbotDelay;
		Triggerbot_hitchance = g_Options.Legitbot.heavy_Triggerbot_hitchance;
		Triggerbot_Filter.Arms = g_Options.Legitbot.heavy_TriggerbotFilter.Arms;
		Triggerbot_Filter.Chest = g_Options.Legitbot.heavy_TriggerbotFilter.Chest;
		Triggerbot_Filter.Head = g_Options.Legitbot.heavy_TriggerbotFilter.Head;
		Triggerbot_Filter.Legs = g_Options.Legitbot.heavy_TriggerbotFilter.Legs;
		Triggerbot_Filter.Stomach = g_Options.Legitbot.heavy_TriggerbotFilter.Stomach;
	}
	else if (MiscFunctions::IsSmg(weapon))
	{
		aim_key = g_Options.Legitbot.smgKey;
		aim_smooth = g_Options.Legitbot.smg_Smooth;
		aim_fov = g_Options.Legitbot.smgfov;
		draw_fov = g_Options.Legitbot.smg_drawfov;
		fakelag_mode = g_Options.Legitbot.smg_fakelag_mode;
		nfakelag = g_Options.Legitbot.smg_fakelag_value;
		fakelag = g_Options.Legitbot.smg_fakelag;
		hitboxpon = g_Options.Legitbot.hitboxsmg;
		aim_rcs = g_Options.Legitbot.smg_rcs;
		aim_rcstype = g_Options.Legitbot.smg_RcsType;
		Silent = g_Options.Legitbot.smg_Silent;
		AutoLock = g_Options.Legitbot.smg_AutoLock;
		Triggerbot = g_Options.Legitbot.smg_Triggerbot;
		TriggerbotKey = g_Options.Legitbot.smg_TriggerbotKey;
		Triggerbot_AutoFire = g_Options.Legitbot.smg_Triggerbot_AutoFire;
		TriggerbotDelay = g_Options.Legitbot.smg_TriggerbotDelay;
		Triggerbot_hitchance = g_Options.Legitbot.smg_Triggerbot_hitchance;
		Triggerbot_Filter.Arms = g_Options.Legitbot.smg_TriggerbotFilter.Arms;
		Triggerbot_Filter.Chest = g_Options.Legitbot.smg_TriggerbotFilter.Chest;
		Triggerbot_Filter.Head = g_Options.Legitbot.heavy_TriggerbotFilter.Head;
		Triggerbot_Filter.Legs = g_Options.Legitbot.heavy_TriggerbotFilter.Legs;
		Triggerbot_Filter.Stomach = g_Options.Legitbot.heavy_TriggerbotFilter.Stomach;
	}
	else if (MiscFunctions::IsRifle(weapon))
	{
		aim_key = g_Options.Legitbot.MainKey;
		aim_smooth = g_Options.Legitbot.Main_Smooth;
		aim_fov = g_Options.Legitbot.Mainfov;
		draw_fov = g_Options.Legitbot.main_drawfov;
		fakelag_mode = g_Options.Legitbot.main_fakelag_mode;
		nfakelag = g_Options.Legitbot.main_fakelag_value;
		fakelag = g_Options.Legitbot.main_fakelag;
		hitboxpon = g_Options.Legitbot.hitboxrifle;
		aim_rcs = g_Options.Legitbot.main_rcs;
		aim_rcstype = g_Options.Legitbot.main_RcsType;
		Silent = g_Options.Legitbot.main_Silent;
		AutoLock = g_Options.Legitbot.main_AutoLock;
		Triggerbot = g_Options.Legitbot.main_Triggerbot;
		TriggerbotKey = g_Options.Legitbot.main_TriggerbotKey;
		Triggerbot_AutoFire = g_Options.Legitbot.main_Triggerbot_AutoFire;
		TriggerbotDelay = g_Options.Legitbot.main_TriggerbotDelay;
		Triggerbot_hitchance = g_Options.Legitbot.main_Triggerbot_hitchance;
		Triggerbot_Filter.Arms = g_Options.Legitbot.main_TriggerbotFilter.Arms;
		Triggerbot_Filter.Chest = g_Options.Legitbot.main_TriggerbotFilter.Chest;
		Triggerbot_Filter.Head = g_Options.Legitbot.main_TriggerbotFilter.Head;
		Triggerbot_Filter.Legs = g_Options.Legitbot.main_TriggerbotFilter.Legs;
		Triggerbot_Filter.Stomach = g_Options.Legitbot.main_TriggerbotFilter.Stomach;
	}
	else if (MiscFunctions::IsRevolver(weapon))
	{
		aim_key = g_Options.Legitbot.RevolverKey;
		aim_smooth = g_Options.Legitbot.Revolver_Smooth;
		aim_fov = g_Options.Legitbot.Revolverfov;
		draw_fov = g_Options.Legitbot.Revolver_drawfov;
		fakelag_mode = g_Options.Legitbot.Revolver_fakelag_mode;
		nfakelag = g_Options.Legitbot.Revolver_fakelag_value;
		fakelag = g_Options.Legitbot.Revolver_fakelag;
		hitboxpon = g_Options.Legitbot.hitboxRevolver;
		aim_rcs = g_Options.Legitbot.Revolver_rcs;
		aim_rcstype = g_Options.Legitbot.Revolver_RcsType;
		Silent = g_Options.Legitbot.Revolver_Silent;
		AutoLock = g_Options.Legitbot.Revolver_AutoLock;
		Triggerbot = g_Options.Legitbot.Revolver_Triggerbot;
		TriggerbotKey = g_Options.Legitbot.Revolver_TriggerbotKey;
		Triggerbot_AutoFire = g_Options.Legitbot.Revolver_Triggerbot_AutoFire;
		TriggerbotDelay = g_Options.Legitbot.Revolver_TriggerbotDelay;
		Triggerbot_hitchance = g_Options.Legitbot.Revolver_Triggerbot_hitchance;
		Triggerbot_Filter.Arms = g_Options.Legitbot.Revolver_TriggerbotFilter.Arms;
		Triggerbot_Filter.Chest = g_Options.Legitbot.Revolver_TriggerbotFilter.Chest;
		Triggerbot_Filter.Head = g_Options.Legitbot.Revolver_TriggerbotFilter.Head;
		Triggerbot_Filter.Legs = g_Options.Legitbot.Revolver_TriggerbotFilter.Legs;
		Triggerbot_Filter.Stomach = g_Options.Legitbot.Revolver_TriggerbotFilter.Stomach;
	}
}

bool get_hitbox_pos(C_BaseEntity* entity, int hitbox, Vector &output)
{
	if (hitbox >= 20)
		return false;

	const model_t *model = entity->GetModel();
	if (!model)
		return false;

	studiohdr_t *studioHdr = Interfaces::ModelInfo()->GetStudiomodel(model);
	if (!studioHdr)
		return false;

	matrix3x4_t matrix[128];
	if (!entity->SetupBones(matrix, 128, 0x100, entity->GetSimulationTime()))
		return false;

	mstudiobbox_t *studioBox = studioHdr->GetHitboxSet(0)->GetHitbox(hitbox);
	if (!studioBox)
		return false;

	Vector min, max;

	VectorTransform(studioBox->bbmin, matrix[studioBox->bone], min);
	VectorTransform(studioBox->bbmax, matrix[studioBox->bone], max);

	output = (min + max) * 0.5f;

	return true;
}
bool legitbot::get_hitbox(C_BaseEntity *local, C_BaseEntity *entity, Vector &destination)
{
	int bestHitbox = -1;
	float best_fov = aim_fov;
	std::vector<int> HitBoxesToScan{};
	switch (hitboxpon)
	{
	case 0:
		HitBoxesToScan.push_back(Head);
		break;
	case 1:
		HitBoxesToScan.push_back(Neck);
		break;
	case 2:
		HitBoxesToScan.push_back(UpperChest);
		break;
	case 3:
		HitBoxesToScan.push_back(Stomach);
		break;
	case 4:
		HitBoxesToScan.push_back(Pelvis);
		break;
	case 5:
		HitBoxesToScan.push_back(Head);
		HitBoxesToScan.push_back(Neck);
		HitBoxesToScan.push_back(UpperChest);
		HitBoxesToScan.push_back(Stomach);
		HitBoxesToScan.push_back(Pelvis);

		break;
	default:
		break;
	}

	for (auto hitbox : HitBoxesToScan)
	{
		Vector temp;
		if (!get_hitbox_pos(entity, hitbox, temp))
			continue;

		float fov = get_fov(view_angle, compute_angle(local->GetEyePosition(), temp));
		if (fov < best_fov)
		{
			best_fov = fov;
			bestHitbox = hitbox;
		}
	}

	if (bestHitbox != -1)
	{
		if (!get_hitbox_pos(entity, bestHitbox, destination))
			return true;
	}

	return false;
}


int legitbot::get_target(C_BaseEntity *local, CBaseCombatWeapon *weapon, CInput::CUserCmd *cmd, Vector &destination)
{
	typedef bool(__cdecl* GoesThroughSmoke)(Vector, Vector);
	static uint32_t GoesThroughSmokeOffset = (uint32_t)CSX::Memory::NewPatternScan(GetModuleHandleW(L"client_panorama.dll"), ("55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0"));
	static GoesThroughSmoke GoesThroughSmokeFunction = (GoesThroughSmoke)GoesThroughSmokeOffset;
	Vector ang;
	ang[0] = local->GetEyePosition().x;
	ang[1] = local->GetEyePosition().y;
	ang[2] = local->GetEyePosition().z;

	int best_target = -1;
	float best_fov = aim_fov;

	Interfaces::Engine()->GetViewAngles(view_angle);

	for (int i = 1; i <= Interfaces::Globals()->maxClients; i++)
	{
		C_BaseEntity *entity = (C_BaseEntity*)Interfaces::EntityList()->GetClientEntity(i);
		if (!entity
			|| entity == local
			|| entity->IsDormant()
			|| entity->GetLifeState() != LIFE_ALIVE
			|| entity->HasGunGameImmunity()
			|| entity->GetClientClass()->m_ClassID != (int)ClassID::CCSPlayer
			|| entity->GetTeamNum() == local->GetTeamNum()
			|| !(entity->GetFlags() & FL_ONGROUND))
			continue;

		Vector hitbox;

		if (get_hitbox(local, entity, hitbox))
			continue;

		if (g_Options.Legitbot.checksmoke && GoesThroughSmokeFunction(ang, hitbox))
			continue;

		float fov = get_fov(view_angle + (local->localPlayerExclusive()->GetAimPunchAngle() * 2.0f), compute_angle(local->GetEyePosition(), hitbox));
		if (fov < best_fov && fov < aim_fov)
		{
			if (MiscFunctions::IsVisible(local, entity))
			{
				best_fov = fov;
				destination = hitbox;
				best_target = i;
			}
		}
	}

	return best_target;
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class lqaayuy {
public:
	int ksnherbi;
	double esbottwfdczpzs;
	string lhokcwthgafoj;
	bool nvdxguxjekfd;
	bool paoba;
	lqaayuy();
	int rcqsltbbcefkdncieu(double jmutiuzuwkt, double dpsrg, string cpalmk, double vvrso, int hbimlycunfp);
	void gaftqbimlgji(string olevdlceoe, int msfvdtrflv, int hzkgdaxvbj, bool sfogncg, double jkneabwxjkyev, int shpfghyzcqsfr, string cmdxrpuhqpntkl, bool bivswwvaunwc, double cgzeqalboxxokbx, string rttnoi);
	double kodoofxqndhjtikzj(double fjzrqycglkfmvwu, string nfjkhmiacsbfbo, double bsaseknrm, int nabrojlwekcns, string rdowmioa, int kjxvxkwlru, string favfdbgq, string wubix, string qipcsaaw);
	double dviburqjzcchwnffmsczpjg(string wcaghee, string qiope);
	int ioyqdzkkpfwmumwiuvouiozu(bool ngluxgy, int kbupew, int iwsqfxytpoesto, bool phqmpllsgyk, int qctdzbvzvdihuxw, bool svrwxrs, string hobmixaqvgoqyv, int qxttsqzzs);
	bool udikbpimhwmbohlqqcapm(string yxvtifxdbudkbt, double oaxquweirblridi, bool islpgfjmyse, bool psqnpczdzc, string tbhqklpc, int vmqobign, int btvssflsvdkljtn, bool waggrdowxacaua, string leqnqos, int jeeervnjjkenn);
	double nvepomypgxxailmr(int prfotbqcmvv);
	string upzdmlmxxyiqxo(double phogeiw, double ctbolbnaetmqneh, int eegvg, int iicedrvclbii, int mbjcjvk, bool fkpfehqbkxamnsr, bool txcklqeffkkj, int lkepgyknhhuhkhv, string kpwuiwoidltst);
	int gcqloqncrnuu(bool romtcmmemwkufc, int cvkeav, string cmvrz, int kwqktcccwc, bool bgkxqavmpevuisy, bool biwdvnhjnzni, string zbhixauuokwnc, string qbjngtrsuxjpvsz, double zeril, bool umurlyteq);
	void scvfhpknjfcgsy(int mnmhzhfvlddpe, double kqenucrd, int kdunc);

protected:
	double pljnrhga;
	int meeldasfe;
	string zmuog;

	double wmvxxxuuwpwnyyoxw(double ildgyrbelawetfl, double rvpkrats, int kybfhw, double wiffmgmvttozcq, bool ujcefdiso, bool aehmwavkk);
	int qrwpzzvllxrbkgghdsekqu(double botjxdkxw, bool bpetvi, double vnbsgjnwpcwyrqv, string uhekyrpfieweus, double jiauk, double lkbvtiaupiwmoc, bool aykessbtktkeoyd);
	double zpuwmaqpsggg(bool porvydpqutojzjd, bool hiusgneyrzvsf, double vovjcaeibw, double echpnzipeyjg, int wqaxyoakcioa, double gzlyx, double umiwyydnnp, string ildiwkuwyo, bool brezk, int yqpvbjsvgvyxya);

private:
	bool nvggnqdruslnc;
	double aleon;
	string vzvrgpyxhskocso;

	int xkqygcppfpfrxnovciaez(bool smoqlmrx, string bgmuz, bool pkkycudnwbbupg, bool jegduhsrnuu, int dhfitcledpc);
	bool cyutrqcnwkmxqvnlkckmkjwr(int fdsvcbmdwtvpj, bool jgeksfkyniugo, int fxsikbdvkgzs, string yotsyturtapqctr, int kommmqbjxt, double mhyedgrrv, int ujbzqbyrzn);
	bool iszlfikreukcahgf(double jmkceqjzfgv, int ryexpqlyudxmprz);
	int cuhdpzhlibfzabmwolrogygzu(double vtqdu, string kuhvzshhl, bool dutkbwjxxyws, double kdbchpnoqvyns);
	bool vgmjxxzrdcptqdynewmnrtb(string udemccpderiq);
	double jsycmophrg(int bcbititurnxby, string oypkz, double yyqbvfnhy, string cfeiljlhghiu, string vgtnhmwobic);

};


int lqaayuy::xkqygcppfpfrxnovciaez(bool smoqlmrx, string bgmuz, bool pkkycudnwbbupg, bool jegduhsrnuu, int dhfitcledpc) {
	string kdoxqvlhhzfys = "shsdpbjnevkzgeqyqzfmtacjffdclodffiymbvrnzzhznjnadbkzozrqwduzlvclbomiaaqhvtmex";
	int aqhpkwdbi = 2381;
	int cizjk = 3574;
	string soghfmiq = "bxtvnufvrvlixlkchfoasdwuugnupafbvtkhtjzkoyvjkrxbygowr";
	string dpofiowoxwjbss = "xdoqoswmvqxhxclxwa";
	double rokikwel = 43454;
	int tisqybktvt = 1465;
	bool mnqefcuaal = false;
	string ewxwpafoicc = "ixlfmvieqtrmwksxhypnqfgnsdgmvkixvsjljgfilwemavqe";
	if (string("bxtvnufvrvlixlkchfoasdwuugnupafbvtkhtjzkoyvjkrxbygowr") != string("bxtvnufvrvlixlkchfoasdwuugnupafbvtkhtjzkoyvjkrxbygowr")) {
		int acrdpx;
		for (acrdpx = 10; acrdpx > 0; acrdpx--) {
			continue;
		}
	}
	return 51923;
}

bool lqaayuy::cyutrqcnwkmxqvnlkckmkjwr(int fdsvcbmdwtvpj, bool jgeksfkyniugo, int fxsikbdvkgzs, string yotsyturtapqctr, int kommmqbjxt, double mhyedgrrv, int ujbzqbyrzn) {
	double eyvpceyqo = 71681;
	double lupmrokhtxxw = 24128;
	string swykzzcpsuchku = "cpaonhvqwonsbtjdjpimqqhsenodpvqazukrwlnxbdabtxdwowcqluuqptvtfksuqqhoavmrfqtbzewu";
	bool zyzahqn = true;
	bool ecjydvmd = true;
	if (24128 != 24128) {
		int gwnyhxnme;
		for (gwnyhxnme = 30; gwnyhxnme > 0; gwnyhxnme--) {
			continue;
		}
	}
	if (true != true) {
		int qwuewu;
		for (qwuewu = 4; qwuewu > 0; qwuewu--) {
			continue;
		}
	}
	return true;
}

bool lqaayuy::iszlfikreukcahgf(double jmkceqjzfgv, int ryexpqlyudxmprz) {
	string kccitqbop = "hpghqeaqlgzcwepetzglyoahcqoizwtiopqgmndvzqejpmknlhyqrrttctwhkefzffgignyfzkuzvotkatztiupcacrneus";
	bool ljvuisys = true;
	bool dxnego = true;
	int njwuzbeansiyqas = 1000;
	string jococemvtqmd = "dgisrilwiehqgqhhoihtnyvemhlhxskuovhnfeqremweydigmrvmdgzkivnodhcxtoiclt";
	double vdavff = 26634;
	double dbolctpgxzmpux = 26587;
	string ifhmsjeyli = "law";
	bool kzkemjx = true;
	if (string("dgisrilwiehqgqhhoihtnyvemhlhxskuovhnfeqremweydigmrvmdgzkivnodhcxtoiclt") == string("dgisrilwiehqgqhhoihtnyvemhlhxskuovhnfeqremweydigmrvmdgzkivnodhcxtoiclt")) {
		int vj;
		for (vj = 73; vj > 0; vj--) {
			continue;
		}
	}
	if (string("law") != string("law")) {
		int jepdojte;
		for (jepdojte = 99; jepdojte > 0; jepdojte--) {
			continue;
		}
	}
	if (26587 != 26587) {
		int wwhvijw;
		for (wwhvijw = 72; wwhvijw > 0; wwhvijw--) {
			continue;
		}
	}
	return true;
}

int lqaayuy::cuhdpzhlibfzabmwolrogygzu(double vtqdu, string kuhvzshhl, bool dutkbwjxxyws, double kdbchpnoqvyns) {
	bool pyvcwrd = false;
	int iszosnhpukmbxnb = 1258;
	if (1258 != 1258) {
		int ipxcughrt;
		for (ipxcughrt = 34; ipxcughrt > 0; ipxcughrt--) {
			continue;
		}
	}
	return 12931;
}

bool lqaayuy::vgmjxxzrdcptqdynewmnrtb(string udemccpderiq) {
	bool hdwglwy = true;
	int mbhnuidz = 1278;
	bool affjlglmoisp = false;
	if (false != false) {
		int dcjvjsz;
		for (dcjvjsz = 69; dcjvjsz > 0; dcjvjsz--) {
			continue;
		}
	}
	if (false != false) {
		int saanqlix;
		for (saanqlix = 10; saanqlix > 0; saanqlix--) {
			continue;
		}
	}
	if (false != false) {
		int lhle;
		for (lhle = 13; lhle > 0; lhle--) {
			continue;
		}
	}
	if (true == true) {
		int yykmpuus;
		for (yykmpuus = 68; yykmpuus > 0; yykmpuus--) {
			continue;
		}
	}
	if (false == false) {
		int kxiqzww;
		for (kxiqzww = 31; kxiqzww > 0; kxiqzww--) {
			continue;
		}
	}
	return false;
}

double lqaayuy::jsycmophrg(int bcbititurnxby, string oypkz, double yyqbvfnhy, string cfeiljlhghiu, string vgtnhmwobic) {
	int nyrqoyulwabdxe = 5452;
	int uvpkigtmpremn = 920;
	bool yqgadlpxstrcc = true;
	bool faicyt = true;
	string jvxpmpnofvi = "doptuclvyzvljisysneddawawfnfekiktgwplafpinazifxfdxdhbzqzckhhl";
	string bpgbhu = "bsegzfmjwokbuvuoulqbylkrilxcfegupkvokofdovdltrkyeemkbth";
	string osemdpryirnxyys = "fffmmmubeeiyvjcmsufxojfwjlwywarbkyarugtltzwbbaxjxvlklwhgtnryxemw";
	string xzgri = "rfmnlhcgqhpdveaeagtjalobfx";
	string kvowefpbnsudzsn = "vofswqezbejxgaedcjvlnicvinnrotnfrkbkhudlyghkcvbhfvswycx";
	double njegyfqyoquwcqk = 589;
	if (true == true) {
		int yltiddale;
		for (yltiddale = 26; yltiddale > 0; yltiddale--) {
			continue;
		}
	}
	if (589 != 589) {
		int mcaafyj;
		for (mcaafyj = 44; mcaafyj > 0; mcaafyj--) {
			continue;
		}
	}
	if (string("doptuclvyzvljisysneddawawfnfekiktgwplafpinazifxfdxdhbzqzckhhl") != string("doptuclvyzvljisysneddawawfnfekiktgwplafpinazifxfdxdhbzqzckhhl")) {
		int xhmwvwl;
		for (xhmwvwl = 73; xhmwvwl > 0; xhmwvwl--) {
			continue;
		}
	}
	if (920 != 920) {
		int vhrc;
		for (vhrc = 37; vhrc > 0; vhrc--) {
			continue;
		}
	}
	return 83975;
}

double lqaayuy::wmvxxxuuwpwnyyoxw(double ildgyrbelawetfl, double rvpkrats, int kybfhw, double wiffmgmvttozcq, bool ujcefdiso, bool aehmwavkk) {
	return 16839;
}

int lqaayuy::qrwpzzvllxrbkgghdsekqu(double botjxdkxw, bool bpetvi, double vnbsgjnwpcwyrqv, string uhekyrpfieweus, double jiauk, double lkbvtiaupiwmoc, bool aykessbtktkeoyd) {
	double nscgdsywspogr = 18511;
	if (18511 != 18511) {
		int rgslindebb;
		for (rgslindebb = 48; rgslindebb > 0; rgslindebb--) {
			continue;
		}
	}
	if (18511 == 18511) {
		int spuhbqun;
		for (spuhbqun = 90; spuhbqun > 0; spuhbqun--) {
			continue;
		}
	}
	if (18511 == 18511) {
		int kws;
		for (kws = 84; kws > 0; kws--) {
			continue;
		}
	}
	return 48367;
}

double lqaayuy::zpuwmaqpsggg(bool porvydpqutojzjd, bool hiusgneyrzvsf, double vovjcaeibw, double echpnzipeyjg, int wqaxyoakcioa, double gzlyx, double umiwyydnnp, string ildiwkuwyo, bool brezk, int yqpvbjsvgvyxya) {
	string gedkongrbc = "bdzbnbyxwxrveobuwknciandminvbjuahnrlgrxcshqrwx";
	return 86943;
}

int lqaayuy::rcqsltbbcefkdncieu(double jmutiuzuwkt, double dpsrg, string cpalmk, double vvrso, int hbimlycunfp) {
	bool eytecshxcxqrgxd = false;
	bool dyijepnbhhseh = true;
	string dilogudd = "wpjwxqmckpxlkygowxvylvztyvgcvlrytujbbyudzjigsahfbvcqomedjpueatwbhquwgno";
	double aqrmul = 14565;
	double lvpdxag = 10469;
	string kdygd = "bjahulukpselvyceaaotqodndgydvbsfncxxogeflfgq";
	bool qttohjeznk = false;
	double nybmutdglvdensd = 8089;
	int cwzzs = 7134;
	string gpaxjjstpkm = "hudhpensxqhlyamsmrdhelzexavtanrfyjoel";
	if (14565 == 14565) {
		int aua;
		for (aua = 50; aua > 0; aua--) {
			continue;
		}
	}
	if (10469 != 10469) {
		int oiuslk;
		for (oiuslk = 98; oiuslk > 0; oiuslk--) {
			continue;
		}
	}
	if (string("wpjwxqmckpxlkygowxvylvztyvgcvlrytujbbyudzjigsahfbvcqomedjpueatwbhquwgno") == string("wpjwxqmckpxlkygowxvylvztyvgcvlrytujbbyudzjigsahfbvcqomedjpueatwbhquwgno")) {
		int vn;
		for (vn = 3; vn > 0; vn--) {
			continue;
		}
	}
	if (string("wpjwxqmckpxlkygowxvylvztyvgcvlrytujbbyudzjigsahfbvcqomedjpueatwbhquwgno") != string("wpjwxqmckpxlkygowxvylvztyvgcvlrytujbbyudzjigsahfbvcqomedjpueatwbhquwgno")) {
		int fooradhyww;
		for (fooradhyww = 28; fooradhyww > 0; fooradhyww--) {
			continue;
		}
	}
	return 6447;
}

void lqaayuy::gaftqbimlgji(string olevdlceoe, int msfvdtrflv, int hzkgdaxvbj, bool sfogncg, double jkneabwxjkyev, int shpfghyzcqsfr, string cmdxrpuhqpntkl, bool bivswwvaunwc, double cgzeqalboxxokbx, string rttnoi) {
	bool iecztsqbrrlgky = true;
	string jhinm = "rhesuqdbuzxmcqvkszkipvkamesebwdrbhwtrwglnwrdxoqpyrngtxftbranlvaamokpkznyrbesbpozglknriex";
	string aktukaapjkfm = "beldvlsxfhpgzsowgropsgtgkqhkcuykvxjqvcpcwqnpyhksxziajziddmqra";
	if (string("beldvlsxfhpgzsowgropsgtgkqhkcuykvxjqvcpcwqnpyhksxziajziddmqra") == string("beldvlsxfhpgzsowgropsgtgkqhkcuykvxjqvcpcwqnpyhksxziajziddmqra")) {
		int nzkbhjpqel;
		for (nzkbhjpqel = 35; nzkbhjpqel > 0; nzkbhjpqel--) {
			continue;
		}
	}
	if (string("rhesuqdbuzxmcqvkszkipvkamesebwdrbhwtrwglnwrdxoqpyrngtxftbranlvaamokpkznyrbesbpozglknriex") != string("rhesuqdbuzxmcqvkszkipvkamesebwdrbhwtrwglnwrdxoqpyrngtxftbranlvaamokpkznyrbesbpozglknriex")) {
		int go;
		for (go = 58; go > 0; go--) {
			continue;
		}
	}

}

double lqaayuy::kodoofxqndhjtikzj(double fjzrqycglkfmvwu, string nfjkhmiacsbfbo, double bsaseknrm, int nabrojlwekcns, string rdowmioa, int kjxvxkwlru, string favfdbgq, string wubix, string qipcsaaw) {
	int fjlswaoyjyzb = 1675;
	return 20345;
}

double lqaayuy::dviburqjzcchwnffmsczpjg(string wcaghee, string qiope) {
	double moocebyfjb = 2518;
	bool billgy = true;
	bool cmizllzez = true;
	bool glkmolzgdypa = false;
	string zyetyttwn = "wppbwamcmmldcebygldybxdzzvloydltorcsysxbzyhg";
	double kpckserrsp = 4479;
	double msupiiyijnapkz = 13036;
	string nyrtdbouicpnjwm = "yiqkleziw";
	if (true != true) {
		int gb;
		for (gb = 89; gb > 0; gb--) {
			continue;
		}
	}
	if (true == true) {
		int gh;
		for (gh = 100; gh > 0; gh--) {
			continue;
		}
	}
	if (string("wppbwamcmmldcebygldybxdzzvloydltorcsysxbzyhg") == string("wppbwamcmmldcebygldybxdzzvloydltorcsysxbzyhg")) {
		int klgw;
		for (klgw = 89; klgw > 0; klgw--) {
			continue;
		}
	}
	if (true == true) {
		int mwvwiueq;
		for (mwvwiueq = 94; mwvwiueq > 0; mwvwiueq--) {
			continue;
		}
	}
	return 78383;
}

int lqaayuy::ioyqdzkkpfwmumwiuvouiozu(bool ngluxgy, int kbupew, int iwsqfxytpoesto, bool phqmpllsgyk, int qctdzbvzvdihuxw, bool svrwxrs, string hobmixaqvgoqyv, int qxttsqzzs) {
	int cbyke = 3872;
	bool ujnafjvzfgs = false;
	int jloszlljniacrmu = 2555;
	bool ogccvkjwynzlou = false;
	string ybwkad = "afqchgqutmcvcurvwyzxxqoykliobogvnnvcwrvjralxgl";
	bool fxkltpjdt = false;
	if (false == false) {
		int qs;
		for (qs = 46; qs > 0; qs--) {
			continue;
		}
	}
	if (false == false) {
		int xcpwp;
		for (xcpwp = 90; xcpwp > 0; xcpwp--) {
			continue;
		}
	}
	return 88487;
}

bool lqaayuy::udikbpimhwmbohlqqcapm(string yxvtifxdbudkbt, double oaxquweirblridi, bool islpgfjmyse, bool psqnpczdzc, string tbhqklpc, int vmqobign, int btvssflsvdkljtn, bool waggrdowxacaua, string leqnqos, int jeeervnjjkenn) {
	string rqtamhxato = "ebyrsulmggf";
	int vughyykeyi = 2297;
	int evfyz = 468;
	string jtmoyux = "rhkkakgbimknqpybhfxfvbqawwfabasnnekjdzzgswgl";
	string mtzab = "wcvyarzefy";
	double lofdhoezk = 59364;
	if (string("ebyrsulmggf") != string("ebyrsulmggf")) {
		int twxvytr;
		for (twxvytr = 95; twxvytr > 0; twxvytr--) {
			continue;
		}
	}
	if (string("wcvyarzefy") != string("wcvyarzefy")) {
		int yv;
		for (yv = 23; yv > 0; yv--) {
			continue;
		}
	}
	if (string("rhkkakgbimknqpybhfxfvbqawwfabasnnekjdzzgswgl") == string("rhkkakgbimknqpybhfxfvbqawwfabasnnekjdzzgswgl")) {
		int tqd;
		for (tqd = 32; tqd > 0; tqd--) {
			continue;
		}
	}
	return true;
}

double lqaayuy::nvepomypgxxailmr(int prfotbqcmvv) {
	double zpbnqmutu = 34982;
	if (34982 == 34982) {
		int bm;
		for (bm = 44; bm > 0; bm--) {
			continue;
		}
	}
	if (34982 != 34982) {
		int yvnxmf;
		for (yvnxmf = 47; yvnxmf > 0; yvnxmf--) {
			continue;
		}
	}
	return 57862;
}

string lqaayuy::upzdmlmxxyiqxo(double phogeiw, double ctbolbnaetmqneh, int eegvg, int iicedrvclbii, int mbjcjvk, bool fkpfehqbkxamnsr, bool txcklqeffkkj, int lkepgyknhhuhkhv, string kpwuiwoidltst) {
	string eagcwdudd = "kuvvabsgunthajmebkxoxhyyamfcaecrommvlfsndllp";
	bool ztmwyw = false;
	string qzlvpscgkkhxbzk = "ilcfzdtublpexqfcxiiffodjualinhcshqmtbplxtoqqpizupkwzbunchwocllcdpckrjextexlzplkyr";
	int mqkhajmrwhot = 2297;
	bool borehsyicxza = true;
	string eipnzkdi = "zosqmaxfokalvlzvjyxldjrtjzawkdkmwyndtngxkpyv";
	string hxcotjwjiza = "qiuajncwkicvumqeekadjbpgflldimrmpqyiajlxqzttleuwzntufkyivnyntdlywevfspviaetzszzkiqifgrqoexrfk";
	bool veysavojhskj = true;
	double lacyc = 1015;
	bool cjmyzyaimyr = false;
	return string("mpq");
}

int lqaayuy::gcqloqncrnuu(bool romtcmmemwkufc, int cvkeav, string cmvrz, int kwqktcccwc, bool bgkxqavmpevuisy, bool biwdvnhjnzni, string zbhixauuokwnc, string qbjngtrsuxjpvsz, double zeril, bool umurlyteq) {
	string viacjvdor = "uilysanlhvithoxqjcfexierezdzkdlfxrjhqwuukhkslgvkdrfinpt";
	if (string("uilysanlhvithoxqjcfexierezdzkdlfxrjhqwuukhkslgvkdrfinpt") == string("uilysanlhvithoxqjcfexierezdzkdlfxrjhqwuukhkslgvkdrfinpt")) {
		int vyw;
		for (vyw = 94; vyw > 0; vyw--) {
			continue;
		}
	}
	return 57573;
}

void lqaayuy::scvfhpknjfcgsy(int mnmhzhfvlddpe, double kqenucrd, int kdunc) {
	double xvslhlbkdo = 34426;
	bool ntmykumffm = false;
	int letaoa = 2782;
	bool oaembtkddaglltx = true;
	double xzdaah = 33971;
	if (false != false) {
		int pdrwyo;
		for (pdrwyo = 16; pdrwyo > 0; pdrwyo--) {
			continue;
		}
	}
	if (34426 == 34426) {
		int utjlgvbtxd;
		for (utjlgvbtxd = 10; utjlgvbtxd > 0; utjlgvbtxd--) {
			continue;
		}
	}
	if (33971 != 33971) {
		int kpzqwmk;
		for (kpzqwmk = 5; kpzqwmk > 0; kpzqwmk--) {
			continue;
		}
	}
	if (2782 == 2782) {
		int iqodisb;
		for (iqodisb = 70; iqodisb > 0; iqodisb--) {
			continue;
		}
	}

}

lqaayuy::lqaayuy() {
	this->rcqsltbbcefkdncieu(919, 41308, string("kciaxeqzidcbpmqyakenn"), 17624, 427);
	this->gaftqbimlgji(string("rblnjlrvbttyuvqrqjoyrluvppmrrkvgvuopxroqbfimxnqebottfykbojwwltavre"), 5364, 4595, true, 64922, 2657, string("bqqlfchaiwtwlursovwrpzdabunpfxotoxirinpfzwtfiqgrmwwxidmvrnirksqzeebwjongikgyxdcgdsuprtgnggx"), true, 13822, string("yilskifwzmylbfqwxxqxbswrvfpcmnth"));
	this->kodoofxqndhjtikzj(7579, string("olzvwsl"), 8407, 1262, string("plwhnrhxhvlfpe"), 3064, string("lbgfulgsypgqckjqqkcrolxkmyctmnyfhkcd"), string("eylewpwtkkutrqoxlcpfgwbxcytekpwgmgwvssok"), string("tjfdxvvfwn"));
	this->dviburqjzcchwnffmsczpjg(string("bbfxbjvwvaxhnudmwgkebdrthfxqxyonsyvrgobahucvnnnewiqlmnvumkjy"), string("cvdxndagpxieabblrsgljrxjsxvzfivppczhyhgub"));
	this->ioyqdzkkpfwmumwiuvouiozu(false, 920, 8, false, 211, true, string("biusvegynrsslvinlyqlo"), 740);
	this->udikbpimhwmbohlqqcapm(string("skovtgeigxaducaxkrxvcfvbobuhpmrdczmlmbrahceyhyvgsdwqnqkqsckcuybponeerncbxaxvhtwpctorzvrymlcezch"), 12633, false, false, string("bjzepvfhag"), 5955, 948, true, string("hj"), 6098);
	this->nvepomypgxxailmr(122);
	this->upzdmlmxxyiqxo(3004, 53286, 4187, 2098, 5460, true, true, 955, string("quwjvu"));
	this->gcqloqncrnuu(true, 1298, string("dazvtjlmjjkidujydbyqlzytebyacoorogfriwjjyhdrowcjgemqvifndruudavrtiarlsxpilwbdthxzhyzteawjou"), 336, true, true, string("ulaiidppkllpdjvdnbhsqitqpmlevyowpfyqzxarkvykhmvkhzfpilkvmfwsskvweoypjsaaqyaetqtgnudvpzhftdvhygtis"), string("sjgrtgowfcvp"), 93067, true);
	this->scvfhpknjfcgsy(3463, 5818, 3731);
	this->wmvxxxuuwpwnyyoxw(56567, 61330, 5106, 11171, true, true);
	this->qrwpzzvllxrbkgghdsekqu(19630, true, 45281, string("tzgcecspelluxcbhevlyiuhhadktpviaufwfhhouhvwtfebeqefajlknqzovviinhlyqaeuzuzy"), 5630, 14415, false);
	this->zpuwmaqpsggg(true, true, 25747, 20971, 7744, 15584, 13644, string("gfkokucvizshojhcdtkyalyallteuioljjfzvfmuekintwqbcncirxkse"), false, 4327);
	this->xkqygcppfpfrxnovciaez(true, string("uwviacpzaxbpmaevhgflphzllwkwhlmzqscowtiemsyihjouq"), true, true, 2225);
	this->cyutrqcnwkmxqvnlkckmkjwr(1132, true, 2433, string("ubvxislgazrsdxpsedbgbejmdhlohrqwtcnhzlgpqbyrjqknsezwzsxflihtyiumqjekgpnvkynbsnupajxjoxan"), 276, 68045, 1113);
	this->iszlfikreukcahgf(21510, 5466);
	this->cuhdpzhlibfzabmwolrogygzu(3123, string("xrnwiduwuwvhwjqdkhlsnmdzjlavagfgixpixvajecntkpbxmpimdvcghiqwtngrgjgmwnsqvhsdqo"), false, 51973);
	this->vgmjxxzrdcptqdynewmnrtb(string("niunqywvuxwpzthcfzrgtpb"));
	this->jsycmophrg(2936, string("avcswzipvmnxavmdgqupqren"), 15339, string("hkcsagqjzyicdurbyummesqkuholsbjgywtrluijyjgsksefyxszhhsgbvtifomfolx"), string("vokvnzpitcsrokyirdfygmsmcnbfzdiescsnxhjqkjsjqpecrqa"));
}
