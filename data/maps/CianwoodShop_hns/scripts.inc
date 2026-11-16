CianwoodShop_hns_MapScripts::
	.byte 0


CianwoodCity_Text_PharmacistGivePotion::
	.string "Your POKéMON appear to be fine.\p"
	.string "Is something worrying you?\p"
	.string "…\p"
	.string "The LIGHTHOUSE POKéMON is in\n"
	.string "trouble?\p"
	.string "I got it!\p"
	.string "This ought to do the trick.$"

SE_J_CianwoodShop_hns_CianwoodCity_EventScript_Pharmacist::
	msgbox CianwoodCity_Text_PharmacistGivePotion, MSGBOX_NPC
	end
