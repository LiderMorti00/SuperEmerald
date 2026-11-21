@ Super Emerald: Pokemon World Tournament. A copy of the Battle Dome scripts (the PWT runs on the
@ Dome engine) with its own labels, warps and texts; nothing here is shared with Hoenn's Dome.
@ PWT-only parts: data/scripts/se_pwt.inc and src/se_pwt.c.

@ On this map the player will automatically walk into the room, but the camera is supposed to remain still.
@ To do this GF sets the player (LOCALID_PLAYER) invisible and creates a fake player object (LOCALID_DOME_PLAYER).
@ The graphics of this fake player object are represented with VAR_OBJ_GFX_ID_1.
@ The graphics of the opponent are represented with VAR_OBJ_GFX_ID_0, which will ultimately be set by dome_setopponentgfx.

.set NO_DRAW,       0
.set DRAW_TRAINER,  1
.set DRAW_TUCKER,   2

PokemonWorldTournamentRoom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PokemonWorldTournamentRoom_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PokemonWorldTournamentRoom_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PokemonWorldTournamentRoom_OnWarp
	map_script MAP_SCRIPT_ON_RESUME, PokemonWorldTournamentRoom_OnResume
	.byte 0

PokemonWorldTournamentRoom_OnTransition:
	setflag FLAG_TEMP_HIDE_FOLLOWER
	dome_setopponentgfx
	frontier_get FRONTIER_DATA_BATTLE_NUM
	copyvar VAR_TEMP_F, VAR_RESULT
	call_if_eq VAR_RESULT, DOME_ROUND1, PokemonWorldTournamentRoom_EventScript_SetWalkingAudienceMemberPos
	call PokemonWorldTournamentRoom_EventScript_SetPlayerGfx
	end

PokemonWorldTournamentRoom_EventScript_SetPlayerGfx::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, PokemonWorldTournamentRoom_EventScript_SetPlayerGfxMale
	goto_if_eq VAR_RESULT, FEMALE, PokemonWorldTournamentRoom_EventScript_SetPlayerGfxFemale
	return

PokemonWorldTournamentRoom_EventScript_SetPlayerGfxMale::
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_RIVAL_BRENDAN_NORMAL
	return

PokemonWorldTournamentRoom_EventScript_SetPlayerGfxFemale::
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_RIVAL_MAY_NORMAL
	return

PokemonWorldTournamentRoom_OnFrame:
	map_script_2 VAR_TEMP_0, 0, PokemonWorldTournamentRoom_EventScript_EnterRoom
	.2byte 0

PokemonWorldTournamentRoom_EventScript_EnterRoom::
	lockall
	call PokemonWorldTournamentRoom_EventScript_GetRoundNum
	call_if_eq VAR_RESULT, DOME_ROUND1, PokemonWorldTournamentRoom_EventScript_TryDoAudienceMemberWalkToSeat
	applymovement LOCALID_DOME_ANNOUNCER, Common_Movement_WalkInPlaceDown
	waitmovement 0
	call PokemonWorldTournamentRoom_EventScript_AnnouncePlayer
	msgbox PokemonWorldTournamentRoom_Text_PlayerHasEnteredDome, MSGBOX_DEFAULT
	closemessage
	showobjectat LOCALID_DOME_PLAYER, MAP_POKEMON_WORLD_TOURNAMENT_ROOM
	goto_if_ne VAR_TEMP_F, DOME_FINAL, PokemonWorldTournamentRoom_EventScript_PlayerEnter
	goto_if_ne VAR_TEMP_E, FRONTIER_BRAIN_NOT_READY, PokemonWorldTournamentRoom_EventScript_PlayerEnterForTucker
PokemonWorldTournamentRoom_EventScript_PlayerEnter::
	applymovement LOCALID_DOME_PLAYER, PokemonWorldTournamentRoom_Movement_PlayerEnter
	goto PokemonWorldTournamentRoom_EventScript_AudienceReactToPlayer

PokemonWorldTournamentRoom_EventScript_PlayerEnterForTucker::
	applymovement LOCALID_DOME_PLAYER, PokemonWorldTournamentRoom_Movement_PlayerEnterForTucker
PokemonWorldTournamentRoom_EventScript_AudienceReactToPlayer::
	playse SE_M_ENCORE2
	call PokemonWorldTournamentRoom_EventScript_AudienceLookAround
	waitmovement 0
	goto_if_ne VAR_TEMP_F, DOME_FINAL, PokemonWorldTournamentRoom_EventScript_BattleOpponent
	goto_if_ne VAR_TEMP_E, FRONTIER_BRAIN_NOT_READY, PokemonWorldTournamentRoom_EventScript_AnnounceTucker
PokemonWorldTournamentRoom_EventScript_BattleOpponent::
	dome_getopponentname
	msgbox PokemonWorldTournamentRoom_Text_PlayerVersusTrainer, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DOME_PLAYER, PokemonWorldTournamentRoom_Movement_PlayerStepForward
	applymovement LOCALID_DOME_OPPONENT, PokemonWorldTournamentRoom_Movement_OpponentStepForward
	waitmovement 0
	tower_getopponentintro 0
	msgbox gStringVar4, MSGBOX_DEFAULT
	closemessage
	call PokemonWorldTournamentRoom_EventScript_DoDomeBattle
	setvar VAR_TEMP_2, NO_DRAW
	switch VAR_RESULT
	case B_OUTCOME_WON, PokemonWorldTournamentRoom_EventScript_DefeatedOpponent
	case B_OUTCOME_LOST, PokemonWorldTournamentRoom_EventScript_LostToOpponent
	case B_OUTCOME_FORFEITED, PokemonWorldTournamentRoom_EventScript_LostToOpponent
	setvar VAR_TEMP_2, DRAW_TRAINER
PokemonWorldTournamentRoom_EventScript_Draw::
	msgbox PokemonWorldTournamentRoom_Text_RefereeDecisionPleaseWait, MSGBOX_DEFAULT
	closemessage
	playse SE_M_ENCORE2
	call PokemonWorldTournamentRoom_EventScript_AudienceLookAround
	delay 60
	applymovement LOCALID_DOME_REFEREE, PokemonWorldTournamentRoom_Movement_RefereeEnter
	waitmovement 0
	applymovement LOCALID_DOME_ANNOUNCER, PokemonWorldTournamentRoom_Movement_AnnouncerFaceLeft
	waitmovement 0
	delay 180
	applymovement LOCALID_DOME_REFEREE, PokemonWorldTournamentRoom_Movement_RefereeExit
	waitmovement 0
	goto_if_eq VAR_TEMP_2, DRAW_TUCKER, PokemonWorldTournamentRoom_EventScript_LostToOpponent @ Tucker always wins on a draw
	dome_compareseeds
	switch VAR_RESULT
	case 1, PokemonWorldTournamentRoom_EventScript_DefeatedOpponent
