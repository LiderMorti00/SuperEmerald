LakeAcuity_Cavern_sinnoh_MapScripts::
	.byte 0


LakeAcuity_Cavern_EventScript_SNUXIE::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_UXIE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_UXIE, 65
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, LakeAcuity_Cavern_EventScript_SNUXIE_Ran
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, LakeAcuity_Cavern_EventScript_SNUXIE_Ran
	setflag FLAG_SN_DONE_UXIE
	setflag FLAG_SN_HIDE_UXIE
	goto Common_EventScript_RemoveStaticPokemon
	end

LakeAcuity_Cavern_EventScript_SNUXIE_Ran::
	setvar VAR_0x8004, SPECIES_UXIE
	goto Common_EventScript_LegendaryFlewAway
	end
