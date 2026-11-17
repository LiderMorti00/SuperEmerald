@ ---------------------------------------------------------------------------
@ Super Emerald: ship trips between regions are made aboard the ship.
@ The S.S. TIDAL links Hoenn with Johto and Sinnoh, the S.S. AQUA links
@ Olivine City and Vermilion City. Walk around (or rest in a cabin bed) until
@ the ship arrives, then talk to the sailor at the exit.
@ VAR_SE_CRUISE_DEST: 1 Olivine, 2 Slateport, 3 Vermilion, 4 Canalave
@ VAR_SE_CRUISE_STATE: 0 none, 1 boarding, 2 sailing, 3 arrived

SE_EventScript_BoardTidal::
	setvar VAR_SS_TIDAL_STATE, 0
	setvar VAR_SE_CRUISE_STATE, 1
	warp MAP_SS_TIDAL_CORRIDOR, 1, 10
	waitstate
	end

SE_EventScript_BoardAqua::
	setvar VAR_SE_CRUISE_STATE, 1
	warp MAP_SSAQUA_1F_HNS, 28, 3
	waitstate
	end

SE_EventScript_CruiseDepart::
	special SetSSTidalFlag
	setvar VAR_CRUISE_STEP_COUNT, SE_CRUISE_START_STEPS
	setvar VAR_SE_CRUISE_STATE, 2
	lockall
	playse SE_DING_DONG
	call SE_EventScript_CruiseBufferDest
	msgbox SE_Text_CruiseDepart, MSGBOX_DEFAULT
	releaseall
	end

SE_EventScript_CruiseArrive::
	special ResetSSTidalFlag
	setvar VAR_SE_CRUISE_STATE, 3
	lockall
	playse SE_DING_DONG
	call SE_EventScript_CruiseBufferDest
	msgbox SE_Text_CruiseArrived, MSGBOX_DEFAULT
	releaseall
	end

@ called from the cabin bed (it uses "call", so this must return)
SE_EventScript_CruiseArriveAfterBed::
	special ResetSSTidalFlag
	setvar VAR_SE_CRUISE_STATE, 3
	playse SE_DING_DONG
	call SE_EventScript_CruiseBufferDest
	msgbox SE_Text_CruiseArrived, MSGBOX_DEFAULT
	return

SE_EventScript_CruiseBufferDest::
	switch VAR_SE_CRUISE_DEST
	case 1, SE_EventScript_CruiseBufferOlivine
	case 2, SE_EventScript_CruiseBufferSlateport
	case 3, SE_EventScript_CruiseBufferVermilion
	case 4, SE_EventScript_CruiseBufferCanalave
	return
SE_EventScript_CruiseBufferOlivine::
	bufferstring STR_VAR_1, SE_Text_CruiseOlivine
	return
SE_EventScript_CruiseBufferSlateport::
	bufferstring STR_VAR_1, SE_Text_CruiseSlateport
	return
SE_EventScript_CruiseBufferVermilion::
	bufferstring STR_VAR_1, SE_Text_CruiseVermilion
	return
SE_EventScript_CruiseBufferCanalave::
	bufferstring STR_VAR_1, SE_Text_CruiseCanalave
	return

@ the sailor at the ship's exit
SE_EventScript_CruiseExitSailor::
	lock
	faceplayer
	goto_if_eq VAR_SE_CRUISE_STATE, 3, SE_EventScript_CruiseDisembark
	call SE_EventScript_CruiseBufferDest
	msgbox SE_Text_CruiseStillSailing, MSGBOX_DEFAULT
	release
	end

SE_EventScript_CruiseDisembark::
	msgbox SE_Text_CruiseDisembark, MSGBOX_DEFAULT
	closemessage
	setvar VAR_SE_CRUISE_STATE, 0
	playse SE_EXIT
	fadescreen FADE_TO_BLACK
	switch VAR_SE_CRUISE_DEST
	case 1, SE_EventScript_CruiseExitOlivine
	case 2, SE_EventScript_CruiseExitSlateport
	case 3, SE_EventScript_CruiseExitVermilion
	case 4, SE_EventScript_CruiseExitCanalave
	warp MAP_SLATEPORT_CITY_HARBOR, 8, 11
	waitstate
	release
	end

SE_EventScript_CruiseExitOlivine::
	warp MAP_OLIVINE_CITY_PORT_INSIDE_HNS, 8, 16
	waitstate
	release
	end

SE_EventScript_CruiseExitSlateport::
	warp MAP_SLATEPORT_CITY_HARBOR, 8, 11
	waitstate
	release
	end

SE_EventScript_CruiseExitVermilion::
	warp MAP_VERMILION_CITY, 23, 32
	waitstate
	release
	end

SE_EventScript_CruiseExitCanalave::
	warp MAP_CANALAVE_CITY_SINNOH, 22, 16
	waitstate
	release
	end

SSAqua_1F_OnFrame::
	map_script_2 VAR_SE_CRUISE_STATE, 1, SE_EventScript_CruiseDepart
	.2byte 0

SE_Text_CruiseOlivine:
	.string "OLIVINE CITY$"
SE_Text_CruiseSlateport:
	.string "SLATEPORT CITY$"
SE_Text_CruiseVermilion:
	.string "VERMILION CITY$"
SE_Text_CruiseCanalave:
	.string "CANALAVE CITY$"

SE_Text_CruiseDepart:
	.string "Welcome aboard! This ship is bound\n"
	.string "for {STR_VAR_1}.\p"
	.string "We will make an announcement when\n"
	.string "we arrive. Please enjoy the voyage!$"

SE_Text_CruiseArrived:
	.string "Ladies and gentlemen, we have\n"
	.string "arrived at {STR_VAR_1}!\p"
	.string "Please make your way to the exit.$"

SE_Text_CruiseStillSailing:
	.string "We're still on our way to\n"
	.string "{STR_VAR_1}.\p"
	.string "You can rest in your cabin until\n"
	.string "we arrive.$"

SE_Text_CruiseDisembark:
	.string "We've arrived! Watch your step\n"
	.string "on your way out.$"
