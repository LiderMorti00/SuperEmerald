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
	goto_if_set FLAG_JOHTO_BADGE1_GET, VioletCity_Gym_EventScript_GymGuy2
	msgbox VioletGym_Text_GymGuide_Intro, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletGym_Text_GymGuide_Intro::
	.string "FALKNER's birds can swoop in fast.\p"
	.string "Save an ELECTRIC or ROCK move for\n"
	.string "his PIDGEOT. It's holding a BERRY!$"

VioletCity_Gym_EventScript_GymGuy2::
	msgbox VioletGym_Text_GymGuide_Win, MSGBOX_DEFAULT
	release
	end	

VioletGym_Text_GymGuide_Win::
	.string "You grounded FALKNER's team!\p"
	.string "That ZEPHYRBADGE looks good on\n"
	.string "you, {PLAYER}.$"

VioletCity_Gym_EventScript_Statue::
	lock
	goto_if_set FLAG_JOHTO_BADGE1_GET, VioletCity_Gym_EventScript_Statue2
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
