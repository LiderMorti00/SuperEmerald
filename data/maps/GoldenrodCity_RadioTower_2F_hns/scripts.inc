GoldenrodCity_RadioTower_2F_hns_MapScripts::
	.byte 0

GoldenrodCity_RadioTower_2F_EventScript_Jigglypuff::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_JIGGLYPUFF, CRY_MODE_NORMAL
	msgbox GoldenrodCity_RadioTower_2F_Text_Jigglypuff, MSGBOX_DEFAULT
	waitmoncry
	release
	end

GoldenrodCity_RadioTower_2F_Text_Jigglypuff::
	.string "JIGGLYPUFF: Jiggly…$"

GoldenrodCity_RadioTower_2F_Text_Teacher::
	.string "Lullabies on the radio may make\n"
	.string "POKéMON sleep.$"

SE_J_GoldenrodCity_RadioTower_2F_hns_GoldenrodCity_RadioTower_2F_EventScript_Teacher::
	msgbox GoldenrodCity_RadioTower_2F_Text_Teacher, MSGBOX_NPC
	end

GoldenrodCity_RadioTower_2F_EventScript_Boy::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_2F_Text_SuperNerd, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_Text_SuperNerd::
	.string "You can listen to the radio\n"
	.string "anywhere. Tune in!$"

GoldenrodCity_RadioTower_2F_Text_BuenaAskPassword::
	.string "BUENA: Hi there! I'm BUENA, the host\n"
	.string "of BUENA'S PASSWORD!\p"
	.string "The show is taking a little break\n"
	.string "right now. Tune in again soon!$"

SE_J_GoldenrodCity_RadioTower_2F_hns_GoldenrodCity_RadioTower_2F_EventScript_Buena::
	msgbox GoldenrodCity_RadioTower_2F_Text_BuenaAskPassword, MSGBOX_NPC
	end

GoldenrodCity_RadioTower_2F_EventScript_Policeman::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_2F_Text_Policeman, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_Text_Policeman::
	.string "Restricted access beyond this\n"
	.string "point.$"

GoldenrodCity_RadioTower_2F_EventScript_Sign1::
	lock
	msgbox GoldenrodCity_RadioTower_2F_Text_SalesSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_Text_SalesSign::
	.string "2F SALES$"

GoldenrodCity_RadioTower_2F_EventScript_Sign2::
	lock
	msgbox GoldenrodCity_RadioTower_2F_Text_OakTalkSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_Text_OakTalkSign::
	.string "PROF.OAK'S POKéMON TALK\p"
	.string "The Hottest Show on the Air!$"
