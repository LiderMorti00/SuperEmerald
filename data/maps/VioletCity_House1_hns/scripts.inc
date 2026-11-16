VioletCity_House1_hns_MapScripts::
	.byte 0


VioletCity_House1_EventScript_Kyle::
	lock
	faceplayer
	msgbox VioletCity_House1_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_House1_Text_PokefanM::
	.string "A POKéMON you get in a trade\n"
	.string "grows quickly.\p"
	.string "But if you don't have the right\n"
	.string "GYM BADGE, they may disobey you.$"

VioletCity_House1_Text_ThisIsntAMon::
	.string "Uh, no, I don't think so.\n"
	.string "That isn't a {STR_VAR_1}.$"

SE_J_VioletCity_House1_hns_VioletCity_House1_EventScript_Rudy::
	msgbox VioletCity_House1_Text_ThisIsntAMon, MSGBOX_NPC
	end
