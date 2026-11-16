Gate_NationalPark_hns_MapScripts::
	.byte 0


Route35NationalParkGate_EventScript_Policeman::
	lock
	faceplayer
	msgbox Route35NationalParkGate_Text_WeHoldContests, MSGBOX_DEFAULT
	closemessage
	release
	end

Route35NationalParkGate_Text_WeHoldContests::
	.string "We hold Contests regularly in the\n"
	.string "PARK. You should give it a shot.$"

Route35NationalParkGate_Text_OfficerAskToParticipate::
	.string "Hello Trainer! The Bug-Catching\n"
	.string "Contest is on today.\p"
	.string "The rules are simple.\p"
	.string "Using one of your POKéMON, catch a\n"
	.string "bug POKéMON to be judged.\p"
	.string "Would you like to give it a try?$"

SE_J_Gate_NationalPark_hns_Gate_NationalPark_EventScript_BAttendant::
	msgbox Route35NationalParkGate_Text_OfficerAskToParticipate, MSGBOX_NPC
	end

SE_J_Gate_NationalPark_hns_Gate_NationalPark_EventScript_Attendant::
	msgbox Route35NationalParkGate_Text_OfficerAskToParticipate, MSGBOX_NPC
	end

Route35NationalParkGate_EventScript_Rocker::
	lock
	faceplayer
	msgbox Route35NationalParkGate_Text_Rocker, MSGBOX_DEFAULT
	closemessage
	release
	end

Route35NationalParkGate_Text_Rocker::
	.string "I love bird POKéMON! I found a\n"
	.string "DARK-type bird in the park\l"
	.string "last night!$"

Route35NationalParkGate_EventScript_BC1::
	lock
	faceplayer
	msgbox Route35NationalParkGate_Text_YoungsterWonders, MSGBOX_DEFAULT
	closemessage
	release
	end

Route35NationalParkGate_Text_YoungsterWonders::
	.string "When is the next Bug-Catching Contest\n"
	.string "going to be?$"

Route35NationalParkGate_EventScript_BC2::
	lock
	faceplayer
	msgbox Route35NationalParkGate_Text_BC2, MSGBOX_DEFAULT
	closemessage
	release
	end

Route35NationalParkGate_Text_BC2::
	.string "I caught a whopping SCYTHER!$"

Route35NationalParkGate_EventScript_Beauty::
	lock
	faceplayer
	msgbox Route35NationalParkGate_Text_Beauty, MSGBOX_DEFAULT
	closemessage
	release
	end

Route35NationalParkGate_Text_Beauty::
	.string "He always wins these contests!$"
