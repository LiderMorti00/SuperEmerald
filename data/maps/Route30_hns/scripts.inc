Route30_hns_MapScripts::
	.byte 0

Route30_EventScript_Poliwag::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_POLIWAG, CRY_MODE_NORMAL
	msgbox Route30_Text_Poliwag, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route30_Text_Poliwag::
	.string "POLIWAG: Wag waag!$"

Route30_EventScript_Boy::
	lock
	faceplayer
	goto_if_set FLAG_J_ADVENTURE_STARTED, Route30_EventScript_Boy2
	msgbox Route30_Text_YoungsterDirectionsToMrPokemon, MSGBOX_DEFAULT
	closemessage
	release
	end

Route30_Text_YoungsterDirectionsToMrPokemon::
	.string "MR. POKéMON's house?\n"
	.string "It's a bit farther ahead.$"

Route30_EventScript_Boy2::
	lock
	faceplayer
	msgbox Route30_Text_YoungsterEveryoneIsBattling, MSGBOX_DEFAULT
	closemessage
	release
	end

Route30_Text_YoungsterEveryoneIsBattling::
	.string "Everyone's having fun\n"
	.string "battling!\p"
	.string "You should too!$"

Route30_EventScript_Youngster_Joey::
	trainerbattle_single TRAINER_JOEY_HNS, Route30_Text_YoungsterJoey1Seen, Route30_Text_YoungsterJoey1Beaten, Route30_EventScript_RegisterJoey
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route30_EventScript_RematchJoey
	msgbox Route30_Text_YoungsterJoey1After, MSGBOX_AUTOCLOSE
	end

Route30_Text_YoungsterJoey1After::
	.string "Do I have to have more POKéMON\n"
	.string "in order to battle better?\p"
	.string "No! I'm sticking with this one\n"
	.string "no matter what!$"

Route30_EventScript_RematchJoey::
	trainerbattle_rematch TRAINER_JOEY_HNS, Route30_Text_JoeyRematchIntro, Route30_Text_JoeyRematchDefeat
	msgbox Route30_Text_JoeyPostRematch, MSGBOX_AUTOCLOSE
	end

Route30_Text_JoeyPostRematch::
	.string "I'm checking out my\n"
	.string "RATTATA's moves and devising\l"
	.string "some strategies.\p"
	.string "When I come up with a good\n"
	.string "one, let's battle!$"

Route30_Text_JoeyRematchDefeat::
	.string "Ack! I lost again!\n"
	.string "Doggone it!$"

Route30_Text_JoeyRematchIntro::
	.string "I promised things would be\n"
	.string "different! Let's battle!$"

Route30_EventScript_RegisterJoey::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route30_Text_JoeyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JOEY_HNS
	release
	end

Route30_Text_JoeyRegister::
	.string "You're pretty good!\p"
	.string "My RATTATA's raring to go,\n"
	.string "just like always.\p"
	.string "It's the only one I have.\n"
	.string "I'm going to become a great\l"
	.string "TRAINER with it!\p"
	.string "Let's battle again sometime!$"

Route30_Text_YoungsterJoey1Beaten::
	.string "Ack! I lost again!\n"
	.string "Doggone it!$"

Route30_Text_YoungsterJoey1Seen::
	.string "I just lost, so I'm trying to\n"
	.string "find more POKéMON.\p"
	.string "Wait! You look weak! Come on,\n"
	.string "let's battle!$"

Route30_EventScript_Girl::
	lock
	faceplayer
	msgbox Route30_Text_CooltrainerF, MSGBOX_DEFAULT
	closemessage
	release
	end

Route30_Text_CooltrainerF::
	.string "I'm not a TRAINER.\p"
	.string "But if you look one in the\n"
	.string "eyes, prepare to battle.$"

Route30_EventScript_Bugcatcher_Don::
	trainerbattle_single TRAINER_DON_HNS, Route30_Text_BugCatcherDonSeen, Route30_Text_BugCatcherDonBeaten
	msgbox Route30_Text_BugCatcherDonAfter, MSGBOX_AUTOCLOSE
	end

Route30_Text_BugCatcherDonAfter::
	.string "I ran out of POKé BALLS while\n"
	.string "I was catching POKéMON.\p"
	.string "I should've bought some more…$"

Route30_Text_BugCatcherDonBeaten::
	.string "Argh! You're too strong!$"

Route30_Text_BugCatcherDonSeen::
	.string "Instead of a bug POKéMON,\n"
	.string "I found a TRAINER!$"

Route30_EventScript_Youngster_Mikey::
	trainerbattle_single TRAINER_MIKEY_HNS, Route30_Text_YoungsterMikeySeen, Route30_Text_YoungsterMikeyBeaten
	msgbox Route30_Text_YoungsterMikeyAfter, MSGBOX_AUTOCLOSE
	end

Route30_Text_YoungsterMikeyAfter::
	.string "Becoming a good TRAINER is\n"
	.string "really tough.\p"
	.string "I'm going to battle other\n"
	.string "people to get better.$"

Route30_Text_YoungsterMikeyBeaten::
	.string "That's strange.\n"
	.string "I won before.$"

Route30_Text_YoungsterMikeySeen::
	.string "You're a POKéMON TRAINER,\n"
	.string "right?\p"
	.string "Then you have to battle!$"

Route30_EventScript_Sign::
	lock
	msgbox Route30_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route30_Text_Sign::
	.string "ROUTE 30\p"
	.string "VIOLET CITY - CHERRYGROVE CITY$"

Route30_EventScript_TrainerTips::
	lock
	msgbox Route30_Text_TrainerTips, MSGBOX_SIGN
	closemessage
	release
	end	

Route30_Text_TrainerTips::
	.string "TRAINER TIPS\p"
	.string "No stealing other people's\n"
	.string "POKéMON!\p"
	.string "POKé BALLS are to be thrown\n"
	.string "only at wild POKéMON!$"

Route30_EventScript_Mailbox::
	msgbox Route30_Text_Mailbox, MSGBOX_SIGN
	end

Route30_Text_Mailbox::
	.string "MR.POKéMON's House$"
