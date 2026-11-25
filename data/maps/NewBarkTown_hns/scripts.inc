NewBarkTown_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SE_EventScript_OroNewBarkOnTransition
	.byte 0

NewBarkTown_Text_FatManState3::
	.string "Yo! Welcome to NEW BARK TOWN!\p"
	.string "I hear PROF.ELM discovered some\n"
	.string "new POKéMON.$"

SE_J_NewBarkTown_hns_NewBarkTown_EventScript_FatMan::
	msgbox NewBarkTown_Text_FatManState3, MSGBOX_NPC
	end

NewBarkTown_Text_LassState5::
	.string "You came all the way from HOENN?\n"
	.string "Your family must miss you!$"

SE_J_NewBarkTown_hns_NewBarkTown_EventScript_Lass::
	msgbox NewBarkTown_Text_LassState5, MSGBOX_NPC
	end

NewBarkTown_EventScript_Wooper::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WOOPER, CRY_MODE_NORMAL
	msgbox NewBarkTown_Text_Wooper, MSGBOX_DEFAULT
	waitmoncry
	release
	end

NewBarkTown_Text_Wooper::
	.string "WOOPER: Woooooop.$"

NewBarkTown_EventScript_TownSign::
	msgbox NewBarkTown_Text_Sign, MSGBOX_SIGN
	closemessage
	end

NewBarkTown_Text_Sign::
	.string "NEW BARK TOWN\p"
	.string "The Town Where the Winds of\n"
	.string "a New Beginning Blow$"

NewBarkTown_EventScript_Door::
	msgbox NewBarkTown_Text_Door, MSGBOX_SIGN
	end

NewBarkTown_Text_Door::
	.string "The door is locked.$"

NewBarkTown_EventScript_PlayersHouseMailbox::
	msgbox NewBarkTown_Text_PlayersHouse, MSGBOX_SIGN
	end

NewBarkTown_Text_PlayersHouse::
	.string "ORO'S HOUSE$"

NewBarkTown_EventScript_ElmsHouseMailbox::
	msgbox NewBarkTown_Text_ElmsHouse, MSGBOX_SIGN
	end

NewBarkTown_Text_ElmsHouse::
	.string "PROF.ELM'S HOUSE$"

NewBarkTown_EventScript_LabSign::
	msgbox NewBarkTown_Text_LabSign, MSGBOX_SIGN
	end

NewBarkTown_Text_LabSign::
	.string "PROF.ELM'S LAB$"
