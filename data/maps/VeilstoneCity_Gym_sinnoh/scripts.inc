	.include "data/maps/VeilstoneCity_Gym_sinnoh/gym_metatiles.inc"

VeilstoneCity_Gym_sinnoh_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, VeilstoneCity_Gym_OnLoad
	.byte 0

@ Super Emerald: two sliding panels. VAR_TEMP_1 = panel A (0: at 12,10 in front of the gap / 1: at 13,10),
@ VAR_TEMP_2 = panel B (0: at 8,5 in front of the last corridor / 1: at 9,5). Temp vars reset
@ when the player leaves, so the panels go back to their places.
VeilstoneCity_Gym_OnLoad::
	call_if_eq VAR_TEMP_1, 1, VeilstoneCity_Gym_EventScript_DrawPanelAMoved
	call_if_eq VAR_TEMP_2, 1, VeilstoneCity_Gym_EventScript_DrawPanelBMoved
	end

VeilstoneCity_Gym_EventScript_DrawPanelAMoved::
	setmetatile 12, 10, METATILE_VeilstoneGym_rail_l, FALSE
	setmetatile 13, 10, METATILE_VeilstoneGym_panel_r, TRUE
	return

VeilstoneCity_Gym_EventScript_DrawPanelAHome::
	setmetatile 12, 10, METATILE_VeilstoneGym_panel_l, TRUE
	setmetatile 13, 10, METATILE_VeilstoneGym_rail_r, FALSE
	return

VeilstoneCity_Gym_EventScript_DrawPanelBMoved::
	setmetatile 8, 5, METATILE_VeilstoneGym_rail_l, FALSE
	setmetatile 9, 5, METATILE_VeilstoneGym_panel_r, TRUE
	return

VeilstoneCity_Gym_EventScript_DrawPanelBHome::
	setmetatile 8, 5, METATILE_VeilstoneGym_panel_l, TRUE
	setmetatile 9, 5, METATILE_VeilstoneGym_rail_r, FALSE
	return

@ VAR_0x8004/5 = the tile the player faces
VeilstoneCity_Gym_EventScript_GetFacedTile::
	getplayerxy VAR_0x8004, VAR_0x8005
	call_if_eq VAR_FACING, DIR_NORTH, VeilstoneCity_Gym_EventScript_FaceNorth
	call_if_eq VAR_FACING, DIR_SOUTH, VeilstoneCity_Gym_EventScript_FaceSouth
	call_if_eq VAR_FACING, DIR_WEST, VeilstoneCity_Gym_EventScript_FaceWest
	call_if_eq VAR_FACING, DIR_EAST, VeilstoneCity_Gym_EventScript_FaceEast
	return

VeilstoneCity_Gym_EventScript_FaceNorth::
	subvar VAR_0x8005, 1
	return

VeilstoneCity_Gym_EventScript_FaceSouth::
	addvar VAR_0x8005, 1
	return

VeilstoneCity_Gym_EventScript_FaceWest::
	subvar VAR_0x8004, 1
	return

VeilstoneCity_Gym_EventScript_FaceEast::
	addvar VAR_0x8004, 1
	return

VeilstoneCity_Gym_EventScript_PanelA::
	lockall
	call VeilstoneCity_Gym_EventScript_GetFacedTile
	goto_if_eq VAR_TEMP_1, 1, VeilstoneCity_Gym_EventScript_PanelAMoved
	goto_if_ne VAR_0x8004, 12, VeilstoneCity_Gym_EventScript_PanelEnd
	goto_if_ne VAR_FACING, DIR_EAST, VeilstoneCity_Gym_EventScript_PanelWontBudge
	msgbox VeilstoneCity_Gym_Text_PushPanel, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, VeilstoneCity_Gym_EventScript_PanelEnd
	playse SE_M_STRENGTH
	call VeilstoneCity_Gym_EventScript_DrawPanelAMoved
	special DrawWholeMapView
	setvar VAR_TEMP_1, 1
	msgbox VeilstoneCity_Gym_Text_PanelSlid, MSGBOX_DEFAULT
	releaseall
	end

