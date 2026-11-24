OlivineCity_Cafe_hns_MapScripts::
	.byte 0

OlivineCity_EventScript_Cook::
	lock
	faceplayer
	msgbox OlivineCity_Text_CafeFishingGuru, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_CafeFishingGuru::
	.string "OLIVINE CAFE's menu is packed\n"
	.string "with hearty fare for beefy\l"
	.string "SAILORS like me!$"

OlivineCity_Text_CafeSailorStrength::
	.string "See a boulder blocking the way?\p"
	.string "A POKéMON with STRENGTH can push\n"
	.string "it aside.$"

SE_J_OlivineCity_Cafe_hns_OlivineCity_EventScript_SailorA::
	msgbox OlivineCity_Text_CafeSailorStrength, MSGBOX_NPC
	end

OlivineCity_EventScript_SailorB::
	lock
	faceplayer
	msgbox OlivineCity_Text_CafeSailor, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_CafeSailor::
	.string "Whenever I roll into this town,\n"
	.string "I always visit the OLIVINE CAFE.\p"
	.string "Everything on the menu makes me\n"
	.string "feel stronger. I can't stop eating!$"
