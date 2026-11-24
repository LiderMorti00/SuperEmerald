CelesticTown_Ruins_sinnoh_MapScripts::
	.byte 0

CelesticTown_Ruins_EventScript_SNElder::
	call CelesticTown_Ruins_EventScript_SNCharm
	lock
	faceplayer
	goto_if_set FLAG_SN_RECEIVED_HM_SURF, CelesticTown_Ruins_EventScript_SNElderDone
	msgbox CelesticTown_Ruins_Text_SNElder1, MSGBOX_DEFAULT
	giveitem ITEM_HM_SURF
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SN_RECEIVED_HM_SURF
	msgbox CelesticTown_Ruins_Text_SNElder2, MSGBOX_DEFAULT
	release
	end

CelesticTown_Ruins_Text_SNElder2::
	.string "Elder: If a POKéMON learns SURF, it\n"
	.string "can carry you across water and the\l"
	.string "sea. Please, use it well.$"

CelesticTown_Ruins_Text_SNElder1::
	.string "Elder: That cave painting isn't\n"
	.string "protected simply because it's old.\p"
	.string "We've preserved it because we value\n"
	.string "the memories that it represents.\p"
	.string "A strange man once came here who\n"
	.string "failed to understand that.\p"
	.string "He wanted to change the world…\n"
	.string "What need is there to change it?\p"
	.string "The time and space of SINNOH are\n"
	.string "filled with the memories of\l"
	.string "countless people and POKéMON.\p"
	.string "Oh, yes. You came all the way from\n"
	.string "HOENN, didn't you? Take this.\p"
	.string "It belonged to my granddaughter,\n"
	.string "but she doesn't use it anymore.$"

CelesticTown_Ruins_EventScript_SNElderDone::
	msgbox CelesticTown_Ruins_Text_PtNpc1_0, MSGBOX_DEFAULT
	release
	end

CelesticTown_Ruins_Text_PtNpc1_0::
	.string "That cave painting isn't protected\n"
	.string "simply because it's old.\p"
	.string "We've preserved it because we value\n"
	.string "the memories that it represents.\p"
	.string "It is a legacy of people and POKéMON\n"
	.string "beyond measure.\p"
	.string "A man who fails to understand that…\n"
	.string "What world could he dream of?$"

CelesticTown_Ruins_EventScript_SNCharmEnd::
	return

CelesticTown_Ruins_EventScript_SNCharm::
	goto_if_unset FLAG_SN_RECEIVED_OLD_CHARM, CelesticTown_Ruins_EventScript_SNCharmEnd
	lock
	faceplayer
	msgbox CelesticTown_Ruins_Text_SNCharm, MSGBOX_DEFAULT
	clearflag FLAG_SN_RECEIVED_OLD_CHARM
	playse SE_SUCCESS
	msgbox CelesticTown_Ruins_Text_SNCharm2, MSGBOX_DEFAULT
	msgbox CelesticTown_Ruins_Text_SNCharm3, MSGBOX_DEFAULT
	release
	goto CelesticTown_Ruins_EventScript_SNCharmEnd

CelesticTown_Ruins_Text_SNCharm3::
	.string "This Old CHARM is something made in\n"
	.string "CELESTIC TOWN long, long ago.\p"
	.string "It was made in honor of a mythical\n"
	.string "deity said to have created SINNOH.\p"
	.string "These Old Charms are still discovered\n"
	.string "now and again.\p"
	.string "Since you're in CELESTIC TOWN, why not\n"
	.string "look around inside the ruins?$"

CelesticTown_Ruins_Text_SNCharm2::
	.string "{PLAYER} handed over the Old CHARM to\n"
	.string "the elder.$"

CelesticTown_Ruins_Text_SNCharm::
	.string "Oh, you were magnificent! Aren't you\n"
	.string "quite the TRAINER?\p"
	.string "As the elder of CELESTIC TOWN, I give\n"
	.string "you my thanks.\p"
	.string "Oh? That Old CHARM… May I see that,\n"
	.string "dear?\p"
	.string "… What's that?\p"
	.string "You say CYNTHIA entrusted you with it\n"
	.string "to deliver to me?\p"
	.string "That CYNTHIA… She's my granddaughter.$"

CelesticTown_Ruins_EventScript_PtSign1::
	msgbox CelesticTown_Ruins_Text_PtSign1, MSGBOX_SIGN
	end

CelesticTown_Ruins_Text_PtSign1::
	.string "{PLAYER} examined the ancient cave\n"
	.string "painting.\p"
	.string "Mysterious designs cover a whole\n"
	.string "section of the wall.\p"
	.string "There are three strange things forming\n"
	.string "a triangle.\p"
	.string "In the middle of them, a shining\n"
	.string "sphere?\p"
	.string "What is this all about?$"

CelesticTown_Ruins_EventScript_PtSign2::
	msgbox CelesticTown_Ruins_Text_PtSign2, MSGBOX_SIGN
	end

CelesticTown_Ruins_Text_PtSign2::
	.string "{PLAYER} examined the ancient cave\n"
	.string "painting.\p"
	.string "Mysterious designs cover a whole\n"
	.string "section of the wall.\p"
	.string "There are three strange things forming\n"
	.string "a triangle.\p"
	.string "In the middle of them, a shining\n"
	.string "sphere?\p"
	.string "What is this all about?$"
