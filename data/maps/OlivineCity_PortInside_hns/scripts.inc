OlivineCity_PortInside_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OlivineCity_PortInside_hns_OnFrame
	.byte 0

OlivineCity_PortInside_hns_OnFrame:
	map_script_2 VAR_SE_JOHTO_ARRIVAL, 1, SE_EventScript_OlivineJasmineArrival
	.2byte 0

OlivinePort_EventScript_Youngster::
	msgbox OlivinePort_Text_Youngster, MSGBOX_NPC
	end

OlivinePort_Text_Youngster::
    .string "S.S.AQUA uses jets to skim\n"
    .string "over the waves!$"

OlivinePort_EventScript_CooltrainerF::
	msgbox OlivinePort_Text_CooltrainerF, MSGBOX_NPC
	end

OlivinePort_Text_CooltrainerF::
    .string "There are lots of POKéMON in KANTO.\p"
    .string "I wish I could go…$"

OlivinePort_EventScript_Fisher2::
	msgbox OlivinePort_Text_FishingGuru2, MSGBOX_NPC
	end

OlivinePort_Text_FishingGuru2::
    .string "How many RODS do you have?\p"
    .string "Different RODS catch different\n"
    .string "POKéMON.$"

OlivinePort_EventScript_Fisher1::
	msgbox OlivinePort_Text_FishingGuru1, MSGBOX_NPC
	end

OlivinePort_Text_FishingGuru1::
    .string "SHELLDER are easy to catch here.\p"
    .string "They're kind of rare elsewhere.$"
