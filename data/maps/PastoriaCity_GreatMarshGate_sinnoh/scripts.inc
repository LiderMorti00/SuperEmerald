PastoriaCity_GreatMarshGate_sinnoh_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PastoriaCity_GreatMarshGate_OnFrame
	.byte 0

@ Super Emerald: the Great Marsh Safari Game (as in Platinum)
PastoriaCity_GreatMarshGate_OnFrame::
	map_script_2 VAR_SAFARI_WARP_STATE, SAFARI_WARP_MANUAL_EXIT, PastoriaCity_GreatMarshGate_EventScript_SNExitEarly
	map_script_2 VAR_SAFARI_WARP_STATE, SAFARI_WARP_NO_BALLS, PastoriaCity_GreatMarshGate_EventScript_SNGameOver
	map_script_2 VAR_SAFARI_WARP_STATE, SAFARI_WARP_NO_STEPS, PastoriaCity_GreatMarshGate_EventScript_SNGameOver
	map_script_2 VAR_SAFARI_WARP_STATE, SAFARI_WARP_NO_BALLS_MID_BATTLE, PastoriaCity_GreatMarshGate_EventScript_SNGameOver
	map_script_2 VAR_SAFARI_WARP_STATE, SAFARI_WARP_RETIRING, PastoriaCity_GreatMarshGate_EventScript_SNGameOver
	map_script_2 VAR_SAFARI_WARP_STATE, SAFARI_WARP_WHITEOUT, PastoriaCity_GreatMarshGate_EventScript_SNGameOver
	.2byte 0

PastoriaCity_GreatMarshGate_EventScript_SNCheckFive::
	specialvar VAR_RESULT, SinnohCountAllMons
	subvar VAR_RESULT, VAR_SN_SAFARI_START
	goto_if_lt VAR_RESULT, 5, Common_EventScript_NopReturn
	setflag FLAG_SN_MARSH_FIVE
	return

PastoriaCity_GreatMarshGate_EventScript_SNGameOver::
	lockall
	call PastoriaCity_GreatMarshGate_EventScript_SNCheckFive
	msgbox PastoriaCity_GreatMarshGate_Text_SNGameOver, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, PastoriaCity_GreatMarshGate_Movement_SNExit
	waitmovement 0
	setvar VAR_SAFARI_WARP_STATE, 0
	releaseall
	end

PastoriaCity_GreatMarshGate_EventScript_SNExitEarly::
	lockall
	msgbox PastoriaCity_GreatMarshGate_Text_SNLeaveEarly, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PastoriaCity_GreatMarshGate_EventScript_SNReturnToMarsh
	call PastoriaCity_GreatMarshGate_EventScript_SNCheckFive
	msgbox PastoriaCity_GreatMarshGate_Text_SNReturnBalls, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, PastoriaCity_GreatMarshGate_Movement_SNExit
	waitmovement 0
	safari_exitnowarp
	setvar VAR_SAFARI_WARP_STATE, 0
	releaseall
	end

PastoriaCity_GreatMarshGate_EventScript_SNReturnToMarsh::
	closemessage
	warp MAP_GREAT_MARSH_SINNOH, 37, 86
	waitstate
	end

PastoriaCity_GreatMarshGate_EventScript_SNCounter::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	showmoneybox 0, 0
	msgbox PastoriaCity_GreatMarshGate_Text_SNAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PastoriaCity_GreatMarshGate_EventScript_SNBack
	getpartysize
	goto_if_ne VAR_RESULT, PARTY_SIZE, PastoriaCity_GreatMarshGate_EventScript_SNRoom
	specialvar VAR_RESULT, ScriptCheckFreePokemonStorageSpace
	goto_if_eq VAR_RESULT, TRUE, PastoriaCity_GreatMarshGate_EventScript_SNRoom
	msgbox PastoriaCity_GreatMarshGate_Text_SNFull, MSGBOX_DEFAULT
	goto PastoriaCity_GreatMarshGate_EventScript_SNBack

