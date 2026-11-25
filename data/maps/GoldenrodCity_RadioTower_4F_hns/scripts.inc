GoldenrodCity_RadioTower_4F_hns_MapScripts::
	.byte 0

GoldenrodCity_RadioTower_4F4_EventScript_Fisher::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_4F4_Text_Fisher, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_4F4_Text_Fisher::
	.string "I listened to the radio while I was\n"
	.string "at the RUINS.\p"
	.string "I heard a strange broadcast there.$"

GoldenrodCity_RadioTower_4F4_Text_DJMaryAfter::
	.string "MARY: Please tune into me on PROF.\n"
	.string "OAK'S POKéMON TALK show!$"

SE_J_GoldenrodCity_RadioTower_4F_hns_GoldenrodCity_RadioTower_4F4_EventScript_Mary::
	msgbox GoldenrodCity_RadioTower_4F4_Text_DJMaryAfter, MSGBOX_NPC
	end

GoldenrodCity_RadioTower_4F4_EventScript_Meowth::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MEOWTH, CRY_MODE_NORMAL
	msgbox GoldenrodCity_RadioTower_4F4_Text_Meowth, MSGBOX_DEFAULT
	waitmoncry
	release
	end

GoldenrodCity_RadioTower_4F4_Text_Meowth::
	.string "MEOWTH: MEOWTH…$"

GoldenrodCity_RadioTower_4F4_EventScript_Sign2::
	lock
	msgbox GoldenrodCity_RadioTower_4F4_Text_ProductionSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_4F4_Text_ProductionSign::
	.string "4F PRODUCTION$"

GoldenrodCity_RadioTower_4F4_EventScript_Sign1::
	lock
	msgbox GoldenrodCity_RadioTower_4F4_Text_Studio2Sign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_4F4_Text_Studio2Sign::
	.string "4F STUDIO 2$"
