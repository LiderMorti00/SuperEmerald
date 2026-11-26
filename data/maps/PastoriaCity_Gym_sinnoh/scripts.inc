	.include "data/maps/PastoriaCity_Gym_sinnoh/gym_metatiles.inc"

PastoriaCity_Gym_sinnoh_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, PastoriaCity_Gym_OnLoad
	.byte 0

@ Super Emerald: two water levels, after Diamond/Platinum's buttons (tools/sfr/gyms/pastoria.py).
@ VAR_TEMP_1: 0 = HIGH (pontoons float at deck height), 1 = LOW (low paths dry, pontoons sunk).
@ The map is drawn HIGH; the level resets to HIGH when the player leaves.
PastoriaCity_Gym_OnLoad::
	call_if_eq VAR_TEMP_1, 1, PastoriaCity_Gym_EventScript_SetWaterLow
	end

PastoriaCity_Gym_EventScript_Drain::
	lockall
	playse SE_SWITCH
	goto_if_eq VAR_TEMP_1, 1, PastoriaCity_Gym_EventScript_AlreadyLow
	setvar VAR_TEMP_1, 1
	waitse
	playse SE_FALL
	call PastoriaCity_Gym_EventScript_SetWaterLow
	special DrawWholeMapView
	waitse
	msgbox PastoriaCity_Gym_Text_Drained, MSGBOX_DEFAULT
	releaseall
	end

PastoriaCity_Gym_EventScript_Fill::
	lockall
	playse SE_SWITCH
	goto_if_eq VAR_TEMP_1, 0, PastoriaCity_Gym_EventScript_AlreadyHigh
	setvar VAR_TEMP_1, 0
	waitse
	playse SE_M_SURF
	call PastoriaCity_Gym_EventScript_SetWaterHigh
	special DrawWholeMapView
	waitse
	msgbox PastoriaCity_Gym_Text_Filled, MSGBOX_DEFAULT
	releaseall
	end

PastoriaCity_Gym_EventScript_AlreadyLow::
	msgbox PastoriaCity_Gym_Text_AlreadyLow, MSGBOX_DEFAULT
	releaseall
	end

PastoriaCity_Gym_EventScript_AlreadyHigh::
	msgbox PastoriaCity_Gym_Text_AlreadyHigh, MSGBOX_DEFAULT
	releaseall
	end

	.include "data/maps/PastoriaCity_Gym_sinnoh/water_levels.inc"

PastoriaCity_Gym_Text_Drained::
	.string "Glug glug glug…\n"
	.string "The water drained away!$"

PastoriaCity_Gym_Text_Filled::
	.string "Whoosh!\n"
	.string "The water rushed back in!$"

PastoriaCity_Gym_Text_AlreadyLow::
	.string "Click!\n"
	.string "The water is already low.$"

PastoriaCity_Gym_Text_AlreadyHigh::
	.string "Click!\n"
	.string "The water is already high.$"

PastoriaCity_Gym_EventScript_Jacky::
	trainerbattle_single TRAINER_WALTER_1_SINNOH, PastoriaCity_Gym_Text_JackyIntro, PastoriaCity_Gym_Text_JackyDefeat
	msgbox PastoriaCity_Gym_Text_JackyPost, MSGBOX_AUTOCLOSE
	end

PastoriaCity_Gym_Text_JackyPost::
	.string "Maybe I'll do like Wake,\p"
	.string "I mean, CRASHER WAKE, and wear the same\n"
	.string "kind of mask.$"

PastoriaCity_Gym_Text_JackyDefeat::
	.string "Wow, TRAINER! You just might be tougher\n"
	.string "than our GYM LEADER!$"

PastoriaCity_Gym_Text_JackyIntro::
	.string "My body isn't the only thing I work on\n"
	.string "toughening up here.\p"
	.string "I also work on my POKéMON and my\n"
	.string "spirit!$"

PastoriaCity_Gym_EventScript_Damian::
	trainerbattle_single TRAINER_WALTER_2_SINNOH, PastoriaCity_Gym_Text_DamianIntro, PastoriaCity_Gym_Text_DamianDefeat
	msgbox PastoriaCity_Gym_Text_DamianPost, MSGBOX_AUTOCLOSE
	end

