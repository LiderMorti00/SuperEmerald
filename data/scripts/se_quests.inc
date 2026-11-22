@ Super Emerald: side quests that link the four regions together.
@  - Wally's journey: Ecruteak City -> Celadon City -> Hearthome City (VAR_SE_WALLY_QUEST)
@  - Steven's journey: Ruins of Alph -> Pewter City -> Oreburgh City (VAR_SE_STEVEN_QUEST)
@  - Pokemon requests: researchers in the Goldenrod, Celadon and Hearthome Pokemon Centers
@ The quest characters use FLAG_SE_QUEST_* flags, which are never set: IsObjectTemplateHidden
@ shows each of them only at its own quest stage.

SE_EventScript_QuestBagFull::
	msgbox SE_Text_QuestBagFull, MSGBOX_DEFAULT
	release
	end

SE_EventScript_QuestLeave::
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

@ ---------------------------------------------------------------------------
@ Wally
@ ---------------------------------------------------------------------------
SE_EventScript_WallyJohto::
	lock
	faceplayer
	msgbox SE_Text_WallyJohto, MSGBOX_DEFAULT
	setvar VAR_SE_WALLY_QUEST, 1
	goto SE_EventScript_QuestLeave

SE_EventScript_WallyKanto::
	lock
	faceplayer
	msgbox SE_Text_WallyKanto, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SE_EventScript_WallyNotNow
	cleartrainerflag TRAINER_SE_WALLY_KANTO
	trainerbattle_no_intro TRAINER_SE_WALLY_KANTO, SE_Text_WallyKantoDefeat
	msgbox SE_Text_WallyKantoAfter, MSGBOX_DEFAULT
	giveitem ITEM_PP_MAX, 3
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_QuestBagFull
	msgbox SE_Text_WallyKantoBye, MSGBOX_DEFAULT
	setvar VAR_SE_WALLY_QUEST, 2
	goto SE_EventScript_QuestLeave

SE_EventScript_WallySinnoh::
	lock
	faceplayer
	goto_if_unset FLAG_SE_SINNOH_LEAGUE_CLEARED, SE_EventScript_WallySinnohWait
	msgbox SE_Text_WallySinnoh, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SE_EventScript_WallyNotNow
	cleartrainerflag TRAINER_SE_WALLY_SINNOH
	trainerbattle_no_intro TRAINER_SE_WALLY_SINNOH, SE_Text_WallySinnohDefeat
	msgbox SE_Text_WallySinnohAfter, MSGBOX_DEFAULT
	giveitem ITEM_ABILITY_PATCH
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_QuestBagFull
	msgbox SE_Text_WallySinnohBye, MSGBOX_DEFAULT
	setvar VAR_SE_WALLY_QUEST, 3
	goto SE_EventScript_QuestLeave

SE_EventScript_WallySinnohWait::
	msgbox SE_Text_WallySinnohWait, MSGBOX_DEFAULT
	release
	end

SE_EventScript_WallyNotNow::
	msgbox SE_Text_WallyNotNow, MSGBOX_DEFAULT
	release
	end

@ ---------------------------------------------------------------------------
@ Steven
@ ---------------------------------------------------------------------------
SE_EventScript_StevenJohto::
	lock
	faceplayer
	msgbox SE_Text_StevenJohto, MSGBOX_DEFAULT
	giveitem ITEM_ABILITY_CAPSULE
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_QuestBagFull
	msgbox SE_Text_StevenJohtoBye, MSGBOX_DEFAULT
	setvar VAR_SE_STEVEN_QUEST, 1
	goto SE_EventScript_QuestLeave

SE_EventScript_StevenKanto::
	lock
	faceplayer
	msgbox SE_Text_StevenKanto, MSGBOX_DEFAULT
	giveitem ITEM_RARE_CANDY, 5
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_QuestBagFull
	msgbox SE_Text_StevenKantoBye, MSGBOX_DEFAULT
	setvar VAR_SE_STEVEN_QUEST, 2
	goto SE_EventScript_QuestLeave

