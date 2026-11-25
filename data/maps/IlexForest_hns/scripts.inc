IlexForest_hns_MapScripts::
	.byte 0

IlexForest_Text_Kwaaaa::
	.string "FARFETCH'D: Kwaa!$"

SE_J_IlexForest_hns_IlexForest_EventScript_Farfetchd_1A::
	msgbox IlexForest_Text_Kwaaaa, MSGBOX_NPC
	end

IlexForest_EventScript_Picnicker::
	lock
	faceplayer
	msgbox IlexForest_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

IlexForest_Text_Lass::
	.string "Did something happen to the\n"
	.string "forest's guardian?$"

IlexForest_EventScript_BugcatcherWayne::
	trainerbattle_single TRAINER_WAYNE_HNS, IlexForest_Text_BugCatcherWayneSeen, IlexForest_Text_BugCatcherWayneBeaten
	msgbox IlexForest_Text_BugCatcherWayneAfter, MSGBOX_AUTOCLOSE
	end

IlexForest_Text_BugCatcherWayneAfter::
	.string "A POKéMON I've never seen before\n"
	.string "fell out of the tree when I used\l"
	.string "HEADBUTT.\p"
	.string "I ought to use HEADBUTT in other\n"
	.string "places too.$"

IlexForest_Text_BugCatcherWayneBeaten::
	.string "I hadn't seen that POKéMON before…$"

IlexForest_Text_BugCatcherWayneSeen::
	.string "Don't sneak up on me like that!\p"
	.string "You frightened a POKéMON away!$"

IlexForest_EventScript_FullHeal::
	finditem ITEM_FULL_HEAL
	end

IlexForest_EventScript_Ether::
	finditem ITEM_ETHER
	end

IlexForest_EventScript_SuperPotion::
	finditem ITEM_SUPER_POTION
	end

IlexForest_EventScript_Farfetchd_2A::
	lock
	faceplayer
	playmoncry SPECIES_FARFETCHD, CRY_MODE_NORMAL
	msgbox IlexForest_Text_Kwaaaa, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	goto_if_eq VAR_FACING, DIR_SOUTH, IlexForest_EventScript_Farfetchd_2B
	applymovement LOCALID_ILEX_FOREST_FARFETCHD_2, IlexForest_Movement_Farfetchd_2A
	waitmovement 0
	setflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_2
	removeobject LOCALID_ILEX_FOREST_FARFETCHD_2
	@add clockwise farfetchd
	clearflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_3
	addobject LOCALID_ILEX_FOREST_FARFETCHD_3
	release
	end

IlexForest_Movement_Farfetchd_2A::
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

IlexForest_EventScript_Farfetchd_2B::
	applymovement LOCALID_ILEX_FOREST_FARFETCHD_2, IlexForest_Movement_Farfetchd_2B
	waitmovement 0
	setflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_2
	removeobject LOCALID_ILEX_FOREST_FARFETCHD_2
	@add counterclockwise farfetchd
	clearflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_1
	addobject LOCALID_ILEX_FOREST_FARFETCHD_1
	release
	end

IlexForest_Movement_Farfetchd_2B::
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

IlexForest_EventScript_Farfetchd_4A::
	lock
	faceplayer
	playmoncry SPECIES_FARFETCHD, CRY_MODE_NORMAL
	msgbox IlexForest_Text_Kwaaaa, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	goto_if_eq VAR_FACING, DIR_SOUTH, IlexForest_EventScript_Farfetchd_4B
	applymovement LOCALID_ILEX_FOREST_FARFETCHD_4, IlexForest_Movement_Farfetchd_4A
	waitmovement 0
	setflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_4
	removeobject LOCALID_ILEX_FOREST_FARFETCHD_4
	@add clockwise farfetchd
	clearflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_3
	addobject LOCALID_ILEX_FOREST_FARFETCHD_3
	release
	end

IlexForest_Movement_Farfetchd_4A::
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

IlexForest_EventScript_Farfetchd_4B::
	applymovement LOCALID_ILEX_FOREST_FARFETCHD_4, IlexForest_Movement_Farfetchd_4B
	waitmovement 0
	setflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_4
	removeobject LOCALID_ILEX_FOREST_FARFETCHD_4
	@add counterclockwise farfetchd
	clearflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_1
	addobject LOCALID_ILEX_FOREST_FARFETCHD_1
	release
	end

