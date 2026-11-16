BlackthornCity_House3_hns_MapScripts::
	.byte 0


BlackthornCity_MoveDeletersHouse_Text_ICanMakeMonForgetMove::
	.string "Uh…\n"
	.string "Oh, yes, I'm the MOVE DELETER.\p"
	.string "I can make POKéMON forget their moves.\p"
	.string "Would you like me to do that?$"

SE_J_BlackthornCity_House3_hns_BlackthornCity_MoveDeletersHouse_EventScript_MoveDeleter::
	msgbox BlackthornCity_MoveDeletersHouse_Text_ICanMakeMonForgetMove, MSGBOX_NPC
	end

BlackthornCity_MoveRelearnersHouse_Text_ImTheMoveTutor::
	.string "I'm the MOVE TUTOR.\p"
	.string "I know all the moves that POKéMON\n"
	.string "learn--every one of them--and I can\l"
	.string "teach POKéMON those moves.\p"
	.string "I can teach a move to a POKéMON\n"
	.string "of yours if you'd like.\p"
	.string "I'll do it for a HEART SCALE.\n"
	.string "I'm collecting those now.$"

SE_J_BlackthornCity_House3_hns_BlackthornCity_MoveRelearnersHouse_EventScript_MoveRelearner::
	msgbox BlackthornCity_MoveRelearnersHouse_Text_ImTheMoveTutor, MSGBOX_NPC
	end
