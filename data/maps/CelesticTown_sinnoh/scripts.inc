CelesticTown_sinnoh_MapScripts::
	.byte 0


CelesticTown_EventScript_PtNpc1::
	msgbox CelesticTown_Text_PtNpc1, MSGBOX_NPC
	end

CelesticTown_Text_PtNpc1::
	.string "Howdy! Studying up on local history?$"

CelesticTown_EventScript_PtNpc2::
	msgbox CelesticTown_Text_PtNpc2, MSGBOX_NPC
	end

CelesticTown_Text_PtNpc2::
	.string "Hey, do you know what they say?\p"
	.string "They say a POKéMON created the\n"
	.string "SINNOH region.$"

CelesticTown_EventScript_PtNpc3::
	msgbox CelesticTown_Text_PtNpc3, MSGBOX_NPC
	end

CelesticTown_Text_PtNpc3::
	.string "There's no POKéMON Mart in this town...\p"
	.string "Instead, you can buy and sell items in\n"
	.string "this house here.$"

CelesticTown_Text_SNWillYouMess::
	.string "This town is insignificant! There’s\n"
	.string "nothing of value here.\p"
	.string "It doesn’t need to exist, so I’ll blow it\n"
	.string "up with a Galactic Bomb!\p"
	.string "If you try to mess with me, I’ll shut\n"
	.string "you down with a POKéMON battle.\p"
	.string "So, what’s it going to be? Are you going\n"
	.string "to mess with me?$"

SE_S_CelesticTown_CelesticTown_EventScript_SNCEL_GRUNT::
	msgbox CelesticTown_Text_SNWillYouMess, MSGBOX_NPC
	end

CelesticTown_EventScript_SNCynthia_T1::
	.string "Cynthia: Was everything all right here?\p"
	.string "You saw those strange people with a\n"
	.string "Galactic Bomb, didn’t you?$"

SE_S_CelesticTown_CelesticTown_EventScript_SNCynthia::
	msgbox CelesticTown_EventScript_SNCynthia_T1, MSGBOX_NPC
	end

CelesticTown_EventScript_SNElderOut::
	msgbox CelesticTown_Text_SNOddSpaceman, MSGBOX_NPC
	end

CelesticTown_Text_SNOddSpaceman::
	.string "There’s an odd spaceman in front of\n"
	.string "the ruins.\p"
	.string "There isn’t anything there, but that\n"
	.string "only seemed to make him get angry.\p"
	.string "He’s saying he will blow the town up\n"
	.string "with a bomb...\p"
	.string "The nerve of it all...\p"
	.string "If only I were younger, I’d punish that\n"
	.string "spaceman with my POKéMON...$"

CelesticTown_EventScript_PtSign1::
	msgbox CelesticTown_Text_PtSign1, MSGBOX_SIGN
	end

CelesticTown_Text_PtSign1::
	.string "CELESTIC TOWN The Past Lives$"
