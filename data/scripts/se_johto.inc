@ Pokémon Super Emerald: hand-made Johto scripts (the HnS ones are in data/maps/*_hns).

@ ---------------------------------------------------------------------------
@ Petalburg Gym: Norman gives the Johto Ticket after the Hoenn League
SE_EventScript_NormanTickets::
	goto_if_unset FLAG_SE_RECEIVED_JOHTO_TICKET, SE_EventScript_NormanJohtoTicket
	return

SE_EventScript_NormanJohtoTicket::
	msgbox SE_Text_NormanJohtoTicket, MSGBOX_DEFAULT
	giveitem ITEM_JOHTO_TICKET
	setflag FLAG_SE_RECEIVED_JOHTO_TICKET
	msgbox SE_Text_NormanJohtoTicketExplain, MSGBOX_DEFAULT
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
	checkitem ITEM_JOHTO_TICKET
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_NopReturn
	msgbox SE_Text_HarborJohtoTicket, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Common_EventScript_NopReturn
	goto_if_ne VAR_SE_JOHTO_ARRIVAL, 0, SE_EventScript_SlateportToOlivine
	setvar VAR_SE_JOHTO_ARRIVAL, 1
SE_EventScript_SlateportToOlivine::
	call SlateportCity_Harbor_EventScript_BoardFerry
	warp MAP_OLIVINE_CITY_PORT_INSIDE_HNS, 8, 16
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
	goto_if_set FLAG_SE_JOHTO_LEAGUE_CLEARED, SE_EventScript_OlivinePortSailorKanto
	msgbox SE_Text_OlivineSailorSlateport, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SE_EventScript_OlivinePortSailorDeclined
	goto SE_EventScript_OlivineToSlateport
	end

SE_EventScript_OlivinePortSailorKanto::
	message SE_Text_OlivineSailorWhere
	waitmessage
	dynmultipush SE_Text_ChoiceSlateport, 0
	dynmultipush SE_Text_ChoiceVermilion, 1
	dynmultichoice 18, 6, FALSE, 2, 0, DYN_MULTICHOICE_CB_NONE
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
	warp MAP_SLATEPORT_CITY_HARBOR, 8, 11
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
	warp MAP_VERMILION_CITY, 23, 32
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
	setflag FLAG_SE_RECEIVED_SILVER_WING
	msgbox SE_Text_JasmineSilverWingAfter, MSGBOX_DEFAULT
	release
	end

SE_EventScript_JasminePost::
	msgbox SE_Text_JasminePost, MSGBOX_DEFAULT
	release
	end

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
	.string "Show them what a TRAINER from\l"
	.string "OLIVINE can do!\p"
	.string "I'll be cheering for you.$"

@ ---------------------------------------------------------------------------
@ Magnet Train: Goldenrod <-> Saffron, open once the Johto League is beaten
SE_EventScript_MagnetTrainGoldenrod::
	lock
	faceplayer
	goto_if_unset FLAG_SE_JOHTO_LEAGUE_CLEARED, SE_EventScript_MagnetTrainClosed
	msgbox SE_Text_MagnetTrainToSaffron, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SE_EventScript_MagnetTrainNo
	msgbox SE_Text_MagnetTrainDepart, MSGBOX_DEFAULT
	closemessage
	playse SE_DOOR
	fadescreen FADE_TO_BLACK
	warp MAP_SAFFRON_CITY, 16, 12
	waitstate
	release
	end

SE_EventScript_MagnetTrainSaffron::
	lock
	faceplayer
	msgbox SE_Text_MagnetTrainToGoldenrod, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SE_EventScript_MagnetTrainNo
	msgbox SE_Text_MagnetTrainDepart, MSGBOX_DEFAULT
	closemessage
	playse SE_DOOR
	fadescreen FADE_TO_BLACK
	warp MAP_GOLDENROD_CITY_TRAIN_STATION_HNS, 16, 21
	waitstate
	release
	end

SE_EventScript_MagnetTrainClosed::
	msgbox SE_Text_MagnetTrainClosed, MSGBOX_DEFAULT
	release
	end

SE_EventScript_MagnetTrainNo::
	msgbox SE_Text_MagnetTrainNo, MSGBOX_DEFAULT
	release
	end

SE_Text_MagnetTrainClosed:
	.string "The MAGNET TRAIN to SAFFRON CITY\n"
	.string "in KANTO is reserved for the\l"
	.string "POKéMON LEAGUE CHAMPION.\p"
	.string "Please come back once you've\n"
	.string "beaten the LEAGUE.$"

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
	waitstate
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
	waitstate
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
	waitstate
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
	dynmultichoice 0, 0, FALSE, 7, 0, DYN_MULTICHOICE_CB_NONE
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