PastoriaCity_GreatMarshGate_EventScript_SNRoom::
	checkmoney 500
	goto_if_eq VAR_RESULT, FALSE, PastoriaCity_GreatMarshGate_EventScript_SNNoMoney
	playse SE_SHOP
	removemoney 500
	updatemoneybox
	msgbox PastoriaCity_GreatMarshGate_Text_SNPay, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message PastoriaCity_GreatMarshGate_Text_SNBalls
	waitfanfare
	msgbox PastoriaCity_GreatMarshGate_Text_SNEnjoyMarsh, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	specialvar VAR_RESULT, SinnohCountAllMons
	copyvar VAR_SN_SAFARI_START, VAR_RESULT
	applymovement OBJ_EVENT_ID_PLAYER, PastoriaCity_GreatMarshGate_Movement_SNEnter
	waitmovement 0
	safari_enter SAFARI_EVENT_SINNOH
	warp MAP_GREAT_MARSH_SINNOH, 37, 86
	waitstate
	end

PastoriaCity_GreatMarshGate_EventScript_SNNoMoney::
	msgbox PastoriaCity_GreatMarshGate_Text_SNNoMoney, MSGBOX_DEFAULT
PastoriaCity_GreatMarshGate_EventScript_SNBack::
	closemessage
	hidemoneybox
	applymovement OBJ_EVENT_ID_PLAYER, PastoriaCity_GreatMarshGate_Movement_SNBack
	waitmovement 0
	releaseall
	end

PastoriaCity_GreatMarshGate_Movement_SNBack:
	walk_down
	step_end

PastoriaCity_GreatMarshGate_Movement_SNEnter:
	walk_up
	step_end

PastoriaCity_GreatMarshGate_Movement_SNExit:
	walk_down
	walk_down
	step_end

PastoriaCity_GreatMarshGate_Text_SNAsk:
	.string "Would you like to play the Safari\n"
	.string "Game? It costs ¥500.$"

PastoriaCity_GreatMarshGate_Text_SNPay:
	.string "That will be ¥500, please.\p"
	.string "Here are your SAFARI BALLS.$"

PastoriaCity_GreatMarshGate_Text_SNBalls:
	.string "{PLAYER} received 30 SAFARI BALLS.$"

PastoriaCity_GreatMarshGate_Text_SNEnjoyMarsh:
	.string "Please enjoy the GREAT MARSH!$"

PastoriaCity_GreatMarshGate_Text_SNFull:
	.string "Your PC boxes are full. Please make\n"
	.string "some room before you play.$"

PastoriaCity_GreatMarshGate_Text_SNNoMoney:
	.string "I'm sorry, but you don't have\n"
	.string "enough money.$"

PastoriaCity_GreatMarshGate_Text_SNGameOver:
	.string "Your Safari Game is over.\n"
	.string "Please come again!$"

PastoriaCity_GreatMarshGate_Text_SNLeaveEarly:
	.string "Are you going to leave the\n"
	.string "GREAT MARSH early?$"

PastoriaCity_GreatMarshGate_Text_SNReturnBalls:
	.string "Please return any SAFARI BALLS\n"
	.string "you have left.$"


PastoriaCity_GreatMarshGate_EventScript_PtNpc1::
	lock
	faceplayer
	goto_if_set FLAG_SN_MARSH_FIVE_PRIZE, PastoriaCity_GreatMarshGate_EventScript_PtNpc1_ExplainMatchupChecker
	goto_if_set FLAG_SN_MARSH_FIVE, PastoriaCity_GreatMarshGate_EventScript_SNCowgirlPrize
	msgbox PastoriaCity_GreatMarshGate_Text_PtNpc1_0, MSGBOX_DEFAULT
	goto PastoriaCity_GreatMarshGate_EventScript_PtNpc1_CowgirlEnd

PastoriaCity_GreatMarshGate_EventScript_PtNpc1_CowgirlEnd::
	release
	end

