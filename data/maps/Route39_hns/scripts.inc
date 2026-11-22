Route39_hns_MapScripts::
	.byte 0


Route39_EventScript_Norman::
	trainerbattle_single TRAINER_NORMAN_HNS, Route39_Text_PsychicNormanSeen, Route39_Text_PsychicNormanBeaten
	msgbox Route39_Text_PsychicNormanAfter, MSGBOX_AUTOCLOSE
	end

Route39_Text_PsychicNormanAfter::
	.string "You know how POKéMON have\n"
	.string "different abilities?\p"
	.string "People are like that too.\n"
	.string "Everyone has different\l"
	.string "potential.$"

Route39_Text_PsychicNormanBeaten::
	.string "Ooh, your POKéMON have\n"
	.string "potential.$"

Route39_Text_PsychicNormanSeen::
	.string "Let me see what your\n"
	.string "POKéMON are capable of.$"

Route39_EventScript_Ruth::
	trainerbattle_single TRAINER_RUTH_HNS, Route39_Text_PokefanFRuthSeen, Route39_Text_PokefanFRuthBeaten
	msgbox Route39_Text_PokefanFRuthAfter, MSGBOX_AUTOCLOSE
	end

Route39_Text_PokefanFRuthAfter::
	.string "Do you know about baby\n"
	.string "POKéMON?\p"
	.string "I bet they're just adorable!$"

Route39_Text_PokefanFRuthBeaten::
	.string "I don't mind losing.$"

Route39_Text_PokefanFRuthSeen::
	.string "Such darling POKéMON.\p"
	.string "Let's show our POKéMON\n"
	.string "together at the same time.$"

Route39_Text_PokefanMDerekSeen::
	.string "This is a good time to brag\n"
	.string "about my PIKACHU!$"

Route39_Text_PokefanMDerekBeaten::
	.string "I had no time to show off\n"
	.string "PIKACHU…$"

Route39_Text_PokefanMDerekAfter::
	.string "I'm not listening to your\n"
	.string "bragging!\p"
	.string "We POKé FANS have a policy\n"
	.string "of not listening to bragging!$"

SE_J_Route39_hns_Route39_EventScript_Derek::
	trainerbattle_single TRAINER_DEREK_HNS, Route39_Text_PokefanMDerekSeen, Route39_Text_PokefanMDerekBeaten
	msgbox Route39_Text_PokefanMDerekAfter, MSGBOX_AUTOCLOSE
	end

Route39_EventScript_Eugene::
	trainerbattle_single TRAINER_EUGENE_HNS, Route39_Text_SailorEugeneSeen, Route39_Text_SailorEugeneBeaten
	msgbox Route39_Text_SailorEugeneAfter, MSGBOX_AUTOCLOSE
	end

Route39_Text_SailorEugeneAfter::
	.string "My POKéMON were caught and\n"
	.string "raised overseas.\p"
	.string "They're my companions on\n"
	.string "those long voyages.$"

Route39_Text_SailorEugeneBeaten::
	.string "Awaaargh!$"

Route39_Text_SailorEugeneSeen::
	.string "I just got back to OLIVINE.\p"
	.string "So how about a POKéMON battle?$"

Route39_EventScript_Miltank::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MILTANK, CRY_MODE_NORMAL
	msgbox Route39_Text_Miltank, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route39_Text_Miltank::
	.string "MILTANK: Mooo!$"

SE_J_Route39_hns_Route39_EventScript_Item_TM::
	end

Route39_EventScript_Jamie::
	trainerbattle_single TRAINER_JAMIE_HNS, Route39_Text_PokefanFJaimeSeen, Route39_Text_PokefanFJaimeBeaten
	msgbox Route39_Text_PokefanFJaimeAfter, MSGBOX_AUTOCLOSE
	end

Route39_Text_PokefanFJaimeAfter::
	.string "I met UMBREON at night right\n"
	.string "here on ROUTE 39.\p"
	.string "I'm not sure why, but it\n"
	.string "seems to like it when I\l"
	.string "train here.\p"
	.string "It seems to become friendlier\n"
	.string "by training here than\l"
	.string "anywhere else.$"

Route39_Text_PokefanFJaimeBeaten::
	.string "Oh, how disappointing…$"

Route39_Text_PokefanFJaimeSeen::
	.string "You came at just the right\n"
	.string "time.\p"
	.string "Let's battle.$"

Route39_EventScript_Item_Nugget::
	finditem ITEM_BIG_NUGGET
	end

Route39_EventScript_Woman::
	lock
	faceplayer
	msgbox Route39_Text_Woman, MSGBOX_DEFAULT
	closemessage
	release
	end

Route39_Text_Woman::
	.string "That shadow… Maybe it was a giant\n"
	.string "PIDGEY?$"

Route39_EventScript_Sign3::
	lock
	msgbox Route39_Text_TrainerTips, MSGBOX_SIGN
	closemessage
	release
	end

Route39_Text_TrainerTips::
	.string "TRAINER TIPS\p"
	.string "Use HEADBUTT on trees to shake\n"
	.string "POKéMON out.\p"
	.string "Different kinds of POKéMON\n"
	.string "drop out of trees.\p"
	.string "Only some trees shake when\n"
	.string "you hit them!$"

Route39_EventScript_Sign1::
	lock
	msgbox Route39_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route39_Text_Sign::
	.string "ROUTE 39\p"
	.string "OLIVINE CITY - ECRUTEAK CITY$"

Route39_EventScript_Sign2::
	lock
	msgbox Route39_Text_MoomooFarmSign, MSGBOX_SIGN
	closemessage
	release
	end

Route39_Text_MoomooFarmSign::
	.string "MOOMOO FARM\p"
	.string "Enjoy Our Fresh and Tasty Milk$"
