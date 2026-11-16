CherrygroveCity_Mart_hns_MapScripts::
	.byte 0


SE_J_CherrygroveCity_Mart_hns_Cherrygrove_Pokemart_EventScript_Clerk::
	msgbox gText_HowMayIServeYou, MSGBOX_NPC
	end

Cherrygrove_Pokemart_EventScript_Youngster::
	lock
	faceplayer
	msgbox Cherrygrove_Pokemart_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

Cherrygrove_Pokemart_Text_Youngster::
	.string "When I was walking in the grass, a\n"
	.string "bug POKéMON poisoned my POKéMON!\p"
	.string "I just kept going, but then my\n"
	.string "POKéMON fainted.\p"
	.string "You should keep an ANTIDOTE\n"
	.string "with you.$"

Cherrygrove_Pokemart_Text_CooltrainerM::
	.string "They're fresh out of POKé BALLS!\p"
	.string "When will they get more of them?$"

SE_J_CherrygroveCity_Mart_hns_Cherrygrove_Pokemart_EventScript_Bugcatcher::
	msgbox Cherrygrove_Pokemart_Text_CooltrainerM, MSGBOX_NPC
	end
