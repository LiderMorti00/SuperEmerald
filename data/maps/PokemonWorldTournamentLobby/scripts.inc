@ Super Emerald: Pokemon World Tournament. A copy of the Battle Dome scripts (the PWT runs on the
@ Dome engine) with its own labels, warps and texts; nothing here is shared with Hoenn's Dome.
@ PWT-only parts: data/scripts/se_pwt.inc and src/se_pwt.c.

PokemonWorldTournamentLobby_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SE_Pwt_UsePwtRecords
	map_script MAP_SCRIPT_ON_RESUME, PokemonWorldTournamentLobby_OnResume
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PokemonWorldTournamentLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PokemonWorldTournamentLobby_OnWarp
	.byte 0

PokemonWorldTournamentLobby_OnResume:
	dome_initresultstree
	end

PokemonWorldTournamentLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, PokemonWorldTournamentLobby_EventScript_TurnPlayerNorth
	.2byte 0

PokemonWorldTournamentLobby_EventScript_TurnPlayerNorth::
	setvar VAR_TEMP_1, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

PokemonWorldTournamentLobby_OnFrame:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, PokemonWorldTournamentLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, PokemonWorldTournamentLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, PokemonWorldTournamentLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, PokemonWorldTournamentLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, PokemonWorldTournamentLobby_EventScript_LostChallenge
	.2byte 0

PokemonWorldTournamentLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

PokemonWorldTournamentLobby_EventScript_QuitWithoutSaving::
	lockall
	msgbox PokemonWorldTournamentLobby_Text_DidntSaveBeforeQuitting, MSGBOX_DEFAULT
	closemessage
	dome_set DOME_DATA_WIN_STREAK, 0
	dome_set DOME_DATA_WIN_STREAK_ACTIVE, FALSE
	dome_set DOME_DATA_ATTEMPTED_CHALLENGE, TRUE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

PokemonWorldTournamentLobby_EventScript_WonChallenge::
	call BattleFrontier_EventScript_IncrementWinStreak
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, PokemonWorldTournamentLobby_EventScript_DefeatedAce
	msgbox PokemonWorldTournamentLobby_Text_CongratsForWinningTourney, MSGBOX_DEFAULT
	goto PokemonWorldTournamentLobby_EventScript_GiveBattlePoints

PokemonWorldTournamentLobby_EventScript_DefeatedAce::
	msgbox PokemonWorldTournamentLobby_Text_CongratsDefeatedTucker, MSGBOX_DEFAULT
PokemonWorldTournamentLobby_EventScript_GiveBattlePoints::
	msgbox PokemonWorldTournamentLobby_Text_AwardTheseBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	call SE_Pwt_GiveCupPrize
	message PokemonWorldTournamentLobby_Text_RecordWillBeSaved
	waitmessage
	special LoadPlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	frontier_checkairshow
	dome_set DOME_DATA_ATTEMPTED_CHALLENGE, TRUE
	dome_set DOME_DATA_HAS_WON_CHALLENGE, TRUE
	dome_set DOME_DATA_WIN_STREAK_ACTIVE, TRUE
	special LoadPlayerParty
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	goto PokemonWorldTournamentLobby_EventScript_AskRecordBattle

PokemonWorldTournamentLobby_EventScript_LostChallenge::
	lockall
	msgbox PokemonWorldTournamentLobby_Text_ThankYouForPlaying, MSGBOX_DEFAULT
	message PokemonWorldTournamentLobby_Text_RecordWillBeSaved
	waitmessage
	special LoadPlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	frontier_checkairshow
	dome_set DOME_DATA_WIN_STREAK_ACTIVE, FALSE
	dome_set DOME_DATA_ATTEMPTED_CHALLENGE, TRUE
	special LoadPlayerParty
	special HealPlayerParty
	callnative UpdateFollowingPokemon