PokemonWorldTournamentRoom_EventScript_LostToOpponent::
	applymovement LOCALID_DOME_ANNOUNCER, Common_Movement_WalkInPlaceDown
	waitmovement 0
	dome_getopponentname
	call_if_eq VAR_TEMP_2, NO_DRAW, PokemonWorldTournamentRoom_EventScript_OpponentWon
	call_if_eq VAR_TEMP_2, DRAW_TRAINER, PokemonWorldTournamentRoom_EventScript_OpponentWonDraw
	call_if_eq VAR_TEMP_2, DRAW_TUCKER, PokemonWorldTournamentRoom_EventScript_TuckerWonDraw
	playse SE_M_ENCORE2
	call PokemonWorldTournamentRoom_EventScript_AudienceLookAround
	delay 60
PokemonWorldTournamentRoom_EventScript_LostTourney::
	dome_resolvewinners DOME_PLAYER_LOST_MATCH
PokemonWorldTournamentRoom_EventScript_WarpToLobbyLost::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST
	goto PokemonWorldTournamentRoom_EventScript_WarpToLobby

PokemonWorldTournamentRoom_EventScript_OpponentWon::
	frontier_gettrainername STR_VAR_2
	message PokemonWorldTournamentRoom_Text_TrainerIsWinner
	waitmessage
	return

PokemonWorldTournamentRoom_EventScript_OpponentWonDraw::
	frontier_gettrainername STR_VAR_1
	message PokemonWorldTournamentRoom_Text_RefereesDecidedWinnerTrainer
	waitmessage
	return

PokemonWorldTournamentRoom_EventScript_TuckerWonDraw::
	message PokemonWorldTournamentRoom_Text_RefereesDecidedWinnerTucker
	waitmessage
	return

PokemonWorldTournamentRoom_EventScript_DefeatedOpponent::
	applymovement LOCALID_DOME_ANNOUNCER, Common_Movement_WalkInPlaceDown
	waitmovement 0
	call_if_eq VAR_TEMP_2, NO_DRAW, PokemonWorldTournamentRoom_EventScript_PlayerWon
	call_if_eq VAR_TEMP_2, DRAW_TRAINER, PokemonWorldTournamentRoom_EventScript_PlayerWonDraw
	playse SE_M_ENCORE2
	call PokemonWorldTournamentRoom_EventScript_AudienceLookAround
	delay 60
	dome_getroundtext
	dome_resolvewinners DOME_PLAYER_WON_MATCH
	frontier_get FRONTIER_DATA_BATTLE_NUM
	addvar VAR_RESULT, 1
	frontier_set FRONTIER_DATA_BATTLE_NUM, VAR_RESULT
	switch VAR_RESULT
	case DOME_ROUNDS_COUNT, PokemonWorldTournamentRoom_EventScript_WonTourney
	setvar VAR_0x8006, 1
	warp MAP_POKEMON_WORLD_TOURNAMENT_PRE_BATTLE_ROOM, 5, 3
	waitstate

PokemonWorldTournamentRoom_EventScript_WonTourney::
	applymovement LOCALID_DOME_PLAYER, PokemonWorldTournamentRoom_Movement_PlayerApproachAudience
	waitmovement 0
	frontier_get FRONTIER_DATA_LVL_MODE
	switch VAR_RESULT
	case FRONTIER_LVL_OPEN, PokemonWorldTournamentRoom_EventScript_WonLvOpenTourney
	msgbox PokemonWorldTournamentRoom_Text_PlayerIsLv50Champ, MSGBOX_DEFAULT
	goto PokemonWorldTournamentRoom_EventScript_CelebrateWin

PokemonWorldTournamentRoom_EventScript_WonLvOpenTourney::
	msgbox PokemonWorldTournamentRoom_Text_PlayerIsLvOpenChamp, MSGBOX_DEFAULT
PokemonWorldTournamentRoom_EventScript_CelebrateWin::
	special DoDomeConfetti
	playse SE_M_ENCORE2
	call PokemonWorldTournamentRoom_EventScript_AudienceLookAround
	delay 60
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_WON
	goto PokemonWorldTournamentRoom_EventScript_WarpToLobby

PokemonWorldTournamentRoom_EventScript_PlayerWon::
	msgbox PokemonWorldTournamentRoom_Text_PlayerIsWinner, MSGBOX_DEFAULT
	return

PokemonWorldTournamentRoom_EventScript_PlayerWonDraw::
	msgbox PokemonWorldTournamentRoom_Text_RefereesDecidedWinnerPlayer, MSGBOX_DEFAULT
	return

PokemonWorldTournamentRoom_EventScript_AnnouncePlayer::
	dome_get DOME_DATA_ATTEMPTED_CHALLENGE
	goto_if_eq VAR_RESULT, FALSE, PokemonWorldTournamentRoom_EventScript_AnnouncePlayerFirstAttempt
	dome_get DOME_DATA_HAS_WON_CHALLENGE
	goto_if_eq VAR_RESULT, FALSE, PokemonWorldTournamentRoom_EventScript_AnnouncePlayerNeverWon
	dome_get DOME_DATA_WIN_STREAK_ACTIVE
	goto_if_eq VAR_RESULT, FALSE, PokemonWorldTournamentRoom_EventScript_AnnouncePlayerBrokenStreak
	goto PokemonWorldTournamentRoom_EventScript_AnnouncePlayerChampion
	return

PokemonWorldTournamentRoom_EventScript_AnnouncePlayerFirstAttempt::
	call PokemonWorldTournamentRoom_EventScript_GetRoundNum
	switch VAR_RESULT
	case DOME_ROUND1, PokemonWorldTournamentRoom_EventScript_AnnouncePlayerFirstAttemptRound1
	case DOME_ROUND2, PokemonWorldTournamentRoom_EventScript_AnnouncePlayerFirstAttemptRound2
	case DOME_SEMIFINAL, PokemonWorldTournamentRoom_EventScript_AnnouncePlayerFirstAttemptSemifinal
	case DOME_FINAL, PokemonWorldTournamentRoom_EventScript_AnnouncePlayerFirstAttemptFinal
	return

PokemonWorldTournamentRoom_EventScript_AnnouncePlayerFirstAttemptRound1::
	message PokemonWorldTournamentRoom_Text_BrightNewHope
	waitmessage
	return

PokemonWorldTournamentRoom_EventScript_AnnouncePlayerFirstAttemptRound2::
	message PokemonWorldTournamentRoom_Text_RisingStar
	waitmessage
	return

PokemonWorldTournamentRoom_EventScript_AnnouncePlayerFirstAttemptSemifinal::
	message PokemonWorldTournamentRoom_Text_WillTheyRaceToChampionship
	waitmessage
	return

PokemonWorldTournamentRoom_EventScript_AnnouncePlayerFirstAttemptFinal::
	message PokemonWorldTournamentRoom_Text_CanAchieveChampionFirstTry
	waitmessage
	return

