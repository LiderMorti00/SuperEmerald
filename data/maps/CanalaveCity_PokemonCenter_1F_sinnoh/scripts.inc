CanalaveCity_PokemonCenter_1F_sinnoh_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SE_CanalaveCity_PC_OnTransition
	.byte 0


CanalaveCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_CANALAVE_CITY_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

CanalaveCity_PokemonCenter_1F_EventScript_PtNpc1::
	lock
	faceplayer
	msgbox CanalaveCity_PokemonCenter_1F_Text_PtNpc1_0, MSGBOX_DEFAULT
	release
	end

CanalaveCity_PokemonCenter_1F_Text_PtNpc1_0::
	.string "I was lucky enough to get a STRENGTH\n"
	.string "HM from IRON ISLAND.\p"
	.string "But I can't use it for moving boulders\n"
	.string "until I beat BYRON, the GYM LEADER.\p"
	.string "I should make a note of that on the\n"
	.string "POKéNAV app Memo Pad.$"

CanalaveCity_PokemonCenter_1F_EventScript_PtNpc2::
	lock
	faceplayer
	msgbox CanalaveCity_PokemonCenter_1F_Text_PtNpc2_0, MSGBOX_DEFAULT
	release
	end

CanalaveCity_PokemonCenter_1F_Text_PtNpc2_0::
	.string "It's easy to get to IRON ISLAND. It's\n"
	.string "one boat trip from here.$"

CanalaveCity_PokemonCenter_1F_EventScript_PtNpc3::
	lock
	faceplayer
	msgbox CanalaveCity_PokemonCenter_1F_Text_PtNpc3_0, MSGBOX_DEFAULT
	release
	end

CanalaveCity_PokemonCenter_1F_Text_PtNpc3_0::
	.string "I heard this cool rumor.\p"
	.string "A ship from this port can take you\n"
	.string "all the way to KANTO, JOHTO and\l"
	.string "even HOENN!\p"
	.string "I wonder what POKéMON live there…$"

CanalaveCity_PokemonCenter_1F_EventScript_PtNpc4::
	lock
	faceplayer
	msgbox CanalaveCity_PokemonCenter_1F_Text_PtNpc4_0, MSGBOX_DEFAULT
	release
	end

CanalaveCity_PokemonCenter_1F_Text_PtNpc4_0::
	.string "It's possible for one kind of POKéMON\n"
	.string "to have different abilities.\p"
	.string "That's news to me!$"

SE_CanalaveCity_PC_OnTransition::
	setrespawn HEAL_LOCATION_CANALAVE_CITY_SINNOH
	end
