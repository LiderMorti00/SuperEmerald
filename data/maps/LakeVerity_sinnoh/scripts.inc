LakeVerity_sinnoh_MapScripts::
	.byte 0

Sinnoh_EventScript_BufferCounterpartName::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Sinnoh_EventScript_BufferDawn
	bufferstring STR_VAR_1, Sinnoh_Text_Lucas
	return

Sinnoh_Text_Lucas::
	.string "LUCAS$"

Sinnoh_EventScript_BufferDawn::
	bufferstring STR_VAR_1, Sinnoh_Text_Dawn
	return

Sinnoh_Text_Dawn::
	.string "DAWN$"

LakeVerity_EventScript_Scene::
	lockall
	applymovement LOCALID_LAKE_BARRY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LakeVerity_Text_Cyrus, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_LAKE_BARRY, Common_Movement_FaceUp
	applymovement LOCALID_LAKE_CYRUS, LakeVerity_Movement_SNCyrusTurn
	waitmovement 0
	sn_walktoplayer LOCALID_LAKE_CYRUS, SN_SPEED_NORMAL
	waitmovement 0
	sn_playerface LOCALID_LAKE_CYRUS
	waitmovement LOCALID_PLAYER
	msgbox LakeVerity_Text_Cyrus2, MSGBOX_DEFAULT
	closemessage
	sn_walkto LOCALID_LAKE_CYRUS, 38, 43, SN_SPEED_NORMAL
	waitmovement 0
	removeobject LOCALID_LAKE_CYRUS
	applymovement LOCALID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	playmoncry SPECIES_MESPRIT, CRY_MODE_NORMAL
	waitmoncry
	msgbox LakeVerity_Text_Cry, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_LAKE_BARRY, Common_Movement_ExclamationMark
	waitmovement 0
	sn_walktoplayer LOCALID_LAKE_BARRY, SN_SPEED_FAST
	waitmovement 0
	sn_playerface LOCALID_LAKE_BARRY
	waitmovement LOCALID_PLAYER
	msgbox LakeVerity_Text_Barry, MSGBOX_DEFAULT
	closemessage
	sn_walkto LOCALID_LAKE_BARRY, 39, 43, SN_SPEED_FAST
	waitmovement 0
	removeobject LOCALID_LAKE_BARRY
	setflag FLAG_HIDE_LAKE_VERITY_ROWAN
	setvar VAR_SN_SINNOH_STORY, 7
	releaseall
	end

LakeVerity_Text_Barry::
	.string "{RIVAL}: What was that about? Weird\n"
	.string "guy…\p"
	.string "{RIVAL}: OK, {PLAYER}! Let's catch\n"
	.string "that legendary POKéMON!\p"
	.string "{RIVAL}: ! Did you hear that,\n"
	.string "{PLAYER}?!\p"
	.string "That was the legendary POKéMON\n"
	.string "crying! That had to be it!\p"
	.string "OK! This is our chance! Let's catch it!\p"
	.string "…Wait! What…?!\p"
	.string "We don't have anything on us!\p"
	.string "You know, POKé BALLS! P-O-K-accent-E\n"
	.string "Balls!\p"
	.string "If we don't have those, we can't catch\n"
	.string "POKéMON or take them around with us!\p"
	.string "…Do you think PROF. ROWAN'd give us\n"
	.string "some if we asked him?\p"
	.string "You know, you remember what he said,\n"
	.string "don't you?\p"
	.string "He said to visit him at his lab if we\n"
	.string "needed anything.\p"
	.string "OK, {PLAYER}! I'll race you!\p"
	.string "First one to the professor's lab in\n"
	.string "SANDGEM TOWN rules!$"

LakeVerity_Text_Cry::
	.string "Kyauuun!$"

LakeVerity_Text_Cyrus2::
	.string "???: Allow me to pass. Step aside.$"

LakeVerity_Movement_SNCyrusTurn::
	delay_16
	face_down
	delay_8
	step_end

LakeVerity_Text_Cyrus::
	.string "???: …The flowing time… …The\n"
	.string "expanding space…\p"
	.string "I will make it all mine one day… CYRUS\n"
	.string "is my name. Remember it…\p"
	.string "Until then, sleep while you can,\n"
	.string "legendary POKéMON of the lake bed…$"