SE_EventScript_StevenSinnoh::
	lock
	faceplayer
	goto_if_unset FLAG_SE_SINNOH_LEAGUE_CLEARED, SE_EventScript_StevenSinnohWait
	msgbox SE_Text_StevenSinnoh, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SE_EventScript_StevenNotNow
	cleartrainerflag TRAINER_SE_STEVEN_SINNOH
	trainerbattle_no_intro TRAINER_SE_STEVEN_SINNOH, SE_Text_StevenSinnohDefeat
	msgbox SE_Text_StevenSinnohAfter, MSGBOX_DEFAULT
	giveitem ITEM_METAGROSSITE
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_QuestBagFull
	msgbox SE_Text_StevenSinnohBye, MSGBOX_DEFAULT
	setvar VAR_SE_STEVEN_QUEST, 3
	goto SE_EventScript_QuestLeave

SE_EventScript_StevenSinnohWait::
	msgbox SE_Text_StevenSinnohWait, MSGBOX_DEFAULT
	release
	end

SE_EventScript_StevenNotNow::
	msgbox SE_Text_StevenNotNow, MSGBOX_DEFAULT
	release
	end

@ ---------------------------------------------------------------------------
@ Pokemon requests. VAR_0x8004/VAR_0x8005 = the two species that count.
@ ---------------------------------------------------------------------------
SE_EventScript_RequestCheck::
	checkspecies VAR_0x8004
	goto_if_eq VAR_RESULT, TRUE, SE_EventScript_RequestHas
	checkspecies VAR_0x8005
	goto_if_eq VAR_RESULT, TRUE, SE_EventScript_RequestHas
	setvar VAR_RESULT, FALSE
	return
SE_EventScript_RequestHas::
	setvar VAR_RESULT, TRUE
	return

@ Goldenrod: Pokemon from Hoenn
SE_EventScript_RequestJohto::
	lock
	faceplayer
	goto_if_ge VAR_SE_REQUEST_JOHTO, 3, SE_EventScript_RequestJohtoDone
	goto_if_ge VAR_SE_REQUEST_JOHTO, 1, SE_EventScript_RequestJohtoNext
	msgbox SE_Text_RequestJohtoIntro, MSGBOX_DEFAULT
SE_EventScript_RequestJohtoNext::
	switch VAR_SE_REQUEST_JOHTO
	case 0, SE_EventScript_RequestJohto0
	case 1, SE_EventScript_RequestJohto1
	case 2, SE_EventScript_RequestJohto2
SE_EventScript_RequestJohto0::
	setvar VAR_0x8004, SPECIES_WINGULL
	setvar VAR_0x8005, SPECIES_PELIPPER
	msgbox SE_Text_RequestJohto0, MSGBOX_DEFAULT
	call SE_EventScript_RequestCheck
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_RequestNotYet
	msgbox SE_Text_RequestThanks, MSGBOX_DEFAULT
	giveitem ITEM_RARE_CANDY, 3
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_QuestBagFull
	setvar VAR_SE_REQUEST_JOHTO, 1
	goto SE_EventScript_RequestMore
SE_EventScript_RequestJohto1::
	setvar VAR_0x8004, SPECIES_SPINDA
	setvar VAR_0x8005, SPECIES_SPINDA
	msgbox SE_Text_RequestJohto1, MSGBOX_DEFAULT
	call SE_EventScript_RequestCheck
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_RequestNotYet
	msgbox SE_Text_RequestThanks, MSGBOX_DEFAULT
	giveitem ITEM_PP_UP, 3
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_QuestBagFull
	setvar VAR_SE_REQUEST_JOHTO, 2
	goto SE_EventScript_RequestMore
