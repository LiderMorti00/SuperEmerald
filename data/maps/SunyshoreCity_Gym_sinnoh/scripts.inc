SunyshoreCity_Gym_sinnoh_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SunyshoreCity_Gym_OnLoad
	.byte 0

@ Super Emerald: barrier puzzle from the Sinnoh repo
SunyshoreCity_Gym_OnLoad::
	goto_if_set FLAG_SINNOH_BADGE8_GET, SunyshoreCity_Gym_EventScript_DeactivatePuzzle
	switch VAR_SE_SUNYSHORE_GYM_STATE
	case 0, SunyshoreCity_Gym_EventScript_UpdateBarriers
	case 1, SunyshoreCity_Gym_EventScript_Switch1Pressed
	case 2, SunyshoreCity_Gym_EventScript_Switch2Pressed
	case 3, SunyshoreCity_Gym_EventScript_Switch3Pressed
	case 4, SunyshoreCity_Gym_EventScript_Switch4Pressed
	end

SunyshoreCity_Gym_EventScript_UpdateBarriers::
	goto_if_set FLAG_SE_SUNYSHORE_GYM_BARRIERS, SunyshoreCity_Gym_EventScript_SetAltBarriers
	end

SunyshoreCity_Gym_EventScript_SetAltBarriers::
	setmetatile 3, 11, METATILE_MauvilleGym_RedBeamV1_On, TRUE
	setmetatile 3, 12, METATILE_MauvilleGym_RedBeamV2_On, TRUE
	setmetatile 3, 13, METATILE_MauvilleGym_PoleTop_On, TRUE
	setmetatile 4, 10, METATILE_MauvilleGym_RedBeamH1_On, FALSE
	setmetatile 5, 10, METATILE_MauvilleGym_RedBeamH2_On, FALSE
	setmetatile 4, 11, METATILE_MauvilleGym_RedBeamH3_On, TRUE
	setmetatile 5, 11, METATILE_MauvilleGym_RedBeamH4_On, TRUE
	setmetatile 7, 10, METATILE_MauvilleGym_RedBeamH1_On, FALSE
	setmetatile 8, 10, METATILE_MauvilleGym_RedBeamH2_On, FALSE
	setmetatile 7, 11, METATILE_MauvilleGym_RedBeamH3_On, TRUE
	setmetatile 8, 11, METATILE_MauvilleGym_RedBeamH4_On, TRUE
	setmetatile 4, 13, METATILE_MauvilleGym_GreenBeamH1_Off, FALSE
	setmetatile 5, 13, METATILE_MauvilleGym_GreenBeamH2_Off, FALSE
	setmetatile 4, 14, METATILE_MauvilleGym_GreenBeamH3_Off, FALSE
	setmetatile 5, 14, METATILE_MauvilleGym_GreenBeamH4_Off, FALSE
	setmetatile 1, 10, METATILE_MauvilleGym_GreenBeamH1_Off, FALSE
	setmetatile 2, 10, METATILE_MauvilleGym_GreenBeamH2_Off, FALSE
	setmetatile 1, 11, METATILE_MauvilleGym_GreenBeamH3_Off, FALSE
	setmetatile 2, 11, METATILE_MauvilleGym_GreenBeamH4_Off, FALSE
	setmetatile 6, 8, METATILE_MauvilleGym_PoleBottom_On, TRUE
	setmetatile 6, 9, METATILE_MauvilleGym_FloorTile, FALSE
	setmetatile 6, 10, METATILE_MauvilleGym_PoleTop_Off, FALSE
	setmetatile 4, 6, METATILE_MauvilleGym_GreenBeamH1_Off, FALSE
	setmetatile 5, 6, METATILE_MauvilleGym_GreenBeamH2_Off, FALSE
	setmetatile 4, 7, METATILE_MauvilleGym_GreenBeamH3_Off, FALSE
	setmetatile 5, 7, METATILE_MauvilleGym_GreenBeamH4_Off, FALSE
	end

SunyshoreCity_Gym_EventScript_Switch1Pressed::
	setvar VAR_0x8004, 0
	special MauvilleGymPressSwitch
	goto SunyshoreCity_Gym_EventScript_UpdateBarriers
	end

SunyshoreCity_Gym_EventScript_Switch2Pressed::
	setvar VAR_0x8004, 1
	special MauvilleGymPressSwitch
	goto SunyshoreCity_Gym_EventScript_UpdateBarriers
	end

SunyshoreCity_Gym_EventScript_Switch3Pressed::
	setvar VAR_0x8004, 2
	special MauvilleGymPressSwitch
	goto SunyshoreCity_Gym_EventScript_UpdateBarriers
	end

