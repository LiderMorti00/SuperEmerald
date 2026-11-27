@ Super Emerald: Pokemon World Tournament. A copy of the Battle Dome scripts (the PWT runs on the
@ Dome engine) with its own labels, warps and texts; nothing here is shared with Hoenn's Dome.
@ PWT-only parts: data/scripts/se_pwt.inc and src/se_pwt.c.

PokemonWorldTournamentPreBattleRoom_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PokemonWorldTournamentPreBattleRoom_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PokemonWorldTournamentPreBattleRoom_OnWarp
	.byte 0

PokemonWorldTournamentPreBattleRoom_OnWarp:
	map_script_2 VAR_TEMP_1, 0, PokemonWorldTournamentPreBattleRoom_EventScript_TurnPlayerNorth
	.2byte 0

PokemonWorldTournamentPreBattleRoom_EventScript_TurnPlayerNorth::
	setvar VAR_TEMP_1, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

PokemonWorldTournamentPreBattleRoom_OnFrame:
	map_script_2 VAR_TEMP_0, 0, PokemonWorldTournamentPreBattleRoom_EventScript_EnterRoom
	.2byte 0

PokemonWorldTournamentPreBattleRoom_EventScript_EnterRoom::
	@ Super Emerald: back from a battle the player arrives at (5, 3), from the corridor at (5, 7).
	@ (VAR_0x8006 can be changed by the warp, so the room didn't tell them apart.)
	getplayerxy VAR_TEMP_2, VAR_TEMP_3
	goto_if_eq VAR_TEMP_3, 3, PokemonWorldTournamentPreBattleRoom_EventScript_ReturnFromBattle
	frontier_set FRONTIER_DATA_RECORD_DISABLED, TRUE
	setvar VAR_TEMP_0, 1
	applymovement LOCALID_PLAYER, PokemonWorldTournamentPreBattleRoom_Movement_PlayerEnter
	waitmovement 0
	lockall
PokemonWorldTournamentPreBattleRoom_EventScript_AskReadyForNextRound::
	call PokemonWorldTournamentPreBattleRoom_EventScript_ReadyForNextRoundMessage
	waitmessage
	switch VAR_RESULT  @ No case?
	call BattleFrontier_EventScript_GetCantRecordBattle
	goto_if_eq VAR_RESULT, TRUE, PokemonWorldTournamentPreBattleRoom_EventScript_AskReadyForNextRoundNoRecord
	multichoice 16, 0, MULTI_TOURNEY_WITH_RECORD, TRUE
	switch VAR_RESULT
	case 0, PokemonWorldTournamentPreBattleRoom_EventScript_ShowOpponentInfo
	case 1, PokemonWorldTournamentPreBattleRoom_EventScript_ShowTourneyTree
	case 2, PokemonWorldTournamentPreBattleRoom_EventScript_ContinueChallenge
	case 3, PokemonWorldTournamentPreBattleRoom_EventScript_AskRecordBattle
	case 4, PokemonWorldTournamentPreBattleRoom_EventScript_AskPauseChallenge
	case 5, PokemonWorldTournamentPreBattleRoom_EventScript_AskRetireChallenge
	case MULTI_B_PRESSED, PokemonWorldTournamentPreBattleRoom_EventScript_AskReadyForNextRound

PokemonWorldTournamentPreBattleRoom_EventScript_AskReadyForNextRoundNoRecord::
	multichoice 16, 2, MULTI_TOURNEY_NO_RECORD, TRUE
	switch VAR_RESULT
	case 0, PokemonWorldTournamentPreBattleRoom_EventScript_ShowOpponentInfo
	case 1, PokemonWorldTournamentPreBattleRoom_EventScript_ShowTourneyTree
	case 2, PokemonWorldTournamentPreBattleRoom_EventScript_ContinueChallenge
	case 3, PokemonWorldTournamentPreBattleRoom_EventScript_AskPauseChallenge
	case 4, PokemonWorldTournamentPreBattleRoom_EventScript_AskRetireChallenge
	case MULTI_B_PRESSED, PokemonWorldTournamentPreBattleRoom_EventScript_AskReadyForNextRound

PokemonWorldTournamentPreBattleRoom_EventScript_AskRecordBattle::
	message PokemonWorldTournamentPreBattleRoom_Text_RecordLastMatch
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, PokemonWorldTournamentPreBattleRoom_EventScript_AskReadyForNextRound
	case 0, PokemonWorldTournamentPreBattleRoom_EventScript_RecordBattle
	case MULTI_B_PRESSED, PokemonWorldTournamentPreBattleRoom_EventScript_AskReadyForNextRound

PokemonWorldTournamentPreBattleRoom_EventScript_RecordBattle::
	call BattleFrontier_EventScript_SaveBattle
	goto PokemonWorldTournamentPreBattleRoom_EventScript_AskReadyForNextRound

PokemonWorldTournamentPreBattleRoom_EventScript_AskPauseChallenge::
	msgbox PokemonWorldTournamentPreBattleRoom_Text_SaveAndQuitGame, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, PokemonWorldTournamentPreBattleRoom_EventScript_AskReadyForNextRound
	case YES, PokemonWorldTournamentPreBattleRoom_EventScript_PauseChallenge
	case MULTI_B_PRESSED, PokemonWorldTournamentPreBattleRoom_EventScript_AskReadyForNextRound

PokemonWorldTournamentPreBattleRoom_EventScript_AskRetireChallenge::
	message PokemonWorldTournamentPreBattleRoom_Text_RetireYourChallenge
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, PokemonWorldTournamentPreBattleRoom_EventScript_AskReadyForNextRound
	case 0, PokemonWorldTournamentPreBattleRoom_EventScript_RetireChallenge
	case MULTI_B_PRESSED, PokemonWorldTournamentPreBattleRoom_EventScript_AskReadyForNextRound

PokemonWorldTournamentPreBattleRoom_EventScript_RetireChallenge::
	dome_resolvewinners DOME_PLAYER_RETIRED
	goto PokemonWorldTournamentRoom_EventScript_WarpToLobbyLost

PokemonWorldTournamentPreBattleRoom_EventScript_PauseChallenge::
	message PokemonWorldTournamentPreBattleRoom_Text_SavingDataPleaseWait
	waitmessage
	dome_save CHALLENGE_STATUS_PAUSED
	playse SE_SAVE
	waitse
	fadescreen FADE_TO_BLACK
	frontier_reset
	end

PokemonWorldTournamentPreBattleRoom_EventScript_ShowOpponentInfo::
	msgbox PokemonWorldTournamentPreBattleRoom_Text_PlayersNextOpponentIsTrainer, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	dome_showopponentinfo
	waitstate
	goto PokemonWorldTournamentPreBattleRoom_EventScript_AskReadyForNextRound

PokemonWorldTournamentPreBattleRoom_EventScript_ShowTourneyTree::
	call PokemonWorldTournamentPreBattleRoom_EventScript_ShowRoundMessage
	fadescreen FADE_TO_BLACK
	dome_showtourneytree
	waitstate
	goto PokemonWorldTournamentPreBattleRoom_EventScript_AskReadyForNextRound

PokemonWorldTournamentPreBattleRoom_EventScript_ShowRoundMessage::
	frontier_get FRONTIER_DATA_BATTLE_NUM
	switch VAR_RESULT
	case DOME_ROUND1, PokemonWorldTournamentPreBattleRoom_EventScript_TourneyInRound1
	case DOME_ROUND2, PokemonWorldTournamentPreBattleRoom_EventScript_TourneyInRound2
	case DOME_SEMIFINAL, PokemonWorldTournamentPreBattleRoom_EventScript_TourneyInSemifinals
	case DOME_FINAL, PokemonWorldTournamentPreBattleRoom_EventScript_TourneyInFinals
	return

PokemonWorldTournamentPreBattleRoom_EventScript_TourneyInRound1::
	msgbox PokemonWorldTournamentPreBattleRoom_Text_TourneyInRound1, MSGBOX_DEFAULT
	return

PokemonWorldTournamentPreBattleRoom_EventScript_TourneyInRound2::
	msgbox PokemonWorldTournamentPreBattleRoom_Text_TourneyInRound2, MSGBOX_DEFAULT
	return

PokemonWorldTournamentPreBattleRoom_EventScript_TourneyInSemifinals::
	msgbox PokemonWorldTournamentPreBattleRoom_Text_TourneyInSemifinals, MSGBOX_DEFAULT
	return

PokemonWorldTournamentPreBattleRoom_EventScript_TourneyInFinals::
	msgbox PokemonWorldTournamentPreBattleRoom_Text_TourneyInFinals, MSGBOX_DEFAULT
	return

PokemonWorldTournamentPreBattleRoom_EventScript_ContinueChallenge::
	@ Super Emerald: 6 against 6, the whole party battles (no choosing two)
	frontier_resetsketch
	dome_setopponent
	msgbox PokemonWorldTournamentPreBattleRoom_Text_RightThisWay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DOME_PRE_BATTLE_ATTENDANT, PokemonWorldTournamentPreBattleRoom_Movement_AttendantMoveAside
	waitmovement 0
	applymovement LOCALID_PLAYER, PokemonWorldTournamentPreBattleRoom_Movement_PlayerWalkToDoor
	waitmovement 0
	opendoor 5, 1
	waitdooranim
	applymovement LOCALID_PLAYER, PokemonWorldTournamentPreBattleRoom_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 5, 1
	waitdooranim
	warp MAP_POKEMON_WORLD_TOURNAMENT_ROOM, 9, 5
	setvar VAR_TEMP_0, 0
	waitstate
	end

PokemonWorldTournamentPreBattleRoom_EventScript_ReadyForNextRoundMessage::
	frontier_get FRONTIER_DATA_BATTLE_NUM
	switch VAR_RESULT
	case DOME_ROUND1, PokemonWorldTournamentPreBattleRoom_EventScript_ReadyForRound1
	case DOME_ROUND2, PokemonWorldTournamentPreBattleRoom_EventScript_ReadyForRound2
	case DOME_SEMIFINAL, PokemonWorldTournamentPreBattleRoom_EventScript_ReadyForSemifinals
	case DOME_FINAL, PokemonWorldTournamentPreBattleRoom_EventScript_ReadyForFinals
	return

PokemonWorldTournamentPreBattleRoom_EventScript_ReadyForRound1::
	message PokemonWorldTournamentPreBattleRoom_Text_ReadyForRound1
	return

PokemonWorldTournamentPreBattleRoom_EventScript_ReadyForRound2::
	message PokemonWorldTournamentPreBattleRoom_Text_ReadyForRound2
	return


PokemonWorldTournamentPreBattleRoom_EventScript_ReadyForSemifinals::
	message PokemonWorldTournamentPreBattleRoom_Text_ReadyForSemifinals
	return

PokemonWorldTournamentPreBattleRoom_EventScript_ReadyForFinals::
	frontier_getbrainstatus
	switch VAR_RESULT
	case FRONTIER_BRAIN_SILVER, PokemonWorldTournamentPreBattleRoom_EventScript_ReadyForTuckerSilver
	case FRONTIER_BRAIN_GOLD, PokemonWorldTournamentPreBattleRoom_EventScript_ReadyForTuckerGold
	case FRONTIER_BRAIN_STREAK, PokemonWorldTournamentPreBattleRoom_EventScript_ReadyForTuckerSilver
	case FRONTIER_BRAIN_STREAK_LONG, PokemonWorldTournamentPreBattleRoom_EventScript_ReadyForTuckerGold
	message PokemonWorldTournamentPreBattleRoom_Text_ReadyForFinals
	return

PokemonWorldTournamentPreBattleRoom_EventScript_ReadyForTuckerSilver::
	goto_if_set FLAG_TEMP_1, PokemonWorldTournamentPreBattleRoom_EventScript_ReadyForTuckerSilverShort
	msgbox PokemonWorldTournamentPreBattleRoom_Text_ReadyForTuckerSilver, MSGBOX_DEFAULT
	setflag FLAG_TEMP_1
	return

PokemonWorldTournamentPreBattleRoom_EventScript_ReadyForTuckerGold::
	goto_if_set FLAG_TEMP_1, PokemonWorldTournamentPreBattleRoom_EventScript_ReadyForTuckerGoldShort
	msgbox PokemonWorldTournamentPreBattleRoom_Text_ReadyForTuckerGold, MSGBOX_DEFAULT
	setflag FLAG_TEMP_1
	return

PokemonWorldTournamentPreBattleRoom_EventScript_ReadyForTuckerSilverShort::
	msgbox PokemonWorldTournamentPreBattleRoom_Text_ReadyForTuckerSilverShort, MSGBOX_DEFAULT
	return

PokemonWorldTournamentPreBattleRoom_EventScript_ReadyForTuckerGoldShort::
	msgbox PokemonWorldTournamentPreBattleRoom_Text_ReadyForTuckerGoldShort, MSGBOX_DEFAULT
	return

PokemonWorldTournamentPreBattleRoom_EventScript_ReturnFromBattle::
	setvar VAR_TEMP_0, 1
	msgbox PokemonWorldTournamentPreBattleRoom_Text_RestoreMonsToFullHealth, MSGBOX_DEFAULT
	special LoadPlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
	call PokemonWorldTournamentPreBattleRoom_EventScript_RoundCompleteMessage
	fadescreen FADE_TO_BLACK
	dome_showstatictourneytree
	waitstate
	goto PokemonWorldTournamentPreBattleRoom_EventScript_AskReadyForNextRound

PokemonWorldTournamentPreBattleRoom_EventScript_RoundCompleteMessage::
	frontier_get FRONTIER_DATA_BATTLE_NUM
	switch VAR_RESULT
	case DOME_ROUND2, PokemonWorldTournamentPreBattleRoom_EventScript_Round1Complete
	case DOME_SEMIFINAL, PokemonWorldTournamentPreBattleRoom_EventScript_Round2Complete
	case DOME_FINAL, PokemonWorldTournamentPreBattleRoom_EventScript_SemifinalsComplete
	return

PokemonWorldTournamentPreBattleRoom_EventScript_Round1Complete::
	special SE_PwtIsEightTrainerTourney
	goto_if_eq VAR_RESULT, TRUE, PokemonWorldTournamentPreBattleRoom_EventScript_NoRoundCompleteMessage
	msgbox PokemonWorldTournamentPreBattleRoom_Text_Round1Complete, MSGBOX_DEFAULT
	return

PokemonWorldTournamentPreBattleRoom_EventScript_Round2Complete::
	msgbox PokemonWorldTournamentPreBattleRoom_Text_Round2Complete, MSGBOX_DEFAULT
	return

PokemonWorldTournamentPreBattleRoom_EventScript_NoRoundCompleteMessage::
	return

PokemonWorldTournamentPreBattleRoom_EventScript_SemifinalsComplete::
	msgbox PokemonWorldTournamentPreBattleRoom_Text_SemifinalsComplete, MSGBOX_DEFAULT
	return

PokemonWorldTournamentPreBattleRoom_Movement_AttendantMoveAside:
	walk_right
	face_left
	step_end

PokemonWorldTournamentPreBattleRoom_Movement_PlayerEnter:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

PokemonWorldTournamentPreBattleRoom_Movement_PlayerWalkToDoor:
	walk_up
	step_end

PokemonWorldTournamentPreBattleRoom_Movement_PlayerEnterDoor:
	walk_up
	set_invisible
	step_end

PokemonWorldTournamentPreBattleRoom_Text_ReadyForRound1:
	.string "Your round-of-16 match is next.\n"
	.string "Are you ready?$"

PokemonWorldTournamentPreBattleRoom_Text_ReadyForRound2:
	.string "Your quarterfinal match is next.\n"
	.string "Are you ready?$"

PokemonWorldTournamentPreBattleRoom_Text_ReadyForSemifinals:
	.string "Your semifinal match is next.\n"
	.string "Are you ready?$"

PokemonWorldTournamentPreBattleRoom_Text_ReadyForFinals:
	.string "Your final match is next.\n"
	.string "Are you ready?$"

PokemonWorldTournamentPreBattleRoom_Text_RightThisWay:
	.string "Right this way, please.$"

PokemonWorldTournamentPreBattleRoom_Text_RestoreMonsToFullHealth:
	.string "Thank you for competing!\p"
	.string "I'll restore your POKéMON to\n"
	.string "full health.$"

PokemonWorldTournamentPreBattleRoom_Text_Round1Complete:
	.string "All round-of-16 matches have been\n"
	.string "completed.\p"
	.string "These are the teams that advanced!$"

PokemonWorldTournamentPreBattleRoom_Text_Round2Complete:
	.string "All quarterfinal matches have been\n"
	.string "completed.\p"
	.string "These are the teams that advanced!$"

PokemonWorldTournamentPreBattleRoom_Text_SemifinalsComplete:
	.string "All semifinal matches have been\n"
	.string "completed.\p"
	.string "These are the teams that advanced!$"

@ Unused
PokemonWorldTournamentPreBattleRoom_Text_CongratsReadyForRound2:
	.string "Congratulations for getting through\n"
	.string "the 1st round.\p"
	.string "The 2nd round is next.\n"
	.string "Are you ready?$"

@ Unused
PokemonWorldTournamentPreBattleRoom_Text_CongratsReadyForSemifinals:
	.string "Congratulations for advancing\n"
	.string "to the semifinals.\p"
	.string "The best four teams meet in this round.\n"
	.string "Are you ready?$"

@ Unused
PokemonWorldTournamentPreBattleRoom_Text_CongratsReadyForFinals:
	.string "Congratulations for advancing\n"
	.string "to the final match.\p"
	.string "You're one win from the championship.\n"
	.string "Are you ready?$"

PokemonWorldTournamentPreBattleRoom_Text_PlayersNextOpponentIsTrainer:
	.string "{PLAYER}'s next opponent\n"
	.string "is this TRAINER.$"

PokemonWorldTournamentPreBattleRoom_Text_TourneyInRound1:
	.string "The tournament is in the round of 16.$"

PokemonWorldTournamentPreBattleRoom_Text_TourneyInRound2:
	.string "The tournament is in the quarterfinals.$"

PokemonWorldTournamentPreBattleRoom_Text_TourneyInSemifinals:
	.string "The tournament is in the semifinals.$"

PokemonWorldTournamentPreBattleRoom_Text_TourneyInFinals:
	.string "The tournament is up to the final.$"

PokemonWorldTournamentPreBattleRoom_Text_SaveAndQuitGame:
	.string "Would you like to save and\n"
	.string "quit the game?$"

PokemonWorldTournamentPreBattleRoom_Text_RetireYourChallenge:
	.string "Would you like to retire from your\n"
	.string "Battle Tournament challenge?$"

PokemonWorldTournamentPreBattleRoom_Text_SavingDataPleaseWait:
	.string "I am saving your data.\n"
	.string "Please wait.$"

PokemonWorldTournamentPreBattleRoom_Text_RecordLastMatch:
	.string "Should I record your last match\n"
	.string "on your FRONTIER PASS?$"

PokemonWorldTournamentPreBattleRoom_Text_ReadyForTuckerSilver:
	.string "Congratulations for advancing\n"
	.string "to the final match.\p"
	.string "For the final match, you will challenge\n"
	.string "the DOME ACE TUCKER.\p"
	.string "Are you ready?$"

@ Identical to ReadyForTuckerSilver
PokemonWorldTournamentPreBattleRoom_Text_ReadyForTuckerGold:
	.string "Congratulations for advancing\n"
	.string "to the final match.\p"
	.string "For the final match, you will challenge\n"
	.string "the DOME ACE TUCKER.\p"
	.string "Are you ready?$"

PokemonWorldTournamentPreBattleRoom_Text_ReadyForTuckerSilverShort:
	.string "Your final battle against TUCKER is\n"
	.string "next. Are you ready?$"

@ Identical again
PokemonWorldTournamentPreBattleRoom_Text_ReadyForTuckerGoldShort:
	.string "Your final battle against TUCKER is\n"
	.string "next. Are you ready?$"


