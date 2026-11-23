MahoganyTown_Shop_hns_MapScripts::
	.byte 0


MahoganyTown_Shop_Text_Granny::
	.string "I'm sorry, dear. The shop is closed\n"
	.string "for now.\p"
	.string "Strange folks used to hang around\n"
	.string "in the back. It gave me the creeps.$"

SE_J_MahoganyTown_Shop_hns_MahoganyTown_Shop_EventScript_Granny::
	msgbox MahoganyTown_Shop_Text_Granny, MSGBOX_NPC
	end