PastoriaCity_Gym_Text_DamianPost::
	.string "If you were to go around the world, I'm\n"
	.string "sure you'd meet tougher POKéMON.$"

PastoriaCity_Gym_Text_DamianDefeat::
	.string "You! You're truly top-class tough!$"

PastoriaCity_Gym_Text_DamianIntro::
	.string "I've been around the world, going from\n"
	.string "place to place training POKéMON.\p"
	.string "It's this GYM I've chosen to make my\n"
	.string "home!\p"
	.string "You can bet it's tough!$"

PastoriaCity_Gym_EventScript_Caitlyn::
	trainerbattle_single TRAINER_WALTER_3_SINNOH, PastoriaCity_Gym_Text_CaitlynIntro, PastoriaCity_Gym_Text_CaitlynDefeat
	msgbox PastoriaCity_Gym_Text_CaitlynPost, MSGBOX_AUTOCLOSE
	end

PastoriaCity_Gym_Text_CaitlynPost::
	.string "Maybe I'll do like Wake…\p"
	.string "I mean, CRASHER WAKE, and use the same\n"
	.string "kinds of POKéMON.$"

PastoriaCity_Gym_Text_CaitlynDefeat::
	.string "Groan… You're too much.$"

PastoriaCity_Gym_Text_CaitlynIntro::
	.string "I want to become a strong TRAINER like\n"
	.string "CRASHER WAKE!$"

PastoriaCity_Gym_EventScript_Samson::
	trainerbattle_single TRAINER_WALTER_4_SINNOH, PastoriaCity_Gym_Text_SamsonIntro, PastoriaCity_Gym_Text_SamsonDefeat
	msgbox PastoriaCity_Gym_Text_SamsonPost, MSGBOX_AUTOCLOSE
	end

PastoriaCity_Gym_Text_SamsonPost::
	.string "I'm now becalmed like a waveless sea…$"

PastoriaCity_Gym_Text_SamsonDefeat::
	.string "That wave didn't even wash my hands…$"

PastoriaCity_Gym_Text_SamsonIntro::
	.string "Like the raging sea, I crash down and\n"
	.string "wash away everything before me!\p"
	.string "That's just how I roll!$"

PastoriaCity_Gym_EventScript_Erick::
	trainerbattle_single TRAINER_WALTER_5_SINNOH, PastoriaCity_Gym_Text_ErickIntro, PastoriaCity_Gym_Text_ErickDefeat
	msgbox PastoriaCity_Gym_Text_ErickPost, MSGBOX_AUTOCLOSE
	end

PastoriaCity_Gym_Text_ErickPost::
	.string "I figure I got too wrapped up in\n"
	.string "fishing and neglected training.$"

PastoriaCity_Gym_Text_ErickDefeat::
	.string "Being number one in the world doesn't\n"
	.string "mean a thing…$"

PastoriaCity_Gym_Text_ErickIntro::
	.string "I've landed the most fish POKéMON in\n"
	.string "the world. I'm next!$"

PastoriaCity_Gym_EventScript_Walter::
	trainerbattle_single TRAINER_JERRY_1_SINNOH, PastoriaCity_Gym_Text_WalterIntro, PastoriaCity_Gym_Text_WalterDefeat
	msgbox PastoriaCity_Gym_Text_WalterPost, MSGBOX_AUTOCLOSE
	end

PastoriaCity_Gym_Text_WalterPost::
	.string "Yellow drains the water, blue fills\n"
	.string "it back up. Watch what each one does!\p"
	.string "If you lose sight of yourself, that's\n"
	.string "when you're set to lose.$"

PastoriaCity_Gym_Text_WalterDefeat::
	.string "But the kid wins anyway! I'm just\n"
	.string "bowled over!$"

PastoriaCity_Gym_Text_WalterIntro::
	.string "I wield the stupendous power of water!\n"
	.string "Don't think you can win!$"

