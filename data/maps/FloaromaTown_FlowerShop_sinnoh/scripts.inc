FloaromaTown_FlowerShop_sinnoh_MapScripts::
	.byte 0


FloaromaTown_FlowerShop_EventScript_Florist::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_FLOAROMA_BERRY, FloaromaTown_FlowerShop_EventScript_FloristAfter
	msgbox FloaromaTown_FlowerShop_Text_Florist, MSGBOX_DEFAULT
	giveitem ITEM_ORAN_BERRY, 3
	setflag FLAG_RECEIVED_FLOAROMA_BERRY
	release
	end

FloaromaTown_FlowerShop_Text_Florist::
	.string "Welcome to the PICK A PECK OF\n"
	.string "COLORS FLOWER SHOP! Here, take\l"
	.string "some BERRIES as a welcome gift!$"

FloaromaTown_FlowerShop_EventScript_FloristAfter::
	msgbox FloaromaTown_FlowerShop_Text_FloristAfter, MSGBOX_DEFAULT
	release
	end

FloaromaTown_FlowerShop_Text_FloristAfter::
	.string "BERRIES grow best in soft,\n"
	.string "soil-rich ground. Take good care\l"
	.string "of them!$"

FloaromaTown_FlowerShop_EventScript_SNSprayduckDone::
	msgbox FloaromaTown_FlowerShop_Text_SNSpray2, MSGBOX_DEFAULT
	release
	end

FloaromaTown_FlowerShop_EventScript_SNSprayduck::
	lock
	faceplayer
	goto_if_set FLAG_SN_RECEIVED_SPRAYDUCK, FloaromaTown_FlowerShop_EventScript_SNSprayduckDone
	msgbox FloaromaTown_FlowerShop_Text_SNSpray1, MSGBOX_DEFAULT
	giveitem ITEM_WAILMER_PAIL
	setflag FLAG_SN_RECEIVED_SPRAYDUCK
	goto FloaromaTown_FlowerShop_EventScript_SNSprayduckDone

FloaromaTown_FlowerShop_Text_SNSpray1::
	.string "TRAINER, please water Berries using\n"
	.string "this Sprayduck watering can.$"

FloaromaTown_FlowerShop_Text_SNSpray2::
	.string "Use that Sprayduck to water the soil\n"
	.string "where you've planted Berries.\p"
	.string "You should also water Berry plants\n"
	.string "while they are growing.$"