PokemonWorldTournamentLobby_EventScript_AskRecordBattle::
	dome_save 0
	playse SE_SAVE
	waitse
	call BattleFrontier_EventScript_GetCantRecordBattle
	goto_if_eq VAR_RESULT, TRUE, PokemonWorldTournamentLobby_EventScript_EndChallenge
	message PokemonWorldTournamentLobby_Text_RecordLastMatch
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, PokemonWorldTournamentLobby_EventScript_EndChallenge
	case 0, PokemonWorldTournamentLobby_EventScript_RecordBattle
	case MULTI_B_PRESSED, PokemonWorldTournamentLobby_EventScript_EndChallenge

PokemonWorldTournamentLobby_EventScript_RecordBattle::
	call BattleFrontier_EventScript_SaveBattle
PokemonWorldTournamentLobby_EventScript_EndChallenge::
	msgbox PokemonWorldTournamentLobby_Text_HopeToSeeYouAgain, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

PokemonWorldTournamentLobby_EventScript_ResumeChallenge::
	lockall
	msgbox PokemonWorldTournamentLobby_Text_WeveBeenWaitingForYou, MSGBOX_DEFAULT
	message PokemonWorldTournamentLobby_Text_OkayToSaveBeforeChallenge2
	waitmessage
	dome_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto PokemonWorldTournamentLobby_EventScript_EnterChallenge

PokemonWorldTournamentLobby_EventScript_SinglesAttendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_DOME
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	goto PokemonWorldTournamentLobby_EventScript_AttendantWelcome
	end

PokemonWorldTournamentLobby_EventScript_DoublesAttendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_DOME
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	goto PokemonWorldTournamentLobby_EventScript_AttendantWelcome
	end

PokemonWorldTournamentLobby_EventScript_AttendantWelcome::
	special SavePlayerParty
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, PokemonWorldTournamentLobby_EventScript_WelcomeSingles
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, PokemonWorldTournamentLobby_EventScript_WelcomeDoubles
PokemonWorldTournamentLobby_EventScript_AskTakeChallenge::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, PokemonWorldTournamentLobby_EventScript_TakeSinglesChallenge
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, PokemonWorldTournamentLobby_EventScript_TakeDoublesChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, PokemonWorldTournamentLobby_EventScript_TryEnterChallenge
	case 1, PokemonWorldTournamentLobby_EventScript_ExplainChallenge
	case 2, PokemonWorldTournamentLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, PokemonWorldTournamentLobby_EventScript_CancelChallenge

PokemonWorldTournamentLobby_EventScript_TryEnterChallenge::
	goto SE_Pwt_ChooseCup
	message PokemonWorldTournamentLobby_Text_WhichLevelMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, PokemonWorldTournamentLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, PokemonWorldTournamentLobby_EventScript_CancelChallenge
PokemonWorldTournamentLobby_EventScript_CheckEligible::
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, PokemonWorldTournamentLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox PokemonWorldTournamentLobby_Text_SelectThreeMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	callnative RemoveFollowingPokemon
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	choosepartyforbattlefrontier FRONTIER_PARTY_SIZE
	goto_if_eq VAR_RESULT, 0, PokemonWorldTournamentLobby_EventScript_LoadPartyCancelChallenge
	msgbox PokemonWorldTournamentLobby_Text_OkayToSaveBeforeChallenge, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, PokemonWorldTournamentLobby_EventScript_LoadPartyCancelChallenge
	case YES, PokemonWorldTournamentLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, PokemonWorldTournamentLobby_EventScript_LoadPartyCancelChallenge

PokemonWorldTournamentLobby_EventScript_SaveBeforeChallenge::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	dome_init
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto_if_eq VAR_RESULT, 0, PokemonWorldTournamentLobby_EventScript_CancelChallengeSaveFailed
	dome_inittrainers
