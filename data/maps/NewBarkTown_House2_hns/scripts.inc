NewBarkTown_House2_hns_MapScripts::
	.byte 0


NewBarkTown_House2_EventScript_ElmsSon::
	lock
	faceplayer
	msgbox NewBarkTown_House2_Text_ElmsSon, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_House2_Text_ElmsSon::
	.string "When I grow up, I'm going to\n"
	.string "help my dad!\p"
	.string "I'm going to be a great\n"
	.string "POKéMON professor!$"

NewBarkTown_House2_EventScript_ElmsWife::
	lock
	faceplayer
	msgbox NewBarkTown_House2_Text_ElmsWife, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_House2_Text_ElmsWife::
	.string "Oh, hello! You're the TRAINER from\n"
	.string "HOENN, aren't you?\p"
	.string "My husband's always so busy--I hope\n"
	.string "he's OK.\p"
	.string "When he's caught up in his POKéMON\n"
	.string "research, he even forgets to eat.$"
