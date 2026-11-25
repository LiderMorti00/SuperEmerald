PalPark_sinnoh_MapScripts::
	.byte 0

@ Super Emerald: wild POKéMON depend on the area (src/wild_encounter.c, SE_GetPalParkArea):
@ HIGHLANDS (north plateau), FOREST (west and middle groves), FIELD (east and south), LAKE.

PalPark_EventScript_Ranger::
	msgbox PalPark_Text_Ranger, MSGBOX_NPC
	end

PalPark_EventScript_ArticunoGalar::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ARTICUNO_GALAR, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_ARTICUNO_GALAR
	setwildbattle SPECIES_ARTICUNO_GALAR, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, SE_EventScript_LegendFled
	setflag FLAG_SE_LEG_ARTICUNO_GALAR
	goto Common_EventScript_RemoveStaticPokemon
	end

PalPark_EventScript_ZapdosGalar::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZAPDOS_GALAR, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_ZAPDOS_GALAR
	setwildbattle SPECIES_ZAPDOS_GALAR, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, SE_EventScript_LegendFled
	setflag FLAG_SE_LEG_ZAPDOS_GALAR
	goto Common_EventScript_RemoveStaticPokemon
	end

PalPark_EventScript_MoltresGalar::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MOLTRES_GALAR, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_MOLTRES_GALAR
	setwildbattle SPECIES_MOLTRES_GALAR, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, SE_EventScript_LegendFled
	setflag FLAG_SE_LEG_MOLTRES_GALAR
	goto Common_EventScript_RemoveStaticPokemon
	end

PalPark_Text_Ranger:
	.string "Welcome to the PAL PARK!\p"
	.string "Different POKéMON live in each area:\n"
	.string "the FIELD, the FOREST, the LAKE…\p"
	.string "and up the stairs, the HIGHLANDS.\p"
	.string "They say three strange birds from\n"
	.string "GALAR have made the park their home.\l"
	.string "One in the FIELD, one in the FOREST\l"
	.string "and one on the HIGHLANDS.$"
