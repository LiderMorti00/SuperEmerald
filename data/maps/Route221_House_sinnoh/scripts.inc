Route221_House_sinnoh_MapScripts::
	.byte 0


Route221_House_EventScript_PtNpc1::
	lock
	faceplayer
	goto_if_set FLAG_SE_GOT_ROUTE221_BELT, Route221_House_EventScript_BeltAfter
	msgbox Route221_House_Text_PtNpc1, MSGBOX_DEFAULT
	giveitem ITEM_EXPERT_BELT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SE_GOT_ROUTE221_BELT
Route221_House_EventScript_BeltAfter::
	msgbox Route221_House_Text_BeltAfter, MSGBOX_DEFAULT
	release
	end

Route221_House_Text_BeltAfter::
	.string "An EXPERT BELT powers up moves that\n"
	.string "are super effective. Use it well!$"

Route221_House_Text_PtNpc1::
	.string "Oh! What splendid POKéMON you have!\p"
	.string "I'll thank you for that visual treat\n"
	.string "with this item.$"

Route221_House_EventScript_PtSign1::
	msgbox Route221_House_Text_PtSign1, MSGBOX_SIGN
	end

Route221_House_Text_PtSign1::
	.string "Win Items from Me!\p"
	.string "Black Belt: Powers up Fighting-type\n"
	.string "moves.\p"
	.string "Expert Belt: Powers up moves if they\n"
	.string "are super effective.\p"
	.string "Focus Sash: The bearer avoids a\n"
	.string "one-hit KO if its HP is full.$"
