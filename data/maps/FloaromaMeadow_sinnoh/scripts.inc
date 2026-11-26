FloaromaMeadow_sinnoh_MapScripts::
	.byte 0

SN_HoneyTree_Text_Wait::
	.string "The bark is slathered with HONEY…$"

SN_HoneyTree_Text_Mon::
	.string "A wild {STR_VAR_1} appeared from the\n"
	.string "tree you slathered with HONEY!$"

SN_HoneyTree_Text_Done::
	.string "The bark was slathered with HONEY.$"

SN_HoneyTree_Text_Ask::
	.string "Slather the bark with HONEY?$"

SN_HoneyTree_Text_Scent::
	.string "There is a sweet scent in the air…$"

FloaromaMeadow_EventScript_HoneyMan::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_MEADOW_GRUNTS, FloaromaMeadow_EventScript_HoneyManNormal
	msgbox FloaromaMeadow_Text_HoneyHelp, MSGBOX_DEFAULT
	release
	end

FloaromaMeadow_Text_HoneyHelp::
	.string "Help! These people want to take\n"
	.string "all my HONEY!$"

FloaromaMeadow_EventScript_HoneyManNormal::
	msgbox FloaromaMeadow_Text_HoneyInfo, MSGBOX_DEFAULT
	release
	end

FloaromaMeadow_Text_HoneyInfo::
	.string "Slather that HONEY on a sweet-smelling\n"
	.string "tree. It might attract POKéMON.$"

FloaromaMeadow_EventScript_SNHoneyTree::
	lock
	goto_if_ne VAR_SN_HONEY_TREE, 16, FloaromaMeadow_EventScript_SNHoneyTree_Fresh
	special SinnohHoneyReady
	goto_if_eq VAR_RESULT, TRUE, FloaromaMeadow_EventScript_SNHoneyTree_Battle
	msgbox SN_HoneyTree_Text_Wait, MSGBOX_DEFAULT
	release
	end

FloaromaMeadow_EventScript_SNHoneyTree_Battle::
	setvar VAR_SN_HONEY_TREE, 0
	setwildbattle SPECIES_WURMPLE, 5
	special SinnohHoneyTreeMon
	msgbox SN_HoneyTree_Text_Mon, MSGBOX_DEFAULT
	closemessage
	dowildbattle
	release
	end

FloaromaMeadow_EventScript_SNHoneyTree_End::
	release
	end

FloaromaMeadow_EventScript_SNHoneyTree_Fresh::
	msgbox SN_HoneyTree_Text_Scent, MSGBOX_DEFAULT
	checkitem ITEM_HONEY
	goto_if_eq VAR_RESULT, FALSE, FloaromaMeadow_EventScript_SNHoneyTree_End
	msgbox SN_HoneyTree_Text_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FloaromaMeadow_EventScript_SNHoneyTree_End
	removeitem ITEM_HONEY
	setvar VAR_SN_HONEY_TREE, 16
	special SinnohHoneySlather
	msgbox SN_HoneyTree_Text_Done, MSGBOX_DEFAULT
	goto FloaromaMeadow_EventScript_SNHoneyTree_End
