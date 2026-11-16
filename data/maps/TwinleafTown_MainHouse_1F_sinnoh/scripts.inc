TwinleafTown_MainHouse_1F_sinnoh_MapScripts::
	.byte 0


TwinleafTown_MainHouse_1F_Text_SNMomPost::
	.string "Mom: {PLAYER}!\p"
	.string "{RIVAL} came looking for you a\n"
	.string "little while ago.\p"
	.string "I don’t know what it was about, but he\n"
	.string "was shouting about you needing\p"
	.string "to get on a ship at Snowpoint City.\p"
	.string "You know how impatient he is. He was\n"
	.string "gone before I could ask.$"

SE_S_TwinleafTown_MainHouse_1F_TwinleafTown_MainHouse_1F_EventScript_Mom::
	msgbox TwinleafTown_MainHouse_1F_Text_SNMomPost, MSGBOX_NPC
	end

TwinleafTown_MainHouse_1F_EventScript_BarrysMom::
	msgbox TwinleafTown_MainHouse_1F_Text_BarrysMom2, MSGBOX_NPC
	end

TwinleafTown_MainHouse_1F_Text_BarrysMom2::
	.string "{PLAYER}’s mom: Let me think...\p"
	.string "Knowing my boy, he would probably head\n"
	.string "straight to Jubilife City...\p"
	.string "OK, please take that to my {PLAYER}.\p"
	.string "Mom: Bye-bye, {PLAYER}! Enjoy your\n"
	.string "adventure!$"
