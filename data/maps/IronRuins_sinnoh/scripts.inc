IronRuins_sinnoh_MapScripts::
	.byte 0


IronRuins_EventScript_SNREGISTEEL::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_REGIELEKI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_REGIELEKI, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, IronRuins_EventScript_SNREGISTEEL_Ran
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, IronRuins_EventScript_SNREGISTEEL_Ran
	setflag FLAG_SN_DONE_REGISTEEL
	setflag FLAG_SN_HIDE_REGISTEEL
	goto Common_EventScript_RemoveStaticPokemon

IronRuins_EventScript_SNREGISTEEL_Ran::
	setvar VAR_0x8004, SPECIES_REGIELEKI
	goto Common_EventScript_LegendaryFlewAway

IronRuins_EventScript_PtSign1::
	msgbox IronRuins_Text_PtSign1, MSGBOX_SIGN
	end

IronRuins_Text_PtSign1::
	.string "The POKéMON statue has stopped\n"
	.string "emanating power.$"

IronRuins_EventScript_PtSign2::
	msgbox IronRuins_Text_PtSign2, MSGBOX_SIGN
	end

IronRuins_Text_PtSign2::
	.string "The POKéMON statue has stopped\n"
	.string "emanating power.$"

IronRuins_EventScript_PtSign3::
	msgbox IronRuins_Text_PtSign3, MSGBOX_SIGN
	end

IronRuins_Text_PtSign3::
	.string "The POKéMON statue has stopped\n"
	.string "emanating power.$"