PokemonWorldTournamentLobby_EventScript_EnterChallenge::
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	dome_settrainers
	msgbox PokemonWorldTournamentLobby_Text_ShowYouToBattleDome, MSGBOX_DEFAULT
	closemessage
	call PokemonWorldTournamentLobby_EventScript_WalkToDoor
	special HealPlayerParty
	warp MAP_POKEMON_WORLD_TOURNAMENT_CORRIDOR, 23, 6
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

PokemonWorldTournamentLobby_EventScript_ExplainChallenge::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, PokemonWorldTournamentLobby_EventScript_ExplainSinglesChallenge
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, PokemonWorldTournamentLobby_EventScript_ExplainDoublesChallenge
	goto PokemonWorldTournamentLobby_EventScript_AskTakeChallenge

PokemonWorldTournamentLobby_EventScript_NotEnoughValidMons::
	goto PokemonWorldTournamentLobby_EventScript_NotEnoughValidMonsLvOpen
	switch VAR_RESULT
	case FRONTIER_LVL_50, PokemonWorldTournamentLobby_EventScript_NotEnoughValidMonsLv50
	case FRONTIER_LVL_OPEN, PokemonWorldTournamentLobby_EventScript_NotEnoughValidMonsLvOpen

PokemonWorldTournamentLobby_EventScript_NotEnoughValidMonsLv50::
	msgbox PokemonWorldTournamentLobby_Text_NotEnoughValidMonsLv50, MSGBOX_DEFAULT
	call BattleFrontier_ShowCaughtBannedSpecies
	msgbox PokemonWorldTournamentLobby_Text_NotEnoughValidMonsEnd, MSGBOX_DEFAULT
	goto PokemonWorldTournamentLobby_EventScript_EndCancelChallenge

PokemonWorldTournamentLobby_EventScript_NotEnoughValidMonsLvOpen::
	msgbox PokemonWorldTournamentLobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
	call BattleFrontier_ShowCaughtBannedSpecies
	msgbox PokemonWorldTournamentLobby_Text_NotEnoughValidMonsEnd, MSGBOX_DEFAULT
	goto PokemonWorldTournamentLobby_EventScript_EndCancelChallenge

PokemonWorldTournamentLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto PokemonWorldTournamentLobby_EventScript_CancelChallenge

PokemonWorldTournamentLobby_EventScript_LoadPartyCancelChallenge::
	special LoadPlayerParty
	callnative UpdateFollowingPokemon
PokemonWorldTournamentLobby_EventScript_CancelChallenge::
	msgbox PokemonWorldTournamentLobby_Text_HopeToSeeYouAgain, MSGBOX_DEFAULT
PokemonWorldTournamentLobby_EventScript_EndCancelChallenge::
	release
	end

PokemonWorldTournamentLobby_EventScript_WalkToDoor::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, PokemonWorldTournamentLobby_EventScript_SinglesAttendantWalkToDoor
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, PokemonWorldTournamentLobby_EventScript_DoublesAttendantWalkToDoor
	applymovement LOCALID_PLAYER, PokemonWorldTournamentLobby_Movement_WalkToDoor
	waitmovement 0
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, PokemonWorldTournamentLobby_EventScript_OpenSinglesDoor
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, PokemonWorldTournamentLobby_EventScript_OpenDoublesDoor
	waitdooranim
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, PokemonWorldTournamentLobby_EventScript_SinglesAttendantEnterDoor
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, PokemonWorldTournamentLobby_EventScript_DoublesAttendantEnterDoor
	applymovement LOCALID_PLAYER, PokemonWorldTournamentLobby_Movement_PlayerEnterDoor
	waitmovement 0
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, PokemonWorldTournamentLobby_EventScript_CloseSinglesDoor
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, PokemonWorldTournamentLobby_EventScript_CloseDoublesDoor
	waitdooranim
	return

PokemonWorldTournamentLobby_EventScript_SinglesAttendantWalkToDoor::
	applymovement LOCALID_DOME_ATTENDANT_SINGLES, PokemonWorldTournamentLobby_Movement_WalkToDoor
	return

