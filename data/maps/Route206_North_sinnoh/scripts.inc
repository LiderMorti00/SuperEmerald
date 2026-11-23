Route206_North_sinnoh_MapScripts::
	.byte 0


Route206_North_EventScript_SNDawnFather::
	lock
	faceplayer
	goto_if_set FLAG_SN_RECEIVED_EXP_SHARE, Route206_North_EventScript_SNDawnFather_After
	setvar VAR_0x8004, 0
	special ScriptGetPokedexInfo
	buffernumberstring STR_VAR_1, VAR_0x8005
	checkplayergender
	goto_if_eq VAR_RESULT, FEMALE, Route206_North_EventScript_SNDawnFather_G_L
	msgbox Route206_North_EventScript_SNDawnFather_T1, MSGBOX_DEFAULT
	goto Route206_North_EventScript_SNDawnFather_G_N

Route206_North_EventScript_SNDawnFather_End::
	release
	end

Route206_North_EventScript_SNDawnFather_G_N::
	goto_if_lt VAR_0x8005, 35, Route206_North_EventScript_SNDawnFather_NotYet
	msgbox Route206_North_EventScript_SNDawnFather_T2, MSGBOX_DEFAULT
	giveitem ITEM_EXP_SHARE
	goto_if_eq VAR_RESULT, FALSE, Route206_North_EventScript_SNDawnFather_End
	setflag FLAG_SN_RECEIVED_EXP_SHARE
	msgbox Route206_North_EventScript_SNDawnFather_T3, MSGBOX_DEFAULT
	goto Route206_North_EventScript_SNDawnFather_End

Route206_North_EventScript_SNDawnFather_T3::
	.string "A POKéMON holding an EXP. SHARE will\n"
	.string "get some of the Exp. Points from\l"
	.string "battle.\p"
	.string "It will get Exp. Points even if it didn't\n"
	.string "actually battle.\p"
	.string "Therefore, it should be held by a\n"
	.string "POKéMON you want to raise quickly.\p"
	.string "Also, a POKéMON you get in a trade may\n"
	.string "disobey you if it is too high in level.\p"
	.string "Don't worry, though. It will obey if you\n"
	.string "have enough GYM BADGES.$"

Route206_North_EventScript_SNDawnFather_T2::
	.string "Oh, my! You've met {STR_VAR_1} POKéMON!\p"
	.string "Wonderful! Yes, bravo! PROFESSOR ROWAN\n"
	.string "should be delighted!\p"
	.string "Here is something for you!$"

Route206_North_EventScript_SNDawnFather_NotYet::
	msgbox Route206_North_EventScript_SNDawnFather_NotYetT, MSGBOX_DEFAULT
	release
	end

Route206_North_EventScript_SNDawnFather_NotYetT::
	.string "You've met only {STR_VAR_1} POKéMON?\p"
	.string "Hmm… You've got to find at least 35.\p"
	.string "If you can't, it will be tough to\n"
	.string "complete the SINNOH POKéDEX.$"

Route206_North_EventScript_SNDawnFather_T1::
	.string "Hello! You must be {PLAYER}, the\n"
	.string "TRAINER from HOENN.\p"
	.string "I'm PROFESSOR ROWAN's assistant and\n"
	.string "DAWN's father.\p"
	.string "The professor asked me to help\n"
	.string "TRAINERS on their adventures.\p"
	.string "{PLAYER}, let me ask you, how many\n"
	.string "POKéMON have you met?$"

Route206_North_EventScript_SNDawnFather_G_L::
	msgbox Route206_North_EventScript_SNDawnFather_T1L, MSGBOX_DEFAULT
	goto Route206_North_EventScript_SNDawnFather_G_N

Route206_North_EventScript_SNDawnFather_T1L::
	.string "Hello! You must be {PLAYER}, the\n"
	.string "TRAINER from HOENN.\p"
	.string "I'm PROFESSOR ROWAN's assistant and\n"
	.string "LUCAS's father.\p"
	.string "The professor asked me to help\n"
	.string "TRAINERS on their adventures.\p"
	.string "{PLAYER}, let me ask you, how many\n"
	.string "POKéMON have you met?$"

Route206_North_EventScript_SNDawnFather_After::
	msgbox Route206_North_EventScript_SNDawnFather_T3, MSGBOX_DEFAULT
	release
	end

Route206_North_EventScript_SNGateGuard::
	msgbox Route206_North_Text_SNGateGuard, MSGBOX_NPC
	end

Route206_North_Text_SNGateGuard::
	.string "Cycling Road is one long slope.\p"
	.string "Riding down it on your BIKE is a real\n"
	.string "thrill, but going up takes some effort!\p"
	.string "Hold tight to your handlebars and\n"
	.string "enjoy the ride!$"
