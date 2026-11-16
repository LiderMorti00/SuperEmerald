Route34_DayCare_hns_MapScripts::
	.byte 0


Route34_Text_SeeWifeIfYoudLikeMeToRaiseMon::
	.string "I'm the DAY-CARE MAN.\p"
	.string "I help take care of the precious\n"
	.string "POKéMON of TRAINERS.\p"
	.string "If you'd like me to raise your POKéMON,\n"
	.string "have a word with my wife.$"

Route34_DayCare_Text_WouldYouLikeUsToRaiseAMon::
	.string "I'm the DAY-CARE LADY.\p"
	.string "We can raise POKéMON for you.\p"
	.string "Would you like us to raise one?$"

SE_J_Route34_DayCare_hns_Route34_DayCare_EventScript_DaycareWoman::
	msgbox Route34_DayCare_Text_WouldYouLikeUsToRaiseAMon, MSGBOX_NPC
	end

Route34_DayCare_EventScript_Ditto::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DITTO, CRY_MODE_NORMAL
	msgbox Route34_DayCare_Text_Ditto, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route34_DayCare_Text_Ditto::
	.string "DITTO: Tto!$"

Route34_DayCare_Text_ClerkBefore::
	.string "I'm the DAY-CARE couple's son.\p"
	.string "An ODD EGG was found with a TRAINER's\n"
	.string "POKéMON, but they didn't want it...\p"
	.string "I'd offer it to you...\n"
	.string "But how can I know you'll take good\l"
	.string "care of it?$"

SE_J_Route34_DayCare_hns_Route34_DayCare_EventScript_Clerk::
	msgbox Route34_DayCare_Text_ClerkBefore, MSGBOX_NPC
	end

Route34_DayCare_Text_Bookshelf1::
	.string "A BABY POKéMON encyclopedia!\p"
	.string "VOLUME 1: ALL ABOUT ABILITIES$"

SE_J_Route34_DayCare_hns_Route34_DayCare_Bookshelf1::
	msgbox Route34_DayCare_Text_Bookshelf1, MSGBOX_SIGN
	end

Route34_DayCare_Text_Bookshelf2::
	.string "A BABY POKéMON encyclopedia!\p"
	.string "VOLUME 2: TYPICAL TYPES$"

SE_J_Route34_DayCare_hns_Route34_DayCare_Bookshelf2::
	msgbox Route34_DayCare_Text_Bookshelf2, MSGBOX_SIGN
	end

Route34_DayCare_Text_Bookshelf4::
	.string "A BABY POKéMON encyclopedia!\p"
	.string "VOLUME 4: ADORABLE ACTIONS$"

SE_J_Route34_DayCare_hns_Route34_DayCare_Bookshelf4::
	msgbox Route34_DayCare_Text_Bookshelf4, MSGBOX_SIGN
	end

Route34_DayCare_Text_Bookshelf3::
	.string "A BABY POKéMON encyclopedia!\p"
	.string "VOLUME 3: BABIES' CRIES$"

SE_J_Route34_DayCare_hns_Route34_DayCare_Bookshelf3::
	msgbox Route34_DayCare_Text_Bookshelf3, MSGBOX_SIGN
	end