PokemonWorldTournamentLobby_EventScript_DoublesAttendantWalkToDoor::
	applymovement LOCALID_DOME_ATTENDANT_DOUBLES, PokemonWorldTournamentLobby_Movement_WalkToDoor
	return

PokemonWorldTournamentLobby_EventScript_SinglesAttendantEnterDoor::
	applymovement LOCALID_DOME_ATTENDANT_SINGLES, PokemonWorldTournamentLobby_Movement_AttendantEnterDoor
	return

PokemonWorldTournamentLobby_EventScript_DoublesAttendantEnterDoor::
	applymovement LOCALID_DOME_ATTENDANT_DOUBLES, PokemonWorldTournamentLobby_Movement_AttendantEnterDoor
	return

PokemonWorldTournamentLobby_EventScript_WelcomeSingles::
	msgbox PokemonWorldTournamentLobby_Text_WelcomeSingleBattle, MSGBOX_DEFAULT
	return

PokemonWorldTournamentLobby_EventScript_WelcomeDoubles::
	msgbox PokemonWorldTournamentLobby_Text_WelcomeDoubleBattle, MSGBOX_DEFAULT
	return

PokemonWorldTournamentLobby_EventScript_TakeSinglesChallenge::
	message PokemonWorldTournamentLobby_Text_TakeSinglesChallenge
	return

PokemonWorldTournamentLobby_EventScript_TakeDoublesChallenge::
	message PokemonWorldTournamentLobby_Text_TakeDoublesChallenge
	return

PokemonWorldTournamentLobby_EventScript_ExplainSinglesChallenge::
	msgbox PokemonWorldTournamentLobby_Text_ExplainSinglesChallenge, MSGBOX_DEFAULT
	msgbox SE_Text_PwtExplainCups, MSGBOX_DEFAULT
	return

PokemonWorldTournamentLobby_EventScript_ExplainDoublesChallenge::
	msgbox PokemonWorldTournamentLobby_Text_ExplainDoublesChallenge, MSGBOX_DEFAULT
	msgbox SE_Text_PwtExplainCups, MSGBOX_DEFAULT
	return

PokemonWorldTournamentLobby_EventScript_OpenSinglesDoor::
	opendoor 5, 4
	return

PokemonWorldTournamentLobby_EventScript_OpenDoublesDoor::
	opendoor 17, 4
	return

PokemonWorldTournamentLobby_EventScript_CloseSinglesDoor::
	closedoor 5, 4
	return

PokemonWorldTournamentLobby_EventScript_CloseDoublesDoor::
	closedoor 17, 4
	return

PokemonWorldTournamentLobby_Movement_WalkToDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

PokemonWorldTournamentLobby_Movement_AttendantEnterDoor:
	walk_up
	set_invisible
	step_end

PokemonWorldTournamentLobby_Movement_PlayerEnterDoor:
	walk_up
	walk_up
	set_invisible
	step_end

PokemonWorldTournamentLobby_EventScript_ShowSinglesResults::
	lockall
	frontier_results FRONTIER_FACILITY_DOME, FRONTIER_MODE_SINGLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

PokemonWorldTournamentLobby_EventScript_ShowDoublesResults::
	lockall
	frontier_results FRONTIER_FACILITY_DOME, FRONTIER_MODE_DOUBLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

PokemonWorldTournamentLobby_EventScript_ShowPrevTourneyTree::
	dome_get DOME_DATA_PREV_TOURNEY_TYPE
	call_if_eq VAR_RESULT, 0, PokemonWorldTournamentLobby_EventScript_PrevTourneyResultsSinglesLv50
	call_if_eq VAR_RESULT, 1, PokemonWorldTournamentLobby_EventScript_PrevTourneyResultsDoublesLv50
	call_if_eq VAR_RESULT, 2, PokemonWorldTournamentLobby_EventScript_PrevTourneyResultsSinglesLvOpen
	call_if_eq VAR_RESULT, 3, PokemonWorldTournamentLobby_EventScript_PrevTourneyResultsDoublesLvOpen
	fadescreen FADE_TO_BLACK
	dome_showprevtourneytree
	waitstate
	end

