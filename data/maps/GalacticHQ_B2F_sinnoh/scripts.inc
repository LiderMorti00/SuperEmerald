GalacticHQ_B2F_sinnoh_MapScripts::
	.byte 0

GalacticHQ_B2F_EventScript_PtNpc1::
	lock
	faceplayer
	msgbox GalacticHQ_B2F_Text_PtNpc1_0, MSGBOX_DEFAULT
	release
	end

GalacticHQ_B2F_Text_PtNpc1_0::
	.string "Master CYRUS's speech… That feels\n"
	.string "like ages ago.\p"
	.string "Now there's nobody left to give us\n"
	.string "orders around here.$"

GalacticHQ_B2F_EventScript_PtNpc2::
	lock
	faceplayer
	msgbox GalacticHQ_B2F_Text_PtNpc2_0, MSGBOX_DEFAULT
	release
	end

GalacticHQ_B2F_Text_PtNpc2_0::
	.string "TEAM GALACTIC was going to set free\n"
	.string "all POKéMON, and then own it all!\p"
	.string "Now look at us. We're just cleaning\n"
	.string "up the labs.$"
