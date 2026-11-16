BlackthornCity_Gym_hns_MapScripts::
	.byte 0


BlackthornGym_EventScript_Mike::
	trainerbattle_single TRAINER_MIKE_HNS, BlackthornGym_Text_CooltrainermMikeSeenText, BlackthornGym_Text_CooltrainermMikeBeatenText
	msgbox BlackthornGym_Text_CooltrainermMikeAfterBattleText, MSGBOX_AUTOCLOSE
	end

BlackthornGym_Text_CooltrainermMikeAfterBattleText::
    .string "I know my short-comings now.\p"
    .string "Thanks for showing me!$"

BlackthornGym_Text_CooltrainermMikeBeatenText::
    .string "That's odd.$"

BlackthornGym_Text_CooltrainermMikeSeenText::
    .string "My chance of losing? Not even one\n"
    .string "percent!$"

BlackthornGym_EventScript_Paul::
	trainerbattle_single TRAINER_PAUL_HNS, BlackthornGym_Text_CooltrainermPaulSeenText, BlackthornGym_Text_CooltrainermPaulBeatenText
	msgbox BlackthornGym_Text_CooltrainermPaulAfterBattleText, MSGBOX_AUTOCLOSE
	end

BlackthornGym_Text_CooltrainermPaulAfterBattleText::
    .string "LANCE told you that he'd like to\n"
    .string "see you again?\p"
    .string "Not a chance!$"

BlackthornGym_Text_CooltrainermPaulBeatenText::
    .string "My dragon POKéMON lost?$"

BlackthornGym_Text_CooltrainermPaulSeenText::
    .string "Your first battle against dragons?\p"
    .string "I'll show you how tough they are!$"

BlackthornGym_EventScript_Lola::
	trainerbattle_single TRAINER_LOLA_HNS, BlackthornGym_Text_CooltrainerfLolaSeenText, BlackthornGym_Text_CooltrainerfLolaBeatenText
	msgbox BlackthornGym_Text_CooltrainerfLolaAfterBattleText, MSGBOX_AUTOCLOSE
	end

BlackthornGym_Text_CooltrainerfLolaAfterBattleText::
    .string "Dragons are weak against DRAGON-\n"
    .string "type moves.$"

BlackthornGym_Text_CooltrainerfLolaBeatenText::
    .string "Way to go!$"

BlackthornGym_Text_CooltrainerfLolaSeenText::
    .string "Dragons are sacred POKéMON.\p"
    .string "They are full of life energy.\p"
    .string "If you're not serious, you won't\n"
    .string "be able to beat them.$"

BlackthornGym_Text_ClairIntroText::
    .string "I am CLAIR.\p"
    .string "The world's best dragon master.\p"
    .string "I can hold my own against even the\n"
    .string "POKéMON LEAGUE's ELITE FOUR.\p"
    .string "Do you still want to take me on?\p"
    .string "…Fine. Let's do it!\p"
    .string "As a GYM LEADER, I will use my full\n"
    .string "power against any opponent!$"

SE_J_BlackthornCity_Gym_hns_BlackthornGym_EventScript_Clair::
	msgbox BlackthornGym_Text_ClairIntroText, MSGBOX_NPC
	end

BlackthornGym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_BLACKTHORN_GYM, BlackthornGym_EventScript_GymGuy2
	msgbox BlackthornGym_Text_GuideText, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackthornGym_Text_GuideText::
    .string "Yo! CHAMP in making!\p"
    .string "It's been a long journey, but we\n"
    .string "are almost done! Count on me!\p"
    .string "While CLAIR looks up to the Dragon\n"
    .string "Master, LANCE, she's managed to\l"
    .string "create her own identity with a\l"
    .string "team consisting of dragons from\l"
    .string "the sea.\p"
    .string "Dragons are supposed to be\n"
    .string "weak against ICE-type moves,\l"
    .string "but you'll need some DRAGON-type\l"
	.string "or FAIRY-type moves of your own if\l"
    .string "you want to win.$"
    .string "You got this!$"

BlackthornGym_EventScript_GymGuy2::
	goto_if_set FLAG_JOHTO_BADGE8_GET, BlackthornGym_EventScript_GymGuy3
	msgbox BlackthornGym_Text_GuideGotoDragonsDen, MSGBOX_DEFAULT
	release
	end

BlackthornGym_Text_GuideGotoDragonsDen::
	.string "You were great to beat CLAIR!\p"
    .string "She can be a bit of a sore loser,\n"
	.string "though\p"
    .string "Sounds like you need to head to the\n"
    .string "DRAGON'S DEN if you want that GYM BADGE!$"

BlackthornGym_EventScript_GymGuy3::
	msgbox BlackthornGym_Text_GuideWinText, MSGBOX_DEFAULT
	release
	end	

BlackthornGym_Text_GuideWinText::
    .string "You were great to beat CLAIR!\p"
    .string "All that's left is the POKéMON\n"
    .string "LEAGUE challenge.\p"
    .string "You're on the way to becoming the\n"
    .string "POKéMON CHAMPION!$"

BlackthornGym_EventScript_Fran::
	trainerbattle_single TRAINER_FRAN_HNS, BlackthornGym_Text_CooltrainerfFranSeenText, BlackthornGym_Text_CooltrainerfFranBeatenText
	msgbox BlackthornGym_Text_CooltrainerfFranAfterBattleText, MSGBOX_AUTOCLOSE
	end

BlackthornGym_Text_CooltrainerfFranAfterBattleText::
    .string "Uh-oh… CLAIR is going to be mad…$"

BlackthornGym_Text_CooltrainerfFranBeatenText::
    .string "Awww… I lost…$"

BlackthornGym_Text_CooltrainerfFranSeenText::
    .string "I can't allow a nameless trainer\n"
    .string "past me!\p"
    .string "CLAIR would be livid if I did!$"

BlackthornGym_EventScript_Cody::
	trainerbattle_single TRAINER_CODY_HNS, BlackthornGym_Text_CooltrainermCodySeenText, BlackthornGym_Text_CooltrainermCodyBeatenText
	msgbox BlackthornGym_Text_CooltrainermCodyAfterBattleText, MSGBOX_AUTOCLOSE
	end

BlackthornGym_Text_CooltrainermCodyAfterBattleText::
    .string "Members of our dragon-user clan\n"
    .string "can use dragon POKéMON only after\l"
    .string "our MASTER allows it.$"

BlackthornGym_Text_CooltrainermCodyBeatenText::
    .string "Rats! If only I had a DRAGONITE!$"

BlackthornGym_Text_CooltrainermCodySeenText::
    .string "I just got access to use DRAGON-\n"
    .string "type POKéMON!$"

BlackthornGym_EventScript_Statue::
	lock
	goto_if_set FLAG_JOHTO_BADGE8_GET, BlackthornGym_EventScript_Statue2
	msgbox BlackthornGym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackthornGym_Text_GymStatue::
	.string "BLACKTHORN CITY POKéMON GYM$"

BlackthornGym_EventScript_Statue2::
	msgbox BlackthornGym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackthornGym_Text_GymStatueCertified::
	.string "BLACKTHORN CITY POKéMON GYM\p"
	.string "CLAIR'S CERTIFIED TRAINERS:\n"
	.string "{PLAYER}$"
