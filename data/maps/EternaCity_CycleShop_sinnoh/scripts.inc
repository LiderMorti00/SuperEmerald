EternaCity_CycleShop_sinnoh_MapScripts::
	.byte 0


EternaCity_CycleShop_EventScript_Clerk::
	goto_if_set FLAG_HIDE_ETERNA_GALACTIC, EternaCity_CycleShop_EventScript_ClerkAfter
	msgbox EternaCity_CycleShop_Text_Clerk, MSGBOX_NPC
	end

EternaCity_CycleShop_Text_Clerk::
	.string "Sorry, we're closed! Our boss went\n"
	.string "to talk to those GALACTIC people\l"
	.string "and hasn't come back…\p"
	.string "Without him, I can't sell any\n"
	.string "bikes. I'm so worried!$"

EternaCity_CycleShop_EventScript_ClerkAfter::
	msgbox EternaCity_CycleShop_Text_ClerkAfter, MSGBOX_NPC
	end

EternaCity_CycleShop_Text_ClerkAfter::
	.string "What was TEAM GALACTIC trying to do\n"
	.string "with other people's POKéMON?$"

EternaCity_CycleShop_EventScript_PtNpc1::
	goto_if_set FLAG_HIDE_ETERNA_GALACTIC, EternaCity_CycleShop_EventScript_PtNpc1After
	msgbox EternaCity_CycleShop_Text_PtNpc1, MSGBOX_NPC
	end

EternaCity_CycleShop_Text_PtNpc1::
	.string "The manager's gone off to the TEAM\n"
	.string "GALACTIC building and hasn't\l"
	.string "returned.\p"
	.string "I wonder what's holding him up?$"

EternaCity_CycleShop_EventScript_PtNpc1After::
	msgbox EternaCity_CycleShop_Text_PtNpc1After, MSGBOX_NPC
	end

EternaCity_CycleShop_Text_PtNpc1After::
	.string "The manager's back!\p"
	.string "I was worried he wouldn't make it\n"
	.string "out of the GALACTIC building.$"

EternaCity_CycleShop_EventScript_Owner::
	lock
	faceplayer
	checkitem ITEM_BICYCLE
	goto_if_eq VAR_RESULT, TRUE, EternaCity_CycleShop_EventScript_OwnerManual
	msgbox EternaCity_CycleShop_Text_OwnerThanks, MSGBOX_DEFAULT
	giveitem ITEM_BICYCLE
	goto_if_eq VAR_RESULT, FALSE, EternaCity_CycleShop_EventScript_OwnerBagFull
	setflag FLAG_RECEIVED_BICYCLE
	msgbox EternaCity_CycleShop_Text_OwnerManual, MSGBOX_DEFAULT
	release
	end

EternaCity_CycleShop_EventScript_OwnerBagFull::
	call Common_EventScript_BagIsFull
	release
	end

EternaCity_CycleShop_Text_OwnerManual::
	.string "You can ride this BIKE on roads\n"
	.string "and paths.\p"
	.string "Register it from your BAG to use\n"
	.string "it without opening the menu.$"

EternaCity_CycleShop_Text_OwnerThanks::
	.string "Welcome to the CYCLE SHOP!\p"
	.string "A BIKE is a good way to see SINNOH.\n"
	.string "Here, I'd like you to have one.$"

EternaCity_CycleShop_EventScript_OwnerManual::
	msgbox EternaCity_CycleShop_Text_OwnerManual, MSGBOX_DEFAULT
	release
	end

EternaCity_CycleShop_EventScript_Clefairy::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CLEFAIRY, CRY_MODE_NORMAL
	msgbox EternaCity_CycleShop_Text_Clefairy, MSGBOX_DEFAULT
	waitmoncry
	release
	end

EternaCity_CycleShop_Text_Clefairy::
	.string "CLEFAIRY: Pip piih!$"
