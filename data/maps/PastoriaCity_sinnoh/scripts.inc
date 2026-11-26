PastoriaCity_sinnoh_MapScripts::
	.byte 0

PastoriaCity_EventScript_PtNpc1::
	msgbox PastoriaCity_Text_PtNpc1, MSGBOX_NPC
	end

PastoriaCity_Text_PtNpc1::
	.string "Some TRAINERS deliberately prevent\n"
	.string "their POKéMON from evolving.\p"
	.string "They wait until the POKéMON levels up\n"
	.string "and learns certain moves.$"

PastoriaCity_EventScript_PtNpc2::
	lock
	faceplayer
	goto_if_set FLAG_SINNOH_BADGE4_GET, PastoriaCity_EventScript_PtNpc2_SNVar0
	msgbox PastoriaCity_Text_PtNpc2, MSGBOX_DEFAULT
	release
	end

PastoriaCity_Text_PtNpc2::
	.string "PASTORIA's GYM LEADER is awesome with\n"
	.string "his water attacks.\p"
	.string "You'll know what I mean when you\n"
	.string "challenge him.$"

PastoriaCity_EventScript_PtNpc2_SNVar0::
	msgbox PastoriaCity_Text_PtNpc2_SNVar0, MSGBOX_DEFAULT
	release
	end

PastoriaCity_Text_PtNpc2_SNVar0::
	.string "Wasn't the PASTORIA GYM LEADER kind of\n"
	.string "awesome in all sorts of ways?\p"
	.string "But don't judge him by the way he looks\n"
	.string "and acts.\p"
	.string "I hear he enters professional\n"
	.string "wrestling matches for prize money.\p"
	.string "That money goes to help people and\n"
	.string "POKéMON in trouble.$"

PastoriaCity_EventScript_PtNpc3::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CLEFAIRY, CRY_MODE_NORMAL
	msgbox PastoriaCity_Text_PtNpc3, MSGBOX_DEFAULT
	waitmoncry
	release
	end

PastoriaCity_Text_PtNpc3::
	.string "CLEFAIRY: Fiiih?!$"

PastoriaCity_EventScript_PtNpc4::
	msgbox PastoriaCity_Text_PtNpc4, MSGBOX_NPC
	end

PastoriaCity_Text_PtNpc4::
	.string "Here where I am standing, I'm\n"
	.string "smack-dab in the middle of town.$"

PastoriaCity_EventScript_PtNpc5::
	msgbox PastoriaCity_Text_PtNpc5, MSGBOX_NPC
	end

PastoriaCity_Text_PtNpc5::
	.string "I'm visiting here to see the GREAT\n"
	.string "MARSH.\p"
	.string "I'm staying at the lakeside hotel.$"

PastoriaCity_EventScript_PtNpc6::
	msgbox PastoriaCity_Text_PtNpc6, MSGBOX_NPC
	end

PastoriaCity_Text_PtNpc6::
	.string "I can't use the hidden move SURF until\n"
	.string "I beat the local GYM LEADER.$"

PastoriaCity_EventScript_PtNpc7::
	msgbox PastoriaCity_Text_PtNpc7, MSGBOX_NPC
	end

PastoriaCity_Text_PtNpc7::
	.string "Have you been to the POKéMON\n"
	.string "Mansion? It's on ROUTE 212.\p"
	.string "The owner, Mr. Backlot, likes to brag\n"
	.string "about his herd of rare POKéMON.$"

PastoriaCity_EventScript_SNPtSCIENTISTM::
	msgbox PastoriaCity_EventScript_SNPtSCIENTISTM_Text, MSGBOX_NPC
	end

PastoriaCity_EventScript_SNPtSCIENTISTM_Text::
	.string "I study rare POKéMON that appear only\n"
	.string "in the GREAT MARSH.$"

PastoriaCity_EventScript_SNPtPARASOLLADY::
	msgbox PastoriaCity_EventScript_SNPtPARASOLLADY_Text, MSGBOX_NPC
	end

PastoriaCity_EventScript_SNPtPARASOLLADY_Text::
	.string "Someone gave me a Berry, so I planted\n"
	.string "it and grew some more.\p"
	.string "Then, I took the Berries and cooked\n"
	.string "them into Poffins.\p"
	.string "All the work is worth it when I see how\n"
	.string "happy they make my POKéMON!$"

PastoriaCity_EventScript_PtSign1::
	msgbox PastoriaCity_Text_PtSign1, MSGBOX_SIGN
	end

PastoriaCity_Text_PtSign1::
	.string "PASTORIA CITY The Marsh City$"

PastoriaCity_EventScript_PtSign2::
	msgbox PastoriaCity_Text_PtSign2, MSGBOX_SIGN
	end

PastoriaCity_Text_PtSign2::
	.string "PASTORIA CITY POKéMON GYM LEADER:\n"
	.string "CRASHER WAKE The Torrential Masked\l"
	.string "Master!$"

PastoriaCity_EventScript_PtSign3::
	msgbox PastoriaCity_Text_PtSign3, MSGBOX_SIGN
	end

PastoriaCity_Text_PtSign3::
	.string "PASTORIA GREAT MARSH Observatory\n"
	.string "Gate$"

PastoriaCity_EventScript_PtSign4::
	msgbox PastoriaCity_Text_PtSign4, MSGBOX_SIGN
	end

PastoriaCity_Text_PtSign4::
	.string "Try the Safari Game in PASTORIA's\n"
	.string "GREAT MARSH!$"
