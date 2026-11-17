GoldenrodCity_DepartmentStore_5F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SE_GoldenrodElevator_OnFrame
	.byte 0


GoldenrodDeptStore_Text_5FReceptionistOhYourMon::
    .string "Hello. Oh, your POKéMON…$"

SE_J_GoldenrodCity_DepartmentStore_5F_hns_GoldenrodDeptStore5_EventScript_Receptionist::
	msgbox GoldenrodDeptStore_Text_5FReceptionistOhYourMon, MSGBOX_NPC
	end

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
    .string "original trainer's feelings for it.$"

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
