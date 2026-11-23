OlivineCity_hns_MapScripts::
	.byte 0


OlivineCity_EventScript_Youngster::
	lock
	faceplayer
	msgbox OlivineCity_Text_YoungsterPokegear, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_YoungsterPokegear::
	.string "That thing you have--\n"
	.string "it's a POKéNAV, right?\l"
	.string "Wow, that's cool.$"

OlivineCity_EventScript_Sailor2::
	lock
	faceplayer
	msgbox OlivineCity_Text_Sailor2, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_Sailor2::
	.string "The league has JASMINE\n"
	.string "pegged as the sixth\l"
	.string "strongest GYM LEADER!\p"
	.string "Hah! That's a load of crud.\p"
	.string "There's no way PRYCE could\n"
	.string "hurt JASMINE's STEEL-type\l"
	.string "POKéMON!\p"
	.string "Bureaucracy if you ask me.\p"
	.string "She's something to be feared,\n"
	.string "that's for sure!$"

OlivineCity_EventScript_Sailor1::
	lock
	faceplayer
	msgbox OlivineCity_Text_Sailor1, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_Sailor1::
	.string "Dark roads are dangerous\n"
	.string "at night.\p"
	.string "But in the pitch-black of\n"
	.string "night, the sea is even more\l"
	.string "treacherous!\p"
	.string "Without the beacon of the\n"
	.string "LIGHTHOUSE to guide it,\l"
	.string "no ship can sail.$"

OlivineCity_EventScript_Machoke::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MACHOKE, CRY_MODE_NORMAL
	msgbox OlivineCity_Text_Machoke, MSGBOX_DEFAULT
	waitmoncry
	release
	end

OlivineCity_Text_Machoke::
	.string "MACHOKE: CHO!$"

SE_J_OlivineCity_hns_OlivineCity_EventScript_Item_ChargeBeam::
	finditem ITEM_TM_SHOCK_WAVE
	end

OlivineCity_EventScript_EonTicketWoman::
	lock
	faceplayer
	goto_if_set FLAG_SE_KANTO_CHAMPION, OlivineCity_EventScript_EonTicketWomanChamp
	msgbox OlivineCity_Text_EonTicketWoman1, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_EonTicketWoman1::
	.string "My name is MARY!\p"
	.string "Just kidding, but I love MARY's\n"
	.string "radio show!$"

OlivineCity_EventScript_EonTicketWomanChamp::
	msgbox OlivineCity_Text_EonTicketWoman2, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_EonTicketWoman2::
	.string "You must be {PLAYER}!!!\p"
	.string "Oh my goodness! The champion!\p"
	.string "I heard about your win in KANTO\n"
	.string "on MARY's radio show!$"

OlivineCity_EventScript_GymSign::
	lock
	msgbox OlivineCity_Text_GymSign, MSGBOX_SIGN
	end

OlivineCity_Text_GymSign::
	.string "OLIVINE CITY POKéMON GYM\n"
	.string "LEADER: JASMINE\p"
	.string "The Steel-Clad Defense Girl$"

OlivineCity_EventScript_LighthouseSign::
	lock
	msgbox OlivineCity_Text_LighthouseSign, MSGBOX_SIGN
	end

OlivineCity_Text_LighthouseSign::
	.string "OLIVINE LIGHTHOUSE\n"
	.string "Also known as the GLITTER\l"
	.string "LIGHTHOUSE$"

OlivineCity_EventScript_PortSign::
	lock
	msgbox OlivineCity_Text_PortSign, MSGBOX_SIGN
	end

OlivineCity_Text_PortSign::
	.string "OLIVINE PORT\n"
	.string "FAST SHIP PIER$"

OlivineCity_EventScript_Sign::
	lock
	msgbox OlivineCity_Text_Sign, MSGBOX_SIGN
	end

OlivineCity_Text_Sign::
	.string "OLIVINE CITY\p"
	.string "The Port Closest to Foreign Lands$"

OlivineCity_EventScript_CafeSign::
	msgbox OlivineCity_Text_CafeSign, MSGBOX_SIGN
	end

OlivineCity_Text_CafeSign::
	.string "OLIVINE CAFE\n"
	.string "WHERE STRONG SAILORS ENJOY\l"
	.string "HEARTY MEALS OF STRENGTH$"
