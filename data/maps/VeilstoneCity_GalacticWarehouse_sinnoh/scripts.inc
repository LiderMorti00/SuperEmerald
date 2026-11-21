VeilstoneCity_GalacticWarehouse_sinnoh_MapScripts::
	.byte 0


VeilstoneCity_GalacticWarehouse_EventScript_SNLooker_End::
	release
	end

VeilstoneCity_GalacticWarehouse_EventScript_SNLooker_After::
	msgbox VeilstoneCity_GalacticWarehouse_EventScript_SNLooker_T2, MSGBOX_DEFAULT
	goto VeilstoneCity_GalacticWarehouse_EventScript_SNLooker_End

VeilstoneCity_GalacticWarehouse_EventScript_SNLooker::
	lock
	faceplayer
	goto_if_set FLAG_SN_VEIL_STORAGE_OPEN, VeilstoneCity_GalacticWarehouse_EventScript_SNLooker_Key
	goto_if_set FLAG_SN_RECEIVED_HM_FLY, VeilstoneCity_GalacticWarehouse_EventScript_SNLooker_After
	msgbox VeilstoneCity_GalacticWarehouse_EventScript_SNLooker_T1, MSGBOX_DEFAULT
	giveitem ITEM_HM02
	goto_if_eq VAR_RESULT, FALSE, VeilstoneCity_GalacticWarehouse_EventScript_SNLooker_End
	setflag FLAG_SN_RECEIVED_HM_FLY
	goto VeilstoneCity_GalacticWarehouse_EventScript_SNLooker_After

VeilstoneCity_GalacticWarehouse_EventScript_SNLooker_T1::
	.string "LOOKER: Ah, this Hidden Machine… It is\n"
	.string "of the hidden move FLY.\p"
	.string "{PLAYER}, this, you should be keeping.\p"
	.string "It will not do to leave this item here\n"
	.string "to be used by the TEAM GALACTIC.$"

VeilstoneCity_GalacticWarehouse_EventScript_SNLooker_T2::
	.string "LOOKER: So, we did not learn very much\n"
	.string "from this exercise… No matter.\p"
	.string "What concerns me is what I have\n"
	.string "overheard in the Game Corner.\p"
	.string "The TEAM GALACTIC has transported\n"
	.string "something to PASTORIA CITY.\p"
	.string "What they are up to, I do not know, but\n"
	.string "I have bad feelings about it.$"

VeilstoneCity_GalacticWarehouse_EventScript_SNLooker_Key::
	msgbox VeilstoneCity_GalacticWarehouse_EventScript_SNLooker_K1, MSGBOX_DEFAULT
	msgbox VeilstoneCity_GalacticWarehouse_EventScript_SNLooker_K2, MSGBOX_DEFAULT
	msgbox VeilstoneCity_GalacticWarehouse_EventScript_SNLooker_K3, MSGBOX_DEFAULT
	release
	end

VeilstoneCity_GalacticWarehouse_EventScript_SNLooker_K3::
	.string "I will go on ahead, my friend. Do not\n"
	.string "expose yourself to danger!$"

VeilstoneCity_GalacticWarehouse_EventScript_SNLooker_K2::
	.string "LOOKER: I will use this STORAGE KEY I\n"
	.string "have obtained from the TEAM GALACTIC…\p"
	.string "…Ker-chunk!\p"
	.string "Yes! It is opened!$"

VeilstoneCity_GalacticWarehouse_EventScript_SNLooker_K1::
	.string "LOOKER: Ah, hello! I have kept you\n"
	.string "waiting.$"
