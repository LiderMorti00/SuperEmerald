PokemonLeague_HallOfFame_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PokemonLeague_HallOfFame_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PokemonLeague_HallOfFame_OnWarp
	.byte 0

PokemonLeague_HallOfFame_OnWarp::
	map_script_2 VAR_TEMP_1, 0, PokemonLeague_HallOfFame_EventScript_TurnPlayerNorth
	.2byte 0

PokemonLeague_HallOfFame_EventScript_TurnPlayerNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

PokemonLeague_HallOfFame_OnFrame::
	map_script_2 VAR_TEMP_1, 0, PokemonLeague_HallOfFame_EventScript_EnterRoom
	.2byte 0

PokemonLeague_HallOfFame_EventScript_LanceCongratulations::
	msgbox PokemonLeague_HallOfFame_Text_OakCongratulations
	return

PokemonLeague_HallOfFame_EventScript_LanceCongratulationsAgain::
	msgbox PokemonLeague_HallOfFame_Text_LanceCongratulationsAgain
	return

PokemonLeague_HallOfFame_Text_LanceCongratulationsAgain::
	.string "LANCE: Once again, {PLAYER}, your name\n"
	.string "joins the HALL OF FAME.\p"
	.string "This time, you earned all sixteen\n"
	.string "BADGES of JOHTO and KANTO first.\p"
	.string "You and your POKéMON have truly\n"
	.string "earned this honor. Congratulations!$"

PokemonLeague_HallOfFame_EventScript_EnterRoom::
	lockall
	textcolor NPC_TEXT_COLOR_MALE
	applymovement LOCALID_PLAYER, PokemonLeague_HallOfFame_Movement_EnterRoom
	waitmovement 0
	applymovement LOCALID_HALL_OF_FAME_PROF_OAK, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 18
	call_if_unset FLAG_SE_KANTO_COMPLETE, PokemonLeague_HallOfFame_EventScript_LanceCongratulations
	call_if_set FLAG_SE_KANTO_COMPLETE, PokemonLeague_HallOfFame_EventScript_LanceCongratulationsAgain
	closemessage
	applymovement LOCALID_HALL_OF_FAME_PROF_OAK, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 20
	dofieldeffect FLDEFF_HALL_OF_FAME_RECORD_FRLG
	waitfieldeffect FLDEFF_HALL_OF_FAME_RECORD_FRLG
	delay 40
	setvar VAR_TEMP_1, 1
	call EventScript_SetDefeatedEliteFourFlagsVars
	call SE_EventScript_HallOfFameRespawn
	fadescreenspeed FADE_TO_BLACK, 24
	special EnterHallOfFame
	waitstate
	releaseall
	end

PokemonLeague_HallOfFame_Movement_EnterRoom::
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

PokemonLeague_HallOfFame_Text_OakCongratulations::
	.string "LANCE: This is the POKéMON\n"
	.string "HALL OF FAME.\p"
	.string "Here we honor the LEAGUE\n"
	.string "CHAMPIONS for all eternity.\p"
	.string "Their courageous POKéMON are also\n"
	.string "inducted here.\p"
	.string "Today, I am honored to welcome\n"
	.string "a new CHAMPION, {PLAYER}.\p"
	.string "Congratulations, {PLAYER}, you and\n"
	.string "your POKéMON are HALL OF FAMERS!$"

