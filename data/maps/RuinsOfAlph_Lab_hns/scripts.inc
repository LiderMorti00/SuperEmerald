RuinsOfAlph_Lab_hns_MapScripts::
	.byte 0


RuinsOfAlph_Lab_EventScript_Scientist2::
	lock
	faceplayer
	msgbox RuinsOfAlph_Lab_Text_Scientist2, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_Lab_Text_Scientist2::
	.string "There are odd patterns drawn on\n"
	.string "on the walls of the RUINS.\p"
	.string "They must be the keys for\n"
	.string "unraveling the RUINS' mystery.$"

RuinsOfAlph_Lab_EventScript_Scientist1::
	lock
	faceplayer
	msgbox RuinsOfAlph_Lab_Text_Scientist1, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_Lab_Text_Scientist1::
	.string "The RUINS are about 1500 years old.\p"
	.string "But it's not known why they were\n"
	.string "built--or by whom.$"

RuinsOfAlph_Lab_Text_DevelopDeviceToResurrectFossils::
	.string "I've been trying to develop a device\n"
	.string "that resurrects POKéMON from fossils…\p"
	.string "And, it's working!$"

SE_J_RuinsOfAlph_Lab_hns_RuinsOfAlph_Lab_EventScript_FossilScientist::
	msgbox RuinsOfAlph_Lab_Text_DevelopDeviceToResurrectFossils, MSGBOX_NPC
	end

RuinsOfAlph_Lab_EventScript_Fossils::
	lock
	msgbox RuinsOfAlph_Lab_Text_Fossils, MSGBOX_DEFAULT
	closemessage
	release
	end

RuinsOfAlph_Lab_Text_Fossils::
	.string "Fossils found within the RUINS.\n"
	.string "Maybe there are more somewhere...$"

SE_J_RuinsOfAlph_Lab_hns_EventScript_FakePC::
	msgbox Text_BootUpPC, MSGBOX_SIGN
	end
