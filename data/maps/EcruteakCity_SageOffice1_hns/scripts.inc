EcruteakCity_SageOffice1_hns_MapScripts::
	.byte 0


EcruteakTinTowerEntrance_Text_WanderingSage::
	.string "The TIN TOWER ahead is a nine-\n"
	.string "tier tower of divine beauty.\p"
	.string "It soothes the soul of all who\n"
	.string "see it.$"

SE_J_EcruteakCity_SageOffice1_hns_EcruteakCity_SageOffice2_EventScript_SageB::
	msgbox EcruteakTinTowerEntrance_Text_WanderingSage, MSGBOX_NPC
	end

EcruteakCity_SageOffice2_EventScript_SageC::
	lock
	faceplayer
	msgbox EcruteakTinTowerEntrance_Text_Gramps, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakTinTowerEntrance_Text_Gramps::
	.string "Two towers… Two POKéMON…\p"
	.string "But when one burned down, both\n"
	.string "POKéMON flew away, never to return.$"

EcruteakTinTowerEntrance_Text_SageNoBadge::
	.string "TIN TOWER is off limits to the\n"
	.string "unworthy. Sorry but you'll have\l"
	.string "to leave.$"

SE_J_EcruteakCity_SageOffice1_hns_EcruteakCity_SageOffice2_EventScript_SageA::
	msgbox EcruteakTinTowerEntrance_Text_SageNoBadge, MSGBOX_NPC
	end

EcruteakCity_SageOffice1_EventScript_Sign::
	msgbox EcruteakCity_SageOffice1_Text_Sign, MSGBOX_SIGN
	end

EcruteakCity_SageOffice1_Text_Sign::
	.string "The bell of tin rings clearly for\n"
	.string "those under the tower's wing.$"
