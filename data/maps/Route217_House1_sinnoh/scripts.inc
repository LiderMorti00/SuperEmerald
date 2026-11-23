Route217_House1_sinnoh_MapScripts::
	.byte 0


Route217_House1_EventScript_PtNpc1::
	lock
	faceplayer
	goto_if_set FLAG_SE_GOT_ROUTE217_SPELL_TAG, Route217_House1_EventScript_SpellTagAfter
	giveitem ITEM_SPELL_TAG
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SE_GOT_ROUTE217_SPELL_TAG
Route217_House1_EventScript_SpellTagAfter::
	msgbox Route217_House1_Text_PtNpc1, MSGBOX_DEFAULT
	release
	end

Route217_House1_Text_PtNpc1::
	.string "…The SPELL TAG… It intensifies\n"
	.string "Ghost-type moves…\p"
	.string "May it serve you well…$"
