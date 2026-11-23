VeilstoneCity_Gym_sinnoh_MapScripts::
	.byte 0


VeilstoneCity_Gym_EventScript_Colby::
	trainerbattle_single TRAINER_JACKI_1_SINNOH, VeilstoneCity_Gym_Text_ColbyIntro, VeilstoneCity_Gym_Text_ColbyDefeat, VeilstoneCity_Gym_EventScript_TakaoBrightenRoom
	msgbox VeilstoneCity_Gym_Text_ColbyPost, MSGBOX_AUTOCLOSE
	end

VeilstoneCity_Gym_Text_ColbyPost::
	.string "Your POKéMON sure are tough!\p"
	.string "But our GYM LEADER MAYLENE will break\n"
	.string "you like a stack of bricks!$"

VeilstoneCity_Gym_EventScript_TakaoBrightenRoom::
	call VeilstoneCity_Gym_EventScript_BrightenRoom
	release
	end

VeilstoneCity_Gym_EventScript_NoLightChange::
	return

@ NOTE: A little confusingly, a larger animateflash param value is a smaller flash radius

VeilstoneCity_Gym_EventScript_BrightenRoom::
	call VeilstoneCity_Gym_EventScript_CountTrainersDefeated
	nop1
	goto_if_eq VAR_0x8000, VAR_0x8001, VeilstoneCity_Gym_EventScript_NoLightChange
	copyvar VAR_0x8001, VAR_0x8000
	goto_if_eq VAR_0x8000, 1, VeilstoneCity_Gym_EventScript_AnimateFlash1Trainer
	goto_if_eq VAR_0x8000, 2, VeilstoneCity_Gym_EventScript_AnimateFlash2Trainers
	goto_if_eq VAR_0x8000, 3, VeilstoneCity_Gym_EventScript_AnimateFlash3Trainers
	goto_if_eq VAR_0x8000, 4, VeilstoneCity_Gym_EventScript_AnimateFlash4Trainers
	goto_if_eq VAR_0x8000, 5, VeilstoneCity_Gym_EventScript_AnimateFlash5Trainers
	goto_if_eq VAR_0x8000, 6, VeilstoneCity_Gym_EventScript_AnimateFlash6Trainers
	goto VeilstoneCity_Gym_EventScript_NoLightChange

VeilstoneCity_Gym_EventScript_AnimateFlash6Trainers::
	playse SE_SWITCH
	animateflash 1
	call VeilstoneCity_Gym_EventScript_SetFlashLevel
	return

VeilstoneCity_Gym_EventScript_SetFlashLevel::
	goto_if_defeated TRAINER_CAMERON_5_SINNOH, VeilstoneCity_Gym_EventScript_SetLightsOn
	call VeilstoneCity_Gym_EventScript_CountTrainersDefeated
	copyvar VAR_0x8001, VAR_0x8000
	goto_if_eq VAR_0x8000, 0, VeilstoneCity_Gym_EventScript_SetFlashLevel7
	goto_if_eq VAR_0x8000, 1, VeilstoneCity_Gym_EventScript_SetFlashLevel6
	goto_if_eq VAR_0x8000, 2, VeilstoneCity_Gym_EventScript_SetFlashLevel5
	goto_if_eq VAR_0x8000, 3, VeilstoneCity_Gym_EventScript_SetFlashLevel4
	goto_if_eq VAR_0x8000, 4, VeilstoneCity_Gym_EventScript_SetFlashLevel3
	goto_if_eq VAR_0x8000, 5, VeilstoneCity_Gym_EventScript_SetFlashLevel2
	goto VeilstoneCity_Gym_EventScript_SetFlashLevel1

VeilstoneCity_Gym_EventScript_SetFlashLevel1::
	setflashlevel 1
	return

VeilstoneCity_Gym_EventScript_SetFlashLevel2::
	setflashlevel 2
	return

VeilstoneCity_Gym_EventScript_SetFlashLevel3::
	setflashlevel 3
	return

VeilstoneCity_Gym_EventScript_SetFlashLevel4::
	setflashlevel 4
	return

