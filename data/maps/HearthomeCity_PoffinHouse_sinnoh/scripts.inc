HearthomeCity_PoffinHouse_sinnoh_MapScripts::
	.byte 0


HearthomeCity_PoffinHouse_EventScript_PtNpc1::
	lock
	faceplayer
	goto_if_unset FLAG_SN_RECEIVED_POKEBLOCK_CASE, HearthomeCity_PoffinHouse_EventScript_SNCase
	msgbox HearthomeCity_PoffinHouse_Text_PtNpc1_0, MSGBOX_DEFAULT
	release
	end

HearthomeCity_PoffinHouse_Text_PtNpc1_0::
	.string "Hi! Let's get blending!\p"
	.string "Here's my advice for making tasty\n"
	.string "POKéBLOCKS for your POKéMON crew!\p"
	.string "Press the A Button just as the\n"
	.string "BLENDER's arrow reaches your marker.\p"
	.string "The faster it spins, the better your\n"
	.string "POKéBLOCKS turn out!$"

HearthomeCity_PoffinHouse_EventScript_SNCase::
	checkitem ITEM_POKEBLOCK_CASE
	goto_if_eq VAR_RESULT, TRUE, HearthomeCity_PoffinHouse_EventScript_SNHasCase
	msgbox HearthomeCity_PoffinHouse_Text_SNCase, MSGBOX_DEFAULT
	giveitem ITEM_POKEBLOCK_CASE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SN_RECEIVED_POKEBLOCK_CASE
	msgbox HearthomeCity_PoffinHouse_Text_SNCase2, MSGBOX_DEFAULT
	release
	end

HearthomeCity_PoffinHouse_EventScript_SNHasCase::
	setflag FLAG_SN_RECEIVED_POKEBLOCK_CASE
	msgbox HearthomeCity_PoffinHouse_Text_SNHasCase, MSGBOX_DEFAULT
	release
	end

HearthomeCity_PoffinHouse_Text_SNHasCase::
	.string "Oh, you already have a POKéBLOCK CASE\n"
	.string "from HOENN! Then you're all set.\p"
	.string "Feed POKéBLOCKS to your POKéMON and\n"
	.string "they'll shine in CONTESTS!$"

HearthomeCity_PoffinHouse_Text_SNCase2::
	.string "Put BERRIES in a BERRY BLENDER to\n"
	.string "make POKéBLOCKS for your POKéMON.\p"
	.string "You'll find BERRY BLENDERS at the\n"
	.string "CONTEST HALL here in HEARTHOME!$"

HearthomeCity_PoffinHouse_Text_SNCase::
	.string "Welcome to the POKéBLOCK HOUSE!\p"
	.string "If you want to make POKéBLOCKS, you'll\n"
	.string "need something to keep them in.\p"
	.string "Here, take this!$"

HearthomeCity_PoffinHouse_EventScript_PtNpc2::
	lock
	faceplayer
	msgbox HearthomeCity_PoffinHouse_Text_PtNpc2_0, MSGBOX_DEFAULT
	release
	end

HearthomeCity_PoffinHouse_Text_PtNpc2_0::
	.string "Eating good food makes people and\n"
	.string "POKéMON more energetic and happy.\p"
	.string "In that sense, we're exactly alike.$"

HearthomeCity_PoffinHouse_EventScript_PtNpc3::
	lock
	faceplayer
	msgbox HearthomeCity_PoffinHouse_Text_PtNpc3_0, MSGBOX_DEFAULT
	release
	end

HearthomeCity_PoffinHouse_Text_PtNpc3_0::
	.string "Have you got some Berries?\p"
	.string "To make delicious POKéBLOCKS, the key\n"
	.string "ingredient is a rare Berry.\p"
	.string "And, the more cooks you have, the more\n"
	.string "delicious the POKéBLOCK!$"

HearthomeCity_PoffinHouse_EventScript_PtNpc4::
	lock
	faceplayer
	msgbox HearthomeCity_PoffinHouse_Text_PtNpc4_0, MSGBOX_DEFAULT
	release
	end

HearthomeCity_PoffinHouse_Text_PtNpc4_0::
	.string "At the BERRY BLENDERS in HOENN, I can\n"
	.string "cook up POKéBLOCKS with my friends!$"

Sinnoh_EventScript_GenericMart::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	specialvar VAR_RESULT, GetSinnohBadgeCount
	goto_if_ge VAR_RESULT, 5, Sinnoh_EventScript_GenericMart5
	goto_if_ge VAR_RESULT, 3, Sinnoh_EventScript_GenericMart3
	goto_if_ge VAR_RESULT, 1, Sinnoh_EventScript_GenericMart1
	pokemart Sinnoh_Pokemart_Tier0
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

Sinnoh_Pokemart_Tier0::
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	pokemartlistend

	.align 2

Sinnoh_EventScript_GenericMart1::
	pokemart Sinnoh_Pokemart_Tier1
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

Sinnoh_Pokemart_Tier1::
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	pokemartlistend

	.align 2

Sinnoh_EventScript_GenericMart3::
	pokemart Sinnoh_Pokemart_Tier3
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

Sinnoh_Pokemart_Tier3::
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_SUPER_REPEL
	pokemartlistend

	.align 2

Sinnoh_EventScript_GenericMart5::
	pokemart Sinnoh_Pokemart_Tier5
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2

Sinnoh_Pokemart_Tier5::
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_MAX_REPEL
	pokemartlistend
