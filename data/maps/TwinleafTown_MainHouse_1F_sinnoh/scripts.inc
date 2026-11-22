TwinleafTown_MainHouse_1F_sinnoh_MapScripts::
	.byte 0


@ Super Emerald: the player is a TRAINER from HOENN, not this family's child
TwinleafTown_MainHouse_1F_EventScript_Mom::
	lock
	faceplayer
	msgbox TwinleafTown_MainHouse_1F_Text_SNMomRest, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox TwinleafTown_MainHouse_1F_Text_MomTalk, MSGBOX_DEFAULT
	release
	end

TwinleafTown_MainHouse_1F_Text_SNMomRest::
	.string "WOMAN: Oh! You must be the CHAMPION\n"
	.string "from HOENN everyone is talking about!\p"
	.string "My son is out traveling with his\n"
	.string "friend BARRY, so the house is so\l"
	.string "quiet…\p"
	.string "Please, take a quick rest here.$"

TwinleafTown_MainHouse_1F_Text_MomTalk::
	.string "WOMAN: Always treat your POKéMON\n"
	.string "with kindness.\p"
	.string "Your POKéMON work hard, not for\n"
	.string "themselves, but for you!$"

TwinleafTown_MainHouse_1F_EventScript_BarrysMom::
	msgbox TwinleafTown_MainHouse_1F_Text_BarrysMom2, MSGBOX_NPC
	end

TwinleafTown_MainHouse_1F_Text_BarrysMom2::
	.string "BARRY's mom: Have you met my son?\p"
	.string "He's always in a hurry. Even when\n"
	.string "he comes home, he barely has time\l"
	.string "to say hello!$"
