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
