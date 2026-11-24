GalacticHQ_1F_sinnoh_MapScripts::
	.byte 0

GalacticHQ_1F_EventScript_Grunt::
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_3_SINNOH, GalacticHQ_1F_Text_GruntIntro, GalacticHQ_1F_Text_GruntDefeat
	msgbox GalacticHQ_1F_Text_GruntPost, MSGBOX_AUTOCLOSE
	end

GalacticHQ_1F_Text_GruntPost::
	.string "In our HQ, we get around by taking warp\n"
	.string "panels.\p"
	.string "I'd like to see you figure out how they\n"
	.string "connect.$"

GalacticHQ_1F_Text_GruntDefeat::
	.string "A tough little TRAINER is what you are…$"

GalacticHQ_1F_Text_GruntIntro::
	.string "Who do you think you are? Desecrating\n"
	.string "the halls of our HQ?!$"

GalacticHQ_1F_EventScript_Fredrick::
	trainerbattle_single TRAINER_GABRIELLE_1_SINNOH, GalacticHQ_1F_Text_FredrickIntro, GalacticHQ_1F_Text_FredrickDefeat
	msgbox GalacticHQ_1F_Text_FredrickPost, MSGBOX_AUTOCLOSE
	end

GalacticHQ_1F_Text_FredrickPost::
	.string "Our boss is trying to create an\n"
	.string "entirely new world.\p"
	.string "A world only for us! For TEAM GALACTIC!$"

GalacticHQ_1F_Text_FredrickDefeat::
	.string "You and your POKéMON weren't part of\n"
	.string "my calculations…$"

GalacticHQ_1F_Text_FredrickIntro::
	.string "Hey, now! Our HQ is a state-of-the- art\n"
	.string "facility!\p"
	.string "A snot-nosed kid like you ought to\n"
	.string "keep your dirty hands to yourself!$"

GalacticHQ_1F_EventScript_PtNpc1::
	lock
	faceplayer
	goto_if_set FLAG_SN_GALACTIC_LEFT_LAKE_VALOR, GalacticHQ_1F_EventScript_PtNpc1_WeHaveNoPlansNow
	msgbox GalacticHQ_1F_Text_PtNpc1_0, MSGBOX_DEFAULT
	release
	end

GalacticHQ_1F_Text_PtNpc1_0::
	.string "Welcome. This is TEAM GALACTIC Headqu…\p"
	.string "I'm sorry, this is the GALACTIC\n"
	.string "VEILSTONE Building.\p"
	.string "Cosmic energy for the win!\p"
	.string "Wouldn't it be wonderful if we could\n"
	.string "harness that boundless energy?$"

GalacticHQ_1F_EventScript_PtNpc1_WeHaveNoPlansNow::
	msgbox GalacticHQ_1F_Text_PtNpc1_1, MSGBOX_DEFAULT
	release
	end

GalacticHQ_1F_Text_PtNpc1_1::
	.string "Welcome. This is TEAM GALACTIC Headqu…\p"
	.string "I'm sorry, this is the GALACTIC\n"
	.string "VEILSTONE Building.\p"
	.string "I'm not certain if it's a good thing or\n"
	.string "not, but we have no plans now.$"

GalacticHQ_1F_EventScript_PtNpc2::
	lock
	faceplayer
	goto_if_set FLAG_SN_GALACTIC_LEFT_LAKE_VALOR, GalacticHQ_1F_EventScript_PtNpc2_ThisIsWhereWeWork
	msgbox GalacticHQ_1F_Text_PtNpc2_0, MSGBOX_DEFAULT
	release
	end

GalacticHQ_1F_Text_PtNpc2_0::
	.string "TEAM GALACTIC conducts R&D around the\n"
	.string "clock here.\p"
	.string "We focus on the development of new\n"
	.string "energy resources.$"

GalacticHQ_1F_EventScript_PtNpc2_ThisIsWhereWeWork::
	msgbox GalacticHQ_1F_Text_PtNpc2_1, MSGBOX_DEFAULT
	release
	end

GalacticHQ_1F_Text_PtNpc2_1::
	.string "This is where we, TEAM GALACTIC, work.\n"
	.string "What are we supposed to do?\p"
	.string "I'm not sure how, but we're supposed to\n"
	.string "chase our dream.\p"
	.string "Our dream of making a wonderful new\n"
	.string "world!$"

GalacticHQ_1F_EventScript_PtNpc3::
	lock
	faceplayer
	goto_if_set FLAG_SN_GALACTIC_LEFT_LAKE_VALOR, GalacticHQ_1F_EventScript_PtNpc3_IWonderWhereBossWent
	msgbox GalacticHQ_1F_Text_PtNpc3_0, MSGBOX_DEFAULT
	release
	end

GalacticHQ_1F_Text_PtNpc3_0::
	.string "You're too young for us… You can join\n"
	.string "us when you're older.$"

GalacticHQ_1F_EventScript_PtNpc3_IWonderWhereBossWent::
	msgbox GalacticHQ_1F_Text_PtNpc3_1, MSGBOX_DEFAULT
	release
	end

GalacticHQ_1F_Text_PtNpc3_1::
	.string "I wonder where our boss went…$"

GalacticHQ_1F_EventScript_PtNpc4::
	lock
	faceplayer
	goto_if_set FLAG_SN_GALACTIC_LEFT_LAKE_VALOR, GalacticHQ_1F_EventScript_PtNpc4_NothingLeftNow
	msgbox GalacticHQ_1F_Text_PtNpc4_0, MSGBOX_DEFAULT
	release
	end

GalacticHQ_1F_Text_PtNpc4_0::
	.string "We, TEAM GALACTIC, will take everything\n"
	.string "that can be taken!\p"
	.string "We will eliminate everything that is\n"
	.string "not needed!\p"
	.string "That is TEAM GALACTIC's policy!$"

GalacticHQ_1F_EventScript_PtNpc4_NothingLeftNow::
	msgbox GalacticHQ_1F_Text_PtNpc4_1, MSGBOX_DEFAULT
	release
	end

GalacticHQ_1F_Text_PtNpc4_1::
	.string "We, TEAM GALACTIC, will take everything\n"
	.string "that can be taken!\p"
	.string "We will eliminate everything that is\n"
	.string "not needed!\p"
	.string "That is TEAM GALACTIC's policy!\p"
	.string "At least it used to be. There's nothing\n"
	.string "left now…$"

GalacticHQ_1F_EventScript_PtSign1::
	msgbox GalacticHQ_1F_Text_PtSign1, MSGBOX_SIGN
	end

GalacticHQ_1F_Text_PtSign1::
	.string "The TEAM GALACTIC credo! Everything\n"
	.string "belongs to TEAM GALACTIC!\p"
	.string "Look beyond the world--space will\n"
	.string "become TEAM GALACTIC's!$"
