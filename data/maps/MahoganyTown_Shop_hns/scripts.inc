MahoganyTown_Shop_hns_MapScripts::
	.byte 0


MahoganyTown_Shop_Text_Granny::
	.string "Please come back another time.\n"
	.string "The store is... closed\l"
	.string "right now.$"

SE_J_MahoganyTown_Shop_hns_MahoganyTown_Shop_EventScript_Granny::
	msgbox MahoganyTown_Shop_Text_Granny, MSGBOX_NPC
	end
