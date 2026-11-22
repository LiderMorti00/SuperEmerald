MtCoronet_4F_Room1_sinnoh_MapScripts::
	.byte 0


MtCoronet_4F_Room1_EventScript_Grunt::
	trainerbattle_single TRAINER_VALERIE_3_SINNOH, MtCoronet_4F_Room1_Text_GruntIntro, MtCoronet_4F_Room1_Text_GruntDefeat
	msgbox MtCoronet_4F_Room1_Text_GruntPost, MSGBOX_AUTOCLOSE
	end

MtCoronet_4F_Room1_Text_GruntPost::
	.string "It doesn't matter if you're an adult or\n"
	.string "a kid if you have POKéMON…\p"
	.string "POKéMON are the equalizers. I should\n"
	.string "have realized sooner…$"

MtCoronet_4F_Room1_Text_GruntDefeat::
	.string "Not standing up to the mighty is\n"
	.string "foolish, you say…$"

MtCoronet_4F_Room1_Text_GruntIntro::
	.string "I used to think this uniform made\n"
	.string "me strong. Care to test that?$"

MtCoronet_4F_Room1_EventScript_Grunt2::
	trainerbattle_single TRAINER_VALERIE_4_SINNOH, MtCoronet_4F_Room1_Text_Grunt2Intro, MtCoronet_4F_Room1_Text_Grunt2Defeat
	msgbox MtCoronet_4F_Room1_Text_Grunt2Post, MSGBOX_AUTOCLOSE
	end

MtCoronet_4F_Room1_Text_Grunt2Post::
	.string "I beat my old time on the climb.\n"
	.string "The battle needs work, though.$"

MtCoronet_4F_Room1_Text_Grunt2Defeat::
	.string "Gyah!$"

MtCoronet_4F_Room1_Text_Grunt2Intro::
	.string "I've been timing my climb.\n"
	.string "One battle before I head back down?$"
