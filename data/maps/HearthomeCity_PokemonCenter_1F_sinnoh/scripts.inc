HearthomeCity_PokemonCenter_1F_sinnoh_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SE_HearthomeCity_PC_OnTransition
	.byte 0


HearthomeCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_HEARTHOME_CITY_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

HearthomeCity_PokemonCenter_1F_EventScript_PtNpc1::
	lock
	faceplayer
	msgbox HearthomeCity_PokemonCenter_1F_Text_PtNpc1_0, MSGBOX_DEFAULT
	release
	end

HearthomeCity_PokemonCenter_1F_Text_PtNpc1_0::
	.string "Have you checked out the Global\n"
	.string "Terminal in JUBILIFE CITY?\p"
	.string "They say it links trainers from\n"
	.string "every region. It's wicked!$"

HearthomeCity_PokemonCenter_1F_EventScript_PtNpc2::
	lock
	faceplayer
	msgbox HearthomeCity_PokemonCenter_1F_Text_PtNpc2_0, MSGBOX_DEFAULT
	release
	end

HearthomeCity_PokemonCenter_1F_Text_PtNpc2_0::
	.string "Hello, do you have a POKéBLOCK CASE?\p"
	.string "If you haven’t got one, you really must\n"
	.string "visit the POKéMON Fan Club.$"

HearthomeCity_PokemonCenter_1F_EventScript_PtNpc3::
	lock
	faceplayer
	msgbox HearthomeCity_PokemonCenter_1F_Text_PtNpc3_0, MSGBOX_DEFAULT
	release
	end

HearthomeCity_PokemonCenter_1F_Text_PtNpc3_0::
	.string "FANTINA, the GYM LEADER, likes\n"
	.string "CONTESTS, too.\p"
	.string "That lady has a huge appetite for\n"
	.string "experiencing everything in life!$"

SE_HearthomeCity_PC_OnTransition::
	setrespawn HEAL_LOCATION_HEARTHOME_CITY_SINNOH
	end
