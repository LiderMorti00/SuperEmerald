ValorLakefront_sinnoh_MapScripts::
	.byte 0


ValorLakefront_Text_SNIHadToTalk::
	.string "Cynthia: Oh, hello, long time no see! How\n"
	.string "is your POKéDEX filling up?\p"
	.string "I came to research the folklore about\n"
	.string "the lake, but...\p"
	.string "Well, it doesn’t appear as if the lake is\n"
	.string "open to the public now.\p"
	.string "Have you heard the folklore about it?\p"
	.string "They say there is an island inside the\n"
	.string "lake.\p"
	.string "And inside that island is a mirage of a\n"
	.string "POKéMON.\p"
	.string "No one must enter the chamber of that\n"
	.string "POKéMON...\p"
	.string "Oh, that’s right! I had to talk to you\n"
	.string "about something else...$"

SE_S_ValorLakefront_ValorLakefront_EventScript_SNCynthia::
	msgbox ValorLakefront_Text_SNIHadToTalk, MSGBOX_NPC
	end

ValorLakefront_EventScript_SNGrunt::
	trainerbattle_single TRAINER_ROBERT_2_SINNOH, ValorLakefront_EventScript_SNGrunt_Intro, ValorLakefront_EventScript_SNGrunt_Defeat, ValorLakefront_EventScript_SNGrunt_Won
	end

ValorLakefront_EventScript_SNNoCyn::
	fadescreen FADE_FROM_BLACK
	release
	end

ValorLakefront_EventScript_SNGrunt_Won::
	lock
	msgbox ValorLakefront_EventScript_SNGrunt_Post, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	setflag FLAG_SN_HIDE_VL_GRUNT
	goto_if_set FLAG_SN_RECEIVED_SECRET_POTION, ValorLakefront_EventScript_SNNoCyn
	clearflag FLAG_SN_HIDE_VALOR_CYNTHIA
	addobject LOCALID_SN_VALOR_CYNTHIA
	goto ValorLakefront_EventScript_SNNoCyn

ValorLakefront_EventScript_SNGrunt_Post::
	.string "I can’t battle anymore... I’m running on\n"
	.string "fumes...\p"
	.string "I’ll have to give this to the\n"
	.string "Commander...\p"
	.string "I wish... I got to use it at the lake...$"

ValorLakefront_EventScript_SNGrunt_Defeat::
	.string "Gweh! I’m running on fumes...$"

ValorLakefront_EventScript_SNGrunt_Intro::
	.string "Aww, no... You’re still on my tail...?\p"
	.string "The lake’s within sight...\p"
	.string "You leave me no choice... My POKéMON\n"
	.string "will KO you...$"

ValorLakefront_EventScript_SNSuiteLady_T1::
	.string "What am I to do...? I’ve gone and\n"
	.string "dropped my Suite Key somewhere again...\l"
	.string "It must be somewhere around the\l"
	.string "lakefront.$"

SE_S_ValorLakefront_ValorLakefront_EventScript_SNSuiteLady::
	msgbox ValorLakefront_EventScript_SNSuiteLady_T1, MSGBOX_NPC
	end

SE_S_ValorLakefront_ValorLakefront_EventScript_SNHoneyTree::
	msgbox SN_HoneyTree_Text_Wait, MSGBOX_NPC
	end

ValorLakefront_EventScript_SNCollector::
	msgbox ValorLakefront_Text_SNBlackout, MSGBOX_NPC
	end

ValorLakefront_Text_SNBlackout::
	.string "Stop, stop! Yes, you!\p"
	.string "Sunyshore City, which is down this\n"
	.string "road, had a major blackout!\p"
	.string "Crews are working on restoring power,\n"
	.string "but the road’s closed now.$"

ValorLakefront_EventScript_PtSign1::
	msgbox ValorLakefront_Text_PtSign1, MSGBOX_SIGN
	end

ValorLakefront_Text_PtSign1::
	.string "Seven Stars Restaurant More Flavor\n"
	.string "Than You Can Wish For$"

ValorLakefront_EventScript_SNSuiteKey::
	goto_if_set FLAG_SN_SUITE_KEY_FOUND, ValorLakefront_EventScript_SNSuiteKey_End
	lockall
	finditem ITEM_ULTRA_BALL
	setflag FLAG_SN_SUITE_KEY_FOUND
	releaseall

ValorLakefront_EventScript_SNSuiteKey_End::
	end
