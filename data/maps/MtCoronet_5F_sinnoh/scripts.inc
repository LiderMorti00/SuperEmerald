MtCoronet_5F_sinnoh_MapScripts::
	.byte 0


MtCoronet_5F_EventScript_Grunt::
	trainerbattle_single TRAINER_VALERIE_5_SINNOH, MtCoronet_5F_Text_GruntIntro, MtCoronet_5F_Text_GruntDefeat
	msgbox MtCoronet_5F_Text_GruntPost, MSGBOX_AUTOCLOSE
	end

MtCoronet_5F_Text_GruntPost::
	.string "All my excitement's gone now…\p"
	.string "This whole MT. CORONET trip is too\n"
	.string "rough, long, and draining…$"

MtCoronet_5F_Text_GruntDefeat::
	.string "You're not supposed to work me over\n"
	.string "like that.$"

MtCoronet_5F_Text_GruntIntro::
	.string "I used to stand guard up here.\n"
	.string "Care to battle for old times' sake?$"

MtCoronet_5F_EventScript_Grunt2::
	trainerbattle_single TRAINER_CINDY_1_SINNOH, MtCoronet_5F_Text_Grunt2Intro, MtCoronet_5F_Text_Grunt2Defeat
	msgbox MtCoronet_5F_Text_Grunt2Post, MSGBOX_AUTOCLOSE
	end

MtCoronet_5F_Text_Grunt2Post::
	.string "When the orders stopped coming,\n"
	.string "my team still showed up for practice.$"

MtCoronet_5F_Text_Grunt2Defeat::
	.string "All you gave me was the taste of\n"
	.string "defeat…$"

MtCoronet_5F_Text_Grunt2Intro::
	.string "The others kept their uniforms.\n"
	.string "I kept training my team. Watch!$"
