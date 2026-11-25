LakeValor_Cavern_sinnoh_MapScripts::
	.byte 0

LakeValor_Cavern_EventScript_SNAZELF::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZELF, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_AZELF, 65
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, LakeValor_Cavern_EventScript_SNAZELF_Ran
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, LakeValor_Cavern_EventScript_SNAZELF_Ran
	setflag FLAG_SN_DONE_AZELF
	setflag FLAG_SN_HIDE_AZELF
	goto Common_EventScript_RemoveStaticPokemon
	end

LakeValor_Cavern_EventScript_SNAZELF_Ran::
	setvar VAR_0x8004, SPECIES_AZELF
	goto Common_EventScript_LegendaryFlewAway
	end
