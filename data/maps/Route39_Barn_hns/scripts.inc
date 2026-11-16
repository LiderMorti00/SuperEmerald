Route39_Barn_hns_MapScripts::
	.byte 0


Route39_Text_MoomooHappyMoo::
	.string "MILTANK: Mooo!$"

SE_J_Route39_Barn_hns_Route39_Barn_EventScript_Miltank::
	msgbox Route39_Text_MoomooHappyMoo, MSGBOX_NPC
	end

Route39_Text_BarnTwinMoomooIsSick::
	.string "MOOMOO is sick…\p"
	.string "She needs lots of ORAN BERRIES.$"

SE_J_Route39_Barn_hns_Route39_Barn_EventScript_Twins::
	msgbox Route39_Text_BarnTwinMoomooIsSick, MSGBOX_NPC
	end
