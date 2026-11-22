EcruteakCity_Gym_hns_MapScripts::
	.byte 0


EcruteakCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_JOHTO_BADGE4_GET, EcruteakCity_Gym_EventScript_GymGuy2
	msgbox EcruteakCity_GymGuideText, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_GymGuideText::
	.string "Watch your step in the dark.\p"
	.string "MORTY's GENGAR is just as tricky\n"
	.string "as the path through this GYM!$"

EcruteakCity_Gym_EventScript_GymGuy2::
	msgbox EcruteakCity_GymGuideWinText, MSGBOX_DEFAULT
	release
	end	

EcruteakCity_GymGuideWinText::
	.string "Whew, {PLAYER}. You did great!\p"
	.string "I was cowering in the corner\n"
	.string "out of pure terror!$"

EcruteakCity_Gym_EventScript_Jeffrey::
	trainerbattle_single TRAINER_JEFFREY_HNS, SageJeffreySeenText, SageJeffreyBeatenText
	msgbox SageJeffreyAfterBattleText, MSGBOX_AUTOCLOSE
	end

SageJeffreyAfterBattleText::
	.string "Where did POKéMON come from?$"

SageJeffreyBeatenText::
	.string "Wins and losses--I've known\n"
	.string "them both.$"

SageJeffreySeenText::
	.string "I spent the spring with my\n"
	.string "POKéMON.\p"
	.string "Then summer, fall, and winter…\p"
	.string "Then spring came again.\n"
	.string "We've been together a long time.$"

EcruteakCity_Gym_EventScript_Martha::
	trainerbattle_single TRAINER_MARTHA_HNS, MediumMarthaSeenText, MediumMarthaBeatenText
	msgbox MediumMarthaAfterBattleText, MSGBOX_AUTOCLOSE
	end

MediumMarthaAfterBattleText::
	.string "The one who wants to win the\n"
	.string "most is the one who will!$"

MediumMarthaBeatenText::
	.string "I… I… I lost!$"

MediumMarthaSeenText::
	.string "I shall win!$"

EcruteakCity_Gym_EventScript_Ping::
	trainerbattle_single TRAINER_PING_HNS, SagePingSeenText, SagePingBeatenText
	msgbox SagePingAfterBattleText, MSGBOX_AUTOCLOSE
	end

SagePingAfterBattleText::
	.string "We use GHOST-type POKéMON.\p"
	.string "No NORMAL-type attacks can\n"
	.string "harm them!$"

SagePingBeatenText::
	.string "Ah! Well done!$"

SagePingSeenText::
	.string "Can you inflict any damage\n"
	.string "on our POKéMON?$"

EcruteakCity_Gym_EventScript_Grace::
	trainerbattle_single TRAINER_GRACE_HNS, MediumGraceSeenText, MediumGraceBeatenText
	msgbox MediumGraceAfterBattleText, MSGBOX_AUTOCLOSE
	end

MediumGraceAfterBattleText::
	.string "Fine. I'll tell you the secret\n"
	.string "of the shadows.\p"
	.string "The path is right in front of\n"
	.string "your eyes!$"

MediumGraceBeatenText::
	.string "Wha-what?$"

MediumGraceSeenText::
	.string "Stumped by our dark corridors?\n"
	.string "Defeat me if you want a hint!$"

MortyIntroText::
	.string "Good of you to have come.\p"
	.string "Here in ECRUTEAK, POKéMON have\n"
	.string "always been revered.\p"
	.string "It's said that a rainbow-colored\n"
	.string "POKéMON will come down to\l"
	.string "appear before a true TRAINER.\p"
	.string "I believed that tale, so I've\n"
	.string "trained here in secret.\p"
	.string "As a result, I can now see what\n"
	.string "others cannot.\p"
	.string "Just a bit more…\p"
	.string "With a little more, I could see\n"
	.string "a future where I meet the\l"
	.string "rainbow-colored POKéMON.\p"
	.string "You're going to help me reach\n"
	.string "that level!$"

SE_J_EcruteakCity_Gym_hns_EcruteakCity_Gym_EventScript_Morty::
	msgbox MortyIntroText, MSGBOX_NPC
	end

EcruteakCity_Gym_EventScript_Statue::
	lock
	goto_if_set FLAG_JOHTO_BADGE4_GET, EcruteakCity_Gym_EventScript_Statue2
	msgbox EcruteakCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Gym_Text_GymStatue::
	.string "ECRUTEAK CITY POKéMON GYM$"

EcruteakCity_Gym_EventScript_Statue2::
	msgbox EcruteakCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Gym_Text_GymStatueCertified::
	.string "ECRUTEAK CITY POKéMON GYM\p"
	.string "MORTY'S CERTIFIED TRAINERS:\n"
	.string "{PLAYER}$"