PokemonWorldTournamentLobby_EventScript_PrevTourneyResultsSinglesLv50::
	msgbox PokemonWorldTournamentLobby_Text_PrevTourneyResultsSinglesLv50, MSGBOX_SIGN
	return

PokemonWorldTournamentLobby_EventScript_PrevTourneyResultsDoublesLv50::
	msgbox PokemonWorldTournamentLobby_Text_PrevTourneyResultsDoublesLv50, MSGBOX_SIGN
	return

PokemonWorldTournamentLobby_EventScript_PrevTourneyResultsSinglesLvOpen::
	msgbox PokemonWorldTournamentLobby_Text_PrevTourneyResultsSinglesLvOpen, MSGBOX_SIGN
	return

PokemonWorldTournamentLobby_EventScript_PrevTourneyResultsDoublesLvOpen::
	msgbox PokemonWorldTournamentLobby_Text_PrevTourneyResultsDoublesLvOpen, MSGBOX_SIGN
	return

PokemonWorldTournamentLobby_EventScript_Maniac::
	dome_getwinnersname
	msgbox PokemonWorldTournamentLobby_Text_LastWinnerWasTough, MSGBOX_NPC
	end

PokemonWorldTournamentLobby_EventScript_Lass::
	msgbox PokemonWorldTournamentLobby_Text_WinnersGainReputation, MSGBOX_NPC
	end

PokemonWorldTournamentLobby_EventScript_FatMan::
	msgbox PokemonWorldTournamentLobby_Text_TrashedInFirstRound, MSGBOX_NPC
	end

PokemonWorldTournamentLobby_EventScript_Man::
	msgbox PokemonWorldTournamentLobby_Text_NeedToCheckOpponentCarefully, MSGBOX_NPC
	end

@ A few OutsideWest event scripts are inserted here instead, two of which are unused
PokemonWorldTournamentLobby_OutsideWest_EventScript_Man3::
	msgbox PokemonWorldTournamentLobby_OutsideWest_Text_LongDreamedAboutBattleFrontier, MSGBOX_NPC
	end

@ Unused
PokemonWorldTournamentLobby_OutsideWest_EventScript_BattleDomeSign2::
	msgbox PokemonWorldTournamentLobby_OutsideWest_Text_BattleDomeSign2, MSGBOX_NPC
	end

@ Unused
PokemonWorldTournamentLobby_OutsideWest_EventScript_UnderConstructionSign::
	msgbox PokemonWorldTournamentLobby_OutsideWest_Text_QuestionMarkUnderConstruction, MSGBOX_NPC
	end

PokemonWorldTournamentLobby_EventScript_RulesBoard::
	lockall
	msgbox PokemonWorldTournamentLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto PokemonWorldTournamentLobby_EventScript_ReadRulesBoard
	end

PokemonWorldTournamentLobby_EventScript_ReadRulesBoard::
	message PokemonWorldTournamentLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 17, 4, MULTI_BATTLE_DOME_RULES, FALSE
	switch VAR_RESULT
	case 0, PokemonWorldTournamentLobby_EventScript_RulesMatchup
	case 1, PokemonWorldTournamentLobby_EventScript_RulesTourneyTree
	case 2, PokemonWorldTournamentLobby_EventScript_RulesDoubleKO
	case 3, PokemonWorldTournamentLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, PokemonWorldTournamentLobby_EventScript_ExitRules
	end

PokemonWorldTournamentLobby_EventScript_RulesMatchup::
	msgbox PokemonWorldTournamentLobby_Text_ExplainMatchupRules, MSGBOX_DEFAULT
	goto PokemonWorldTournamentLobby_EventScript_ReadRulesBoard
	end

