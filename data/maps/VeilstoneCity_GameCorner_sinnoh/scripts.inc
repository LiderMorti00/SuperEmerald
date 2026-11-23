VeilstoneCity_GameCorner_sinnoh_MapScripts::
	.byte 0


VeilstoneCity_GameCorner_EventScript_Woman2::
	msgbox VeilstoneCity_GameCorner_Text_CoinsAreNeededToPlay, MSGBOX_NPC
	end

VeilstoneCity_GameCorner_Text_CoinsAreNeededToPlay::
	.string "Hey, kid, if you want to play here, you\n"
	.string "need a COIN CASE.\p"
	.string "I think the young man next door had\n"
	.string "one.$"

VeilstoneCity_GameCorner_EventScript_Gentleman::
	msgbox VeilstoneCity_GameCorner_Text_RouletteOnlyLuck, MSGBOX_NPC
	end

VeilstoneCity_GameCorner_Text_RouletteOnlyLuck::
	.string "I want Coins, of course, but setting\n"
	.string "records is hot, too!$"

VeilstoneCity_GameCorner_Text_ThisIsMauvilleGameCorner::
	.string "This is VEILSTONE GAME CORNER.$"

SE_S_VeilstoneCity_GameCorner_VeilstoneCity_GameCorner_EventScript_CoinsClerk::
	msgbox VeilstoneCity_GameCorner_Text_ThisIsMauvilleGameCorner, MSGBOX_NPC
	end

VeilstoneCity_GameCorner_Text_ExchangeCoinsForPrizes::
	.string "Welcome.\p"
	.string "You can exchange your COINS for\n"
	.string "prizes here.$"

SE_S_VeilstoneCity_GameCorner_VeilstoneCity_GameCorner_EventScript_PrizeCornerDolls::
	msgbox VeilstoneCity_GameCorner_Text_ExchangeCoinsForPrizes, MSGBOX_NPC
	end

VeilstoneCity_GameCorner_EventScript_Girl::
	msgbox VeilstoneCity_GameCorner_Text_SNNothingGoingMyWay, MSGBOX_NPC
	end

VeilstoneCity_GameCorner_Text_SNNothingGoingMyWay::
	.string "Sigh… Nothing's going my way today…\p"
	.string "Are you a TRAINER? Did you battle the\n"
	.string "GYM LEADER?\p"
	.string "She happens to be my daughter. She's\n"
	.string "some kind of tough!$"

VeilstoneCity_GameCorner_EventScript_PokefanM::
	lock
	faceplayer
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, TRUE, VeilstoneCity_GameCorner_EventScript_TryGive20Coins
	msgbox VeilstoneCity_GameCorner_Text_NeedCoinCaseGoNextDoor, MSGBOX_DEFAULT
	goto VeilstoneCity_GameCorner_EventScript_NPCReturnToSlots
	end

VeilstoneCity_GameCorner_EventScript_NPCReturnToSlots::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VeilstoneCity_GameCorner_Text_NeedCoinCaseGoNextDoor::
	.string "Hey, kid, if you want to play here,\n"
	.string "you need a COIN CASE.\p"
	.string "I think the young lady next door\n"
	.string "had one. Go see her!$"

VeilstoneCity_GameCorner_EventScript_TryGive20Coins::
	goto_if_set FLAG_SN_RECEIVED_20_COINS, VeilstoneCity_GameCorner_EventScript_PokefanMNormal
	checkcoins VAR_TEMP_1
	goto_if_ge VAR_TEMP_1, 1, VeilstoneCity_GameCorner_EventScript_PokefanMNormal @ Only give 20 coins if player has no coins
	setflag FLAG_SN_RECEIVED_20_COINS
	addcoins 20
	msgbox VeilstoneCity_GameCorner_Text_LuckOnlyLastSoLongTakeCoins, MSGBOX_DEFAULT
	playse SE_SHOP
	goto VeilstoneCity_GameCorner_EventScript_PokefanMNormal
	end