SunyshoreCity_Gym_EventScript_Switch4Pressed::
	setvar VAR_0x8004, 3
	special MauvilleGymPressSwitch
	goto SunyshoreCity_Gym_EventScript_UpdateBarriers
	end

SunyshoreCity_Gym_EventScript_DeactivatePuzzle::
	special MauvilleGymDeactivatePuzzle
	end

SunyshoreCity_Gym_EventScript_Switch1::
	lockall
	goto_if_set FLAG_SINNOH_BADGE8_GET, SunyshoreCity_Gym_EventScript_SwitchDoNothing
	goto_if_eq VAR_SE_SUNYSHORE_GYM_STATE, 1, SunyshoreCity_Gym_EventScript_SwitchDoNothing
	setvar VAR_SE_SUNYSHORE_GYM_STATE, 1
	setvar VAR_0x8004, 0
	goto SunyshoreCity_Gym_EventScript_PressFloorSwitch
	end

SunyshoreCity_Gym_EventScript_Switch2::
	lockall
	goto_if_set FLAG_SINNOH_BADGE8_GET, SunyshoreCity_Gym_EventScript_SwitchDoNothing
	goto_if_eq VAR_SE_SUNYSHORE_GYM_STATE, 2, SunyshoreCity_Gym_EventScript_SwitchDoNothing
	setvar VAR_SE_SUNYSHORE_GYM_STATE, 2
	setvar VAR_0x8004, 1
	goto SunyshoreCity_Gym_EventScript_PressFloorSwitch
	end

SunyshoreCity_Gym_EventScript_Switch3::
	lockall
	goto_if_set FLAG_SINNOH_BADGE8_GET, SunyshoreCity_Gym_EventScript_SwitchDoNothing
	goto_if_eq VAR_SE_SUNYSHORE_GYM_STATE, 3, SunyshoreCity_Gym_EventScript_SwitchDoNothing
	setvar VAR_SE_SUNYSHORE_GYM_STATE, 3
	setvar VAR_0x8004, 2
	goto SunyshoreCity_Gym_EventScript_PressFloorSwitch
	end

SunyshoreCity_Gym_EventScript_Switch4::
	lockall
	goto_if_set FLAG_SINNOH_BADGE8_GET, SunyshoreCity_Gym_EventScript_SwitchDoNothing
	goto_if_eq VAR_SE_SUNYSHORE_GYM_STATE, 4, SunyshoreCity_Gym_EventScript_SwitchDoNothing
	setvar VAR_SE_SUNYSHORE_GYM_STATE, 4
	setvar VAR_0x8004, 3
	goto SunyshoreCity_Gym_EventScript_PressFloorSwitch
	end

SunyshoreCity_Gym_EventScript_PressFloorSwitch::
	special MauvilleGymSetDefaultBarriers
	special MauvilleGymPressSwitch
	special DrawWholeMapView
	playse SE_UNLOCK
	goto_if_set FLAG_SE_SUNYSHORE_GYM_BARRIERS, SunyshoreCity_Gym_EventScript_ClearBarriersAltState
	goto_if_unset FLAG_SE_SUNYSHORE_GYM_BARRIERS, SunyshoreCity_Gym_EventScript_SetBarriersAltState
	releaseall
	end

SunyshoreCity_Gym_EventScript_SwitchDoNothing::
	releaseall
	end

SunyshoreCity_Gym_EventScript_SetBarriersAltState::
	setflag FLAG_SE_SUNYSHORE_GYM_BARRIERS
	releaseall
	end

SunyshoreCity_Gym_EventScript_ClearBarriersAltState::
	clearflag FLAG_SE_SUNYSHORE_GYM_BARRIERS
	releaseall
	end


SunyshoreCity_Gym_EventScript_Tiera::
	trainerbattle_single TRAINER_MIGUEL_3_SINNOH, SunyshoreCity_Gym_Text_TieraIntro, SunyshoreCity_Gym_Text_TieraDefeat
	msgbox SunyshoreCity_Gym_Text_TieraPost, MSGBOX_AUTOCLOSE
	end

SunyshoreCity_Gym_Text_TieraPost::
	.string "Our GYM's electric barriers are sure to\n"
	.string "give you a shock! Think before you\l"
	.string "step on a switch.$"

SunyshoreCity_Gym_Text_TieraDefeat::
	.string "The barriers crackle on and off… And\n"
	.string "I'm switched off…$"

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
	.string "Electric barriers block the GYM. Step\n"
	.string "on the floor switches to turn them on\l"
	.string "and off and open a path to VOLKNER.$"

SunyshoreCity_Gym_Text_PtGymGuide::
	.string "Hey, there! How's it going, CHAMP-to-be?\p"
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
