IronIsland_B1F_Left_sinnoh_MapScripts::
	.byte 0


IronIsland_B1F_Left_EventScript_Lawrence::
	trainerbattle_single TRAINER_ROSE_3_SINNOH, IronIsland_B1F_Left_Text_LawrenceIntro, IronIsland_B1F_Left_Text_LawrenceDefeat
	msgbox IronIsland_B1F_Left_Text_LawrencePost, MSGBOX_AUTOCLOSE
	end

IronIsland_B1F_Left_Text_LawrencePost::
	.string "When I'm with my POKéMON, I can camp\n"
	.string "just about anywhere I want!$"

IronIsland_B1F_Left_Text_LawrenceDefeat::
	.string "I should've just stuck to camping out\n"
	.string "here…$"

IronIsland_B1F_Left_Text_LawrenceIntro::
	.string "Yeah, I like to camp! So what? Let's\n"
	.string "battle!$"
