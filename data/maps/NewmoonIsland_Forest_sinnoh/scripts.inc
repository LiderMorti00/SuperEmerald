NewmoonIsland_Forest_sinnoh_MapScripts::
	.byte 0


NewmoonIsland_Forest_EventScript_SNDARKRAI::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DARKRAI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_DARKRAI, 50
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, NewmoonIsland_Forest_EventScript_SNDARKRAI_Ran
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, NewmoonIsland_Forest_EventScript_SNDARKRAI_Ran
	setflag FLAG_SN_DONE_DARKRAI
	setflag FLAG_SN_HIDE_DARKRAI
	goto Common_EventScript_RemoveStaticPokemon
	end

NewmoonIsland_Forest_EventScript_SNDARKRAI_Ran::
	setvar VAR_0x8004, SPECIES_DARKRAI
	goto Common_EventScript_LegendaryFlewAway
	end
