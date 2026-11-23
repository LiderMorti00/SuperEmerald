LakeOfRage_House1_hns_MapScripts::
	.byte 0


HiddenPowerGuy_Text_Intro::
    .string "…You have strayed far…\p"
    .string "Here I have meditated. Inside me,\n"
    .string "a new power has been awakened.\p"
    .string "Let me share my power with your\n"
    .string "POKéMON. Take this, child.$"

SE_J_LakeOfRage_House1_hns_LakeOfRage_House1_EventScript_HiddenPowerGuy::
	lock
	faceplayer
	goto_if_set FLAG_SE_GOT_HIDDEN_POWER_TM, LakeOfRage_House1_EventScript_HiddenPowerGuyAfter
	msgbox HiddenPowerGuy_Text_Intro, MSGBOX_DEFAULT
	giveitem ITEM_TM_HIDDEN_POWER
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SE_GOT_HIDDEN_POWER_TM
LakeOfRage_House1_EventScript_HiddenPowerGuyAfter::
	msgbox HiddenPowerGuy_Text_After, MSGBOX_DEFAULT
	release
	end

HiddenPowerGuy_Text_After::
	.string "HIDDEN POWER changes with each\n"
	.string "POKéMON that learns it.\p"
	.string "Seek the power hidden within\n"
	.string "your POKéMON.$"
