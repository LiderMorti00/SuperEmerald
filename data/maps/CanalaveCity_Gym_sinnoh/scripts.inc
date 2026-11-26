	.include "data/maps/CanalaveCity_Gym_sinnoh/gym_metatiles.inc"

CanalaveCity_Gym_sinnoh_MapScripts::
	.byte 0

@ Super Emerald: freight lifts. Each numbered pad is a coord event (VAR_TEMP_0 is always 0);
@ the ride asks YES/NO and warps inside the gym to the pad with the same number, so the
@ same pad always rides back.
CanalaveCity_Gym_EventScript_Lift1Up::
	lockall
	msgbox CanalaveCity_Gym_Text_Lift1Up, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CanalaveCity_Gym_EventScript_LiftStay
	call CanalaveCity_Gym_EventScript_LiftRide
	warpsilent MAP_CANALAVE_CITY_GYM_SINNOH, 9, 16
	waitstate
	end

CanalaveCity_Gym_EventScript_Lift1Down::
	lockall
	msgbox CanalaveCity_Gym_Text_Lift1Down, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CanalaveCity_Gym_EventScript_LiftStay
	call CanalaveCity_Gym_EventScript_LiftRide
	warpsilent MAP_CANALAVE_CITY_GYM_SINNOH, 0, 16
	waitstate
	end

CanalaveCity_Gym_EventScript_Lift2Up::
	lockall
	msgbox CanalaveCity_Gym_Text_Lift2Up, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CanalaveCity_Gym_EventScript_LiftStay
	call CanalaveCity_Gym_EventScript_LiftRide
	warpsilent MAP_CANALAVE_CITY_GYM_SINNOH, 17, 7
	waitstate
	end

CanalaveCity_Gym_EventScript_Lift2Down::
	lockall
	msgbox CanalaveCity_Gym_Text_Lift2Down, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CanalaveCity_Gym_EventScript_LiftStay
	call CanalaveCity_Gym_EventScript_LiftRide
	warpsilent MAP_CANALAVE_CITY_GYM_SINNOH, 0, 11
	waitstate
	end

CanalaveCity_Gym_EventScript_Lift3Up::
	lockall
	msgbox CanalaveCity_Gym_Text_Lift3Up, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CanalaveCity_Gym_EventScript_LiftStay
	call CanalaveCity_Gym_EventScript_LiftRide
	warpsilent MAP_CANALAVE_CITY_GYM_SINNOH, 0, 3
	waitstate
	end

CanalaveCity_Gym_EventScript_Lift3Down::
	lockall
	msgbox CanalaveCity_Gym_Text_Lift3Down, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CanalaveCity_Gym_EventScript_LiftStay
	call CanalaveCity_Gym_EventScript_LiftRide
	warpsilent MAP_CANALAVE_CITY_GYM_SINNOH, 0, 7
	waitstate
	end

CanalaveCity_Gym_EventScript_LiftRide::
	playse SE_ELEVATOR
	waitse
	return

CanalaveCity_Gym_EventScript_LiftStay::
	releaseall
	end

CanalaveCity_Gym_EventScript_Panel1::
	msgbox CanalaveCity_Gym_Text_Panel1, MSGBOX_SIGN
	end

CanalaveCity_Gym_EventScript_Panel2::
	msgbox CanalaveCity_Gym_Text_Panel2, MSGBOX_SIGN
	end

CanalaveCity_Gym_EventScript_Panel3::
	msgbox CanalaveCity_Gym_Text_Panel3, MSGBOX_SIGN
	end

CanalaveCity_Gym_Text_Lift1Up::
	.string "LIFT 1: TEST PLATFORM.\n"
	.string "Ride it up?$"

CanalaveCity_Gym_Text_Lift1Down::
	.string "LIFT 1: GROUND FLOOR.\n"
	.string "Ride it back down?$"

CanalaveCity_Gym_Text_Lift2Up::
	.string "LIFT 2: MAIN CATWALK.\n"
	.string "Ride it up?$"

