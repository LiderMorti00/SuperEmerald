GoldenrodCity_Gym_hns_MapScripts::
	.byte 0


GoldenrodCity_Gym_EventScript_Gym_Guy::
	lock
	faceplayer
	goto_if_set FLAG_JOHTO_BADGE3_GET, GoldenrodCity_Gym_EventScript_Gym_Guy_After
	msgbox GoldenrodCity_Gym_Text_GymGuide, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Gym_Text_GymGuide::
    .string "Yo! CHAMP in making!\p"
    .string "This GYM is home to WHITNEY, the\n"
    .string "master of NORMAL-type POKéMON.\p"
    .string "Be cautious of her cute team.\p"
    .string "Some of the POKéMON in this gym\n"
    .string "have the newly discovered FAIRY\l"
    .string "type as well.\p"
    .string "Check ROUTE 34 if you need a\n"
    .string "FIGHTING-type or POISON-type.$"

GoldenrodCity_Gym_EventScript_Gym_Guy_After::
	msgbox GoldenrodCity_Gym_Text_GymGuideWin, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Gym_Text_GymGuideWin::
    .string "You won? Great! I was busy admiring\n"
    .string "the ladies here.$"

GoldenrodCity_Gym_EventScript_Carrie::
	trainerbattle_single TRAINER_CARRIE_HNS, GoldenrodCity_Gym_Text_LassCarrieSeen, GoldenrodCity_Gym_Text_LassCarrieBeaten
	msgbox GoldenrodCity_Gym_Text_LassCarrieAfter, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_Gym_Text_LassCarrieAfter::
    .string "Do my POKéMON think I'm cute?$"

GoldenrodCity_Gym_Text_LassCarrieBeaten::
    .string "Darn… I thought you were weak…$"

GoldenrodCity_Gym_Text_LassCarrieSeen::
    .string "Don't let my POKéMON's cute looks\n"
    .string "fool you.\p"
    .string "They can whip you!$"

GoldenrodCity_Gym_EventScript_Victoria::
	trainerbattle_single TRAINER_VICTORIA_HNS, GoldenrodCity_Gym_Text_BeautyVictoriaSeen, GoldenrodCity_Gym_Text_BeautyVictoriaBeaten
	msgbox GoldenrodCity_Gym_Text_BeautyVictoriaAfter, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_Gym_Text_BeautyVictoriaAfter::
    .string "Wow, you must be good to beat me!\n"
    .string "Keep it up!$"

GoldenrodCity_Gym_Text_BeautyVictoriaBeaten::
    .string "Let's see… Oops, it's over?$"

GoldenrodCity_Gym_Text_BeautyVictoriaSeen::
    .string "Oh, you are a cute little trainer!\p"
    .string "I like you, but I won't hold back!$"

GoldenrodCity_Gym_Text_WhitneyBefore::
    .string "Hi! I'm WHITNEY!\p"
    .string "Everyone was into POKéMON, so I got\n"
    .string "into it too!\p"
    .string "POKéMON are super-cute!\p"
    .string "You want to battle? I'm warning\n"
    .string "you- I'm good!$"

SE_J_GoldenrodCity_Gym_hns_GoldenrodCity_Gym_EventScript_Whitney::
	msgbox GoldenrodCity_Gym_Text_WhitneyBefore, MSGBOX_NPC
	end

GoldenrodCity_Gym_EventScript_Samantha::
	trainerbattle_single TRAINER_SAMANTHA_HNS, GoldenrodCity_Gym_Text_BeautySamanthaSeen, GoldenrodCity_Gym_Text_BeautySamanthaBeaten
	msgbox GoldenrodCity_Gym_Text_BeautySamanthaAfter, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_Gym_Text_BeautySamanthaAfter::
    .string "I taught MEOWTH moves for taking on\n"
    .string "any type…$"

GoldenrodCity_Gym_Text_BeautySamanthaBeaten::
    .string "No! Oh, MEOWTH, I'm so sorry!$"

GoldenrodCity_Gym_Text_BeautySamanthaSeen::
    .string "Give it your best shot, or I'll take\n"
    .string "you down!$"

GoldenrodCity_Gym_EventScript_Bridget::
	trainerbattle_single TRAINER_BRIDGET_HNS, GoldenrodCity_Gym_Text_LassBridgetSeen, GoldenrodCity_Gym_Text_LassBridgetBeaten
	msgbox GoldenrodCity_Gym_Text_LassBridgetAfter, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_Gym_Text_LassBridgetAfter::
    .string "I'm trying to beat WHITNEY, but…\n"
    .string "It's depressing.\p"
    .string "I'm okay! If I lose, I'll just try\n"
    .string "harder next time!$"

GoldenrodCity_Gym_Text_LassBridgetBeaten::
    .string "Oh, no, no, no!$"

GoldenrodCity_Gym_Text_LassBridgetSeen::
    .string "I like cute POKéMON better than\n"
    .string "strong POKéMON.\p"
    .string "But I have strong and cute POKéMON!$"

GoldenrodCity_Gym_EventScript_Statue::
	lock
	goto_if_set FLAG_DEFEATED_GOLDENROD_CITY_GYM, GoldenrodCity_Gym_EventScript_Statue2
	msgbox GoldenrodCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Gym_Text_GymStatue::
	.string "GOLDENROD POKéMON GYM$"

GoldenrodCity_Gym_EventScript_Statue2::
	msgbox GoldenrodCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Gym_Text_GymStatueCertified::
	.string "GOLDENROD TOWN POKéMON GYM\p"
	.string "WHITNEY'S CERTIFIED TRAINERS:\n"
	.string "{PLAYER}$"