VeilstoneCity_Gym_EventScript_SetFlashLevel5::
	setflashlevel 5
	return

VeilstoneCity_Gym_EventScript_SetFlashLevel6::
	setflashlevel 6
	return

@ Darkest

VeilstoneCity_Gym_EventScript_SetFlashLevel7::
	setflashlevel 7
	return

VeilstoneCity_Gym_EventScript_StopCountingTrainers::
	return

VeilstoneCity_Gym_EventScript_CheckLilith::
	goto_if_not_defeated TRAINER_LILITH_SINNOH, VeilstoneCity_Gym_EventScript_StopCountingTrainers
	addvar VAR_0x8000, 1
	goto VeilstoneCity_Gym_EventScript_StopCountingTrainers

VeilstoneCity_Gym_EventScript_CheckCristian::
	goto_if_not_defeated TRAINER_JACKI_4_SINNOH, VeilstoneCity_Gym_EventScript_CheckLilith
	addvar VAR_0x8000, 1
	goto VeilstoneCity_Gym_EventScript_CheckLilith

VeilstoneCity_Gym_EventScript_CheckBrenden::
	goto_if_not_defeated TRAINER_BRENDEN_SINNOH, VeilstoneCity_Gym_EventScript_CheckCristian
	addvar VAR_0x8000, 1
	goto VeilstoneCity_Gym_EventScript_CheckCristian

VeilstoneCity_Gym_EventScript_CheckLaura::
	goto_if_not_defeated TRAINER_JACKI_3_SINNOH, VeilstoneCity_Gym_EventScript_CheckBrenden
	addvar VAR_0x8000, 1
	goto VeilstoneCity_Gym_EventScript_CheckBrenden

VeilstoneCity_Gym_EventScript_CheckJocelyn::
	goto_if_not_defeated TRAINER_JACKI_2_SINNOH, VeilstoneCity_Gym_EventScript_CheckLaura
	addvar VAR_0x8000, 1
	goto VeilstoneCity_Gym_EventScript_CheckLaura

VeilstoneCity_Gym_EventScript_CountTrainersDefeated::
	setvar VAR_0x8000, 0
	goto_if_not_defeated TRAINER_JACKI_1_SINNOH, VeilstoneCity_Gym_EventScript_CheckJocelyn
	addvar VAR_0x8000, 1
	goto VeilstoneCity_Gym_EventScript_CheckJocelyn

VeilstoneCity_Gym_EventScript_SetLightsOn::
	setflashlevel 0
	return

@ Brightest

VeilstoneCity_Gym_EventScript_AnimateFlash5Trainers::
	playse SE_SWITCH
	animateflash 2
	call VeilstoneCity_Gym_EventScript_SetFlashLevel
	return

VeilstoneCity_Gym_EventScript_AnimateFlash4Trainers::
	playse SE_SWITCH
	animateflash 3
	call VeilstoneCity_Gym_EventScript_SetFlashLevel
	return

VeilstoneCity_Gym_EventScript_AnimateFlash3Trainers::
	playse SE_SWITCH
	animateflash 4
	call VeilstoneCity_Gym_EventScript_SetFlashLevel
	return

VeilstoneCity_Gym_EventScript_AnimateFlash2Trainers::
	playse SE_SWITCH
	animateflash 5
	call VeilstoneCity_Gym_EventScript_SetFlashLevel
	return

VeilstoneCity_Gym_EventScript_AnimateFlash1Trainer::
	playse SE_SWITCH
	animateflash 6
	call VeilstoneCity_Gym_EventScript_SetFlashLevel
	return

VeilstoneCity_Gym_Text_ColbyDefeat::
	.string "Argh! Crunched!$"

VeilstoneCity_Gym_Text_ColbyIntro::
	.string "We're the Karate Quads!\p"
	.string "I will strike a blow for love with my\n"
	.string "fist! Hiyah, looooooooove!$"

