	.include "data/maps/SunyshoreCity_Gym_sinnoh/gym_metatiles.inc"

SunyshoreCity_Gym_sinnoh_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SunyshoreCity_Gym_OnLoad
	.byte 0

@ Super Emerald: rotating walkway crosses, after Platinum's gear rooms (tools/sfr/gyms/sunyshore.py).
@ VAR_TEMP_1 / VAR_TEMP_2 = which arm of turntable 1 / 2 is retracted (0 N, 1 E, 2 S, 3 W).
@ Floor buttons turn a turntable clockwise; the reverse button on the hub turns it back.
@ The map is drawn in state 0; ON_LOAD redraws the current state (temp vars reset on leaving).
SunyshoreCity_Gym_OnLoad::
	call SunyshoreCity_Gym_EventScript_DrawTT1
	call SunyshoreCity_Gym_EventScript_DrawTT2
	end

SunyshoreCity_Gym_EventScript_DrawTT1::
	switch VAR_TEMP_1
	case 0, SunyshoreCity_Gym_EventScript_TT1_0
	case 1, SunyshoreCity_Gym_EventScript_TT1_1
	case 2, SunyshoreCity_Gym_EventScript_TT1_2
	case 3, SunyshoreCity_Gym_EventScript_TT1_3
	return

SunyshoreCity_Gym_EventScript_TT1_0::
	setmetatile 8, 16, METATILE_SunyshoreGym_tt1_c0, FALSE
	setmetatile 8, 15, METATILE_SunyshoreGym_tt1_n_off, TRUE
	setmetatile 9, 16, METATILE_SunyshoreGym_tt1_e_on, FALSE
	setmetatile 8, 17, METATILE_SunyshoreGym_tt1_s_on, FALSE
	setmetatile 7, 16, METATILE_SunyshoreGym_tt1_w_on, FALSE
	return

SunyshoreCity_Gym_EventScript_TT1_1::
	setmetatile 8, 16, METATILE_SunyshoreGym_tt1_c1, FALSE
	setmetatile 8, 15, METATILE_SunyshoreGym_tt1_n_on, FALSE
	setmetatile 9, 16, METATILE_SunyshoreGym_tt1_e_off, TRUE
	setmetatile 8, 17, METATILE_SunyshoreGym_tt1_s_on, FALSE
	setmetatile 7, 16, METATILE_SunyshoreGym_tt1_w_on, FALSE
	return

SunyshoreCity_Gym_EventScript_TT1_2::
	setmetatile 8, 16, METATILE_SunyshoreGym_tt1_c2, FALSE
	setmetatile 8, 15, METATILE_SunyshoreGym_tt1_n_on, FALSE
	setmetatile 9, 16, METATILE_SunyshoreGym_tt1_e_on, FALSE
	setmetatile 8, 17, METATILE_SunyshoreGym_tt1_s_off, TRUE
	setmetatile 7, 16, METATILE_SunyshoreGym_tt1_w_on, FALSE
	return

SunyshoreCity_Gym_EventScript_TT1_3::
	setmetatile 8, 16, METATILE_SunyshoreGym_tt1_c3, FALSE
	setmetatile 8, 15, METATILE_SunyshoreGym_tt1_n_on, FALSE
	setmetatile 9, 16, METATILE_SunyshoreGym_tt1_e_on, FALSE
	setmetatile 8, 17, METATILE_SunyshoreGym_tt1_s_on, FALSE
	setmetatile 7, 16, METATILE_SunyshoreGym_tt1_w_off, TRUE
	return

SunyshoreCity_Gym_EventScript_TT1_Turning::
	setmetatile 8, 15, METATILE_SunyshoreGym_tt1_n_off, TRUE
	setmetatile 9, 16, METATILE_SunyshoreGym_tt1_e_off, TRUE
	setmetatile 8, 17, METATILE_SunyshoreGym_tt1_s_off, TRUE
	setmetatile 7, 16, METATILE_SunyshoreGym_tt1_w_off, TRUE
	special DrawWholeMapView
	playse SE_M_THUNDER_WAVE
	delay 10
	return

SunyshoreCity_Gym_EventScript_DrawTT2::
	switch VAR_TEMP_2
	case 0, SunyshoreCity_Gym_EventScript_TT2_0
	case 1, SunyshoreCity_Gym_EventScript_TT2_1
	case 2, SunyshoreCity_Gym_EventScript_TT2_2
	case 3, SunyshoreCity_Gym_EventScript_TT2_3
	return

