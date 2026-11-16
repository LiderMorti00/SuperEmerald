StarkMountain_Room3_sinnoh_MapScripts::
	.byte 0


StarkMountain_Room3_EventScript_SNHEATRAN::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_HEATRAN, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_HEATRAN, 50
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, StarkMountain_Room3_EventScript_SNHEATRAN_Ran
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, StarkMountain_Room3_EventScript_SNHEATRAN_Ran
	setflag FLAG_SN_DONE_HEATRAN
	setflag FLAG_SN_BATTLED_STARK_MOUNTAIN_ROOM_3_HEATRAN
	setflag FLAG_SN_HIDE_HEATRAN
	goto Common_EventScript_RemoveStaticPokemon
	end

StarkMountain_Room3_EventScript_SNHEATRAN_Ran::
	setvar VAR_0x8004, SPECIES_HEATRAN
	goto Common_EventScript_LegendaryFlewAway
	end

StarkMountain_Room3_EventScript_SNCharon_T1::
	.string "Charon: ...Cyrus disappeared. Mars and\n"
	.string "Jupiter quit.\p"
	.string "Saturn said he would look after what\n"
	.string "remains of Team Galactic.\p"
	.string "But he won’t join me. So foolish of him!\p"
	.string "So very foolish of the rest of them!\n"
	.string "Throwing away Team Galactic!\p"
	.string "After all the effort we took as a team\n"
	.string "to make it grow...\p"
	.string "That power could have made us rich\n"
	.string "beyond imagination.\p"
	.string "But, enough of that. The Magma Stone\n"
	.string "will be mine.$"

SE_S_StarkMountain_Room3_StarkMountain_Room3_EventScript_SNCharon::
	msgbox StarkMountain_Room3_EventScript_SNCharon_T1, MSGBOX_NPC
	end
