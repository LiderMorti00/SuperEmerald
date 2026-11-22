@ Pokémon Super Emerald: hand-made Johto scripts (the HnS ones are in data/maps/*_hns).

@ ---------------------------------------------------------------------------
@ Petalburg Gym: Norman gives the Johto Ticket after the Hoenn League
SE_EventScript_NormanTickets::
	checkitem ITEM_JOHTO_TICKET
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_NormanJohtoTicket
	return

SE_EventScript_NormanJohtoTicket::
	msgbox SE_Text_NormanJohtoTicket, MSGBOX_DEFAULT
	giveitem ITEM_JOHTO_TICKET
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_NormanJohtoTicketBagFull
	setflag FLAG_SE_RECEIVED_JOHTO_TICKET
	msgbox SE_Text_NormanJohtoTicketExplain, MSGBOX_DEFAULT
	release
	end

SE_EventScript_NormanJohtoTicketBagFull::
	call Common_EventScript_BagIsFull
	release
	end

SE_Text_NormanJohtoTicket:
	.string "NORMAN: {PLAYER}, you've become the\n"
	.string "CHAMPION of HOENN. I'm proud of you.\p"
	.string "You know, before we moved here, we\n"
	.string "lived in OLIVINE CITY, in JOHTO.\p"
	.string "You were so small… I wonder if you\n"
	.string "still remember your old friends there.\p"
	.string "Why don't you go and see your home\n"
	.string "region with your own eyes?\p"
	.string "Here, take this.$"

SE_Text_NormanJohtoTicketExplain:
	.string "NORMAN: That JOHTO TICKET lets you\n"
	.string "board the S.S. TIDAL in SLATEPORT.\p"
	.string "It sails to OLIVINE CITY.\p"
	.string "JOHTO has eight GYMS of its own.\n"
	.string "Show them what HOENN's CHAMPION\l"
	.string "is made of!$"

@ ---------------------------------------------------------------------------
@ Slateport harbor: S.S. Tidal to Olivine City with the Johto Ticket
SE_EventScript_SlateportOfferJohto::
	checkitem ITEM_CANALAVE_TICKET
	goto_if_eq VAR_RESULT, TRUE, SE_EventScript_SlateportOfferJohtoSinnoh
	checkitem ITEM_JOHTO_TICKET
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_NopReturn
	msgbox SE_Text_HarborJohtoTicket, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Common_EventScript_NopReturn
	goto_if_ne VAR_SE_JOHTO_ARRIVAL, 0, SE_EventScript_SlateportToOlivine
	setvar VAR_SE_JOHTO_ARRIVAL, 1
SE_EventScript_SlateportToOlivine::
	call SlateportCity_Harbor_EventScript_BoardFerry
	setvar VAR_SE_CRUISE_DEST, 1
	goto SE_EventScript_BoardTidal
	waitstate
	release
	end

SE_Text_HarborJohtoTicket:
	.string "Oh, that's a JOHTO TICKET!\p"
	.string "Would you like to sail to\n"
	.string "OLIVINE CITY in JOHTO?$"

@ ---------------------------------------------------------------------------
@ Olivine Port: the S.S. Aqua / S.S. Tidal sailor
SE_EventScript_OlivinePortSailor::
	lock
	faceplayer
	setvar VAR_0x8008, 1
	goto SE_EventScript_ShipSailor
	end

SE_EventScript_OlivinePortSailorKanto::
	message SE_Text_OlivineSailorWhere
	waitmessage
	dynmultipush SE_Text_ChoiceSlateport, 0
	dynmultipush SE_Text_ChoiceVermilion, 1
	dynmultistack 18, 6, FALSE, 2, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case 0, SE_EventScript_OlivineToSlateport
	case 1, SE_EventScript_OlivineToVermilion
	goto SE_EventScript_OlivinePortSailorDeclined
	end

SE_EventScript_OlivineToSlateport::
	msgbox SE_Text_OlivineSailorAllAboard, MSGBOX_DEFAULT
	closemessage
	playse SE_SHIP
	fadescreenspeed FADE_TO_BLACK, 12
	delay 60
	setvar VAR_SE_CRUISE_DEST, 2
	goto SE_EventScript_BoardTidal
	waitstate
	release
	end

SE_EventScript_OlivineToVermilion::
	msgbox SE_Text_OlivineSailorAllAboard, MSGBOX_DEFAULT
	closemessage
	call SE_EventScript_InitKantoPostgame
	playse SE_SHIP
	fadescreenspeed FADE_TO_BLACK, 12
	delay 60
	setvar VAR_SE_CRUISE_DEST, 3
	goto SE_EventScript_BoardAqua
	waitstate
	release
	end

SE_EventScript_OlivinePortSailorDeclined::
	msgbox SE_Text_OlivineSailorComeBack, MSGBOX_DEFAULT
	release
	end

SE_Text_OlivineSailorSlateport:
	.string "The S.S. TIDAL is bound for\n"
	.string "SLATEPORT CITY in HOENN.\p"
	.string "Would you like to board?$"

SE_Text_OlivineSailorWhere:
	.string "Where would you like to sail?$"

SE_Text_ChoiceSlateport:
	.string "SLATEPORT$"

SE_Text_ChoiceOlivine:
	.string "OLIVINE$"

SE_Text_ChoiceVermilion:
	.string "VERMILION$"

SE_Text_OlivineSailorAllAboard:
	.string "All aboard!$"

SE_Text_OlivineSailorComeBack:
	.string "Come back whenever you're ready\n"
	.string "to set sail.$"

@ ---------------------------------------------------------------------------
@ Olivine Port: Jasmine meets her childhood friend
SE_EventScript_OlivineJasmineArrival::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	clearflag FLAG_SE_HIDE_OLIVINE_PORT_JASMINE
	addobject LOCALID_OLIVINEPORT_SE_JASMINE
	applymovement LOCALID_OLIVINEPORT_SE_JASMINE, SE_Movement_JasmineApproach
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_OLIVINEPORT_SE_JASMINE, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox SE_Text_JasmineWelcome, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OLIVINEPORT_SE_JASMINE, SE_Movement_JasmineLeave
	waitmovement 0
	removeobject LOCALID_OLIVINEPORT_SE_JASMINE
	setflag FLAG_SE_HIDE_OLIVINE_PORT_JASMINE
	setvar VAR_SE_JOHTO_ARRIVAL, 2
	releaseall
	end

SE_Movement_JasmineApproach:
	walk_down
	walk_down
	walk_down
	step_end

SE_Movement_JasmineLeave:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SE_Text_JasmineWelcome:
	.string "…Um… Excuse me…\p"
	.string "Is that… {PLAYER}? It really is you!\p"
	.string "It's me, JASMINE! We used to play\n"
	.string "by the LIGHTHOUSE when we were\l"
	.string "little, remember?\p"
	.string "I heard you became the CHAMPION\n"
	.string "of HOENN… That's amazing.\p"
	.string "I'm the GYM LEADER of OLIVINE now.\n"
	.string "My STEEL-type POKéMON and I have\l"
	.string "become really strong, too.\p"
	.string "If you're going to challenge the\n"
	.string "GYMS of JOHTO… please come and see\l"
	.string "me at the GYM. I'll be waiting.\p"
	.string "Welcome home, {PLAYER}.$"

@ ---------------------------------------------------------------------------
@ Olivine City: the neighbor from the player's old house
SE_EventScript_OlivineNeighbor::
	lock
	faceplayer
	goto_if_set FLAG_SE_TALKED_OLIVINE_NEIGHBOR, SE_EventScript_OlivineNeighborAgain
	setflag FLAG_SE_TALKED_OLIVINE_NEIGHBOR
	msgbox SE_Text_OlivineNeighbor, MSGBOX_DEFAULT
	release
	end

SE_EventScript_OlivineNeighborAgain::
	msgbox SE_Text_OlivineNeighborAgain, MSGBOX_DEFAULT
	release
	end

SE_Text_OlivineNeighbor:
	.string "My, my… Is that you, {PLAYER}?\p"
	.string "I'd know that face anywhere!\n"
	.string "Your family lived right here, in\l"
	.string "this very house, before you all\l"
	.string "moved away to HOENN.\p"
	.string "You and little JASMINE were\n"
	.string "always running to the LIGHTHOUSE\l"
	.string "together.\p"
	.string "Now look at you, a grown TRAINER!\n"
	.string "Make yourself at home, dear.$"

SE_Text_OlivineNeighborAgain:
	.string "This house will always be your\n"
	.string "home too, {PLAYER}.$"

@ ---------------------------------------------------------------------------
@ Johto Gym Leaders (Super Emerald teams, HGSS-era Gym badges)
SE_EventScript_JohtoLeader_Falkner::
	trainerbattle_single TRAINER_SE_LEADER_FALKNER, SE_Text_FalknerIntro, SE_Text_FalknerDefeat, SE_EventScript_FalknerDefeated, NO_MUSIC
	goto_if_unset FLAG_SE_RECEIVED_JOHTO_TM1, SE_EventScript_FalknerGiveTM
	msgbox SE_Text_FalknerPost, MSGBOX_DEFAULT
	release
	end

SE_EventScript_FalknerDefeated::
	message SE_Text_ReceivedFalknerBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_JOHTO_BADGE1_GET
	goto SE_EventScript_FalknerGiveTM
	end

SE_EventScript_FalknerGiveTM::
	giveitem ITEM_TM_STEEL_WING
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SE_RECEIVED_JOHTO_TM1
	msgbox SE_Text_FalknerPost, MSGBOX_DEFAULT
	release
	end

SE_Text_FalknerIntro:
	.string "I'm FALKNER, the VIOLET CITY GYM\nLEADER!\pPeople say you can clip a FLYING-\ntype's wings with a jolt of\lelectricity…\pI won't let anyone say that about\nmy magnificent bird POKéMON!$"

SE_Text_FalknerDefeat:
	.string "…Darn! My dad's cherished bird\nPOKéMON… All right. Take this.$"

SE_Text_FalknerPost:
	.string "There are POKéMON GYMS in cities\nall over JOHTO.\pI'm going to train harder and become\nthe greatest bird master!$"

SE_Text_ReceivedFalknerBadge:
	.string "{PLAYER} received the ZEPHYRBADGE\nfrom FALKNER.$"

SE_EventScript_JohtoLeader_Bugsy::
	trainerbattle_single TRAINER_SE_LEADER_BUGSY, SE_Text_BugsyIntro, SE_Text_BugsyDefeat, SE_EventScript_BugsyDefeated, NO_MUSIC
	goto_if_unset FLAG_SE_RECEIVED_JOHTO_TM2, SE_EventScript_BugsyGiveTM
	msgbox SE_Text_BugsyPost, MSGBOX_DEFAULT
	release
	end

SE_EventScript_BugsyDefeated::
	message SE_Text_ReceivedBugsyBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_JOHTO_BADGE2_GET
	goto SE_EventScript_BugsyGiveTM
	end

SE_EventScript_BugsyGiveTM::
	giveitem ITEM_TM_GIGA_DRAIN
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SE_RECEIVED_JOHTO_TM2
	msgbox SE_Text_BugsyPost, MSGBOX_DEFAULT
	release
	end

SE_Text_BugsyIntro:
	.string "I'm BUGSY! I never lose when it\ncomes to bug POKéMON.\pMy research is going to make me the\nauthority on bug POKéMON!\pLet me demonstrate what I've learned\nfrom my studies.$"

SE_Text_BugsyDefeat:
	.string "Whoa, amazing! You're an expert on\nPOKéMON! My research isn't complete\lyet. OK, you win. Take this badge.$"

SE_Text_BugsyPost:
	.string "Bug POKéMON are deep. There are\nmany mysteries to be explored.\pStudy your favorites thoroughly.$"

SE_Text_ReceivedBugsyBadge:
	.string "{PLAYER} received the HIVEBADGE\nfrom BUGSY.$"

SE_EventScript_JohtoLeader_Whitney::
	trainerbattle_single TRAINER_SE_LEADER_WHITNEY, SE_Text_WhitneyIntro, SE_Text_WhitneyDefeat, SE_EventScript_WhitneyDefeated, NO_MUSIC
	goto_if_unset FLAG_SE_RECEIVED_JOHTO_TM3, SE_EventScript_WhitneyGiveTM
	msgbox SE_Text_WhitneyPost, MSGBOX_DEFAULT
	release
	end

SE_EventScript_WhitneyDefeated::
	message SE_Text_ReceivedWhitneyBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_JOHTO_BADGE3_GET
	goto SE_EventScript_WhitneyGiveTM
	end

SE_EventScript_WhitneyGiveTM::
	giveitem ITEM_TM_ATTRACT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SE_RECEIVED_JOHTO_TM3
	msgbox SE_Text_WhitneyPost, MSGBOX_DEFAULT
	release
	end

SE_Text_WhitneyIntro:
	.string "Hi! I'm WHITNEY!\pEveryone was into POKéMON, so I got\ninto it too! POKéMON are super cute!\pI only use FAIRY-type POKéMON now.\nAren't they the cutest?\pYou want to battle? I'm warning you\n--I'm good!$"

SE_Text_WhitneyDefeat:
	.string "Waaah! My precious FAIRIES…\n…Sniff… OK, OK. Here's your badge.$"

SE_Text_WhitneyPost:
	.string "Ah, that was a blast! I can't wait\nto show you how much stronger my\lfairies get next time!$"

SE_Text_ReceivedWhitneyBadge:
	.string "{PLAYER} received the PLAINBADGE\nfrom WHITNEY.$"

SE_EventScript_JohtoLeader_Morty::
	trainerbattle_single TRAINER_SE_LEADER_MORTY, SE_Text_MortyIntro, SE_Text_MortyDefeat, SE_EventScript_MortyDefeated, NO_MUSIC
	goto_if_unset FLAG_SE_RECEIVED_JOHTO_TM4, SE_EventScript_MortyGiveTM
	goto SE_EventScript_MortyPostOrWing
	end

SE_EventScript_MortyDefeated::
	message SE_Text_ReceivedMortyBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_JOHTO_BADGE4_GET
	goto SE_EventScript_MortyGiveTM
	end

SE_EventScript_MortyGiveTM::
	giveitem ITEM_TM_SHADOW_BALL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SE_RECEIVED_JOHTO_TM4
	goto SE_EventScript_MortyPostOrWing
	end

@ With all eight Johto badges, Morty hands over the Rainbow Wing
SE_EventScript_MortyPostOrWing::
	goto_if_set FLAG_SE_RECEIVED_RAINBOW_WING, SE_EventScript_MortyPost
	call SE_EventScript_CheckJohtoBadges
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_MortyPost
	msgbox SE_Text_MortyRainbowWing, MSGBOX_DEFAULT
	giveitem ITEM_RAINBOW_WING
	setflag FLAG_SE_RECEIVED_RAINBOW_WING
	msgbox SE_Text_MortyRainbowWingAfter, MSGBOX_DEFAULT
	release
	end

SE_EventScript_MortyPost::
	msgbox SE_Text_MortyPost, MSGBOX_DEFAULT
	release
	end

SE_Text_MortyIntro:
	.string "Good of you to have come.\pHere in ECRUTEAK, POKéMON have\nbeen revered.\pI've trained here since I was a\nchild, to see what cannot be seen.\pLet me show you what I've learned.$"

SE_Text_MortyDefeat:
	.string "I'm not good enough yet…\nAll right. This badge is yours.$"

SE_Text_MortyPost:
	.string "I see… Your journey has taken you\nto far-away places.\pAnd you have witnessed much more\nthan I have.$"

SE_Text_ReceivedMortyBadge:
	.string "{PLAYER} received the FOGBADGE\nfrom MORTY.$"

SE_EventScript_JohtoLeader_Chuck::
	trainerbattle_single TRAINER_SE_LEADER_CHUCK, SE_Text_ChuckIntro, SE_Text_ChuckDefeat, SE_EventScript_ChuckDefeated, NO_MUSIC
	goto_if_unset FLAG_SE_RECEIVED_JOHTO_TM5, SE_EventScript_ChuckGiveTM
	msgbox SE_Text_ChuckPost, MSGBOX_DEFAULT
	release
	end

SE_EventScript_ChuckDefeated::
	message SE_Text_ReceivedChuckBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_JOHTO_BADGE5_GET
	goto SE_EventScript_ChuckGiveTM
	end

SE_EventScript_ChuckGiveTM::
	giveitem ITEM_TM_FOCUS_PUNCH
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SE_RECEIVED_JOHTO_TM5
	msgbox SE_Text_ChuckPost, MSGBOX_DEFAULT
	release
	end

SE_Text_ChuckIntro:
	.string "WAHAHAH!\pSo you've come this far!\pLet me tell you, I'm tough!\pMy POKéMON will crush stones and\nshatter bones! Watch this!\pHah! … … … Let's go!$"

SE_Text_ChuckDefeat:
	.string "Wha? Huh? I lost?\nHow about that! You're worthy of\lthe STORMBADGE!$"

SE_Text_ChuckPost:
	.string "WAHAHAH! I enjoyed battling you!\pBut a loss is a loss!\pFrom now on, I'm going to train\n24 hours a day!$"

SE_Text_ReceivedChuckBadge:
	.string "{PLAYER} received the STORMBADGE\nfrom CHUCK.$"

SE_EventScript_JohtoLeader_Jasmine::
	trainerbattle_single TRAINER_SE_LEADER_JASMINE, SE_Text_JasmineIntro, SE_Text_JasmineDefeat, SE_EventScript_JasmineDefeated, NO_MUSIC
	goto_if_unset FLAG_SE_RECEIVED_JOHTO_TM6, SE_EventScript_JasmineGiveTM
	goto SE_EventScript_JasminePostOrWing
	end

SE_EventScript_JasmineDefeated::
	message SE_Text_ReceivedJasmineBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_JOHTO_BADGE6_GET
	goto SE_EventScript_JasmineGiveTM
	end

SE_EventScript_JasmineGiveTM::
	giveitem ITEM_TM_IRON_TAIL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SE_RECEIVED_JOHTO_TM6
	goto SE_EventScript_JasminePostOrWing
	end

@ With all eight Johto badges, Jasmine hands over the Silver Wing
SE_EventScript_JasminePostOrWing::
	goto_if_set FLAG_SE_RECEIVED_SILVER_WING, SE_EventScript_JasminePost
	call SE_EventScript_CheckJohtoBadges
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_JasminePost
	msgbox SE_Text_JasmineSilverWing, MSGBOX_DEFAULT
	giveitem ITEM_SILVER_WING
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SE_RECEIVED_SILVER_WING
	msgbox SE_Text_JasmineSilverWingAfter, MSGBOX_DEFAULT
	release
	end

SE_EventScript_JasminePost::
	goto_if_set FLAG_SE_JOHTO_LEAGUE_CLEARED, SE_EventScript_JasmineAfterLeague
	msgbox SE_Text_JasminePost, MSGBOX_DEFAULT
	release
	end

SE_EventScript_JasmineAfterLeague::
	msgbox SE_Text_JasmineAfterLeague, MSGBOX_DEFAULT
	release
	end

SE_Text_JasmineAfterLeague:
	.string "JASMINE: I heard you beat LANCE.\p"
	.string "When we raced to the LIGHTHOUSE,\n"
	.string "I always wanted to get there first.\p"
	.string "Now I'm glad I got to see how far\n"
	.string "we've both come.\p"
	.string "Whatever port you sail to next,\n"
	.string "I hope you'll visit OLIVINE again.$"

SE_Text_JasmineIntro:
	.string "{PLAYER}… You came.\pI've been waiting for this ever\nsince we were little.\pI use the… the clang! STEEL type!\pPlease, show me how strong you've\nbecome. I won't hold back.$"

SE_Text_JasmineDefeat:
	.string "…You really are amazing, {PLAYER}.\nPlease take this badge.$"

SE_Text_JasminePost:
	.string "Fighting you felt like the old days,\nwhen we raced to the LIGHTHOUSE.\pCome back and visit, OK? Olivine\nwill always be your home.$"

SE_Text_ReceivedJasmineBadge:
	.string "{PLAYER} received the MINERALBADGE\nfrom JASMINE.$"

SE_EventScript_JohtoLeader_Pryce::
	trainerbattle_single TRAINER_SE_LEADER_PRYCE, SE_Text_PryceIntro, SE_Text_PryceDefeat, SE_EventScript_PryceDefeated, NO_MUSIC
	goto_if_unset FLAG_SE_RECEIVED_JOHTO_TM7, SE_EventScript_PryceGiveTM
	msgbox SE_Text_PrycePost, MSGBOX_DEFAULT
	release
	end

SE_EventScript_PryceDefeated::
	message SE_Text_ReceivedPryceBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_JOHTO_BADGE7_GET
	goto SE_EventScript_PryceGiveTM
	end

SE_EventScript_PryceGiveTM::
	giveitem ITEM_TM_HAIL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SE_RECEIVED_JOHTO_TM7
	msgbox SE_Text_PrycePost, MSGBOX_DEFAULT
	release
	end

SE_Text_PryceIntro:
	.string "POKéMON have many experiences in\ntheir lives, just like we do.\pI, too, have seen and suffered\nmuch in my life.\pSince I am your elder, let me show\nyou what I mean.$"

SE_Text_PryceDefeat:
	.string "Ah, I am impressed by your prowess.\nYou have earned the GLACIERBADGE.$"

SE_Text_PrycePost:
	.string "When the ice and snow melt, spring\narrives.\pYou and your POKéMON will be\ntogether for many years to come.$"

SE_Text_ReceivedPryceBadge:
	.string "{PLAYER} received the GLACIERBADGE\nfrom PRYCE.$"

SE_EventScript_JohtoLeader_Clair::
	trainerbattle_single TRAINER_SE_LEADER_CLAIR, SE_Text_ClairIntro, SE_Text_ClairDefeat, SE_EventScript_ClairDefeated, NO_MUSIC
	goto_if_unset FLAG_SE_RECEIVED_JOHTO_TM8, SE_EventScript_ClairGiveTM
	msgbox SE_Text_ClairPost, MSGBOX_DEFAULT
	release
	end

SE_EventScript_ClairDefeated::
	message SE_Text_ReceivedClairBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_JOHTO_BADGE8_GET
	goto SE_EventScript_ClairGiveTM
	end

SE_EventScript_ClairGiveTM::
	giveitem ITEM_TM_DRAGON_CLAW
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SE_RECEIVED_JOHTO_TM8
	msgbox SE_Text_ClairPost, MSGBOX_DEFAULT
	release
	end

SE_Text_ClairIntro:
	.string "I am CLAIR.\pThe world's best dragon master.\pI can hold my own against even the\nPOKéMON LEAGUE's ELITE FOUR.\pDo you still want to take me on?\n…Fine. Let's do it!$"

SE_Text_ClairDefeat:
	.string "I lost?\pI don't believe it. There must be\nsome mistake… Fine. Take the\lRISINGBADGE.$"

SE_Text_ClairPost:
	.string "With all eight JOHTO badges, the\nPOKéMON LEAGUE awaits you.\pHead east of NEW BARK TOWN, through\nROUTE 27 and the TOHJO FALLS.$"

SE_Text_ReceivedClairBadge:
	.string "{PLAYER} received the RISINGBADGE\nfrom CLAIR.$"

@ ---------------------------------------------------------------------------
@ Pokemon League Reception Gate (Route 26 / Route 22 / Route 23 / Route 28)
SE_EventScript_ReceptionGateOnTransition::
	call SE_EventScript_UpdateKantoComplete
	call_if_set FLAG_SE_KANTO_COMPLETE, SE_EventScript_HideSilverGateGuard
	call_if_set FLAG_SE_JOHTO_LEAGUE_CLEARED, SE_EventScript_HideKantoGateGuard
	call SE_EventScript_CheckJohtoBadges
	call_if_eq VAR_RESULT, TRUE, SE_EventScript_ReceptionGateOpen
	end

SE_EventScript_ReceptionGateOpen::
	setvar VAR_TEMP_1, 1
	return

SE_EventScript_HideSilverGateGuard::
	setflag FLAG_SE_HIDE_SILVER_GATE_GUARD
	return

SE_EventScript_HideKantoGateGuard::
	setflag FLAG_SE_HIDE_KANTO_GATE_GUARD
	return

@ VAR_RESULT = TRUE if the player has all eight Johto badges
SE_EventScript_CheckJohtoBadges::
	setvar VAR_RESULT, FALSE
	goto_if_unset FLAG_JOHTO_BADGE1_GET, Common_EventScript_NopReturn
	goto_if_unset FLAG_JOHTO_BADGE2_GET, Common_EventScript_NopReturn
	goto_if_unset FLAG_JOHTO_BADGE3_GET, Common_EventScript_NopReturn
	goto_if_unset FLAG_JOHTO_BADGE4_GET, Common_EventScript_NopReturn
	goto_if_unset FLAG_JOHTO_BADGE5_GET, Common_EventScript_NopReturn
	goto_if_unset FLAG_JOHTO_BADGE6_GET, Common_EventScript_NopReturn
	goto_if_unset FLAG_JOHTO_BADGE7_GET, Common_EventScript_NopReturn
	goto_if_unset FLAG_JOHTO_BADGE8_GET, Common_EventScript_NopReturn
	setvar VAR_RESULT, TRUE
	return

@ Sets FLAG_SE_KANTO_COMPLETE once the player holds all eight Kanto badges
SE_EventScript_UpdateKantoComplete::
	goto_if_set FLAG_SE_KANTO_COMPLETE, Common_EventScript_NopReturn
	goto_if_unset FLAG_BADGE09_GET, Common_EventScript_NopReturn
	goto_if_unset FLAG_BADGE10_GET, Common_EventScript_NopReturn
	goto_if_unset FLAG_BADGE11_GET, Common_EventScript_NopReturn
	goto_if_unset FLAG_BADGE12_GET, Common_EventScript_NopReturn
	goto_if_unset FLAG_BADGE13_GET, Common_EventScript_NopReturn
	goto_if_unset FLAG_BADGE14_GET, Common_EventScript_NopReturn
	goto_if_unset FLAG_BADGE15_GET, Common_EventScript_NopReturn
	goto_if_unset FLAG_BADGE16_GET, Common_EventScript_NopReturn
	setflag FLAG_SE_KANTO_COMPLETE
	return

SE_EventScript_ReceptionGateBadgeCheck::
	lockall
	playse SE_PIN
	applymovement LOCALID_RECEPTIONGATE_OFFICER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RECEPTIONGATE_OFFICER, Common_Movement_WalkInPlaceFasterRight
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox SE_Text_ReceptionGateNotEnoughBadges, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, SE_Movement_WalkDown1
	waitmovement 0
	releaseall
	end

SE_EventScript_ReceptionGateOfficer::
	lock
	faceplayer
	call SE_EventScript_CheckJohtoBadges
	goto_if_eq VAR_RESULT, TRUE, SE_EventScript_ReceptionGateOfficerOK
	msgbox SE_Text_ReceptionGateNotEnoughBadges, MSGBOX_DEFAULT
	release
	end

SE_EventScript_ReceptionGateOfficerOK::
	msgbox SE_Text_ReceptionGateEightBadges, MSGBOX_DEFAULT
	release
	end

SE_EventScript_ReceptionGateSilverGuard::
	msgbox SE_Text_ReceptionGateSilverGuard, MSGBOX_NPC
	end

SE_EventScript_ReceptionGateKantoGuard::
	msgbox SE_Text_ReceptionGateKantoGuard, MSGBOX_NPC
	end

SE_Text_ReceptionGateNotEnoughBadges:
	.string "Only TRAINERS who have all eight\n"
	.string "JOHTO GYM BADGES may challenge\l"
	.string "the POKéMON LEAGUE.\p"
	.string "I'm sorry, but you can't go\n"
	.string "through yet.$"

SE_Text_ReceptionGateEightBadges:
	.string "You have all eight JOHTO BADGES!\p"
	.string "VICTORY ROAD lies ahead, past\n"
	.string "ROUTE 23. Good luck!$"

SE_Text_ReceptionGateSilverGuard:
	.string "MT. SILVER is home to very\n"
	.string "dangerous wild POKéMON.\p"
	.string "Only TRAINERS who have earned all\n"
	.string "eight KANTO GYM BADGES may enter.$"

SE_Text_ReceptionGateKantoGuard:
	.string "ROUTE 22 leads to VIRIDIAN CITY\n"
	.string "in KANTO.\p"
	.string "The way is only open to the\n"
	.string "CHAMPION of the POKéMON LEAGUE.$"

@ ---------------------------------------------------------------------------
@ Hall of Fame (hall_of_fame_frlg.inc): the first time is the Johto League, the second
@ (after all eight Kanto badges) is the stronger League rematch.
SE_EventScript_LeagueCleared::
	setflag FLAG_DAILY_SE_KANTO_LEAGUE
	call_if_set FLAG_SE_KANTO_COMPLETE, SE_EventScript_KantoLeagueCleared
	setflag FLAG_SE_JOHTO_LEAGUE_CLEARED
	setflag FLAG_SE_HIDE_KANTO_GATE_GUARD
	return

SE_EventScript_KantoLeagueCleared::
	setflag FLAG_SE_KANTO_CHAMPION
	setflag FLAG_HIDE_CERULEAN_CAVE_GUARD @ as in HGSS, Cerulean Cave opens after the rematch
	return

SE_EventScript_HallOfFameRespawn::
	goto_if_set FLAG_SE_KANTO_COMPLETE, SE_EventScript_HallOfFameRespawnKanto
	setrespawn HEAL_LOCATION_NEW_BARK_TOWN_HNS
	return

SE_EventScript_HallOfFameRespawnKanto::
	setrespawn HEAL_LOCATION_PALLET_TOWN
	return

@ ---------------------------------------------------------------------------
@ Red at the summit of Mt. Silver
SE_EventScript_MtSilverRed::
	lock
	faceplayer
	goto_if_defeated TRAINER_SE_RED, SE_EventScript_MtSilverRedDefeated
	msgbox SE_Text_MtSilverRedIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_SE_RED, SE_Text_MtSilverRedDefeat
	msgbox SE_Text_MtSilverRedIntro, MSGBOX_DEFAULT
	release
	end

SE_EventScript_MtSilverRedDefeated::
	msgbox SE_Text_MtSilverRedIntro, MSGBOX_DEFAULT
	release
	end

SE_Text_MtSilverRedIntro:
	.string "…\n"
	.string "…$"

SE_Text_MtSilverRedDefeat:
	.string "…$"

SE_Movement_WalkDown1:
	walk_down
	step_end

@ ---------------------------------------------------------------------------
@ Oro (Gold of New Bark), the Johto rival. He picks the starter strong against the
@ player's Johto starter (VAR_SE_JOHTO_STARTER: 1 Cyndaquil, 2 Totodile, 3 Chikorita).
@ VAR_SE_ORO_STATE: 1 after New Bark, 2 after Goldenrod, 3 after Victory Road.

SE_EventScript_OroNewBarkOnTransition::
	goto_if_ne VAR_SE_ORO_STATE, 0, SE_EventScript_OroHideNewBark
	clearflag FLAG_SE_HIDE_ORO_NEWBARK
	return

SE_EventScript_OroHideNewBark::
	setflag FLAG_SE_HIDE_ORO_NEWBARK
	return

SE_EventScript_OroNewBark::
	lock
	faceplayer
	playbgm MUS_HG_ENCOUNTER_RIVAL, FALSE
	msgbox SE_Text_OroNewBarkIntro, MSGBOX_DEFAULT
	goto_if_eq VAR_SE_JOHTO_STARTER, 2, SE_EventScript_OroNewBarkMeganium
	goto_if_eq VAR_SE_JOHTO_STARTER, 3, SE_EventScript_OroNewBarkTyphlosion
	trainerbattle_no_intro TRAINER_SE_ORO_1_FERALIGATR, SE_Text_OroNewBarkDefeat
	goto SE_EventScript_OroNewBarkWon

SE_EventScript_OroNewBarkMeganium::
	trainerbattle_no_intro TRAINER_SE_ORO_1_MEGANIUM, SE_Text_OroNewBarkDefeat
	goto SE_EventScript_OroNewBarkWon

SE_EventScript_OroNewBarkTyphlosion::
	trainerbattle_no_intro TRAINER_SE_ORO_1_TYPHLOSION, SE_Text_OroNewBarkDefeat
	goto SE_EventScript_OroNewBarkWon

SE_EventScript_OroNewBarkWon::
	msgbox SE_Text_OroNewBarkAfter, MSGBOX_DEFAULT
	closemessage
	setvar VAR_SE_ORO_STATE, 1
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_NEWBARK_SE_ORO
	setflag FLAG_SE_HIDE_ORO_NEWBARK
	fadescreen FADE_FROM_BLACK
	release
	end

SE_EventScript_OroGoldenrodOnTransition::
	goto_if_ne VAR_SE_ORO_STATE, 1, SE_EventScript_OroHideGoldenrod
	clearflag FLAG_SE_HIDE_ORO_GOLDENROD
	return

SE_EventScript_OroHideGoldenrod::
	setflag FLAG_SE_HIDE_ORO_GOLDENROD
	return

SE_EventScript_OroGoldenrod::
	lock
	faceplayer
	playbgm MUS_HG_ENCOUNTER_RIVAL, FALSE
	msgbox SE_Text_OroGoldenrodIntro, MSGBOX_DEFAULT
	goto_if_eq VAR_SE_JOHTO_STARTER, 2, SE_EventScript_OroGoldenrodMeganium
	goto_if_eq VAR_SE_JOHTO_STARTER, 3, SE_EventScript_OroGoldenrodTyphlosion
	trainerbattle_no_intro TRAINER_SE_ORO_2_FERALIGATR, SE_Text_OroGoldenrodDefeat
	goto SE_EventScript_OroGoldenrodWon

SE_EventScript_OroGoldenrodMeganium::
	trainerbattle_no_intro TRAINER_SE_ORO_2_MEGANIUM, SE_Text_OroGoldenrodDefeat
	goto SE_EventScript_OroGoldenrodWon

SE_EventScript_OroGoldenrodTyphlosion::
	trainerbattle_no_intro TRAINER_SE_ORO_2_TYPHLOSION, SE_Text_OroGoldenrodDefeat
	goto SE_EventScript_OroGoldenrodWon

SE_EventScript_OroGoldenrodWon::
	msgbox SE_Text_OroGoldenrodAfter, MSGBOX_DEFAULT
	closemessage
	setvar VAR_SE_ORO_STATE, 2
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_GOLDENROD_SE_ORO
	setflag FLAG_SE_HIDE_ORO_GOLDENROD
	fadescreen FADE_FROM_BLACK
	release
	end

SE_EventScript_OroVictoryRoadOnTransition::
	goto_if_ge VAR_SE_ORO_STATE, 3, SE_EventScript_OroHideVictoryRoad
	clearflag FLAG_SE_HIDE_ORO_VICTORY_ROAD
	return

SE_EventScript_OroHideVictoryRoad::
	setflag FLAG_SE_HIDE_ORO_VICTORY_ROAD
	return

SE_EventScript_OroVictoryRoad::
	lock
	faceplayer
	playbgm MUS_HG_ENCOUNTER_RIVAL, FALSE
	msgbox SE_Text_OroVictoryRoadIntro, MSGBOX_DEFAULT
	goto_if_eq VAR_SE_JOHTO_STARTER, 2, SE_EventScript_OroVictoryRoadMeganium
	goto_if_eq VAR_SE_JOHTO_STARTER, 3, SE_EventScript_OroVictoryRoadTyphlosion
	trainerbattle_no_intro TRAINER_SE_ORO_3_FERALIGATR, SE_Text_OroVictoryRoadDefeat
	goto SE_EventScript_OroVictoryRoadWon

SE_EventScript_OroVictoryRoadMeganium::
	trainerbattle_no_intro TRAINER_SE_ORO_3_MEGANIUM, SE_Text_OroVictoryRoadDefeat
	goto SE_EventScript_OroVictoryRoadWon

SE_EventScript_OroVictoryRoadTyphlosion::
	trainerbattle_no_intro TRAINER_SE_ORO_3_TYPHLOSION, SE_Text_OroVictoryRoadDefeat
	goto SE_EventScript_OroVictoryRoadWon

SE_EventScript_OroVictoryRoadWon::
	msgbox SE_Text_OroVictoryRoadAfter, MSGBOX_DEFAULT
	closemessage
	setvar VAR_SE_ORO_STATE, 3
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_ROUTE23_SE_ORO
	setflag FLAG_SE_HIDE_ORO_VICTORY_ROAD
	fadescreen FADE_FROM_BLACK
	release
	end

SE_Text_OroNewBarkIntro:
	.string "Hey! You're {PLAYER}, right?\p"
	.string "I'm ORO. I live here in\n"
	.string "NEW BARK TOWN.\p"
	.string "My mom says your family lived in\n"
	.string "OLIVINE before moving to HOENN.\p"
	.string "And now you're the HOENN CHAMPION?\n"
	.string "No way I'm letting that slide!\p"
	.string "I'm going to beat every JOHTO GYM\n"
	.string "before you do. But first…\p"
	.string "Let's see what a CHAMPION's got!$"

SE_Text_OroNewBarkDefeat:
	.string "Whoa… You're the real deal.$"

SE_Text_OroNewBarkAfter:
	.string "Okay, I lost this time.\p"
	.string "But JOHTO is my turf! I'll train\n"
	.string "harder than anyone and catch up.\p"
	.string "See you around, {PLAYER}!$"

SE_Text_OroGoldenrodIntro:
	.string "{PLAYER}! Fancy meeting you in\n"
	.string "GOLDENROD!\p"
	.string "I've been training non-stop since\n"
	.string "NEW BARK. My team is way stronger.\p"
	.string "This time, I'm winning!$"

SE_Text_OroGoldenrodDefeat:
	.string "Again?! Come on…$"

SE_Text_OroGoldenrodAfter:
	.string "You're tough, {PLAYER}.\p"
	.string "But I can feel it, I'm getting\n"
	.string "closer every time.\p"
	.string "I'll see you at the POKéMON\n"
	.string "LEAGUE. Don't you dare lose\l"
	.string "before then!$"

SE_Text_OroVictoryRoadIntro:
	.string "There you are, {PLAYER}!\p"
	.string "Past VICTORY ROAD is the POKéMON\n"
	.string "LEAGUE.\p"
	.string "I'm not going to let you through\n"
	.string "without one more battle.\p"
	.string "Everything I've got. Let's go!$"

SE_Text_OroVictoryRoadDefeat:
	.string "…That's it. You win.\n"
	.string "I mean it this time.$"

SE_Text_OroVictoryRoadAfter:
	.string "You and your POKéMON trust each\n"
	.string "other completely. I get it now.\p"
	.string "Go beat the ELITE FOUR and LANCE.\n"
	.string "Show them what HOENN's CHAMPION\l"
	.string "can do!\p"
	.string "I'll be cheering for you.$"

@ ---------------------------------------------------------------------------
@ Magnet Train: Goldenrod <-> Saffron, open once the Johto League is beaten
SE_EventScript_MagnetTrainGoldenrod::
	lock
	faceplayer
	checkitem ITEM_PASS
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_MagnetTrainClosed
	msgbox SE_Text_MagnetTrainToSaffron, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SE_EventScript_MagnetTrainNo
	msgbox SE_Text_MagnetTrainDepart, MSGBOX_DEFAULT
	closemessage
	playse SE_DOOR
	fadescreen FADE_TO_BLACK
	setvar VAR_SE_TRAIN_RIDE, 1
	warpsilent MAP_GOLDENROD_CITY_TRAIN_STATION_HNS, 12, 5
	waitstate
	release
	end

SE_EventScript_MagnetTrainSaffron::
	lock
	faceplayer
	checkitem ITEM_PASS
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_MagnetTrainClosed
	msgbox SE_Text_MagnetTrainToGoldenrod, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SE_EventScript_MagnetTrainNo
	msgbox SE_Text_MagnetTrainDepart, MSGBOX_DEFAULT
	closemessage
	playse SE_DOOR
	fadescreen FADE_TO_BLACK
	setvar VAR_SE_TRAIN_RIDE, 3
	warpsilent MAP_SAFFRON_CITY_MAGNET_TRAIN_STATION, 138, 5
	waitstate
	release
	end

SE_EventScript_SaffronStationNpc::
	msgbox SE_Text_SaffronStationNpc, MSGBOX_NPC
	end

SE_Text_SaffronStationNpc:
	.string "The MAGNET TRAIN links SAFFRON CITY\n"
	.string "and GOLDENROD CITY in no time!$"

SE_EventScript_MagnetTrainClosed::
	msgbox SE_Text_MagnetTrainClosed, MSGBOX_DEFAULT
	release
	end

SE_EventScript_MagnetTrainNo::
	msgbox SE_Text_MagnetTrainNo, MSGBOX_DEFAULT
	release
	end

SE_Text_MagnetTrainClosed:
	.string "Sorry, you can't board the\n"
	.string "MAGNET TRAIN without a PASS.$"

SE_Text_MagnetTrainToSaffron:
	.string "Welcome to the MAGNET TRAIN!\p"
	.string "Would you like to ride to\n"
	.string "SAFFRON CITY in KANTO?$"

SE_Text_MagnetTrainToGoldenrod:
	.string "I'm the MAGNET TRAIN clerk.\p"
	.string "Would you like to ride to\n"
	.string "GOLDENROD CITY in JOHTO?$"

SE_Text_MagnetTrainDepart:
	.string "All aboard!\n"
	.string "We hope you enjoy the trip.$"

SE_Text_MagnetTrainNo:
	.string "We hope to see you again.$"

SE_Text_MortyRainbowWing:
	.string "Eight JOHTO BADGES…\n"
	.string "So the legend was true.\p"
	.string "It is said that HO-OH appears\n"
	.string "before a TRAINER of true skill.\p"
	.string "My family has guarded this\n"
	.string "feather for generations.\p"
	.string "I believe it was meant for you.$"

SE_Text_MortyRainbowWingAfter:
	.string "Take the RAINBOW WING to the top\n"
	.string "of the TIN TOWER.\p"
	.string "HO-OH will be waiting for you.$"

SE_Text_JasmineSilverWing:
	.string "{PLAYER}… You collected all eight\n"
	.string "JOHTO BADGES. I'm so proud of you.\p"
	.string "Do you remember the stories we\n"
	.string "heard as kids, about the guardian\l"
	.string "of the seas?\p"
	.string "A sailor gave me this feather long\n"
	.string "ago. I kept it all this time.\p"
	.string "I want you to have it.$"

SE_Text_JasmineSilverWingAfter:
	.string "That's the SILVER WING.\p"
	.string "They say LUGIA sleeps deep inside\n"
	.string "the WHIRL ISLANDS…\p"
	.string "Maybe it will answer the feather's\n"
	.string "call.$"

@ ---------------------------------------------------------------------------
@ Johto legendaries: Lugia (Silver Wing, Whirl Islands), Ho-Oh (Rainbow Wing, Tin Tower),
@ Suicune (Tin Tower after the Burned Tower); Raikou and Entei roam Johto.

SE_EventScript_Lugia::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_LUGIA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_LAST_TALKED, LOCALID_LUGIA
	setwildbattle SPECIES_LUGIA, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SE_EventScript_LugiaDefeated
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SE_EventScript_LugiaRan
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SE_EventScript_LugiaRan
	setflag FLAG_SE_LUGIA_DONE
	release
	end

SE_EventScript_LugiaDefeated::
	setflag FLAG_SE_LUGIA_DONE
	goto Common_EventScript_RemoveStaticPokemon
	end

SE_EventScript_LugiaRan::
	setvar VAR_0x8004, SPECIES_LUGIA
	goto Common_EventScript_LegendaryFlewAway
	end

SE_EventScript_HoOh::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_HO_OH, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_LAST_TALKED, LOCALID_HO_OH
	setwildbattle SPECIES_HO_OH, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SE_EventScript_HoOhDefeated
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SE_EventScript_HoOhRan
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SE_EventScript_HoOhRan
	setflag FLAG_SE_HO_OH_DONE
	release
	end

SE_EventScript_HoOhDefeated::
	setflag FLAG_SE_HO_OH_DONE
	goto Common_EventScript_RemoveStaticPokemon
	end

SE_EventScript_HoOhRan::
	setvar VAR_0x8004, SPECIES_HO_OH
	goto Common_EventScript_LegendaryFlewAway
	end

SE_EventScript_Suicune::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SUICUNE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_LAST_TALKED, LOCALID_TINTOWER_SE_SUICUNE
	setwildbattle SPECIES_SUICUNE, 60
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SE_EventScript_SuicuneDefeated
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SE_EventScript_SuicuneRan
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SE_EventScript_SuicuneRan
	setflag FLAG_SE_SUICUNE_DONE
	release
	end

SE_EventScript_SuicuneDefeated::
	setflag FLAG_SE_SUICUNE_DONE
	goto Common_EventScript_RemoveStaticPokemon
	end

SE_EventScript_SuicuneRan::
	setvar VAR_0x8004, SPECIES_SUICUNE
	goto Common_EventScript_LegendaryFlewAway
	end

SE_EventScript_LugiaChamberOnTransition::
	setflag FLAG_J_HIDE_LUGIA
	setflag FLAG_HIDE_WHIRL_ISLANDS_KIMONO_GIRLS
	goto_if_set FLAG_SE_LUGIA_DONE, Common_EventScript_NopReturn
	checkitem ITEM_SILVER_WING
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_NopReturn
	clearflag FLAG_J_HIDE_LUGIA
	return

SE_EventScript_TinTowerRoofOnTransition::
	setflag FLAG_J_HIDE_HO_OH
	goto_if_set FLAG_SE_HO_OH_DONE, Common_EventScript_NopReturn
	checkitem ITEM_RAINBOW_WING
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_NopReturn
	clearflag FLAG_J_HIDE_HO_OH
	return

SE_EventScript_TinTower1FOnTransition::
	setflag FLAG_SE_HIDE_TIN_TOWER_SUICUNE
	goto_if_set FLAG_SE_SUICUNE_DONE, Common_EventScript_NopReturn
	goto_if_unset FLAG_SE_BEASTS_RELEASED, Common_EventScript_NopReturn
	clearflag FLAG_SE_HIDE_TIN_TOWER_SUICUNE
	return

SE_EventScript_BurnedTowerB1FOnTransition::
	setflag FLAG_HIDE_BURNED_TOWER_BEASTS
	goto_if_set FLAG_SE_BEASTS_RELEASED, SE_EventScript_BurnedTowerBeastsGone
	clearflag FLAG_HIDE_BURNED_TOWER_BEASTS
	return

SE_EventScript_BurnedTowerBeastsGone::
	setvar VAR_TEMP_1, 1
	return

SE_EventScript_BurnedTowerBeasts::
	lockall
	delay 20
	msgbox SE_Text_BurnedTowerBeastsAwake, MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_RAIKOU, CRY_MODE_ENCOUNTER
	waitmoncry
	removeobject LOCALID_BURNEDTOWER_RAIKOU
	delay 10
	playmoncry SPECIES_ENTEI, CRY_MODE_ENCOUNTER
	waitmoncry
	removeobject LOCALID_BURNEDTOWER_ENTEI
	delay 10
	playmoncry SPECIES_SUICUNE, CRY_MODE_ENCOUNTER
	waitmoncry
	removeobject LOCALID_BURNEDTOWER_SUICUNE
	delay 20
	msgbox SE_Text_BurnedTowerBeastsFled, MSGBOX_DEFAULT
	special StartJohtoBeasts
	setflag FLAG_SE_BEASTS_RELEASED
	setflag FLAG_HIDE_BURNED_TOWER_BEASTS
	setvar VAR_TEMP_1, 1
	releaseall
	end

SE_Text_BurnedTowerBeastsAwake:
	.string "Three POKéMON are resting in the\n"
	.string "basement of the BURNED TOWER…\p"
	.string "They noticed you!$"

SE_Text_BurnedTowerBeastsFled:
	.string "RAIKOU and ENTEI ran off across\n"
	.string "JOHTO!\p"
	.string "SUICUNE dashed away toward the\n"
	.string "TIN TOWER…$"


@ ---------------------------------------------------------------------------
@ Kurt (Azalea Town) turns berries into special Poke Balls, as in Heart & Soul:
@ Pecha->Love, Rawst->Lure, Cheri->Friend, Oran->Heavy, Chesto->Moon, Aspear->Fast, Persim->Level
SE_EventScript_Kurt::
	lock
	faceplayer
	msgbox KurtsHouse_Text_KurtAskYouHaveAnApricorn, MSGBOX_DEFAULT
	message SE_Text_KurtWhichBall
	waitmessage
	dynmultipush SE_Text_KurtLove, 0
	dynmultipush SE_Text_KurtLure, 1
	dynmultipush SE_Text_KurtFriend, 2
	dynmultipush SE_Text_KurtHeavy, 3
	dynmultipush SE_Text_KurtMoon, 4
	dynmultipush SE_Text_KurtFast, 5
	dynmultipush SE_Text_KurtLevel, 6
	dynmultistack 0, 0, FALSE, 7, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, 0, SE_EventScript_KurtLove
	goto_if_eq VAR_RESULT, 1, SE_EventScript_KurtLure
	goto_if_eq VAR_RESULT, 2, SE_EventScript_KurtFriend
	goto_if_eq VAR_RESULT, 3, SE_EventScript_KurtHeavy
	goto_if_eq VAR_RESULT, 4, SE_EventScript_KurtMoon
	goto_if_eq VAR_RESULT, 5, SE_EventScript_KurtFast
	goto_if_eq VAR_RESULT, 6, SE_EventScript_KurtLevel
	goto SE_EventScript_KurtCancel
	end

SE_EventScript_KurtLove::
	setvar VAR_0x8004, ITEM_PECHA_BERRY
	setvar VAR_0x8005, ITEM_LOVE_BALL
	goto SE_EventScript_KurtMake

SE_EventScript_KurtLure::
	setvar VAR_0x8004, ITEM_RAWST_BERRY
	setvar VAR_0x8005, ITEM_LURE_BALL
	goto SE_EventScript_KurtMake

SE_EventScript_KurtFriend::
	setvar VAR_0x8004, ITEM_CHERI_BERRY
	setvar VAR_0x8005, ITEM_FRIEND_BALL
	goto SE_EventScript_KurtMake

SE_EventScript_KurtHeavy::
	setvar VAR_0x8004, ITEM_ORAN_BERRY
	setvar VAR_0x8005, ITEM_HEAVY_BALL
	goto SE_EventScript_KurtMake

SE_EventScript_KurtMoon::
	setvar VAR_0x8004, ITEM_CHESTO_BERRY
	setvar VAR_0x8005, ITEM_MOON_BALL
	goto SE_EventScript_KurtMake

SE_EventScript_KurtFast::
	setvar VAR_0x8004, ITEM_ASPEAR_BERRY
	setvar VAR_0x8005, ITEM_FAST_BALL
	goto SE_EventScript_KurtMake

SE_EventScript_KurtLevel::
	setvar VAR_0x8004, ITEM_PERSIM_BERRY
	setvar VAR_0x8005, ITEM_LEVEL_BALL
	goto SE_EventScript_KurtMake

SE_EventScript_KurtMake::
	bufferitemname STR_VAR_1, VAR_0x8004
	bufferitemname STR_VAR_2, VAR_0x8005
	special SE_KurtMakeBalls
	goto_if_eq VAR_RESULT, 0, SE_EventScript_KurtNoBerries
	buffernumberstring STR_VAR_3, VAR_RESULT
	closemessage
	playse SE_BANG
	delay 30
	playse SE_BANG
	delay 30
	message SE_Text_KurtMadeBalls
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	msgbox SE_Text_KurtTurnedOutGreat, MSGBOX_DEFAULT
	release
	end

SE_EventScript_KurtNoBerries::
	msgbox SE_Text_KurtNoBerries, MSGBOX_DEFAULT
	release
	end

SE_EventScript_KurtCancel::
	msgbox SE_Text_KurtCancel, MSGBOX_DEFAULT
	release
	end

SE_Text_KurtWhichBall:
	.string "Which BALL do you want?$"

SE_Text_KurtNoBerries:
	.string "KURT: You don't have any\n"
	.string "{STR_VAR_1} for the {STR_VAR_2}!\p"
	.string "Bring me some and I'll get to work.$"

SE_Text_KurtCancel:
	.string "KURT: Come back if you find\n"
	.string "some good BERRIES.$"

SE_Text_KurtMadeBalls:
	.string "KURT made {STR_VAR_3} {STR_VAR_2}(S)\n"
	.string "from your {STR_VAR_1}!$"

SE_Text_KurtTurnedOutGreat:
	.string "KURT: They turned out great!\n"
	.string "Try catching POKéMON with them.$"

SE_Text_KurtLove:
	.string "LOVE BALL$"

SE_Text_KurtLure:
	.string "LURE BALL$"

SE_Text_KurtFriend:
	.string "FRIEND BALL$"

SE_Text_KurtHeavy:
	.string "HEAVY BALL$"

SE_Text_KurtMoon:
	.string "MOON BALL$"

SE_Text_KurtFast:
	.string "FAST BALL$"

SE_Text_KurtLevel:
	.string "LEVEL BALL$"

@ ---------------------------------------------------------------------------
@ Headbutt trees (Johto): a POKéMON that knows HEADBUTT shakes the tree; wild
@ POKéMON come from the map's rock smash table, as in Heart & Soul.
SE_EventScript_Headbutt::
	lockall
	special SE_CheckPartyHeadbutt
	goto_if_eq VAR_RESULT, PARTY_SIZE, SE_EventScript_HeadbuttNoMon
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	msgbox SE_Text_HeadbuttAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SE_EventScript_HeadbuttEnd
	msgbox SE_Text_HeadbuttUsed, MSGBOX_DEFAULT
	closemessage
	playse SE_M_HEADBUTT
	waitse
	special RockSmashWildEncounter
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_HeadbuttNothing
	waitstate
	releaseall
	end

SE_EventScript_HeadbuttNothing::
	msgbox SE_Text_HeadbuttNothing, MSGBOX_DEFAULT
SE_EventScript_HeadbuttEnd::
	releaseall
	end

SE_EventScript_HeadbuttNoMon::
	msgbox SE_Text_HeadbuttNoMon, MSGBOX_DEFAULT
	releaseall
	end

SE_Text_HeadbuttAsk:
	.string "A POKéMON could be in this tree.\n"
	.string "Want {STR_VAR_1} to use HEADBUTT?$"

SE_Text_HeadbuttUsed:
	.string "{STR_VAR_1} used HEADBUTT!$"

SE_Text_HeadbuttNothing:
	.string "Nope. Nothing…$"

SE_Text_HeadbuttNoMon:
	.string "A POKéMON could be in this tree.\n"
	.string "A POKéMON that knows HEADBUTT\l"
	.string "could shake it.$"

Common_Movement_WalkUp1::
	walk_up
	step_end

Common_Movement_WalkLeft1::
	walk_left
	step_end

@ ---------------------------------------------------------------------------
@ Goldenrod Dept. Store elevator (Heart & Soul). The player walks in from the
@ tile below the elevator door; the door is two tiles north of that tile.
SE_GoldenrodElevator_OnFrame::
	map_script_2 VAR_SE_ELEVATOR, 1, SE_GoldenrodElevator_EventScript_Exit
	.2byte 0

SE_GoldenrodElevator_EventScript_Exit::
	lockall
	getplayerxy VAR_0x8004, VAR_0x8005
	addvar VAR_0x8005, 1
	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim
	applymovement OBJ_EVENT_ID_PLAYER, SE_GoldenrodElevator_Movement_Out
	waitmovement 0
	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim
	setvar VAR_SE_ELEVATOR, 0
	releaseall
	end

SE_GoldenrodElevator_EventScript_Enter::
	lockall
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	delay 8
	getplayerxy VAR_0x8004, VAR_0x8005
	subvar VAR_0x8005, 1
	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim
	applymovement OBJ_EVENT_ID_PLAYER, SE_GoldenrodElevator_Movement_In
	waitmovement 0
	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim
	message SE_GoldenrodElevator_Text_WhichFloor
	waitmessage
	dynmultipush SE_GoldenrodElevator_Text_6F, 0
	dynmultipush SE_GoldenrodElevator_Text_5F, 1
	dynmultipush SE_GoldenrodElevator_Text_4F, 2
	dynmultipush SE_GoldenrodElevator_Text_3F, 3
	dynmultipush SE_GoldenrodElevator_Text_2F, 4
	dynmultipush SE_GoldenrodElevator_Text_1F, 5
	dynmultipush SE_GoldenrodElevator_Text_B1F, 6
	dynmultistack 0, 0, FALSE, 7, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	closemessage
	switch VAR_RESULT
	case 0, SE_GoldenrodElevator_EventScript_6F
	case 1, SE_GoldenrodElevator_EventScript_5F
	case 2, SE_GoldenrodElevator_EventScript_4F
	case 3, SE_GoldenrodElevator_EventScript_3F
	case 4, SE_GoldenrodElevator_EventScript_2F
	case 5, SE_GoldenrodElevator_EventScript_1F
	case 6, SE_GoldenrodElevator_EventScript_B1F
	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim
	applymovement OBJ_EVENT_ID_PLAYER, SE_GoldenrodElevator_Movement_Out
	waitmovement 0
	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim
	releaseall
	end

SE_GoldenrodElevator_EventScript_Ride::
	setvar VAR_SE_ELEVATOR, 1
	playse SE_ELEVATOR
	waitse
	fadescreen FADE_TO_BLACK
	return

SE_GoldenrodElevator_EventScript_6F::
	call SE_GoldenrodElevator_EventScript_Ride
	warp MAP_GOLDENROD_CITY_DEPARTMENT_STORE_6F_HNS, 9, 3
	waitstate
	end

SE_GoldenrodElevator_EventScript_5F::
	call SE_GoldenrodElevator_EventScript_Ride
	warp MAP_GOLDENROD_CITY_DEPARTMENT_STORE_5F_HNS, 9, 3
	waitstate
	end

SE_GoldenrodElevator_EventScript_4F::
	call SE_GoldenrodElevator_EventScript_Ride
	warp MAP_GOLDENROD_CITY_DEPARTMENT_STORE_4F_HNS, 9, 3
	waitstate
	end

SE_GoldenrodElevator_EventScript_3F::
	call SE_GoldenrodElevator_EventScript_Ride
	warp MAP_GOLDENROD_CITY_DEPARTMENT_STORE_3F_HNS, 9, 3
	waitstate
	end

SE_GoldenrodElevator_EventScript_2F::
	call SE_GoldenrodElevator_EventScript_Ride
	warp MAP_GOLDENROD_CITY_DEPARTMENT_STORE_2F_HNS, 9, 3
	waitstate
	end

SE_GoldenrodElevator_EventScript_1F::
	call SE_GoldenrodElevator_EventScript_Ride
	warp MAP_GOLDENROD_CITY_DEPARTMENT_STORE_1F_HNS, 9, 3
	waitstate
	end

SE_GoldenrodElevator_EventScript_B1F::
	call SE_GoldenrodElevator_EventScript_Ride
	warp MAP_GOLDENROD_CITY_DEPARTMENT_STORE_BASEMENT_HNS, 10, 5
	waitstate
	end

SE_GoldenrodElevator_Movement_In:
	walk_up
	walk_up
	step_end

SE_GoldenrodElevator_Movement_Out:
	walk_down
	walk_down
	step_end

SE_GoldenrodElevator_Text_WhichFloor:
	.string "Which floor?$"
SE_GoldenrodElevator_Text_6F:
	.string "6F$"
SE_GoldenrodElevator_Text_5F:
	.string "5F$"
SE_GoldenrodElevator_Text_4F:
	.string "4F$"
SE_GoldenrodElevator_Text_3F:
	.string "3F$"
SE_GoldenrodElevator_Text_2F:
	.string "2F$"
SE_GoldenrodElevator_Text_1F:
	.string "1F$"
SE_GoldenrodElevator_Text_B1F:
	.string "B1F$"

SE_Movement_JumpUp1:
	jump_up
	step_end

SE_Movement_JumpDown1:
	jump_down
	step_end

SE_EventScript_RadioTowerDirector::
	msgbox SE_Text_RadioTowerDirector, MSGBOX_NPC
	end

SE_Text_RadioTowerDirector:
	.string "I'm the DIRECTOR of the RADIO TOWER.\p"
	.string "Our programs reach every corner of\n"
	.string "JOHTO and KANTO.\p"
	.string "Busy days, but I wouldn't have it\n"
	.string "any other way!$"

@ Super Emerald: NPCs that had nothing to say
SE_EventScript_StationEngineer::
	msgbox SE_EventScript_StationEngineer_Text, MSGBOX_NPC
	end

SE_EventScript_StationEngineer_Text:
	.string "I keep the MAGNET TRAIN running.\n"
	.string "It links GOLDENROD and SAFFRON!$"

SE_EventScript_StationBlackBelt::
	msgbox SE_EventScript_StationBlackBelt_Text, MSGBOX_NPC
	end

SE_EventScript_StationBlackBelt_Text:
	.string "I train in SAFFRON every weekend.\p"
	.string "The MAGNET TRAIN gets me there\n"
	.string "in no time.$"

SE_EventScript_StationWoman::
	msgbox SE_EventScript_StationWoman_Text, MSGBOX_NPC
	end

SE_EventScript_StationWoman_Text:
	.string "I'm going shopping in KANTO.\n"
	.string "I hear SAFFRON has huge stores!$"

SE_EventScript_StationOldWoman::
	msgbox SE_EventScript_StationOldWoman_Text, MSGBOX_NPC
	end

SE_EventScript_StationOldWoman_Text:
	.string "In my day, going to KANTO took\n"
	.string "several days on foot!$"

SE_EventScript_OlivineWoman::
	msgbox SE_EventScript_OlivineWoman_Text, MSGBOX_NPC
	end

SE_EventScript_OlivineWoman_Text:
	.string "Ships from all over the world stop\n"
	.string "at OLIVINE's port.$"

SE_EventScript_Route38TwinA::
	msgbox SE_EventScript_Route38TwinA_Text, MSGBOX_NPC
	end

SE_EventScript_Route38TwinA_Text:
	.string "We love the cows at MOOMOO FARM!$"

SE_EventScript_Route38TwinB::
	msgbox SE_EventScript_Route38TwinB_Text, MSGBOX_NPC
	end

SE_EventScript_Route38TwinB_Text:
	.string "The MILTANK milk here is the\n"
	.string "best in JOHTO!$"

SE_EventScript_SafariIndoorAttendant::
	msgbox SE_EventScript_SafariIndoorAttendant_Text, MSGBOX_NPC
	end

SE_EventScript_SafariIndoorAttendant_Text:
	.string "This is a rest house for visitors\n"
	.string "of the SAFARI ZONE.\p"
	.string "Take your time!$"

SE_EventScript_SafariIndoorWorker::
	msgbox SE_EventScript_SafariIndoorWorker_Text, MSGBOX_NPC
	end

SE_EventScript_SafariIndoorWorker_Text:
	.string "We're always working to make the\n"
	.string "SAFARI ZONE better for POKéMON.$"

@ ---------------------------------------------------------------------------
@ Johto Gym Leader rematches (stronger teams), after beating Red
SE_EventScript_FalknerRematch::
	lock
	faceplayer
	goto_if_unset FLAG_SE_RECEIVED_JOHTO_TM1, SE_EventScript_FalknerGiveTM
	msgbox SE_Text_FalknerRematch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SFR_EventScript_KantoRematchDecline
	cleartrainerflag TRAINER_SE_LEADER_FALKNER_REMATCH
	trainerbattle_no_intro TRAINER_SE_LEADER_FALKNER_REMATCH, SE_Text_FalknerRematchDefeat
	msgbox SFR_Text_KantoRematchAfter, MSGBOX_DEFAULT
	release
	end

SE_Text_FalknerRematch:
	.string "FALKNER: My birds and I have been\nsoaring higher than ever!\pWill you face my new team?$"

SE_Text_FalknerRematchDefeat:
	.string "My birds… still not enough.$"

SE_EventScript_BugsyRematch::
	lock
	faceplayer
	goto_if_unset FLAG_SE_RECEIVED_JOHTO_TM2, SE_EventScript_BugsyGiveTM
	msgbox SE_Text_BugsyRematch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SFR_EventScript_KantoRematchDecline
	cleartrainerflag TRAINER_SE_LEADER_BUGSY_REMATCH
	trainerbattle_no_intro TRAINER_SE_LEADER_BUGSY_REMATCH, SE_Text_BugsyRematchDefeat
	msgbox SFR_Text_KantoRematchAfter, MSGBOX_DEFAULT
	release
	end

SE_Text_BugsyRematch:
	.string "BUGSY: I've studied bug POKéMON\neven more since our battle.\pWant to see my research in action?$"

SE_Text_BugsyRematchDefeat:
	.string "Your team is amazing!\nI have to study more.$"

SE_EventScript_WhitneyRematch::
	lock
	faceplayer
	goto_if_unset FLAG_SE_RECEIVED_JOHTO_TM3, SE_EventScript_WhitneyGiveTM
	msgbox SE_Text_WhitneyRematch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SFR_EventScript_KantoRematchDecline
	cleartrainerflag TRAINER_SE_LEADER_WHITNEY_REMATCH
	trainerbattle_no_intro TRAINER_SE_LEADER_WHITNEY_REMATCH, SE_Text_WhitneyRematchDefeat
	msgbox SFR_Text_KantoRematchAfter, MSGBOX_DEFAULT
	release
	end

SE_Text_WhitneyRematch:
	.string "WHITNEY: I'm not gonna cry this\ntime! My team's way tougher now!\pBattle me again?$"

SE_Text_WhitneyRematchDefeat:
	.string "Waaah! …No, no, I'm not crying!\nThat was fun!$"

SE_EventScript_MortyRematch::
	lock
	faceplayer
	goto_if_unset FLAG_SE_RECEIVED_JOHTO_TM4, SE_EventScript_MortyGiveTM
	msgbox SE_Text_MortyRematch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SFR_EventScript_KantoRematchDecline
	cleartrainerflag TRAINER_SE_LEADER_MORTY_REMATCH
	trainerbattle_no_intro TRAINER_SE_LEADER_MORTY_REMATCH, SE_Text_MortyRematchDefeat
	msgbox SFR_Text_KantoRematchAfter, MSGBOX_DEFAULT
	release
	end

SE_Text_MortyRematch:
	.string "MORTY: I have seen a new future\nin my training.\pWill you battle me once more?$"

SE_Text_MortyRematchDefeat:
	.string "I still couldn't see past you.$"

SE_EventScript_ChuckRematch::
	lock
	faceplayer
	goto_if_unset FLAG_SE_RECEIVED_JOHTO_TM5, SE_EventScript_ChuckGiveTM
	msgbox SE_Text_ChuckRematch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SFR_EventScript_KantoRematchDecline
	cleartrainerflag TRAINER_SE_LEADER_CHUCK_REMATCH
	trainerbattle_no_intro TRAINER_SE_LEADER_CHUCK_REMATCH, SE_Text_ChuckRematchDefeat
	msgbox SFR_Text_KantoRematchAfter, MSGBOX_DEFAULT
	release
	end

SE_Text_ChuckRematch:
	.string "CHUCK: WAHAHAH! I've been training\nunder the waterfall day and night!\pFight me again!$"

SE_Text_ChuckRematchDefeat:
	.string "Hoo! You're stronger than a\nwaterfall!$"

SE_EventScript_JasmineRematch::
	lock
	faceplayer
	goto_if_unset FLAG_SE_RECEIVED_JOHTO_TM6, SE_EventScript_JasmineGiveTM
	msgbox SE_Text_JasmineRematch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SFR_EventScript_KantoRematchDecline
	cleartrainerflag TRAINER_SE_LEADER_JASMINE_REMATCH
	trainerbattle_no_intro TRAINER_SE_LEADER_JASMINE_REMATCH, SE_Text_JasmineRematchDefeat
	msgbox SFR_Text_KantoRematchAfter, MSGBOX_DEFAULT
	release
	end

SE_Text_JasmineRematch:
	.string "JASMINE: I… I've grown stronger\ntoo, like steel.\pWould you battle me again?$"

SE_Text_JasmineRematchDefeat:
	.string "You are truly strong…$"

SE_EventScript_PryceRematch::
	lock
	faceplayer
	goto_if_unset FLAG_SE_RECEIVED_JOHTO_TM7, SE_EventScript_PryceGiveTM
	msgbox SE_Text_PryceRematch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SFR_EventScript_KantoRematchDecline
	cleartrainerflag TRAINER_SE_LEADER_PRYCE_REMATCH
	trainerbattle_no_intro TRAINER_SE_LEADER_PRYCE_REMATCH, SE_Text_PryceRematchDefeat
	msgbox SFR_Text_KantoRematchAfter, MSGBOX_DEFAULT
	release
	end

SE_Text_PryceRematch:
	.string "PRYCE: Even an old man keeps\nlearning. My ice is colder now.\pWill you battle me?$"

SE_Text_PryceRematchDefeat:
	.string "Your fire melted my ice again.$"

SE_EventScript_ClairRematch::
	lock
	faceplayer
	goto_if_unset FLAG_SE_RECEIVED_JOHTO_TM8, SE_EventScript_ClairGiveTM
	msgbox SE_Text_ClairRematch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SFR_EventScript_KantoRematchDecline
	cleartrainerflag TRAINER_SE_LEADER_CLAIR_REMATCH
	trainerbattle_no_intro TRAINER_SE_LEADER_CLAIR_REMATCH, SE_Text_ClairRematchDefeat
	msgbox SFR_Text_KantoRematchAfter, MSGBOX_DEFAULT
	release
	end

SE_Text_ClairRematch:
	.string "CLAIR: I won't lose to you again!\nMy dragons have grown even mightier!\pAccept my challenge!$"

SE_Text_ClairRematchDefeat:
	.string "…I admit it. You're the stronger\nTRAINER.$"


@ ---------------------------------------------------------------------------
@ Johto Safari Zone (west of Cianwood): Safari Game, 500 steps and 30 Safari Balls
SE_JohtoSafari_OnFrame::
	map_script_2 VAR_SAFARI_WARP_STATE, SAFARI_WARP_MANUAL_EXIT, SE_JohtoSafari_EventScript_ExitEarly
	map_script_2 VAR_SAFARI_WARP_STATE, SAFARI_WARP_NO_BALLS, SE_JohtoSafari_EventScript_GameOver
	map_script_2 VAR_SAFARI_WARP_STATE, SAFARI_WARP_NO_STEPS, SE_JohtoSafari_EventScript_GameOver
	map_script_2 VAR_SAFARI_WARP_STATE, SAFARI_WARP_NO_BALLS_MID_BATTLE, SE_JohtoSafari_EventScript_GameOver
	map_script_2 VAR_SAFARI_WARP_STATE, SAFARI_WARP_RETIRING, SE_JohtoSafari_EventScript_GameOver
	map_script_2 VAR_SAFARI_WARP_STATE, SAFARI_WARP_WHITEOUT, SE_JohtoSafari_EventScript_GameOver
	.2byte 0

SE_JohtoSafari_EventScript_GameOver::
	lockall
	msgbox SE_JohtoSafari_Text_GameOver, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, SE_JohtoSafari_Movement_Exit
	waitmovement 0
	setvar VAR_SAFARI_WARP_STATE, 0
	releaseall
	end

SE_JohtoSafari_EventScript_ExitEarly::
	lockall
	msgbox SE_JohtoSafari_Text_LeaveEarly, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SE_JohtoSafari_EventScript_ReturnToZone
	msgbox SE_JohtoSafari_Text_ReturnBalls, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, SE_JohtoSafari_Movement_Exit
	waitmovement 0
	safari_exitnowarp
	setvar VAR_SAFARI_WARP_STATE, 0
	releaseall
	end

SE_JohtoSafari_EventScript_ReturnToZone::
	closemessage
	warp MAP_SAFARI_ZONE_ENTERANCE_HNS, 0
	waitstate
	end

SE_JohtoSafari_EventScript_Counter::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	showmoneybox 0, 0
	msgbox SE_JohtoSafari_Text_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SE_JohtoSafari_EventScript_Back
	getpartysize
	goto_if_ne VAR_RESULT, PARTY_SIZE, SE_JohtoSafari_EventScript_Room
	specialvar VAR_RESULT, ScriptCheckFreePokemonStorageSpace
	goto_if_eq VAR_RESULT, TRUE, SE_JohtoSafari_EventScript_Room
	msgbox SE_JohtoSafari_Text_Full, MSGBOX_DEFAULT
	goto SE_JohtoSafari_EventScript_Back

SE_JohtoSafari_EventScript_Room::
	checkmoney 500
	goto_if_eq VAR_RESULT, FALSE, SE_JohtoSafari_EventScript_NoMoney
	playse SE_SHOP
	removemoney 500
	updatemoneybox
	msgbox SE_JohtoSafari_Text_Pay, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message SE_JohtoSafari_Text_Balls
	waitfanfare
	msgbox SE_JohtoSafari_Text_Enjoy, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	applymovement OBJ_EVENT_ID_PLAYER, SE_JohtoSafari_Movement_Enter
	waitmovement 0
	safari_enter SAFARI_EVENT_JOHTO
	warp MAP_SAFARI_ZONE_ENTERANCE_HNS, 0
	waitstate
	end

SE_JohtoSafari_EventScript_NoMoney::
	msgbox SE_JohtoSafari_Text_NoMoney, MSGBOX_DEFAULT
SE_JohtoSafari_EventScript_Back::
	closemessage
	hidemoneybox
	applymovement OBJ_EVENT_ID_PLAYER, SE_JohtoSafari_Movement_Back
	waitmovement 0
	releaseall
	end

SE_JohtoSafari_Movement_Back:
	walk_down
	step_end

SE_JohtoSafari_Movement_Enter:
	walk_up
	step_end

SE_JohtoSafari_Movement_Exit:
	walk_down
	walk_down
	step_end

SE_JohtoSafari_Text_Ask:
	.string "Welcome to the SAFARI ZONE!\p"
	.string "Would you like to play the Safari\n"
	.string "Game? It costs ¥500.$"

SE_JohtoSafari_Text_Pay:
	.string "That will be ¥500, please.\p"
	.string "Here are your SAFARI BALLS.$"

SE_JohtoSafari_Text_Balls:
	.string "{PLAYER} received 30 SAFARI BALLS.$"

SE_JohtoSafari_Text_Enjoy:
	.string "You have 500 steps. Please enjoy\n"
	.string "the SAFARI ZONE!$"

SE_JohtoSafari_Text_Full:
	.string "Your PC boxes are full. Please make\n"
	.string "some room before you play.$"

SE_JohtoSafari_Text_NoMoney:
	.string "I'm sorry, but you don't have\n"
	.string "enough money.$"

SE_JohtoSafari_Text_GameOver:
	.string "Your Safari Game is over.\n"
	.string "Please come again!$"

SE_JohtoSafari_Text_LeaveEarly:
	.string "Are you going to leave the\n"
	.string "SAFARI ZONE early?$"

SE_JohtoSafari_Text_ReturnBalls:
	.string "Please return any SAFARI BALLS\n"
	.string "you have left.$"

@ ---------------------------------------------------------------------------
@ The League rematches can be done once a day
SE_EventScript_IndigoLeagueDoor::
	goto_if_unset FLAG_SE_KANTO_CHAMPION, SE_EventScript_LeagueDoorOpen
	goto_if_unset FLAG_DAILY_SE_KANTO_LEAGUE, SE_EventScript_LeagueDoorOpen
	goto SE_EventScript_LeagueDoorClosed

SE_EventScript_SinnohLeagueDoor::
	goto_if_unset FLAG_SE_SINNOH_LEAGUE_CLEARED, SE_EventScript_LeagueDoorOpen
	goto_if_unset FLAG_DAILY_SE_SINNOH_LEAGUE, SE_EventScript_LeagueDoorOpen
SE_EventScript_LeagueDoorClosed::
	lockall
	msgbox SE_Text_LeagueClosedToday, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown
	waitmovement 0
	releaseall
SE_EventScript_LeagueDoorOpen::
	end

SE_Text_LeagueClosedToday:
	.string "The ELITE FOUR have already faced a\n"
	.string "challenger today.\p"
	.string "Please come back tomorrow!$"

@ ---------------------------------------------------------------------------
@ Magnet Train ride on the track outside the stations (VAR_SE_TRAIN_RIDE: 1 leave Goldenrod,
@ 2 reach Saffron, 3 leave Saffron, 4 reach Goldenrod). The train is two cars, the hidden
@ player rides between them so the camera shows the whole train, and the screen fades
@ while it is moving; SE_DoTrainRideWarp starts the arrival while the next map fades in.
SE_GoldenrodStation_OnTransition:
	call_if_ne VAR_SE_TRAIN_RIDE, 4, SE_EventScript_HideArrivingTrain
	call_if_eq VAR_SE_TRAIN_RIDE, 4, SE_EventScript_HideParkedTrain
	call_if_eq VAR_SE_TRAIN_RIDE, 1, SE_EventScript_TrainRideMusic
	end

SE_SaffronStation_OnTransition:
	call_if_ne VAR_SE_TRAIN_RIDE, 2, SE_EventScript_HideArrivingTrain
	call_if_eq VAR_SE_TRAIN_RIDE, 2, SE_EventScript_HideParkedTrain
	call_if_eq VAR_SE_TRAIN_RIDE, 3, SE_EventScript_TrainRideMusic
	end

SE_EventScript_HideArrivingTrain::
	setflag FLAG_TEMP_12
	return

SE_EventScript_HideParkedTrain::
	setflag FLAG_TEMP_11
	return

SE_EventScript_TrainRideMusic::
	playbgm MUS_HG_MAGNET_TRAIN, FALSE
	return

SE_GoldenrodStation_OnWarpInto:
	map_script_2 VAR_SE_TRAIN_RIDE, 1, SE_EventScript_TrainHidePlayer
	map_script_2 VAR_SE_TRAIN_RIDE, 4, SE_EventScript_TrainHidePlayer
	.2byte 0

SE_SaffronStation_OnWarpInto:
	map_script_2 VAR_SE_TRAIN_RIDE, 2, SE_EventScript_TrainHidePlayer
	map_script_2 VAR_SE_TRAIN_RIDE, 3, SE_EventScript_TrainHidePlayer
	.2byte 0

SE_EventScript_TrainHidePlayer::
	hideplayer
	end

SE_GoldenrodStation_OnFrame:
	map_script_2 VAR_SE_TRAIN_RIDE, 1, SE_EventScript_TrainLeaveGoldenrod
	.2byte 0

SE_SaffronStation_OnFrame:
	map_script_2 VAR_SE_TRAIN_RIDE, 3, SE_EventScript_TrainLeaveSaffron
	.2byte 0

SE_EventScript_TrainLeaveGoldenrod::
	lockall
	hidefollower
	hideplayer
	delay 30
	applymovement LOCALID_GOLDENROD_TRAIN_REAR, SE_Movement_TrainRight
	applymovement LOCALID_GOLDENROD_CITY_TRAIN_STATION_TRAIN, SE_Movement_TrainRight
	applymovement LOCALID_PLAYER, SE_Movement_TrainRight
	delay 150
	fadescreenspeed FADE_TO_BLACK, 1
	setvar VAR_SE_TRAIN_RIDE, 2
	setwarp MAP_SAFFRON_CITY_MAGNET_TRAIN_STATION, 110, 5
	special SE_DoTrainRideWarp
	waitstate
	releaseall
	end

SE_EventScript_TrainReachSaffron::
	lockall
	hidefollower
	hideplayer
	applymovement LOCALID_SAFFRON_TRAIN_ARRIVING_REAR, SE_Movement_TrainRightStop
	applymovement LOCALID_SAFFRON_TRAIN_ARRIVING, SE_Movement_TrainRightStop
	applymovement LOCALID_PLAYER, SE_Movement_TrainRightStop
	waitmovement 0
	playse SE_TRUCK_STOP
	delay 40
	setvar VAR_SE_TRAIN_RIDE, 0
	fadescreen FADE_TO_BLACK
	warp MAP_SAFFRON_CITY_MAGNET_TRAIN_STATION, 137, 21
	waitstate
	releaseall
	end

SE_EventScript_TrainLeaveSaffron::
	lockall
	hidefollower
	hideplayer
	delay 30
	applymovement LOCALID_SAFFRON_TRAIN_REAR, SE_Movement_TrainLeft
	applymovement LOCALID_SAFFRON_TRAIN, SE_Movement_TrainLeft
	applymovement LOCALID_PLAYER, SE_Movement_TrainLeft
	delay 150
	fadescreenspeed FADE_TO_BLACK, 1
	setvar VAR_SE_TRAIN_RIDE, 4
	setwarp MAP_GOLDENROD_CITY_TRAIN_STATION_HNS, 45, 5
	special SE_DoTrainRideWarp
	waitstate
	releaseall
	end

SE_EventScript_TrainReachGoldenrod::
	lockall
	hidefollower
	hideplayer
	applymovement LOCALID_GOLDENROD_TRAIN_ARRIVING_REAR, SE_Movement_TrainLeftStop
	applymovement LOCALID_GOLDENROD_TRAIN_ARRIVING, SE_Movement_TrainLeftStop
	applymovement LOCALID_PLAYER, SE_Movement_TrainLeftStop
	waitmovement 0
	playse SE_TRUCK_STOP
	delay 40
	setvar VAR_SE_TRAIN_RIDE, 0
	fadescreen FADE_TO_BLACK
	warp MAP_GOLDENROD_CITY_TRAIN_STATION_HNS, 16, 21
	waitstate
	releaseall
	end

SE_Movement_TrainRight:
	walk_slow_right
	walk_right
	walk_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	.rept 60
	walk_faster_right
	.endr
	step_end

SE_Movement_TrainRightStop:
	.rept 20
	walk_faster_right
	.endr
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_right
	walk_right
	walk_slow_right
	step_end

SE_Movement_TrainLeft:
	walk_slow_left
	walk_left
	walk_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	.rept 60
	walk_faster_left
	.endr
	step_end

SE_Movement_TrainLeftStop:
	.rept 20
	walk_faster_left
	.endr
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_left
	walk_left
	walk_slow_left
	step_end