VeilstoneCity_GameCorner_EventScript_PokefanMNormal::
	msgbox VeilstoneCity_GameCorner_Text_MauvilleSomethingForEveryone, MSGBOX_DEFAULT
	goto VeilstoneCity_GameCorner_EventScript_NPCReturnToSlots
	end

VeilstoneCity_GameCorner_Text_MauvilleSomethingForEveryone::
	.string "VEILSTONE has something for\n"
	.string "everyone.\p"
	.string "For me, it's the GAME CORNER.$"

VeilstoneCity_GameCorner_Text_LuckOnlyLastSoLongTakeCoins::
	.string "My luck can only last so long.\n"
	.string "This is too much for me.\l"
	.string "Here, take some COINS!$"

VeilstoneCity_GameCorner_EventScript_OldMan::
	lock
	faceplayer
	msgbox VeilstoneCity_GameCorner_Text_RouletteTablesDifferentRates, MSGBOX_DEFAULT
	goto VeilstoneCity_GameCorner_EventScript_NPCReturnToSlots
	end

VeilstoneCity_GameCorner_Text_RouletteTablesDifferentRates::
	.string "A friend in my group scored a ton of\n"
	.string "Coins here.\p"
	.string "Why mess with a good thing? I'll try the\n"
	.string "same spot, too!$"

VeilstoneCity_GameCorner_EventScript_Cook::
	lock
	faceplayer
	msgbox VeilstoneCity_GameCorner_Text_EasyToLoseTrackOfTime, MSGBOX_DEFAULT
	goto VeilstoneCity_GameCorner_EventScript_NPCReturnToSlots
	end

VeilstoneCity_GameCorner_Text_EasyToLoseTrackOfTime::
	.string "When a POKé BALL appears, it's a chance\n"
	.string "to line up slot marks.\p"
	.string "Replays and PIKACHU line up even if\n"
	.string "you don't make an effort.\p"
	.string "But you need to aim for better marks,\n"
	.string "like POKé BALLS and Moon Stones.$"

SE_S_VeilstoneCity_GameCorner_VeilstoneCity_GameCorner_EventScript_PrizeCornerTMs::
	msgbox VeilstoneCity_GameCorner_Text_ExchangeCoinsForPrizes, MSGBOX_NPC
	end

VeilstoneCity_GameCorner_EventScript_Man::
	lock
	faceplayer
	msgbox VeilstoneCity_GameCorner_Text_UpTo3CoinsCanBeUsed, MSGBOX_DEFAULT
	goto VeilstoneCity_GameCorner_EventScript_NPCReturnToSlots
	end

VeilstoneCity_GameCorner_Text_UpTo3CoinsCanBeUsed::
	.string "Up to three COINS can be used to play\n"
	.string "the SLOTS.$"

VeilstoneCity_GameCorner_EventScript_Maniac::
	lock
	faceplayer
	msgbox VeilstoneCity_GameCorner_Text_DifficultToStopOn7, MSGBOX_DEFAULT
	goto VeilstoneCity_GameCorner_EventScript_NPCReturnToSlots
	end

VeilstoneCity_GameCorner_Text_DifficultToStopOn7::
	.string "Listen, when CLEFAIRY appears, that's\n"
	.string "your chance to line up sevens.\p"
	.string "Line those babies up and you're into\n"
	.string "the bonus round!$"

VeilstoneCity_GameCorner_EventScript_Woman::
	lock
	faceplayer
	msgbox VeilstoneCity_GameCorner_Text_HeresSomeSlotsInfo, MSGBOX_DEFAULT
	goto VeilstoneCity_GameCorner_EventScript_NPCReturnToSlots
	end