CanalaveCity_Gym_Text_Lift2Down::
	.string "LIFT 2: GROUND FLOOR.\n"
	.string "Ride it back down?$"

CanalaveCity_Gym_Text_Lift3Up::
	.string "LIFT 3: LEADER'S FLOOR.\n"
	.string "Ride it up?$"

CanalaveCity_Gym_Text_Lift3Down::
	.string "LIFT 3: MAIN CATWALK.\n"
	.string "Ride it back down?$"

CanalaveCity_Gym_Text_Panel1::
	.string "LIFT 1\n"
	.string "GROUND FLOOR {UP_ARROW}{DOWN_ARROW} TEST PLATFORM$"

CanalaveCity_Gym_Text_Panel2::
	.string "LIFT 2\n"
	.string "GROUND FLOOR {UP_ARROW}{DOWN_ARROW} MAIN CATWALK$"

CanalaveCity_Gym_Text_Panel3::
	.string "LIFT 3\n"
	.string "MAIN CATWALK {UP_ARROW}{DOWN_ARROW} LEADER'S FLOOR$"


CanalaveCity_Gym_EventScript_David::
	trainerbattle_single TRAINER_JERRY_3_SINNOH, CanalaveCity_Gym_Text_DavidIntro, CanalaveCity_Gym_Text_DavidDefeat
	msgbox CanalaveCity_Gym_Text_DavidPost, MSGBOX_AUTOCLOSE
	end

CanalaveCity_Gym_Text_DavidPost::
	.string "I must rededicate myself to training.\n"
	.string "The road extends into infinity…$"

CanalaveCity_Gym_Text_DavidDefeat::
	.string "That was… A complete trashing!$"

CanalaveCity_Gym_Text_DavidIntro::
	.string "Aiyaah! We're coming out swinging with\n"
	.string "super-heavy judo chops!$"

CanalaveCity_Gym_EventScript_Jackson::
	trainerbattle_single TRAINER_JERRY_4_SINNOH, CanalaveCity_Gym_Text_JacksonIntro, CanalaveCity_Gym_Text_JacksonDefeat
	msgbox CanalaveCity_Gym_Text_JacksonPost, MSGBOX_AUTOCLOSE
	end

CanalaveCity_Gym_Text_JacksonPost::
	.string "I can't keep this up! I'll go back to\n"
	.string "oiling the lifts.$"

CanalaveCity_Gym_Text_JacksonDefeat::
	.string "You've got me feeling down!$"

CanalaveCity_Gym_Text_JacksonIntro::
	.string "Up and down you go on the lifts.\n"
	.string "Me? I like to battle!$"

CanalaveCity_Gym_EventScript_Gary::
	trainerbattle_single TRAINER_JERRY_5_SINNOH, CanalaveCity_Gym_Text_GaryIntro, CanalaveCity_Gym_Text_GaryDefeat
	msgbox CanalaveCity_Gym_Text_GaryPost, MSGBOX_AUTOCLOSE
	end

CanalaveCity_Gym_Text_GaryPost::
	.string "I get to work all day with my POKéMON,\n"
	.string "and even battle sometimes.\p"
	.string "I get all the fun I need every day!$"

CanalaveCity_Gym_Text_GaryDefeat::
	.string "That move was devastating!$"

CanalaveCity_Gym_Text_GaryIntro::
	.string "A POKéMON GYM isn't only about seeing\n"
	.string "how tough your POKéMON happen to be.\p"
	.string "It's so much deeper than just that.\n"
	.string "It's a test of you as a person.$"

CanalaveCity_Gym_EventScript_Ricky::
	trainerbattle_single TRAINER_KAREN_1_SINNOH, CanalaveCity_Gym_Text_RickyIntro, CanalaveCity_Gym_Text_RickyDefeat
	msgbox CanalaveCity_Gym_Text_RickyPost, MSGBOX_AUTOCLOSE
	end

