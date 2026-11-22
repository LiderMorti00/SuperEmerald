MtCoronet_3F_sinnoh_MapScripts::
	.byte 0


MtCoronet_3F_EventScript_Grunt::
	trainerbattle_single TRAINER_VALERIE_1_SINNOH, MtCoronet_3F_Text_GruntIntro, MtCoronet_3F_Text_GruntDefeat
	msgbox MtCoronet_3F_Text_GruntPost, MSGBOX_AUTOCLOSE
	end

MtCoronet_3F_Text_GruntPost::
	.string "I still turn around when I hear\n"
	.string "boots on those stairs.$"

MtCoronet_3F_Text_GruntDefeat::
	.string "I don't accept this! I will not accept\n"
	.string "this!$"

MtCoronet_3F_Text_GruntIntro::
	.string "I used to guard these stairs.\n"
	.string "Now I just come up here to train.$"

MtCoronet_3F_EventScript_Grunt2::
	trainerbattle_single TRAINER_VALERIE_2_SINNOH, MtCoronet_3F_Text_Grunt2Intro, MtCoronet_3F_Text_Grunt2Defeat
	msgbox MtCoronet_3F_Text_Grunt2Post, MSGBOX_AUTOCLOSE
	end

MtCoronet_3F_Text_Grunt2Post::
	.string "We used to march up here in pairs.\n"
	.string "It's a quieter climb these days.$"

MtCoronet_3F_Text_Grunt2Defeat::
	.string "When's it gonna be my turn…$"

MtCoronet_3F_Text_Grunt2Intro::
	.string "My old uniform still fits.\n"
	.string "Let's see if my team is rusty!$"