SunyshoreCity_Gym_EventScript_TT2_0::
	setmetatile 8, 9, METATILE_SunyshoreGym_tt2_c0, FALSE
	setmetatile 8, 8, METATILE_SunyshoreGym_tt2_n_off, TRUE
	setmetatile 9, 9, METATILE_SunyshoreGym_tt2_e_on, FALSE
	setmetatile 8, 10, METATILE_SunyshoreGym_tt2_s_on, FALSE
	setmetatile 7, 9, METATILE_SunyshoreGym_tt2_w_on, FALSE
	return

SunyshoreCity_Gym_EventScript_TT2_1::
	setmetatile 8, 9, METATILE_SunyshoreGym_tt2_c1, FALSE
	setmetatile 8, 8, METATILE_SunyshoreGym_tt2_n_on, FALSE
	setmetatile 9, 9, METATILE_SunyshoreGym_tt2_e_off, TRUE
	setmetatile 8, 10, METATILE_SunyshoreGym_tt2_s_on, FALSE
	setmetatile 7, 9, METATILE_SunyshoreGym_tt2_w_on, FALSE
	return

SunyshoreCity_Gym_EventScript_TT2_2::
	setmetatile 8, 9, METATILE_SunyshoreGym_tt2_c2, FALSE
	setmetatile 8, 8, METATILE_SunyshoreGym_tt2_n_on, FALSE
	setmetatile 9, 9, METATILE_SunyshoreGym_tt2_e_on, FALSE
	setmetatile 8, 10, METATILE_SunyshoreGym_tt2_s_off, TRUE
	setmetatile 7, 9, METATILE_SunyshoreGym_tt2_w_on, FALSE
	return

SunyshoreCity_Gym_EventScript_TT2_3::
	setmetatile 8, 9, METATILE_SunyshoreGym_tt2_c3, FALSE
	setmetatile 8, 8, METATILE_SunyshoreGym_tt2_n_on, FALSE
	setmetatile 9, 9, METATILE_SunyshoreGym_tt2_e_on, FALSE
	setmetatile 8, 10, METATILE_SunyshoreGym_tt2_s_on, FALSE
	setmetatile 7, 9, METATILE_SunyshoreGym_tt2_w_off, TRUE
	return

SunyshoreCity_Gym_EventScript_TT2_Turning::
	setmetatile 8, 8, METATILE_SunyshoreGym_tt2_n_off, TRUE
	setmetatile 9, 9, METATILE_SunyshoreGym_tt2_e_off, TRUE
	setmetatile 8, 10, METATILE_SunyshoreGym_tt2_s_off, TRUE
	setmetatile 7, 9, METATILE_SunyshoreGym_tt2_w_off, TRUE
	special DrawWholeMapView
	playse SE_M_THUNDER_WAVE
	delay 10
	return

SunyshoreCity_Gym_EventScript_Button1::
	lockall
	playse SE_SWITCH
	call SunyshoreCity_Gym_EventScript_TT1_Turning
	addvar VAR_TEMP_1, 1
	call_if_eq VAR_TEMP_1, 4, SunyshoreCity_Gym_EventScript_TT1_Wrap
	call SunyshoreCity_Gym_EventScript_DrawTT1
	special DrawWholeMapView
	releaseall
	end

SunyshoreCity_Gym_EventScript_TT1_Wrap::
	setvar VAR_TEMP_1, 0
	return

SunyshoreCity_Gym_EventScript_Button2::
	lockall
	playse SE_SWITCH
	call SunyshoreCity_Gym_EventScript_TT2_Turning
	addvar VAR_TEMP_2, 1
	call_if_eq VAR_TEMP_2, 4, SunyshoreCity_Gym_EventScript_TT2_Wrap
	call SunyshoreCity_Gym_EventScript_DrawTT2
	special DrawWholeMapView
	releaseall
	end

SunyshoreCity_Gym_EventScript_TT2_Wrap::
	setvar VAR_TEMP_2, 0
	return

SunyshoreCity_Gym_EventScript_Button2Rev::
	lockall
	playse SE_SWITCH
	call SunyshoreCity_Gym_EventScript_TT2_Turning
	call_if_eq VAR_TEMP_2, 0, SunyshoreCity_Gym_EventScript_TT2_Unwrap
	subvar VAR_TEMP_2, 1
	call SunyshoreCity_Gym_EventScript_DrawTT2
	special DrawWholeMapView
	releaseall
	end

