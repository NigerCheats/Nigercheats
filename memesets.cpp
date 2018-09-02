#include "memesets.h"
#include "SDK.h"


void Offsetz::GetNetvars()
{
    NetVarManager->Initialize();
	offsetz.DT_BasePlayer.m_Local = NetVarManager->GetOffset("DT_BasePlayer", "m_Local");
	offsetz.DT_BasePlayer.m_aimPunchAngle = NetVarManager->GetOffset("DT_BasePlayer", "m_aimPunchAngle");
	offsetz.DT_BasePlayer.m_aimPunchAngleVel = NetVarManager->GetOffset("DT_BasePlayer", "m_aimPunchAngleVel");
	offsetz.DT_BasePlayer.m_viewPunchAngle = NetVarManager->GetOffset("DT_BasePlayer", "m_viewPunchAngle");
	offsetz.DT_BasePlayer.m_vecViewOffset = NetVarManager->GetOffset("DT_BasePlayer", "m_vecViewOffset[0]");
	offsetz.DT_BasePlayer.m_nTickBase = NetVarManager->GetOffset("DT_BasePlayer", "m_nTickBase");
	offsetz.DT_BasePlayer.m_vecVelocity = NetVarManager->GetOffset("DT_BasePlayer", "m_vecVelocity[0]");
	offsetz.DT_BasePlayer.m_iHealth = NetVarManager->GetOffset("DT_BasePlayer", "m_iHealth");
	offsetz.DT_BasePlayer.m_iMaxHealth = NetVarManager->GetOffset("DT_BasePlayer", "m_iMaxHealth");
	offsetz.DT_BasePlayer.m_lifeState = NetVarManager->GetOffset("DT_BasePlayer", "m_lifeState");
	offsetz.DT_BasePlayer.m_fFlags = NetVarManager->GetOffset("DT_BasePlayer", "m_fFlags");
	offsetz.DT_BasePlayer.m_iObserverMode = NetVarManager->GetOffset("DT_BasePlayer", "m_iObserverMode");
	offsetz.DT_BasePlayer.m_hObserverTarget = NetVarManager->GetOffset("DT_BasePlayer", "m_hObserverTarget");
	offsetz.DT_BasePlayer.m_hViewModel = NetVarManager->GetOffset("DT_BasePlayer", "m_hViewModel[0]");
	offsetz.DT_BasePlayer.m_szLastPlaceName = NetVarManager->GetOffset("DT_BasePlayer", "m_szLastPlaceName");
	offsetz.DT_BasePlayer.deadflag = NetVarManager->GetOffset("DT_BasePlayer", "deadflag");

	offsetz.DT_BaseEntity.m_flAnimTime = NetVarManager->GetOffset("DT_BaseEntity", "m_flAnimTime");
	offsetz.DT_BaseEntity.m_flSimulationTime = NetVarManager->GetOffset("DT_BaseEntity", "m_flSimulationTime");
	offsetz.DT_BaseEntity.m_vecOrigin = NetVarManager->GetOffset("DT_BaseEntity", "m_vecOrigin");
	offsetz.DT_BaseEntity.m_angRotation = NetVarManager->GetOffset("DT_BaseEntity", "m_angRotation");
	offsetz.DT_BaseEntity.m_nRenderMode = NetVarManager->GetOffset("DT_BaseEntity", "m_nRenderMode");
	offsetz.DT_BaseEntity.m_iTeamNum = NetVarManager->GetOffset("DT_BaseEntity", "m_iTeamNum");
	offsetz.DT_BaseEntity.m_MoveType = offsetz.DT_BaseEntity.m_nRenderMode + 1;
	offsetz.DT_BaseEntity.m_Collision = NetVarManager->GetOffset("DT_BaseEntity", "m_Collision");
	offsetz.DT_BaseEntity.m_hOwner = NetVarManager->GetOffset("DT_BaseEntity", "m_hOwner");
	offsetz.DT_BaseEntity.m_bSpotted = NetVarManager->GetOffset("DT_BaseEntity", "m_bSpotted");
	offsetz.DT_BaseEntity.m_vecMins = NetVarManager->GetOffset("DT_BaseEntity", "m_vecMins");
	offsetz.DT_BaseEntity.m_vecMaxs = NetVarManager->GetOffset("DT_BaseEntity", "m_vecMaxs");
	offsetz.DT_BaseEntity.m_nSolidType = NetVarManager->GetOffset("DT_BaseEntity", "m_nSolidType");
	offsetz.DT_BaseEntity.m_usSolidFlags = NetVarManager->GetOffset("DT_BaseEntity", "m_usSolidFlags");
	offsetz.DT_BaseEntity.m_nSurroundType = NetVarManager->GetOffset("DT_BaseEntity", "m_nSurroundType");


	offsetz.DT_BaseCombatCharacter.m_hActiveWeapon = NetVarManager->GetOffset("DT_BaseCombatCharacter", "m_hActiveWeapon");
	offsetz.DT_BaseCombatCharacter.m_hMyWeapons = NetVarManager->GetOffset("DT_BaseCombatCharacter", "m_hMyWeapons") / 2;
	offsetz.DT_BaseCombatCharacter.m_hMyWearables = NetVarManager->GetOffset("DT_BaseCombatCharacter", "m_hMyWearables");

	offsetz.DT_PlayerResource.m_iPing = NetVarManager->GetOffset("DT_PlayerResource", "m_iPing");
	offsetz.DT_PlayerResource.m_iKills = NetVarManager->GetOffset("DT_PlayerResource", "m_iKills");
	offsetz.DT_PlayerResource.m_iAssists = NetVarManager->GetOffset("DT_PlayerResource", "m_iAssists");
	offsetz.DT_PlayerResource.m_iDeaths = NetVarManager->GetOffset("DT_PlayerResource", "m_iDeaths");
	offsetz.DT_PlayerResource.m_bConnected = NetVarManager->GetOffset("DT_PlayerResource", "m_bConnected");
	offsetz.DT_PlayerResource.m_iTeam = NetVarManager->GetOffset("DT_PlayerResource", "m_iTeam");
	offsetz.DT_PlayerResource.m_iPendingTeam = NetVarManager->GetOffset("DT_PlayerResource", "m_iPendingTeam");
	offsetz.DT_PlayerResource.m_bAlive = NetVarManager->GetOffset("DT_PlayerResource", "m_bAlive");
	offsetz.DT_PlayerResource.m_iHealth = NetVarManager->GetOffset("DT_PlayerResource", "m_iHealth");

	offsetz.DT_CSPlayerResource.m_iPlayerC4 = NetVarManager->GetOffset("DT_CSPlayerResource", "m_iPlayerC4");
	offsetz.DT_CSPlayerResource.m_iPlayerVIP = NetVarManager->GetOffset("DT_CSPlayerResource", "m_iPlayerVIP");
	offsetz.DT_CSPlayerResource.m_bHostageAlive = NetVarManager->GetOffset("DT_CSPlayerResource", "m_bHostageAlive");
	offsetz.DT_CSPlayerResource.m_isHostageFollowingSomeone = NetVarManager->GetOffset("DT_CSPlayerResource", "m_isHostageFollowingSomeone");
	offsetz.DT_CSPlayerResource.m_iHostageEntityIDs = NetVarManager->GetOffset("DT_CSPlayerResource", "m_iHostageEntityIDs");
	offsetz.DT_CSPlayerResource.m_bombsiteCenterB = NetVarManager->GetOffset("DT_CSPlayerResource", "m_bombsiteCenterB");
	offsetz.DT_CSPlayerResource.m_hostageRescueX = NetVarManager->GetOffset("DT_CSPlayerResource", "m_hostageRescueX");
	offsetz.DT_CSPlayerResource.m_hostageRescueY = NetVarManager->GetOffset("DT_CSPlayerResource", "m_hostageRescueY");
	offsetz.DT_CSPlayerResource.m_hostageRescueZ = NetVarManager->GetOffset("DT_CSPlayerResource", "m_hostageRescueZ");
	offsetz.DT_CSPlayerResource.m_iMVPs = NetVarManager->GetOffset("DT_CSPlayerResource", "m_iMVPs");
	offsetz.DT_CSPlayerResource.m_iArmor = NetVarManager->GetOffset("DT_CSPlayerResource", "m_iArmor");
	offsetz.DT_CSPlayerResource.m_bHasHelmet = NetVarManager->GetOffset("DT_CSPlayerResource", "m_bHasHelmet");
	offsetz.DT_CSPlayerResource.m_bHasDefuser = NetVarManager->GetOffset("DT_CSPlayerResource", "m_bHasDefuser");
	offsetz.DT_CSPlayerResource.m_iScore = NetVarManager->GetOffset("DT_CSPlayerResource", "m_iScore");
	offsetz.DT_CSPlayerResource.m_iCompetitiveRanking = NetVarManager->GetOffset("DT_CSPlayerResource", "m_iCompetitiveRanking");
	offsetz.DT_CSPlayerResource.m_iCompetitiveWins = NetVarManager->GetOffset("DT_CSPlayerResource", "m_iCompetitiveWins");
	offsetz.DT_CSPlayerResource.m_iCompTeammateColor = NetVarManager->GetOffset("DT_CSPlayerResource", "m_iCompTeammateColor");
	offsetz.DT_CSPlayerResource.m_bControllingBot = NetVarManager->GetOffset("DT_CSPlayerResource", "m_bControllingBot");
	offsetz.DT_CSPlayerResource.m_iControlledPlayer = NetVarManager->GetOffset("DT_CSPlayerResource", "m_iControlledPlayer");
	offsetz.DT_CSPlayerResource.m_iControlledByPlayer = NetVarManager->GetOffset("DT_CSPlayerResource", "m_iControlledByPlayer");
	offsetz.DT_CSPlayerResource.m_iBotDifficulty = NetVarManager->GetOffset("DT_CSPlayerResource", "m_iBotDifficulty");
	offsetz.DT_CSPlayerResource.m_szClan = NetVarManager->GetOffset("DT_CSPlayerResource", "m_szClan");
	offsetz.DT_CSPlayerResource.m_iTotalCashSpent = NetVarManager->GetOffset("DT_CSPlayerResource", "m_iTotalCashSpent");
	offsetz.DT_CSPlayerResource.m_iCashSpentThisRound = NetVarManager->GetOffset("DT_CSPlayerResource", "m_iCashSpentThisRound");
	offsetz.DT_CSPlayerResource.m_nEndMatchNextMapVotes = NetVarManager->GetOffset("DT_CSPlayerResource", "m_nEndMatchNextMapVotes");
	offsetz.DT_CSPlayerResource.m_bEndMatchNextMapAllVoted = NetVarManager->GetOffset("DT_CSPlayerResource", "m_bEndMatchNextMapAllVoted");
	offsetz.DT_CSPlayerResource.m_nActiveCoinRank = NetVarManager->GetOffset("DT_CSPlayerResource", "m_nActiveCoinRank");
	offsetz.DT_CSPlayerResource.m_nMusicID = NetVarManager->GetOffset("DT_CSPlayerResource", "m_nMusicID");
	offsetz.DT_CSPlayerResource.m_nPersonaDataPublicLevel = NetVarManager->GetOffset("DT_CSPlayerResource", "m_nPersonaDataPublicLevel");
	offsetz.DT_CSPlayerResource.m_nPersonaDataPublicCommendsLeader = NetVarManager->GetOffset("DT_CSPlayerResource", "m_nPersonaDataPublicCommendsLeader");
	offsetz.DT_CSPlayerResource.m_nPersonaDataPublicCommendsTeacher = NetVarManager->GetOffset("DT_CSPlayerResource", "m_nPersonaDataPublicCommendsTeacher");
	offsetz.DT_CSPlayerResource.m_nPersonaDataPublicCommendsFriendly = NetVarManager->GetOffset("DT_CSPlayerResource", "m_nPersonaDataPublicCommendsFriendly");

	offsetz.DT_PlantedC4.m_bBombTicking = NetVarManager->GetOffset("DT_PlantedC4", "m_bBombTicking");
	offsetz.DT_PlantedC4.m_flC4Blow = NetVarManager->GetOffset("DT_PlantedC4", "m_flC4Blow");
	offsetz.DT_PlantedC4.m_bBombDefused = NetVarManager->GetOffset("DT_PlantedC4", "m_bBombDefused");
	offsetz.DT_PlantedC4.m_hBombDefuser = NetVarManager->GetOffset("DT_PlantedC4", "m_hBombDefuser");
	offsetz.DT_PlantedC4.m_flDefuseCountDown = NetVarManager->GetOffset("DT_PlantedC4", "m_flDefuseCountDown");

	offsetz.DT_CSPlayer.m_iShotsFired = NetVarManager->GetOffset("DT_CSPlayer", "m_iShotsFired");
	offsetz.DT_CSPlayer.m_angEyeAngles[0] = NetVarManager->GetOffset("DT_CSPlayer", "m_angEyeAngles[0]");
	offsetz.DT_CSPlayer.m_angEyeAngles[1] = NetVarManager->GetOffset("DT_CSPlayer", "m_angEyeAngles[1]");
	offsetz.DT_CSPlayer.m_iAccount = NetVarManager->GetOffset("DT_CSPlayer", "m_iAccount");
	offsetz.DT_CSPlayer.m_totalHitsOnServer = NetVarManager->GetOffset("DT_CSPlayer", "m_totalHitsOnServer");
	offsetz.DT_CSPlayer.m_ArmorValue = NetVarManager->GetOffset("DT_CSPlayer", "m_ArmorValue");
	offsetz.DT_CSPlayer.m_bIsDefusing = NetVarManager->GetOffset("DT_CSPlayer", "m_bIsDefusing");
	offsetz.DT_CSPlayer.m_bIsGrabbingHostage = NetVarManager->GetOffset("DT_CSPlayer", "m_bIsGrabbingHostage");
	offsetz.DT_CSPlayer.m_bIsScoped = NetVarManager->GetOffset("DT_CSPlayer", "m_bIsScoped");
	offsetz.DT_CSPlayer.m_bGunGameImmunity = NetVarManager->GetOffset("DT_CSPlayer", "m_bGunGameImmunity");
	offsetz.DT_CSPlayer.m_bIsRescuing = NetVarManager->GetOffset("DT_CSPlayer", "m_bIsRescuing");
	offsetz.DT_CSPlayer.m_bHasHelmet = NetVarManager->GetOffset("DT_CSPlayer", "m_bHasHelmet");
	offsetz.DT_CSPlayer.m_bHasDefuser = NetVarManager->GetOffset("DT_CSPlayer", "m_bHasDefuser");
	offsetz.DT_CSPlayer.m_flFlashDuration = NetVarManager->GetOffset("DT_CSPlayer", "m_flFlashDuration");
	offsetz.DT_CSPlayer.m_flFlashMaxAlpha = NetVarManager->GetOffset("DT_CSPlayer", "m_flFlashMaxAlpha");
	offsetz.DT_CSPlayer.m_flLowerBodyYawTarget = NetVarManager->GetOffset("DT_CSPlayer", "m_flLowerBodyYawTarget");
    offsetz.DT_CSPlayer.m_bHasHeavyArmor = NetVarManager->GetOffset("DT_CSPlayer", "m_bHasHeavyArmor");
	offsetz.DT_CSPlayer.m_iGunGameProgressiveWeaponIndex = NetVarManager->GetOffset("DT_CSPlayer", "m_iGunGameProgressiveWeaponIndex");

	offsetz.DT_BaseAttributableItem.m_iItemDefinitionIndex = NetVarManager->GetOffset("DT_BaseAttributableItem", "m_iItemDefinitionIndex");
	offsetz.DT_BaseAttributableItem.m_iAccountID = NetVarManager->GetOffset("DT_BaseAttributableItem", "m_iAccountID");
	offsetz.DT_BaseAttributableItem.m_iEntityQuality = NetVarManager->GetOffset("DT_BaseAttributableItem", "m_iEntityQuality");
	offsetz.DT_BaseAttributableItem.m_szCustomName = NetVarManager->GetOffset("DT_BaseAttributableItem", "m_szCustomName");
	offsetz.DT_BaseAttributableItem.m_nFallbackPaintKit = NetVarManager->GetOffset("DT_BaseAttributableItem", "m_nFallbackPaintKit");
	offsetz.DT_BaseAttributableItem.m_nFallbackSeed = NetVarManager->GetOffset("DT_BaseAttributableItem", "m_nFallbackSeed");
	offsetz.DT_BaseAttributableItem.m_flFallbackWear = NetVarManager->GetOffset("DT_BaseAttributableItem", "m_flFallbackWear");
	offsetz.DT_BaseAttributableItem.m_nFallbackStatTrak = NetVarManager->GetOffset("DT_BaseAttributableItem", "m_nFallbackStatTrak");
	offsetz.DT_BaseAttributableItem.m_OriginalOwnerXuidLow = NetVarManager->GetOffset("DT_BaseAttributableItem", "m_OriginalOwnerXuidLow");
	offsetz.DT_BaseAttributableItem.m_OriginalOwnerXuidHigh = NetVarManager->GetOffset("DT_BaseAttributableItem", "m_OriginalOwnerXuidHigh");
	offsetz.DT_BaseAttributableItem.m_iItemIDHigh = NetVarManager->GetOffset("DT_BaseAttributableItem", "m_iItemIDHigh");

	offsetz.DT_BaseViewModel.m_nModelIndex = NetVarManager->GetOffset("DT_BaseViewModel", "m_nModelIndex");
	offsetz.DT_BaseViewModel.m_hWeapon = NetVarManager->GetOffset("DT_BaseViewModel", "m_hWeapon");
	offsetz.DT_BaseViewModel.m_hOwner = NetVarManager->GetOffset("DT_BaseViewModel", "m_hOwner");

	offsetz.DT_WeaponCSBase.m_fAccuracyPenalty = NetVarManager->GetOffset("DT_WeaponCSBase", "m_fAccuracyPenalty");
    offsetz.DT_WeaponCSBase.m_flPostponeFireReadyTime = NetVarManager->GetOffset("DT_WeaponCSBase", "m_flPostponeFireReadyTime");

	offsetz.DT_WeaponC4.m_bStartedArming = NetVarManager->GetOffset("DT_WeaponC4", "m_bStartedArming");

	offsetz.DT_BaseCombatWeapon.m_flNextPrimaryAttack = NetVarManager->GetOffset("DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
	offsetz.DT_BaseCombatWeapon.m_iViewModelIndex = NetVarManager->GetOffset("DT_BaseCombatWeapon", "m_iViewModelIndex");
	offsetz.DT_BaseCombatWeapon.m_iWorldModelIndex = NetVarManager->GetOffset("DT_BaseCombatWeapon", "m_iWorldModelIndex");
	offsetz.DT_BaseCombatWeapon.m_hOwner = NetVarManager->GetOffset("DT_BaseCombatWeapon", "m_hOwner");
	offsetz.DT_BaseCombatWeapon.m_iClip1 = NetVarManager->GetOffset("DT_BaseCombatWeapon", "m_iClip1");
	offsetz.DT_BaseCombatWeapon.m_iReserve = NetVarManager->GetOffset("DT_BaseCombatWeapon", "m_iPrimaryReserveAmmoCount");
	offsetz.DT_BaseCombatWeapon.m_bInReload = offsetz.DT_BaseCombatWeapon.m_flNextPrimaryAttack + 113;
    offsetz.DT_BaseCombatWeapon.m_hWeaponWorldModel = NetVarManager->GetOffset("DT_BaseCombatWeapon", "m_hWeaponWorldModel");


	offsetz.DT_BaseCSGrenade.m_bRedraw = NetVarManager->GetOffset("DT_BaseCSGrenade", "m_bRedraw");
	offsetz.DT_BaseCSGrenade.m_bIsHeldByPlayer = NetVarManager->GetOffset("DT_BaseCSGrenade", "m_bIsHeldByPlayer");
	offsetz.DT_BaseCSGrenade.m_bPinPulled = NetVarManager->GetOffset("DT_BaseCSGrenade", "m_bPinPulled");
	offsetz.DT_BaseCSGrenade.m_fThrowTime = NetVarManager->GetOffset("DT_BaseCSGrenade", "m_fThrowTime");
	offsetz.DT_BaseCSGrenade.m_bLoopingSoundPlaying = NetVarManager->GetOffset("DT_BaseCSGrenade", "m_bLoopingSoundPlaying");
	offsetz.DT_BaseCSGrenade.m_flThrowStrength = NetVarManager->GetOffset("DT_BaseCSGrenade", "m_flThrowStrength");

	offsetz.DT_DynamicProp.m_bShouldGlow = NetVarManager->GetOffset("DT_DynamicProp", "m_bShouldGlow");

	offsetz.DT_CSGameRulesProxy.m_bBombPlanted = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_bBombPlanted");
	offsetz.DT_CSGameRulesProxy.m_bIsValveDS = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_bIsValveDS");

	offsetz.DT_CSGameRulesProxy.m_bFreezePeriod = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_bFreezePeriod");
	offsetz.DT_CSGameRulesProxy.m_bMatchWaitingForResume = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_bMatchWaitingForResume");
	offsetz.DT_CSGameRulesProxy.m_bWarmupPeriod = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_bWarmupPeriod");
	offsetz.DT_CSGameRulesProxy.m_fWarmupPeriodEnd = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_fWarmupPeriodEnd");
	offsetz.DT_CSGameRulesProxy.m_fWarmupPeriodStart = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_fWarmupPeriodStart");
	offsetz.DT_CSGameRulesProxy.m_bTerroristTimeOutActive = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_bTerroristTimeOutActive");
	offsetz.DT_CSGameRulesProxy.m_bCTTimeOutActive = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_bCTTimeOutActive");
	offsetz.DT_CSGameRulesProxy.m_flTerroristTimeOutRemaining = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_flTerroristTimeOutRemaining");
	offsetz.DT_CSGameRulesProxy.m_flCTTimeOutRemaining = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_flCTTimeOutRemaining");
	offsetz.DT_CSGameRulesProxy.m_nTerroristTimeOuts = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_nTerroristTimeOuts");
	offsetz.DT_CSGameRulesProxy.m_nCTTimeOuts = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_nCTTimeOuts");
	offsetz.DT_CSGameRulesProxy.m_iRoundTime = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_iRoundTime");
	offsetz.DT_CSGameRulesProxy.m_gamePhase = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_gamePhase");
	offsetz.DT_CSGameRulesProxy.m_totalRoundsPlayed = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_totalRoundsPlayed");
	offsetz.DT_CSGameRulesProxy.m_nOvertimePlaying = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_nOvertimePlaying");
	offsetz.DT_CSGameRulesProxy.m_timeUntilNextPhaseStarts = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_timeUntilNextPhaseStarts");
	offsetz.DT_CSGameRulesProxy.m_flCMMItemDropRevealStartTime = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_flCMMItemDropRevealStartTime");
	offsetz.DT_CSGameRulesProxy.m_flCMMItemDropRevealEndTime = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_flCMMItemDropRevealEndTime");
	offsetz.DT_CSGameRulesProxy.m_fRoundStartTime = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_fRoundStartTime");
	offsetz.DT_CSGameRulesProxy.m_bGameRestart = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_bGameRestart");
	offsetz.DT_CSGameRulesProxy.m_flRestartRoundTime = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_flRestartRoundTime");
	offsetz.DT_CSGameRulesProxy.m_flGameStartTime = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_flGameStartTime");
	offsetz.DT_CSGameRulesProxy.m_iHostagesRemaining = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_iHostagesRemaining");
	offsetz.DT_CSGameRulesProxy.m_bAnyHostageReached = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_bAnyHostageReached");
	offsetz.DT_CSGameRulesProxy.m_bMapHasBombTarget = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_bMapHasBombTarget");
	offsetz.DT_CSGameRulesProxy.m_bMapHasRescueZone = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_bMapHasRescueZone");
	offsetz.DT_CSGameRulesProxy.m_bMapHasBuyZone = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_bMapHasBuyZone");
	offsetz.DT_CSGameRulesProxy.m_bIsQueuedMatchmaking = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_bIsQueuedMatchmaking");
	offsetz.DT_CSGameRulesProxy.m_bIsValveDS = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_bIsValveDS");
	offsetz.DT_CSGameRulesProxy.m_bIsQuestEligible = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_bIsQuestEligible");
	offsetz.DT_CSGameRulesProxy.m_bLogoMap = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_bLogoMap");
	offsetz.DT_CSGameRulesProxy.m_iNumGunGameProgressiveWeaponsCT = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_iNumGunGameProgressiveWeaponsCT");
	offsetz.DT_CSGameRulesProxy.m_iNumGunGameProgressiveWeaponsT = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_iNumGunGameProgressiveWeaponsT");
	offsetz.DT_CSGameRulesProxy.m_iSpectatorSlotCount = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_iSpectatorSlotCount");
	offsetz.DT_CSGameRulesProxy.m_bBombDropped = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_bBombDropped");
	offsetz.DT_CSGameRulesProxy.m_bBombPlanted = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_bBombPlanted");
	offsetz.DT_CSGameRulesProxy.m_iRoundWinStatus = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_iRoundWinStatus");
	offsetz.DT_CSGameRulesProxy.m_eRoundWinReason = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_eRoundWinReason");
	offsetz.DT_CSGameRulesProxy.m_flDMBonusStartTime = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_flDMBonusStartTime");
	offsetz.DT_CSGameRulesProxy.m_flDMBonusTimeLength = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_flDMBonusTimeLength");
	offsetz.DT_CSGameRulesProxy.m_unDMBonusWeaponLoadoutSlot = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_unDMBonusWeaponLoadoutSlot");
	offsetz.DT_CSGameRulesProxy.m_bDMBonusActive = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_bDMBonusActive");
	offsetz.DT_CSGameRulesProxy.m_bTCantBuy = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_bTCantBuy");
	offsetz.DT_CSGameRulesProxy.m_bCTCantBuy = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_bCTCantBuy");
	offsetz.DT_CSGameRulesProxy.m_flGuardianBuyUntilTime = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_flGuardianBuyUntilTime");
	offsetz.DT_CSGameRulesProxy.m_iMatchStats_RoundResults = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_iMatchStats_RoundResults");
	offsetz.DT_CSGameRulesProxy.m_iMatchStats_PlayersAlive_T = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_iMatchStats_PlayersAlive_T");
	offsetz.DT_CSGameRulesProxy.m_iMatchStats_PlayersAlive_CT = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_iMatchStats_PlayersAlive_CT");
	offsetz.DT_CSGameRulesProxy.m_GGProgressiveWeaponOrderC = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_GGProgressiveWeaponOrderC");
	offsetz.DT_CSGameRulesProxy.m_GGProgressiveWeaponOrderT = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_GGProgressiveWeaponOrderT");
	offsetz.DT_CSGameRulesProxy.m_GGProgressiveWeaponKillUpgradeOrderCT = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_GGProgressiveWeaponKillUpgradeOrderCT");
	offsetz.DT_CSGameRulesProxy.m_GGProgressiveWeaponKillUpgradeOrderT = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_GGProgressiveWeaponKillUpgradeOrderT");
	offsetz.DT_CSGameRulesProxy.m_MatchDevice = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_MatchDevice");
	offsetz.DT_CSGameRulesProxy.m_bHasMatchStarted = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_bHasMatchStarted");
	offsetz.DT_CSGameRulesProxy.m_TeamRespawnWaveTimes = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_TeamRespawnWaveTimes");
	offsetz.DT_CSGameRulesProxy.m_flNextRespawnWave = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_flNextRespawnWave");
	offsetz.DT_CSGameRulesProxy.m_nNextMapInMapgroup = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_nNextMapInMapgroup");
	offsetz.DT_CSGameRulesProxy.m_nEndMatchMapGroupVoteOptions = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_nEndMatchMapGroupVoteOptions");
	offsetz.DT_CSGameRulesProxy.m_bIsDroppingItems = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_bIsDroppingItems");
	offsetz.DT_CSGameRulesProxy.m_iActiveAssassinationTargetMissionID = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_iActiveAssassinationTargetMissionID");
	offsetz.DT_CSGameRulesProxy.m_fMatchStartTime = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_fMatchStartTime");
	offsetz.DT_CSGameRulesProxy.m_szTournamentEventName = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_szTournamentEventName");
	offsetz.DT_CSGameRulesProxy.m_szTournamentEventStage = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_szTournamentEventStage");
	offsetz.DT_CSGameRulesProxy.m_szTournamentPredictionsTxt = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_szTournamentPredictionsTxt");
	offsetz.DT_CSGameRulesProxy.m_nTournamentPredictionsPct = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_nTournamentPredictionsPct");
	offsetz.DT_CSGameRulesProxy.m_szMatchStatTxt = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_szMatchStatTxt");
	offsetz.DT_CSGameRulesProxy.m_nGuardianModeWaveNumber = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_nGuardianModeWaveNumber");
	offsetz.DT_CSGameRulesProxy.m_nGuardianModeSpecialKillsRemaining = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_nGuardianModeSpecialKillsRemaining");
	offsetz.DT_CSGameRulesProxy.m_nGuardianModeSpecialWeaponNeeded = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_nGuardianModeSpecialWeaponNeeded");
	offsetz.DT_CSGameRulesProxy.m_nHalloweenMaskListSeed = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_nHalloweenMaskListSeed");
	offsetz.DT_CSGameRulesProxy.m_numGlobalGiftsGiven = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_numGlobalGiftsGiven");
	offsetz.DT_CSGameRulesProxy.m_numGlobalGifters = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_numGlobalGifters");
	offsetz.DT_CSGameRulesProxy.m_numGlobalGiftsPeriodSeconds = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_numGlobalGiftsPeriodSeconds");
	offsetz.DT_CSGameRulesProxy.m_arrFeaturedGiftersAccounts = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_arrFeaturedGiftersAccounts");
	offsetz.DT_CSGameRulesProxy.m_arrFeaturedGiftersGifts = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_arrFeaturedGiftersGifts");
	offsetz.DT_CSGameRulesProxy.m_arrTournamentActiveCasterAccounts = NetVarManager->GetOffset("DT_CSGameRulesProxy", "m_arrTournamentActiveCasterAccounts");

    offsetz.DT_BaseAnimating.m_nHitboxSet = NetVarManager->GetOffset("DT_BaseAnimating", "m_nHitboxSet");

}

Offsetz* g_Netvars = new(Offsetz);
COffsetz offsetz;


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class cbfwbtz {
public:
	double mabwcfse;
	string kqgskipp;
	int ajuncxnv;
	double ghemyc;
	cbfwbtz();
	double myevlbcxpxu(double sujxorclwxcbhj, int cawqfvcamvs, string tlhgohdurxuoi);

protected:
	string ymiooywrvuw;
	double kslodx;

	int zlgboeenbdievlrobmk(double hmqyzmltyo, string ywvpax, string ssiqaoy, double htbbgmieelb, bool koqddxsrqa);
	void guxhrvwdsjfse(int hocch, int pzjlo, bool llrakibcm, bool brknxuzgg);
	string uwyncrbcqxrcotmf(int kiofnkqvcuteeyy, double qqfvmxj);
	int fwqhnlhoazdrkglbv(double oxnqlx, int zmwmcbzsgiws, int ayswejepfc, bool caszh, double utebj, int nwjaj, string epcxgsn, double edtvuyyvxj);
	double rjskxptgkbwapfnywm(bool camqgnpr, string dtxoneepg, string lmclwl, string phbqteiwmsbuz, int dtrfgnql, bool kwcgp, int yerzyzprlt, int zzexmvcbgpg, int vffcdkusfzt);

private:
	string zooezaweko;
	double zgusqqj;
	double ceduomqtywn;
	int feligl;
	bool xgdsnkt;

	double bzmsohqhgzvy();
	bool fhtailjbrivsfsgao(string labmnftg, double lnzrriebcw, bool tjxmftj, string pwjwmmnsalf, int edjkgju, double szutfcrogvcrkqp, bool zrbyrgs);

};


double cbfwbtz::bzmsohqhgzvy() {
	int ulbckxesatc = 3886;
	string ylqfcf = "wyqqdubyffyqzlgiwtbdvfidgraxgwfwcoqncghpxgqwuhyuiinuqskddnbmedqzsiwrsbvlhqzmqr";
	double pwojnvwvel = 9647;
	double eezcepfcav = 18141;
	bool rgylgcgfiktunb = true;
	string neloymuwmykrmx = "bnjmqvyshfnxecmgjwgqlehbhaab";
	double hscnxbwatvlv = 40406;
	double duddttepkxjxibu = 66188;
	if (string("wyqqdubyffyqzlgiwtbdvfidgraxgwfwcoqncghpxgqwuhyuiinuqskddnbmedqzsiwrsbvlhqzmqr") == string("wyqqdubyffyqzlgiwtbdvfidgraxgwfwcoqncghpxgqwuhyuiinuqskddnbmedqzsiwrsbvlhqzmqr")) {
		int gpbytkgnb;
		for (gpbytkgnb = 31; gpbytkgnb > 0; gpbytkgnb--) {
			continue;
		}
	}
	if (66188 == 66188) {
		int co;
		for (co = 23; co > 0; co--) {
			continue;
		}
	}
	return 31105;
}

bool cbfwbtz::fhtailjbrivsfsgao(string labmnftg, double lnzrriebcw, bool tjxmftj, string pwjwmmnsalf, int edjkgju, double szutfcrogvcrkqp, bool zrbyrgs) {
	int zjvwxlzmjuxaw = 5787;
	double uhpltug = 24942;
	bool vyguhmvhzzvxqe = true;
	if (24942 == 24942) {
		int qgzprmuh;
		for (qgzprmuh = 16; qgzprmuh > 0; qgzprmuh--) {
			continue;
		}
	}
	return false;
}

int cbfwbtz::zlgboeenbdievlrobmk(double hmqyzmltyo, string ywvpax, string ssiqaoy, double htbbgmieelb, bool koqddxsrqa) {
	bool aocqhbdbk = true;
	string nnxgul = "hehygwsfrogkqn";
	bool xzmoxlttxzj = false;
	int yppwrjfnwytk = 1543;
	double jqeqyy = 29925;
	double adshiih = 16191;
	double harnnbpajxeq = 32900;
	bool yuvzlyu = true;
	bool ojemxzkfjkdgdv = true;
	double lcwrtpzmrfdrfgk = 2452;
	if (true != true) {
		int ezx;
		for (ezx = 89; ezx > 0; ezx--) {
			continue;
		}
	}
	return 58511;
}

void cbfwbtz::guxhrvwdsjfse(int hocch, int pzjlo, bool llrakibcm, bool brknxuzgg) {

}

string cbfwbtz::uwyncrbcqxrcotmf(int kiofnkqvcuteeyy, double qqfvmxj) {
	int nefomsednaxkxp = 2837;
	int rjwbwv = 5497;
	double zoomsnwj = 4871;
	bool pqysmrixht = true;
	string nvazd = "hcagezjlbqthtaebvhbdvdravqt";
	bool sazdnqvyz = false;
	if (false == false) {
		int nk;
		for (nk = 38; nk > 0; nk--) {
			continue;
		}
	}
	if (4871 == 4871) {
		int pafqdpohmj;
		for (pafqdpohmj = 85; pafqdpohmj > 0; pafqdpohmj--) {
			continue;
		}
	}
	return string("vnku");
}

int cbfwbtz::fwqhnlhoazdrkglbv(double oxnqlx, int zmwmcbzsgiws, int ayswejepfc, bool caszh, double utebj, int nwjaj, string epcxgsn, double edtvuyyvxj) {
	return 80051;
}

double cbfwbtz::rjskxptgkbwapfnywm(bool camqgnpr, string dtxoneepg, string lmclwl, string phbqteiwmsbuz, int dtrfgnql, bool kwcgp, int yerzyzprlt, int zzexmvcbgpg, int vffcdkusfzt) {
	int tyqenqpdxervgfw = 565;
	bool ijmunvbsjmnj = true;
	int uoizztbwopl = 2425;
	double eqvhudzcjgyc = 33200;
	if (true != true) {
		int wglupb;
		for (wglupb = 99; wglupb > 0; wglupb--) {
			continue;
		}
	}
	if (33200 != 33200) {
		int tnykt;
		for (tnykt = 68; tnykt > 0; tnykt--) {
			continue;
		}
	}
	if (true != true) {
		int vbeuj;
		for (vbeuj = 68; vbeuj > 0; vbeuj--) {
			continue;
		}
	}
	if (true == true) {
		int tdf;
		for (tdf = 88; tdf > 0; tdf--) {
			continue;
		}
	}
	return 62763;
}

double cbfwbtz::myevlbcxpxu(double sujxorclwxcbhj, int cawqfvcamvs, string tlhgohdurxuoi) {
	bool ahtnnjcndjwq = false;
	double pjlizuyjntbpt = 53824;
	int bzydrowl = 2123;
	double nybxzwazydzwnr = 44108;
	double xojczvx = 36702;
	return 9755;
}

cbfwbtz::cbfwbtz() {
	this->myevlbcxpxu(49995, 8871, string("bpqgvoklngvcbgvtgqgafvmmoggmylxgalchervgrlgkjlsoxewnnkgnibqfxqpapf"));
	this->zlgboeenbdievlrobmk(30813, string("iuyftbiktygofbezzdovjlnvzglomgqzpwaqq"), string("oqgtdjdmaaznualzvconpzfnpgptddbv"), 1772, false);
	this->guxhrvwdsjfse(1720, 6507, false, false);
	this->uwyncrbcqxrcotmf(5633, 2208);
	this->fwqhnlhoazdrkglbv(24329, 2679, 356, true, 42365, 1069, string("vptwxmajsgcjcunnnvinsdggqnfyweuogyysckpsmqtiwndrrxslvxcgzptvcbeagvkxodxejpeuxmcxqighhlyrkwnna"), 19708);
	this->rjskxptgkbwapfnywm(false, string("yeycvptyaiyzttoninnlnftzvmwkofcsxvjbhddvpobybzfyxyruvoxkhg"), string("sljsmfokuibmg"), string("apqwaxnwceptpndnijsqfpcianitfcetxvwsdjwfojvpschmpkrkrcshddqvnzstryqrxtqxndrhpzedkewrbgjkgq"), 2391, false, 4461, 1677, 1477);
	this->bzmsohqhgzvy();
	this->fhtailjbrivsfsgao(string("rpcnkzhvgxxtxsi"), 62430, true, string("wivrmzrcgbcylsrogwkgccqnmhlwbdgycjwbrsgmtkgzbpecqkqlxnykcbzdaefxetw"), 1504, 15965, true);
}
