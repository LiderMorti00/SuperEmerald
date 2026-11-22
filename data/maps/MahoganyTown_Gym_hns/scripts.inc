MahoganyTown_Gym_hns_MapScripts::
	.byte 0


MahoganyTown_Gym_EventScript_Clarissa::
	trainerbattle_single TRAINER_CLARISSA_HNS, MahoganyTown_Gym_Text_SkierClarissaSeen, MahoganyTown_Gym_Text_SkierClarissaBeaten
	msgbox MahoganyTown_Gym_Text_SkierClarissaAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_Text_SkierClarissaAfter::
    .string "I shouldn't have been bragging\n"
    .string "about my skiing…$"

MahoganyTown_Gym_Text_SkierClarissaBeaten::
    .string "No! You made me wipe out!$"

MahoganyTown_Gym_Text_SkierClarissaSeen::
    .string "Check out my parallel turn!$"

MahoganyTown_Gym_EventScript_Brad::
	trainerbattle_single TRAINER_BRAD_HNS, MahoganyTown_Gym_Text_BoarderBradSeen, MahoganyTown_Gym_Text_BoarderBradBeaten
	msgbox MahoganyTown_Gym_Text_BoarderBradAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_Text_BoarderBradAfter::
    .string "This GYM is great.\n"
    .string "I love boarding with my\l"
    .string "POKéMON!$"

MahoganyTown_Gym_Text_BoarderBradBeaten::
    .string "Do you see how serious we are?$"

MahoganyTown_Gym_Text_BoarderBradSeen::
    .string "This GYM has a slippery floor.\p"
    .string "It's fun, isn't it?\p"
    .string "But hey--we're not playing\n"
    .string "games here!$"

MahoganyTown_Gym_EventScript_Ronald::
	trainerbattle_single TRAINER_RONALD_HNS, MahoganyTown_Gym_Text_BoarderRonaldSeen, MahoganyTown_Gym_Text_BoarderRonaldBeaten
	msgbox MahoganyTown_Gym_Text_BoarderRonaldAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_Text_BoarderRonaldAfter::
    .string "I think there's a move a\n"
    .string "POKéMON can use while it's\l"
    .string "frozen.$"

MahoganyTown_Gym_Text_BoarderRonaldBeaten::
    .string "Darn. I couldn't do a thing.$"

MahoganyTown_Gym_Text_BoarderRonaldSeen::
    .string "I'll freeze your POKéMON,\n"
    .string "so you can't do a thing!$"

MahoganyTown_Gym_EventScript_Douglas::
	trainerbattle_single TRAINER_DOUGLAS_HNS, MahoganyTown_Gym_Text_BoarderDouglasSeen, MahoganyTown_Gym_Text_BoarderDouglasBeaten
	msgbox MahoganyTown_Gym_Text_BoarderDouglasAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_Text_BoarderDouglasAfter::
    .string "The secret behind PRYCE's power…\p"
    .string "He meditates under a waterfall\n"
    .string "daily to strengthen his mind\l"
    .string "and body.$"

MahoganyTown_Gym_Text_BoarderDouglasBeaten::
    .string "OK. I'll tell you PRYCE's secret.$"

MahoganyTown_Gym_Text_BoarderDouglasSeen::
    .string "I know PRYCE's secret.$"

MahoganyTown_Gym_EventScript_Roxanne::
	trainerbattle_single TRAINER_ROXANNE_HNS, MahoganyTown_Gym_Text_SkierRoxanneSeen, MahoganyTown_Gym_Text_SkierRoxanneBeaten
	msgbox MahoganyTown_Gym_Text_SkierRoxanneAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_Text_SkierRoxanneAfter::
    .string "If you don't skate with precision,\n"
    .string "you won't get far in this GYM.$"

MahoganyTown_Gym_Text_SkierRoxanneBeaten::
    .string "I wouldn't lose to you in skiing!$"

MahoganyTown_Gym_Text_SkierRoxanneSeen::
    .string "To get to PRYCE, our GYM LEADER,\n"
    .string "you need to think before you skate.$"

MahoganyTown_Gym_Text_PryceIntro::
    .string "POKéMON have many experiences\n"
    .string "in their lives, just like we do.\p"
    .string "I, too, have seen and suffered\n"
    .string "much in my life.\p"
    .string "Since I am your elder, let me\n"
    .string "show you what I mean.\p"
    .string "I have been with POKéMON since\n"
    .string "before you were born.\p"
    .string "I do not lose easily.\p"
    .string "I, PRYCE--the winter TRAINER--\n"
    .string "shall demonstrate my power!$"

SE_J_MahoganyTown_Gym_hns_MahoganyTown_Gym_EventScript_Pryce::
	msgbox MahoganyTown_Gym_Text_PryceIntro, MSGBOX_NPC
	end

MahoganyTown_GymEventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_JOHTO_BADGE7_GET, MahoganyTown_Gym_EventScript_GymGuy2
	msgbox MahoganyTown_Gym_Text_Guide, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_Gym_Text_Guide::
    .string "PRYCE is a veteran who has\n"
    .string "trained POKéMON for some 50 years.\p"
    .string "He's got a solid lineup of\n"
    .string "POKéMON to cover whatever\l"
    .string "you bring his way.\p"
    .string "Thinking of using FIRE? Watch out\n"
    .string "for DEWGONG and WALREIN's SURF!$"

MahoganyTown_Gym_EventScript_GymGuy2::
	msgbox MahoganyTown_Gym_Text_GuideWin, MSGBOX_DEFAULT
	release
	end	

MahoganyTown_Gym_Text_GuideWin::
    .string "PRYCE is something, but you're\n"
    .string "something else!\p"
    .string "That was a hot battle that\n"
    .string "bridged the generation gap!$"

MahoganyTown_Gym_EventScript_Statue::
	lock
	goto_if_set FLAG_JOHTO_BADGE7_GET,  MahoganyTown_Gym_EventScript_Statue2
	msgbox MahoganyTown_Gym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_Gym_Text_GymStatue::
	.string "MAHOGANY TOWN POKéMON GYM$"

MahoganyTown_Gym_EventScript_Statue2::
	msgbox MahoganyTown_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_Gym_Text_GymStatueCertified::
	.string "MAHOGANY TOWN POKéMON GYM\p"
	.string "PRYCE'S CERTIFIED TRAINERS:\n"
	.string "{PLAYER}$"
