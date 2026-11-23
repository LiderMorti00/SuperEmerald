AzaleaTown_House1_hns_MapScripts::
	.byte 0


CharcoalKiln_Text_Boss1::
	.string "The SLOWPOKE are back, and the\n"
	.string "rain came with them.\p"
	.string "That's good for our CHARCOAL\n"
	.string "business!\p"
	.string "My apprentice took our FARFETCH'D\n"
	.string "out to gather wood.$"

SE_J_AzaleaTown_House1_hns_AzaleaTown_House1_EventScript_Boss::
	msgbox CharcoalKiln_Text_Boss1, MSGBOX_NPC
	end

CharcoalKiln_Text_Apprentice1::
	.string "Where have all the SLOWPOKE gone?\p"
	.string "Are they out playing somewhere?$"

SE_J_AzaleaTown_House1_hns_AzaleaTown_House1_EventScript_Apprentice::
	msgbox CharcoalKiln_Text_Apprentice1, MSGBOX_NPC
	end

AzaleaTown_House1_EventScript_Farfetchd::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_FARFETCHD, CRY_MODE_NORMAL
	msgbox CharcoalKiln_Text_Farfetchd, MSGBOX_DEFAULT
	waitmoncry
	release
	end

CharcoalKiln_Text_Farfetchd::
	.string "FARFETCH'D: Kwaa!$"
