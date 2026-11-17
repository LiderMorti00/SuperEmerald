StarkMountain_Room1_sinnoh_MapScripts::
	.byte 0


StarkMountain_Room1_EventScript_SNCommanders::
	setvar VAR_TEMP_E, 1
	goto_if_set FLAG_SN_HIDE_STARK_R1, StarkMountain_Room1_EventScript_SNCommanders_End
	lockall
	applymovement LOCALID_SN_STARK_MARS, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_SN_STARK_MARS, StarkMountain_Room1_EventScript_SNCommanders_MarsStep
	waitmovement 0
	msgbox StarkMountain_Room1_EventScript_SNCommanders_T1, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_SOPHIE_SINNOH, StarkMountain_Room1_EventScript_SNCommanders_MarsDefeat
	msgbox StarkMountain_Room1_EventScript_SNCommanders_T2, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SN_STARK_MARS, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_SN_STARK_JUPITER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox StarkMountain_Room1_EventScript_SNCommanders_T3, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SN_STARK_JUPITER, Common_Movement_FaceDown
	waitmovement 0
	trainerbattle_no_intro TRAINER_COBY_SINNOH, StarkMountain_Room1_EventScript_SNCommanders_JupDefeat
	msgbox StarkMountain_Room1_EventScript_SNCommanders_T4, MSGBOX_DEFAULT
	closemessage
	delay 15
	msgbox StarkMountain_Room1_EventScript_SNCommanders_T5, MSGBOX_DEFAULT
	msgbox StarkMountain_Room1_EventScript_SNCommanders_T6, MSGBOX_DEFAULT
	closemessage
	msgbox StarkMountain_Room1_EventScript_SNCommanders_T7, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SN_STARK_MARS, StarkMountain_Room1_EventScript_SNCommanders_MarsLeave
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_SN_STARK_MARS
	waitse
	msgbox StarkMountain_Room1_EventScript_SNCommanders_T8, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SN_STARK_JUPITER, StarkMountain_Room1_EventScript_SNCommanders_JupLeave
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_SN_STARK_JUPITER
	waitse
	applymovement LOCALID_SN_STARK_CHARON, Common_Movement_FaceDown
	waitmovement 0
	msgbox StarkMountain_Room1_EventScript_SNCommanders_T9, MSGBOX_DEFAULT
	msgbox StarkMountain_Room1_EventScript_SNCommanders_T10, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SN_STARK_R1_GRUNT1, StarkMountain_Room1_EventScript_SNCommanders_Up
	applymovement LOCALID_SN_STARK_R1_GRUNT2, StarkMountain_Room1_EventScript_SNCommanders_Up
	applymovement LOCALID_SN_STARK_CHARON, StarkMountain_Room1_EventScript_SNCommanders_Up
	waitmovement 0
	removeobject LOCALID_SN_STARK_CHARON
	removeobject LOCALID_SN_STARK_R1_GRUNT1
	removeobject LOCALID_SN_STARK_R1_GRUNT2
	setflag FLAG_SN_HIDE_STARK_R1
	setflag FLAG_SN_STARK_R1_DONE
	releaseall

StarkMountain_Room1_EventScript_SNCommanders_Up::
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

StarkMountain_Room1_EventScript_SNCommanders_T10::
	.string "...But that’s fine. The young can live\n"
	.string "with their dreams.\p"
	.string "I prefer to remain firmly in reality.\n"
	.string "And for that, money is paramount.\p"
	.string "You there, child. I’m not dealing with\n"
	.string "you.\p"
	.string "After all, the other GALACTIC members\n"
	.string "who did all suffered consequences.\p"
	.string "We’ll be off to collect the Magma\n"
	.string "Stone. It’s all for the money!$"

StarkMountain_Room1_EventScript_SNCommanders_T9::
	.string "CHARON: Sigh... So impressionable and\n"
	.string "impetuous.\p"
	.string "What do they see in CYRUS? Immature,\n"
	.string "overthinking buffoon.\p"
	.string "He goes through the trouble of\n"
	.string "assembling TEAM GALACTIC for what?\p"
	.string "Ultimately, he destroys his own\n"
	.string "creation for his ludicrous vision.\p"
	.string "It’s no thanks to him that I have to\n"
	.string "struggle with the pieces.$"

StarkMountain_Room1_EventScript_SNCommanders_JupLeave::
	walk_fast_right
	walk_fast_down
	walk_fast_down
	step_end

StarkMountain_Room1_EventScript_SNCommanders_T8::
	.string "JUPITER: ...Says you. An “ordinary girl”\n"
	.string "you’re not.\p"
	.string "What should I do now? Is leaving on a\n"
	.string "journey the right idea?$"

StarkMountain_Room1_EventScript_SNCommanders_MarsLeave::
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	step_end

StarkMountain_Room1_EventScript_SNCommanders_T7::
	.string "MARS: There you have it. We’re going\n"
	.string "back to being ordinary girls.\p"
	.string "You can mop up whichever way you want.$"

StarkMountain_Room1_EventScript_SNCommanders_T6::
	.string "JUPITER: Following MARS’s lead at\n"
	.string "anything irks me, but...\p"
	.string "I’m quitting to do my own thing, too.\p"
	.string "TEAM GALACTIC’s just no fun without\n"
	.string "Master CYRUS around.\p"
	.string "So, old-timer, go ahead. Do what you\n"
	.string "want with TEAM GALACTIC.$"

StarkMountain_Room1_EventScript_SNCommanders_T5::
	.string "MARS: OK! That’s it for me! I’m going to\n"
	.string "look for Master CYRUS.\p"
	.string "The DISTORTION WORLD, was it called? I\n"
	.string "should go there, right?\p"
	.string "I’m quits with TEAM GALACTIC. JUPITER,\n"
	.string "you can deal with it!$"

StarkMountain_Room1_EventScript_SNCommanders_T4::
	.string "JUPITER: ...How dare you!$"

StarkMountain_Room1_EventScript_SNCommanders_JupDefeat::
	.string "JUPITER: ...Impossible.$"

StarkMountain_Room1_EventScript_SNCommanders_T3::
	.string "JUPITER: ...MARS. You really are weak.\n"
	.string "Pitifully so.\p"
	.string "You make me embarrassed to be a\n"
	.string "COMMANDER like you.\p"
	.string "Fine. I’ll go up next.\p"
	.string "I want to know what became of Master\n"
	.string "CYRUS, too.$"

StarkMountain_Room1_EventScript_SNCommanders_T2::
	.string "MARS: My POKéMON let me down again!\p"
	.string "How am I supposed to get information\n"
	.string "about our missing Master CYRUS?$"

StarkMountain_Room1_EventScript_SNCommanders_MarsDefeat::
	.string "MARS: No! Not again!$"

StarkMountain_Room1_EventScript_SNCommanders_T1::
	.string "MARS: Hey! You! Tell us where Master\n"
	.string "CYRUS went.\p"
	.string "Where were you after you disappeared\n"
	.string "at the SPEAR PILLAR?\p"
	.string "Huh? The DISTORTION WORLD?! Where\n"
	.string "GIRATINA was?\p"
	.string "You’re not making any sense! Don’t play\n"
	.string "that card with me!\p"
	.string "Fine! You don’t want to talk? I’ll bash\n"
	.string "you and make you talk!$"

StarkMountain_Room1_EventScript_SNCommanders_MarsStep::
	walk_down
	step_end

StarkMountain_Room1_EventScript_SNCommanders_End::
	end