SE_EventScript_RequestJohto2::
	setvar VAR_0x8004, SPECIES_ABSOL
	setvar VAR_0x8005, SPECIES_ABSOL
	msgbox SE_Text_RequestJohto2, MSGBOX_DEFAULT
	call SE_EventScript_RequestCheck
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_RequestNotYet
	msgbox SE_Text_RequestThanksLast, MSGBOX_DEFAULT
	giveitem ITEM_ABILITY_CAPSULE
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_QuestBagFull
	setvar VAR_SE_REQUEST_JOHTO, 3
SE_EventScript_RequestJohtoDone::
	msgbox SE_Text_RequestJohtoDone, MSGBOX_DEFAULT
	release
	end

@ Celadon: Pokemon from Johto
SE_EventScript_RequestKanto::
	lock
	faceplayer
	goto_if_ge VAR_SE_REQUEST_KANTO, 3, SE_EventScript_RequestKantoDone
	goto_if_ge VAR_SE_REQUEST_KANTO, 1, SE_EventScript_RequestKantoNext
	msgbox SE_Text_RequestKantoIntro, MSGBOX_DEFAULT
SE_EventScript_RequestKantoNext::
	switch VAR_SE_REQUEST_KANTO
	case 0, SE_EventScript_RequestKanto0
	case 1, SE_EventScript_RequestKanto1
	case 2, SE_EventScript_RequestKanto2
SE_EventScript_RequestKanto0::
	setvar VAR_0x8004, SPECIES_GIRAFARIG
	setvar VAR_0x8005, SPECIES_FARIGIRAF
	msgbox SE_Text_RequestKanto0, MSGBOX_DEFAULT
	call SE_EventScript_RequestCheck
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_RequestNotYet
	msgbox SE_Text_RequestThanks, MSGBOX_DEFAULT
	giveitem ITEM_RARE_CANDY, 3
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_QuestBagFull
	setvar VAR_SE_REQUEST_KANTO, 1
	goto SE_EventScript_RequestMore
SE_EventScript_RequestKanto1::
	setvar VAR_0x8004, SPECIES_SNEASEL
	setvar VAR_0x8005, SPECIES_WEAVILE
	msgbox SE_Text_RequestKanto1, MSGBOX_DEFAULT
	call SE_EventScript_RequestCheck
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_RequestNotYet
	msgbox SE_Text_RequestThanks, MSGBOX_DEFAULT
	giveitem ITEM_PP_MAX, 2
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_QuestBagFull
	setvar VAR_SE_REQUEST_KANTO, 2
	goto SE_EventScript_RequestMore
SE_EventScript_RequestKanto2::
	setvar VAR_0x8004, SPECIES_MANTINE
	setvar VAR_0x8005, SPECIES_MANTYKE
	msgbox SE_Text_RequestKanto2, MSGBOX_DEFAULT
	call SE_EventScript_RequestCheck
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_RequestNotYet
	msgbox SE_Text_RequestThanksLast, MSGBOX_DEFAULT
	giveitem ITEM_ABILITY_PATCH
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_QuestBagFull
	setvar VAR_SE_REQUEST_KANTO, 3
SE_EventScript_RequestKantoDone::
	msgbox SE_Text_RequestKantoDone, MSGBOX_DEFAULT
	release
	end

@ Hearthome: Pokemon from Kanto
SE_EventScript_RequestSinnoh::
	lock
	faceplayer
	goto_if_ge VAR_SE_REQUEST_SINNOH, 3, SE_EventScript_RequestSinnohDone
	goto_if_ge VAR_SE_REQUEST_SINNOH, 1, SE_EventScript_RequestSinnohNext
	msgbox SE_Text_RequestSinnohIntro, MSGBOX_DEFAULT
SE_EventScript_RequestSinnohNext::
	switch VAR_SE_REQUEST_SINNOH
	case 0, SE_EventScript_RequestSinnoh0
	case 1, SE_EventScript_RequestSinnoh1
	case 2, SE_EventScript_RequestSinnoh2
