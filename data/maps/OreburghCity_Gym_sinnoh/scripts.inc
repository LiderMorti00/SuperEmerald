OreburghCity_Gym_sinnoh_MapScripts::
	.byte 0


OreburghCity_Gym_Text_RoarkPost::
	.string "In this region of SINNOH, there are\n"
	.string "seven other GYM LEADERS.\p"
	.string "I should warn you--they're a lot\n"
	.string "tougher than I am!$"

SE_S_OreburghCity_Gym_OreburghCity_Gym_EventScript_Roark::
	msgbox OreburghCity_Gym_Text_RoarkPost, MSGBOX_NPC
	end

OreburghCity_Gym_EventScript_Jonathon::
	trainerbattle_single TRAINER_JOSH_SINNOH, OreburghCity_Gym_Text_JonathonIntro, OreburghCity_Gym_Text_JonathonDefeat
	msgbox OreburghCity_Gym_Text_JonathonPost, MSGBOX_AUTOCLOSE
	end

OreburghCity_Gym_Text_JonathonPost::
	.string "You should go whichever way you want,\n"
	.string "shortcut or the long way!$"

OreburghCity_Gym_Text_JonathonDefeat::
	.string "Now I understand why you decided to\n"
	.string "battle with me.$"

OreburghCity_Gym_Text_JonathonIntro::
	.string "You avoided the long way around?\n"
	.string "Let's see why you'd do that!$"

OreburghCity_Gym_EventScript_Darius::
	trainerbattle_single TRAINER_TOMMY_SINNOH, OreburghCity_Gym_Text_DariusIntro, OreburghCity_Gym_Text_DariusDefeat
	msgbox OreburghCity_Gym_Text_DariusPost, MSGBOX_AUTOCLOSE
	end

OreburghCity_Gym_Text_DariusPost::
	.string "One day, I'm going to become a tough\n"
	.string "TRAINER like you.$"

OreburghCity_Gym_Text_DariusDefeat::
	.string "Gggh… This is humiliating!$"

OreburghCity_Gym_Text_DariusIntro::
	.string "Only those who want to win can\n"
	.string "challenge a POKéMON GYM!$"

OreburghCity_Gym_EventScript_Guide::
	lock
	faceplayer
	goto_if_set FLAG_SINNOH_BADGE1_GET, OreburghCity_Gym_EventScript_GuideWon
	msgbox OreburghCity_Gym_Text_Guide, MSGBOX_DEFAULT
	msgbox OreburghCity_Gym_Text_SNGuideInfo, MSGBOX_DEFAULT
	release
	end

OreburghCity_Gym_Text_SNGuideInfo::
	.string "Let me tell you about this GYM!\p"
	.string "The GYM LEADER is ROARK, the\n"
	.string "Rock-Loving Honor Student. He is also\l"
	.string "the young boss of the OREBURGH MINE.\p"
	.string "He uses Rock-type POKéMON like\n"
	.string "GEODUDE, ONIX and his partner\l"
	.string "CRANIDOS.\p"
	.string "Rock types are weak to Water, Grass,\n"
	.string "Fighting, Ground and Steel moves!\p"
	.string "His TRAINERS wait along the path. Beat\n"
	.string "them and you can walk right up to\l"
	.string "ROARK. Go for it!$"

OreburghCity_Gym_Text_Guide::
	.string "Howdy! How's it going, CHAMP-to-be?\p"
	.string "That's what I said to a really\n"
	.string "impatient boy earlier, too.\p"
	.string "The GYM LEADER is a user of Rock-type\n"
	.string "POKéMON.\p"
	.string "Well, listen. Rock-type POKéMON really\n"
	.string "hate water, all right?\p"
	.string "They're also weak to Grass-type moves.\p"
	.string "Gee, they sure have weaknesses!\p"
	.string "But don't think it will be easy.\p"
	.string "You don't get to be a GYM LEADER\n"
	.string "without covering for weaknesses.\p"
	.string "Going after a Rock-type POKéMON with\n"
	.string "a Fire-type POKéMON won't be\p"
	.string "easy, either.\p"
	.string "That's all the advice I can give.\n"
	.string "Thanks for listening!$"

OreburghCity_Gym_EventScript_GuideWon::
	msgbox OreburghCity_Gym_Text_GuideWon, MSGBOX_DEFAULT
	release
	end

OreburghCity_Gym_Text_GuideWon::
	.string "Oh! {PLAYER}! You've taken care of the\n"
	.string "GYM LEADER!\p"
	.string "So, did my advice come in handy or\n"
	.string "what?\p"
	.string "If my advice was useful, it'd be great\n"
	.string "if you'd become my fan!$"

OreburghCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_SINNOH_BADGE1_GET, OreburghCity_Gym_EventScript_GymStatuePostVictory
	msgbox OreburghCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

OreburghCity_Gym_Text_GymStatue::
	.string "OREBURGH CITY POKéMON GYM\n"
	.string "LEADER: ROARK\p"
	.string "Certified TRAINERS:\n"
	.string "{RIVAL}$"

OreburghCity_Gym_EventScript_GymStatuePostVictory::
	msgbox OreburghCity_Gym_Text_GymStatuePlayerWon, MSGBOX_DEFAULT
	releaseall
	end

OreburghCity_Gym_Text_GymStatuePlayerWon::
	.string "OREBURGH CITY POKéMON GYM\n"
	.string "LEADER: ROARK\p"
	.string "Certified TRAINERS:\n"
	.string "{RIVAL}\n"
	.string "{PLAYER}$"