SunyshoreCity_Gym_EventScript_TT2_Unwrap::
	setvar VAR_TEMP_2, 4
	return

SunyshoreCity_Gym_EventScript_Tiera::
	trainerbattle_single TRAINER_MIGUEL_3_SINNOH, SunyshoreCity_Gym_Text_TieraIntro, SunyshoreCity_Gym_Text_TieraDefeat
	msgbox SunyshoreCity_Gym_Text_TieraPost, MSGBOX_AUTOCLOSE
	end

SunyshoreCity_Gym_Text_TieraPost::
	.string "Our GYM's turning walkways are sure to\n"
	.string "give you a spin! Think before you\l"
	.string "step on a button.$"

SunyshoreCity_Gym_Text_TieraDefeat::
	.string "The gears spin round and round… And\n"
	.string "I'm spun right out…$"

SunyshoreCity_Gym_Text_TieraIntro::
	.string "Can you make it to the GYM LEADER? You\n"
	.string "sure now?$"

SunyshoreCity_Gym_EventScript_Forrest::
	trainerbattle_single TRAINER_MIGUEL_4_SINNOH, SunyshoreCity_Gym_Text_ForrestIntro, SunyshoreCity_Gym_Text_ForrestDefeat
	msgbox SunyshoreCity_Gym_Text_ForrestPost, MSGBOX_AUTOCLOSE
	end

SunyshoreCity_Gym_Text_ForrestPost::
	.string "You just showed me that there's still\n"
	.string "lots I need to learn.\p"
	.string "The world of POKéMON is deep!$"

SunyshoreCity_Gym_Text_ForrestDefeat::
	.string "…You're tough.$"

SunyshoreCity_Gym_Text_ForrestIntro::
	.string "This is the toughest GYM in SINNOH.\p"
	.string "That's why I'm here--to learn the best\n"
	.string "battle techniques around!$"

SunyshoreCity_Gym_EventScript_Jerry::
	trainerbattle_single TRAINER_MIGUEL_5_SINNOH, SunyshoreCity_Gym_Text_JerryIntro, SunyshoreCity_Gym_Text_JerryDefeat
	msgbox SunyshoreCity_Gym_Text_JerryPost, MSGBOX_AUTOCLOSE
	end

SunyshoreCity_Gym_Text_JerryPost::
	.string "The TRAINER's desire to win!\p"
	.string "If you don't lose that, there's no limit\n"
	.string "on what you can become!$"

SunyshoreCity_Gym_Text_JerryDefeat::
	.string "We couldn't win… No encores for us…$"

SunyshoreCity_Gym_Text_JerryIntro::
	.string "I want to win! That desire I pour into\n"
	.string "my guitar!\p"
	.string "I want to win! That passion compels my\n"
	.string "POKéMON!$"

SunyshoreCity_Gym_EventScript_Meghan::
	trainerbattle_single TRAINER_ISABEL_1_SINNOH, SunyshoreCity_Gym_Text_MeghanIntro, SunyshoreCity_Gym_Text_MeghanDefeat
	msgbox SunyshoreCity_Gym_Text_MeghanPost, MSGBOX_AUTOCLOSE
	end

SunyshoreCity_Gym_Text_MeghanPost::
	.string "I dress this way so I can get a feel for\n"
	.string "how electric POKéMON think.\p"
	.string "Would you like to try, too?$"

SunyshoreCity_Gym_Text_MeghanDefeat::
	.string "I was being serious! Don't laugh at me!\n"
	.string "I mean it!$"

SunyshoreCity_Gym_Text_MeghanIntro::
	.string "Look at the way I'm dressed. Can't you\n"
	.string "see that I'm hardcore?$"

SunyshoreCity_Gym_EventScript_Destiny::
	trainerbattle_single TRAINER_ISABEL_2_SINNOH, SunyshoreCity_Gym_Text_DestinyIntro, SunyshoreCity_Gym_Text_DestinyDefeat
	msgbox SunyshoreCity_Gym_Text_DestinyPost, MSGBOX_AUTOCLOSE
	end

