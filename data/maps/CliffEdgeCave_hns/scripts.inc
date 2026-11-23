CliffEdgeCave_hns_MapScripts::
	.byte 0


CliffEdgeCave_EventScript_BaldMan::
	lock
	faceplayer
	msgbox CliffEdgeCave_Text_Baldman, MSGBOX_DEFAULT
	closemessage
	release
	end

CliffEdgeCave_Text_Baldman::
	.string "The ladders lead to different\n"
	.string "parts of ROUTE 47.\p"
	.string "Try the other ladder if you're\n"
	.string "looking for a way down to the sea.$"
