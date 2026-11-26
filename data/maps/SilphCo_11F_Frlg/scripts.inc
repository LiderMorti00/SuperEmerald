SilphCo_11F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SilphCo_11F_OnLoad
	.byte 0

SilphCo_11F_OnLoad::
	call_if_unset FLAG_SILPH_11F_DOOR, EventScript_Close11FDoor
	end

SilphCo_11F_EventScript_President::
	lock
	faceplayer
	call SE_EventScript_SilphPresidentGift
	goto_if_set FLAG_GOT_MASTER_BALL_FROM_SILPH, SilphCo_11F_EventScript_AlreadyGotMasterBall
	msgbox SilphCo_11F_Text_GiftForVisitingChampion
	checkitemspace ITEM_MASTER_BALL
	goto_if_eq VAR_RESULT, FALSE, SilphCo_11F_EventScript_NoRoomForMasterBall
	giveitem_msg SilphCo_11F_Text_ObtainedMasterBallFromPresident, ITEM_MASTER_BALL, 1, MUS_RG_OBTAIN_KEY_ITEM
	msgbox SilphCo_11F_Text_ThatsOurSecretPrototype
	setflag FLAG_GOT_MASTER_BALL_FROM_SILPH
	release
	end

SilphCo_11F_EventScript_NoRoomForMasterBall::
	msgbox SilphCo_11F_Text_YouHaveNoRoomForThis
	release
	end

SilphCo_11F_EventScript_AlreadyGotMasterBall::
	msgbox SilphCo_11F_Text_ThatsOurSecretPrototype
	release
	end

SilphCo_11F_EventScript_Secretary::
	msgbox SilphCo_11F_Text_SilphOpenToVisitors, MSGBOX_NPC
	end

SilphCo_11F_EventScript_FloorSign::
	msgbox SilphCo_11F_Text_FloorSign, MSGBOX_SIGN
	end

SilphCo_11F_Text_GiftForVisitingChampion::
	.string "PRESIDENT: Welcome to SILPH!\p"
	.string "Ever since TEAM ROCKET left,\n"
	.string "we've been busy with our research.\p"
	.string "I hear you're the CHAMPION of\n"
	.string "HOENN. I'd like you to have this.$"

SilphCo_11F_Text_ObtainedMasterBallFromPresident::
	.string "{PLAYER} obtained a MASTER BALL\n"
	.string "from the PRESIDENT!$"

SilphCo_11F_Text_ThatsOurSecretPrototype::
	.string "PRESIDENT: You can't buy that\n"
	.string "anywhere.\p"
	.string "It's our secret prototype MASTER\n"
	.string "BALL.\p"
	.string "It will catch any POKéMON without\n"
	.string "fail!\p"
	.string "You should be quiet about using it,\n"
	.string "though.$"

SilphCo_11F_Text_YouHaveNoRoomForThis::
	.string "You have no room for this.$"

SilphCo_11F_Text_SilphOpenToVisitors::
	.string "SECRETARY: Welcome!\p"
	.string "SILPH is open to visitors again.\n"
	.string "It's good to see people back here.$"

SilphCo_11F_Text_FloorSign::
	.string "SILPH CO. HEAD OFFICE\n"
	.string "11F$"

