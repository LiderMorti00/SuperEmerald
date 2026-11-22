MtCoronet_6F_sinnoh_MapScripts::
	.byte 0


MtCoronet_6F_EventScript_Grunt::
	trainerbattle_single TRAINER_GRUNT_SPACE_CENTER_2_SINNOH, MtCoronet_6F_Text_GruntIntro, MtCoronet_6F_Text_GruntDefeat
	msgbox MtCoronet_6F_Text_GruntPost, MSGBOX_AUTOCLOSE
	end

MtCoronet_6F_Text_GruntPost::
	.string "I used to dread reporting a loss.\n"
	.string "Feels good to just shake hands.$"

MtCoronet_6F_Text_GruntDefeat::
	.string "Wh-- How dare you! That's how you\n"
	.string "respond to my generosity?$"

MtCoronet_6F_Text_GruntIntro::
	.string "You've worked so hard to get here. You\n"
	.string "should be proud of yourself!\p"
	.string "And now, I'll send you packing home\n"
	.string "with only that happy thought!$"