PokemonWorldTournamentLobby_EventScript_RulesTourneyTree::
	msgbox PokemonWorldTournamentLobby_Text_ExplainTourneyTree, MSGBOX_DEFAULT
	goto PokemonWorldTournamentLobby_EventScript_ReadRulesBoard
	end

PokemonWorldTournamentLobby_EventScript_RulesDoubleKO::
	msgbox PokemonWorldTournamentLobby_Text_ExplainDoubleKORules, MSGBOX_DEFAULT
	goto PokemonWorldTournamentLobby_EventScript_ReadRulesBoard
	end

PokemonWorldTournamentLobby_EventScript_ExitRules::
	releaseall
	end

PokemonWorldTournamentLobby_Text_WelcomeSingleBattle:
	.string "Where the strategies of TRAINERS\n"
	.string "are put to the test!\p"
	.string "Welcome to the PWT!\p"
	.string "I am your guide to the SINGLE BATTLE\n"
	.string "Tournament.$"

PokemonWorldTournamentLobby_Text_TakeSinglesChallenge:
	.string "Would you like to challenge\n"
	.string "the SINGLE BATTLE Tournament?$"

PokemonWorldTournamentLobby_Text_HopeToSeeYouAgain:
	.string "We hope to see you again.$"

PokemonWorldTournamentLobby_Text_ExplainSinglesChallenge:
	.string "The SINGLE BATTLE Tournament\n"
	.string "is exactly as the name suggests--\l"
	.string "a tournament of SINGLE BATTLES.\p"
	.string "All participating TRAINERS must\n"
	.string "enter three POKéMON each.\p"
	.string "In each battle, one of the three\n"
	.string "POKéMON must be held in reserve.\p"
	.string "The other two POKéMON can battle\n"
	.string "one at a time.\p"
	.string "Choose the two battling POKéMON after\n"
	.string "examining the opponent's trio.\p"
	.string "You win the tournament by defeating\n"
	.string "four TRAINERS.\p"
	.string "Battle Points are awarded to\n"
	.string "the tournament winner.\p"
	.string "If you want to interrupt your\n"
	.string "tournament, please save the game.\p"
	.string "If you don't save before interrupting,\n"
	.string "you will be disqualified.$"

PokemonWorldTournamentLobby_Text_OkayToSaveBeforeChallenge:
	.string "Before I show you to the PWT,\n"
	.string "I must save the data. Is that okay?$"

PokemonWorldTournamentLobby_Text_WhichLevelMode:
	.string "The tournament offers two levels\n"
	.string "of challenge, Level 50 and Open Level.\l"
	.string "Which is your choice?$"

PokemonWorldTournamentLobby_Text_SelectThreeMons:
	.string "Now select the three POKéMON that\n"
	.string "you wish to enter, please.$"

PokemonWorldTournamentLobby_Text_NotEnoughValidMonsLvOpen:
	.string "Excuse me!\p"
	.string "You don't have three eligible POKéMON.\p"
	.string "Also, the POKéMON must be holding\n"
	.string "different kinds of items.\p"
	.string "EGGS{STR_VAR_1}.$"

PokemonWorldTournamentLobby_Text_NotEnoughValidMonsEnd:
	.string "Please come see me when you are ready.$"

PokemonWorldTournamentLobby_Text_NotEnoughValidMonsLv50:
	.string "Excuse me!\p"
	.string "You don't have three eligible POKéMON.\p"
	.string "You must have three different POKéMON\n"
	.string "of Level 50 or less to enter.\p"
	.string "They also must be holding different\n"
	.string "kinds of items.\p"
	.string "EGGS{STR_VAR_1}.$"

PokemonWorldTournamentLobby_Text_ShowYouToBattleDome:
	.string "I will now show you to\n"
	.string "the PWT.$"