PokemonWorldTournamentRoom_EventScript_AnnouncePlayerNeverWon::
	call PokemonWorldTournamentRoom_EventScript_GetRoundNum
	switch VAR_RESULT
	case DOME_ROUND1, PokemonWorldTournamentRoom_EventScript_AnnouncePlayerNeverWonRound1
	case DOME_ROUND2, PokemonWorldTournamentRoom_EventScript_AnnouncePlayerNeverWonRound2
	case DOME_SEMIFINAL, PokemonWorldTournamentRoom_EventScript_AnnouncePlayerNeverWonSemifinal
	case DOME_FINAL, PokemonWorldTournamentRoom_EventScript_AnnouncePlayerNeverWonFinal
	return

PokemonWorldTournamentRoom_EventScript_AnnouncePlayerNeverWonRound1::
	message PokemonWorldTournamentRoom_Text_CanLossBeAvenged
	waitmessage
	return

PokemonWorldTournamentRoom_EventScript_AnnouncePlayerNeverWonRound2::
	message PokemonWorldTournamentRoom_Text_OnFireForChampionship
	waitmessage
	return

PokemonWorldTournamentRoom_EventScript_AnnouncePlayerNeverWonSemifinal::
	message PokemonWorldTournamentRoom_Text_WinHereAdvancesToFinal
	waitmessage
	return

PokemonWorldTournamentRoom_EventScript_AnnouncePlayerNeverWonFinal::
	message PokemonWorldTournamentRoom_Text_WillLongHeldDreamComeTrue
	waitmessage
	return

PokemonWorldTournamentRoom_EventScript_AnnouncePlayerChampion::
	goto_if_ne VAR_TEMP_F, DOME_FINAL, PokemonWorldTournamentRoom_EventScript_AnnouncePlayerChampionNoTucker
	switch VAR_TEMP_E
	case FRONTIER_BRAIN_SILVER, PokemonWorldTournamentRoom_EventScript_AnnouncePlayerPreTuckerSilver
	case FRONTIER_BRAIN_GOLD, PokemonWorldTournamentRoom_EventScript_AnnouncePlayerPreTuckerGold
	case FRONTIER_BRAIN_STREAK, PokemonWorldTournamentRoom_EventScript_AnnouncePlayerPreTuckerSilver
	case FRONTIER_BRAIN_STREAK_LONG, PokemonWorldTournamentRoom_EventScript_AnnouncePlayerPreTuckerGold
PokemonWorldTournamentRoom_EventScript_AnnouncePlayerChampionNoTucker::
	call PokemonWorldTournamentRoom_EventScript_GetRoundNum
	switch VAR_RESULT
	case DOME_ROUND1, PokemonWorldTournamentRoom_EventScript_AnnouncePlayerChampionRound1
	case DOME_ROUND2, PokemonWorldTournamentRoom_EventScript_AnnouncePlayerChampionRound2
	case DOME_SEMIFINAL, PokemonWorldTournamentRoom_EventScript_AnnouncePlayerChampionSemifinal
	case DOME_FINAL, PokemonWorldTournamentRoom_EventScript_AnnouncePlayerChampionFinal
	return

PokemonWorldTournamentRoom_EventScript_AnnouncePlayerChampionRound1::
	message PokemonWorldTournamentRoom_Text_TheInvincibleChampion
	waitmessage
	return

PokemonWorldTournamentRoom_EventScript_AnnouncePlayerChampionRound2::
	message PokemonWorldTournamentRoom_Text_CanAnyoneHopeToBeatTrainer
	waitmessage
	return

PokemonWorldTournamentRoom_EventScript_AnnouncePlayerChampionSemifinal::
	message PokemonWorldTournamentRoom_Text_DoBattlesExistSolelyForTrainer
	waitmessage
	return

PokemonWorldTournamentRoom_EventScript_AnnouncePlayerChampionFinal::
	message PokemonWorldTournamentRoom_Text_CurrentChampAimingToRetainTitle
	waitmessage
	return

PokemonWorldTournamentRoom_EventScript_AnnouncePlayerPreTuckerSilver::
	msgbox PokemonWorldTournamentRoom_Text_FeelGlowOfTrueMaster, MSGBOX_DEFAULT
	return

PokemonWorldTournamentRoom_EventScript_AnnouncePlayerPreTuckerGold::
	msgbox PokemonWorldTournamentRoom_Text_CanWinStreakBeStretched, MSGBOX_DEFAULT
	return

PokemonWorldTournamentRoom_EventScript_AnnouncePlayerBrokenStreak::
	call PokemonWorldTournamentRoom_EventScript_GetRoundNum
	switch VAR_RESULT
	case DOME_ROUND1, PokemonWorldTournamentRoom_EventScript_AnnouncePlayerBrokenStreakRound1
	case DOME_ROUND2, PokemonWorldTournamentRoom_EventScript_AnnouncePlayerBrokenStreakRound2
	case DOME_SEMIFINAL, PokemonWorldTournamentRoom_EventScript_AnnouncePlayerBrokenStreakSemifinal
	case DOME_FINAL, PokemonWorldTournamentRoom_EventScript_AnnouncePlayerBrokenStreakFinal
	return

PokemonWorldTournamentRoom_EventScript_AnnouncePlayerBrokenStreakRound1::
	message PokemonWorldTournamentRoom_Text_FormerChampHasReturned
	waitmessage
	return

PokemonWorldTournamentRoom_EventScript_AnnouncePlayerBrokenStreakRound2::
	message PokemonWorldTournamentRoom_Text_FormerToughnessReturned
	waitmessage
	return

PokemonWorldTournamentRoom_EventScript_AnnouncePlayerBrokenStreakSemifinal::
	message PokemonWorldTournamentRoom_Text_WillDoExpectedAdvanceToFinals
	waitmessage
	return

PokemonWorldTournamentRoom_EventScript_AnnouncePlayerBrokenStreakFinal::
	message PokemonWorldTournamentRoom_Text_WillFormerChampRegainGlory
	waitmessage
	return

PokemonWorldTournamentRoom_EventScript_GetRoundNum::
	frontier_get FRONTIER_DATA_BATTLE_NUM
	return

PokemonWorldTournamentRoom_EventScript_AnnounceTucker::
	switch VAR_TEMP_E
	case FRONTIER_BRAIN_SILVER, PokemonWorldTournamentRoom_EventScript_AnnounceTuckerSilver
	case FRONTIER_BRAIN_GOLD, PokemonWorldTournamentRoom_EventScript_AnnounceTuckerGold
	case FRONTIER_BRAIN_STREAK, PokemonWorldTournamentRoom_EventScript_AnnounceTuckerSilver
	case FRONTIER_BRAIN_STREAK_LONG, PokemonWorldTournamentRoom_EventScript_AnnounceTuckerGold

PokemonWorldTournamentRoom_EventScript_AnnounceTuckerSilver::
	msgbox PokemonWorldTournamentRoom_Text_MakeWayForDomeAceTucker, MSGBOX_DEFAULT
	goto PokemonWorldTournamentRoom_EventScript_TuckerEnter

PokemonWorldTournamentRoom_EventScript_AnnounceTuckerGold::
	msgbox PokemonWorldTournamentRoom_Text_LegendHasReturnedDomeAceTucker, MSGBOX_DEFAULT
