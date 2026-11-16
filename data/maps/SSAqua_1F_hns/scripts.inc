SSAqua_1F_hns_MapScripts::
	.byte 0


SSAqua_1F_EventScript_Sailor3::
	msgbox SSAqua_1F_Text_Sailor3, MSGBOX_NPC
	end

SSAqua_1F_Text_Sailor3::
    .string "The passengers are all trainers.\p"
    .string "They're all itching to battle in\n"
    .string "their cabins.$"

SSAqua_1F_EventScript_RoomSailor::
	msgbox SSAqua_1F_Text_Sailor2_FirstTime, MSGBOX_NPC
	end

SSAqua_1F_Text_Sailor2_FirstTime::
    .string "Here's your cabin.\p"
    .string "If your POKéMON are hurt, take a\n"
    .string "nap in the bed.\p"
    .string "That will heal them.$"

SSAqua_1F_Text_Sailor1_ToVermilion::
    .string "FAST SHIP S.S.AQUA is en route to\n"
    .string "VERMILION CITY.\p"
    .string "We will make an announcement when\n"
    .string "we arrive.$"

SE_J_SSAqua_1F_hns_SSAqua_1F_EventScript_DoorSailor::
	msgbox SSAqua_1F_Text_Sailor1_ToVermilion, MSGBOX_NPC
	end
