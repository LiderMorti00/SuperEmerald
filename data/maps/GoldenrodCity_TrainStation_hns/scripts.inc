GoldenrodCity_TrainStation_hns_MapScripts::
	.byte 0


GoldenrodMagnetTrainStation_Text_OfficerTrainHasntComeIn::
    .string "The train hasn't come in…\p"
    .string "I know! I'll carry the passengers\n"
    .string "on my back!\p"
    .string "That won't work.$"

SE_J_GoldenrodCity_TrainStation_hns_GoldenrodCity_TrainStation_EventScript_Attendant::
	msgbox GoldenrodMagnetTrainStation_Text_OfficerTrainHasntComeIn, MSGBOX_NPC
	end

GoldenrodCity_TrainStation_EventScript_Gent::
	lock
	faceplayer
	msgbox GoldenrodMagnetTrainStation_Text_GentlemanPresident, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodMagnetTrainStation_Text_GentlemanPresident::
    .string "I'm the PRESIDENT.\p"
    .string "My dream was to build a train that\n"
    .string "is faster than any POKéMON.\p"
    .string "It really brings JOHTO much closer\n"
    .string "to KANTO.$"

GoldenrodCity_TrainStation_EventScript_Boy::
	lock
	msgbox GoldenrodCity_TrainStation_Text_Boy, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_TrainStation_Text_Boy::
	.string "You brought the MAGNET TRAIN PASS,\n"
	.string "right?$"

GoldenrodCity_TrainStation_EventScript_Psychic::
	lock
	msgbox GoldenrodCity_TrainStation_Text_Psychic, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_TrainStation_Text_Psychic::
	.string "I thought you had it!$"