SunyshoreCity_Gym_Text_DestinyPost::
	.string "I'm so glad that there are POKéMON!\p"
	.string "There isn't much else that gives me the\n"
	.string "thrill that POKéMON do!$"

SunyshoreCity_Gym_Text_DestinyDefeat::
	.string "Your power is thrilling… I'm thrilled\n"
	.string "down to my toes!$"

SunyshoreCity_Gym_Text_DestinyIntro::
	.string "I'm not just looking for tough TRAINERS\n"
	.string "to battle.\p"
	.string "I've been battling here because I want\n"
	.string "to feel the rush!$"

SunyshoreCity_Gym_EventScript_Preston::
	trainerbattle_single TRAINER_ISABEL_3_SINNOH, SunyshoreCity_Gym_Text_PrestonIntro, SunyshoreCity_Gym_Text_PrestonDefeat
	msgbox SunyshoreCity_Gym_Text_PrestonPost, MSGBOX_AUTOCLOSE
	end

SunyshoreCity_Gym_Text_PrestonPost::
	.string "We were lacking energy…\p"
	.string "No, we lacked more than that. We didn't\n"
	.string "want the win enough.$"

SunyshoreCity_Gym_Text_PrestonDefeat::
	.string "Spark…$"

SunyshoreCity_Gym_Text_PrestonIntro::
	.string "Spark!\p"
	.string "This is what our GYM LEADER did to the\n"
	.string "GYM out of boredom!$"

SunyshoreCity_Gym_EventScript_Lonnie::
	trainerbattle_single TRAINER_ISABEL_4_SINNOH, SunyshoreCity_Gym_Text_LonnieIntro, SunyshoreCity_Gym_Text_LonnieDefeat
	msgbox SunyshoreCity_Gym_Text_LonniePost, MSGBOX_AUTOCLOSE
	end

SunyshoreCity_Gym_Text_LonniePost::
	.string "The way you battle, I can feel the very\n"
	.string "heart of rock and roll.\p"
	.string "Tell me, are you maybe a fan of rocking\n"
	.string "out?$"

SunyshoreCity_Gym_Text_LonnieDefeat::
	.string "My skills seem to have let me down. I\n"
	.string "must have been out of tune!$"

SunyshoreCity_Gym_Text_LonnieIntro::
	.string "Whether you're a TRAINER or a Guitarist,\n"
	.string "it takes dedication to\p"
	.string "improve your mad skills!$"

SunyshoreCity_Gym_EventScript_Zachery::
	trainerbattle_single TRAINER_ISABEL_5_SINNOH, SunyshoreCity_Gym_Text_ZacheryIntro, SunyshoreCity_Gym_Text_ZacheryDefeat
	msgbox SunyshoreCity_Gym_Text_ZacheryPost, MSGBOX_AUTOCLOSE
	end

SunyshoreCity_Gym_Text_ZacheryPost::
	.string "As a challenger, you're one tough\n"
	.string "TRAINER.$"

SunyshoreCity_Gym_Text_ZacheryDefeat::
	.string "What makes your POKéMON so special?$"

SunyshoreCity_Gym_Text_ZacheryIntro::
	.string "Wow! I'm surprised you've come this far,\n"
	.string "but you'll have to turn back.\p"
	.string "There isn't any chance that you could\n"
	.string "ever beat me!$"

SunyshoreCity_Gym_EventScript_Leader::
	goto_if_set FLAG_SYS_GAME_CLEAR, SunyshoreCity_Gym_EventScript_SNRematch
	trainerbattle_single TRAINER_MIGUEL_2_SINNOH, SunyshoreCity_Gym_Text_LeaderIntro, SunyshoreCity_Gym_Text_LeaderDefeat, SunyshoreCity_Gym_EventScript_LeaderDefeated, NO_MUSIC
	goto_if_unset FLAG_RECEIVED_ITEM_TM57_FROM_VOLKNER, SunyshoreCity_Gym_EventScript_GiveTM
	msgbox SunyshoreCity_Gym_Text_LeaderPostBattle, MSGBOX_DEFAULT
	release
	end

SunyshoreCity_Gym_Text_LeaderPostBattle::
	.string "Your next step is the POKéMON LEAGUE\n"
	.string "challenge.\p"
	.string "It's time for you to cross the sea and\n"
	.string "win your way through the\p"
	.string "gauntlet that is VICTORY ROAD.\p"
	.string "Demonstrate to the POKéMON LEAGUE\n"
	.string "your mastery of your team.\p"
	.string "Against you, even the ELITE FOUR will be\n"
	.string "pushed to fend off your challenge!$"

