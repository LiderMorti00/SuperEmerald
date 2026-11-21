VioletCity_Gym_hns_MapScripts::
	.byte 0


VioletGym_Text_Falkner_Intro::
	.string "I'm FALKNER, the VIOLET POKéMON\n"
	.string "GYM leader!\p"
	.string "People say you can clip\n"
	.string "FLYING-type POKéMON's wings\p"
	.string "with a jolt of electricity…\n"
	.string "I won't allow such insults to bird\l"
	.string "POKéMON!\p"
	.string "I'll show you the real power\n"
	.string "of the magnificent bird POKéMON!$"

SE_J_VioletCity_Gym_hns_VioletCity_Gym_EventScript_Falkner::
	msgbox VioletGym_Text_Falkner_Intro, MSGBOX_NPC
	end

VioletCity_Gym_EventScript_Abe::
	trainerbattle_single TRAINER_ABE_HNS, VioletGym_Text_BirdKeeperAbe_Seen, VioletGym_Text_BirdKeeperAbe_Beaten
	msgbox VioletGym_Text_BirdKeeperAbe_After, MSGBOX_AUTOCLOSE
	end

VioletGym_Text_BirdKeeperAbe_After::
	.string "This is pathetic, losing to some\n"
	.string "rookie TRAINER…$"

VioletGym_Text_BirdKeeperAbe_Beaten::
	.string "This can't be true!$"

VioletGym_Text_BirdKeeperAbe_Seen::
	.string "Let me see if you are good\n"
	.string "enough to face FALKNER!$"

VioletCity_Gym_EventScript_Rod::
	trainerbattle_single TRAINER_ROD_HNS, VioletGym_Text_BirdKeeperRod_Seen, VioletGym_Text_BirdKeeperRod_Beaten
	msgbox VioletGym_Text_BirdKeeperRod_After, MSGBOX_AUTOCLOSE
	end

VioletGym_Text_BirdKeeperRod_After::
	.string "FALKNER's skills are for real!\p"
	.string "Don't get cocky just because\n"
	.string "you beat me!$"

VioletGym_Text_BirdKeeperRod_Beaten::
	.string "Gaaah!$"

VioletGym_Text_BirdKeeperRod_Seen::
	.string "The keyword is guts!\p"
	.string "Those here are training night and\n"
	.string "day to become bird POKéMON masters.\p"
	.string "Come on!$"

VioletCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_VIOLET_GYM, VioletCity_Gym_EventScript_GymGuy2
	msgbox VioletGym_Text_GymGuide_Intro, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletGym_Text_GymGuide_Intro::
	.string "Hey! What's up? I'm no TRAINER,\n"
	.string "but I can give some advice!\p"
	.string "Believe me! If you believe, a\n"
	.string "championship dream can come true.\p"
	.string "You believe? Then listen.\p"
	.string "FALKNER's ace is a bulky owl\n"
	.string "that loves to eat BERRIES.\p"
	.string "While it's not the strongest,\n"
	.string "it can take a lot of hits.\p"
	.string "You can hurt it with ELECTRIC \n"
	.string "and ROCK-type moves, but watch out\l"
	.string "for MUD-SLAP!\p"
	.string "If you want more help, go visit the\n"
	.string "POKéMON ACADEMY.\p"
	.string "The students there really know\n"
	.string "their stuff!$"

VioletCity_Gym_EventScript_GymGuy2::
	msgbox VioletGym_Text_GymGuide_Win, MSGBOX_DEFAULT
	release
	end	

VioletGym_Text_GymGuide_Win::
	.string "Nice battle! Keep it up,\n"
	.string "and you'll be the CHAMP in no\l"
	.string "time at all!$"

VioletCity_Gym_EventScript_Statue::
	lock
	goto_if_set FLAG_DEFEATED_VIOLET_GYM, VioletCity_Gym_EventScript_Statue2
	msgbox VioletCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_Gym_Text_GymStatue::
	.string "VIOLET CITY POKéMON GYM$"

VioletCity_Gym_EventScript_Statue2::
	msgbox VioletCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_Gym_Text_GymStatueCertified::
	.string "VIOLET CITY POKéMON GYM\p"
	.string "FALKNER'S CERTIFIED TRAINERS:\n"
	.string "{PLAYER}$"
