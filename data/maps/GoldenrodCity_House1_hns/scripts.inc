GoldenrodCity_House1_hns_MapScripts::
	.byte 0


GoldenrodCity_NameRatersHouse_Text_PleasedToRateMonNickname::
	.string "Hi, hi! I'm the NAME RATER!\n"
	.string "I'm the fortune-teller of names!\p"
	.string "I shall be pleased to rate your\n"
	.string "POKéMON's nickname.$"

SE_J_GoldenrodCity_House1_hns_GoldenrodCity_NameRatersHouse_EventScript_NameRater::
	msgbox GoldenrodCity_NameRatersHouse_Text_PleasedToRateMonNickname, MSGBOX_NPC
	end

GoldenrodCity_NameRatersHouse_Text_RenameRival::
	.string "It's the news...\p"
	.string "The POLICE are looking for this\n"
	.string "REDHEADED BOY!\p"
	.string "Do YOU know his name?$"

SE_J_GoldenrodCity_House1_hns_GoldenrodCity_NameRatersHouse_EventScript_RenameRival::
	msgbox GoldenrodCity_NameRatersHouse_Text_RenameRival, MSGBOX_SIGN
	end
