PastoriaCity_sinnoh_MapScripts::
	.byte 0


PastoriaCity_EventScript_PtNpc1::
	msgbox PastoriaCity_Text_PtNpc1, MSGBOX_NPC
	end

PastoriaCity_Text_PtNpc1::
	.string "Some Trainers deliberately prevent\n"
	.string "their POKéMON from evolving.\p"
	.string "They wait until the POKéMON levels up\n"
	.string "and learns certain moves.$"

PastoriaCity_EventScript_PtNpc2::
	lock
	faceplayer
	goto_if_set FLAG_SINNOH_BADGE5_GET, PastoriaCity_EventScript_PtNpc2_SNVar0
	msgbox PastoriaCity_Text_PtNpc2, MSGBOX_DEFAULT
	release
	end

PastoriaCity_Text_PtNpc2::
	.string "PASTORIA's Gym Leader is awesome with\n"
	.string "his water attacks.\p"
	.string "You'll know what I mean when you\n"
	.string "challenge him.$"

PastoriaCity_EventScript_PtNpc2_SNVar0::
	msgbox PastoriaCity_Text_PtNpc2_SNVar0, MSGBOX_DEFAULT
	release
	end

PastoriaCity_Text_PtNpc2_SNVar0::
	.string "Wasn’t the Pastoria Gym Leader kind of\n"
	.string "awesome in all sorts of ways?\p"
	.string "But don’t judge him by the way he looks\n"
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
	.string "I'm visiting here to see the Great\n"
	.string "Marsh.\p"
	.string "I'm staying at the lakeside hotel.$"

PastoriaCity_EventScript_PtNpc6::
	msgbox PastoriaCity_Text_PtNpc6, MSGBOX_NPC
	end

PastoriaCity_Text_PtNpc6::
	.string "I can't use the hidden move Surf until\n"
	.string "I beat the local Gym Leader.$"

PastoriaCity_EventScript_PtNpc7::
	msgbox PastoriaCity_Text_PtNpc7, MSGBOX_NPC
	end

PastoriaCity_Text_PtNpc7::
	.string "Have you been to the POKéMON\n"
	.string "Mansion? It's on Route 212.\p"
	.string "The owner, Mr. Backlot, likes to brag\n"
	.string "about his herd of rare POKéMON.$"

PastoriaCity_EventScript_SNBarry_Intro::
	.string "BARRY: Whoops!\p"
	.string "Hehehe! I’m not always going to plow\n"
	.string "into you every time we meet!\p"
	.string "So how’s it going, {PLAYER}? Buffing up\n"
	.string "your POKéMON, eh?\p"
	.string "I’ll test you and your POKéMON out to\n"
	.string "see how buff and tough you are!$"

SE_S_PastoriaCity_PastoriaCity_EventScript_SNBarry::
	msgbox PastoriaCity_EventScript_SNBarry_Intro, MSGBOX_NPC
	end

PastoriaCity_Text_SNGrunt1::
	.string "What’s with you? Stop chasing after\n"
	.string "me, you.\p"
	.string "I’ve half a mind to pulverize you with\n"
	.string "my POKéMON!\p"
	.string "But I have to be on my way to the lake\n"
	.string "ASAP! So, you’re lucky! I’m out!\p"
	.string "All right, do I make myself clear? Don’t\n"
	.string "you dare follow me!$"

SE_S_PastoriaCity_PastoriaCity_EventScript_SNGrunt::
	msgbox PastoriaCity_Text_SNGrunt1, MSGBOX_NPC
	end

PastoriaCity_Text_SNWA1::
	.string "Wake: What’s this racket, then? Oh, it’s\n"
	.string "you two.\p"
	.string "{RIVAL}: Oh, Master!$"

SE_S_PastoriaCity_PastoriaCity_EventScript_SNWakeA::
	msgbox PastoriaCity_Text_SNWA1, MSGBOX_NPC
	end

PastoriaCity_Text_SNWB1::
	.string "{RIVAL}: Hey!\p"
	.string "What am I, chopped liver? Don’t forget\n"
	.string "I’m here, too!\p"
	.string "Wake: So, where’s this Galac...$"

SE_S_PastoriaCity_PastoriaCity_EventScript_SNBomb::
	msgbox PastoriaCity_Text_SNWB1, MSGBOX_NPC
	end

PastoriaCity_EventScript_SNPtSCIENTISTM::
	msgbox PastoriaCity_EventScript_SNPtSCIENTISTM_Text, MSGBOX_NPC
	end

PastoriaCity_EventScript_SNPtSCIENTISTM_Text::
	.string "I study rare POKéMON that appear only\n"
	.string "in the Great Marsh.$"

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

PastoriaCity_EventScript_SNBarryGuard::
	lock
	faceplayer
	msgbox PastoriaCity_Text_SNWhyArentYouGone, MSGBOX_DEFAULT
	msgbox PastoriaCity_Text_SNWB4, MSGBOX_DEFAULT
	release
	end

PastoriaCity_Text_SNWB4::
	.string "{RIVAL}: Hey! {PLAYER}! You go after\n"
	.string "that Galactic goon!\p"
	.string "I’m staying here like Master said!\n"
	.string "Gotta keep others from going in!\p"
	.string "Don’t let that Galactic guy get away!$"

PastoriaCity_Text_SNWhyArentYouGone::
	.string "{RIVAL}: What’s the matter?! Why\n"
	.string "aren’t you gone already?!\p"
	.string "Go after that Galactic goon!$"

PastoriaCity_EventScript_PtSign1::
	msgbox PastoriaCity_Text_PtSign1, MSGBOX_SIGN
	end

PastoriaCity_Text_PtSign1::
	.string "PASTORIA CITY The Marsh City$"

PastoriaCity_EventScript_PtSign2::
	msgbox PastoriaCity_Text_PtSign2, MSGBOX_SIGN
	end

PastoriaCity_Text_PtSign2::
	.string "PASTORIA CITY POKéMON Gym Leader:\n"
	.string "CRASHER WAKE The Torrential Masked\l"
	.string "Master!$"

PastoriaCity_EventScript_PtSign3::
	msgbox PastoriaCity_Text_PtSign3, MSGBOX_SIGN
	end

PastoriaCity_Text_PtSign3::
	.string "PASTORIA Great Marsh Observatory\n"
	.string "Gate$"

PastoriaCity_EventScript_PtSign4::
	msgbox PastoriaCity_Text_PtSign4, MSGBOX_SIGN
	end

PastoriaCity_Text_PtSign4::
	.string "Try the Safari Game in PASTORIA's\n"
	.string "Great Marsh!$"
