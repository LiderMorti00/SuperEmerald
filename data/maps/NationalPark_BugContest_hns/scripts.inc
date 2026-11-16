NationalPark_BugContest_hns_MapScripts::
	.byte 0


NationalPark_BugContest_EventScript_Trash::
	lock
	msgbox NationalPark_BugContest_Text_Trash, MSGBOX_SIGN
	closemessage
	release
	end

NationalPark_BugContest_Text_Trash::
	.string "Nothing here.$"

NationalPark_BugContest_EventScript_RelaxationSquare::
	lock
	msgbox NationalParkBugContest_Text_Sign_RelaxationSquare, MSGBOX_SIGN
	closemessage
	release
	end

NationalParkBugContest_Text_Sign_RelaxationSquare::
	.string "RELAXATION SQUARE\n"
	.string "NATIONAL PARK$"

NationalPark_BugContest_EventScript_BattleSign::
	lock
	msgbox NationalParkBugContest_Text_Sign_BattleNotice, MSGBOX_SIGN
	closemessage
	release
	end

NationalParkBugContest_Text_Sign_BattleNotice::
	.string "What is this notice?\p"
	.string "Please battle only in the grass.\p"
	.string "NATIONAL PARK WARDEN'S OFFICE$"

NationalPark_BugContest_EventScript_TrainerTips::
	lock
	msgbox NationalParkBugContest_Text_TrainerTips, MSGBOX_SIGN
	closemessage
	release
	end

NationalParkBugContest_Text_TrainerTips::
	.string "The NATIONAL PARK has different\n"
	.string "POKéMON during the BUG-CATCHING\l"
	.string "CONTEST.$"

NationalPark_BugContest_EventScript_BC2::
	lock
	faceplayer
	msgbox NationalParkBugContest_Text_Contestant2A, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalParkBugContest_Text_Contestant2A::
	.string "ED: My PARASECT puts POKéMON to\n"
	.string "sleep with SPORE.$"

NationalPark_BugContest_EventScript_BC1::
	lock
	faceplayer
	msgbox NationalParkBugContest_Text_ContestantShaun, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalParkBugContest_Text_ContestantShaun::
	.string "SHAUN: I'm not concerned about\n"
	.string "winning.\p"
	.string "I'm just looking for rare POKéMON.$"

NationalParkBugContest_Text_Attendant::
	.string "ATTENDANT: Would you like to end\n"
	.string "the contest?$"

SE_J_NationalPark_BugContest_hns_NationalPark_BugContest_EventScript_Attendant::
	msgbox NationalParkBugContest_Text_Attendant, MSGBOX_NPC
	end

NationalPark_BugContest_EventScript_Boy::
	lock
	faceplayer
	msgbox NationalParkBugContest_Text_Contestant6A, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalParkBugContest_Text_Contestant6A::
	.string "BARRY: You should weaken bug\n"
	.string "POKéMON first,\p"
	.string "then throw a BALL.$"

NationalPark_BugContest_EventScript_Belinda::
	lock
	faceplayer
	msgbox NationalParkBugContest_Text_ContestantBelinda, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalParkBugContest_Text_ContestantBelinda::
	.string "BELINDA: I'm going to win!\n"
	.string "Don't bother me.$"
