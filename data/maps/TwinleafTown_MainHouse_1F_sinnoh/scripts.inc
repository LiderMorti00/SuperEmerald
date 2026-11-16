TwinleafTown_MainHouse_1F_sinnoh_MapScripts::
	.byte 0


TwinleafTown_MainHouse_1F_EventScript_Mom::
	lock
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, TwinleafTown_MainHouse_1F_EventScript_SNMomNormal
	goto_if_set FLAG_SN_MOM_POSTGAME, TwinleafTown_MainHouse_1F_EventScript_SNMomNormal
	setflag FLAG_SN_MOM_POSTGAME
	msgbox TwinleafTown_MainHouse_1F_Text_SNMomPost, MSGBOX_DEFAULT
	release
	end

TwinleafTown_MainHouse_1F_Text_SNMomPost::
	.string "Mom: {PLAYER}!\p"
	.string "{RIVAL} came looking for you a\n"
	.string "little while ago.\p"
	.string "I don’t know what it was about, but he\n"
	.string "was shouting about you needing\p"
	.string "to get on a ship at Snowpoint City.\p"
	.string "You know how impatient he is. He was\n"
	.string "gone before I could ask.$"

TwinleafTown_MainHouse_1F_EventScript_SNMomNormal::
	goto_if_unset FLAG_SYS_POKEMON_GET, TwinleafTown_MainHouse_1F_EventScript_SNMomEarly
	goto_if_lt VAR_SN_SINNOH_STORY, 10, TwinleafTown_MainHouse_1F_EventScript_SNMomShoesInfo
	call TwinleafTown_MainHouse_1F_EventScript_SNMomRestText
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	goto_if_lt VAR_SN_SINNOH_STORY, 31, TwinleafTown_MainHouse_1F_EventScript_SNMomRandom
	goto_if_set FLAG_SYS_GAME_CLEAR, TwinleafTown_MainHouse_1F_EventScript_SNMomRandom
	msgbox TwinleafTown_MainHouse_1F_Text_SNMomWorried, MSGBOX_DEFAULT
	release
	end

TwinleafTown_MainHouse_1F_Text_SNMomWorried::
	.string "Mom: {PLAYER}, is everything all\n"
	.string "right?\p"
	.string "I get worried seeing the news...\p"
	.string "But you’re all right, aren’t you?\n"
	.string "After all, you’re never alone.$"

TwinleafTown_MainHouse_1F_EventScript_SNMomRandom::
	random 4
	switch VAR_RESULT
	case 0, TwinleafTown_MainHouse_1F_EventScript_SNMom0
	case 1, TwinleafTown_MainHouse_1F_EventScript_SNMom1
	case 2, TwinleafTown_MainHouse_1F_EventScript_SNMom2
	msgbox TwinleafTown_MainHouse_1F_Text_MomTalk, MSGBOX_DEFAULT
	release
	end

TwinleafTown_MainHouse_1F_Text_MomTalk::
	.string "Mom: {PLAYER}.\p"
	.string "Listen. Always treat your POKéMON with\n"
	.string "kindness.\p"
	.string "Your POKéMON work hard, not for\n"
	.string "themselves, but for you!$"

TwinleafTown_MainHouse_1F_EventScript_SNMom2::
	msgbox TwinleafTown_MainHouse_1F_Text_SNMomC, MSGBOX_DEFAULT
	release
	end

TwinleafTown_MainHouse_1F_Text_SNMomC::
	.string "Mom: While you’re gone, I go and visit\n"
	.string "{RIVAL}’s mom.\p"
	.string "We talk about this and that.\p"
	.string "Well, actually, all we do is talk about\n"
	.string "you two.$"

TwinleafTown_MainHouse_1F_EventScript_SNMom1::
	msgbox TwinleafTown_MainHouse_1F_Text_SNMomB, MSGBOX_DEFAULT
	release
	end

TwinleafTown_MainHouse_1F_Text_SNMomB::
	.string "Mom: {PLAYER}.\p"
	.string "Seeing you reminds me so much of your\n"
	.string "father.\p"
	.string "You two are so alike!$"

TwinleafTown_MainHouse_1F_EventScript_SNMom0::
	msgbox TwinleafTown_MainHouse_1F_Text_SNMomA, MSGBOX_DEFAULT
	release
	end

TwinleafTown_MainHouse_1F_Text_SNMomA::
	.string "Mom: {PLAYER}!\p"
	.string "You and your POKéMON are looking good!\n"
	.string "Nothing can stop you now!$"