VeilstoneCity_Gym_EventScript_Darren::
	trainerbattle_single TRAINER_JACKI_2_SINNOH, VeilstoneCity_Gym_Text_DarrenIntro, VeilstoneCity_Gym_Text_DarrenDefeat, VeilstoneCity_Gym_EventScript_JocelynBrightenRoom
	msgbox VeilstoneCity_Gym_Text_DarrenPost, MSGBOX_AUTOCLOSE
	end

VeilstoneCity_Gym_Text_DarrenPost::
	.string "To overwhelm by force… That is my\n"
	.string "ideal beat-down style.\p"
	.string "It doesn't seem to work that way with\n"
	.string "POKéMON, however.$"

VeilstoneCity_Gym_EventScript_JocelynBrightenRoom::
	call VeilstoneCity_Gym_EventScript_BrightenRoom
	release
	end

VeilstoneCity_Gym_Text_DarrenDefeat::
	.string "I couldn't force my way to victory…$"

VeilstoneCity_Gym_Text_DarrenIntro::
	.string "We're the Karate Quads!\p"
	.string "I will strike a blow for courage with my\n"
	.string "fist! Hiyah, couraaaaaaaaaaage!$"

VeilstoneCity_Gym_EventScript_Jeffery::
	trainerbattle_single TRAINER_JACKI_3_SINNOH, VeilstoneCity_Gym_Text_JefferyIntro, VeilstoneCity_Gym_Text_JefferyDefeat, VeilstoneCity_Gym_EventScript_LauraBrightenRoom
	msgbox VeilstoneCity_Gym_Text_JefferyPost, MSGBOX_AUTOCLOSE
	end

VeilstoneCity_Gym_Text_JefferyPost::
	.string "I lost because I didn't eat enough\n"
	.string "pizza.\p"
	.string "…No. Anything I say will sound like I'm\n"
	.string "making excuses.$"

VeilstoneCity_Gym_EventScript_LauraBrightenRoom::
	call VeilstoneCity_Gym_EventScript_BrightenRoom
	release
	end

VeilstoneCity_Gym_Text_JefferyDefeat::
	.string "I'm so hungry, kid… I don't have any\n"
	.string "strength left…$"

VeilstoneCity_Gym_Text_JefferyIntro::
	.string "We're the Karate Quads!\p"
	.string "I will strike a blow for tears with my\n"
	.string "fist! Hiyah, teeeeeeaaaaaaaaars!$"

VeilstoneCity_Gym_EventScript_Rafael::
	trainerbattle_single TRAINER_JACKI_4_SINNOH, VeilstoneCity_Gym_Text_RafaelIntro, VeilstoneCity_Gym_Text_RafaelDefeat, VeilstoneCity_Gym_EventScript_CristianBrightenRoom
	msgbox VeilstoneCity_Gym_Text_RafaelPost, MSGBOX_AUTOCLOSE
	end

VeilstoneCity_Gym_Text_RafaelPost::
	.string "I'll have to redo my training, though.\n"
	.string "MAYLENE's gonna trample me again…$"

VeilstoneCity_Gym_EventScript_CristianBrightenRoom::
	call VeilstoneCity_Gym_EventScript_BrightenRoom
	release
	end

VeilstoneCity_Gym_Text_RafaelDefeat::
	.string "We came up short, but not by much.$"

VeilstoneCity_Gym_Text_RafaelIntro::
	.string "We're the Karate Quads!\p"
	.string "I will strike a blow for hope with my\n"
	.string "fist! Hiyah, hoooooooooooooope!$"

VeilstoneCity_Gym_EventScript_Leader::
	goto_if_set FLAG_SYS_GAME_CLEAR, VeilstoneCity_Gym_EventScript_SNRematch
	trainerbattle_single TRAINER_CAMERON_5_SINNOH, VeilstoneCity_Gym_Text_LeaderIntro, VeilstoneCity_Gym_Text_LeaderDefeat, VeilstoneCity_Gym_EventScript_LeaderDefeated, NO_MUSIC
	goto_if_unset FLAG_RECEIVED_ITEM_TM60_FROM_MAYLENE, VeilstoneCity_Gym_EventScript_GiveTM
	msgbox VeilstoneCity_Gym_Text_LeaderPostBattle, MSGBOX_DEFAULT
	release
	end

