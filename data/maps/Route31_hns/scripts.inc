Route31_hns_MapScripts::
	.byte 0


Route31_Text_BugCatcherWade1_Seen::
	.string "I caught a bunch of POKéMON.\n"
	.string "Let me battle with you!$"

Route31_Text_BugCatcherWade1_Beaten::
	.string "Awwwww…$"

Route31_Text_BugCatcherWade1_After::
	.string "You can catch POKéMON even if\n"
	.string "you have six with you.\p"
	.string "If you catch one, it'll go to\n"
	.string "your BOX automatically.$"

SE_J_Route31_hns_Route31_EventScript_Bugcatcher_Wade::
	trainerbattle_single TRAINER_WADE_HNS, Route31_Text_BugCatcherWade1_Seen, Route31_Text_BugCatcherWade1_Beaten
	msgbox Route31_Text_BugCatcherWade1_After, MSGBOX_AUTOCLOSE
	end

Route31_EventScript_Youngster::
	lock
	faceplayer
	msgbox Route31_Text_CooltrainerM, MSGBOX_DEFAULT
	closemessage
	release
	end

Route31_Text_CooltrainerM::
	.string "DARK CAVE…\p"
	.string "If POKéMON could light it up,\n"
	.string "I'd explore it.$"

Route31_Text_SleepyMan::
	.string "… Hnuurg… Huh?\p"
	.string "I walked too far today looking\n"
	.string "for POKéMON.\p"
	.string "My feet hurt and I'm sleepy…\p"
	.string "If I were a wild POKéMON, I'd\n"
	.string "be easy to catch…\p"
	.string "…Zzzz…$"

SE_J_Route31_hns_Route31_EventScript_SleepyMan::
	msgbox Route31_Text_SleepyMan, MSGBOX_NPC
	end

Route31_EventScript_Boy::
	lock
	faceplayer
	msgbox Route31_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

Route31_Text_Youngster::
	.string "I found a good POKéMON in DARK\n"
	.string "CAVE.\p"
	.string "I'm going to raise it to take\n"
	.string "on FALKNER.\p"
	.string "He's the leader of VIOLET\n"
	.string "CITY's GYM.$"

Route31_EventScript_ItemPokeBall::
	finditem ITEM_POKE_BALL
	end

Route31_EventScript_ItemAntidote::
	finditem ITEM_ANTIDOTE
	end

Route31_EventScript_Sign::
	lock
	msgbox Route31_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route31_Text_Sign::
	.string "ROUTE 31\p"
	.string "VIOLET CITY - CHERRYGROVE CITY$"

Route31_EventScript_DarkCaveSign::
	lock
	msgbox Route31_Text_DarkCaveSign, MSGBOX_SIGN
	closemessage
	release
	end

Route31_Text_DarkCaveSign::
	.string "DARK CAVE$"
