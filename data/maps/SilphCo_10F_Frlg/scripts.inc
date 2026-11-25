SilphCo_10F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SilphCo_10F_OnLoad
	.byte 0

SilphCo_10F_OnLoad::
	call_if_unset FLAG_SILPH_10F_DOOR, EventScript_Close10FDoor
	end

SilphCo_10F_EventScript_WorkerF::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_SILPH_CO_11F, 1, SilphCo_10F_EventScript_WorkerFRocketsGone
	msgbox SilphCo_10F_Text_WaaaImScared
	release
	end

SilphCo_10F_EventScript_WorkerFRocketsGone::
	msgbox SilphCo_10F_Text_NewStaff
	release
	end

SilphCo_10F_EventScript_FloorSign::
	msgbox SilphCo_10F_Text_FloorSign, MSGBOX_SIGN
	end

SilphCo_10F_Text_WaaaImScared::
	.string "Waaaaa!\n"
	.string "I'm scared!$"

SilphCo_10F_Text_NewStaff::
	.string "I started here after SILPH reopened.\p"
	.string "The warp panels help when I get\n"
	.string "sent from floor to floor.$"

SilphCo_10F_Text_FloorSign::
	.string "SILPH CO. HEAD OFFICE\n"
	.string "10F$"

