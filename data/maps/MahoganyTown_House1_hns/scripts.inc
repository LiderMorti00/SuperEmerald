MahoganyTown_House1_hns_MapScripts::
	.byte 0


MahoganyRedGyaradosHouse_Text_Teacher_Rockets::
    .string "I've been hearing laughter on the\n"
    .string "radio…\p"
    .string "It's creepy.$"

SE_J_MahoganyTown_House1_hns_MahoganyTown_House1_EventScript_Teacher::
	goto_if_ne VAR_SE_ROCKET_QUEST, 1, SE_MahoganyHouse1_Radio_Script
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

SE_MahoganyHouse1_Radio_Script::
	msgbox SE_MahoganyHouse1_Radio_Text, MSGBOX_NPC
	end

SE_MahoganyHouse1_Radio_Text::
	.string "The radio has been playing such\n"
	.string "nice music lately.\p"
	.string "It's so relaxing.$"
