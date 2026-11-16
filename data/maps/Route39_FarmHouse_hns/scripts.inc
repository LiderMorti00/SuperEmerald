Route39_FarmHouse_hns_MapScripts::
	.byte 0


Route39_Text_FarmerMBuyMilk::
	.string "How'd you like my MOOMOO MILK?\p"
	.string "It's my pride and joy, there.\p"
	.string "Give it to POKéMON to restore HP!\p"
	.string "I'll give it to ya fer just\n"
	.string "¥500.$"

SE_J_Route39_FarmHouse_hns_Route39_FarmHouse_EventScript_FarmerM::
	msgbox Route39_Text_FarmerMBuyMilk, MSGBOX_NPC
	end

Route39_Text_FarmerFInTrouble::
	.string "Our milk even goes out to\n"
	.string "KANTO.\p"
	.string "So if our own MILTANK won't\n"
	.string "give us any milk, we're in trouble.$"

SE_J_Route39_FarmHouse_hns_Route39House_EventScript_FarmerF::
	msgbox Route39_Text_FarmerFInTrouble, MSGBOX_NPC
	end
