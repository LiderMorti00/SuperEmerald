GoldenrodCity_RadioTower_1F_hns_MapScripts::
	.byte 0

RadioTower1F_EventScript_Youngster::
	lock
	faceplayer
	msgbox RadioTower1F_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

RadioTower1F_Text_Youngster::
    .string "I love MARY, from POKéMON TALK.\p"
    .string "I only know what she sounds like,\n"
    .string "though.$"

RadioTower1F_EventScript_Lass::
	lock
	faceplayer
	msgbox RadioTower1F_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

RadioTower1F_Text_Lass::
    .string "BEN is a fabulous DJ.\p"
    .string "His sweet voice makes me melt!$"

RadioTower1F_Text_GruntM3Seen::
    .string "We've finally taken over the\n"
    .string "RADIO TOWER!\p"
    .string "Now everyone will get to experience\n"
    .string "the true terror of TEAM ROCKET!\p"
    .string "We'll show you how scary we are!$"

SE_J_GoldenrodCity_RadioTower_1F_hns_RadioTower1F_EventScript_Grunt::
	msgbox RadioTower1F_Text_GruntM3Seen, MSGBOX_NPC
	end

GoldenrodCity_RadioTower_1F_Text_LotteryCornerDrawTicket::
	.string "This is the POKéMON LOTTERY CORNER.\p"
	.string "If the LOTO TICKET's number matches\n"
	.string "the ID number of any of your POKéMON,\l"
	.string "you will receive a fabulous gift.\p"
	.string "Would you like to draw a POKéMON\n"
	.string "LOTO TICKET?$"

SE_J_GoldenrodCity_RadioTower_1F_hns_GoldenrodCity_RadioTower_1F_EventScript_LotteryClerk::
	lock
	faceplayer
	dotimebasedevents
	goto_if_ne VAR_POKELOT_PRIZE_ITEM, ITEM_NONE, LilycoveCity_DepartmentStore_1F_EventScript_GivePrizeFromEarlier
	goto_if_set FLAG_DAILY_PICKED_LOTO_TICKET, LilycoveCity_DepartmentStore_1F_EventScript_ComeBackTomorrow
	msgbox GoldenrodCity_RadioTower_1F_Text_LotteryCornerDrawTicket, MSGBOX_YESNO
	goto LilycoveCity_DepartmentStore_1F_EventScript_DrawTicketAnswer
	end

RadioTower1F_Text_ReceptionistWelcome::
    .string "Welcome!$"

SE_J_GoldenrodCity_RadioTower_1F_hns_RadioTower1F_EventScript_Reception::
	msgbox RadioTower1F_Text_ReceptionistWelcome, MSGBOX_NPC
	end

GoldenrodCity_RadioTower_1F_EventScript_Sign::
	lock
	msgbox RadioTower1F_Text_Directory, MSGBOX_SIGN
	closemessage
	release
	end

RadioTower1F_Text_Directory::
    .string "1F RECEPTION\n"
    .string "2F SALES\p"
    .string "3F PERSONNEL\n"
    .string "4F PRODUCTION\p"
    .string "5F DIRECTOR'S OFFICE$"