PokemonWorldTournamentLobby_Text_DidntSaveBeforeQuitting:
	.string "Excuse me!\p"
	.string "You didn't save before you quit your\n"
	.string "challenge last time.\p"
	.string "Because of that, your challenge so far\n"
	.string "has been disqualified. Sorry!$"

PokemonWorldTournamentLobby_Text_CongratsForWinningTourney:
	.string "Congratulations for winning\n"
	.string "your Battle Tournament!$"

@ Unused
PokemonWorldTournamentLobby_Text_HereIsYourPrize:
	.string "Here is your prize for your Battle\n"
	.string "Tournament victory.$"

@ Used by Verdanturf Tent
PokemonWorldTournamentLobby_Text_ReceivedPrize:
	.string "{PLAYER} received the prize\n"
	.string "{STR_VAR_1}.$"

@ Unused
PokemonWorldTournamentLobby_Text_BagFullMakeRoom:
	.string "Oh, your BAG appears to be full.\p"
	.string "Please make room in your BAG, then come\n"
	.string "see me.$"

PokemonWorldTournamentLobby_Text_ThankYouForPlaying:
	.string "Thank you for playing!$"

PokemonWorldTournamentLobby_Text_RecordWillBeSaved:
	.string "Your record will be saved.\n"
	.string "Please wait.$"

PokemonWorldTournamentLobby_Text_WeveBeenWaitingForYou:
	.string "We've been waiting for you!$"

PokemonWorldTournamentLobby_Text_OkayToSaveBeforeChallenge2:
	.string "Before I show you to the PWT,\n"
	.string "I must save the data. Is that okay?$"

PokemonWorldTournamentLobby_Text_WelcomeDoubleBattle:
	.string "Where the strategies of TRAINERS\n"
	.string "are put to the test!\p"
	.string "Welcome to the PWT!\p"
	.string "I am your guide to the DOUBLE BATTLE\n"
	.string "Tournament.$"

PokemonWorldTournamentLobby_Text_TakeDoublesChallenge:
	.string "Would you like to challenge\n"
	.string "the DOUBLE BATTLE Tournament?$"

PokemonWorldTournamentLobby_Text_ExplainDoublesChallenge:
	.string "The DOUBLE BATTLE Tournament\n"
	.string "is exactly as the name suggests--\l"
	.string "a tournament of DOUBLE BATTLES.\p"
	.string "All participating TRAINERS must\n"
	.string "enter three POKéMON each.\p"
	.string "In each battle, one of the three\n"
	.string "POKéMON must be held in reserve.\p"
	.string "The remaining two POKéMON must take\n"
	.string "part in a DOUBLE BATTLE.\p"
	.string "Choose the two battling POKéMON after\n"
	.string "examining the opponent's trio.\p"
	.string "You win the tournament by defeating\n"
	.string "four TRAINERS.\p"
	.string "Battle Points are awarded to\n"
	.string "the tournament winner.\p"
	.string "If you want to interrupt your\n"
	.string "tournament, please save the game.\p"
	.string "If you don't save before interrupting,\n"
	.string "you will be disqualified.$"

PokemonWorldTournamentLobby_Text_PrevTourneyResultsSinglesLv50:
	.string "They're the results of the last\n"
	.string "Level 50 SINGLE BATTLE Tournament.$"

PokemonWorldTournamentLobby_Text_PrevTourneyResultsDoublesLv50:
	.string "They're the results of the last\n"
	.string "Level 50 DOUBLE BATTLE Tournament.$"

PokemonWorldTournamentLobby_Text_PrevTourneyResultsSinglesLvOpen:
	.string "They're the results of the last\n"
	.string "Open Level SINGLE BATTLE Tournament.$"

PokemonWorldTournamentLobby_Text_PrevTourneyResultsDoublesLvOpen:
	.string "They're the results of the last\n"
	.string "Open Level DOUBLE BATTLE Tournament.$"