VeilstoneCity_Gym_Text_LeaderPostBattle::
	.string "Gee, I'm hungry…\p"
	.string "Oh, sorry, it's nothing. I didn't say\n"
	.string "anything.\p"
	.string "{PLAYER}, I can't explain what it means\n"
	.string "to be strong.\p"
	.string "I don't know how much effort goes into\n"
	.string "being strong…\p"
	.string "But being with POKéMON lets us keep\n"
	.string "making the effort, doesn't it?$"

VeilstoneCity_Gym_EventScript_GiveTM::
	giveitem ITEM_TM60
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_ITEM_TM60_FROM_MAYLENE
	msgbox VeilstoneCity_Gym_Text_ExplainTM, MSGBOX_DEFAULT
	release
	end

VeilstoneCity_Gym_Text_ExplainTM::
	.string "That TM60 contains the move DRAIN\n"
	.string "PUNCH.\p"
	.string "Um… That move inflicts damage, and it\n"
	.string "robs the target's HP.$"

VeilstoneCity_Gym_EventScript_LeaderDefeated::
	call VeilstoneCity_Gym_EventScript_AnimateFlashFullBrightness
	setflag FLAG_SN_DEFEATED_DEWFORD_GYM
	message VeilstoneCity_Gym_Text_ReceivedBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox VeilstoneCity_Gym_Text_ExplainBadge, MSGBOX_DEFAULT
	setflag FLAG_SINNOH_BADGE3_GET
	settrainerflag TRAINER_JACKI_1_SINNOH
	settrainerflag TRAINER_JACKI_2_SINNOH
	settrainerflag TRAINER_JACKI_3_SINNOH
	settrainerflag TRAINER_JACKI_4_SINNOH
	goto VeilstoneCity_Gym_EventScript_GiveTM

VeilstoneCity_Gym_Text_ExplainBadge::
	.string "Um… I should explain about that\n"
	.string "official POKéMON LEAGUE GYM BADGE.\p"
	.string "With it, you can use the hidden move\n"
	.string "Fly outside of battle.\p"
	.string "Oh, and since you now have four GYM\n"
	.string "BADGES, POKéMON obtained in trades\p"
	.string "will obey you up to Lv. 50.\p"
	.string "Oh, and please take this as well.$"

VeilstoneCity_Gym_Text_ReceivedBadge::
	.string "{PLAYER} received the Cobble BADGE\n"
	.string "from MAYLENE.$"

VeilstoneCity_Gym_EventScript_AnimateFlashFullBrightness::
	playse SE_SWITCH
	animateflash 0
	call VeilstoneCity_Gym_EventScript_SetFlashLevel
	return

VeilstoneCity_Gym_Text_LeaderDefeat::
	.string "…OK. You win.\p"
	.string "That was a tough loss. I learned a lot\n"
	.string "from it.\p"
	.string "Please, accept this GYM BADGE.$"

VeilstoneCity_Gym_Text_LeaderIntro::
	.string "Hello. I'm pleased to meet you.\p"
	.string "I'm MAYLENE, and I'm the GYM LEADER.\p"
	.string "I don't really know what it means to be\n"
	.string "strong, or how I got to be the\p"
	.string "GYM LEADER.\p"
	.string "But I will do the best I can as the GYM\n"
	.string "LEADER.\p"
	.string "I take battling very seriously.\n"
	.string "Whenever you're ready!$"

VeilstoneCity_Gym_EventScript_SNRematch::
	lock
	faceplayer
	msgbox VeilstoneCity_Gym_EventScript_SNRematch_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, VeilstoneCity_Gym_EventScript_SNRematch_No
	msgbox VeilstoneCity_Gym_EventScript_SNRematch_Go, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_KATELYN_2_SINNOH, VeilstoneCity_Gym_EventScript_SNRematch_Defeat
	msgbox VeilstoneCity_Gym_EventScript_SNRematch_After, MSGBOX_DEFAULT
	release
	end

