Route36_hns_MapScripts::
	.byte 0

Route36_EventScript_Lass::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_SUDOWOODO, Route36_EventScript_Lass2
	msgbox Route36_Text_Lass1, MSGBOX_DEFAULT
	closemessage
	release
	end

Route36_Text_Lass1::
	.string "Be careful at night on this route!\p"
	.string "I saw a POKéMON that looked like\n"
	.string "GROWLITHE, but it had a scary aura\l"
	.string "to it.$"

Route36_EventScript_Lass2::
	msgbox Route36_Text_Lass2_ClearedSudowoodo, MSGBOX_DEFAULT
	closemessage
	release
	end

Route36_Text_Lass2_ClearedSudowoodo::
	.string "That odd tree disappeared without\n"
	.string "a trace.\p"
	.string "Oh! That tree was really a\n"
	.string "POKéMON?$"

Route36_Text_MeetArthur::
    .string "ARTHUR: Thursday belongs to me.\p"
    .string "My brothers and sisters each have a\n"
    .string "favorite spot. ROUTE 36 is mine.$"

SE_J_Route36_hns_Route36_EventScript_Arthur::
	msgbox Route36_Text_MeetArthur, MSGBOX_NPC
	end

Route36_Text_RockSmashGuy1::
	.string "Wa-hey!\p"
	.string "I was going to snap that tree\n"
	.string "with my straight-arm punch.\p"
	.string "But I couldn't! I'm a failure!$"

SE_J_Route36_hns_Route36_EventScript_RockSmashGuy::
	msgbox Route36_Text_RockSmashGuy1, MSGBOX_NPC
	end

Route36_EventScript_Mark::
	trainerbattle_single TRAINER_MARK_HNS, Route36_Text_PsychicMarkSeen, Route36_Text_PsychicMarkBeaten
	msgbox Route36_Text_PsychicMarkAfter, MSGBOX_AUTOCLOSE
	end

Route36_Text_PsychicMarkAfter::
	.string "I'd be strong if only I could tell\n"
	.string "what my opponent was thinking.$"

Route36_Text_PsychicMarkBeaten::
	.string "I misread you!$"

Route36_Text_PsychicMarkSeen::
	.string "I'm going to read your thoughts!$"

Route36_Text_SchoolboyAlan1Seen::
	.string "Thanks to my studies, I'm ready\n"
	.string "for any POKéMON!$"

Route36_Text_SchoolboyAlan1Beaten::
	.string "Oops! Computation error?$"

Route36_Text_SchoolboyAlanAfter::
	.string "Darn. I study five hours a day too.\p"
	.string "There's more to learning than just\n"
	.string "reading books.$"

SE_J_Route36_hns_Route36_EventScript_Schoolboy::
	trainerbattle_single TRAINER_ALAN_HNS, Route36_Text_SchoolboyAlan1Seen, Route36_Text_SchoolboyAlan1Beaten
	msgbox Route36_Text_SchoolboyAlanAfter, MSGBOX_AUTOCLOSE
	end

Route36_EventScript_Sign::
	lock
	msgbox Route36_Text_Sign_RuinsNorth, MSGBOX_SIGN
	closemessage
	release
	end

Route36_Text_Sign_RuinsNorth::
	.string "RUINS OF ALPH\n"
	.string "NORTH ENTRANCE$"

Route36_EventScript_Sign2::
	lock
	msgbox Route36_Text_Tips1, MSGBOX_SIGN
	closemessage
	release
	end

Route36_Text_Tips1::
	.string "TRAINER TIPS\n"
	.string "POKéMON stats vary--even within\l"
	.string "the same species.\p"
	.string "Their stats may be similar at first.\p"
	.string "However, differences will become\n"
	.string "pronounced as the POKéMON grow.$"
