NewBarkTown_PlayersHouse_1F_hns_MapScripts::
	.byte 0


NewBarkTown_PlayersHouse_1F_Text_MomHurryUpElmIsWaiting::
	.string "MOM: PROF.ELM is waiting for you.\p"
	.string "Hurry up, baby!$"

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
	.string "Hi, {PLAYER}!\p"
	.string "I'm visiting!\p"
	.string "Have you heard?\p"
	.string "My daughter is adamant about\n"
	.string "becoming PROF.ELM's assistant.\p"
	.string "She really loves POKéMON!$"
