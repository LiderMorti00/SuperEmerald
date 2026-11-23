SunyshoreCity_Market_sinnoh_MapScripts::
	.byte 0


SunyshoreCity_Market_EventScript_PtNpc1::
	msgbox SunyshoreCity_Market_Text_PtNpc1, MSGBOX_NPC
	end

SunyshoreCity_Market_Text_PtNpc1::
	.string "Effort Ribbons go to POKéMON that\n"
	.string "train really hard.\p"
	.string "I hope my POKéMON gets one someday!$"

SunyshoreCity_Market_EventScript_PtNpc2::
	msgbox SunyshoreCity_Market_Text_PtNpc2, MSGBOX_NPC
	end

SunyshoreCity_Market_Text_PtNpc2::
	.string "See the Seal Merchant there?$"

SunyshoreCity_Market_EventScript_PtNpc3::
	lock
	faceplayer
	msgbox SunyshoreCity_Market_Text_PtNpc3_0, MSGBOX_DEFAULT
	release
	end

SunyshoreCity_Market_Text_PtNpc3_0::
	.string "SUNYSHORE Market is best known for its\n"
	.string "big selection of Seals.$"

SunyshoreCity_Market_EventScript_PtNpc4::
	msgbox SunyshoreCity_Market_Text_PtNpc4, MSGBOX_NPC
	end

SunyshoreCity_Market_Text_PtNpc4::
	.string "Ah, please, allow me a little of your\n"
	.string "time, if you will.\p"
	.string "…Oh, but, no, no, no! You have no Seal\n"
	.string "Case? What a shame! They're quite\l"
	.string "hard to come by these days.$"

SunyshoreCity_Market_EventScript_PtNpc5::
	lock
	faceplayer
	msgbox SunyshoreCity_Market_Text_PtNpc5_0, MSGBOX_DEFAULT
	release
	end

SunyshoreCity_Market_Text_PtNpc5_0::
	.string "I love Tap Toys! Plaza Games are great,\n"
	.string "too!\p"
	.string "I'm a huge fan of the GAME CORNER in\n"
	.string "VEILSTONE, so I'm promoting it!$"