PokemonWorldTournamentRoom_EventScript_TuckerEnter::
	closemessage
	applymovement LOCALID_DOME_AUDIENCE_TWIN, PokemonWorldTournamentRoom_Movement_AudienceTwinJump
	applymovement LOCALID_DOME_ANNOUNCER, PokemonWorldTournamentRoom_Movement_AnnouncerMoveForTuckerEntrance
	applymovement LOCALID_DOME_OPPONENT, PokemonWorldTournamentRoom_Movement_TuckerEnterAndDance
	playse SE_M_ENCORE2
	call PokemonWorldTournamentRoom_EventScript_AudienceLookAround
	waitse
	playse SE_M_ENCORE2
	call PokemonWorldTournamentRoom_EventScript_AudienceLookAround
	waitse
	playse SE_M_ENCORE2
	call PokemonWorldTournamentRoom_EventScript_AudienceLookAround
	waitse
	playse SE_M_ENCORE2
	call PokemonWorldTournamentRoom_EventScript_AudienceLookAround
	waitse
	playse SE_M_ENCORE2
	call PokemonWorldTournamentRoom_EventScript_AudienceLookAround
	waitse
	waitmovement 0
	message PokemonWorldTournamentRoom_Text_SpectatorTuckerChant
	waitmessage
	playse SE_M_ENCORE2
	call PokemonWorldTournamentRoom_EventScript_AudienceLookAround
	waitse
	switch VAR_TEMP_E
	case FRONTIER_BRAIN_GOLD, PokemonWorldTournamentRoom_EventScript_TuckerGoldIntro
	case FRONTIER_BRAIN_STREAK, PokemonWorldTournamentRoom_EventScript_BattleTuckerSilver
	case FRONTIER_BRAIN_STREAK_LONG, PokemonWorldTournamentRoom_EventScript_BattleTuckerGold
	frontier_get FRONTIER_DATA_HEARD_BRAIN_SPEECH
	goto_if_ne VAR_RESULT, FALSE, PokemonWorldTournamentRoom_EventScript_BattleTuckerSilver
	msgbox PokemonWorldTournamentRoom_Text_TuckerSilverIntro, MSGBOX_DEFAULT
	frontier_set FRONTIER_DATA_HEARD_BRAIN_SPEECH
PokemonWorldTournamentRoom_EventScript_BattleTuckerSilver::
	msgbox PokemonWorldTournamentRoom_Text_LetsSeeYourStrategy, MSGBOX_DEFAULT
	call PokemonWorldTournamentRoom_EventScript_DoTuckerBattle
	switch VAR_RESULT
	case B_OUTCOME_LOST, PokemonWorldTournamentRoom_EventScript_LostToTucker
	case B_OUTCOME_FORFEITED, PokemonWorldTournamentRoom_EventScript_LostToTucker
	case B_OUTCOME_DREW, PokemonWorldTournamentRoom_EventScript_TuckerDraw
	msgbox PokemonWorldTournamentRoom_Text_IncredibleVictorIsPlayer, MSGBOX_DEFAULT
	dome_resolvewinners DOME_PLAYER_WON_MATCH
	frontier_getsymbols
	goto_if_ne VAR_RESULT, 0, PokemonWorldTournamentRoom_EventScript_WonTourney
	closemessage
	applymovement LOCALID_DOME_OPPONENT, PokemonWorldTournamentRoom_Movement_TuckerApproachPlayer
	waitmovement 0
	msgbox PokemonWorldTournamentRoom_Text_SeeYourFrontierPass, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_SYMBOL
	message PokemonWorldTournamentRoom_Text_ReceivedTacticsSymbol
	waitmessage
	waitfanfare
	frontier_givesymbol
	msgbox PokemonWorldTournamentRoom_Text_WontUnderestimateYouNextTime, MSGBOX_DEFAULT
	goto PokemonWorldTournamentRoom_EventScript_WonTourney

PokemonWorldTournamentRoom_EventScript_TuckerGoldIntro::
	frontier_get FRONTIER_DATA_HEARD_BRAIN_SPEECH
	goto_if_ne VAR_RESULT, FALSE, PokemonWorldTournamentRoom_EventScript_BattleTuckerGold
	msgbox PokemonWorldTournamentRoom_Text_TuckerGoldIntro, MSGBOX_DEFAULT
	frontier_set FRONTIER_DATA_HEARD_BRAIN_SPEECH
PokemonWorldTournamentRoom_EventScript_BattleTuckerGold::
	msgbox PokemonWorldTournamentRoom_Text_UnleashAllPowerIPossess, MSGBOX_DEFAULT
	call PokemonWorldTournamentRoom_EventScript_DoTuckerBattle
	switch VAR_RESULT
	case B_OUTCOME_LOST, PokemonWorldTournamentRoom_EventScript_LostToTucker
	case B_OUTCOME_FORFEITED, PokemonWorldTournamentRoom_EventScript_LostToTucker
	case B_OUTCOME_DREW, PokemonWorldTournamentRoom_EventScript_TuckerDraw
	msgbox PokemonWorldTournamentRoom_Text_IncredibleVictorIsPlayer, MSGBOX_DEFAULT
	dome_resolvewinners DOME_PLAYER_WON_MATCH
	frontier_getsymbols
	goto_if_eq VAR_RESULT, 2, PokemonWorldTournamentRoom_EventScript_WonTourney
	closemessage
	applymovement LOCALID_DOME_OPPONENT, PokemonWorldTournamentRoom_Movement_TuckerApproachPlayer
	waitmovement 0
	msgbox PokemonWorldTournamentRoom_Text_NeverLostWhenPowerUnleashed, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_SYMBOL
	message PokemonWorldTournamentRoom_Text_TacticsSymbolTookGoldenShine
	waitmessage
	waitfanfare
	frontier_givesymbol
	msgbox PokemonWorldTournamentRoom_Text_LookForwardToNextEncounter, MSGBOX_DEFAULT
	goto PokemonWorldTournamentRoom_EventScript_WonTourney

PokemonWorldTournamentRoom_EventScript_DoTuckerBattle::
	msgbox PokemonWorldTournamentRoom_Text_PlayerVersusTucker, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DOME_PLAYER, PokemonWorldTournamentRoom_Movement_PlayerStepForward2
	applymovement LOCALID_DOME_OPPONENT, PokemonWorldTournamentRoom_Movement_TuckerStepForward
	waitmovement 0
	call PokemonWorldTournamentRoom_EventScript_DoDomeBattle
	return

PokemonWorldTournamentRoom_EventScript_LostToTucker::
	msgbox PokemonWorldTournamentRoom_Text_WinnerIsTucker, MSGBOX_DEFAULT
	playse SE_M_ENCORE2
	call PokemonWorldTournamentRoom_EventScript_AudienceLookAround
	waitse
	goto PokemonWorldTournamentRoom_EventScript_LostTourney

PokemonWorldTournamentRoom_EventScript_TuckerDraw::
	setvar VAR_TEMP_2, DRAW_TUCKER
	goto PokemonWorldTournamentRoom_EventScript_Draw

