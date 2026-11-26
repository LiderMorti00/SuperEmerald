SSAqua_1F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SSAqua_1F_OnFrame
	.byte 0

SSAqua_1F_EventScript_Sailor3::
	msgbox SSAqua_1F_Text_Sailor3, MSGBOX_NPC
	end

SSAqua_1F_Text_Sailor3::
    .string "The passengers are all TRAINERS.\p"
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
	.string "The S.S. AQUA runs between OLIVINE\n"
	.string "and VERMILION. Welcome aboard!$"

SE_J_SSAqua_1F_hns_SSAqua_1F_EventScript_DoorSailor::
	goto_if_ne VAR_SE_CRUISE_STATE, 0, SE_EventScript_CruiseExitSailor
	msgbox SSAqua_1F_Text_Sailor1_ToVermilion, MSGBOX_NPC
	end
