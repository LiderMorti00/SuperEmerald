BlackthornCity_hns_MapScripts::
	.byte 0


BlackthornCity_EventScript_Youngster::
	msgbox BlackthornYoungsterText, MSGBOX_NPC
	end

BlackthornYoungsterText::
	.string "Dragon masters all come from the city\n"
	.string "of BLACKTHORN.$"

BlackthornCity_Text_ClairIsBeaten::
	.string "You defeated CLAIR?\p"
	.string "That's amazing!\p"
	.string "I've never heard of her losing to\n"
	.string "anyone other than LANCE.$"

SE_J_BlackthornCity_hns_BlackthornCity_EventScript_GymBoy::
	msgbox BlackthornCity_Text_ClairIsBeaten, MSGBOX_NPC
	end

BlackthornCity_MeetSantosText::
	.string "SANTOS: …\p"
	.string "I'm SANTOS of the weekday family.\p"
	.string "Take a guess.$"

SE_J_BlackthornCity_hns_BlackthornCity_EventScript_Santos::
	msgbox BlackthornCity_MeetSantosText, MSGBOX_NPC
	end

BlackthornCity_EventScript_CoolTrainerF2::
	msgbox BlackthornCooltrainerF2Text, MSGBOX_NPC
	end

BlackthornCooltrainerF2Text::
	.string "Wow, you came through the ICE PATH?\p"
	.string "You must be a real hotshot trainer!$"

BlackthornCity_EventScript_CoolTrainerF::
	msgbox BlackthornCooltrainerF1Text, MSGBOX_NPC
	end

BlackthornCooltrainerF1Text::
	.string "Are you going to make your POKéMON\n"
	.string "remember some moves?$"

BlackthornCity_EventScript_BlackBelt::
	msgbox BlackBeltText_VoicesInMyHead, MSGBOX_NPC
	end

BlackBeltText_VoicesInMyHead::
	.string "Arooo! Voices in my head!\p"
	.string "Huh? I'm listening to my radio!$"

BlackthornGrampsGrantsEntryText::
	.string "If CLAIR allows it, her grand-\n"
	.string "father--our MASTER--will also.\p"
	.string "You may enter.$"

SE_J_BlackthornCity_hns_BlackThornCity_EventScript_Sage::
	msgbox BlackthornGrampsGrantsEntryText, MSGBOX_NPC
	end

BlackthornCity_EventScript_DragonsDenSign::
	msgbox BlackthornCity_Text_DragonDenSign, MSGBOX_SIGN
	end

BlackthornCity_Text_DragonDenSign::
	.string "DRAGON'S DEN AHEAD$"

BlackthornCity_EventScript_GymSign::
	msgbox BlackthornGymSignText, MSGBOX_SIGN
	end

BlackthornGymSignText::
	.string "BLACKTHORN CITY POKéMON GYM\n"
	.string "LEADER: CLAIR\p"
	.string "The Blessed User of Dragon POKéMON$"

BlackthornCity_EventScript_MoveHouseSign::
	msgbox BlackthornCity_Text_MoveDeletersHouseSign, MSGBOX_SIGN
	end

BlackthornCity_Text_MoveDeletersHouseSign::
	.string "MOVE BROS' HOUSE$"

BlackthornCity_EventScript_CitySign::
	msgbox BlackthornCitySignText, MSGBOX_SIGN
	end

BlackthornCitySignText::
	.string "BLACKTHORN CITY\p"
	.string "A Quiet Mountain Retreat$"
