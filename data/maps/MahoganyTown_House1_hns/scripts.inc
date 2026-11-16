MahoganyTown_House1_hns_MapScripts::
	.byte 0


MahoganyRedGyaradosHouse_Text_Teacher_Rockets::
    .string "I've been hearing laughter on the\n"
    .string "radio…\p"
    .string "It's creepy.$"

SE_J_MahoganyTown_House1_hns_MahoganyTown_House1_EventScript_Teacher::
	msgbox MahoganyRedGyaradosHouse_Text_Teacher_Rockets, MSGBOX_NPC
	end

MahoganyTown_House1_EventScript_BlackBelt::
	msgbox MahoganyRedGyaradosHouse_Text_BlackBelt, MSGBOX_NPC
	end

MahoganyRedGyaradosHouse_Text_BlackBelt::
    .string "I heard that a red GYARADOS appeared\n"
    .string "at the LAKE.\p"
    .string "That's odd, since even ordinary\n"
    .string "GYARADOS are rare in that lake…$"