PastoriaCity_Gym_EventScript_Leader::
	goto_if_set FLAG_SYS_GAME_CLEAR, PastoriaCity_Gym_EventScript_SNRematch
	trainerbattle_single TRAINER_JACKI_5_SINNOH, PastoriaCity_Gym_Text_LeaderIntro, PastoriaCity_Gym_Text_LeaderDefeat, PastoriaCity_Gym_EventScript_LeaderDefeated, NO_MUSIC
	goto_if_unset FLAG_RECEIVED_ITEM_TM55_FROM_WAKE, PastoriaCity_Gym_EventScript_GiveTM
	msgbox PastoriaCity_Gym_Text_LeaderPostBattle, MSGBOX_DEFAULT
	release
	end

PastoriaCity_Gym_Text_LeaderPostBattle::
	.string "The styles of battling and winning are\n"
	.string "as widely varied as TRAINERS are.\p"
	.string "Do you want to know how I battle? I\n"
	.string "battle so I can say I had fun at\p"
	.string "the end, whether I win or lose!$"

PastoriaCity_Gym_EventScript_GiveTM::
	giveitem ITEM_TM55
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_ITEM_TM55_FROM_WAKE
	msgbox PastoriaCity_Gym_Text_ExplainTM, MSGBOX_DEFAULT
	release
	end

PastoriaCity_Gym_Text_ExplainTM::
	.string "That TM55 contains the move BRINE.\p"
	.string "It inflicts double the damage on\n"
	.string "targets with less than half their\p"
	.string "HP left.\p"
	.string "Use it to end battles decisively!$"

PastoriaCity_Gym_EventScript_LeaderDefeated::
	message PastoriaCity_Gym_Text_ReceivedBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox PastoriaCity_Gym_Text_ExplainBadge, MSGBOX_DEFAULT
	setflag FLAG_SINNOH_BADGE4_GET
	settrainerflag TRAINER_WALTER_1_SINNOH
	settrainerflag TRAINER_WALTER_2_SINNOH
	settrainerflag TRAINER_WALTER_3_SINNOH
	settrainerflag TRAINER_WALTER_4_SINNOH
	settrainerflag TRAINER_WALTER_5_SINNOH
	settrainerflag TRAINER_JERRY_1_SINNOH
	goto PastoriaCity_Gym_EventScript_GiveTM

PastoriaCity_Gym_Text_ExplainBadge::
	.string "You need that Fen BADGE to use the\n"
	.string "hidden move SURF outside of battle.\p"
	.string "This is a special reward from me in\n"
	.string "recognition of your team's power.$"

PastoriaCity_Gym_Text_ReceivedBadge::
	.string "{PLAYER} received the Fen BADGE from\n"
	.string "Wake!$"

PastoriaCity_Gym_Text_LeaderDefeat::
	.string "It seems the undertow pulled me\n"
	.string "under…\p"
	.string "But I had a great time battling with\n"
	.string "you!\p"
	.string "You've earned this!$"

PastoriaCity_Gym_Text_LeaderIntro::
	.string "Welcome! I don't get challenged very\n"
	.string "often!\p"
	.string "The glory you are now beholding is the\n"
	.string "PASTORIA GYM LEADER!\p"
	.string "That's right, I'm CRASHER WAKE!\p"
	.string "My POKéMON were toughened up by\n"
	.string "stormy white waters!\p"
	.string "They'll take everything you can throw\n"
	.string "at them and then pull you under!\p"
	.string "Victory will be ours! Come on, let's get\n"
	.string "it done!$"

PastoriaCity_Gym_EventScript_SNRematch::
	lock
	faceplayer
	msgbox PastoriaCity_Gym_EventScript_SNRematch_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PastoriaCity_Gym_EventScript_SNRematch_No
	msgbox PastoriaCity_Gym_EventScript_SNRematch_Go, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_KATELYN_3_SINNOH, PastoriaCity_Gym_EventScript_SNRematch_Defeat
	msgbox PastoriaCity_Gym_EventScript_SNRematch_After, MSGBOX_DEFAULT
	release
	end

PastoriaCity_Gym_EventScript_SNRematch_After::
	.string "That was a great battle! Come back\n"
	.string "anytime for another match!$"

PastoriaCity_Gym_EventScript_SNRematch_Defeat::
	.string "Amazing… You really are the CHAMPION!$"

