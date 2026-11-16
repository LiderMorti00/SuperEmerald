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
