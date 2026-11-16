OlivineCity_PortInside_hns_MapScripts::
	.byte 0


OlivinePort_Text_AskBoard::
    .string "Welcome to FAST SHIP S.S.AQUA.\p"
    .string "Will you be boarding today?$"

SE_J_OlivineCity_PortInside_hns_OlivinePort_EventScript_Sailor::
	msgbox OlivinePort_Text_AskBoard, MSGBOX_NPC
	end

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

OlivineCity_PortInside_Text_Nationaldex1::
	.string "PROF.OAK: Hello!\n"
	.string "You are starting to have the\l"
	.string "attitude of a CHAMPION, {PLAYER}!\p"
	.string "It's time for your POKéDEX to\n"
	.string "match who you are.\p"
	.string "Let me see your POKéDEX for a\n"
	.string "second.\p"
	.string "I'll upgrade your POKéDEX with the\n"
	.string "NATIONAL MODE.$"

SE_J_OlivineCity_PortInside_hns_OlivineCity_PortInside_EventScript_Oak::
	msgbox OlivineCity_PortInside_Text_Nationaldex1, MSGBOX_NPC
	end
