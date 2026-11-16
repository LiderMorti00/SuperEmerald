GoldenrodCity_DepartmentStore_6F_hns_MapScripts::
	.byte 0


GoldenrodDeptStore6_EventScript_Nerd::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_6FSuperNerd, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_6FSuperNerd::
    .string "If you're tired, try the vending\n"
    .string "machine's drinks.\p"
    .string "Your POKéMON will love them too.$"

GoldenrodDeptStore6_EventScript_Lass::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_6FLass, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_6FLass::
    .string "Do you listen to LUCKY CHANNEL?\p"
    .string "They say if you want to win,\n"
	.string "you should trade POKéMON with as\l"
    .string "many people as possible to get\l"
    .string "different ID numbers.\p"
	.string "However, trading isn't as widely\n"
	.string "available as it once was.$"

GoldenrodCity_DepartmentStore_6F_Text_ThisIsntAMon::
	.string "Uh, no, I don't think so.\n"
	.string "That isn't a {STR_VAR_1}.$"

SE_J_GoldenrodCity_DepartmentStore_6F_hns_GoldenrodCity_DepartmentStore_6F_EventScript_Jose::
	msgbox GoldenrodCity_DepartmentStore_6F_Text_ThisIsntAMon, MSGBOX_NPC
	end

GoldenrodDeptStore6_EventScript_Whitney::
	lock
	faceplayer
	msgbox GoldenrodDeptStore6_Text_Whitney, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_DEPTSTORE_WHITNEY
	removeobject LOCALID_STORE_WHITNEY
	fadescreenswapbuffers FADE_FROM_BLACK
	clearflag FLAG_HIDE_DOJO_WHITNEY
	release
	end

GoldenrodDeptStore6_Text_Whitney::
	.string "{PLAYER}! Fancy seeing you here!\p"
	.string "I'm picking up something for\n"
	.string "my MILTANK.\p"
	.string "If you want another battle, come to\n"
	.string "the FIGHTING DOJO!$"

SE_J_GoldenrodCity_DepartmentStore_6F_hns_GoldenrodDeptStore_EventScript_VendingMachine::
	msgbox GoldenrodDeptStore_Text_WhichDrinkWouldYouLike, MSGBOX_SIGN
	end

GoldenrodDeptStore6_EventScript_Sign::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_6FDirectory, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_6FDirectory::
    .string "Take a Break from Shopping!\p"
    .string "6F TRANQUIL SQUARE$"
