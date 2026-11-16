GoldenrodCity_GameCorner_hns_MapScripts::
	.byte 0


SE_J_GoldenrodCity_GameCorner_hns_GoldenrodCity_GameCorner_PrizeRoom_EventScript_PrizeClerkMons::
	msgbox MauvilleCity_GameCorner_Text_ExchangeCoinsForPrizes, MSGBOX_NPC
	end

GoldenrodCity_GameCorner_Text_PrizeVendorIntro::
    .string "Welcome!\p"
    .string "We exchange your game coins for\n"
    .string "fabulous prizes!$"

SE_J_GoldenrodCity_GameCorner_hns_GoldenrodCity_GameCorner_PrizeRoom_EventScript_PrizeClerkTMs::
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorIntro, MSGBOX_NPC
	end

GoldenrodCity_GameCorner_EventScript_PokefanM::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_PokefanM1, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_GameCorner_Text_PokefanM1::
    .string "I just love this new slot machine.\p"
    .string "It's more of a challenge than the\n"
    .string "ones in CELADON.$"

GoldenrodCity_GameCorner_EventScript_PokefanM2::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_PokefanM2, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_GameCorner_Text_PokefanM2::
    .string "I couldn't win at the slots, and I\n"
    .string "blew it on roulette.\p"
    .string "I got so furious, I tossed out my\n"
    .string "COIN CASE in the UNDERGROUND.$"

GoldenrodCity_GameCorner_EventScript_Gentleman::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_Gentleman, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_GameCorner_Text_Gentleman::
    .string "I taught ICE BEAM to my POKéMON.\p"
    .string "It was hard to get enough coins for\n"
    .string "it, but it was worth it.$"

GoldenrodCity_GameCorner_EventScript_Pharmacist::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_Pharmacist, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_GameCorner_Text_Pharmacist::
    .string "I always play this slot machine.\n"
    .string "It pays out more than others,\l"
    .string "I think.$"

GoldenrodCity_GameCorner_EventScript_CooltrainerM::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_CooltrainerM, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_GameCorner_Text_CooltrainerM::
    .string "Life is a gamble. I'm going to pull\n"
    .string "till I drop!$"

GoldenrodCity_GameCorner_EventScript_Hiker::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_MoveTutorInside, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_GameCorner_Text_MoveTutorInside::
    .string "Wahahah! The coins keep rolling in!$"

GoldenrodCity_GameCorner_EventScript_VFAttendant2::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_VFAttendant2, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceDown
	waitmovement 0
	release
	end

@ Voltorb Flip Menu Option Strings

GoldenrodCity_GameCorner_Text_VFAttendant2::
	.string "Try the other side of\n"
	.string "the table, pal.$"

GoldenrodCity_GameCorner_EventScript_VFAttendant1::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_VFAttendant1, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceDown
	waitmovement 0
	release
	end

GoldenrodCity_GameCorner_Text_VFAttendant1::
	.string "You want to play VOLTORB FLIP?\p"
	.string "You need to be on the other\n"
	.string "side of the table.$"

GoldenrodCity_GameCorner_EventScript_VoltorbFlip::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_GameCorner_EventScript_VF_NoCoinCase
	message GoldenrodCity_GameCorner_Text_VF_Welcome
	waitmessage
	setvar VAR_TEMP_4, 0

GoldenrodCity_GameCorner_Text_VF_Welcome::
	.string "Welcome to VOLTORB FLIP!\p$"

GoldenrodCity_GameCorner_EventScript_VF_NoCoinCase::
	msgbox GoldenrodCity_GameCorner_Text_VF_NeedCoinCase, MSGBOX_DEFAULT
	releaseall
	end

GoldenrodCity_GameCorner_Text_VF_NeedCoinCase::
	.string "Oh? You don't have a COIN CASE.$"