SunyshoreCity_Gym_EventScript_GiveTM::
	giveitem ITEM_TM57
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_ITEM_TM57_FROM_VOLKNER
	msgbox SunyshoreCity_Gym_Text_ExplainTM, MSGBOX_DEFAULT
	release
	end

SunyshoreCity_Gym_Text_ExplainTM::
	.string "What's inside that TM57 is the move\n"
	.string "CHARGE BEAM.\p"
	.string "It may raise Special Attack if it lands.\n"
	.string "It's electrifying!$"

SunyshoreCity_Gym_EventScript_LeaderDefeated::
	setflag FLAG_SN_DEFEATED_MAUVILLE_GYM
	special MauvilleGymDeactivatePuzzle
	special DrawWholeMapView
	playse SE_UNLOCK
	message SunyshoreCity_Gym_Text_ReceivedBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox SunyshoreCity_Gym_Text_ExplainBadge, MSGBOX_DEFAULT
	setflag FLAG_SINNOH_BADGE8_GET
	settrainerflag TRAINER_MIGUEL_3_SINNOH
	settrainerflag TRAINER_MIGUEL_4_SINNOH
	settrainerflag TRAINER_MIGUEL_5_SINNOH
	settrainerflag TRAINER_ISABEL_1_SINNOH
	settrainerflag TRAINER_ISABEL_2_SINNOH
	settrainerflag TRAINER_ISABEL_3_SINNOH
	settrainerflag TRAINER_ISABEL_4_SINNOH
	settrainerflag TRAINER_ISABEL_5_SINNOH
	goto SunyshoreCity_Gym_EventScript_GiveTM

SunyshoreCity_Gym_Text_ExplainBadge::
	.string "That Beacon BADGE lets you use the\n"
	.string "hidden move WATERFALL even when\l"
	.string "you're not in a battle.\p"
	.string "Waterfall happens to be key if you're\n"
	.string "going to the POKéMON LEAGUE.\p"
	.string "I want you to take this, too.$"

SunyshoreCity_Gym_Text_ReceivedBadge::
	.string "{PLAYER} received the Beacon BADGE\n"
	.string "from VOLKNER.$"

SunyshoreCity_Gym_Text_LeaderDefeat::
	.string "…Hehehe.\p"
	.string "Hahahah!\p"
	.string "…That was the most fun I've had in a\n"
	.string "battle since…I don't know when!\p"
	.string "It's also made me excited to know you\n"
	.string "and your team will keep battling\p"
	.string "to greater heights!\p"
	.string "This GYM BADGE is yours. You've\n"
	.string "earned it!$"

SunyshoreCity_Gym_Text_LeaderIntro::
	.string "…All right, challenger.\p"
	.string "It's not often, but some TRAINERS\n"
	.string "manage to come and challenge me.\p"
	.string "But they've all been boring battles. I\n"
	.string "didn't break a sweat beating them.\p"
	.string "…Sigh… I'm VOLKNER, the GYM LEADER.\p"
	.string "They say I'm the top GYM LEADER in\n"
	.string "SINNOH, but…\p"
	.string "Anyway, I guess we'd better get this\n"
	.string "done.\p"
	.string "I hope you're the TRAINER who'll make me\n"
	.string "remember how fun it is to battle!$"

SunyshoreCity_Gym_EventScript_SNRematch::
	lock
	faceplayer
	msgbox SunyshoreCity_Gym_EventScript_SNRematch_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SunyshoreCity_Gym_EventScript_SNRematch_No
	msgbox SunyshoreCity_Gym_EventScript_SNRematch_Go, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_NICOLAS_1_SINNOH, SunyshoreCity_Gym_EventScript_SNRematch_Defeat
	msgbox SunyshoreCity_Gym_EventScript_SNRematch_After, MSGBOX_DEFAULT
	release
	end

SunyshoreCity_Gym_EventScript_SNRematch_After::
	.string "That was a great battle! Come back\n"
	.string "anytime for another match!$"

SunyshoreCity_Gym_EventScript_SNRematch_Defeat::
	.string "Amazing… You really are the CHAMPION!$"

