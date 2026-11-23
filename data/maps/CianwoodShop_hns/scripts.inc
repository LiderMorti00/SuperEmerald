CianwoodShop_hns_MapScripts::
	.byte 0


CianwoodCity_Text_PharmacistGivePotion::
	.string "The medicine we sent to OLIVINE\n"
	.string "worked. AMPHY's back on its feet!\p"
	.string "I can see the lighthouse from here\n"
	.string "on a clear night.$"

SE_J_CianwoodShop_hns_CianwoodCity_EventScript_Pharmacist::
	msgbox CianwoodCity_Text_PharmacistGivePotion, MSGBOX_NPC
	end
