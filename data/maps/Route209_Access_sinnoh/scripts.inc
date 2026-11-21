Route209_Access_sinnoh_MapScripts::
	.byte 0


Route209_Access_EventScript_PtNpc1::
	msgbox Route209_Access_Text_PtNpc1, MSGBOX_NPC
	end

Route209_Access_Text_PtNpc1::
	.string "There's a wrecked stone pillar up\n"
	.string "ahead.\p"
	.string "I wonder what it is? It's got me very\n"
	.string "curious.$"

Route209_Access_EventScript_SNBarry_B0::
	trainerbattle_no_intro TRAINER_CELINA_SINNOH, Route209_Access_EventScript_SNBarry_Defeat
	goto Route209_Access_EventScript_SNBarry_After

Route209_Access_EventScript_SNBarry::
	lockall
	playbgm MUS_RG_ENCOUNTER_RIVAL, FALSE
	msgbox Route209_Access_EventScript_SNBarry_Intro, MSGBOX_DEFAULT
	closemessage
	switch VAR_SN_STARTER_MON
	case 0, Route209_Access_EventScript_SNBarry_B0
	case 1, Route209_Access_EventScript_SNBarry_B1
	case 2, Route209_Access_EventScript_SNBarry_B2
	goto Route209_Access_EventScript_SNBarry_B0

Route209_Access_EventScript_SNBarry_B2::
	trainerbattle_no_intro TRAINER_HAYDEN_SINNOH, Route209_Access_EventScript_SNBarry_Defeat
	goto Route209_Access_EventScript_SNBarry_After

Route209_Access_EventScript_SNBarry_After::
	msgbox Route209_Access_EventScript_SNBarry_Post, MSGBOX_DEFAULT
	closemessage
	getplayerxy VAR_0x8004, VAR_0x8005
	switch VAR_0x8005
	case 4, Route209_Access_EventScript_SNBarry_L4
	case 6, Route209_Access_EventScript_SNBarry_L6
	applymovement LOCALID_SN_R209_BARRY, Route209_Access_EventScript_SNBarry_M5
	goto Route209_Access_EventScript_SNBarry_Gone

Route209_Access_EventScript_SNBarry_Gone::
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_SN_R209_BARRY
	setflag FLAG_SN_HIDE_R209_BARRY
	fadedefaultbgm
	releaseall
	end

Route209_Access_EventScript_SNBarry_M5::
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

Route209_Access_EventScript_SNBarry_L6::
	applymovement LOCALID_SN_R209_BARRY, Route209_Access_EventScript_SNBarry_M6
	goto Route209_Access_EventScript_SNBarry_Gone

Route209_Access_EventScript_SNBarry_M6::
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

Route209_Access_EventScript_SNBarry_L4::
	applymovement LOCALID_SN_R209_BARRY, Route209_Access_EventScript_SNBarry_M4
	goto Route209_Access_EventScript_SNBarry_Gone

Route209_Access_EventScript_SNBarry_M4::
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

Route209_Access_EventScript_SNBarry_Post::
	.string "BARRY: Waaah!\p"
	.string "It goes to show my surefire winning\n"
	.string "strategy doesn't work.\p"
	.string "Say, hey, {PLAYER}. Remember what I told\n"
	.string "you before?\p"
	.string "Make sure all your attacks hit! Avoid\n"
	.string "every enemy attack!\p"
	.string "I thought that was a wicked strategy,\n"
	.string "but it doesn't work worth beans.\p"
	.string "I guess I have to grind it out and\n"
	.string "toughen up the team a bit at a time.\p"
	.string "Anyway! I'm off to SOLACEON TOWN! See\n"
	.string "ya, {PLAYER}!\p"
	.string "You'll be shocked by my growth the\n"
	.string "next time we meet!$"

Route209_Access_EventScript_SNBarry_Defeat::
	.string "BARRY: Waaah! What the…?!$"

Route209_Access_EventScript_SNBarry_B1::
	trainerbattle_no_intro TRAINER_BIANCA_SINNOH, Route209_Access_EventScript_SNBarry_Defeat
	goto Route209_Access_EventScript_SNBarry_After

Route209_Access_EventScript_SNBarry_Intro::
	.string "BARRY: Ta-daah! Kept me waiting again,\n"
	.string "{PLAYER}!\p"
	.string "Let's see how much tougher you and I\n"
	.string "have gotten, right here and now!\p"
	.string "Hey, you're a TRAINER now. You're\n"
	.string "expected to be ready for a battle.\p"
	.string "No whining! No waiting! Let's get the\n"
	.string "show started!$"
