ValleyWindworks_sinnoh_MapScripts::
	.byte 0


ValleyWindworks_EventScript_DoorGrunt::
	trainerbattle_single TRAINER_CHARLIE_SINNOH, ValleyWindworks_Text_DoorIntro, ValleyWindworks_Text_DoorDefeat, ValleyWindworks_EventScript_DoorGruntFlees
	msgbox ValleyWindworks_Text_DoorDefeat, MSGBOX_AUTOCLOSE
	end

ValleyWindworks_Text_DoorDefeat::
	.string "Tch! Lucky kid!$"

ValleyWindworks_EventScript_DoorGruntFlees::
	msgbox ValleyWindworks_Text_DoorFlee, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WINDWORKS_DOOR_GRUNT, Common_Movement_WalkUp
	waitmovement 0
	playse SE_DOOR
	removeobject LOCALID_WINDWORKS_DOOR_GRUNT
	setflag FLAG_HIDE_WINDWORKS_DOOR_GRUNT
	playse SE_PIN
	msgbox ValleyWindworks_Text_Locked, MSGBOX_DEFAULT
	release
	end

ValleyWindworks_Text_Locked::
	.string "It’s locked from inside!$"

ValleyWindworks_Text_DoorFlee::
	.string "Isn’t that just great. Getting owned\n"
	.string "by some kid.\p"
	.string "But you can’t do a thing if I lock\n"
	.string "myself in with my Works Key!\p"
	.string "That’s right, the other Works Key’s not\n"
	.string "here!\p"
	.string "My cohorts in the flower patch have\n"
	.string "the only other one!\p"
	.string "Hahaha! In that sense, I’m no longer\n"
	.string "the loser!$"

ValleyWindworks_Text_DoorIntro::
	.string "GRUNT: The WINDWORKS belongs to\n"
	.string "TEAM GALACTIC now! Get lost!$"

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
	.string "Looker: Ah, yes. It is you, yes.\p"
	.string "I have heard that the Team Galactic\n"
	.string "appeared at this power plant.\p"
	.string "I have, therefore, come running. So,\n"
	.string "the Team Galactic. Where are they?\p"
	.string "...\p"
	.string "You have run them off, you say? You\n"
	.string "are a Trainer, but...?\p"
	.string "Very well! I shall go investigate\n"
	.string "inside!\p"
	.string "Looker: Magnificent! Yes, it is! What\n"
	.string "you have said, it is all true!\p"
	.string "Superb! Though you are young, you are\n"
	.string "a Trainer through and through!\p"
	.string "Very well! I shall pursue the culprits!\p"
	.string "I have received tips that the Team\n"
	.string "Galactic hideout is in Eterna City.\p"
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
	waitstate
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

SE_S_ValleyWindworks_ValleyWindworks_EventScript_SNHoneyTree::
	msgbox SN_HoneyTree_Text_Wait, MSGBOX_NPC
	end

ValleyWindworks_EventScript_Sign1::
	msgbox ValleyWindworks_Text_Sign1, MSGBOX_SIGN
	end

ValleyWindworks_Text_Sign1::
	.string "VALLEY WINDWORKS$"