PokemonWorldTournamentLobby_Text_LastWinnerWasTough:
	.string "Did you see it?\n"
	.string "The last Battle Tournament?\p"
	.string "The winner, {STR_VAR_1}, was seriously\n"
	.string "tough.\p"
	.string "You should check out the results\n"
	.string "on the monitor beside the PC.$"

PokemonWorldTournamentLobby_OutsideWest_Text_LongDreamedAboutBattleFrontier:
	.string "The BATTLE FRONTIER…\n"
	.string "I've long dreamed about a place like it.$"

@ Functionally unused
PokemonWorldTournamentLobby_OutsideWest_Text_BattleDomeSign2:
	.string "The PWT\n"
	.string "Become the Unbeatable Superstar!$"

@ Functionally unused
PokemonWorldTournamentLobby_OutsideWest_Text_QuestionMarkUnderConstruction:
	.string "The ??????\n"
	.string "Under Construction!$"

PokemonWorldTournamentLobby_Text_WinnersGainReputation:
	.string "When a TRAINER chains tournament\n"
	.string "wins at the PWT, he or she\l"
	.string "gains a reputation as a star.\p"
	.string "Tough TRAINERS are drawn by that\n"
	.string "reputation to the PWT.\p"
	.string "A true superstar is a TRAINER who\n"
	.string "can keep winning tournaments.$"

PokemonWorldTournamentLobby_Text_TrashedInFirstRound:
	.string "I ran into one of the tournament\n"
	.string "favorites in the very first round.\p"
	.string "Of course I got trashed…$"

PokemonWorldTournamentLobby_Text_NeedToCheckOpponentCarefully:
	.string "I would've won if I'd kept this POKéMON\n"
	.string "held in reserve.\p"
	.string "You need to check your opponent's\n"
	.string "POKéMON carefully before choosing\l"
	.string "your battling POKéMON.$"

PokemonWorldTournamentLobby_Text_CongratsDefeatedTucker:
	.string "Congratulations!\p"
	.string "You defeated the DOME ACE and won\n"
	.string "the Battle Tournament!$"

PokemonWorldTournamentLobby_Text_AwardTheseBattlePoints:
	.string "In recognition of your strategy--\n"
	.string "a thing of beauty it was, too--\l"
	.string "we award you these Battle Point(s)!$"

PokemonWorldTournamentLobby_Text_RecordLastMatch:
	.string "Would you like to record your\n"
	.string "last PWT match on your\l"
	.string "FRONTIER PASS?$"

PokemonWorldTournamentLobby_Text_RulesAreListed:
	.string "The Battle Tournament rules\n"
	.string "are listed.$"

PokemonWorldTournamentLobby_Text_ReadWhichHeading:
	.string "Which heading do you want to read?$"

PokemonWorldTournamentLobby_Text_ExplainMatchupRules:
	.string "The tournament matchups are drawn up\n"
	.string "based on the toughness of POKéMON\l"
	.string "held by TRAINERS.\p"
	.string "The matchups avoid having tough\n"
	.string "TRAINERS face each other right away.$"

PokemonWorldTournamentLobby_Text_ExplainTourneyTree:
	.string "The tournament chart, or as we call it,\n"
	.string "the “Tree,” is available for viewing\l"
	.string "in the Waiting Room from any guide.\p"
	.string "The Tournament Tree will provide\n"
	.string "several kinds of data.\p"
	.string "The data on view includes the previous\n"
	.string "tournament's results, the POKéMON held\l"
	.string "by TRAINERS, and the battle styles of\l"
	.string "TRAINERS.$"

PokemonWorldTournamentLobby_Text_ExplainDoubleKORules:
	.string "If battling POKéMON faint at the same\n"
	.string "time--a double KO--in a tournament\l"
	.string "match, the REFEREES will review\l"
	.string "the match and declare the winner.$"
