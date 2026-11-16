EternaCity_sinnoh_MapScripts::
	.byte 0


EternaCity_Text_Barry::
	.string "{RIVAL}: Hey, {PLAYER}!\p"
	.string "You came to see the POKéMON statue,\n"
	.string "right? I’ll take you there!$"

SE_S_EternaCity_EternaCity_EventScript_Barry::
	msgbox EternaCity_Text_Barry, MSGBOX_NPC
	end

EternaCity_Text_Cyrus::
	.string "Cyrus: ...So, this is Eterna’s POKéMON\n"
	.string "statue...\p"
	.string "Shaping our world are time and space in\n"
	.string "an intertwining spiral.\p"
	.string "Revered in Sinnoh are the POKéMON of\n"
	.string "time and space...\p"
	.string "Sinnoh’s myth... Its truth needs\n"
	.string "investigation...$"

SE_S_EternaCity_EternaCity_EventScript_Statue::
	msgbox EternaCity_Text_Cyrus, MSGBOX_NPC
	end

EternaCity_EventScript_PtNpc1::
	msgbox EternaCity_Text_PtNpc1, MSGBOX_NPC
	end

EternaCity_Text_PtNpc1::
	.string "If you're visiting ETERNA, you need to\n"
	.string "get yourself a Bicycle and take a ride\l"
	.string "down the Cycling Road.$"

EternaCity_EventScript_PtNpc2::
	msgbox EternaCity_Text_PtNpc2, MSGBOX_NPC
	end

EternaCity_Text_PtNpc2::
	.string "ETERNA CITY's not anything like it was\n"
	.string "before, way back in the day.$"

EternaCity_EventScript_PtNpc3::
	msgbox EternaCity_Text_PtNpc3, MSGBOX_NPC
	end

EternaCity_Text_PtNpc3::
	.string "They say this is an awesome POKéMON\n"
	.string "that people saw long ago.$"

EternaCity_EventScript_PtNpc4::
	msgbox EternaCity_Text_PtNpc4, MSGBOX_NPC
	end

EternaCity_Text_PtNpc4::
	.string "Since that TEAM GALACTIC building\n"
	.string "went up, the city's atmosphere has\l"
	.string "gotten all creepy and tense.\p"
	.string "I don't know what those people are\n"
	.string "doing up in that place...$"

EternaCity_EventScript_PtNpc5::
	msgbox EternaCity_Text_PtNpc5, MSGBOX_NPC
	end

EternaCity_Text_PtNpc5::
	.string "They say this is an old city.\p"
	.string "It doesn't look it, though. Not with all\n"
	.string "these tall buildings.$"

EternaCity_EventScript_PtNpc6::
	msgbox EternaCity_Text_PtNpc6, MSGBOX_NPC
	end

EternaCity_Text_PtNpc6::
	.string "My friend said TEAM GALACTIC took his\n"
	.string "favorite POKéMON away.\p"
	.string "I don't think he's telling the truth.\n"
	.string "TEAM GALACTIC looks so cool.\p"
	.string "They don't look like common thugs.$"

EternaCity_EventScript_PtNpc7::
	msgbox EternaCity_Text_PtNpc7, MSGBOX_NPC
	end

EternaCity_Text_PtNpc7::
	.string "The bike shop is closed. The owner\n"
	.string "hasn't been seen for days...$"

EternaCity_EventScript_PtNpc8::
	msgbox EternaCity_Text_PtNpc8, MSGBOX_NPC
	end

EternaCity_Text_PtNpc8::
	.string "Oh, wow! You got a Bicycle!\p"
	.string "You can ride down Cycling Road and end\n"
	.string "up in HEARTHOME CITY.\p"
	.string "It's a fast and fun ride. You should\n"
	.string "check it out!$"

EternaCity_EventScript_PtNpc9::
	msgbox EternaCity_Text_PtNpc9, MSGBOX_NPC
	end

EternaCity_Text_PtNpc9::
	.string "Oh, don't tell me you don't have an\n"
	.string "Explorer Kit?\p"
	.string "You should have a word with the man\n"
	.string "next door to the POKéMON CENTER.$"

EternaCity_EventScript_GalacticGruntM1::
	msgbox EternaCity_Text_GalacticGruntM1, MSGBOX_NPC
	end

EternaCity_Text_GalacticGruntM1::
	.string "Hey! You there, kid! Stay away from\n"
	.string "that POKéMON statue!\p"
	.string "TEAM GALACTIC is conducting an\n"
	.string "official investigation here!$"

EternaCity_EventScript_GalacticGruntM2::
	msgbox EternaCity_Text_GalacticGruntM2, MSGBOX_NPC
	end

EternaCity_Text_GalacticGruntM2::
	.string "Hey, you! Yeah, you, Trainer!\p"
	.string "Errr... It's OK. Never mind. You look\n"
	.string "tough.\p"
	.string "I won't take... Um, I'll just let you\n"
	.string "keep your POKéMON. Carry on!$"

EternaCity_EventScript_GalacticGruntM3::
	msgbox EternaCity_Text_GalacticGruntM3, MSGBOX_NPC
	end

EternaCity_Text_GalacticGruntM3::
	.string "Have you seen our building?\p"
	.string "TEAM GALACTIC is so stinking rich\n"
	.string "that we can have one built instantly!$"

EternaCity_EventScript_SNCynthiaEgg_T1::
	.string "Cynthia: Oh, there you are!\p"
	.string "I was looking for you. I’ve got\n"
	.string "something nice.\p"
	.string "I wanted you to have this POKéMON Egg.\n"
	.string "Will you accept it?$"

SE_S_EternaCity_EternaCity_EventScript_SNCynthiaEgg::
	msgbox EternaCity_EventScript_SNCynthiaEgg_T1, MSGBOX_NPC
	end

EternaCity_EventScript_Sign1::
	msgbox EternaCity_Text_Sign1, MSGBOX_SIGN
	end

EternaCity_Text_Sign1::
	.string "ETERNA CITY\p"
	.string "A city that remembers the past.$"

EternaCity_EventScript_Sign2::
	msgbox EternaCity_Text_Sign2, MSGBOX_SIGN
	end

EternaCity_Text_Sign2::
	.string "ETERNA CITY\p"
	.string "A city that remembers the past.$"

EternaCity_EventScript_Sign3::
	msgbox EternaCity_Text_Sign3, MSGBOX_SIGN
	end

EternaCity_Text_Sign3::
	.string "POKéMON CENTER\p"
	.string "Heal your POKéMON!$"

EternaCity_EventScript_Sign4::
	msgbox EternaCity_Text_Sign4, MSGBOX_SIGN
	end

EternaCity_Text_Sign4::
	.string "UNDERGROUND MAN'S HOUSE$"
