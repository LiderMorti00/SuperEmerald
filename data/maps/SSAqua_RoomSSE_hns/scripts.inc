SSAqua_RoomSSE_hns_MapScripts::
	.byte 0


SSAqua_RoomSSE_Text_CantFindGranddaughter::
    .string "Oh, hello…\p"
    .string "I still can't find my\n"
    .string "granddaughter.\p"
    .string "If she's on the ship,\n"
    .string "that's OK.\p"
    .string "She's an energetic child,\n"
    .string "so she may be bugging someone\l"
    .string "I'm worried…$"

SE_J_SSAqua_RoomSSE_hns_SSAqua_RoomSSE_EventScript_Grandpa::
	msgbox SSAqua_RoomSSE_Text_CantFindGranddaughter, MSGBOX_NPC
	end

SSAqua_RoomSSE_EventScript_GrandDaughter::
	msgbox SSAqua_RoomSSE_Text_GranddaughterHadFun, MSGBOX_NPC
	end

SSAqua_RoomSSE_Text_GranddaughterHadFun::
    .string "I had lots of fun playing!$"