IlexForest_Movement_Farfetchd_4B::
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

IlexForest_EventScript_Farfetchd_3A::
	lock
	faceplayer
	playmoncry SPECIES_FARFETCHD, CRY_MODE_NORMAL
	msgbox IlexForest_Text_Kwaaaa, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	goto_if_eq VAR_FACING, DIR_SOUTH, IlexForest_EventScript_Farfetchd_3B
	applymovement LOCALID_ILEX_FOREST_FARFETCHD_3, IlexForest_Movement_Farfetchd_3A
	waitmovement 0
	setflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_3
	removeobject LOCALID_ILEX_FOREST_FARFETCHD_3
	@add clockwise farfetchd
	clearflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_2
	addobject LOCALID_ILEX_FOREST_FARFETCHD_2
	release
	end

IlexForest_Movement_Farfetchd_3A::
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

IlexForest_EventScript_Farfetchd_3B::
	applymovement LOCALID_ILEX_FOREST_FARFETCHD_3, IlexForest_Movement_Farfetchd_3B
	waitmovement 0
	setflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_3
	removeobject LOCALID_ILEX_FOREST_FARFETCHD_3
	@add counterclockwise farfetchd
	clearflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_4
	addobject LOCALID_ILEX_FOREST_FARFETCHD_4
	release
	end

IlexForest_Movement_Farfetchd_3B::
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

SE_J_IlexForest_hns_IlexForest_EventScript_Item_FalseSwipe::
	end

IlexForest_Text_Shrine::
	.string "ILEX FOREST SHRINE…\p"
	.string "It's in honor of the forest's\n"
	.string "protector…$"

SE_J_IlexForest_hns_IlexForest_EventScript_Shrine::
	lockall
	msgbox IlexForest_Text_Shrine, MSGBOX_DEFAULT
	goto_if_set FLAG_SE_DONE_CELEBI, IlexForest_EventScript_ShrineEnd
	goto_if_set FLAG_SE_GS_BALL_PLACED, IlexForest_EventScript_ShrineCelebi
	checkitem ITEM_GS_BALL
	goto_if_eq VAR_RESULT, FALSE, IlexForest_EventScript_ShrineEnd
	msgbox IlexForest_Text_ShrinePlaceGSBall, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, IlexForest_EventScript_ShrineEnd
	removeitem ITEM_GS_BALL
	setflag FLAG_SE_GS_BALL_PLACED
	msgbox IlexForest_Text_ShrineGSBallPlaced, MSGBOX_DEFAULT
	closemessage
IlexForest_EventScript_ShrineCelebi::
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 8
	setvar VAR_0x8007, 5
	special ShakeCamera
	waitstate
	waitse
	playmoncry SPECIES_CELEBI, CRY_MODE_ENCOUNTER
	msgbox IlexForest_Text_ShrineCelebi, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	setwildbattle SPECIES_CELEBI, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, IlexForest_EventScript_CelebiRan
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, IlexForest_EventScript_CelebiRan
	setflag FLAG_SE_DONE_CELEBI
	releaseall
	end

IlexForest_EventScript_CelebiRan::
	setvar VAR_0x8004, SPECIES_CELEBI
	goto Common_EventScript_LegendaryFlewAway
	end

IlexForest_EventScript_ShrineEnd::
	releaseall
	end

IlexForest_Text_ShrinePlaceGSBall:
	.string "The GS BALL is trembling…\p"
	.string "Place the GS BALL on the shrine?$"

IlexForest_Text_ShrineGSBallPlaced:
	.string "{PLAYER} placed the GS BALL on\n"
	.string "the shrine…$"

IlexForest_Text_ShrineCelebi:
	.string "Something is coming out of the\n"
	.string "forest's shadows!$"

IlexForest_EventScript_Sign::
	lock
	msgbox IlexForest_Text_Signpost, MSGBOX_SIGN
	closemessage
	release
	end

IlexForest_Text_Signpost::
	.string "ILEX FOREST is so overgrown with\n"
	.string "trees that you can't see the sky.\p"
	.string "Please watch out for items that may\n"
	.string "have been dropped.$"