VeilstoneCity_Gym_EventScript_PanelAMoved::
	goto_if_ne VAR_0x8004, 13, VeilstoneCity_Gym_EventScript_PanelEnd
	goto_if_ne VAR_FACING, DIR_WEST, VeilstoneCity_Gym_EventScript_PanelNoFurther
	msgbox VeilstoneCity_Gym_Text_PushPanelBack, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, VeilstoneCity_Gym_EventScript_PanelEnd
	playse SE_M_STRENGTH
	call VeilstoneCity_Gym_EventScript_DrawPanelAHome
	special DrawWholeMapView
	setvar VAR_TEMP_1, 0
	msgbox VeilstoneCity_Gym_Text_PanelSlidBack, MSGBOX_DEFAULT
	releaseall
	end

VeilstoneCity_Gym_EventScript_PanelB::
	lockall
	call VeilstoneCity_Gym_EventScript_GetFacedTile
	goto_if_eq VAR_TEMP_2, 1, VeilstoneCity_Gym_EventScript_PanelBMoved
	goto_if_ne VAR_0x8004, 8, VeilstoneCity_Gym_EventScript_PanelEnd
	goto_if_ne VAR_FACING, DIR_EAST, VeilstoneCity_Gym_EventScript_PanelWontBudge
	msgbox VeilstoneCity_Gym_Text_PushPanel, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, VeilstoneCity_Gym_EventScript_PanelEnd
	playse SE_M_STRENGTH
	call VeilstoneCity_Gym_EventScript_DrawPanelBMoved
	special DrawWholeMapView
	setvar VAR_TEMP_2, 1
	msgbox VeilstoneCity_Gym_Text_PanelSlid, MSGBOX_DEFAULT
	releaseall
	end

VeilstoneCity_Gym_EventScript_PanelBMoved::
	goto_if_ne VAR_0x8004, 9, VeilstoneCity_Gym_EventScript_PanelEnd
	goto_if_ne VAR_FACING, DIR_WEST, VeilstoneCity_Gym_EventScript_PanelNoFurther
	msgbox VeilstoneCity_Gym_Text_PushPanelBack, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, VeilstoneCity_Gym_EventScript_PanelEnd
	playse SE_M_STRENGTH
	call VeilstoneCity_Gym_EventScript_DrawPanelBHome
	special DrawWholeMapView
	setvar VAR_TEMP_2, 0
	msgbox VeilstoneCity_Gym_Text_PanelSlidBack, MSGBOX_DEFAULT
	releaseall
	end

VeilstoneCity_Gym_EventScript_PanelWontBudge::
	msgbox VeilstoneCity_Gym_Text_PanelWontBudge, MSGBOX_DEFAULT
	releaseall
	end

VeilstoneCity_Gym_EventScript_PanelNoFurther::
	msgbox VeilstoneCity_Gym_Text_PanelNoFurther, MSGBOX_DEFAULT
	releaseall
	end

VeilstoneCity_Gym_EventScript_PanelEnd::
	releaseall
	end

VeilstoneCity_Gym_Text_PushPanel::
	.string "It's a sliding screen on a floor rail.\n"
	.string "Give it a push?$"

VeilstoneCity_Gym_Text_PushPanelBack::
	.string "The screen can slide back along its\n"
	.string "rail. Push it back?$"

VeilstoneCity_Gym_Text_PanelSlidBack::
	.string "The screen slid back to its stop!$"

VeilstoneCity_Gym_Text_PanelSlid::
	.string "The screen slid along its rail!$"

VeilstoneCity_Gym_Text_PanelWontBudge::
	.string "The screen won't budge from this side.\p"
	.string "There's a stop at this end of its\n"
	.string "rail. Push it from the other side!$"

VeilstoneCity_Gym_Text_PanelNoFurther::
	.string "The screen is at the end of its rail.\n"
	.string "It won't move any further.$"


VeilstoneCity_Gym_EventScript_Colby::
	trainerbattle_single TRAINER_JACKI_1_SINNOH, VeilstoneCity_Gym_Text_ColbyIntro, VeilstoneCity_Gym_Text_ColbyDefeat
	msgbox VeilstoneCity_Gym_Text_ColbyPost, MSGBOX_AUTOCLOSE
	end

