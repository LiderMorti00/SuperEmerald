Route28_House_hns_MapScripts::
	.byte 0


Route28House_Text_Celebrity1::
	.string "Oh, dear. You've found me.\p"
	.string "Please don't tell anyone about me.\p"
	.string "Out here I can open my window and\n"
	.string "hear birds instead of applause.$"

SE_J_Route28_House_hns_Route28House_EventScript_Celebrity::
	msgbox Route28House_Text_Celebrity1, MSGBOX_NPC
	end
