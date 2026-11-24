EcruteakCity_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EcruteakCity_PokemonCenter_hns_OnTransition
	.byte 0

EcruteakCity_PokemonCenter_hns_OnTransition:
	setrespawn HEAL_LOCATION_ECRUTEAK_CITY_HNS
	end

EcruteakCity_PokemonCenter_EventScript_Nerd::
	lock
	faceplayer
	goto_if_ne VAR_SE_ROCKET_QUEST, 1, SE_EcruteakPC_RadioCalm_Script
	msgbox EcruteakCity_PokemonCenter1F_Text_GymGuide, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_PokemonCenter1F_Text_GymGuide::
	.string "My radio keeps picking up a strange\n"
	.string "signal near the LAKE OF RAGE.\p"
	.string "It sounds like someone giving\n"
	.string "orders… Creepy!$"

EcruteakCity_PokemonCenter_EventScript_Hiker::
	lock
	faceplayer
	msgbox EcruteakCity_PokemonCenter1F_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_PokemonCenter1F_Text_PokefanM::
	.string "The way the KIMONO GIRLS dance is\n"
	.string "marvelous.\p"
	.string "Just like the way they use their\n"
	.string "POKéMON.$"

EcruteakCity_PokemonCenter_EventScript_Woman::
	lock
	faceplayer
	msgbox EcruteakCity_PokemonCenter1F_Text_CooltrainerF, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_PokemonCenter1F_Text_CooltrainerF::
	.string "MORTY, the GYM LEADER, is soooo\n"
	.string "cool.\p"
	.string "His POKéMON are really tough too.$"

SE_EcruteakPC_RadioCalm_Script::
	msgbox SE_EcruteakPC_RadioCalm_Text, MSGBOX_DEFAULT
	closemessage
	release
	end

SE_EcruteakPC_RadioCalm_Text::
	.string "My radio used to pick up a strange\n"
	.string "signal near the LAKE OF RAGE.\p"
	.string "These days all I hear is music.$"
