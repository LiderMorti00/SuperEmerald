FourIsland_LoreleisHouse_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FourIsland_LoreleisHouse_OnTransition
	.byte 0

FourIsland_LoreleisHouse_OnTransition::
	special UpdateLoreleiDollCollection
	end

FourIsland_LoreleisHouse_EventScript_Lorelei::
	lock
	faceplayer
	goto_if_eq VAR_SE_ROCKET_QUEST, 5, FourIsland_LoreleisHouse_EventScript_LoreleiRocketsBack
	goto_if_set FLAG_TALKED_TO_LORELEI_AFTER_WAREHOUSE, FourIsland_LoreleisHouse_EventScript_Lorelei3
	goto_if_set FLAG_DEFEATED_ROCKETS_IN_WAREHOUSE, FourIsland_LoreleisHouse_EventScript_Lorelei2
	msgbox FourIsland_LoreleisHouse_Text_IfAnythingWereToHappenToIsland
	release
	end

FourIsland_LoreleisHouse_EventScript_Lorelei2::
	setflag FLAG_TALKED_TO_LORELEI_AFTER_WAREHOUSE
	msgbox FourIsland_LoreleisHouse_Text_RocketIsGone
	release
	end

FourIsland_LoreleisHouse_EventScript_Lorelei3::
	msgbox FourIsland_LoreleisHouse_Text_WillDoWhatICanHereAndNow
	release
	end

FourIsland_LoreleisHouse_EventScript_LoreleiRocketsBack::
	msgbox FourIsland_LoreleisHouse_Text_RocketsAtWarehouse
	release
	end

FourIsland_LoreleisHouse_EventScript_Doll::
	lock
	msgbox FourIsland_LoreleisHouse_Text_StuffedMonDollsGalore
	release
	end

FourIsland_LoreleisHouse_Text_IfAnythingWereToHappenToIsland::
	.string "LORELEI: Welcome to FOUR ISLAND.\p"
	.string "I left the ELITE FOUR so I could\n"
	.string "look after the island where I was\l"
	.string "born.\p"
	.string "It's quiet here. I like it that way.$"

FourIsland_LoreleisHouse_Text_RocketIsGone::
	.string "LORELEI: Welcome to FOUR ISLAND.\p"
	.string "TEAM ROCKET used to cause trouble\n"
	.string "out here. The islands have been\l"
	.string "quieter since they left.\p"
	.string "I grew up here. Even now, I like to\n"
	.string "stay close to home.$"

FourIsland_LoreleisHouse_Text_WillDoWhatICanHereAndNow::
	.string "LORELEI: Being home lets me keep an\n"
	.string "eye on the islands.\p"
	.string "I don't know what the future holds,\n"
	.string "but I'll do what I can here and now.$"

FourIsland_LoreleisHouse_Text_RocketsAtWarehouse::
	.string "LORELEI: The fishermen say TEAM\n"
	.string "ROCKET is back in the old warehouse\l"
	.string "on FIVE ISLAND.\p"
	.string "I thought we were rid of them…\p"
	.string "If you're going there, be careful.$"

FourIsland_LoreleisHouse_Text_StuffedMonDollsGalore::
	.string "Stuffed POKéMON dolls galore!$"

