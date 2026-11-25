EternaCity_sinnoh_MapScripts::
	.byte 0

EternaCity_EventScript_BarryEnd::
	releaseall
	end

EternaCity_EventScript_Barry::
	lockall
	goto_if_ne VAR_SN_SINNOH_STORY, 24, EternaCity_EventScript_BarryEnd
	applymovement LOCALID_ETERNA_BARRY, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox EternaCity_Text_Barry, MSGBOX_DEFAULT
	closemessage
	setvar VAR_SN_SINNOH_STORY, 25
	setflag FLAG_HIDE_ETERNA_BARRY
	clearflag FLAG_HIDE_ETERNA_STATUE
	warpsilent MAP_ETERNA_CITY_SINNOH, 37, 15
	waitstate
	goto EternaCity_EventScript_BarryEnd

EternaCity_Text_Barry::
	.string "{RIVAL}: Hey, {PLAYER}!\p"
	.string "You came to see the POKéMON statue,\n"
	.string "right? I'll take you there!$"

EternaCity_EventScript_Statue::
	lockall
	goto_if_ne VAR_SN_SINNOH_STORY, 25, EternaCity_EventScript_BarryEnd
	applymovement LOCALID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	msgbox EternaCity_Text_Cyrus, MSGBOX_DEFAULT
	msgbox EternaCity_Text_BarryStatue, MSGBOX_DEFAULT
	msgbox EternaCity_Text_Cyrus2, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_ETERNA_CYRUS
	fadescreenswapbuffers FADE_FROM_BLACK
	msgbox EternaCity_Text_BarryBye, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_ETERNA_BARRY_STATUE
	fadescreenswapbuffers FADE_FROM_BLACK
	applymovement LOCALID_ETERNA_CYNTHIA, Common_Movement_FacePlayer
	applymovement LOCALID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	msgbox EternaCity_Text_Cynthia, MSGBOX_DEFAULT
	giveitem ITEM_HM_CUT
	msgbox EternaCity_Text_Cynthia2, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_ETERNA_CYNTHIA
	setflag FLAG_HIDE_ETERNA_STATUE
	fadescreenswapbuffers FADE_FROM_BLACK
	setvar VAR_SN_SINNOH_STORY, 26
	releaseall
	end

EternaCity_Text_Cynthia2::
	.string "CYNTHIA: Remember, the hidden move CUT\n"
	.string "can be used in the field.\p"
	.string "It will let you go places that were\n"
	.string "previously inaccessible to you.\p"
	.string "That's important for filling up your\n"
	.string "POKéDEX, right?\p"
	.string "Then luck be with you, young TRAINER!\p"
	.string "Oh, there's one last thing! Please give\n"
	.string "my regards to PROF. ROWAN.$"

EternaCity_Text_Cynthia::
	.string "???: Oh, that device you have…\p"
	.string "It is a POKéDEX? Wow, it brings back\n"
	.string "some memories.\p"
	.string "Pardon me, but what's your name?\p"
	.string "…\p"
	.string "OK, hello, {PLAYER}. I'll be sure to\n"
	.string "remember that name!\p"
	.string "My name is CYNTHIA. I'm a TRAINER just\n"
	.string "like you.\p"
	.string "I've been studying POKéMON mythology\n"
	.string "lately, just out of curiosity.\p"
	.string "CYNTHIA: Here in ETERNA CITY, there is a\n"
	.string "statue of an ancient POKéMON.\p"
	.string "Have you seen it already?\p"
	.string "According to myth, it was an extremely\n"
	.string "powerful POKéMON.\p"
	.string "Who knows? You may encounter\n"
	.string "something like it while you're traveling\l"
	.string "with your\p"
	.string "POKéDEX.\p"
	.string "Oh, I know! Try using this. It should be\n"
	.string "helpful.$"

EternaCity_Text_BarryBye::
	.string "{RIVAL}: Oh, hey!\p"
	.string "When we smacked together, a brilliant\n"
	.string "flash of inspiration came to me!\p"
	.string "An easy way to become a great TRAINER!\n"
	.string "Yeah, that!\p"
	.string "All right. Listen close…\p"
	.string "Make certain all your attacks hit!\n"
	.string "Avoid enemy attacks for sure!\p"
	.string "You do that, you'd never lose! You'd be\n"
	.string "the invincible TRAINER!\p"
	.string "Anyway, go check out the POKéMON\n"
	.string "statue. See you around!$"

EternaCity_Text_Cyrus2::
	.string "CYRUS: …Pardon me. Stand aside.$"

EternaCity_Text_BarryStatue::
	.string "{RIVAL}: Uh… who's this guy? Are\n"
	.string "you a researcher or something?$"

EternaCity_Text_Cyrus::
	.string "CYRUS: …So, this is ETERNA's POKéMON\n"
	.string "statue…\p"
	.string "Shaping our world are time and space in\n"
	.string "an intertwining spiral.\p"
	.string "Revered in SINNOH are the POKéMON of\n"
	.string "time and space…\p"
	.string "SINNOH's myth… Its truth needs\n"
	.string "investigation…$"

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
	.string "That TEAM GALACTIC building still\n"
	.string "gives me the creeps.\p"
	.string "I hope there's nobody left inside…$"

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
	.string "My friend said TEAM GALACTIC took\n"
	.string "his favorite POKéMON away.\p"
	.string "I didn't believe him, but he got it\n"
	.string "back after they broke up!$"

EternaCity_EventScript_PtNpc7::
	msgbox EternaCity_Text_PtNpc7, MSGBOX_NPC
	end

EternaCity_Text_PtNpc7::
	.string "The bike shop owner is back!\n"
	.string "He's been gone for days, you know.$"

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
	.string "Hey, you! Yeah, you, TRAINER!\p"
	.string "Errr… It's OK. Never mind. You look\n"
	.string "tough.\p"
	.string "I won't take… Um, I'll just let you\n"
	.string "keep your POKéMON. Carry on!$"

EternaCity_EventScript_GalacticGruntM3::
	msgbox EternaCity_Text_GalacticGruntM3, MSGBOX_NPC
	end

EternaCity_Text_GalacticGruntM3::
	.string "Have you seen our building?\p"
	.string "TEAM GALACTIC is so stinking rich\n"
	.string "that we can have one built instantly!$"

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
