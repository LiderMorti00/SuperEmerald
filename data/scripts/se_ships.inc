@ Super Emerald: every port sails to every other port the player has unlocked.
@ Ports (VAR_SE_CRUISE_DEST values): 1 Olivine, 2 Slateport, 3 Vermilion, 4 Canalave.
@ Olivine needs the JOHTO TICKET, Vermilion the JOHTO LEAGUE, Canalave the CANALAVE TICKET.
@ VAR_0x8008 = the port the player is at. Trips to or from Vermilion use the S.S. AQUA.

@ Shows the menu; VAR_RESULT = chosen port, or MULTI_B_PRESSED
SE_EventScript_ShipChooseDest::
	message SE_Text_ShipWhere
	waitmessage
	call_if_ne VAR_0x8008, 1, SE_EventScript_ShipPushOlivine
	call_if_ne VAR_0x8008, 2, SE_EventScript_ShipPushSlateport
	call_if_ne VAR_0x8008, 3, SE_EventScript_ShipPushVermilion
	call_if_ne VAR_0x8008, 4, SE_EventScript_ShipPushCanalave
	dynmultistack 18, 5, FALSE, 3, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	return

SE_EventScript_ShipPushOlivine::
	checkitem ITEM_JOHTO_TICKET
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_NopReturn
	dynmultipush SE_Text_ChoiceOlivine, 1
	return

SE_EventScript_ShipPushSlateport::
	dynmultipush SE_Text_ChoiceSlateport, 2
	return

SE_EventScript_ShipPushVermilion::
	goto_if_unset FLAG_SE_JOHTO_LEAGUE_CLEARED, Common_EventScript_NopReturn
	dynmultipush SE_Text_ChoiceVermilion, 3
	return

SE_EventScript_ShipPushCanalave::
	checkitem ITEM_CANALAVE_TICKET
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_NopReturn
	dynmultipush SE_Text_ChoiceCanalave, 4
	return

@ True when the menu was cancelled
SE_EventScript_ShipCheckCancel::
	goto_if_eq VAR_RESULT, 1, SE_EventScript_ShipSetDest
	goto_if_eq VAR_RESULT, 2, SE_EventScript_ShipSetDest
	goto_if_eq VAR_RESULT, 3, SE_EventScript_ShipSetDest
	goto_if_eq VAR_RESULT, 4, SE_EventScript_ShipSetDest
	setvar VAR_RESULT, TRUE
	return

SE_EventScript_ShipSetDest::
	copyvar VAR_SE_CRUISE_DEST, VAR_RESULT
	setvar VAR_0x8009, FALSE
	call_if_eq VAR_SE_CRUISE_DEST, 3, SE_EventScript_ShipUseAqua
	call_if_eq VAR_0x8008, 3, SE_EventScript_ShipUseAqua
	call_if_eq VAR_SE_CRUISE_DEST, 1, SE_EventScript_ShipFirstJohto
	call_if_eq VAR_SE_CRUISE_DEST, 4, SE_EventScript_ShipFirstSinnoh
	setvar VAR_RESULT, FALSE
	return

SE_EventScript_ShipUseAqua::
	setvar VAR_0x8009, TRUE
	return

SE_EventScript_ShipFirstJohto::
	goto_if_ne VAR_SE_JOHTO_ARRIVAL, 0, Common_EventScript_NopReturn
	setvar VAR_SE_JOHTO_ARRIVAL, 1
	return

SE_EventScript_ShipFirstSinnoh::
	goto_if_ne VAR_SE_SINNOH_ARRIVAL, 0, Common_EventScript_NopReturn
	setvar VAR_SE_SINNOH_ARRIVAL, 1
	return

@ Sailors at Olivine, Vermilion and Canalave
SE_EventScript_ShipSailor::
	call SE_EventScript_ShipChooseDest
	call SE_EventScript_ShipCheckCancel
	goto_if_eq VAR_RESULT, TRUE, SE_EventScript_ShipDeclined
	msgbox SFR_Text_VermilionSailorAllAboard, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_SE_CRUISE_DEST, 3, SE_EventScript_InitKantoPostgame
	playse SE_SHIP
	fadescreenspeed FADE_TO_BLACK, 12
	delay 60
SE_EventScript_ShipBoard::
	goto_if_eq VAR_0x8009, TRUE, SE_EventScript_BoardAqua
	goto SE_EventScript_BoardTidal
	end

SE_EventScript_ShipDeclined::
	msgbox SFR_Text_VermilionSailorComeBackAnytime, MSGBOX_DEFAULT
	release
	end

@ Slateport harbor: called from the Emerald ferry clerk, returns if the player says no
SE_EventScript_SlateportShips::
	checkitem ITEM_JOHTO_TICKET
	goto_if_eq VAR_RESULT, TRUE, SE_EventScript_SlateportShipsMenu
	checkitem ITEM_CANALAVE_TICKET
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_NopReturn
SE_EventScript_SlateportShipsMenu::
	setvar VAR_0x8008, 2
	call SE_EventScript_ShipChooseDest
	call SE_EventScript_ShipCheckCancel
	goto_if_eq VAR_RESULT, TRUE, Common_EventScript_NopReturn
	call_if_eq VAR_SE_CRUISE_DEST, 3, SE_EventScript_InitKantoPostgame
	call SlateportCity_Harbor_EventScript_BoardFerry
	goto SE_EventScript_ShipBoard
	end

SE_Text_ShipWhere:
	.string "Where would you like to sail?$"
