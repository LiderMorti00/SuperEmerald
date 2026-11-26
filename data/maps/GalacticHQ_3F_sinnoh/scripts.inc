GalacticHQ_3F_sinnoh_MapScripts::
	.byte 0

GalacticHQ_3F_EventScript_PtNpc1::
	lock
	faceplayer
	msgbox GalacticHQ_3F_Text_PtNpc1_0, MSGBOX_DEFAULT
	release
	end

GalacticHQ_3F_Text_PtNpc1_0::
	.string "The locked doors only open with a\n"
	.string "special key.\p"
	.string "…Not that there's anything left\n"
	.string "behind them now.$"

GalacticHQ_3F_EventScript_PtSign1::
	msgbox GalacticHQ_3F_Text_PtSign1, MSGBOX_SIGN
	end

GalacticHQ_3F_Text_PtSign1::
	.string "The TEAM GALACTIC credo! Everything\n"
	.string "belongs to TEAM GALACTIC!\p"
	.string "Look beyond the world--space will\n"
	.string "become TEAM GALACTIC's!$"