CanalaveCity_Gym_Text_RickyPost::
	.string "If you give up, well, that's when\n"
	.string "everything ends for you!$"

CanalaveCity_Gym_Text_RickyDefeat::
	.string "I never gave up, but still I failed to\n"
	.string "win…$"

CanalaveCity_Gym_Text_RickyIntro::
	.string "Steel represents an unbending spirit!\p"
	.string "If one refuses to accept defeat, the\n"
	.string "path to victory reveals itself!$"

CanalaveCity_Gym_EventScript_Cesar::
	trainerbattle_single TRAINER_KAREN_2_SINNOH, CanalaveCity_Gym_Text_CesarIntro, CanalaveCity_Gym_Text_CesarDefeat
	msgbox CanalaveCity_Gym_Text_CesarPost, MSGBOX_AUTOCLOSE
	end

CanalaveCity_Gym_Text_CesarPost::
	.string "Your earnest enthusiasm… I guess\n"
	.string "that kinda makes you an ace.\p"
	.string "Maybe you're a TRAINER who has the\n"
	.string "potential to surpass aces!$"

CanalaveCity_Gym_Text_CesarDefeat::
	.string "Wow… I'm in the mood to sing a lullaby…$"

CanalaveCity_Gym_Text_CesarIntro::
	.string "An ace has the knowledge and\n"
	.string "experience of battling at high levels.\p"
	.string "I'll demonstrate what that means to a\n"
	.string "noob like you!$"

CanalaveCity_Gym_EventScript_Gerardo::
	trainerbattle_single TRAINER_KAREN_3_SINNOH, CanalaveCity_Gym_Text_GerardoIntro, CanalaveCity_Gym_Text_GerardoDefeat
	msgbox CanalaveCity_Gym_Text_GerardoPost, MSGBOX_AUTOCLOSE
	end

CanalaveCity_Gym_Text_GerardoPost::
	.string "The way you helped each other… That\n"
	.string "is what made you prevail!$"

CanalaveCity_Gym_Text_GerardoDefeat::
	.string "A spectacular loss! But it's still a\n"
	.string "loss!$"

CanalaveCity_Gym_Text_GerardoIntro::
	.string "POKéMON and people have worked\n"
	.string "together for many years.\p"
	.string "Let us show you an example of that\n"
	.string "history!$"

CanalaveCity_Gym_EventScript_Breanna::
	trainerbattle_single TRAINER_KAREN_4_SINNOH, CanalaveCity_Gym_Text_BreannaIntro, CanalaveCity_Gym_Text_BreannaDefeat
	msgbox CanalaveCity_Gym_Text_BreannaPost, MSGBOX_AUTOCLOSE
	end

CanalaveCity_Gym_Text_BreannaPost::
	.string "Start by becoming friendly with your\n"
	.string "POKéMON. I mean really friendly.\p"
	.string "If you do that, you'll learn naturally\n"
	.string "how you should battle with it.$"

CanalaveCity_Gym_Text_BreannaDefeat::
	.string "My focus was too narrow minded…$"

CanalaveCity_Gym_Text_BreannaIntro::
	.string "By focusing on only one type, you can\n"
	.string "really see the strengths and\p"
	.string "weaknesses of that POKéMON.$"

CanalaveCity_Gym_EventScript_Leader::
	goto_if_set FLAG_SYS_GAME_CLEAR, CanalaveCity_Gym_EventScript_SNRematch
	trainerbattle_single TRAINER_JERRY_2_SINNOH, CanalaveCity_Gym_Text_LeaderIntro, CanalaveCity_Gym_Text_LeaderDefeat, CanalaveCity_Gym_EventScript_LeaderDefeated, NO_MUSIC
	goto_if_unset FLAG_RECEIVED_ITEM_TM91_FROM_BYRON, CanalaveCity_Gym_EventScript_GiveTM
	msgbox CanalaveCity_Gym_Text_LeaderPostBattle, MSGBOX_DEFAULT
	release
	end