SE_EventScript_RequestSinnoh0::
	setvar VAR_0x8004, SPECIES_TAUROS
	setvar VAR_0x8005, SPECIES_TAUROS
	msgbox SE_Text_RequestSinnoh0, MSGBOX_DEFAULT
	call SE_EventScript_RequestCheck
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_RequestNotYet
	msgbox SE_Text_RequestThanks, MSGBOX_DEFAULT
	giveitem ITEM_RARE_CANDY, 5
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_QuestBagFull
	setvar VAR_SE_REQUEST_SINNOH, 1
	goto SE_EventScript_RequestMore
SE_EventScript_RequestSinnoh1::
	setvar VAR_0x8004, SPECIES_KANGASKHAN
	setvar VAR_0x8005, SPECIES_KANGASKHAN
	msgbox SE_Text_RequestSinnoh1, MSGBOX_DEFAULT
	call SE_EventScript_RequestCheck
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_RequestNotYet
	msgbox SE_Text_RequestThanks, MSGBOX_DEFAULT
	giveitem ITEM_GOLD_BOTTLE_CAP
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_QuestBagFull
	setvar VAR_SE_REQUEST_SINNOH, 2
	goto SE_EventScript_RequestMore
SE_EventScript_RequestSinnoh2::
	setvar VAR_0x8004, SPECIES_CHANSEY
	setvar VAR_0x8005, SPECIES_BLISSEY
	msgbox SE_Text_RequestSinnoh2, MSGBOX_DEFAULT
	call SE_EventScript_RequestCheck
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_RequestNotYet
	msgbox SE_Text_RequestThanksLast, MSGBOX_DEFAULT
	giveitem ITEM_MASTER_BALL
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_QuestBagFull
	setvar VAR_SE_REQUEST_SINNOH, 3
SE_EventScript_RequestSinnohDone::
	msgbox SE_Text_RequestSinnohDone, MSGBOX_DEFAULT
	release
	end

SE_EventScript_RequestNotYet::
	msgbox SE_Text_RequestNotYet, MSGBOX_DEFAULT
	release
	end

SE_EventScript_RequestMore::
	msgbox SE_Text_RequestMore, MSGBOX_DEFAULT
	release
	end

@ ---------------------------------------------------------------------------
@ Texts
@ ---------------------------------------------------------------------------
SE_Text_QuestBagFull:
	.string "Oh, your BAG is full.\n"
	.string "Make some room and come back!$"

SE_Text_WallyJohto:
	.string "WALLY: {PLAYER}! I can't believe it!\n"
	.string "The CHAMPION of HOENN, here in JOHTO!\p"
	.string "After you beat me at VICTORY ROAD,\n"
	.string "I decided to see the world too.\p"
	.string "The people of ECRUTEAK say legendary\n"
	.string "POKéMON once lived in these towers…\p"
	.string "My GALLADE and I still have a lot\n"
	.string "to learn. I'll head east to KANTO.\p"
	.string "When we meet again, I want to show\n"
	.string "you how much stronger we've gotten!$"

SE_Text_WallyKanto:
	.string "WALLY: {PLAYER}! I knew you'd come\n"
	.string "to KANTO after beating the JOHTO\l"
	.string "LEAGUE. Everyone's talking about it!\p"
	.string "I've been training on the routes\n"
	.string "around CELADON. Will you battle me?$"

SE_Text_WallyKantoDefeat:
	.string "You're still so far ahead of me…$"

SE_Text_WallyKantoAfter:
	.string "WALLY: Haha… I still lost, but it\n"
	.string "was closer than last time, right?\p"
	.string "Here, take these. They really helped\n"
	.string "my team while I trained.$"

SE_Text_WallyKantoBye:
	.string "WALLY: I heard there's a region far\n"
	.string "to the north called SINNOH.\p"
	.string "I'll train there next. See you in\n"
	.string "HEARTHOME CITY, {PLAYER}!$"

