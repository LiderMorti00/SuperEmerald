GoldenrodCity_DepartmentStore_5F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SE_GoldenrodElevator_OnFrame
	.byte 0


GoldenrodDeptStore_Text_5FReceptionistOhYourMon::
    .string "Hello. Oh, your POKéMON…$"

SE_J_GoldenrodCity_DepartmentStore_5F_hns_GoldenrodDeptStore5_EventScript_Receptionist::
	lock
	faceplayer
	goto_if_set FLAG_SE_GOLDENROD_TM_LADY, GoldenrodDeptStore5_EventScript_ReceptionistDone
	msgbox GoldenrodDeptStore_Text_5FReceptionistOhYourMon, MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetLeadMonFriendship
	goto_if_ge VAR_RESULT, 4, GoldenrodDeptStore5_EventScript_ReceptionistReturn
	goto_if_le VAR_RESULT, 1, GoldenrodDeptStore5_EventScript_ReceptionistFrustration
	msgbox GoldenrodDeptStore_Text_5FReceptionistNotYet, MSGBOX_DEFAULT
	release
	end

GoldenrodDeptStore5_EventScript_ReceptionistReturn::
	msgbox GoldenrodDeptStore_Text_5FReceptionistLovesYou, MSGBOX_DEFAULT
	giveitem ITEM_TM_RETURN
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SE_GOLDENROD_TM_LADY
	msgbox GoldenrodDeptStore_Text_5FReceptionistDone, MSGBOX_DEFAULT
	release
	end

GoldenrodDeptStore5_EventScript_ReceptionistFrustration::
	msgbox GoldenrodDeptStore_Text_5FReceptionistUnhappy, MSGBOX_DEFAULT
	giveitem ITEM_TM_FRUSTRATION
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SE_GOLDENROD_TM_LADY
	msgbox GoldenrodDeptStore_Text_5FReceptionistDone, MSGBOX_DEFAULT
	release
	end

GoldenrodDeptStore5_EventScript_ReceptionistDone::
	msgbox GoldenrodDeptStore_Text_5FReceptionistDone, MSGBOX_DEFAULT
	release
	end

GoldenrodDeptStore_Text_5FReceptionistNotYet::
	.string "It's still getting used to you.\p"
	.string "Come back when you two are closer.\n"
	.string "I may have something for you then.$"

GoldenrodDeptStore_Text_5FReceptionistLovesYou::
	.string "It loves you very much!\n"
	.string "This TM is perfect for it.$"

GoldenrodDeptStore_Text_5FReceptionistUnhappy::
	.string "It looks rather unhappy…\n"
	.string "Maybe this TM suits it better.$"

GoldenrodDeptStore_Text_5FReceptionistDone::
	.string "I hope you and your POKéMON\n"
	.string "grow even closer.$"

GoldenrodDeptStore5_EventScript_Girl::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_Girl, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_Girl::
	.string "The lady gave me RETURN!\n"
	.string "My POKéMON must really like me!$"

GoldenrodDeptStore5_EventScript_Lass::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_5FLass, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_5FLass::
    .string "During the day, a lady comes to check\n"
    .string "out POKéMON.\p"
    .string "She even gives away TMs!$"

GoldenrodDeptStore5_EventScript_PokefanM::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_5FPokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_5FPokefanM::
    .string "You can't rename a POKéMON you get\n"
    .string "in a trade.\p"
    .string "The name is a reflection of the\n"
    .string "original TRAINER's feelings for it.$"

SE_J_GoldenrodCity_DepartmentStore_5F_hns_GoldenrodDeptStore5_EventScript_Clerk::
	msgbox gText_HowMayIServeYou, MSGBOX_NPC
	end

GoldenrodDeptStore5_EventScript_Sign::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_5FDirectory, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_5FDirectory::
    .string "Customize Your POKéMON\p"
    .string "5F TM CORNER$"
