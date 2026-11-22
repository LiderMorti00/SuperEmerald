SSAqua_RoomSSE_hns_MapScripts::
	.byte 0


SSAqua_RoomSSE_Text_CantFindGranddaughter::
	.string "My granddaughter loves this ship.\p"
	.string "Last time we sailed together, she\n"
	.string "talked the CAPTAIN into playing tag!$"

SE_J_SSAqua_RoomSSE_hns_SSAqua_RoomSSE_EventScript_Grandpa::
	msgbox SSAqua_RoomSSE_Text_CantFindGranddaughter, MSGBOX_NPC
	end

SSAqua_RoomSSE_EventScript_GrandDaughter::
	msgbox SSAqua_RoomSSE_Text_GranddaughterHadFun, MSGBOX_NPC
	end

SSAqua_RoomSSE_Text_GranddaughterHadFun::
    .string "I had lots of fun playing!$"