PokemonWorldTournamentRoom_EventScript_DoDomeBattle::
	frontier_set FRONTIER_DATA_RECORD_DISABLED, FALSE
	special HealPlayerParty
	setvar VAR_TEMP_9, 1
	dofacilitytrainerbattle FACILITY_BATTLE_DOME
	waitstate
	setvar VAR_TEMP_9, 0
	dome_restorehelditems
	special HealPlayerParty
	dome_resetsketch
	return

PokemonWorldTournamentRoom_OnWarp:
	map_script_2 VAR_TEMP_1, 0, PokemonWorldTournamentRoom_EventScript_SetUpObjects
	.2byte 0

PokemonWorldTournamentRoom_EventScript_SetUpObjects::
	hideobjectat LOCALID_DOME_PLAYER, MAP_POKEMON_WORLD_TOURNAMENT_ROOM
	call PokemonWorldTournamentRoom_EventScript_AddAudience
	call PokemonWorldTournamentRoom_EventScript_SetPlayerGfx
	setvar VAR_TEMP_1, 1
	applymovement LOCALID_PLAYER, PokemonWorldTournamentRoom_Movement_SetInvisible
	frontier_get FRONTIER_DATA_BATTLE_NUM
	goto_if_ne VAR_RESULT, DOME_FINAL, PokemonWorldTournamentRoom_EventScript_EndSetUpObjects
	frontier_getbrainstatus
	copyvar VAR_TEMP_E, VAR_RESULT
	goto_if_eq VAR_RESULT, FRONTIER_BRAIN_NOT_READY, PokemonWorldTournamentRoom_EventScript_EndSetUpObjects
	call BattleFrontier_EventScript_SetBrainObjectGfx
	setobjectxyperm LOCALID_DOME_OPPONENT, 13, 9
	removeobject LOCALID_DOME_OPPONENT
	delay 1
	addobject LOCALID_DOME_OPPONENT
	applymovement LOCALID_DOME_OPPONENT, PokemonWorldTournamentRoom_Movement_SetInvisibleFacingUp
PokemonWorldTournamentRoom_EventScript_EndSetUpObjects::
	end

PokemonWorldTournamentRoom_OnResume:
	call_if_eq VAR_TEMP_9, 1, PokemonWorldTournamentRoom_EventScript_CallAddAudience
	end

PokemonWorldTournamentRoom_EventScript_CallAddAudience::
	call PokemonWorldTournamentRoom_EventScript_AddAudience
	return

@ Add audience members to supplement the permanent object event audience
PokemonWorldTournamentRoom_EventScript_AddAudience::
	call_if_eq VAR_TEMP_F, DOME_ROUND1, PokemonWorldTournamentRoom_EventScript_AddRound1Audience
	call_if_eq VAR_TEMP_F, DOME_ROUND2, PokemonWorldTournamentRoom_EventScript_AddRound2Audience
	call_if_eq VAR_TEMP_F, DOME_SEMIFINAL, PokemonWorldTournamentRoom_EventScript_AddSemifinalAudience
	call_if_eq VAR_TEMP_F, DOME_FINAL, PokemonWorldTournamentRoom_EventScript_AddFinalAudience
	return

PokemonWorldTournamentRoom_EventScript_AddRound1Audience::
	return

PokemonWorldTournamentRoom_EventScript_AddRound2Audience::
	createvobject OBJ_EVENT_GFX_SCIENTIST_1, 1, 3, 0
	createvobject OBJ_EVENT_GFX_EXPERT_F, 4, 6, 0
	createvobject OBJ_EVENT_GFX_NINJA_BOY, 6, 8, 0
	createvobject OBJ_EVENT_GFX_LITTLE_GIRL, 9, 11, 0
	createvobject OBJ_EVENT_GFX_SCIENTIST_1, 11, 13, 0
	createvobject OBJ_EVENT_GFX_MAN_5, 13, 15, 0
	createvobject OBJ_EVENT_GFX_BEAUTY, 19, 7, 1
	createvobject OBJ_EVENT_GFX_WOMAN_5, 22, 11, 1
	createvobject OBJ_EVENT_GFX_LITTLE_BOY, 25, 15, 1
	createvobject OBJ_EVENT_GFX_YOUNGSTER, 26, 2, 2
	createvobject OBJ_EVENT_GFX_SCHOOL_KID_M, 29, 5, 1
	return

PokemonWorldTournamentRoom_EventScript_AddSemifinalAudience::
	createvobject OBJ_EVENT_GFX_SCIENTIST_1, 1, 3, 0
	createvobject OBJ_EVENT_GFX_EXPERT_F, 4, 6, 0
	createvobject OBJ_EVENT_GFX_NINJA_BOY, 6, 8, 0
	createvobject OBJ_EVENT_GFX_WOMAN_2, 7, 9, 0
	createvobject OBJ_EVENT_GFX_LITTLE_GIRL, 9, 11, 0
	createvobject OBJ_EVENT_GFX_LASS, 10, 12, 0
	createvobject OBJ_EVENT_GFX_SCIENTIST_1, 11, 13, 0
	createvobject OBJ_EVENT_GFX_MAN_5, 13, 15, 0
	createvobject OBJ_EVENT_GFX_GENTLEMAN, 15, 2, 1
	createvobject OBJ_EVENT_GFX_NINJA_BOY, 16, 3, 1
	createvobject OBJ_EVENT_GFX_WOMAN_2, 17, 4, 1
	createvobject OBJ_EVENT_GFX_BEAUTY, 19, 7, 1
	createvobject OBJ_EVENT_GFX_EXPERT_F, 20, 9, 1
	createvobject OBJ_EVENT_GFX_WOMAN_5, 22, 11, 1
	createvobject OBJ_EVENT_GFX_SCIENTIST_1, 23, 13, 1
	createvobject OBJ_EVENT_GFX_LITTLE_BOY, 25, 15, 1
	createvobject OBJ_EVENT_GFX_YOUNGSTER, 26, 2, 2
	createvobject OBJ_EVENT_GFX_HEX_MANIAC, 28, 5, 2
	createvobject OBJ_EVENT_GFX_SCHOOL_KID_M, 29, 5, 1
	createvobject OBJ_EVENT_GFX_MART_EMPLOYEE, 30, 6, 2
	createvobject OBJ_EVENT_GFX_WOMAN_5, 31, 8, 2
	return