CanalaveCity_Gym_Text_LeaderPostBattle::
	.string "Gwahahahaha! The SINNOH region is\n"
	.string "vast!\p"
	.string "Tough TRAINERS like you and {PLAYER}\n"
	.string "crop up constantly\p"
	.string "to challenge the old guard!\p"
	.string "With more young TRAINERS like my son\n"
	.string "and you two taking charge, the\p"
	.string "future of POKéMON is bright!\p"
	.string "But I'm not stepping aside just yet!\p"
	.string "I merely need to rededicate myself to\n"
	.string "training on IRON ISLAND.$"

CanalaveCity_Gym_EventScript_GiveTM::
	giveitem ITEM_TM91
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_ITEM_TM91_FROM_BYRON
	msgbox CanalaveCity_Gym_Text_ExplainTM, MSGBOX_DEFAULT
	release
	end

CanalaveCity_Gym_Text_ExplainTM::
	.string "That TM91 contains the move FLASH\n"
	.string "CANNON.\p"
	.string "If it hits, it may also lower the\n"
	.string "target's Special Defense.$"

CanalaveCity_Gym_EventScript_LeaderDefeated::
	message CanalaveCity_Gym_Text_ReceivedBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox CanalaveCity_Gym_Text_ExplainBadge, MSGBOX_DEFAULT
	setflag FLAG_SINNOH_BADGE6_GET
	settrainerflag TRAINER_JERRY_3_SINNOH
	settrainerflag TRAINER_JERRY_4_SINNOH
	settrainerflag TRAINER_JERRY_5_SINNOH
	settrainerflag TRAINER_KAREN_1_SINNOH
	settrainerflag TRAINER_KAREN_2_SINNOH
	settrainerflag TRAINER_KAREN_3_SINNOH
	settrainerflag TRAINER_KAREN_4_SINNOH
	goto CanalaveCity_Gym_EventScript_GiveTM

CanalaveCity_Gym_Text_ExplainBadge::
	.string "Having the Mine BADGE enables you to\n"
	.string "use the hidden move STRENGTH anytime\p"
	.string "outside of battle.\p"
	.string "Here! Take this, too!$"

CanalaveCity_Gym_Text_ReceivedBadge::
	.string "{PLAYER} received the Mine BADGE from\n"
	.string "BYRON!$"

CanalaveCity_Gym_Text_LeaderDefeat::
	.string "You were strong enough to take down\n"
	.string "my prized team of POKéMON.\p"
	.string "In recognition of that power, I give\n"
	.string "you this: the Mine BADGE!$"

CanalaveCity_Gym_Text_LeaderIntro::
	.string "Ah! That's OREBURGH's GYM BADGE!\p"
	.string "I see, I see! You've defeated my son.\p"
	.string "But that's no surprise. He still has\n"
	.string "much to learn.\p"
	.string "In place of my son ROARK, I, BYRON, will\n"
	.string "take your challenge!$"

CanalaveCity_Gym_EventScript_SNRematch::
	lock
	faceplayer
	msgbox CanalaveCity_Gym_EventScript_SNRematch_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CanalaveCity_Gym_EventScript_SNRematch_No
	msgbox CanalaveCity_Gym_EventScript_SNRematch_Go, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_KATELYN_4_SINNOH, CanalaveCity_Gym_EventScript_SNRematch_Defeat
	msgbox CanalaveCity_Gym_EventScript_SNRematch_After, MSGBOX_DEFAULT
	release
	end

CanalaveCity_Gym_EventScript_SNRematch_After::
	.string "That was a great battle! Come back\n"
	.string "anytime for another match!$"

CanalaveCity_Gym_EventScript_SNRematch_Defeat::
	.string "Amazing… You really are the CHAMPION!$"

CanalaveCity_Gym_EventScript_SNRematch_Go::
	.string "Then I won't hold back this time!$"

