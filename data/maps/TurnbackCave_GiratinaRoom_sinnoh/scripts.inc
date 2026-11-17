TurnbackCave_GiratinaRoom_sinnoh_MapScripts::
	.byte 0


TurnbackCave_GiratinaRoom_EventScript_SNGIRATINA::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_GIRATINA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_GIRATINA, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, TurnbackCave_GiratinaRoom_EventScript_SNGIRATINA_Ran
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, TurnbackCave_GiratinaRoom_EventScript_SNGIRATINA_Ran
	setflag FLAG_SN_DONE_GIRATINA
	setflag FLAG_SN_HIDE_GIRATINA
	goto Common_EventScript_RemoveStaticPokemon
	end

TurnbackCave_GiratinaRoom_EventScript_SNGIRATINA_Ran::
	setvar VAR_0x8004, SPECIES_GIRATINA
	goto Common_EventScript_LegendaryFlewAway
	end

TurnbackCave_GiratinaRoom_EventScript_SNOrb_End::
	release
	end

TurnbackCave_GiratinaRoom_EventScript_SNOrb::
	lock
	finditem ITEM_GRISEOUS_ORB
	goto_if_eq VAR_RESULT, FALSE, TurnbackCave_GiratinaRoom_EventScript_SNOrb_End
	setflag FLAG_SN_GOT_GRISEOUS_ORB
	removeobject LOCALID_SN_GRISEOUS
	setflag FLAG_SN_HIDE_GRISEOUS
	goto TurnbackCave_GiratinaRoom_EventScript_SNOrb_End

TurnbackCave_GiratinaRoom_EventScript_PtSign1::
	msgbox TurnbackCave_GiratinaRoom_Text_PtSign1, MSGBOX_SIGN
	end

TurnbackCave_GiratinaRoom_Text_PtSign1::
	.string "This is...\p"
	.string "That where life sparkles... That where\n"
	.string "life has faded...\p"
	.string "A place where two worlds overlap...$"

TurnbackCave_GiratinaRoom_EventScript_PtSign2::
	msgbox TurnbackCave_GiratinaRoom_Text_PtSign2, MSGBOX_SIGN
	end

TurnbackCave_GiratinaRoom_Text_PtSign2::
	.string "This is...\p"
	.string "That where life sparkles... That where\n"
	.string "life has faded...\p"
	.string "A place where two worlds overlap...$"

TurnbackCave_GiratinaRoom_EventScript_PtSign3::
	msgbox TurnbackCave_GiratinaRoom_Text_PtSign3, MSGBOX_SIGN
	end

TurnbackCave_GiratinaRoom_Text_PtSign3::
	.string "This is...\p"
	.string "That where life sparkles... That where\n"
	.string "life has faded...\p"
	.string "A place where two worlds overlap...$"

TurnbackCave_GiratinaRoom_EventScript_PtSign4::
	msgbox TurnbackCave_GiratinaRoom_Text_PtSign4, MSGBOX_SIGN
	end

TurnbackCave_GiratinaRoom_Text_PtSign4::
	.string "It’s a portal leading to the Distortion\n"
	.string "World...\p"
	.string "Would you like to leap into the portal\n"
	.string "and go to the DISTORTION WORLD?$"