VeilstoneCity_Gym_EventScript_SNRematch_After::
	.string "That was a great battle! Come back\n"
	.string "anytime for another match!$"

VeilstoneCity_Gym_EventScript_SNRematch_Defeat::
	.string "Amazing… You really are the CHAMPION!$"

VeilstoneCity_Gym_EventScript_SNRematch_Go::
	.string "Then I won't hold back this time!$"

VeilstoneCity_Gym_EventScript_SNRematch_No::
	msgbox VeilstoneCity_Gym_EventScript_SNRematch_NoT, MSGBOX_DEFAULT
	release
	end

VeilstoneCity_Gym_EventScript_SNRematch_NoT::
	.string "Come back whenever you're ready!$"

VeilstoneCity_Gym_EventScript_SNRematch_Ask::
	.string "MAYLENE: You became the CHAMPION!\n"
	.string "Welcome back!\p"
	.string "I've been training even harder since\n"
	.string "our last battle.\p"
	.string "Will you battle me again?$"

VeilstoneCity_Gym_EventScript_PtGymGuide::
	lock
	faceplayer
	goto_if_set FLAG_SINNOH_BADGE3_GET, VeilstoneCity_Gym_EventScript_PtGymGuideAfter
	msgbox VeilstoneCity_Gym_Text_PtGymGuide, MSGBOX_DEFAULT
	msgbox VeilstoneCity_Gym_Text_SNGuideInfo, MSGBOX_DEFAULT
	release
	end

VeilstoneCity_Gym_Text_SNGuideInfo::
	.string "Let me tell you about this GYM!\p"
	.string "The GYM LEADER is MAYLENE, a young\n"
	.string "genius of Fighting-type battles who\l"
	.string "trains barefoot.\p"
	.string "She uses POKéMON like MEDITITE,\n"
	.string "MACHOKE and her partner LUCARIO.\p"
	.string "Fighting types are weak to Flying,\n"
	.string "Psychic and Fairy moves!\p"
	.string "This GYM is a pitch-dark maze. Every\n"
	.string "TRAINER you defeat makes the room a\l"
	.string "little brighter.\p"
	.string "Battle them all to light up the way to\n"
	.string "MAYLENE!$"

VeilstoneCity_Gym_Text_PtGymGuide::
	.string "Hey, there! How's it going,\n"
	.string "CHAMP-to-be?\p"
	.string "I'm the GYM guide! I help out TRAINERS\n"
	.string "who come to challenge the GYM LEADER.$"

VeilstoneCity_Gym_EventScript_PtGymGuideAfter::
	msgbox VeilstoneCity_Gym_Text_PtGymGuideAfter, MSGBOX_DEFAULT
	release
	end

VeilstoneCity_Gym_Text_PtGymGuideAfter::
	.string "Oh! {PLAYER}! You've beaten the GYM\n"
	.string "LEADER!\p"
	.string "Of course, I thought you'd win.$"

VeilstoneCity_Gym_EventScript_PtGymStatue::
	lockall
	goto_if_set FLAG_SINNOH_BADGE3_GET, VeilstoneCity_Gym_EventScript_PtGymStatueWon
	msgbox VeilstoneCity_Gym_Text_PtGymStatue, MSGBOX_DEFAULT
	releaseall
	end

VeilstoneCity_Gym_Text_PtGymStatue::
	.string "VEILSTONE CITY POKéMON GYM\n"
	.string "LEADER: MAYLENE$"

VeilstoneCity_Gym_EventScript_PtGymStatueWon::
	msgbox VeilstoneCity_Gym_Text_PtGymStatueWon, MSGBOX_DEFAULT
	releaseall
	end

VeilstoneCity_Gym_Text_PtGymStatueWon::
	.string "VEILSTONE CITY POKéMON GYM\n"
	.string "LEADER: MAYLENE\p"
	.string "Certified TRAINERS:\n"
	.string "{PLAYER}$"
