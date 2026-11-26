CianwoodCity_hns_MapScripts::
	.byte 0

CianwoodCity_EventScript_PokefanM::
	lock
	faceplayer
	msgbox CianwoodCity_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_PokefanM::
	.string "Boulders to the north of town can\n"
	.string "be crushed.\p"
	.string "They may be hiding something.\p"
	.string "Your POKéMON could use ROCK SMASH\n"
	.string "to break them.$"

CianwoodCity_EventScript_Youngster::
	lock
	faceplayer
	msgbox CianwoodCity_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_Youngster::
	.string "If you use FLY, you can get back\n"
	.string "to OLIVINE instantly.$"

CianwoodCity_EventScript_Lass::
	lock
	faceplayer
	msgbox CianwoodCity_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_Lass::
	.string "CHUCK, the GYM LEADER, spars with\n"
	.string "his fighting POKéMON.$"

CianwoodCity_Text_ChucksWifeEasierToFly::
	.string "You crossed the sea to get here?\p"
	.string "That must have been hard.\p"
	.string "It would be much easier if your\n"
	.string "POKéMON knew how to FLY…$"

SE_J_CianwoodCity_hns_CianwoodCity_EventScript_ChucksWife::
	msgbox CianwoodCity_Text_ChucksWifeEasierToFly, MSGBOX_NPC
	end

CianwoodCity_EventScript_CitySign::
	lock
	msgbox CianwoodCity_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

CianwoodCity_Text_Sign::
	.string "CIANWOOD CITY\p"
	.string "A Port Surrounded by Rough Seas$"

CianwoodCity_EventScript_Pharmacy::
	lock
	msgbox CianwoodCity_Text_PharmacySign, MSGBOX_SIGN
	closemessage
	release
	end

CianwoodCity_Text_PharmacySign::
	.string "500 Years of Tradition\p"
	.string "CIANWOOD CITY PHARMACY\p"
	.string "We Await Your Medicinal Queries$"

CianwoodCity_EventScript_GymSign::
	lock
	msgbox CianwoodCity_Text_GymSign, MSGBOX_SIGN
	closemessage
	release
	end

CianwoodCity_Text_GymSign::
	.string "CIANWOOD CITY POKéMON GYM\p"
	.string "LEADER: CHUCK\p"
	.string "His Roaring Fists Do the Talking$"

CianwoodCity_EventScript_CaveSign::
	lock
	msgbox CianwoodCity_Text_Safari, MSGBOX_SIGN
	closemessage
	release
	end

CianwoodCity_Text_Safari::
	.string "CLIFF EDGE CAVE\n"
	.string "Road to the SAFARI ZONE.$"
