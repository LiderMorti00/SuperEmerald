Route37_hns_MapScripts::
	.byte 0


Route37_EventScript_TwinAnn::
	trainerbattle_double TRAINER_ANN_AND_ANNE_HNS, Route37_Text_TwinsAnnAndAnne1_Seen, Route37_Text_TwinsAnnAndAnne1_Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route37_Text_TwinsAnnAndAnne1_After, MSGBOX_DEFAULT
	release
	end

Route37_Text_TwinsAnnAndAnne1_After::
	.string "ANN: I can tell what my sister and\n"
	.string "my POKéMON are thinking.$"

Route37_Text_TwinsAnnAndAnne1_Beaten::
	.string "ANN & ANNE: Nnn… A little too\n"
	.string "strong.$"

Route37_Text_TwinsAnnAndAnne1_Seen::
	.string "ANN: ANNE and I are in this\n"
	.string "together!$"

Route37_EventScript_TwinAnne::
	trainerbattle_double TRAINER_ANN_AND_ANNE_HNS, Route37_Text_TwinsAnnAndAnne2_Seen, Route37_Text_TwinsAnnAndAnne2_Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route37_Text_TwinsAnnAndAnne2_After, MSGBOX_DEFAULT
	release
	end

Route37_Text_TwinsAnnAndAnne2_After::
	.string "ANNE: We share the same feelings as\n"
	.string "our POKéMON.$"

Route37_Text_TwinsAnnAndAnne2_Beaten::
	.string "ANN & ANNE: Nnn… A little too\n"
	.string "strong.$"

Route37_Text_TwinsAnnAndAnne2_Seen::
	.string "ANNE: ANN and I are in this\n"
	.string "together!$"

Route37_EventScript_Greg::
	trainerbattle_single TRAINER_GREG_HNS, Route37_Text_PsychicGreg_Seen, Route37_Text_PsychicGreg_Beaten
	msgbox Route37_Text_PsychicGreg_After, MSGBOX_AUTOCLOSE
	end

Route37_Text_PsychicGreg_After::
	.string "Putting POKéMON to sleep or paralyz-\n"
	.string "ing them are good battle techniques.$"

Route37_Text_PsychicGreg_Beaten::
	.string "I lost. That's pretty sad…$"

Route37_Text_PsychicGreg_Seen::
	.string "POKéMON can't do a thing if they are\n"
	.string "asleep.\p"
	.string "I'll show you how scary that is!$"

Route37_Text_Sunny_Meet::
	.string "SUNNY: Hi!\p"
	.string "I'm SUNNY of the WEEKDAY family!\p"
	.string "If you can guess my favorite day,\n"
	.string "I'll give you a reward.$"

SE_J_Route37_hns_Route37_EventScript_Sunny::
	msgbox Route37_Text_Sunny_Meet, MSGBOX_NPC
	end

Route37_EventScript_Sign::
	lock
	msgbox Route37_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route37_Text_Sign::
	.string "ROUTE 37\n"
	.string "ECRUTEAK CITY AHEAD$"
