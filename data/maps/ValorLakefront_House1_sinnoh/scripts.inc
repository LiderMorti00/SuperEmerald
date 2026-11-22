ValorLakefront_House1_sinnoh_MapScripts::
	.byte 0


ValorLakefront_House1_EventScript_PtNpc1::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_SN_GRAND_LAKE_VALOR_LAKEFRONT_EAST_HOUSE_WHITE_FLUTE, ValorLakefront_House1_EventScript_PtNpc1_BlowToAttractPokemon
	msgbox ValorLakefront_House1_Text_PtNpc1_0, MSGBOX_DEFAULT
	giveitem ITEM_WHITE_FLUTE, 1
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_SN_GRAND_LAKE_VALOR_LAKEFRONT_EAST_HOUSE_WHITE_FLUTE
	release
	end

ValorLakefront_House1_Text_PtNpc1_0::
	.string "A visitor from HOENN!\p"
	.string "I brought this flute back from a\n"
	.string "trip there. Would you like it?$"

ValorLakefront_House1_EventScript_PtNpc1_BlowToAttractPokemon::
	msgbox ValorLakefront_House1_Text_PtNpc1_1, MSGBOX_DEFAULT
	release
	end

ValorLakefront_House1_Text_PtNpc1_1::
	.string "Blow the WHITE FLUTE if you want to\n"
	.string "attract more wild POKéMON.\p"
	.string "It was made from volcanic ash\n"
	.string "collected in HOENN.$"
