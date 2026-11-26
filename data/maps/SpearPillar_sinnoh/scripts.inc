SpearPillar_sinnoh_MapScripts::
	.byte 0

SpearPillar_EventScript_SNDIALGA::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DIALGA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_DIALGA, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SpearPillar_EventScript_SNDIALGA_Ran
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SpearPillar_EventScript_SNDIALGA_Ran
	setflag FLAG_SN_DONE_DIALGA
	setflag FLAG_SN_HIDE_DIALGA
	goto Common_EventScript_RemoveStaticPokemon
	end

SpearPillar_EventScript_SNDIALGA_Ran::
	setvar VAR_0x8004, SPECIES_DIALGA
	goto Common_EventScript_LegendaryFlewAway
	end

SpearPillar_EventScript_SNPALKIA::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PALKIA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_PALKIA, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SpearPillar_EventScript_SNPALKIA_Ran
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SpearPillar_EventScript_SNPALKIA_Ran
	setflag FLAG_SN_DONE_PALKIA
	setflag FLAG_SN_HIDE_PALKIA
	goto Common_EventScript_RemoveStaticPokemon
	end

SpearPillar_EventScript_SNPALKIA_Ran::
	setvar VAR_0x8004, SPECIES_PALKIA
	goto Common_EventScript_LegendaryFlewAway
	end

