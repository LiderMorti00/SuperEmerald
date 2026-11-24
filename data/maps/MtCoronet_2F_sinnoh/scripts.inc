MtCoronet_2F_sinnoh_MapScripts::
	.byte 0

MtCoronet_2F_EventScript_PtNpc1::
	lock
	faceplayer
	goto_if_unset FLAG_RECEIVED_SN_MT_CORONET_2F_BLACK_FLUTE, MtCoronet_2F_EventScript_PtNpc1_TryAgainGiveBlackFlute
	msgbox MtCoronet_2F_Text_PtNpc1_0, MSGBOX_DEFAULT
	release
	end

MtCoronet_2F_Text_PtNpc1_0::
	.string "MT. CORONET is full of surprises.\n"
	.string "Who knows what else is buried here?$"

MtCoronet_2F_EventScript_PtNpc1_TryAgainGiveBlackFlute::
	msgbox MtCoronet_2F_Text_PtNpc1_1, MSGBOX_DEFAULT
	giveitem ITEM_BLACK_FLUTE, 1
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	call MtCoronet_2F_EventScript_PtNpc1_YouMustStopTeamGalactic
	release
	end

MtCoronet_2F_EventScript_PtNpc1_YouMustStopTeamGalactic::
	setflag FLAG_RECEIVED_SN_MT_CORONET_2F_BLACK_FLUTE
	msgbox MtCoronet_2F_Text_PtNpc1_2, MSGBOX_DEFAULT
	return

MtCoronet_2F_Text_PtNpc1_2::
	.string "MT. CORONET is full of surprises.\n"
	.string "Who knows what else is buried here?$"

MtCoronet_2F_Text_PtNpc1_1::
	.string "Phew… These tunnels go on forever.\p"
	.string "I found this odd flute while I was\n"
	.string "digging. I've no use for it, though.\p"
	.string "Here, you can have it.$"
