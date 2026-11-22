SSAqua_PlayersRoom_hns_MapScripts::
	.byte 0


SSAquaRooms_Text_TakeRestOnBed::
	.string "There's a bed…\n"
	.string "Let's take a rest.$"

SE_J_SSAqua_PlayersRoom_hns_SSAquaRooms_EventScript_Bed::
	lockall
	msgbox SSAquaRooms_Text_TakeRestOnBed, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	call_if_eq VAR_SE_CRUISE_STATE, 2, SE_EventScript_CruiseArriveAfterBed
	releaseall
	end