SunyshoreCity_Gym_EventScript_SNRematch_Go::
	.string "Then I won't hold back this time!$"

SunyshoreCity_Gym_EventScript_SNRematch_No::
	msgbox SunyshoreCity_Gym_EventScript_SNRematch_NoT, MSGBOX_DEFAULT
	release
	end

SunyshoreCity_Gym_EventScript_SNRematch_NoT::
	.string "Come back whenever you're ready!$"

SunyshoreCity_Gym_EventScript_SNRematch_Ask::
	.string "VOLKNER: You became the CHAMPION!\n"
	.string "Welcome back!\p"
	.string "I've been training even harder since\n"
	.string "our last battle.\p"
	.string "Will you battle me again?$"

SunyshoreCity_Gym_EventScript_PtGymGuide::
	lock
	faceplayer
	goto_if_set FLAG_SINNOH_BADGE8_GET, SunyshoreCity_Gym_EventScript_PtGymGuideAfter
	msgbox SunyshoreCity_Gym_Text_PtGymGuide, MSGBOX_DEFAULT
	msgbox SunyshoreCity_Gym_Text_SNGuideInfo, MSGBOX_DEFAULT
	release
	end

SunyshoreCity_Gym_Text_SNGuideInfo::
	.string "Let me tell you about this GYM!\p"
	.string "The GYM LEADER is VOLKNER, the Shining,\n"
	.string "Shocking Star and the strongest GYM\l"
	.string "LEADER in SINNOH.\p"
	.string "He uses Electric-type POKéMON like\n"
	.string "JOLTEON, RAICHU, LUXRAY and\l"
	.string "ELECTIVIRE.\p"
	.string "Electric types are weak to Ground\n"
	.string "moves, and Ground types are immune to\l"
	.string "Electric moves!\p"
	.string "The walkways meet on big turning\n"
	.string "gears. Step on a round button and its\l"
	.string "gear turns a quarter of a circle.\p"
	.string "The arrow on the gear points at the\n"
	.string "side that's closed. The orange button\l"
	.string "here turns the first gear.\p"
	.string "Up ahead, the blue button turns the\n"
	.string "second gear, and the one with the\l"
	.string "backward arrow turns it back!$"

SunyshoreCity_Gym_Text_PtGymGuide::
	.string "Hey there, CHAMPION! How's it going?\p"
	.string "Let me check out your TRAINER Case…\n"
	.string "Whoa! Look at all those BADGES!\p"
	.string "The GYM LEADER here is a master of\n"
	.string "Electric-type POKéMON!\p"
	.string "That's all I have to say. The rest is\n"
	.string "up to you!$"

SunyshoreCity_Gym_EventScript_PtGymGuideAfter::
	msgbox SunyshoreCity_Gym_Text_PtGymGuideAfter, MSGBOX_DEFAULT
	release
	end

SunyshoreCity_Gym_Text_PtGymGuideAfter::
	.string "Oh! {PLAYER}! Did you beat the GYM\n"
	.string "LEADER?\p"
	.string "Well, of course you did!\p"
	.string "But, you know what? You haven't made\n"
	.string "it in my mind yet!\p"
	.string "Do you know why?\p"
	.string "Because you and your POKéMON are\n"
	.string "capable of achieving so much more!\p"
	.string "But, I am proud of you! You beat\n"
	.string "VOLKNER!\p"
	.string "Way to go, kiddo!$"

SunyshoreCity_Gym_EventScript_PtGymStatue::
	lockall
	goto_if_set FLAG_SINNOH_BADGE8_GET, SunyshoreCity_Gym_EventScript_PtGymStatueWon
	msgbox SunyshoreCity_Gym_Text_PtGymStatue, MSGBOX_DEFAULT
	releaseall
	end

SunyshoreCity_Gym_Text_PtGymStatue::
	.string "SUNYSHORE CITY POKéMON GYM\p"
	.string "LEADER: VOLKNER$"

SunyshoreCity_Gym_EventScript_PtGymStatueWon::
	msgbox SunyshoreCity_Gym_Text_PtGymStatueWon, MSGBOX_DEFAULT
	releaseall
	end

SunyshoreCity_Gym_Text_PtGymStatueWon::
	.string "SUNYSHORE CITY POKéMON GYM\p"
	.string "LEADER: VOLKNER\p"
	.string "Certified TRAINERS:\n"
	.string "{PLAYER}$"
