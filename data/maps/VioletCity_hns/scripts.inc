VioletCity_hns_MapScripts::
	.byte 0


VioletCity_EventScript_Lass::
	lock
	faceplayer
	msgbox VioletCity_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_Text_Lass::
	.string "Ghosts are rumored to appear\n"
	.string "in SPROUT TOWER.\p"
	.string "They say that GHOST-type\n"
	.string "moves can bypass the defenses\p"
	.string "of tough POKéMON like ONIX\n"
	.string "and GEODUDE.$"

VioletCity_EventScript_Boy::
	lock
	faceplayer
	msgbox VioletCity_Text_Boy, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_Text_Boy::
	.string "Hey, you're a POKéMON trainer?\p"
	.string "If you head to the ACADEMY,\n"
	.string "you might learn something new!$"

VioletCity_EventScript_Gramps::
	lock
	faceplayer
	msgbox VioletCity_Text_Gramps, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_Text_Gramps::
	.string "FALKNER, from the VIOLET\n"
	.string "POKéMON GYM, is a fine trainer!\p"
	.string "He inherited his father's gym\n"
	.string "and has done a great job with\l"
	.string "it.$"

VioletCity_Text_EarlAsksIfYouBeatFalkner::
	.string "Hello!\n"
	.string "You are trainer?\p"
	.string "Battle GYM LEADER,\n"
	.string "win you did?$"

SE_J_VioletCity_hns_VioletCity_EventScript_Earl::
	msgbox VioletCity_Text_EarlAsksIfYouBeatFalkner, MSGBOX_NPC
	end

VioletCity_EventScript_Youngster::
	lock
	faceplayer
	msgbox VioletCity_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_Text_Youngster::
	.string "I saw a wiggly tree up ahead!\p"
	.string "If you touch it, it squirms\n"
	.string "and dances! Cool!$"

VioletCity_EventScript_ItemPechaBerry::
	finditem ITEM_PECHA_BERRY
	end

VioletCity_EventScript_ItemHyperPotion::
	finditem ITEM_HYPER_POTION
	end

VioletCity_EventScript_Bellsprout::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_BELLSPROUT, CRY_MODE_NORMAL
	msgbox VioletCity_Text_Bellsprout, MSGBOX_DEFAULT
	waitmoncry
	release
	end

VioletCity_Text_Bellsprout::
	.string "BELLSPROUT: Sprouuuut.$"

VioletCity_EventScript_Pichu::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PICHU, CRY_MODE_NORMAL
	msgbox VioletCity_Text_Pichu, MSGBOX_DEFAULT
	waitmoncry
	release
	end

VioletCity_Text_Pichu::
	.string "PICHU: Chuuuu!$"

VioletCity_EventScript_Rattata::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_RATTATA, CRY_MODE_NORMAL
	msgbox VioletCity_Text_Rattata, MSGBOX_DEFAULT
	waitmoncry
	release
	end

VioletCity_Text_Rattata::
	.string "RATTATA: RATTATARATTA!$"

VioletCity_EventScript_ItemRareCandy::
	finditem ITEM_RARE_CANDY
	end

VioletCity_EventScript_GymSign::
	msgbox VioletCity_Text_GymSign, MSGBOX_SIGN
	end

VioletCity_Text_GymSign::
	.string "VIOLET CITY POKéMON GYM\p"
	.string "LEADER: FALKNER, The Elegant\n"
	.string "Master of Flying POKéMON$"

VioletCity_EventScript_LiquidJustice::
	msgbox VioletCity_Text_LiquidJustice, MSGBOX_NPC
	end

VioletCity_Text_LiquidJustice::
	.string "Look around!\p"
	.string "It's easy to see what POKéMON\n"
	.string "you can catch in an area without\l"
	.string "having to run around in tall\l"
	.string "grass all day!$"
