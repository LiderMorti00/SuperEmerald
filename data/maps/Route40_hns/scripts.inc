Route40_hns_MapScripts::
	.byte 0


Route40_EventScript_Elaine::
	trainerbattle_single TRAINER_ELAINE_HNS, Route40_Text_SwimmerfElaineSeen, Route40_Text_SwimmerfElaineBeaten
	msgbox Route40_Text_SwimmerfElaineAfter, MSGBOX_AUTOCLOSE
	end

Route40_Text_SwimmerfElaineAfter::
	.string "I'd say I'm a better swimmer\n"
	.string "than you. Yeah!$"

Route40_Text_SwimmerfElaineBeaten::
	.string "I lost that one!$"

Route40_Text_SwimmerfElaineSeen::
	.string "Are you going to CIANWOOD?\p"
	.string "How about a quick battle\n"
	.string "first?$"

Route40_EventScript_Youngster::
	lock
	faceplayer
	msgbox Route40_Text_StandingYoungster, MSGBOX_DEFAULT
	closemessage
	release
	end

Route40_Text_StandingYoungster::
	.string "The gate here leads to the POKéMON\n"
	.string "WORLD TOURNAMENT.\p"
	.string "I like to watch TRAINERS from all\n"
	.string "over the world battle there!$"

Route40_EventScript_Woman1::
	lock
	faceplayer
	msgbox Route40_Text_Lass1, MSGBOX_DEFAULT
	closemessage
	release
	end

Route40_Text_Lass1::
	.string "Although you can't see it from here,\n"
	.string "CIANWOOD is across the sea.$"

Route40_EventScript_Simon::
	trainerbattle_single TRAINER_SIMON_HNS, Route40_Text_SwimmermSimonSeen, Route40_Text_SwimmermSimonBeaten
	msgbox Route40_Text_SwimmermSimonAfter, MSGBOX_AUTOCLOSE
	end

Route40_Text_SwimmermSimonAfter::
	.string "CIANWOOD CITY is a good\n"
	.string "distance away from here.$"

Route40_Text_SwimmermSimonBeaten::
	.string "OK! Uncle! I give!$"

Route40_Text_SwimmermSimonSeen::
	.string "You have to warm up before\n"
	.string "going into the water.\p"
	.string "That's basic.$"

Route40_EventScript_Paula::
	trainerbattle_single TRAINER_PAULA_HNS, Route40_Text_SwimmerfPaulaSeen, Route40_Text_SwimmerfPaulaBeaten
	msgbox Route40_Text_SwimmerfPaulaAfter, MSGBOX_AUTOCLOSE
	end

Route40_Text_SwimmerfPaulaAfter::
	.string "While I float like this,\n"
	.string "the waves carry me along.$"

Route40_Text_SwimmerfPaulaBeaten::
	.string "Ooh, I'm feeling dizzy!$"

Route40_Text_SwimmerfPaulaSeen::
	.string "No inner tube for me.\p"
	.string "I'm hanging on to a sea\n"
	.string "POKéMON!$"

Route40_EventScript_Randall::
	trainerbattle_single TRAINER_RANDALL_HNS, Route40_Text_SwimmermRandallSeen, Route40_Text_SwimmermRandallBeaten
	msgbox Route40_Text_SwimmermRandallAfter, MSGBOX_AUTOCLOSE
	end

Route40_Text_SwimmermRandallAfter::
	.string "Swimming exercises your\n"
	.string "entire body. It's healthy.$"

Route40_Text_SwimmermRandallBeaten::
	.string "Uh-oh. I lost…$"

Route40_Text_SwimmermRandallSeen::
	.string "Hey, you're young and fit!\p"
	.string "Don't ride your POKéMON!\n"
	.string "Swim!$"

Route40_Text_Monica::
	.string "MONICA: Glad to meet you.\n"
	.string "I'm MONICA of the WEEKDAY FAMILY.\p"
	.string "Monday is my favorite day. I like to\n"
	.string "start the week here by the sea.$"

SE_J_Route40_hns_Rotue40_EventScript_Monica::
	msgbox Route40_Text_Monica, MSGBOX_NPC
	end