SE_Text_WallySinnohWait:
	.string "WALLY: {PLAYER}! You made it to\n"
	.string "SINNOH too!\p"
	.string "I want our next battle to be our\n"
	.string "best one ever.\p"
	.string "Come back after you've beaten the\n"
	.string "SINNOH LEAGUE, okay?$"

SE_Text_WallySinnoh:
	.string "WALLY: The CHAMPION of HOENN, JOHTO,\n"
	.string "KANTO and now SINNOH…\p"
	.string "When we first met, I couldn't even\n"
	.string "catch a POKéMON on my own.\p"
	.string "Now my team and I are ready.\n"
	.string "{PLAYER}, let's battle with everything!$"

SE_Text_WallySinnohDefeat:
	.string "This is what a true CHAMPION is like!$"

SE_Text_WallySinnohAfter:
	.string "WALLY: …I lost again. But I'm not sad.\n"
	.string "I gave it everything I had.\p"
	.string "Please take this. It's my thanks for\n"
	.string "everything you've shown me.$"

SE_Text_WallySinnohBye:
	.string "WALLY: I'm going home to VERDANTURF.\n"
	.string "My family must be worried by now.\p"
	.string "{PLAYER}, thank you. For everything.$"

SE_Text_WallyNotNow:
	.string "WALLY: Oh… Okay. I'll keep training\n"
	.string "here until you're ready!$"

SE_Text_StevenJohto:
	.string "STEVEN: Well, {PLAYER}! The CHAMPION\n"
	.string "of HOENN, all the way out in JOHTO.\p"
	.string "These RUINS are fascinating. The\n"
	.string "UNOWN carvings speak of stones that\l"
	.string "awaken hidden power in POKéMON.\p"
	.string "I'm following those legends from\n"
	.string "region to region. Here, take this.\l"
	.string "I found it in the ruins.$"

SE_Text_StevenJohtoBye:
	.string "STEVEN: My research will take me to\n"
	.string "PEWTER CITY in KANTO next.\p"
	.string "It has a famous MUSEUM of SCIENCE.\n"
	.string "Come find me there!$"

SE_Text_StevenKanto:
	.string "STEVEN: {PLAYER}, we meet again.\p"
	.string "The fossils in the PEWTER MUSEUM\n"
	.string "are older than any stone I've seen.\p"
	.string "The stones of legend seem to come\n"
	.string "from deep inside SINNOH's mountains.\p"
	.string "You've helped my research more than\n"
	.string "you know. Please, take these.$"

SE_Text_StevenKantoBye:
	.string "STEVEN: I'll be in OREBURGH CITY in\n"
	.string "SINNOH, near its old coal mine.\p"
	.string "When you get there… let's have a\n"
	.string "battle worthy of two CHAMPIONS.$"

SE_Text_StevenSinnohWait:
	.string "STEVEN: {PLAYER}! The mine here is full\n"
	.string "of stones I've never seen before.\p"
	.string "Become the CHAMPION of SINNOH first.\n"
	.string "Then we'll battle, CHAMPION to\l"
	.string "CHAMPION.$"

SE_Text_StevenSinnoh:
	.string "STEVEN: So you've won in SINNOH!\n"
	.string "You've come so far since HOENN.\p"
	.string "My team has trained in every region\n"
	.string "I've visited, just like you.\p"
	.string "Shall we see which of us is truly\n"
	.string "the strongest?$"

SE_Text_StevenSinnohDefeat:
	.string "I knew it… You are the best there is.$"

SE_Text_StevenSinnohAfter:
	.string "STEVEN: What a battle! The stones of\n"
	.string "legend were right about you.\p"
	.string "This is the stone that started my\n"
	.string "journey. I want you to have it.$"

SE_Text_StevenSinnohBye:
	.string "STEVEN: My search is over. I'll go\n"
	.string "back to my home in MOSSDEEP.\p"
	.string "Come visit whenever you're in HOENN.\n"
	.string "Take care, {PLAYER}.$"

