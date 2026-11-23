SaffronCity_MagnetTrainStation_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SE_SaffronStation_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, SE_SaffronStation_OnWarpInto
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SE_SaffronStation_OnFrame
	.byte 0

@ Super Emerald: HGSS look, texts from Pokemon Heart & Soul (tools/sfr/hns/import_kanto_hgss.py)

SE_KH_SaffronCity_MagnetTrainStation_Frlg_Teacher::
	msgbox SE_KH_SaffronCity_MagnetTrainStation_Frlg_Teacher_Text, MSGBOX_NPC
	end

SE_KH_SaffronCity_MagnetTrainStation_Frlg_Teacher_Text:
	.string "Thanks to the MAGNET TRAIN, KANTO\n"
	.string "and JOHTO are just a short ride\l"
	.string "apart now.$"

SE_KH_SaffronCity_MagnetTrainStation_Frlg_Lass::
	msgbox SE_KH_SaffronCity_MagnetTrainStation_Frlg_Lass_Text, MSGBOX_NPC
	end

SE_KH_SaffronCity_MagnetTrainStation_Frlg_Lass_Text:
	.string "Hi. Do you have a rail PASS?\n"
	.string "I have one.\p"
	.string "All the people in SAFFRON who ride\n"
	.string "the MAGNET TRAIN have PASSES.$"

SE_KH_SaffronCity_MagnetTrainStation_Frlg_Nerd::
	msgbox SE_KH_SaffronCity_MagnetTrainStation_Frlg_Nerd_Text, MSGBOX_NPC
	end

SE_KH_SaffronCity_MagnetTrainStation_Frlg_Nerd_Text:
	.string "Whew…\p"
	.string "How many times have I gone back\n"
	.string "and forth between KANTO and JOHTO?$"