PastoriaCity_GreatMarshGate_Text_PtNpc1_0::
	.string "Howdy. You’re playing the Safari Game?\p"
	.string "How would you like to try my game out\n"
	.string "at the same time?\p"
	.string "The rule--yep, there’s only one--is\n"
	.string "real simple.\p"
	.string "All you have to do is capture five or\n"
	.string "more POKéMON in one Safari Game.\p"
	.string "If you can do that, I’ll give you\n"
	.string "something real rare!$"

PastoriaCity_GreatMarshGate_EventScript_SNCowgirlPrize::
	msgbox PastoriaCity_GreatMarshGate_Text_SNCowgirlWin, MSGBOX_DEFAULT
	giveitem ITEM_RARE_CANDY, 3
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SN_MARSH_FIVE_PRIZE
	goto PastoriaCity_GreatMarshGate_EventScript_PtNpc1_ExplainMatchupChecker

PastoriaCity_GreatMarshGate_EventScript_PtNpc1_ExplainMatchupChecker::
	msgbox PastoriaCity_GreatMarshGate_Text_PtNpc1_1, MSGBOX_DEFAULT
	goto PastoriaCity_GreatMarshGate_EventScript_PtNpc1_CowgirlEnd

PastoriaCity_GreatMarshGate_Text_PtNpc1_1::
	.string "Rare Candies make a POKéMON grow\n"
	.string "stronger in a snap.\p"
	.string "Use ’em well, and come back to the\n"
	.string "Great Marsh anytime, y’hear?$"

PastoriaCity_GreatMarshGate_Text_SNCowgirlWin::
	.string "So, how many POKéMON did you catch in\n"
	.string "your Safari Game? At least five?\p"
	.string "Ayup! You’ve done that all right! Isn’t\n"
	.string "that something!\p"
	.string "Well, here you are, then.$"

PastoriaCity_GreatMarshGate_EventScript_SNAttendant::
	lock
	faceplayer
	msgbox PastoriaCity_GreatMarshGate_Text_SNFirst, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PastoriaCity_GreatMarshGate_EventScript_SNNotFirst
	msgbox PastoriaCity_GreatMarshGate_Text_SNExplain, MSGBOX_DEFAULT
	release
	end

PastoriaCity_GreatMarshGate_Text_SNExplain::
	.string "When you enter the Great Marsh, you\n"
	.string "start with 30 Safari Balls.\p"
	.string "That’s the only kind of Ball you’re\n"
	.string "allowed to use in the Safari Game.\p"
	.string "The game is over when you run out of\n"
	.string "Safari Balls, or when you’ve walked\p"
	.string "500 steps.\p"
	.string "Please do enjoy the untamed nature of\n"
	.string "the Great Marsh!$"

PastoriaCity_GreatMarshGate_EventScript_SNNotFirst::
	msgbox PastoriaCity_GreatMarshGate_Text_SNEnjoy, MSGBOX_DEFAULT
	release
	end

PastoriaCity_GreatMarshGate_Text_SNEnjoy::
	.string "I see. Enjoy your Safari Game!$"

PastoriaCity_GreatMarshGate_Text_SNFirst::
	.string "Welcome to the Great Marsh! Is this\n"
	.string "your first Safari Game?$"

PastoriaCity_GreatMarshGate_EventScript_SNBinoculars::
	lockall
	msgbox PastoriaCity_GreatMarshGate_EventScript_SNBinoculars_T1, MSGBOX_DEFAULT
	special SinnohMarshBinoculars
	msgbox PastoriaCity_GreatMarshGate_EventScript_SNBinoculars_T2, MSGBOX_DEFAULT
	releaseall
	end

PastoriaCity_GreatMarshGate_EventScript_SNBinoculars_T2::
	.string "{PLAYER} looked through the\n"
	.string "binoculars... A wild {STR_VAR_1} can be\l"
	.string "seen in the Great Marsh today!$"

PastoriaCity_GreatMarshGate_EventScript_SNBinoculars_T1::
	.string "Use a pair of binoculars to look out\n"
	.string "over the Great Marsh.\p"
	.string "You can see what kinds of POKéMON can\n"
	.string "be caught, and where they are.$"