PokemonWorldTournamentRoom_EventScript_AddFinalAudience::
	createvobject OBJ_EVENT_GFX_NINJA_BOY, 0, 2, 0
	createvobject OBJ_EVENT_GFX_SCIENTIST_1, 1, 3, 0
	createvobject OBJ_EVENT_GFX_BEAUTY, 2, 15, 0
	createvobject OBJ_EVENT_GFX_MAN_5, 3, 5, 0
	createvobject OBJ_EVENT_GFX_EXPERT_F, 4, 6, 0
	createvobject OBJ_EVENT_GFX_SCIENTIST_1, 5, 7, 0
	createvobject OBJ_EVENT_GFX_NINJA_BOY, 6, 8, 0
	createvobject OBJ_EVENT_GFX_WOMAN_2, 7, 9, 0
	createvobject OBJ_EVENT_GFX_WOMAN_3, 8, 10, 0
	createvobject OBJ_EVENT_GFX_LITTLE_GIRL, 9, 11, 0
	createvobject OBJ_EVENT_GFX_LASS, 10, 12, 0
	createvobject OBJ_EVENT_GFX_SCIENTIST_1, 11, 13, 0
	createvobject OBJ_EVENT_GFX_BEAUTY, 12, 14, 0
	createvobject OBJ_EVENT_GFX_MAN_5, 13, 15, 2
	createvobject OBJ_EVENT_GFX_HIKER, 14, 12, 2
	createvobject OBJ_EVENT_GFX_GENTLEMAN, 15, 2, 1
	createvobject OBJ_EVENT_GFX_NINJA_BOY, 16, 3, 1
	createvobject OBJ_EVENT_GFX_WOMAN_2, 17, 4, 1
	createvobject OBJ_EVENT_GFX_WOMAN_3, 18, 6, 1
	createvobject OBJ_EVENT_GFX_BEAUTY, 19, 7, 1
	createvobject OBJ_EVENT_GFX_EXPERT_F, 20, 9, 1
	createvobject OBJ_EVENT_GFX_MAN_2, 21, 10, 1
	createvobject OBJ_EVENT_GFX_WOMAN_5, 22, 11, 1
	createvobject OBJ_EVENT_GFX_SCIENTIST_1, 23, 13, 1
	createvobject OBJ_EVENT_GFX_GENTLEMAN, 24, 14, 1
	createvobject OBJ_EVENT_GFX_LITTLE_BOY, 25, 15, 1
	createvobject OBJ_EVENT_GFX_YOUNGSTER, 26, 2, 2
	createvobject OBJ_EVENT_GFX_FAT_MAN, 27, 3, 2
	createvobject OBJ_EVENT_GFX_HEX_MANIAC, 28, 5, 2
	createvobject OBJ_EVENT_GFX_SCHOOL_KID_M, 29, 5, 1
	createvobject OBJ_EVENT_GFX_MART_EMPLOYEE, 30, 6, 2
	createvobject OBJ_EVENT_GFX_WOMAN_5, 31, 8, 2
	return

PokemonWorldTournamentRoom_Movement_SetInvisible:
	set_invisible
	step_end

PokemonWorldTournamentRoom_Movement_PlayerEnter:
	set_visible
	delay_16
	walk_up
	walk_up
	walk_up
	walk_right
PokemonWorldTournamentRoom_Movement_PlayerStepForward:
	walk_right
	step_end

PokemonWorldTournamentRoom_Movement_PlayerApproachAudience:
	walk_up
	step_end

@ Identical to Movement_PlayerEnter
PokemonWorldTournamentRoom_Movement_PlayerEnterForTucker:
	set_visible
	delay_16
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	step_end

PokemonWorldTournamentRoom_Movement_PlayerStepForward2:
	walk_right
	step_end

PokemonWorldTournamentRoom_Movement_OpponentStepForward:
	walk_left
	step_end

PokemonWorldTournamentRoom_Movement_SetInvisibleFacingUp:
	face_up
	set_invisible
	step_end

PokemonWorldTournamentRoom_Movement_TuckerEnterAndDance:
	set_visible
	walk_up
	walk_up
	walk_up
	face_left
	delay_8
	delay_4
	face_down
	delay_8
	delay_4
	face_right
	delay_8
	delay_4
	face_up
	delay_8
	delay_4
	face_left
	delay_16
	walk_fast_up
	walk_fast_up
	face_left
	delay_8
	delay_4
	face_down
	delay_8
	delay_4
	face_right
	delay_8
	delay_4
	face_up
	delay_8
	delay_4
	face_left
	jump_2_left
	unlock_facing_direction
	face_up
	lock_facing_direction
	jump_2_left
	jump_2_left
	unlock_facing_direction
	face_right
	lock_facing_direction
	jump_2_left
	unlock_facing_direction
	face_down
	delay_2
	face_left
	delay_8
	delay_4
	face_up
	delay_8
	delay_4
	face_right
	delay_8
	delay_4
	face_down
	delay_8
	delay_4
	face_left
	delay_4
	face_up
	delay_4
	face_right
	delay_4
	face_down
	delay_4
	face_left
	delay_2
	face_up
	delay_2
	face_right
	delay_2
	face_down
	delay_2
	face_left
	lock_facing_direction
	walk_right
	walk_slow_right
	walk_right
	walk_slow_right
	unlock_facing_direction
	face_up
	delay_16
	jump_in_place_up
	jump_in_place_up
	delay_16
	walk_right
	walk_right
	walk_right
	jump_in_place_up
	delay_16
	walk_right
	walk_down
	walk_down
	face_left
	delay_2
	face_up
	delay_2
	face_right
	delay_2
	face_down
	delay_2
	face_left
	delay_4
	walk_left
	walk_left
	step_end

PokemonWorldTournamentRoom_Movement_AnnouncerMoveForTuckerEntrance:
	delay_16
	delay_16
	walk_left
	walk_left
	walk_in_place_faster_right
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_right
	walk_right
	walk_in_place_faster_down
	step_end

PokemonWorldTournamentRoom_Movement_TuckerStepForward:
	walk_left
	step_end

PokemonWorldTournamentRoom_Movement_TuckerApproachPlayer:
	walk_left
	walk_left
	step_end

PokemonWorldTournamentRoom_EventScript_AudienceLookAround::
	turnvobject 0, DIR_EAST
	turnvobject 2, DIR_EAST
	turnvobject 4, DIR_EAST
	turnvobject 6, DIR_EAST
	turnvobject 8, DIR_EAST
	turnvobject 10, DIR_WEST
	turnvobject 12, DIR_WEST
	turnvobject 14, DIR_WEST
	turnvobject 16, DIR_WEST
	turnvobject 18, DIR_WEST
	turnvobject 20, DIR_EAST
	turnvobject 22, DIR_EAST
	turnvobject 24, DIR_EAST
	turnvobject 26, DIR_EAST
	turnvobject 28, DIR_EAST
	turnvobject 30, DIR_EAST
	delay 20
	turnvobject 0, DIR_SOUTH
	turnvobject 2, DIR_SOUTH
	turnvobject 4, DIR_SOUTH
	turnvobject 6, DIR_SOUTH
	turnvobject 8, DIR_SOUTH
	turnvobject 10, DIR_SOUTH
	turnvobject 12, DIR_SOUTH
	turnvobject 14, DIR_SOUTH
	turnvobject 16, DIR_SOUTH
	turnvobject 18, DIR_SOUTH
	turnvobject 20, DIR_SOUTH
	turnvobject 22, DIR_SOUTH
	turnvobject 24, DIR_SOUTH
	turnvobject 26, DIR_SOUTH
	turnvobject 28, DIR_SOUTH
	turnvobject 30, DIR_SOUTH
	delay 20
	turnvobject 1, DIR_EAST
	turnvobject 3, DIR_EAST
	turnvobject 5, DIR_EAST
	turnvobject 7, DIR_EAST
	turnvobject 9, DIR_EAST
	turnvobject 11, DIR_WEST
	turnvobject 13, DIR_WEST
	turnvobject 15, DIR_WEST
	turnvobject 17, DIR_WEST
	turnvobject 19, DIR_WEST
	turnvobject 21, DIR_EAST
	turnvobject 23, DIR_EAST
	turnvobject 25, DIR_EAST
	turnvobject 27, DIR_WEST
	turnvobject 31, DIR_WEST
	delay 20
	turnvobject 1, DIR_SOUTH
	turnvobject 3, DIR_SOUTH
	turnvobject 5, DIR_SOUTH
	turnvobject 7, DIR_SOUTH
	turnvobject 9, DIR_SOUTH
	turnvobject 11, DIR_SOUTH
	turnvobject 13, DIR_SOUTH
	turnvobject 15, DIR_SOUTH
	turnvobject 17, DIR_SOUTH
	turnvobject 19, DIR_SOUTH
	turnvobject 21, DIR_SOUTH
	turnvobject 23, DIR_SOUTH
	turnvobject 25, DIR_SOUTH
	turnvobject 27, DIR_SOUTH
	turnvobject 31, DIR_SOUTH
	delay 20
	return

