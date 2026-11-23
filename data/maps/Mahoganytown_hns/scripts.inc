Mahoganytown_hns_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, Mahoganytown_OnLoad
	.byte 0

@ Super Emerald: post-story Mahogany (Heart & Soul FixTree)
Mahoganytown_OnLoad::
	setmetatile 18, 8, 0x378, FALSE
	setmetatile 19, 8, 0x379, FALSE
	end


MahoganyTown_Text_Gramps::
	.string "Are you off to see the LAKE OF\n"
	.string "RAGE? It's a fine place to fish.$"

SE_J_Mahoganytown_hns_MahoganyTown_EventScript_Gramps::
	msgbox MahoganyTown_Text_Gramps, MSGBOX_NPC
	end

MahoganyTown_EventScript_Lass::
	lock
	faceplayer
	msgbox MahoganyTown_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_Text_Lass::
    .string "Visit Grandma's shop. She sells\n"
    .string "stuff that nobody else has.$"

MahoganyTown_Text_RageCandyBarMerchantTryOne::
	.string "Hiya, kid!\p"
	.string "I see you're new in MAHOGANY TOWN.\p"
	.string "Since you're new, you should try a\n"
	.string "yummy RAGECANDYBAR!\p"
	.string "Right now, it can be yours for just\n"
	.string "¥300! Want one?$"

SE_J_Mahoganytown_hns_MahoganyTown_EventScript_Merchant::
	lock
	faceplayer
	msgbox MahoganyTown_Text_RageCandyBarMerchantTryOne, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MahoganyTown_EventScript_MerchantNo
	checkmoney 300
	goto_if_eq VAR_RESULT, FALSE, MahoganyTown_EventScript_MerchantNoMoney
	checkitemspace ITEM_RAGE_CANDY_BAR
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	removemoney 300
	giveitem ITEM_RAGE_CANDY_BAR
	msgbox MahoganyTown_Text_MerchantThanks, MSGBOX_DEFAULT
	release
	end

MahoganyTown_EventScript_MerchantNo::
	msgbox MahoganyTown_Text_MerchantNo, MSGBOX_DEFAULT
	release
	end

MahoganyTown_EventScript_MerchantNoMoney::
	msgbox MahoganyTown_Text_MerchantNoMoney, MSGBOX_DEFAULT
	release
	end

MahoganyTown_Text_MerchantThanks::
	.string "Thanks, kid!\n"
	.string "Enjoy that RAGECANDYBAR!$"

MahoganyTown_Text_MerchantNo::
	.string "Suit yourself. You don't know what\n"
	.string "you're missing!$"

MahoganyTown_Text_MerchantNoMoney::
	.string "Hm? You don't have enough money.\n"
	.string "Come back when you do!$"

MahoganyTown_EventScript_Fisher::
	lock
	faceplayer
	msgbox MahoganyTown_Text_Fisher, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_Text_Fisher::
    .string "Since you came this far, take the\n"
    .string "time to do some sightseeing.\p"
    .string "You should head north and check\n"
    .string "out LAKE OF RAGE right now.$"

MahoganyTown_EventScript_Sign::
	lock
	msgbox MahoganyTown_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

MahoganyTown_Text_Sign::
    .string "MAHOGANY TOWN\p"
    .string "Welcome to the Home of the Ninja$"

MahoganyTown_EventScript_CandybarSign::
	lock
	msgbox MahoganyTown_Text_RagecandybarSign, MSGBOX_SIGN
	closemessage
	release
	end

MahoganyTown_Text_RagecandybarSign::
    .string "While visiting MAHOGANY TOWN, try\n"
    .string "a RAGECANDYBAR!$"

MahoganyTown_EventScript_GymSign::
	lock
	msgbox MahoganyTown_Text_GymSign, MSGBOX_SIGN
	closemessage
	release
	end

MahoganyTown_Text_GymSign::
    .string "MAHOGANY TOWN POKéMON GYM\p"
    .string "LEADER: PRYCE\p"
    .string "The Teacher of Winter's Harshness$"
