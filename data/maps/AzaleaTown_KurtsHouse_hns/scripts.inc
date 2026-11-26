AzaleaTown_KurtsHouse_hns_MapScripts::
	.byte 0

KurtsHouse_Text_GranddaughterSlowpokeGone::
	.string "The SLOWPOKE came back to town!\p"
	.string "Grandpa says they were just\n"
	.string "foolin' around somewhere.$"

SE_J_AzaleaTown_KurtsHouse_hns_AzaleaTown_KurtsHouse_EventScript_Girl::
	msgbox KurtsHouse_Text_GranddaughterSlowpokeGone, MSGBOX_NPC
	end

KurtsHouse_Text_KurtAskYouHaveAnApricorn::
	.string "KURT: You have BERRIES for me?\p"
	.string "Fine! I'll turn them into POKé BALLS.$"

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