TwinleafTown_MainHouse_1F_EventScript_SNMomRestText::
	gettime
	goto_if_lt VAR_0x8000, 4, TwinleafTown_MainHouse_1F_EventScript_SNMomRestLate
	goto_if_lt VAR_0x8000, 10, TwinleafTown_MainHouse_1F_EventScript_SNMomRestMorning
	goto_if_ge VAR_0x8000, 20, TwinleafTown_MainHouse_1F_EventScript_SNMomRestNight
	msgbox TwinleafTown_MainHouse_1F_Text_SNMomRest, MSGBOX_DEFAULT
	return

TwinleafTown_MainHouse_1F_Text_SNMomRest::
	.string "Mom: Welcome home, {PLAYER}. Are you and\n"
	.string "your POKéMON healthy?\p"
	.string "Take a quick rest, dear.$"

TwinleafTown_MainHouse_1F_EventScript_SNMomRestNight::
	msgbox TwinleafTown_MainHouse_1F_Text_SNMomRestNight, MSGBOX_DEFAULT
	return

TwinleafTown_MainHouse_1F_Text_SNMomRestNight::
	.string "Mom: Welcome home, {PLAYER}.\n"
	.string "Are you and your POKéMON healthy?\p"
	.string "I just made dinner.\n"
	.string "Take a quick rest, dear.$"

TwinleafTown_MainHouse_1F_EventScript_SNMomRestMorning::
	msgbox TwinleafTown_MainHouse_1F_Text_SNMomRestMorning, MSGBOX_DEFAULT
	return

TwinleafTown_MainHouse_1F_Text_SNMomRestMorning::
	.string "Mom: Welcome home, {PLAYER}.\n"
	.string "Are you and your POKéMON healthy?\p"
	.string "It’s still early in the morning.\n"
	.string "Take a quick rest, dear.$"

TwinleafTown_MainHouse_1F_EventScript_SNMomRestLate::
	msgbox TwinleafTown_MainHouse_1F_Text_SNMomRestLate, MSGBOX_DEFAULT
	return

TwinleafTown_MainHouse_1F_Text_SNMomRestLate::
	.string "Mom: Welcome home, {PLAYER}.\n"
	.string "Are you and your POKéMON healthy?\p"
	.string "It’s so late right now...\n"
	.string "Take a quick rest, dear.$"

TwinleafTown_MainHouse_1F_EventScript_SNMomShoesInfo::
	goto_if_lt VAR_SN_SINNOH_STORY, 5, TwinleafTown_MainHouse_1F_EventScript_SNMomTalk
	msgbox TwinleafTown_MainHouse_1F_Text_SNMomInstructions, MSGBOX_DEFAULT
	release
	end

TwinleafTown_MainHouse_1F_Text_SNMomInstructions::
	.string "Mom: I’ll read you the instructions\n"
	.string "for the Running Shoes...\p"
	.string "“Press the B Button and dash\n"
	.string "about faster than ever before!\p"
	.string "“Put on the Running Shoes and\n"
	.string "blaze new trails of adventure!”\p"
	.string "Well, isn’t that just nifty!$"

TwinleafTown_MainHouse_1F_EventScript_SNMomTalk::
	msgbox TwinleafTown_MainHouse_1F_Text_MomTalk, MSGBOX_DEFAULT
	release
	end

TwinleafTown_MainHouse_1F_EventScript_SNMomEarly::
	goto_if_ge VAR_SN_SINNOH_STORY, 2, TwinleafTown_MainHouse_1F_EventScript_SNMomWaiting
	msgbox TwinleafTown_MainHouse_1F_Text_SNMomImpatient, MSGBOX_DEFAULT
	release
	end

TwinleafTown_MainHouse_1F_Text_SNMomImpatient::
	.string "Mom: You know how impatient\n"
	.string "{RIVAL} is.\p"
	.string "He took off before I could even\n"
	.string "ask what it was about.$"

TwinleafTown_MainHouse_1F_EventScript_SNMomWaiting::
	msgbox TwinleafTown_MainHouse_1F_Text_SNMomIsntRivalWaiting, MSGBOX_DEFAULT
	release
	end

TwinleafTown_MainHouse_1F_Text_SNMomIsntRivalWaiting::
	.string "Mom: What is it, dear?\n"
	.string "Isn’t {RIVAL} waiting for you?$"

TwinleafTown_MainHouse_1F_EventScript_BarrysMom::
	msgbox TwinleafTown_MainHouse_1F_Text_BarrysMom2, MSGBOX_NPC
	end

TwinleafTown_MainHouse_1F_Text_BarrysMom2::
	.string "{PLAYER}’s mom: Let me think...\p"
	.string "Knowing my boy, he would probably head\n"
	.string "straight to Jubilife City...\p"
	.string "OK, please take that to my {PLAYER}.\p"
	.string "Mom: Bye-bye, {PLAYER}! Enjoy your\n"
	.string "adventure!$"