PokemonWorldTournamentRoom_EventScript_WarpToLobby::
	copyvar VAR_RESULT, VAR_FRONTIER_BATTLE_MODE
	goto_if_eq VAR_RESULT, FRONTIER_MODE_DOUBLES, PokemonWorldTournamentPreBattleRoom_EventScript_WarpToLobbyDoubles
	warp MAP_POKEMON_WORLD_TOURNAMENT_LOBBY, 5, 11
	waitstate
	end

PokemonWorldTournamentPreBattleRoom_EventScript_WarpToLobbyDoubles::
	warp MAP_POKEMON_WORLD_TOURNAMENT_LOBBY, 17, 11
	waitstate
	end

@ On round 1 there's a 50% chance that a specific audience member will walk to his seat
PokemonWorldTournamentRoom_EventScript_SetWalkingAudienceMemberPos::
	random 2
	copyvar VAR_TEMP_D, VAR_RESULT
	goto_if_eq VAR_TEMP_D, 0, Common_EventScript_NopReturn
	setobjectxyperm LOCALID_DOME_AUDIENCE_WALKING, 2, 0
	setobjectmovementtype LOCALID_DOME_AUDIENCE_WALKING, MOVEMENT_TYPE_FACE_RIGHT
	return

PokemonWorldTournamentRoom_EventScript_TryDoAudienceMemberWalkToSeat::
	goto_if_eq VAR_TEMP_D, 0, Common_EventScript_NopReturn
	applymovement LOCALID_DOME_AUDIENCE_WALKING, PokemonWorldTournamentRoom_Movement_AudienceMemberWalkToSeat
	return

PokemonWorldTournamentRoom_Movement_AudienceTwinJump:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_8
	disable_jump_landing_ground_effect
	jump_in_place_down
	delay_4
	jump_in_place_down
	enable_jump_landing_ground_effect
	step_end

PokemonWorldTournamentRoom_Movement_AudienceMemberWalkToSeat:
	walk_down
	walk_down
	walk_right
	walk_right
	walk_in_place_faster_down
	step_end

PokemonWorldTournamentRoom_Movement_RefereeEnter:
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

PokemonWorldTournamentRoom_Movement_AnnouncerFaceLeft:
	walk_in_place_faster_left
	step_end

PokemonWorldTournamentRoom_Movement_RefereeExit:
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

PokemonWorldTournamentRoom_Text_PlayerHasEnteredDome:
	.string "{PLAYER} has entered the PWT!$"

PokemonWorldTournamentRoom_Text_PlayerVersusTrainer:
	.string "{STR_VAR_1}\n"
	.string "match!\p"
	.string "{PLAYER} versus {STR_VAR_2}!\p"
	.string "Let the battle begin!$"

PokemonWorldTournamentRoom_Text_PlayerIsWinner:
	.string "{PLAYER} is the winner!\n"
	.string "Congratulations!$"

PokemonWorldTournamentRoom_Text_TrainerIsWinner:
	.string "{STR_VAR_2} is the winner!\n"
	.string "Congratulations!$"

PokemonWorldTournamentRoom_Text_PlayerIsLv50Champ:
	.string "{PLAYER} is the Level 50\n"
	.string "Battle Tournament CHAMPION!\p"
	.string "Congratulations!$"

PokemonWorldTournamentRoom_Text_PlayerIsLvOpenChamp:
	.string "{PLAYER} is the Open Level\n"
	.string "Battle Tournament CHAMPION!\p"
	.string "Congratulations!$"

PokemonWorldTournamentRoom_Text_RefereeDecisionPleaseWait:
	.string "What an unbelievable finish!\n"
	.string "We have a double knockout!\p"
	.string "In this event, the Battle Tournament\n"
	.string "rules call for a REFEREE'S decision.\p"
	.string "Please wait while the judging\n"
	.string "is under way.$"

PokemonWorldTournamentRoom_Text_RefereesDecidedWinnerTrainer:
	.string "The REFEREES have reached\n"
	.string "a decision!\p"
	.string "The winner is…\n"
	.string "Oh, my goodness!\l"
	.string "The winner is {STR_VAR_1}!\l"
	.string "Congratulations!$"

PokemonWorldTournamentRoom_Text_RefereesDecidedWinnerPlayer:
	.string "The REFEREES have reached\n"
	.string "a decision!\p"
	.string "The winner is…\n"
	.string "Oh, my goodness!\l"
	.string "The winner is {PLAYER}!\l"
	.string "Congratulations!$"

PokemonWorldTournamentRoom_Text_BrightNewHope:
	.string "The bright new hope!\p"
	.string "$"

PokemonWorldTournamentRoom_Text_RisingStar:
	.string "The rising star!\p"
	.string "$"

PokemonWorldTournamentRoom_Text_WillTheyRaceToChampionship:
	.string "Will this TRAINER race to\n"
	.string "the championship?\p"
	.string "$"

PokemonWorldTournamentRoom_Text_CanAchieveChampionFirstTry:
	.string "Can the feat of a championship\n"
	.string "on the first try be achieved?\p"
	.string "$"

PokemonWorldTournamentRoom_Text_CanLossBeAvenged:
	.string "Can the loss of the last match\n"
	.string "be avenged?\p"
	.string "$"

PokemonWorldTournamentRoom_Text_OnFireForChampionship:
	.string "The TRAINER is on fire for\n"
	.string "the first championship try!\p"
	.string "$"

PokemonWorldTournamentRoom_Text_WinHereAdvancesToFinal:
	.string "A win here means this TRAINER\n"
	.string "advances to the final!\p"
	.string "$"

PokemonWorldTournamentRoom_Text_WillLongHeldDreamComeTrue:
	.string "Will the long-held dream of\n"
	.string "a championship finally come true?\p"
	.string "$"

