GoldenrodCity_BillsHouse_hns_MapScripts::
	.byte 0

BillHouse_Text_MomBeforeEcruteak::
	.string "Oh, you collect POKéMON? My son\n"
	.string "BILL is an expert.\p"
	.string "He's working at his SEA COTTAGE\n"
	.string "in KANTO these days.\p"
	.string "My husband went off to the GAME\n"
	.string "CORNER without being called…$"

SE_J_GoldenrodCity_BillsHouse_hns_GoldenrodCity_BillsHouse_EventScript_Mom::
	msgbox BillHouse_Text_MomBeforeEcruteak, MSGBOX_NPC
	end

GoldenrodCity_BillsHouse_EventScript_Sister::
	lock
	faceplayer
	msgbox BillHouse_Text_SisterStorageSystem, MSGBOX_DEFAULT
	closemessage
	release
	end

BillHouse_Text_SisterStorageSystem::
    .string "My big brother BILL made the PC\n"
    .string "POKéMON storage system.$"