VeilstoneCity_Gym_Text_ColbyPost::
	.string "Your POKéMON sure are tough!\p"
	.string "But our GYM LEADER MAYLENE will break\n"
	.string "you like a stack of bricks!$"

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

VeilstoneCity_Gym_Text_ColbyDefeat::
	.string "Argh! Crunched!$"

VeilstoneCity_Gym_Text_ColbyIntro::
	.string "We're the Karate Quads!\p"
	.string "I will strike a blow for love with my\n"
	.string "fist! Hiyah, looooooooove!$"

VeilstoneCity_Gym_EventScript_Darren::
	trainerbattle_single TRAINER_JACKI_2_SINNOH, VeilstoneCity_Gym_Text_DarrenIntro, VeilstoneCity_Gym_Text_DarrenDefeat
	msgbox VeilstoneCity_Gym_Text_DarrenPost, MSGBOX_AUTOCLOSE
	end

VeilstoneCity_Gym_Text_DarrenPost::
	.string "To overwhelm by force… That is my\n"
	.string "ideal beat-down style.\p"
	.string "It doesn't seem to work that way with\n"
	.string "POKéMON, however.$"

VeilstoneCity_Gym_Text_DarrenDefeat::
	.string "I couldn't force my way to victory…$"

VeilstoneCity_Gym_Text_DarrenIntro::
	.string "We're the Karate Quads!\p"
	.string "I will strike a blow for courage with my\n"
	.string "fist! Hiyah, couraaaaaaaaaaage!$"

VeilstoneCity_Gym_EventScript_Jeffery::
	trainerbattle_single TRAINER_JACKI_3_SINNOH, VeilstoneCity_Gym_Text_JefferyIntro, VeilstoneCity_Gym_Text_JefferyDefeat
	msgbox VeilstoneCity_Gym_Text_JefferyPost, MSGBOX_AUTOCLOSE
	end

VeilstoneCity_Gym_Text_JefferyPost::
	.string "I lost because I didn't eat enough\n"
	.string "pizza.\p"
	.string "…No. Anything I say will sound like I'm\n"
	.string "making excuses.$"

VeilstoneCity_Gym_Text_JefferyDefeat::
	.string "I'm so hungry, kid… I don't have any\n"
	.string "strength left…$"

VeilstoneCity_Gym_Text_JefferyIntro::
	.string "We're the Karate Quads!\p"
	.string "I will strike a blow for tears with my\n"
	.string "fist! Hiyah, teeeeeeaaaaaaaaars!$"

VeilstoneCity_Gym_EventScript_Rafael::
	trainerbattle_single TRAINER_JACKI_4_SINNOH, VeilstoneCity_Gym_Text_RafaelIntro, VeilstoneCity_Gym_Text_RafaelDefeat
	msgbox VeilstoneCity_Gym_Text_RafaelPost, MSGBOX_AUTOCLOSE
	end

VeilstoneCity_Gym_Text_RafaelPost::
	.string "I'll have to redo my training, though.\n"
	.string "MAYLENE's gonna trample me again…$"

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
	.string "Oh, and please take this as well.$"

VeilstoneCity_Gym_Text_ReceivedBadge::
	.string "{PLAYER} received the Cobble BADGE\n"
	.string "from MAYLENE.$"

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
	.string "This GYM is a training hall. Sliding\n"
	.string "screens on floor rails close the way.\p"
	.string "Push the sliding screens along\n"
	.string "their rails.\p"
	.string "Each screen runs toward the red\n"
	.string "arrows on its rail, so push it\l"
	.string "from the other side!\p"
	.string "The last one stands in front of\n"
	.string "MAYLENE's corridor. It only slides\l"
	.string "one way, so think about which side\l"
	.string "to push it from!\p"
	.string "If you get it wrong, just walk\n"
	.string "around and try the other side.\l"
	.string "The screens reset when you leave.$"

VeilstoneCity_Gym_Text_PtGymGuide::
	.string "Hey, there! How's it going,\n"
	.string "CHAMPION?\p"
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
