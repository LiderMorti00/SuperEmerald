IronIsland_House_sinnoh_MapScripts::
	.byte 0


IronIsland_House_EventScript_PtNpc1::
	lock
	faceplayer
	goto_if_set FLAG_SE_GOT_BYRON_APOLOGY, IronIsland_House_EventScript_ByronAfter
	msgbox IronIsland_House_Text_PtNpc1, MSGBOX_DEFAULT
	giveitem ITEM_METAL_COAT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SE_GOT_BYRON_APOLOGY
IronIsland_House_EventScript_ByronAfter::
	msgbox IronIsland_House_Text_ByronAfter, MSGBOX_DEFAULT
	release
	end

IronIsland_House_Text_ByronAfter::
	.string "BYRON: A METAL COAT hardens STEEL-type\n"
	.string "moves. Some POKéMON even evolve with it!\p"
	.string "Gwahahaha! Train hard, CHAMPION!$"

IronIsland_House_Text_PtNpc1::
	.string "BYRON: Hm? You're in training, then?\p"
	.string "You know, my son trains as hard as you\n"
	.string "do.\p"
	.string "But I still treat him as if he were a\n"
	.string "child.\p"
	.string "It's ridiculous, really. He is a proper\n"
	.string "GYM LEADER and all.\p"
	.string "It's always tricky between a father\n"
	.string "and son, it seems.\p"
	.string "Humph, I've wasted your time. Take this\n"
	.string "as my apology!$"
