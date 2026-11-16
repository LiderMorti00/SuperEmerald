FloaromaMeadow_sinnoh_MapScripts::
	.byte 0


SN_HoneyTree_Text_Wait::
	.string "The bark is slathered with Honey...$"

FloaromaMeadow_EventScript_HoneyMan::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_MEADOW_GRUNTS, FloaromaMeadow_EventScript_HoneyManNormal
	msgbox FloaromaMeadow_Text_HoneyHelp, MSGBOX_DEFAULT
	release
	end

FloaromaMeadow_Text_HoneyHelp::
	.string "Help! These people want to take\n"
	.string "all my HONEY!$"

FloaromaMeadow_EventScript_HoneyManNormal::
	msgbox FloaromaMeadow_Text_HoneyInfo, MSGBOX_DEFAULT
	release
	end

FloaromaMeadow_Text_HoneyInfo::
	.string "Slather that Honey on a sweet-smelling\n"
	.string "tree. It might attract POKéMON.$"

FloaromaMeadow_EventScript_Grunts::
	lock
	faceplayer
	msgbox FloaromaMeadow_Text_Grunt1Intro, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_RANDALL_SINNOH, FloaromaMeadow_Text_Grunt1Defeat
	msgbox FloaromaMeadow_Text_Grunt2Intro, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_PARKER_SINNOH, FloaromaMeadow_Text_Grunt2Defeat
	msgbox FloaromaMeadow_Text_GruntsFlee, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MEADOW_GRUNT_1
	removeobject LOCALID_MEADOW_GRUNT_2
	setflag FLAG_HIDE_MEADOW_GRUNTS
	fadescreenswapbuffers FADE_FROM_BLACK
	applymovement LOCALID_MEADOW_HONEY_MAN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox FloaromaMeadow_Text_HoneyThanks, MSGBOX_DEFAULT
	giveitem ITEM_ULTRA_BALL
	msgbox FloaromaMeadow_Text_HoneyGift, MSGBOX_DEFAULT
	giveitem ITEM_HONEY, 10
	msgbox FloaromaMeadow_Text_HoneyInfo, MSGBOX_DEFAULT
	release
	end

FloaromaMeadow_Text_HoneyGift::
	.string "And please, take some of my HONEY\n"
	.string "as thanks!$"

FloaromaMeadow_Text_HoneyThanks::
	.string "Oh, what’s this thing? They seem to\n"
	.string "have forgotten it...\p"
	.string "It’s a Works Key... It must be for the\n"
	.string "Valley Windworks!\p"
	.string "It’s of no use to me. You may as well\n"
	.string "have it.\p"
	.string "Thank you! You surely saved me.\p"
	.string "Those goons were trying to rob me of\n"
	.string "my sweet, sweet Honey.\p"
	.string "They sure were weird, though. You saw\n"
	.string "how they were dressed.\p"
	.string "What they were saying didn’t make a\n"
	.string "whole lot of sense, either.\p"
	.string "Oh! I need to thank you! This sweet,\n"
	.string "sweet Honey!\p"
	.string "Go on, take a whole lot!$"

FloaromaMeadow_Text_GruntsFlee::
	.string "Grunt 1: This brat’s tough! Like, really,\n"
	.string "really tough!\p"
	.string "Tougher than I can put into words, and\n"
	.string "I know a lot of words!\p"
	.string "We’re done for here... Let’s get back to\n"
	.string "the Valley Windworks.$"

FloaromaMeadow_Text_Grunt2Defeat::
	.string "No way...$"

FloaromaMeadow_Text_Grunt2Intro::
	.string "Grunt 2: I’m up next! Heheheh...\p"
	.string "Battling you right after my cohort\n"
	.string "weakened you gives me the edge!$"

FloaromaMeadow_Text_Grunt1Defeat::
	.string "Grunt 1: This is so lame... They’re going\n"
	.string "to dock my pay!$"

FloaromaMeadow_Text_Grunt1Intro::
	.string "Grunt 1: Enough arguing! Hand over\n"
	.string "that sweet Honey!\p"
	.string "Grunt 2: Do as we say! Team Galactic\n"
	.string "will have that Honey!\p"
	.string "We must have it to attract POKéMON in\n"
	.string "great numbers!\p"
	.string "Grunt 1: Hey! This kid is a witness!\n"
	.string "What’ll we do?\p"
	.string "Grunt 2: We don’t need the brat running\n"
	.string "off to get help...\p"
	.string "The solution’s simple! We ensure the\n"
	.string "brat stays quiet!$"

SE_S_FloaromaMeadow_FloaromaMeadow_EventScript_SNHoneyTree::
	msgbox SN_HoneyTree_Text_Wait, MSGBOX_NPC
	end
