MtSilver_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtSilver_PokemonCenter_hns_OnTransition
	.byte 0

MtSilver_PokemonCenter_hns_OnTransition:
	setrespawn HEAL_LOCATION_MT_SILVER_HNS
	end


MtSilver_PokemonCenter_Text_Meara1::
	.string "I'm a researcher from the PEWTER\n"
	.string "MUSEUM.\p"
	.string "An unusual number of artifacts have\n"
	.string "been found around MT. SILVER.\p"
	.string "So I've come here to investigate.$"

SE_J_MtSilver_PokemonCenter_hns_MtSilver_PokemonCenter_EventScript_Meara::
	msgbox MtSilver_PokemonCenter_Text_Meara1, MSGBOX_NPC
	end
