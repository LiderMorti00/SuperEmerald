Route208_House_sinnoh_MapScripts::
	.byte 0


Route208_House_EventScript_PtNpc2::
	msgbox Route208_House_Text_PtNpc2, MSGBOX_NPC
	end

Route208_House_Text_PtNpc2::
	.string "Did you know? Soft soil turns dark\n"
	.string "when it has plenty of water.\p"
	.string "That's how you know your Berries\n"
	.string "are growing happily!$"

Route208_House_EventScript_SNMulch::
	lock
	faceplayer
	msgbox Route208_House_Text_SNMulch, MSGBOX_DEFAULT
	pokemart Route208_House_Mart_SNMulch
	msgbox Route208_House_Text_SNMulchBye, MSGBOX_DEFAULT
	release
	end

	.align 2

Route208_House_Text_SNMulchBye::
	.string "Grow lots of Berries!$"

Route208_House_Mart_SNMulch::
	.2byte ITEM_GROWTH_MULCH
	.2byte ITEM_DAMP_MULCH
	.2byte ITEM_STABLE_MULCH
	.2byte ITEM_GOOEY_MULCH
	pokemartlistend

Route208_House_Text_SNMulch::
	.string "Um… Would you like some Mulch? If\n"
	.string "you're going to grow Berries, Mulch is a\l"
	.string "good fertilizer.$"

Route208_House_EventScript_BerryMaster::
	lock
	faceplayer
	dotimebasedevents
	goto_if_set FLAG_DAILY_BERRY_MASTER_RECEIVED_BERRY, Route123_BerryMastersHouse_EventScript_ReceivedBerryToday
	msgbox Route123_BerryMastersHouse_Text_YoureDeservingOfBerry, MSGBOX_DEFAULT
	giverandomberry BERRY_ID_POMEG, BERRY_ID_NOMEL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_DAILY_BERRY_MASTER_RECEIVED_BERRY
	msgbox Route123_BerryMastersHouse_Text_WhyBeStingyTakeAnother, MSGBOX_DEFAULT
	giverandomberry BERRY_ID_POMEG, BERRY_ID_NOMEL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox Route208_House_Text_VisitFloaromaFlowerShop, MSGBOX_DEFAULT
	release
	end

Route208_House_Text_VisitFloaromaFlowerShop::
	.string "Be sure to visit the flower shop in\n"
	.string "FLOAROMA TOWN.\p"
	.string "Let flowers fill the world!$"
