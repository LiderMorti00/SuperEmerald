MahoganyTown_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MahoganyTown_PokemonCenter_hns_OnTransition
	.byte 0

MahoganyTown_PokemonCenter_hns_OnTransition:
	setrespawn HEAL_LOCATION_MAHOGANY_TOWN_HNS
	end


MahoganyTown_PokemonCenter_EventScript_Hiker::
	goto_if_ne VAR_SE_ROCKET_QUEST, 1, SE_MahoganyPC_HikerCalm_Script
	msgbox MahoganyTown_PokemonCenter_Text_PokefanM, MSGBOX_NPC
	end

MahoganyTown_PokemonCenter_Text_PokefanM::
    .string "What's this? TEAM ROCKET has come\n"
    .string "back?\p"
    .string "I saw some men in black at LAKE OF\n"
    .string "RAGE…$"

MahoganyTown_PokemonCenter_EventScript_Boy::
	msgbox MahoganyTown_PokemonCenter_Text_Youngster, MSGBOX_NPC
	end

MahoganyTown_PokemonCenter_Text_Youngster::
    .string "I stop my POKéMON from evolving too\n"
    .string "early.\p"
    .string "I make them learn certain moves\n"
    .string "before I let them evolve.$"

MahoganyTown_PokemonCenter_EventScript_Girl::
	msgbox MahoganyTown_PokemonCenter_Text_CooltrainerF, MSGBOX_NPC
	end

MahoganyTown_PokemonCenter_Text_CooltrainerF::
    .string "POKéMON do become stronger when they\n"
    .string "evolve,\p"
    .string "but they also learn moves more\n"
    .string "slowly.$"

SE_MahoganyPC_HikerCalm_Script::
	msgbox SE_MahoganyPC_HikerCalm_Text, MSGBOX_NPC
	end

SE_MahoganyPC_HikerCalm_Text::
	.string "TEAM ROCKET had a hideout right\n"
	.string "here in MAHOGANY once.\p"
	.string "Hard to believe, isn't it?$"