VeilstoneCity_GameCorner_Text_HeresSomeSlotsInfo::
	.string "Shoot for 10! Line up those bonus\n"
	.string "rounds!\p"
	.string "If you complete 10 uninterrupted\n"
	.string "bonus rounds, please go to the\l"
	.string "counter.\p"
	.string "You will be presented with a\n"
	.string "fabulous prize!$"

VeilstoneCity_GameCorner_EventScript_SNLooker::
	lock
	faceplayer
	goto_if_set FLAG_SN_HIDE_STARK_R3, VeilstoneCity_GameCorner_EventScript_SNLookerPost
	msgbox VeilstoneCity_GameCorner_Text_SNLooker, MSGBOX_DEFAULT
	goto VeilstoneCity_GameCorner_EventScript_SNLookerEnd

VeilstoneCity_GameCorner_EventScript_SNLookerEnd::
	closemessage
	applymovement LOCALID_SN_GC_LOOKER, Common_Movement_FaceUp
	waitmovement 0
	release
	end

VeilstoneCity_GameCorner_Text_SNLooker::
	.string "LOOKER: Ah, it is you, yes.\p"
	.string "Examine, if you will, the reels. The Team\n"
	.string "GALACTIC logo, it is here.\p"
	.string "Further investigation is needed, and I\n"
	.string "am just the man to do it.\p"
	.string "Also, where the masses gather, so too\n"
	.string "does information.\p"
	.string "…Ack. My streak is broken.$"

VeilstoneCity_GameCorner_EventScript_SNLookerPost::
	msgbox VeilstoneCity_GameCorner_Text_SNLookerPost, MSGBOX_DEFAULT
	goto VeilstoneCity_GameCorner_EventScript_SNLookerEnd

VeilstoneCity_GameCorner_Text_SNLookerPost::
	.string "LOOKER: Ah, it is you, yes.\p"
	.string "I have decided to use the opportunity\n"
	.string "of being here in SINNOH.\p"
	.string "I am therefore trying to teach moves\n"
	.string "to POKéMON that I have captured.\p"
	.string "Also, if I have nothing to do, it means\n"
	.string "the world, it is at peace.\p"
	.string "…Ack. My streak is broken.$"

VeilstoneCity_GameCorner_EventScript_SlotMachine0::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, VeilstoneCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

VeilstoneCity_GameCorner_EventScript_NoCoinCase::
	msgbox VeilstoneCity_GameCorner_Text_CantPlayWithNoCoinCase, MSGBOX_DEFAULT
	releaseall
	end

VeilstoneCity_GameCorner_Text_CantPlayWithNoCoinCase::
	.string "You can't play if you don't have\n"
	.string "a COIN CASE.$"

VeilstoneCity_GameCorner_EventScript_SlotMachine1::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, VeilstoneCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 1
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

VeilstoneCity_GameCorner_EventScript_SlotMachine2::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, VeilstoneCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 2
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

VeilstoneCity_GameCorner_EventScript_SlotMachine3::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, VeilstoneCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 3
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

VeilstoneCity_GameCorner_EventScript_SlotMachine4::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, VeilstoneCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 4
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

VeilstoneCity_GameCorner_EventScript_SlotMachine5::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, VeilstoneCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 5
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

VeilstoneCity_GameCorner_EventScript_SlotMachine6::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, VeilstoneCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 6
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

VeilstoneCity_GameCorner_EventScript_SlotMachine7::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, VeilstoneCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 7
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

VeilstoneCity_GameCorner_EventScript_SlotMachine8::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, VeilstoneCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 8
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

VeilstoneCity_GameCorner_EventScript_SlotMachine9::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, VeilstoneCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 9
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

VeilstoneCity_GameCorner_EventScript_SlotMachine10::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, VeilstoneCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 10
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end

VeilstoneCity_GameCorner_EventScript_SlotMachine11::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, VeilstoneCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 11
	specialvar VAR_RESULT, GetSlotMachineId
	playslotmachine VAR_RESULT
	releaseall
	end
