ValleyWindoworks_Indoor_sinnoh_MapScripts::
	.byte 0


ValleyWindoworks_Indoor_Text_MarsIntro::
	.string "Mars: I’m one of Team Galactic’s three\n"
	.string "Commanders.\p"
	.string "...No, wait. That’s one of four\n"
	.string "Commanders.\p"
	.string "My name is Mars!\p"
	.string "We’ve been trying to create a new world\n"
	.string "that’s better than this one...\p"
	.string "But people have shown little\n"
	.string "understanding about what we do.\p"
	.string "You don’t understand either, do you?\n"
	.string "It’s a little saddening...\p"
	.string "So, let’s have a battle to decide what\n"
	.string "we should do next.\p"
	.string "If I win, you leave.\p"
	.string "If you win, we, Team Galactic, will\n"
	.string "leave!$"

SE_S_ValleyWindoworks_Indoor_ValleyWindoworks_Indoor_EventScript_Mars::
	msgbox ValleyWindoworks_Indoor_Text_MarsIntro, MSGBOX_NPC
	end

ValleyWindoworks_Indoor_Text_WorkerHelp::
	.string "Please... stop them!$"

SE_S_ValleyWindoworks_Indoor_ValleyWindoworks_Indoor_EventScript_Worker::
	msgbox ValleyWindoworks_Indoor_Text_WorkerHelp, MSGBOX_NPC
	end

ValleyWindoworks_Indoor_EventScript_Grunt1::
	trainerbattle_single TRAINER_GEORGE_SINNOH, ValleyWindoworks_Indoor_Text_G1Intro, ValleyWindoworks_Indoor_Text_G1Defeat
	msgbox ValleyWindoworks_Indoor_Text_G1Post, MSGBOX_AUTOCLOSE
	end

ValleyWindoworks_Indoor_Text_G1Post::
	.string "TEAM GALACTIC needs electricity for\n"
	.string "doing something big!$"

ValleyWindoworks_Indoor_Text_G1Defeat::
	.string "What...?! Some brat messed up my job...$"

ValleyWindoworks_Indoor_Text_G1Intro::
	.string "Oi! This is no fun and games! This is\n"
	.string "proper work, I tell you!$"

ValleyWindoworks_Indoor_EventScript_Grunt2::
	trainerbattle_single TRAINER_BERKE_SINNOH, ValleyWindoworks_Indoor_Text_G2Intro, ValleyWindoworks_Indoor_Text_G2Defeat
	msgbox ValleyWindoworks_Indoor_Text_G2Post, MSGBOX_AUTOCLOSE
	end

ValleyWindoworks_Indoor_Text_G2Post::
	.string "You don't have an inkling of what TEAM\n"
	.string "GALACTIC is trying to achieve!\p"
	.string "Of course, they don't tell a grunt like\n"
	.string "me anything, either... But still!$"

ValleyWindoworks_Indoor_Text_G2Defeat::
	.string "I really don't like kids who also\n"
	.string "happen to be tough Trainers...$"

ValleyWindoworks_Indoor_Text_G2Intro::
	.string "Collecting electricity from the\n"
	.string "VALLEY WINDWORKS... That's our\l"
	.string "mission.$"

ValleyWindoworks_Indoor_EventScript_SNGirl::
	lock
	faceplayer
	msgbox ValleyWindoworks_Indoor_Text_SNGirl2, MSGBOX_DEFAULT
	release
	end

ValleyWindoworks_Indoor_Text_SNGirl2::
	.string "Little girl: Thank you, Trainer! You\n"
	.string "made those bad people go away!\p"
	.string "I think the balloon POKéMON will come\n"
	.string "visiting again!$"
