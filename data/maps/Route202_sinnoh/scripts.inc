Route202_sinnoh_MapScripts::
	.byte 0


Route202_EventScript_Dawn::


Route202_EventScript_Tristan::
	trainerbattle_single TRAINER_BILLY_SINNOH, Route202_Text_TristanIntro, Route202_Text_TristanDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route202_EventScript_Tristan_Rematch
	msgbox Route202_Text_TristanPost, MSGBOX_AUTOCLOSE
	end

Route202_Text_TristanPost::
	.string "Don't be shy about talking to TRAINERS\n"
	.string "you'd like to battle.\p"
	.string "POKéMON grow stronger and stronger\n"
	.string "from battling.$"

Route202_EventScript_Tristan_Rematch::
	trainerbattle_rematch TRAINER_BILLY_SINNOH, Route202_Text_TristanIntro, Route202_Text_TristanDefeat
	msgbox Route202_Text_TristanPost, MSGBOX_AUTOCLOSE
	end

Route202_Text_TristanDefeat::
	.string "Too strong! Too strong!$"

Route202_Text_TristanIntro::
	.string "You're a POKéMON TRAINER, and so am I!\n"
	.string "Our eyes met, so battle we must!$"

Route202_EventScript_Natalie::
	trainerbattle_single TRAINER_JOEY_SINNOH, Route202_Text_NatalieIntro, Route202_Text_NatalieDefeat
	msgbox Route202_Text_NataliePost, MSGBOX_AUTOCLOSE
	end

Route202_Text_NataliePost::
	.string "My POKéMON are all tuckered out! I\n"
	.string "need to go to a POKéMON CENTER!$"

Route202_Text_NatalieDefeat::
	.string "Oh, boo! I can't win!$"

Route202_Text_NatalieIntro::
	.string "I spy, with my little eye… A TRAINER!\p"
	.string "A battle, please!$"

Route202_EventScript_Logan::
	trainerbattle_single TRAINER_TIMMY_SINNOH, Route202_Text_LoganIntro, Route202_Text_LoganDefeat
	msgbox Route202_Text_LoganPost, MSGBOX_AUTOCLOSE
	end

Route202_Text_LoganPost::
	.string "It was fun battling! Yup! I'm going to\n"
	.string "battle everyone!$"

Route202_Text_LoganDefeat::
	.string "You beat me?! You've got talent!$"

Route202_Text_LoganIntro::
	.string "Let's have a POKéMON battle! Humph!\n"
	.string "But I'm gonna win!$"

Route202_EventScript_PtNpc1::
	msgbox Route202_Text_PtNpc1, MSGBOX_NPC
	end

Route202_Text_PtNpc1::
	.string "Some POKéMON only appear in the\n"
	.string "morning.\p"
	.string "Some only come out at night.\p"
	.string "I'll keep looking till I've seen them\n"
	.string "all!$"

Route202_EventScript_SNRadarCP::
	lock
	faceplayer
	checkplayergender
	goto_if_eq VAR_RESULT, FEMALE, Route202_EventScript_SNRadar_AL
	msgbox Route202_Text_SNRadarAD, MSGBOX_DEFAULT
	goto Route202_EventScript_SNRadar_AN

Route202_EventScript_SNRadar_AN::
	closemessage
	applymovement LOCALID_SN_R202_RADAR_CP, Common_Movement_FaceRight
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	checkplayergender
	goto_if_eq VAR_RESULT, FEMALE, Route202_EventScript_SNRadar_BL
	msgbox Route202_Text_SNRadarBD, MSGBOX_DEFAULT
	goto Route202_EventScript_SNRadar_BN

Route202_EventScript_SNRadar_BN::
	closemessage
	applymovement LOCALID_SN_R202_RADAR_CP, Route202_Movement_SNLookAround
	waitmovement 0
	checkplayergender
	goto_if_eq VAR_RESULT, FEMALE, Route202_EventScript_SNRadar_CL
	msgbox Route202_Text_SNRadarCD, MSGBOX_DEFAULT
	goto Route202_EventScript_SNRadar_CN

