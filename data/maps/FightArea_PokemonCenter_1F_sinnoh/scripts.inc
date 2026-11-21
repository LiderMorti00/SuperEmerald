FightArea_PokemonCenter_1F_sinnoh_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SE_FightArea_PC_OnTransition
	.byte 0


FightArea_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_FIGHT_AREA_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

FightArea_PokemonCenter_1F_EventScript_PtNpc1::
	lock
	faceplayer
	msgbox FightArea_PokemonCenter_1F_Text_PtNpc1_0, MSGBOX_DEFAULT
	release
	end

FightArea_PokemonCenter_1F_Text_PtNpc1_0::
	.string "The BATTLE FRONTIER's as tough as they\n"
	.string "say…\p"
	.string "None of the facilities are cakewalks,\n"
	.string "that's for sure.$"

FightArea_PokemonCenter_1F_EventScript_PtNpc2::
	lock
	faceplayer
	msgbox FightArea_PokemonCenter_1F_Text_PtNpc2_0, MSGBOX_DEFAULT
	release
	end

FightArea_PokemonCenter_1F_Text_PtNpc2_0::
	.string "The best TRAINERS from around the\n"
	.string "country…\p"
	.string "No, the best TRAINERS from around the\n"
	.string "world gather at the BATTLE ZONE.$"

FightArea_PokemonCenter_1F_EventScript_PtNpc3::
	lock
	faceplayer
	msgbox FightArea_PokemonCenter_1F_Text_PtNpc3_0, MSGBOX_DEFAULT
	release
	end

FightArea_PokemonCenter_1F_Text_PtNpc3_0::
	.string "To toughen myself! To toughen my\n"
	.string "POKéMON!\p"
	.string "For that alone, I have come!$"

SE_FightArea_PC_OnTransition::
	setrespawn HEAL_LOCATION_FIGHT_AREA_SINNOH
	end
