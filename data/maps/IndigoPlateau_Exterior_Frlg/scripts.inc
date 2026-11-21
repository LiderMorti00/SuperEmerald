IndigoPlateau_Exterior_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, IndigoPlateau_Exterior_OnTransition
	.byte 0

IndigoPlateau_Exterior_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_INDIGO_PLATEAU_EXTERIOR
	call_if_unset FLAG_SE_KANTO_CHAMPION, SE_EventScript_HideRival
	end

@ Super Emerald: HGSS look (tools/sfr/hns/import_kanto_hgss.py)
SE_KH_IndigoPlateau_Exterior_Frlg_RuinsOfAlph_PuzzleAndRewardChambers_MapScript_StatueDescription::
	msgbox SE_KH_IndigoPlateau_Exterior_Frlg_RuinsOfAlph_PuzzleAndRewardChambers_MapScript_StatueDescription_Text, MSGBOX_SIGN
	end

SE_KH_IndigoPlateau_Exterior_Frlg_RuinsOfAlph_PuzzleAndRewardChambers_MapScript_StatueDescription_Text:
	.string "It's a replica of an ancient\n"
	.string "POKéMON.$"

SE_KH_IndigoPlateau_Exterior_Frlg_IndigoPlateau_Sign::
	msgbox SE_KH_IndigoPlateau_Exterior_Frlg_IndigoPlateau_Sign_Text, MSGBOX_SIGN
	end

SE_KH_IndigoPlateau_Exterior_Frlg_IndigoPlateau_Sign_Text:
	.string "INDIGO PLATEAU\p"
	.string "The Ultimate Goal for TRAINERS!\p"
	.string "POKéMON LEAGUE HQ$"

