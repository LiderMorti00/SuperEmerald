ValleyWindworks_sinnoh_MapScripts::
	.byte 0

ValleyWindworks_EventScript_Looker::
	lock
	faceplayer
	msgbox ValleyWindworks_Text_Looker, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_WINDWORKS_LOOKER
	setflag FLAG_HIDE_WINDWORKS_LOOKER
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

ValleyWindworks_Text_Looker::
	.string "LOOKER: Ah, yes. It is you, yes.\p"
	.string "I have heard that the TEAM GALACTIC\n"
	.string "appeared at this power plant.\p"
	.string "I have, therefore, come running. So,\n"
	.string "the TEAM GALACTIC. Where are they?\p"
	.string "…\p"
	.string "You have run them off, you say? You\n"
	.string "are a TRAINER, but…?\p"
	.string "Very well! I shall go investigate\n"
	.string "inside!\p"
	.string "LOOKER: Magnificent! Yes, it is! What\n"
	.string "you have said, it is all true!\p"
	.string "Superb! Though you are young, you are\n"
	.string "a TRAINER through and through!\p"
	.string "Very well! I shall pursue the culprits!\p"
	.string "I have received tips that the Team\n"
	.string "GALACTIC hideout is in ETERNA CITY.\p"
	.string "To there, I must be off!$"

ValleyWindworks_EventScript_SNDRIFLOON::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DRIFLOON, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_DRIFLOON, 45
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, ValleyWindworks_EventScript_SNDRIFLOON_Ran
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, ValleyWindworks_EventScript_SNDRIFLOON_Ran
	setflag FLAG_SN_DONE_DRIFLOON
	setflag FLAG_SN_HIDE_DRIFLOON
	goto Common_EventScript_RemoveStaticPokemon
	end

ValleyWindworks_EventScript_SNDRIFLOON_Ran::
	setvar VAR_0x8004, SPECIES_DRIFLOON
	goto Common_EventScript_LegendaryFlewAway
	end

ValleyWindworks_EventScript_SNHoneyTree::
	lock
	goto_if_ne VAR_SN_HONEY_TREE, 17, ValleyWindworks_EventScript_SNHoneyTree_Fresh
	special SinnohHoneyReady
	goto_if_eq VAR_RESULT, TRUE, ValleyWindworks_EventScript_SNHoneyTree_Battle
	msgbox SN_HoneyTree_Text_Wait, MSGBOX_DEFAULT
	release
	end

ValleyWindworks_EventScript_SNHoneyTree_Battle::
	setvar VAR_SN_HONEY_TREE, 0
	setwildbattle SPECIES_WURMPLE, 5
	special SinnohHoneyTreeMon
	msgbox SN_HoneyTree_Text_Mon, MSGBOX_DEFAULT
	closemessage
	dowildbattle
	release
	end

ValleyWindworks_EventScript_SNHoneyTree_End::
	release
	end

ValleyWindworks_EventScript_SNHoneyTree_Fresh::
	msgbox SN_HoneyTree_Text_Scent, MSGBOX_DEFAULT
	checkitem ITEM_HONEY
	goto_if_eq VAR_RESULT, FALSE, ValleyWindworks_EventScript_SNHoneyTree_End
	msgbox SN_HoneyTree_Text_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ValleyWindworks_EventScript_SNHoneyTree_End
	removeitem ITEM_HONEY
	setvar VAR_SN_HONEY_TREE, 17
	special SinnohHoneySlather
	msgbox SN_HoneyTree_Text_Done, MSGBOX_DEFAULT
	goto ValleyWindworks_EventScript_SNHoneyTree_End

ValleyWindworks_EventScript_Sign1::
	msgbox ValleyWindworks_Text_Sign1, MSGBOX_SIGN
	end

ValleyWindworks_Text_Sign1::
	.string "VALLEY WINDWORKS$"
