LakeOfRage_House1_hns_MapScripts::
	.byte 0


HiddenPowerGuy_Text_Intro::
    .string "…You have strayed far…\p"
    .string "Here I have meditated. Inside me,\n"
    .string "a new power has been awakened.\p"
    .string "Let me share my power with your\n"
    .string "POKéMON. Take this, child.$"

SE_J_LakeOfRage_House1_hns_LakeOfRage_House1_EventScript_HiddenPowerGuy::
	msgbox HiddenPowerGuy_Text_Intro, MSGBOX_NPC
	end