CanalaveCity_Gym_EventScript_SNRematch_No::
	msgbox CanalaveCity_Gym_EventScript_SNRematch_NoT, MSGBOX_DEFAULT
	release
	end

CanalaveCity_Gym_EventScript_SNRematch_NoT::
	.string "Come back whenever you're ready!$"

CanalaveCity_Gym_EventScript_SNRematch_Ask::
	.string "BYRON: You became the CHAMPION!\n"
	.string "Welcome back!\p"
	.string "I've been training even harder since\n"
	.string "our last battle.\p"
	.string "Will you battle me again?$"

CanalaveCity_Gym_EventScript_PtGymGuide::
	lock
	faceplayer
	goto_if_set FLAG_SINNOH_BADGE6_GET, CanalaveCity_Gym_EventScript_PtGymGuideAfter
	msgbox CanalaveCity_Gym_Text_PtGymGuide, MSGBOX_DEFAULT
	msgbox CanalaveCity_Gym_Text_SNGuideInfo, MSGBOX_DEFAULT
	release
	end

CanalaveCity_Gym_Text_SNGuideInfo::
	.string "Let me tell you about this GYM!\p"
	.string "The GYM LEADER is BYRON, the\n"
	.string "Solid-Rock Father of ROARK from\l"
	.string "OREBURGH.\p"
	.string "He uses Steel-type POKéMON like\n"
	.string "MAGNETON, STEELIX and BASTIODON.\p"
	.string "Steel types are weak to Fire, Fighting\n"
	.string "and Ground moves!\p"
	.string "This GYM is a steel workshop with\n"
	.string "freight lifts. Each pad has a number.\p"
	.string "LIFT 1 only goes to a test platform.\n"
	.string "LIFT 2 takes you up to the catwalk,\l"
	.string "and LIFT 3 at its end goes to BYRON.\p"
	.string "Step on the same pad to ride back!$"

CanalaveCity_Gym_Text_PtGymGuide::
	.string "Hey there, CHAMPION!\p"
	.string "The GYM LEADER here uses Steel-type\n"
	.string "POKéMON.\p"
	.string "Steel-type POKéMON have high Defense,\n"
	.string "so you'd have to hit them hard!$"

CanalaveCity_Gym_EventScript_PtGymGuideAfter::
	msgbox CanalaveCity_Gym_Text_PtGymGuideAfter, MSGBOX_DEFAULT
	release
	end

CanalaveCity_Gym_Text_PtGymGuideAfter::
	.string "Oh! {PLAYER}! You've beaten the GYM\n"
	.string "LEADER!\p"
	.string "Good going! That's one more GYM\n"
	.string "BADGE for your TRAINER Case!\p"
	.string "I tell you what, you're really turning\n"
	.string "into one fine TRAINER.\p"
	.string "If you were to say you're going to try\n"
	.string "to become the POKéMON CHAMP…\p"
	.string "No one'd laugh at you now! I'm in your\n"
	.string "corner, kiddo!$"

CanalaveCity_Gym_EventScript_PtGymStatue::
	lockall
	goto_if_set FLAG_SINNOH_BADGE6_GET, CanalaveCity_Gym_EventScript_PtGymStatueWon
	msgbox CanalaveCity_Gym_Text_PtGymStatue, MSGBOX_DEFAULT
	releaseall
	end

CanalaveCity_Gym_Text_PtGymStatue::
	.string "CANALAVE CITY POKéMON GYM\n"
	.string "LEADER: BYRON$"

CanalaveCity_Gym_EventScript_PtGymStatueWon::
	msgbox CanalaveCity_Gym_Text_PtGymStatueWon, MSGBOX_DEFAULT
	releaseall
	end

CanalaveCity_Gym_Text_PtGymStatueWon::
	.string "CANALAVE CITY POKéMON GYM\n"
	.string "LEADER: BYRON\p"
	.string "Certified TRAINERS:\n"
	.string "{PLAYER}$"
