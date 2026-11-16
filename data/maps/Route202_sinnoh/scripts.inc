Route202_sinnoh_MapScripts::
	.byte 0


Route202_EventScript_Dawn::


Route202_EventScript_Tristan::
	trainerbattle_single TRAINER_BILLY_SINNOH, Route202_Text_TristanIntro, Route202_Text_TristanDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route202_EventScript_Tristan_Rematch
	msgbox Route202_Text_TristanPost, MSGBOX_AUTOCLOSE
	end

Route202_Text_TristanPost::
	.string "Don't be shy about talking to Trainers\n"
	.string "you'd like to battle.\p"
	.string "POKéMON grow stronger and stronger\n"
	.string "from battling.$"

Route202_EventScript_Tristan_Rematch::
	trainerbattle_rematch TRAINER_BILLY_SINNOH, Route202_Text_TristanIntro, Route202_Text_TristanDefeat
	msgbox Route202_Text_TristanPost, MSGBOX_AUTOCLOSE
	end

Route202_Text_TristanDefeat::
	.string "Too strong! Too strong!$"

Route202_Text_TristanIntro::
	.string "You're a POKéMON Trainer, and so am I!\n"
	.string "Our eyes met, so battle we must!$"

Route202_EventScript_Natalie::
	trainerbattle_single TRAINER_JOEY_SINNOH, Route202_Text_NatalieIntro, Route202_Text_NatalieDefeat
	msgbox Route202_Text_NataliePost, MSGBOX_AUTOCLOSE
	end

Route202_Text_NataliePost::
	.string "My POKéMON are all tuckered out! I\n"
	.string "need to go to a POKéMON CENTER!$"

Route202_Text_NatalieDefeat::
	.string "Oh, boo! I can't win!$"

Route202_Text_NatalieIntro::
	.string "I spy, with my little eye... A Trainer!\p"
	.string "A battle, please!$"

Route202_EventScript_Logan::
	trainerbattle_single TRAINER_TIMMY_SINNOH, Route202_Text_LoganIntro, Route202_Text_LoganDefeat
	msgbox Route202_Text_LoganPost, MSGBOX_AUTOCLOSE
	end

Route202_Text_LoganPost::
	.string "It was fun battling! Yup! I'm going to\n"
	.string "battle everyone!$"

Route202_Text_LoganDefeat::
	.string "You beat me?! You've got talent!$"

Route202_Text_LoganIntro::
	.string "Let's have a POKéMON battle! Humph!\n"
	.string "But I'm gonna win!$"

Route202_EventScript_PtNpc1::
	msgbox Route202_Text_PtNpc1, MSGBOX_NPC
	end

Route202_Text_PtNpc1::
	.string "Some POKéMON only appear in the\n"
	.string "morning.\p"
	.string "Some only come out at night.\p"
	.string "I'll keep looking till I've seen them\n"
	.string "all!$"

Route202_Text_SNRadarAD::
	.string "Dawn: Hi, {PLAYER}! I was waiting for\n"
	.string "you.\p"
	.string "Let me show you how the Poké Radar\n"
	.string "works.\p"
	.string "Let’s not waste any time. So, when you\n"
	.string "use the Poké Radar...$"

SE_S_Route202_Route202_EventScript_SNRadarCP::
	msgbox Route202_Text_SNRadarAD, MSGBOX_NPC
	end

Route202_EventScript_Sign1::
	msgbox Route202_Text_Sign1, MSGBOX_SIGN
	end

Route202_Text_Sign1::
	.string "ROUTE 202\p"
	.string "North: JUBILIFE CITY South:\n"
	.string "SANDGEM TOWN$"

Route202_EventScript_Sign2::
	msgbox Route202_Text_Sign2, MSGBOX_SIGN
	end

Route202_Text_Sign2::
	.string "TRAINER TIPS\p"
	.string "A POKéMON that is asleep or\n"
	.string "paralyzed is easier to catch!$"

Route202_EventScript_Sign3::
	msgbox Route202_Text_Sign3, MSGBOX_SIGN
	end

Route202_Text_Sign3::
	.string "TRAINER TIPS\p"
	.string "Trainers will challenge you as\n"
	.string "soon as your eyes meet. Be ready!$"