PokemonWorldTournamentRoom_Text_TheInvincibleChampion:
	.string "The invincible champion!\p"
	.string "$"

PokemonWorldTournamentRoom_Text_CanAnyoneHopeToBeatTrainer:
	.string "Can anyone hope to beat this\n"
	.string "TRAINER?\p"
	.string "$"

PokemonWorldTournamentRoom_Text_DoBattlesExistSolelyForTrainer:
	.string "Do battles exist solely for\n"
	.string "this TRAINER?\p"
	.string "$"

PokemonWorldTournamentRoom_Text_CurrentChampAimingToRetainTitle:
	.string "The current champion aiming to\n"
	.string "retain the title!\p"
	.string "$"

PokemonWorldTournamentRoom_Text_FormerChampHasReturned:
	.string "The former champion has returned!\p"
	.string "$"

PokemonWorldTournamentRoom_Text_FormerToughnessReturned:
	.string "The former toughness has returned!\p"
	.string "$"

PokemonWorldTournamentRoom_Text_WillDoExpectedAdvanceToFinals:
	.string "Will this TRAINER do as expected\n"
	.string "and advance to the finals?\p"
	.string "$"

PokemonWorldTournamentRoom_Text_WillFormerChampRegainGlory:
	.string "Will the former champ regain\n"
	.string "lost glory?\p"
	.string "$"

PokemonWorldTournamentRoom_Text_FeelGlowOfTrueMaster:
	.string "Feel the glow of a true master!$"

PokemonWorldTournamentRoom_Text_MakeWayForDomeAceTucker:
	.string "And now… The TRAINER standing in\n"
	.string "{PLAYER}'s record-setting path…\p"
	.string "Yes! The one and only!\n"
	.string "The PWT COMMISSIONER!\l"
	.string "Our very own DOME ACE!\l"
	.string "Make way for TUCKER!$"

PokemonWorldTournamentRoom_Text_SpectatorTuckerChant:
	.string "Spectators: TUCKER! TUCKER!\n"
	.string "TUCKER! TUCKER! TUCKER!$"

PokemonWorldTournamentRoom_Text_TuckerSilverIntro:
	.string "TUCKER: Ahahah!\p"
	.string "Do you hear it? This crowd!\n"
	.string "They're all itching to see our match!\p"
	.string "Ahahah!\p"
	.string "I bet you're twitching all over from\n"
	.string "the tension of getting to battle me!\p"
	.string "But don't you worry about a thing!\p"
	.string "I'm the no. 1 star of the PWT!\n"
	.string "I, TUCKER the DOME ACE, will bathe you\l"
	.string "in my brilliant glow!$"

PokemonWorldTournamentRoom_Text_LetsSeeYourStrategy:
	.string "Your strategy!\n"
	.string "Let's see it!$"

PokemonWorldTournamentRoom_Text_IncredibleVictorIsPlayer:
	.string "Unbelievable! It's incredible!\n"
	.string "The victor is {PLAYER}!$"

PokemonWorldTournamentRoom_Text_WinnerIsTucker:
	.string "The winner is TUCKER!\n"
	.string "The DOME ACE has prevailed!\p"
	.string "Congratulations, TUCKER!$"

PokemonWorldTournamentRoom_Text_SeeYourFrontierPass:
	.string "TUCKER: Rules are rules!\n"
	.string "Let me see your FRONTIER PASS.$"

PokemonWorldTournamentRoom_Text_ReceivedTacticsSymbol:
	.string "The Tactics Symbol was embossed on\n"
	.string "the FRONTIER PASS!$"

PokemonWorldTournamentRoom_Text_WontUnderestimateYouNextTime:
	.string "… … … … … …\p"
	.string "I sorely underestimated you. I won't\n"
	.string "make the same mistake next time…$"

PokemonWorldTournamentRoom_Text_CanWinStreakBeStretched:
	.string "Can the win streak be stretched?\n"
	.string "The confidence is there!$"

PokemonWorldTournamentRoom_Text_LegendHasReturnedDomeAceTucker:
	.string "Ladies and gentlemen!\n"
	.string "Boys, girls, and POKéMON!\p"
	.string "Finally!\n"
	.string "Finally, the legend has returned!\p"
	.string "Yes, the name of that legend!\n"
	.string "Our very own DOME ACE!\l"
	.string "It's none other than TUCKER!$"

PokemonWorldTournamentRoom_Text_TuckerGoldIntro:
	.string "TUCKER: Ah…\n"
	.string "The pummeling roar of the crowd…\l"
	.string "Their furnace-like heat of excitement…\l"
	.string "This is a wonderful place…\p"
	.string "To the crowd, I am the DOME ACE…\n"
	.string "I represent their hopes and dreams…\l"
	.string "I must never fade from their sight…\p"
	.string "I must burn!\n"
	.string "Brighter and more brilliant!\l"
	.string "I must light all that gather here!$"

PokemonWorldTournamentRoom_Text_UnleashAllPowerIPossess:
	.string "I will unleash all the power that\n"
	.string "I possess! Right here and now!$"

PokemonWorldTournamentRoom_Text_NeverLostWhenPowerUnleashed:
	.string "TUCKER: You're genuinely fantastic!\p"
	.string "Never before! I haven't ever lost in the\n"
	.string "times I've had to unleash my power.\p"
	.string "Yes, quite fantastic!\n"
	.string "Your FRONTIER PASS, please?$"

PokemonWorldTournamentRoom_Text_TacticsSymbolTookGoldenShine:
	.string "The Tactics Symbol took on\n"
	.string "a golden shine!$"

PokemonWorldTournamentRoom_Text_LookForwardToNextEncounter:
	.string "You're strong, but above all,\n"
	.string "you have a unique charm!\p"
	.string "In you, I see a definite potential for\n"
	.string "a superstar like me.\p"
	.string "I will very much look forward to\n"
	.string "our next encounter!$"

@ Unused
PokemonWorldTournamentRoom_Text_PlayerIsLv50Champ2:
	.string "{PLAYER} is the Level 50\n"
	.string "Battle Tournament CHAMPION!\p"
	.string "Congratulations!$"

@ Unused
PokemonWorldTournamentRoom_Text_PlayerIsLvOpenChamp2:
	.string "{PLAYER} is the Open Level\n"
	.string "Battle Tournament CHAMPION!\p"
	.string "Congratulations!$"

PokemonWorldTournamentRoom_Text_PlayerVersusTucker:
	.string "The final match!\p"
	.string "{PLAYER} versus the DOME ACE, TUCKER!\p"
	.string "Let the battle begin!$"

PokemonWorldTournamentRoom_Text_RefereesDecidedWinnerTucker:
	.string "The REFEREES have reached\n"
	.string "a decision!\p"
	.string "The winner is…\n"
	.string "Oh, my goodness!\l"
	.string "The winner is our very own DOME ACE!\l"
	.string "It's TUCKER!\p"
	.string "Congratulations! And thank you!\n"
	.string "Let's hear it for the DOME ACE, TUCKER!$"
