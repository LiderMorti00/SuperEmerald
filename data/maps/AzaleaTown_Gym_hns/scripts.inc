AzaleaTown_Gym_hns_MapScripts::
	.byte 0


AzaleaTown_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_JOHTO_BADGE2_GET, AzaleaTown_Gym_EventScript_GymGuy2
	msgbox AzaleaTown_Gym_Text_GymGuide, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_Gym_Text_GymGuide::
	.string "Yo, challenger!\p"
	.string "BUGSY's young, but his knowledge\n"
	.string "of bug POKéMON is for real.\p"
	.string "It's going to be tough\n"
	.string "without my advice.\p"
	.string "Let's see… BUGSY's bagworm POKéMON\n"
	.string "knows a move that covers its\l"
	.string "ROCK-type weakness.\p"
	.string "Oh, and don't forget about those\n"
	.string "nasty critical hits! Good luck!$"

AzaleaTown_Gym_EventScript_GymGuy2::
	msgbox AzaleaTown_Gym_Text_GymGuideWin, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_Gym_Text_GymGuideWin::
	.string "Well done! That was a great\n"
	.string "clash of talented young trainers.\p"
	.string "With people like you, the\n"
	.string "future of POKéMON is bright!$"

AzaleaTown_Gym_Text_BugsyIntro::
	.string "I'm BUGSY!\p"
	.string "I never lose when it comes\n"
	.string "to bug POKéMON.\p"
	.string "My research is going to make me the\n"
	.string "authority on bug POKéMON!\p"
	.string "Let me demonstrate all I've\n"
	.string "learned from my studies.$"

SE_J_AzaleaTown_Gym_hns_AzaleaTown_Gym_EventScript_Bugsy::
	msgbox AzaleaTown_Gym_Text_BugsyIntro, MSGBOX_NPC
	end

AzaleaTown_Gym_EventScript_Amy::
	trainerbattle_double TRAINER_AMY_AND_MAY_HNS, AzaleaTown_Gym_Text_TwinsAmyMay1Seen, AzaleaTown_Gym_Text_TwinsAmyMay1Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox AzaleaTown_Gym_Text_TwinsAmyMay1After, MSGBOX_DEFAULT
	release
	end

AzaleaTown_Gym_Text_TwinsAmyMay1After::
	.string "AMY: You're really strong!\p"
	.string "But BUGSY's even stronger!\n"
	.string "His SCYTHER's CUT almost\l"
	.string "always makes critical hits!$"

AzaleaTown_Gym_Text_TwinsAmyMay1Beaten::
	.string "AMY & MAY: Oh, double\n"
	.string "goodness!$"

AzaleaTown_Gym_Text_TwinsAmyMay1Seen::
	.string "AMY: Hi! Are you challenging\n"
	.string "the LEADER? No way!$"

AzaleaTown_Gym_EventScript_May::
	trainerbattle_double TRAINER_AMY_AND_MAY_HNS, AzaleaTown_Gym_Text_TwinsAmyMay2Seen, AzaleaTown_Gym_Text_TwinsAmyMay2Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox AzaleaTown_Gym_Text_TwinsAmyMay2After, MSGBOX_DEFAULT
	release
	end

AzaleaTown_Gym_Text_TwinsAmyMay2After::
	.string "MAY: Our bug POKéMON lost!\n"
	.string "Oh, what a shame.\p"
	.string "BUGSY's won't lose though!\p"
	.string "His PINECO makes short work\n"
	.string "of ROCK-type POKéMON!$"

AzaleaTown_Gym_Text_TwinsAmyMay2Beaten::
	.string "AMY & MAY: Oh, double\n"
	.string "goodness!$"

AzaleaTown_Gym_Text_TwinsAmyMay2Seen::
	.string "MAY: You want to see the\n"
	.string "LEADER? Good luck!\p"
	.string "BUGSY is so strong!\n"
	.string "His SCYTHER's CUT always\l"
	.string "seems to crit!$"

AzaleaTown_Gym_EventScript_Benny::
	trainerbattle_single TRAINER_BENNY_HNS, AzaleaTown_Gym_Text_BugCatcherBennySeen, AzaleaTown_Gym_Text_BugCatcherBennyBeaten
	msgbox AzaleaTown_Gym_Text_BugCatcherBennyAfter, MSGBOX_AUTOCLOSE
	end

AzaleaTown_Gym_Text_BugCatcherBennyAfter::
	.string "POKéMON become stronger\n"
	.string "if they evolve. Really!$"

AzaleaTown_Gym_Text_BugCatcherBennyBeaten::
	.string "Just evolving isn't enough!$"

AzaleaTown_Gym_Text_BugCatcherBennySeen::
	.string "Bug POKéMON evolve young. So they\n"
	.string "get stronger that much faster.$"

AzaleaTown_Gym_EventScript_Josh::
	trainerbattle_single TRAINER_JOSH_HNS, AzaleaTown_Gym_Text_BugCatcherJoshSeen, AzaleaTown_Gym_Text_BugCatcherJoshBeaten
	msgbox AzaleaTown_Gym_Text_BugCatcherJoshAfter, MSGBOX_AUTOCLOSE
	end

AzaleaTown_Gym_Text_BugCatcherJoshAfter::
	.string "I guess I should teach them\n"
	.string "better moves…$"

AzaleaTown_Gym_Text_BugCatcherJoshBeaten::
	.string "Urrgggh!$"

AzaleaTown_Gym_Text_BugCatcherJoshSeen::
	.string "You saved all the SLOWPOKE?\n"
	.string "Whew, you're mighty!\p"
	.string "But my grown-up POKéMON are\n"
	.string "pretty tough too!$"

AzaleaTown_Gym_EventScript_Al::
	trainerbattle_single TRAINER_AL_HNS, AzaleaTown_Gym_Text_BugCatcherAlSeen, AzaleaTown_Gym_Text_BugCatcherAlBeaten
	msgbox AzaleaTown_Gym_Text_BugCatcherAlAfter, MSGBOX_AUTOCLOSE
	end

AzaleaTown_Gym_Text_BugCatcherAlAfter::
	.string "They're so cool, but most girls\n"
	.string "don't like bug POKéMON.\p"
	.string "I don't know why…$"

AzaleaTown_Gym_Text_BugCatcherAlBeaten::
	.string "You proved how tough you are…$"

AzaleaTown_Gym_Text_BugCatcherAlSeen::
	.string "Bug POKéMON are cool and tough!\n"
	.string "I'll prove it to you!$"

AzaleaTown_Gym_EventScript_Statue::
	lock
	goto_if_set FLAG_DEFEATED_AZALEA_TOWN_GYM, AzaleaTown_Gym_EventScript_Statue2
	msgbox AzaleaTown_Gym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_Gym_Text_GymStatue::
	.string "AZALEA POKéMON GYM$"

AzaleaTown_Gym_EventScript_Statue2::
	msgbox AzaleaTown_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_Gym_Text_GymStatueCertified::
	.string "AZALEA TOWN POKéMON GYM\p"
	.string "BUGSY'S CERTIFIED TRAINERS:\n"
	.string "{PLAYER}$"
