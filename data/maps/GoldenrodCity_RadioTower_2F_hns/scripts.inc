GoldenrodCity_RadioTower_2F_hns_MapScripts::
	.byte 0


GoldenrodCity_RadioTower_2F_EventScript_Jigglypuff::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_JIGGLYPUFF, CRY_MODE_NORMAL
	msgbox GoldenrodCity_RadioTower_2F_Text_Jigglypuff, MSGBOX_DEFAULT
	waitmoncry
	release
	end

GoldenrodCity_RadioTower_2F_Text_Jigglypuff::
	.string "JIGGLYPUFF: Jiggly…$"

GoldenrodCity_RadioTower_2F_Text_Teacher::
	.string "Lullabies on the radio may make\n"
	.string "POKéMON sleep.$"

SE_J_GoldenrodCity_RadioTower_2F_hns_GoldenrodCity_RadioTower_2F_EventScript_Teacher::
	msgbox GoldenrodCity_RadioTower_2F_Text_Teacher, MSGBOX_NPC
	end

GoldenrodCity_RadioTower_2F_EventScript_Boy::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_2F_Text_SuperNerd, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_Text_SuperNerd::
	.string "You can listen to the radio\n"
	.string "anywhere. Tune in!$"

GoldenrodRaidoTower2_EventScript_Grunt3::
	trainerbattle_single TRAINER_GRUNT_3_HNS, GoldenrodCity_RadioTower_2F_Text_GruntM4Seen, GoldenrodCity_RadioTower_2F_Text_GruntM4Beaten
	msgbox GoldenrodCity_RadioTower_2F_Text_GruntM4After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_RadioTower_2F_Text_GruntM4After::
	.string "We won't let you ruin our plans\n"
	.string "for our comeback!$"

GoldenrodCity_RadioTower_2F_Text_GruntM4Beaten::
	.string "Gwah! Don't get cute!$"

GoldenrodCity_RadioTower_2F_Text_GruntM4Seen::
	.string "Three years ago, TEAM ROCKET was\n"
	.string "forced to disband.\p"
	.string "But we're making a comeback here!$"

GoldenrodRaidoTower2_EventScript_Grunt5::
	trainerbattle_single TRAINER_GRUNT_5_HNS, GoldenrodCity_RadioTower_2F_Text_GruntM6Seen, GoldenrodCity_RadioTower_2F_Text_GruntM6Beaten
	msgbox GoldenrodCity_RadioTower_2F_Text_GruntM6After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_RadioTower_2F_Text_GruntM6After::
	.string "Our EXECUTIVES are trying to take\n"
	.string "this place over.\p"
	.string "They have some big plan. I wonder\n"
	.string "what that is?$"

GoldenrodCity_RadioTower_2F_Text_GruntM6Beaten::
	.string "Arggh. I give up.$"

GoldenrodCity_RadioTower_2F_Text_GruntM6Seen::
	.string "Hey, hey! Keep out of our way!$"

GoldenrodRaidoTower2_EventScript_GruntF2::
	trainerbattle_single TRAINER_GRUNT_26_HNS, GoldenrodCity_RadioTower_2F_Text_GruntF2Seen, GoldenrodCity_RadioTower_2F_Text_GruntF2Beaten
	msgbox GoldenrodCity_RadioTower_2F_Text_GruntF2After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_RadioTower_2F_Text_GruntF2After::
	.string "You beat me, and I won't forget\n"
	.string "it!$"

GoldenrodCity_RadioTower_2F_Text_GruntF2Beaten::
	.string "Wh-who are you?$"

GoldenrodCity_RadioTower_2F_Text_GruntF2Seen::
	.string "Hahaha!\p"
	.string "How boring. It was far too easy\n"
	.string "to take over this place!\p"
	.string "Come on, keep me amused!$"

GoldenrodRaidoTower2_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_4_HNS, GoldenrodCity_RadioTower_2F_Text_GruntM5Seen, GoldenrodCity_RadioTower_2F_Text_GruntM5Beaten
	msgbox GoldenrodCity_RadioTower_2F_Text_GruntM5After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_RadioTower_2F_Text_GruntM5After::
	.string "We're not always evil. We just do\n"
	.string "whatever we like.$"

GoldenrodCity_RadioTower_2F_Text_GruntM5Beaten::
	.string "You think you're a hero?$"

GoldenrodCity_RadioTower_2F_Text_GruntM5Seen::
	.string "We're TEAM ROCKET, the exploiters\n"
	.string "of POKéMON!\p"
	.string "We love being evil! Scared?$"

GoldenrodCity_RadioTower_2F_Text_BuenaAskPassword::
	.string "BUENA: Hi there!\p"
	.string "So, do you know today's\n"
	.string "password?\p"
	.string "OK! Which one is it?$"

SE_J_GoldenrodCity_RadioTower_2F_hns_GoldenrodCity_RadioTower_2F_EventScript_Buena::
	msgbox GoldenrodCity_RadioTower_2F_Text_BuenaAskPassword, MSGBOX_NPC
	end

GoldenrodCity_RadioTower_2F_EventScript_Policeman::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_2F_Text_Policeman, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_Text_Policeman::
	.string "Restricted access beyond this\n"
	.string "point.$"

GoldenrodCity_RadioTower_2F_EventScript_Sign1::
	lock
	msgbox GoldenrodCity_RadioTower_2F_Text_SalesSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_Text_SalesSign::
	.string "2F SALES$"

GoldenrodCity_RadioTower_2F_EventScript_Sign2::
	lock
	msgbox GoldenrodCity_RadioTower_2F_Text_OakTalkSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_Text_OakTalkSign::
	.string "PROF.OAK'S POKéMON TALK\p"
	.string "The Hottest Show on the Air!$"
