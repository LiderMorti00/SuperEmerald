GoldenrodCity_UndergroundTunnel_hns_MapScripts::
	.byte 0


GoldenrodUnderground_EventScript_Issac::
	trainerbattle_single TRAINER_ISSAC_HNS, GoldenrodUnderground_Text_PokemaniacIssacSeen, GoldenrodUnderground_Text_PokemaniacIssacBeaten
	msgbox GoldenrodUnderground_Text_PokemaniacIssacAfterBattle, MSGBOX_AUTOCLOSE
	end

GoldenrodUnderground_Text_PokemaniacIssacAfterBattle::
    .string "Your POKéMON will like you more if\n"
    .string "you give them haircuts.$"

GoldenrodUnderground_Text_PokemaniacIssacBeaten::
    .string "Aiyeeee!$"

GoldenrodUnderground_Text_PokemaniacIssacSeen::
    .string "My POKéMON just got a haircut!\p"
    .string "I'll show you how strong it is!$"

GoldenrodUnderground_Text_OlderBrotherOffer::
	.string "Welcome!\p"
	.string "I run the POKéMON SALON! I'm the\n"
	.string "older and better of the two\l"
	.string "HAIRCUT BROTHERS.\p"
	.string "Sorry, but I'm fully booked today.\n"
	.string "My little brother works nights!$"

SE_J_GoldenrodCity_UndergroundTunnel_hns_GoldenrodUnderground_EventScript_Brother_Haircut1::
	msgbox GoldenrodUnderground_Text_OlderBrotherOffer, MSGBOX_NPC
	end

GoldenrodUnderground_Text_YoungerBrotherOffer::
	.string "Welcome to the POKéMON SALON!\p"
	.string "I'm the younger of the two\n"
	.string "HAIRCUT BROTHERS.\p"
	.string "Sorry, I'm all booked up tonight.\n"
	.string "My big brother works days!$"

SE_J_GoldenrodCity_UndergroundTunnel_hns_GoldenrodUnderground_EventScript_Brother_Haircut2::
	msgbox GoldenrodUnderground_Text_YoungerBrotherOffer, MSGBOX_NPC
	end

GoldenrodUnderground_EventScript_Teru::
	trainerbattle_single TRAINER_TERU_HNS, GoldenrodUnderground_Text_SupernerdTeruSeen, GoldenrodUnderground_Text_SupernerdTeruBeaten
	msgbox GoldenrodUnderground_Text_SupernerdTeruAfterBattle, MSGBOX_AUTOCLOSE
	end

GoldenrodUnderground_Text_SupernerdTeruAfterBattle::
    .string "I know my POKéMON type alignments.\p"
    .string "But I only use one type of POKéMON.$"

GoldenrodUnderground_Text_SupernerdTeruBeaten::
    .string "Ow, ow, ow!$"

GoldenrodUnderground_Text_SupernerdTeruSeen::
    .string "Do you consider type alignments in\n"
    .string "battle?\p"
    .string "If you know your type advantages,\n"
    .string "you'll do better in battle.$"

GoldenrodUnderground_EventScript_Eric::
	trainerbattle_single TRAINER_ERIC_HNS, GoldenrodUnderground_Text_SupernerdEricSeen, GoldenrodUnderground_Text_SupernerdEricBeaten
	msgbox GoldenrodUnderground_Text_SupernerdEricAfterBattle, MSGBOX_AUTOCLOSE
	end

GoldenrodUnderground_Text_SupernerdEricAfterBattle::
    .string "I guess I have to do things fair and\n"
    .string "square…$"

GoldenrodUnderground_Text_SupernerdEricBeaten::
    .string "…Grumble…$"

GoldenrodUnderground_Text_SupernerdEricSeen::
    .string "I got booted out of the GAME CORNER.\p"
    .string "I was trying to cheat using my\n"
    .string "POKéMON…$"

GoldenrodUnderground_EventScript_Donald::
	trainerbattle_single TRAINER_DONALD_HNS, GoldenrodUnderground_Text_PokemaniacDonaldSeen, GoldenrodUnderground_Text_PokemaniacDonaldBeaten
	msgbox GoldenrodUnderground_Text_PokemaniacDonaldAfterBattle, MSGBOX_AUTOCLOSE
	end

GoldenrodUnderground_Text_PokemaniacDonaldAfterBattle::
	.string "When I was walking near the BIKE\n"
	.string "SHOP last night, I felt like I was\l"
	.string "being watched from the rooftops…$"

GoldenrodUnderground_Text_PokemaniacDonaldBeaten::
    .string "Gaah! I lost! That makes me mad!$"

GoldenrodUnderground_Text_PokemaniacDonaldSeen::
    .string "I think you have some rare POKéMON\n"
    .string "with you.\p"
    .string "Let me see them!$"

GoldenrodCity_UndergroundTunnel_EventScript_Item_CoinCase::
	finditem ITEM_COIN_CASE
	end

GoldenrodCity_UndergroundTunnel_EventScript_Item_ParalyzeHeal::
	finditem ITEM_PARALYZE_HEAL
	end

GoldenrodCity_UndergroundTunnel_EventScript_Item_Antidote::
	finditem ITEM_ANTIDOTE
	end

GoldenrodCity_UndergroundTunnel_EventScript_Item_SuperPotion::
	finditem ITEM_SUPER_POTION
	end

GoldenrodCity_UndergroundTunnel_EventScript_Door::
	lock
	goto_if_set FLAG_UNLOCKED_GOLDENROD_UNDERGROUND_DOOR, GoldenrodCity_UndergroundTunnel_EventScript_DoorAlreadyOpened
	checkitem ITEM_BASEMENT_KEY
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_UndergroundTunnel_EventScript_OpenDoor
	msgbox GoldenrodUnderground_Text_DoorsLocked, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodUnderground_Text_DoorsLocked::
    .string "The door's locked…$"

GoldenrodCity_UndergroundTunnel_EventScript_OpenDoor::
	msgbox GoldenrodUnderground_Text_KeyOpenedDoor, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_UNLOCKED_GOLDENROD_UNDERGROUND_DOOR
	setmetatile 12, 10, 0x2DD, FALSE
	playse SE_BANG
	special DrawWholeMapView
	waitse
	release
	end

GoldenrodUnderground_Text_KeyOpenedDoor::
    .string "The BASEMENT KEY opened the door.$"

GoldenrodCity_UndergroundTunnel_EventScript_DoorAlreadyOpened::
	msgbox GoldenrodUnderground_Text_DoorIsOpen, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodUnderground_Text_DoorIsOpen::
    .string "The door is open.$"
