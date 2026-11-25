PalPark_Lobby_sinnoh_MapScripts::
	.byte 0

@ Super Emerald: the PAL PARK opens after the Sinnoh League. Its four areas hold the
@ regional forms (Hisui, Galar and Paldea) that live nowhere else in the game.

PalPark_Lobby_EventScript_Receptionist::
	lock
	faceplayer
	goto_if_unset FLAG_SE_SINNOH_LEAGUE_CLEARED, PalPark_Lobby_EventScript_ReceptionistClosed
	msgbox PalPark_Lobby_Text_Welcome, MSGBOX_DEFAULT
	release
	end

PalPark_Lobby_EventScript_ReceptionistClosed::
	msgbox PalPark_Lobby_Text_Closed, MSGBOX_DEFAULT
	release
	end

PalPark_Lobby_EventScript_Guard::
	msgbox PalPark_Lobby_Text_Guard, MSGBOX_NPC
	end

PalPark_Lobby_EventScript_HisuiResearcher::
	lock
	faceplayer
	goto_if_set FLAG_SE_GIFT_STARTERS_HISUI, PalPark_Lobby_EventScript_HisuiAfter
	goto_if_unset FLAG_SE_SINNOH_LEAGUE_CLEARED, PalPark_Lobby_EventScript_HisuiBefore
	specialvar VAR_RESULT, ScriptHasRoomForThreeMons
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_StarterNoRoom
	msgbox PalPark_Lobby_Text_HisuiGift, MSGBOX_DEFAULT
	givemon SPECIES_DECIDUEYE_HISUI, 40
	bufferspeciesname STR_VAR_1, SPECIES_DECIDUEYE_HISUI
	call SE_EventScript_StarterReceived
	givemon SPECIES_TYPHLOSION_HISUI, 40
	bufferspeciesname STR_VAR_1, SPECIES_TYPHLOSION_HISUI
	call SE_EventScript_StarterReceived
	givemon SPECIES_SAMUROTT_HISUI, 40
	bufferspeciesname STR_VAR_1, SPECIES_SAMUROTT_HISUI
	call SE_EventScript_StarterReceived
	setflag FLAG_SE_GIFT_STARTERS_HISUI
	msgbox PalPark_Lobby_Text_HisuiGiven, MSGBOX_DEFAULT
	release
	end

PalPark_Lobby_EventScript_HisuiBefore::
	msgbox PalPark_Lobby_Text_HisuiBefore, MSGBOX_DEFAULT
	release
	end

PalPark_Lobby_EventScript_HisuiAfter::
	msgbox PalPark_Lobby_Text_HisuiAfter, MSGBOX_DEFAULT
	release
	end

PalPark_Lobby_EventScript_GalarTourist::
	msgbox PalPark_Lobby_Text_GalarTourist, MSGBOX_NPC
	end

PalPark_Lobby_EventScript_PaldeaFan::
	msgbox PalPark_Lobby_Text_PaldeaFan, MSGBOX_NPC
	end

PalPark_Lobby_Text_Welcome:
	.string "Welcome to the PAL PARK!\p"
	.string "POKéMON from faraway lands and\n"
	.string "long-gone times live in our park.\p"
	.string "You'll find them in the FIELD,\n"
	.string "the FOREST, up on the HIGHLANDS\l"
	.string "and in the LAKE.\p"
	.string "Catch them with your own BALLS.\n"
	.string "Please enjoy your visit!$"

PalPark_Lobby_Text_Closed:
	.string "Welcome to the PAL PARK!\p"
	.string "I'm sorry, the park is getting ready\n"
	.string "for its new residents.\p"
	.string "We'll open it to the TRAINER who\n"
	.string "becomes SINNOH's CHAMPION.$"

PalPark_Lobby_Text_Guard:
	.string "The PAL PARK isn't open yet.\p"
	.string "Our new POKéMON are still settling\n"
	.string "in. Only the SINNOH CHAMPION may\l"
	.string "go through before the opening.$"

PalPark_Lobby_Text_HisuiBefore:
	.string "I study POKéMON of HISUI, the\n"
	.string "land SINNOH was long, long ago.\p"
	.string "The forms of that age are living in\n"
	.string "the park now. Isn't it wonderful?$"

PalPark_Lobby_Text_HisuiGift:
	.string "You're the CHAMPION, aren't you?\n"
	.string "I study POKéMON of ancient HISUI.\p"
	.string "These three grew up the HISUIAN way,\n"
	.string "but they long to see the world.\p"
	.string "DECIDUEYE, TYPHLOSION and SAMUROTT…\n"
	.string "Please take all three with you!$"

PalPark_Lobby_Text_HisuiGiven:
	.string "In HISUI, POKéMON and people learned\n"
	.string "to live together, step by step.\p"
	.string "I'm sure they'll learn a lot\n"
	.string "travelling with you!$"

PalPark_Lobby_Text_HisuiAfter:
	.string "In the park you'll meet HISUIAN\n"
	.string "GROWLITHE, ZORUA, SNEASEL…\p"
	.string "Some of them only evolve the way\n"
	.string "they used to, with the right item!$"

PalPark_Lobby_Text_GalarTourist:
	.string "I came all the way from GALAR!\p"
	.string "Our SLOWPOKE are special. Give one\n"
	.string "a GALARICA CUFF or a GALARICA WREATH\l"
	.string "and it will evolve.\p"
	.string "I dropped both in the park…\n"
	.string "I hope someone finds them!$"

PalPark_Lobby_Text_PaldeaFan:
	.string "There are three kinds of TAUROS\n"
	.string "from PALDEA running in the FIELD!\p"
	.string "And PALDEAN WOOPER swim in the\n"
	.string "LAKE. I want them all!$"
