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
	.string "My child is out traveling with\n"
	.string "BARRY, so the house is so quiet…\p"
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
	.string "{PLAYER}'s mom: Let me think…\p"
	.string "Knowing my boy, he would probably head\n"
	.string "straight to JUBILIFE CITY…\p"
	.string "OK, please take that to my {PLAYER}.\p"
	.string "MOM: Bye-bye, {PLAYER}! Enjoy your\n"
	.string "adventure!$"
