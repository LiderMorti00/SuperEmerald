@ Super Emerald: Pokemon World Tournament. A copy of the Battle Dome scripts (the PWT runs on the
@ Dome engine) with its own labels, warps and texts; nothing here is shared with Hoenn's Dome.
@ PWT-only parts: data/scripts/se_pwt.inc and src/se_pwt.c.

PokemonWorldTournamentCorridor_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PokemonWorldTournamentCorridor_OnFrame
	.byte 0

PokemonWorldTournamentCorridor_OnFrame:
	map_script_2 VAR_TEMP_0, 0, PokemonWorldTournamentCorridor_EventScript_EnterCorridor
	.2byte 0

PokemonWorldTournamentCorridor_EventScript_EnterCorridor::
	delay 16
	setvar VAR_TEMP_0, 1
	frontier_get FRONTIER_DATA_LVL_MODE
	goto_if_eq VAR_RESULT, FRONTIER_LVL_OPEN, PokemonWorldTournamentCorridor_EventScript_WalkToBattleRoomLvOpen
	applymovement LOCALID_DOME_CORRIDOR_ATTENDANT, PokemonWorldTournamentCorridor_Movement_AttendantWalkToDoorLv50
	applymovement LOCALID_PLAYER, PokemonWorldTournamentCorridor_Movement_PlayerWalkToDoorLv50
	waitmovement 0
	opendoor 13, 3
	waitdooranim
	applymovement LOCALID_DOME_CORRIDOR_ATTENDANT, PokemonWorldTournamentCorridor_Movement_AttendantEnterDoorLv50
	applymovement LOCALID_PLAYER, PokemonWorldTournamentCorridor_Movement_PlayerEnterDoorLv50
	waitmovement 0
	closedoor 13, 3
	waitdooranim
	goto PokemonWorldTournamentCorridor_EventScript_WarpToPreBattleRoom

PokemonWorldTournamentCorridor_EventScript_WalkToBattleRoomLvOpen::
	applymovement LOCALID_DOME_CORRIDOR_ATTENDANT, PokemonWorldTournamentCorridor_Movement_AttendantWalkToDoorLvOpen
	applymovement LOCALID_PLAYER, PokemonWorldTournamentCorridor_Movement_PlayerWalkToDoorLvOpen
	waitmovement 0
	opendoor 37, 3
	waitdooranim
	applymovement LOCALID_DOME_CORRIDOR_ATTENDANT, PokemonWorldTournamentCorridor_Movement_AttendantEnterDoorLvOpen
	applymovement LOCALID_PLAYER, PokemonWorldTournamentCorridor_Movement_PlayerEnterDoorLvOpen
	waitmovement 0
	closedoor 37, 3
	waitdooranim
PokemonWorldTournamentCorridor_EventScript_WarpToPreBattleRoom::
	waitmovement 0
	setvar VAR_0x8006, 0
	warp MAP_POKEMON_WORLD_TOURNAMENT_PRE_BATTLE_ROOM, 5, 7
	waitstate
	end

PokemonWorldTournamentCorridor_Movement_PlayerWalkToDoorLv50:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

PokemonWorldTournamentCorridor_Movement_PlayerEnterDoorLv50:
	walk_up
	walk_up
	set_invisible
	step_end

PokemonWorldTournamentCorridor_Movement_AttendantWalkToDoorLv50:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

PokemonWorldTournamentCorridor_Movement_AttendantEnterDoorLv50:
	walk_up
	set_invisible
	step_end

PokemonWorldTournamentCorridor_Movement_PlayerWalkToDoorLvOpen:
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

PokemonWorldTournamentCorridor_Movement_PlayerEnterDoorLvOpen:
	walk_up
	walk_up
	set_invisible
	step_end

PokemonWorldTournamentCorridor_Movement_AttendantWalkToDoorLvOpen:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	step_end

PokemonWorldTournamentCorridor_Movement_AttendantEnterDoorLvOpen:
	walk_up
	set_invisible
	step_end

@ Unused
PokemonWorldTournamentCorridor_Movement_WalkToBattleRoomMidRight:
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	set_invisible
	step_end
