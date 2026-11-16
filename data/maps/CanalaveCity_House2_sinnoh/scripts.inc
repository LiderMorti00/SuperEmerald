CanalaveCity_House2_sinnoh_MapScripts::
	.byte 0


CanalaveCity_House2_EventScript_SNMoveDeleter::
	lockall
	faceplayer
	msgbox LilycoveCity_MoveDeletersHouse_Text_ICanMakeMonForgetMove, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, LilycoveCity_MoveDeletersHouse_EventScript_ChooseMonAndMoveToForget
	case NO, LilycoveCity_MoveDeletersHouse_EventScript_ComeAgain
	releaseall
	end
