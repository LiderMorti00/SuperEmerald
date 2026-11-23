CeruleanCity_House2_Frlg_MapScripts::
	.byte 0

CeruleanCity_House2_EventScript_Hiker::
	lock
	faceplayer
	goto_if_set FLAG_GOT_TM28_FROM_ROCKET, CeruleanCity_House2_EventScript_HikerGotTM28
	msgbox CeruleanCity_House2_Text_RocketsStoleTMForDig
	giveitem ITEM_TM28
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_TM28_FROM_ROCKET
	msgbox CeruleanCity_House2_Text_TeachDiglettDigWithoutTM
	release
	end

CeruleanCity_House2_EventScript_HikerGotTM28::
	msgbox CeruleanCity_House2_Text_TeachDiglettDigWithoutTM
	release
	end

CeruleanCity_House2_EventScript_Lass::
	msgbox CeruleanCity_House2_Text_TeamRocketTryingToDigIntoNoGood, MSGBOX_NPC
	end

CeruleanCity_House2_EventScript_WallHole::
	msgbox CeruleanCity_House2_Text_TeamRocketLeftWayOut, MSGBOX_SIGN
	end

CeruleanCity_House2_Text_RocketsStoleTMForDig::
	.string "Years ago, TEAM ROCKET broke into\n"
	.string "my house and stole a TM for DIG!\p"
	.string "The POLICE got it back for me,\n"
	.string "but I don't need it anymore.\p"
	.string "You look like a strong TRAINER.\n"
	.string "Here, you can have it!$"

CeruleanCity_House2_Text_TeachDiglettDigWithoutTM::
	.string "My DIGLETT learned how to DIG\n"
	.string "without a TM. It works just fine!$"

CeruleanCity_House2_Text_TeamRocketTryingToDigIntoNoGood::
	.string "TEAM ROCKET dug right through our\n"
	.string "wall back then. We never fixed it.$"

CeruleanCity_House2_Text_TeamRocketLeftWayOut::
	.string "A hole TEAM ROCKET dug long ago.$"

