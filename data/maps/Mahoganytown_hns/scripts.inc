Mahoganytown_hns_MapScripts::
	.byte 0


MahoganyTown_Text_Gramps::
    .string "Are you off to see the GYARADOS\n"
    .string "rampage at the LAKE?$"

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
	msgbox MahoganyTown_Text_RageCandyBarMerchantTryOne, MSGBOX_NPC
	end

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
