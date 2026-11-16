Route23_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route23_OnTransition
	.byte 0

Route23_OnTransition::
	call SE_EventScript_OroVictoryRoadOnTransition
	end

@ Super Emerald: HGSS look, texts from Pokemon Heart & Soul (tools/sfr/hns/import_kanto_hgss.py)

SE_KH_Route23_Frlg_RuinsOfAlph_PuzzleAndRewardChambers_MapScript_StatueDescription::
	msgbox SE_KH_Route23_Frlg_RuinsOfAlph_PuzzleAndRewardChambers_MapScript_StatueDescription_Text, MSGBOX_SIGN
	end

SE_KH_Route23_Frlg_RuinsOfAlph_PuzzleAndRewardChambers_MapScript_StatueDescription_Text:
	.string "It's a replica of an ancient\n"
	.string "POKéMON.$"

