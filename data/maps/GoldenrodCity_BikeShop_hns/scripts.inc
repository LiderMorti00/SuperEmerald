GoldenrodCity_BikeShop_hns_MapScripts::
	.byte 0


GoldenrodCity_BikeShop_EventScript_Clerk::
	lock
	faceplayer
	goto_if_set FLAG_J_RECEIVED_BIKE, GoldenrodCity_BikeShop_EventScript_Clerk_BikeReceived
	msgbox GoldenrodCity_BikeShop_Text_ClerkIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_BikeShop_EventScript_Clerk_BikeAgreed
	msgbox GoldenrodCity_BikeShop_Text_Refused, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BikeShop_Text_Refused::
    .string "…sigh… Oh, for the kindness of\n"
    .string "people…$"

GoldenrodCity_BikeShop_EventScript_Clerk_BikeAgreed::
	msgbox GoldenrodCity_BikeShop_Text_ClerkAgreed, MSGBOX_DEFAULT
	giveitem ITEM_BICYCLE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_J_RECEIVED_BIKE
	closemessage
	release
	end

GoldenrodCity_BikeShop_Text_ClerkAgreed::
    .string "Really? Great!\p"
    .string "Give me your name and phone number,\n"
    .string "and I'll loan you a BICYCLE.$"

GoldenrodCity_BikeShop_Text_ClerkIntro::
    .string "…sigh… I moved here, but I can't\n"
    .string "sell my BICYCLES. Why is that?\p"
    .string "Could you ride a BICYCLE and\n"
    .string "advertise for me?$"

GoldenrodCity_BikeShop_EventScript_Clerk_BikeReceived::
	msgbox GoldenrodCity_BikeShop_Text_Mainshop, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BikeShop_Text_Mainshop::
	.string "When we moved here from KANTO,\n"
	.string "hardly anyone knew our shop.\p"
	.string "Then a kid started riding one of\n"
	.string "our bikes all over JOHTO. Best\l"
	.string "advertising we ever had!$"

GoldenrodCity_BikeShop_EventScript_Clerk2::
	lock
	faceplayer
	msgbox GoldenrodCity_BikeShop_Text_Clerk2, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BikeShop_Text_Clerk2::
	.string "Riding the BIKE is as simple as\n"
	.string "pressing a button if you\l"
	.string "REGISTER it from the BAG.\p"
	.string "If you need to go faster,\n"
	.string "you first need to come to a stop!\p"
	.string "That might seem like strange\n"
	.string "advice, but you can only change\l"
	.string "gears on the BIKE while stopped.\p"
	.string "Press your R button when stopped\n"
	.string "and the next time you pedal,\l"
	.string "you will reach greater speeds!$"

GoldenrodCity_BikeShop_EventScript_Bike::
	lock
	msgbox GoldenrodCity_BikeShop_Text_Bicycle, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BikeShop_Text_Bicycle::
    .string "It's a shiny new BICYCLE!$"
