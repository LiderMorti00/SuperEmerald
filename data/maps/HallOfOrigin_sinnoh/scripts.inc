HallOfOrigin_sinnoh_MapScripts::
	.byte 0


HallOfOrigin_EventScript_SNARCEUS::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ARCEUS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_ARCEUS, 80
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, HallOfOrigin_EventScript_SNARCEUS_Ran
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, HallOfOrigin_EventScript_SNARCEUS_Ran
	setflag FLAG_SN_DONE_ARCEUS
	setflag FLAG_SN_HIDE_ARCEUS
	goto Common_EventScript_RemoveStaticPokemon
	end

HallOfOrigin_EventScript_SNARCEUS_Ran::
	setvar VAR_0x8004, SPECIES_ARCEUS
	goto Common_EventScript_LegendaryFlewAway
	end