SE_Text_StevenNotNow:
	.string "STEVEN: I'll be waiting here. Come\n"
	.string "back whenever you're ready.$"

SE_Text_RequestJohtoIntro:
	.string "Oh! You came from HOENN, didn't you?\n"
	.string "I'm a POKéMON researcher.\p"
	.string "I study how POKéMON from other\n"
	.string "regions live here in JOHTO.\p"
	.string "Could you show me some POKéMON from\n"
	.string "HOENN? I'll reward you, of course!$"

SE_Text_RequestJohto0:
	.string "First, I'd love to see a WINGULL\n"
	.string "or a PELIPPER in your party.$"

SE_Text_RequestJohto1:
	.string "Next, please show me a SPINDA.\n"
	.string "I want to see its spot pattern!$"

SE_Text_RequestJohto2:
	.string "Last one! The rare ABSOL. They say\n"
	.string "it lives on HOENN's ROUTE 120.$"

SE_Text_RequestJohtoDone:
	.string "Thanks to you, my study of HOENN\n"
	.string "POKéMON is complete!\p"
	.string "I hear a colleague of mine in\n"
	.string "CELADON CITY studies JOHTO POKéMON.$"

SE_Text_RequestKantoIntro:
	.string "You're the TRAINER who beat the\n"
	.string "JOHTO LEAGUE! What luck!\p"
	.string "I'm researching POKéMON that live\n"
	.string "in JOHTO but not in KANTO.\p"
	.string "Could you show me a few? I'll give\n"
	.string "you something nice for each one!$"

SE_Text_RequestKanto0:
	.string "First, a GIRAFARIG, please. Its tail\n"
	.string "has a brain of its own, you know!$"

SE_Text_RequestKanto1:
	.string "Next, a SNEASEL or a WEAVILE. They\n"
	.string "live in JOHTO's ICE PATH.$"

SE_Text_RequestKanto2:
	.string "Last one! A MANTINE or a MANTYKE.\n"
	.string "They swim near CIANWOOD CITY.$"

SE_Text_RequestKantoDone:
	.string "My notes on JOHTO POKéMON are\n"
	.string "complete! Thank you so much!\p"
	.string "A friend of mine in HEARTHOME CITY,\n"
	.string "SINNOH, is studying KANTO POKéMON.$"

SE_Text_RequestSinnohIntro:
	.string "Wow, a TRAINER who's been to HOENN,\n"
	.string "JOHTO and KANTO!\p"
	.string "I'm writing a book about POKéMON\n"
	.string "from KANTO. Could you help me?\p"
	.string "Show me the POKéMON I ask for,\n"
	.string "and I'll reward you well!$"

SE_Text_RequestSinnoh0:
	.string "First, a TAUROS. You can find them\n"
	.string "in KANTO's SAFARI ZONE.$"

SE_Text_RequestSinnoh1:
	.string "Next, a KANGASKHAN. I hear they live\n"
	.string "in ROCK TUNNEL.$"

SE_Text_RequestSinnoh2:
	.string "Last one! A CHANSEY or a BLISSEY.\n"
	.string "Please, I've never seen one up close!$"

SE_Text_RequestSinnohDone:
	.string "My book about KANTO POKéMON is\n"
	.string "finished, all thanks to you!\p"
	.string "You really are a TRAINER of the\n"
	.string "whole WORLD.$"

SE_Text_RequestNotYet:
	.string "Come back when you have one in\n"
	.string "your party!$"

SE_Text_RequestThanks:
	.string "Oh! That's it! Thank you!\n"
	.string "Here's your reward.$"

SE_Text_RequestThanksLast:
	.string "Amazing! That's the last one!\n"
	.string "Here, you've earned this.$"

SE_Text_RequestMore:
	.string "I have another request for you.\n"
	.string "Talk to me again whenever you can.$"
