Route7_EventScript_Door::
	msgbox Route7_Text_LockedDoor, MSGBOX_SIGN
	end

Route7_Text_LockedDoor::
	.string "It's locked…$"

EventScript_Whirlpool::
	lockall
	goto_if_unset FLAG_JOHTO_BADGE7_GET, EventScript_CantWhirlpool
	@checkpartymove MOVE_WHIRLPOOL @checkpartymove doesn't work for the 8th hm i guess.
	@goto_if_eq VAR_RESULT, FALSE, EventScript_CantWhirlpool
	playse SE_M_WATERFALL
	goto_if_eq VAR_FACING, DIR_NORTH, EventScript_WhirlpoolGoNorth
	goto_if_eq VAR_FACING, DIR_SOUTH, EventScript_WhirlpoolGoSouth
	goto_if_eq VAR_FACING, DIR_EAST, EventScript_WhirlpoolGoEast
	goto_if_eq VAR_FACING, DIR_WEST, EventScript_WhirlpoolGoWest
	releaseall
	end

EventScript_WhirlpoolGoWest::
	applymovement OBJ_EVENT_ID_PLAYER, Movement_WhirlpoolWest
	waitmovement 0
	releaseall
	end

Movement_WhirlpoolWest::
	slide_left
	slide_left
	slide_left
	step_end

EventScript_WhirlpoolGoEast::
	applymovement OBJ_EVENT_ID_PLAYER, Movement_WhirlpoolEast
	waitmovement 0
	releaseall
	end

Movement_WhirlpoolEast::
	slide_right
	slide_right
	slide_right
	step_end

EventScript_WhirlpoolGoSouth::
	applymovement OBJ_EVENT_ID_PLAYER, Movement_WhirlpoolSouth
	waitmovement 0
	releaseall
	end

Movement_WhirlpoolSouth::
	slide_down
	slide_down
	slide_down
	step_end

EventScript_WhirlpoolGoNorth::
	applymovement OBJ_EVENT_ID_PLAYER, Movement_WhirlpoolNorth
	waitmovement 0
	releaseall
	end

Movement_WhirlpoolNorth::
	slide_up
	slide_up
	slide_up
	step_end

EventScript_CantWhirlpool::
	msgbox Text_CantWhirlpool, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

Text_CantWhirlpool::
	.string "The water is swirling and spinning\n"
	.string "around with a mighty roar.$"

IlexForest_EventScript_HeadbuttMoveTutor::
	lock
	faceplayer
	move_tutor MOVE_HEADBUTT, MoveTutor_Text_HeadbuttTeach, MoveTutor_Text_HeadbuttWhichMon, MoveTutor_EventScript_HeadbuttDeclined, MoveTutor_EventScript_HeadbuttTaught
	end

MoveTutor_EventScript_HeadbuttTaught::
	setflag FLAG_GET_HEADBUTT
	msgbox MoveTutor_Text_HeadbuttTaught, MSGBOX_DEFAULT
	release
	end

MoveTutor_Text_HeadbuttTaught::
	.string "Rattle trees with HEADBUTT.\n"
	.string "Sometimes, sleeping POKéMON fall out.$"

MoveTutor_EventScript_HeadbuttDeclined::
	msgbox MoveTutor_Text_HeadbuttDeclined, MSGBOX_DEFAULT
	release
	end

MoveTutor_Text_HeadbuttDeclined::
	.string "You don't need to be shy about it.\n"
	.string "Let's butt heads!$"

MoveTutor_Text_HeadbuttWhichMon::
	.string "Ehehe, sure thing! It'd be great if\n"
	.string "the POKéMON looked like me.$"

MoveTutor_Text_HeadbuttTeach::
	.string "What am I doing?\p"
	.string "I'm shaking trees using HEADBUTT.\p"
	.string "Do you think your POKéMON will\n"
	.string "want to HEADBUTT, too?\p"
	.string "I can teach one the move HEADBUTT\n"
	.string "if you'd like. It's fun!$"
