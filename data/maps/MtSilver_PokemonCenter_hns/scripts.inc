MtSilver_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtSilver_PokemonCenter_hns_OnTransition
	.byte 0

MtSilver_PokemonCenter_hns_OnTransition:
	setrespawn HEAL_LOCATION_MT_SILVER_HNS
	end


MtSilver_PokemonCenter_Text_Meara1::
	.string "I'm a researcher from… Uhh…\n"
	.string "the PEWTER CITY museum!\p"
	.string "An unusual amount of artifacts have\n"
	.string "been discovered in this area, so\l"
	.string "I've come here to investigate.\p"
	.string "Have you found anything strange\n"
	.string "in the mountain?\p"
	.string "Maybe something like a FLUTE?\p"
	.string "If you do, please show me.$"

SE_J_MtSilver_PokemonCenter_hns_MtSilver_PokemonCenter_EventScript_Meara::
	msgbox MtSilver_PokemonCenter_Text_Meara1, MSGBOX_NPC
	end
