VeilstoneCity_PokemonCenter_1F_sinnoh_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SE_VeilstoneCity_PC_OnTransition
	.byte 0


VeilstoneCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_VEILSTONE_CITY_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

VeilstoneCity_PokemonCenter_1F_EventScript_PtNpc1::
	msgbox VeilstoneCity_PokemonCenter_1F_Text_PtNpc1, MSGBOX_NPC
	end

VeilstoneCity_PokemonCenter_1F_Text_PtNpc1::
	.string "If you use the hidden move Fly, you’ll\n"
	.string "be instantly whisked to any\p"
	.string "town you’ve visited before.$"

VeilstoneCity_PokemonCenter_1F_EventScript_PtNpc2::
	lock
	faceplayer
	msgbox VeilstoneCity_PokemonCenter_1F_Text_PtNpc2_0, MSGBOX_DEFAULT
	release
	end

VeilstoneCity_PokemonCenter_1F_Text_PtNpc2_0::
	.string "MAYLENE, the GYM LEADER, is a cute girl.\p"
	.string "But don’t let her looks fool you. Even\n"
	.string "grown-ups have trouble with her.$"

SE_VeilstoneCity_PC_OnTransition::
	setrespawn HEAL_LOCATION_VEILSTONE_CITY_SINNOH
	end
