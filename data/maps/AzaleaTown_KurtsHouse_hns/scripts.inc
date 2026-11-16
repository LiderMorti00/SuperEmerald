AzaleaTown_KurtsHouse_hns_MapScripts::
	.byte 0


KurtsHouse_Text_KurtMakingBallsMustWait::
	.string "Hm? Who are you?\p"
	.string "{PLAYER}, eh? You want me to make\n"
	.string "some BALLS?\p"
	.string "Sorry, but that'll have to wait.\p"
	.string "Do you know TEAM ROCKET?\n"
	.string "Ah, don't worry.\p"
	.string "I'll tell you anyhow.\p"
	.string "TEAM ROCKET's an evil gang that\n"
	.string "uses POKéMON for their dirty work.\p"
	.string "They're supposed to have disbanded\n"
	.string "three years ago.\p"
	.string "Anyway, they're at the WELL,\n"
	.string "cutting off SLOWPOKETAILS to sell!\p"
	.string "So I'm going to go give them a\n"
	.string "lesson in pain!\p"
	.string "Hang on, SLOWPOKE! Old KURT\n"
	.string "is on his way!$"

SE_J_AzaleaTown_KurtsHouse_hns_AzaleaTown_KurtsHouse_EventScript_KurtBefore::
	msgbox KurtsHouse_Text_KurtMakingBallsMustWait, MSGBOX_NPC
	end

KurtsHouse_Text_GranddaughterSlowpokeGone::
	.string "The SLOWPOKE are gone… \n"
	.string "Were they taken away by bad people?$"

SE_J_AzaleaTown_KurtsHouse_hns_AzaleaTown_KurtsHouse_EventScript_Girl::
	msgbox KurtsHouse_Text_GranddaughterSlowpokeGone, MSGBOX_NPC
	end

KurtsHouse_Text_KurtAskYouHaveAnApricorn::
	.string "KURT: You have BERRIES for me?\p"
	.string "Fine! I'll turn them into POKé BALLS.$"

SE_J_AzaleaTown_KurtsHouse_hns_AzaleaTown_KurtsHouse_EventScript_Kurt::
	msgbox KurtsHouse_Text_KurtAskYouHaveAnApricorn, MSGBOX_NPC
	end

AzaleaTown_KurtsHouse_EventScript_CelebiStatue::
	msgbox KurtsHouse_Text_CelebiStatue, MSGBOX_SIGN
	closemessage
	end

KurtsHouse_Text_CelebiStatue::
	.string "It's a statue of the forest's\n"
	.string "protector.$"

AzaleaTown_KurtsHouse_EventScript_OakPhoto::
	msgbox KurtsHouse_Text_OakPhoto, MSGBOX_SIGN
	closemessage
	end

KurtsHouse_Text_OakPhoto::
	.string "…A young PROF. OAK?$"