PastoriaCity_Gym_EventScript_SNRematch_Go::
	.string "Then I won't hold back this time!$"

PastoriaCity_Gym_EventScript_SNRematch_No::
	msgbox PastoriaCity_Gym_EventScript_SNRematch_NoT, MSGBOX_DEFAULT
	release
	end

PastoriaCity_Gym_EventScript_SNRematch_NoT::
	.string "Come back whenever you're ready!$"

PastoriaCity_Gym_EventScript_SNRematch_Ask::
	.string "WAKE: You became the CHAMPION! Welcome\n"
	.string "back!\p"
	.string "I've been training even harder since\n"
	.string "our last battle.\p"
	.string "Will you battle me again?$"

PastoriaCity_Gym_EventScript_PtGymGuide::
	lock
	faceplayer
	goto_if_set FLAG_SINNOH_BADGE4_GET, PastoriaCity_Gym_EventScript_PtGymGuideAfter
	msgbox PastoriaCity_Gym_Text_PtGymGuide, MSGBOX_DEFAULT
	msgbox PastoriaCity_Gym_Text_SNGuideInfo, MSGBOX_DEFAULT
	release
	end

PastoriaCity_Gym_Text_SNGuideInfo::
	.string "Let me tell you about this GYM!\p"
	.string "The GYM LEADER is CRASHER WAKE, the\n"
	.string "masked wrestler who is a master of\l"
	.string "Water-type POKéMON.\p"
	.string "He uses GYARADOS, QUAGSIRE and\n"
	.string "FLOATZEL.\p"
	.string "Water types are weak to Electric and\n"
	.string "Grass moves!\p"
	.string "This GYM is a water plant. The yellow\n"
	.string "buttons drain the tanks and the blue\l"
	.string "ones fill them back up.\p"
	.string "When the water is high, the orange\n"
	.string "floats rise and you can cross them.\l"
	.string "When it's low, the paths below dry out.\p"
	.string "The gauges on the walls show the\n"
	.string "level. Switch it to reach WAKE!$"

PastoriaCity_Gym_Text_PtGymGuide::
	.string "The GYM LEADER WAKE… Uh, I mean\n"
	.string "CRASHER WAKE, is a master of\p"
	.string "Water-type POKéMON.\p"
	.string "I'd say you've got guts if you try to\n"
	.string "face down Water types with Fire-\p"
	.string "or Ground-type POKéMON!\p"
	.string "But that part I'll leave up to you! Go\n"
	.string "and have some good battles!$"

PastoriaCity_Gym_EventScript_PtGymGuideAfter::
	msgbox PastoriaCity_Gym_Text_PtGymGuideAfter, MSGBOX_DEFAULT
	release
	end

PastoriaCity_Gym_Text_PtGymGuideAfter::
	.string "Oh! {PLAYER}! You've beaten the GYM\n"
	.string "LEADER!\p"
	.string "So, how was it?\p"
	.string "Did you enjoy your battle against\n"
	.string "Wake… I mean CRASHER WAKE?\p"
	.string "Sure, winning is important, but don't\n"
	.string "forget to have fun, too!\p"
	.string "I think Wake… I mean CRASHER WAKE,\n"
	.string "showed you what I mean by fun.$"

PastoriaCity_Gym_EventScript_PtGymStatue::
	lockall
	goto_if_set FLAG_SINNOH_BADGE4_GET, PastoriaCity_Gym_EventScript_PtGymStatueWon
	msgbox PastoriaCity_Gym_Text_PtGymStatue, MSGBOX_DEFAULT
	releaseall
	end

PastoriaCity_Gym_Text_PtGymStatue::
	.string "PASTORIA CITY POKéMON GYM\n"
	.string "LEADER: CRASHER WAKE$"

PastoriaCity_Gym_EventScript_PtGymStatueWon::
	msgbox PastoriaCity_Gym_Text_PtGymStatueWon, MSGBOX_DEFAULT
	releaseall
	end

PastoriaCity_Gym_Text_PtGymStatueWon::
	.string "PASTORIA CITY POKéMON GYM\n"
	.string "LEADER: CRASHER WAKE\p"
	.string "Certified TRAINERS:\n"
	.string "{PLAYER}$"
