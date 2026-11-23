NewBarkTown_PlayersHouse_1F_hns_MapScripts::
	.byte 0


NewBarkTown_PlayersHouse_1F_Text_MomHurryUpElmIsWaiting::
	.string "WOMAN: Oh, hello! Are you a friend\n"
	.string "of my son's?\p"
	.string "He left to travel all over JOHTO\n"
	.string "with the POKéMON PROF.ELM gave him.\p"
	.string "If you see him, tell him his mom\n"
	.string "says to eat properly!$"

SE_J_NewBarkTown_PlayersHouse_1F_hns_NewBarkTown_PlayersHouse_1F_EventScript_Mom::
	goto_if_eq VAR_SE_ORO_STATE, 0, SE_NewBarkMom_OroOutside_Script
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomHurryUpElmIsWaiting, MSGBOX_NPC
	end

NewBarkTown_PlayersHouse_1F_EventScript_MomsFriend::
	lock
	faceplayer
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomsFriend, MSGBOX_DEFAULT
	applymovement LOCALID_MOMS_FRIEND, NewBarkTown_PlayersHouse_1F_MovementFaceRight
	waitmovement 0
	release
	end

NewBarkTown_PlayersHouse_1F_MovementFaceRight::
	face_right
	step_end

NewBarkTown_PlayersHouse_1F_Text_MomsFriend::
	.string "Hi there! I'm visiting, too!\p"
	.string "Have you heard?\p"
	.string "My daughter is adamant about\n"
	.string "becoming PROF.ELM's assistant.\p"
	.string "She really loves POKéMON!$"

SE_NewBarkMom_OroOutside_Script::
	msgbox SE_NewBarkMom_OroOutside_Text, MSGBOX_NPC
	end

SE_NewBarkMom_OroOutside_Text::
	.string "WOMAN: Oh, hello! You must be the\n"
	.string "TRAINER from HOENN!\p"
	.string "My son ORO is right outside.\n"
	.string "He's been dying to battle you!$"
