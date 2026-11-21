Route201_sinnoh_MapScripts::
	.byte 0


Route201_EventScript_PtNpc1::
	msgbox Route201_Text_PtNpc1, MSGBOX_NPC
	end

Route201_Text_PtNpc1::
	.string "Wild POKéMON lurk in tall grass. They\n"
	.string "can come bursting out at any time.\p"
	.string "So, if you're wanting to battle wild\n"
	.string "POKéMON, just walk in tall grass.\p"
	.string "If you want to avoid wild POKéMON,\n"
	.string "then stay out of the tall grass.$"

Route201_EventScript_PtNpc2::
	msgbox Route201_Text_PtNpc2, MSGBOX_NPC
	end

Route201_Text_PtNpc2::
	.string "That ledge is one way. Jump down for a\n"
	.string "shortcut to TWINLEAF TOWN!$"

Route201_EventScript_PtNpc3::
	msgbox Route201_Text_PtNpc3, MSGBOX_NPC
	end

Route201_Text_PtNpc3::
	.string "If your POKéMON's health--that's its\n"
	.string "HP--is getting low, you should go home\l"
	.string "and get some rest.$"

Route201_Text_PtTooSlow::
	.string "Too slow!$"

SE_S_Route201_Route201_EventScript_Barry::
	msgbox Route201_Text_PtTooSlow, MSGBOX_NPC
	end

Route201_EventScript_Clerk::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_ROUTE201_POTION, Route201_EventScript_ClerkAfter
	msgbox Route201_Text_PtPotion, MSGBOX_DEFAULT
	giveitem ITEM_POTION
	setflag FLAG_RECEIVED_ROUTE201_POTION
	release
	end

Route201_Text_PtPotion::
	.string "Hi! I work at a POKéMON Mart.\p"
	.string "Did you know that a POKéMON's health is\n"
	.string "measured by Hit Points (HP)?\p"
	.string "If a POKéMON runs out of HP, it faints\n"
	.string "and can't battle anymore.\p"
	.string "If a POKéMON's HP gets low, you should\n"
	.string "heal it with a POTION.\p"
	.string "Here, let me give you a POTION as a free\n"
	.string "sample. First one's free!\p"
	.string "It will automatically go in the Medicine\n"
	.string "Pocket of your Bag.$"

Route201_EventScript_ClerkAfter::
	msgbox Route201_Text_PtFindMarts, MSGBOX_DEFAULT
	release
	end

Route201_Text_PtFindMarts::
	.string "You can find a POKéMON Mart in cities\n"
	.string "and most major towns.$"

Route201_EventScript_Sign1::
	msgbox Route201_Text_Sign1, MSGBOX_SIGN
	end

Route201_Text_Sign1::
	.string "ROUTE 201\p"
	.string "West: LAKE VERITY South: TWINLEAF\n"
	.string "TOWN East: SANDGEM TOWN$"

Route201_EventScript_Sign2::
	msgbox Route201_Text_Sign2, MSGBOX_SIGN
	end

Route201_Text_Sign2::
	.string "TRAINER TIPS\p"
	.string "Press START to open the menu. You\n"
	.string "can check your POKéMON and your\l"
	.string "BAG there.$"

Route201_EventScript_Sign3::
	msgbox Route201_Text_Sign3, MSGBOX_SIGN
	end

Route201_Text_Sign3::
	.string "Beware of tall grass! Wild POKéMON\n"
	.string "may jump out at any time.$"
