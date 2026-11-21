CherrygroveCity_hns_MapScripts::
	.byte 0


CherrygroveCity_Text_GuideGentIntro::
	.string "You're a rookie TRAINER,\n"
	.string "aren't you? I can tell!\p"
	.string "That's OK! Everyone is a\n"
	.string "rookie at some point!\p"
	.string "If you'd like, I can teach\n"
	.string "you a few things.$"

SE_J_CherrygroveCity_hns_CherryGroveCity_EventScript_TriggerGent_Top::
	msgbox CherrygroveCity_Text_GuideGentIntro, MSGBOX_NPC
	end

CherryGroveCity_EventScript_Fisherman::
	lock
	faceplayer
	goto_if_set FLAG_GOT_MYSTICWATER, CherryGroveCity_EventScript_Fisherman2
	msgbox CherrygroveCity_Text_MysticWaterGuyBefore, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CherryGroveCity_EventScript_Fisherman2
	giveitem ITEM_MYSTIC_WATER
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull 
	closemessage
	setflag FLAG_GOT_MYSTICWATER
	release
	end

CherryGroveCity_EventScript_Fisherman2::
	msgbox CherrygroveCity_Text_MysticWaterGuyAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

CherrygroveCity_Text_MysticWaterGuyAfter::
	.string "Back to fishing for me, then.$"

CherrygroveCity_Text_MysticWaterGuyBefore::
	.string "A POKéMON I caught had an\n"
	.string "item.\p"
	.string "I think it's MYSTIC WATER.\p"
	.string "I don't need it, so do you\n"
	.string "want it?$"

CherryGroveCity_EventScript_Boy::
	lock
	faceplayer
	goto_if_set FLAG_SYS_POKEDEX_GET, CherryGroveCity_EventScript_Boy2
	msgbox CherrygroveCity_Text_YoungsterNoPokedex, MSGBOX_DEFAULT
	closemessage
	release
	end

CherrygroveCity_Text_YoungsterNoPokedex::
	.string "MR. POKéMON's house is still\n"
	.string "farther up ahead.$"

CherryGroveCity_EventScript_Boy2::
	msgbox CherrygroveCity_Text_YoungsterHavePokedex, MSGBOX_DEFAULT
	closemessage
	release
	end

CherrygroveCity_Text_YoungsterHavePokedex::
	.string "I battled the TRAINERS on the\n"
	.string "road.\p"
	.string "My POKéMON lost. They're a\n"
	.string "mess! I must take them to a\l"
	.string "POKéMON CENTER.$"

CherryGroveCity_EventScript_Lass::
	lock
	faceplayer
	msgbox CherrygroveCity_Text_TeacherHaveMapCard, MSGBOX_DEFAULT
	closemessage
	release
	end

CherrygroveCity_Text_TeacherHaveMapCard::
	.string "When you're with POKéMON,\n"
	.string "going anywhere is fun.$"

CherryGroveCity_EventScript_Corsola::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CORSOLA, CRY_MODE_NORMAL
	msgbox CherryGroveCity_Text_Corsola, MSGBOX_DEFAULT
	waitmoncry
	release
	end

CherryGroveCity_Text_Corsola::
	.string "CORSOLA: CORSOLA! La!$"

CherryGroveCity_EventScript_Staryu::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_STARYU, CRY_MODE_NORMAL
	msgbox CherryGroveCity_Text_Staryu, MSGBOX_DEFAULT
	waitmoncry
	release
	end

CherryGroveCity_Text_Staryu::
	.string "STARYU: Yuuuuuuuu.$"

CherryGroveCity_EventScript_Krabby::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_KRABBY, CRY_MODE_NORMAL
	msgbox CherryGroveCity_Text_Krabby, MSGBOX_DEFAULT
	waitmoncry
	release
	end

CherryGroveCity_Text_Krabby::
	.string "KRABBY: KOOOOKEEE!$"

CherryGroveCity_EventScript_Sign::
	lock
	msgbox CherrygroveCity_Text_CitySign, MSGBOX_SIGN
	closemessage
	release
	end	

CherrygroveCity_Text_CitySign::
	.string "CHERRYGROVE CITY\p"
	.string "The City of Cute, Fragrant\n"
	.string "Flowers$"
