AcuityLakefront_sinnoh_MapScripts::
	.byte 0


AcuityLakefront_EventScript_SNBarry::
	lock
	faceplayer
	msgbox AcuityLakefront_Text_SNBarry, MSGBOX_DEFAULT
	release
	end

AcuityLakefront_Text_SNBarry::
	.string "{RIVAL}: Hey, {PLAYER}!\n"
	.string "What, you finally come along now?\p"
	.string "Slooow! Way too slow!\p"
	.string "Listen, {PLAYER}.\n"
	.string "See how the rocks are all lumpy here?\p"
	.string "You can’t climb those rocks until you\n"
	.string "get the SNOWPOINT GYM BADGE.\p"
	.string "Anyway, I’m off.\n"
	.string "TEAM GALACTIC! I’m coming for you!$"

AcuityLakefront_EventScript_PtSign1::
	msgbox AcuityLakefront_Text_PtSign1, MSGBOX_SIGN
	end

AcuityLakefront_Text_PtSign1::
	.string "LAKE ACUITY ahead$"
