SnowpointTemple_B5F_sinnoh_MapScripts::
	.byte 0


SnowpointTemple_B5F_EventScript_SNREGIGIGAS::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_REGIGIGAS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_REGIGIGAS, 1
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SnowpointTemple_B5F_EventScript_SNREGIGIGAS_Ran
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SnowpointTemple_B5F_EventScript_SNREGIGIGAS_Ran
	setflag FLAG_SN_DONE_REGIGIGAS
	setflag FLAG_SN_HIDE_REGIGIGAS
	goto Common_EventScript_RemoveStaticPokemon
	end

SnowpointTemple_B5F_EventScript_SNREGIGIGAS_Ran::
	setvar VAR_0x8004, SPECIES_REGIGIGAS
	goto Common_EventScript_LegendaryFlewAway
	end