Route202_EventScript_SNRadar_CN::
	closemessage
	setflag FLAG_SN_R202_RADAR_DONE
	sn_walkto LOCALID_SN_R202_RADAR_CP, 0, 26, SN_SPEED_NORMAL, 0, 0, 0
	waitmovement LOCALID_SN_R202_RADAR_CP
	removeobject LOCALID_SN_R202_RADAR_CP
	setflag FLAG_SN_HIDE_R202_RADAR
	release
	end

Route202_Text_SNRadarCD::
	.string "Now, this is where it gets interesting.\p"
	.string "If you see another patch of rustling\n"
	.string "grass some distance away, go into it.\p"
	.string "You'll see the same kind of POKéMON as\n"
	.string "before.\p"
	.string "If you want to keep meeting the same\n"
	.string "kind of POKéMON, you should maybe\p"
	.string "use some Repels.$"

Route202_EventScript_SNRadar_CL::
	msgbox Route202_Text_SNRadarCL, MSGBOX_DEFAULT
	goto Route202_EventScript_SNRadar_CN

Route202_Text_SNRadarCL::
	.string "Now, here's the strange part.\p"
	.string "If you see another patch of rustling\n"
	.string "grass far away, it means the same kind\p"
	.string "of POKéMON is hiding there.\p"
	.string "So, if your aim is to keep seeing the\n"
	.string "same kind of POKéMON, you should\p"
	.string "consider using Repels.$"

Route202_Movement_SNLookAround::
	face_down
	delay_16
	face_up
	delay_16
	face_left
	delay_16
	face_player
	step_end

Route202_Text_SNRadarBD::
	.string "DAWN: See? Did you notice the tall\n"
	.string "grass rustling?\p"
	.string "There's a POKéMON in that patch of tall\n"
	.string "grass.\p"
	.string "If you go there, the POKéMON will come\n"
	.string "bursting out.$"

Route202_EventScript_SNRadar_BL::
	msgbox Route202_Text_SNRadarBL, MSGBOX_DEFAULT
	goto Route202_EventScript_SNRadar_BN

Route202_Text_SNRadarBL::
	.string "LUCAS: There! Did you see the tall\n"
	.string "grass rustling?\p"
	.string "There's a POKéMON in that patch of tall\n"
	.string "grass.\p"
	.string "Go in there, and the POKéMON will come\n"
	.string "leaping out.$"

Route202_Text_SNRadarAD::
	.string "DAWN: Hi, {PLAYER}! I was waiting for\n"
	.string "you.\p"
	.string "Let me show you how the POKé RADAR\n"
	.string "works.\p"
	.string "Let's not waste any time. So, when you\n"
	.string "use the POKé RADAR…$"

Route202_EventScript_SNRadar_AL::
	msgbox Route202_Text_SNRadarAL, MSGBOX_DEFAULT
	goto Route202_EventScript_SNRadar_AN

Route202_Text_SNRadarAL::
	.string "LUCAS: {PLAYER}.\p"
	.string "Let me explain how the POKé RADAR\n"
	.string "works.\p"
	.string "Let's give it a go. When you use the\n"
	.string "POKé RADAR…$"

Route202_EventScript_Sign1::
	msgbox Route202_Text_Sign1, MSGBOX_SIGN
	end

Route202_Text_Sign1::
	.string "ROUTE 202\p"
	.string "North: JUBILIFE CITY South:\n"
	.string "SANDGEM TOWN$"

Route202_EventScript_Sign2::
	msgbox Route202_Text_Sign2, MSGBOX_SIGN
	end

Route202_Text_Sign2::
	.string "TRAINER TIPS\p"
	.string "A POKéMON that is asleep or\n"
	.string "paralyzed is easier to catch!$"

Route202_EventScript_Sign3::
	msgbox Route202_Text_Sign3, MSGBOX_SIGN
	end

Route202_Text_Sign3::
	.string "TRAINER TIPS\p"
	.string "TRAINERS will challenge you as\n"
	.string "soon as your eyes meet. Be ready!$"
