Route210_South_sinnoh_MapScripts::
	.byte 0


Route210_South_EventScript_Fabian::
	trainerbattle_single TRAINER_DEAN_SINNOH, Route210_South_Text_FabianIntro, Route210_South_Text_FabianDefeat
	msgbox Route210_South_Text_FabianPost, MSGBOX_AUTOCLOSE
	end

Route210_South_Text_FabianPost::
	.string "My cover is blown, so what should I do?\p"
	.string "Maybe I'll go catch some CONTESTS in\n"
	.string "HEARTHOME CITY. Maybe I'll do that.$"

Route210_South_Text_FabianDefeat::
	.string "I concede defeat...$"

Route210_South_Text_FabianIntro::
	.string "I am one of the Ninja Trio! Being\n"
	.string "discovered means I must battle!$"

Route210_South_EventScript_Brennan::
	trainerbattle_single TRAINER_RODNEY_SINNOH, Route210_South_Text_BrennanIntro, Route210_South_Text_BrennanDefeat
	msgbox Route210_South_Text_BrennanPost, MSGBOX_AUTOCLOSE
	end

Route210_South_Text_BrennanPost::
	.string "While I hid in the tall grass, I sensed\n"
	.string "POKéMON all around me!\p"
	.string "Furtive sounds of movement... Stifled\n"
	.string "cries... I heard them!$"

Route210_South_Text_BrennanDefeat::
	.string "I concede defeat...$"

Route210_South_Text_BrennanIntro::
	.string "I am one of the Ninja Trio! Being\n"
	.string "discovered means I must battle!$"

Route210_South_EventScript_TeriTia::
	trainerbattle_double TRAINER_RICHARD_SINNOH, Route210_South_Text_TeriTiaIntro, Route210_South_Text_TeriTiaDefeat, Route210_South_Text_TeriTiaNotEnough
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route210_South_EventScript_TeriTia_Rematch
	msgbox Route210_South_Text_TeriTiaPost, MSGBOX_AUTOCLOSE
	end

Route210_South_Text_TeriTiaPost::
	.string "TERI: Our mommy is a twin, too.$"

Route210_South_EventScript_TeriTia_Rematch::
	trainerbattle_rematch_double TRAINER_RICHARD_SINNOH, Route210_South_Text_TeriTiaIntro, Route210_South_Text_TeriTiaDefeat, Route210_South_Text_TeriTiaNotEnough
	msgbox Route210_South_Text_TeriTiaPost, MSGBOX_AUTOCLOSE
	end

Route210_South_Text_TeriTiaNotEnough::
	.string "TERI: We want to battle with lots of\n"
	.string "POKéMON.$"

Route210_South_Text_TeriTiaDefeat::
	.string "TERI: We tried really hard together,\n"
	.string "but we lost anyway.$"

Route210_South_Text_TeriTiaIntro::
	.string "TERI: Yay! We're gonna battle with lots\n"
	.string "of POKéMON!$"

Route210_South_EventScript_Bruce::
	trainerbattle_single TRAINER_HERMAN_SINNOH, Route210_South_Text_BruceIntro, Route210_South_Text_BruceDefeat
	msgbox Route210_South_Text_BrucePost, MSGBOX_AUTOCLOSE
	end

Route210_South_Text_BrucePost::
	.string "A POKéMON TRAINER's good at finding\n"
	.string "stuff, I guess.$"

Route210_South_Text_BruceDefeat::
	.string "I concede defeat...$"

Route210_South_Text_BruceIntro::
	.string "I am one of the Ninja Trio! Being\n"
	.string "discovered means I must battle!\p"
	.string "But how did you discover me? Don't\n"
	.string "tell me you're a ninja, too!$"

Route210_South_EventScript_Wyatt::
	trainerbattle_single TRAINER_SANTIAGO_SINNOH, Route210_South_Text_WyattIntro, Route210_South_Text_WyattDefeat
	msgbox Route210_South_Text_WyattPost, MSGBOX_AUTOCLOSE
	end

Route210_South_Text_WyattPost::
	.string "I wish I could just run from all this...\n"
	.string "Just joking.$"

Route210_South_Text_WyattDefeat::
	.string "...Oh, serious woe. I wasn't prepared\n"
	.string "emotionally for this.$"

Route210_South_Text_WyattIntro::
	.string "I'm warmed up and limber. I'm OK to\n"
	.string "battle!$"

Route210_South_EventScript_Kahlil::
	trainerbattle_single TRAINER_GILBERT_SINNOH, Route210_South_Text_KahlilIntro, Route210_South_Text_KahlilDefeat
	msgbox Route210_South_Text_KahlilPost, MSGBOX_AUTOCLOSE
	end

Route210_South_Text_KahlilPost::
	.string "The VEILSTONE Department Store is\n"
	.string "pretty impressive!\p"
	.string "Did you know they even sell POKéBLOCKS?$"

Route210_South_Text_KahlilDefeat::
	.string "Hey, hey, did you take a good look?$"

Route210_South_Text_KahlilIntro::
	.string "Hey, check this out! Look at the\n"
	.string "luster of my POKéMON's fur!$"

Route210_South_EventScript_Amber::
	trainerbattle_single TRAINER_FRANKLIN_SINNOH, Route210_South_Text_AmberIntro, Route210_South_Text_AmberDefeat
	msgbox Route210_South_Text_AmberPost, MSGBOX_AUTOCLOSE
	end

Route210_South_Text_AmberPost::
	.string "The best way to raise POKéMON?\p"
	.string "...Hmm, when it comes right down to it,\n"
	.string "isn't it all about love?$"

Route210_South_Text_AmberDefeat::
	.string "It's all right! I'm still a rookie!$"

Route210_South_Text_AmberIntro::
	.string "I'm a rookie breeder, but I'll do my\n"
	.string "very best!$"

Route210_South_EventScript_AvaMatt::
	trainerbattle_double TRAINER_KEVIN_SINNOH, Route210_South_Text_AvaMattIntro, Route210_South_Text_AvaMattDefeat, Route210_South_Text_AvaMattNotEnough
	msgbox Route210_South_Text_AvaMattPost, MSGBOX_AUTOCLOSE
	end

Route210_South_Text_AvaMattPost::
	.string "Matt: I reckon the bonds between you\n"
	.string "and your POKéMON are like the bonds\l"
	.string "parents share with their kids.$"

Route210_South_Text_AvaMattNotEnough::
	.string "Matt: Oh, there's no way you could\n"
	.string "beat us both with one POKéMON.$"

Route210_South_Text_AvaMattDefeat::
	.string "Matt: Parent-and-child power couldn't\n"
	.string "get the job done.$"

Route210_South_Text_AvaMattIntro::
	.string "Matt: Uhohoho! I'll show y'all how\n"
	.string "tightly I've bonded with my daughter!$"

Route210_South_EventScript_Marco::
	trainerbattle_single TRAINER_JACK_SINNOH, Route210_South_Text_MarcoIntro, Route210_South_Text_MarcoDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route210_South_EventScript_Marco_Rematch
	msgbox Route210_South_Text_MarcoPost, MSGBOX_AUTOCLOSE
	end

Route210_South_Text_MarcoPost::
	.string "When I cuddle with my POKéMON, I can\n"
	.string "feel not just their bodies' warmth,\l"
	.string "but their compassion.$"

Route210_South_EventScript_Marco_Rematch::
	trainerbattle_rematch TRAINER_JACK_SINNOH, Route210_South_Text_MarcoIntro, Route210_South_Text_MarcoDefeat
	msgbox Route210_South_Text_MarcoPost, MSGBOX_AUTOCLOSE
	end

Route210_South_Text_MarcoDefeat::
	.string "Hahahah! Your POKéMON sure can be\n"
	.string "counted on!$"

Route210_South_Text_MarcoIntro::
	.string "My POKéMON toughened up while working\n"
	.string "on the ranch.\p"
	.string "I'm right proud of them!$"

Route210_South_EventScript_SNPsyduck::
	lock
	faceplayer
	playmoncry SPECIES_PSYDUCK, CRY_MODE_NORMAL
	waitmoncry
	checkitem ITEM_SECRET_POTION
	goto_if_eq VAR_RESULT, FALSE, Route210_South_EventScript_SNPsyduck_Firm
	msgbox Route210_South_EventScript_SNPsyduck_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route210_South_EventScript_SNPsyduck_End
	msgbox Route210_South_EventScript_SNPsyduck_Used, MSGBOX_DEFAULT
	closemessage
	removeitem ITEM_SECRET_POTION
	setflag FLAG_SN_PSYDUCK_GONE
	setflag FLAG_SN_USED_SECRETPOTION
	setflag FLAG_SN_HIDE_PSYDUCK
	sn_walkto LOCALID_SN_PSYDUCK_1, 30, 47, SN_SPEED_FAST, 0, 0, 0
	sn_walkto LOCALID_SN_PSYDUCK_2, 30, 47, SN_SPEED_FAST, 0, 0, 1
	sn_walkto LOCALID_SN_PSYDUCK_3, 25, 30, SN_SPEED_FAST, 0, 0, 2
	sn_walkto LOCALID_SN_PSYDUCK_4, 24, 31, SN_SPEED_FAST, 0, 0, 3
	waitmovement LOCALID_SN_PSYDUCK_1
	waitmovement LOCALID_SN_PSYDUCK_2
	waitmovement LOCALID_SN_PSYDUCK_3
	waitmovement LOCALID_SN_PSYDUCK_4
	removeobject LOCALID_SN_PSYDUCK_1
	removeobject LOCALID_SN_PSYDUCK_2
	removeobject LOCALID_SN_PSYDUCK_3
	removeobject LOCALID_SN_PSYDUCK_4
	clearflag FLAG_SN_HIDE_R210_CYNTHIA
	addobject LOCALID_SN_R210_CYNTHIA
	goto Route210_South_EventScript_SNCynthiaCharm
	end

Route210_South_EventScript_SNCynthiaCharm::
	lock
	faceplayer
	msgbox Route210_South_EventScript_SNCynthiaCharm_T1, MSGBOX_DEFAULT
	giveitem ITEM_ULTRA_BALL
	setflag FLAG_SN_RECEIVED_OLD_CHARM
	msgbox Route210_South_EventScript_SNCynthiaCharm_T2, MSGBOX_DEFAULT
	closemessage
	sn_walkto LOCALID_SN_R210_CYNTHIA, 30, 47, SN_SPEED_NORMAL, 0, 0, 0
	waitmovement LOCALID_SN_R210_CYNTHIA
	removeobject LOCALID_SN_R210_CYNTHIA
	setflag FLAG_SN_HIDE_R210_CYNTHIA
	release
	end

Route210_South_EventScript_SNCynthiaCharm_T2::
	.string "I know I’m asking a big favor of you.\p"
	.string "But I really want you to do it. Will you\n"
	.string "go to CELESTIC TOWN for me?$"

Route210_South_EventScript_SNCynthiaCharm_T1::
	.string "CYNTHIA: Oh, good. You used the\n"
	.string "SecretPotion I gave you.\p"
	.string "PSYDUCK are known to suffer from\n"
	.string "chronic headaches.\p"
	.string "But no one’s been able to figure out\n"
	.string "what triggers the headaches.\p"
	.string "Oh, yes! Can I ask you a big favor?\p"
	.string "I want you to deliver this Old Charm to\n"
	.string "my grandma in CELESTIC TOWN.\p"
	.string "I know there are some rare POKéMON\n"
	.string "between here and CELESTIC TOWN, so\p"
	.string "it will be worth your while to go.$"

Route210_South_EventScript_SNPsyduck_Used::
	.string "{PLAYER} used the SecretPotion!\p"
	.string "The PSYDUCK appear to be cured of\n"
	.string "their chronic headache!$"

Route210_South_EventScript_SNPsyduck_End::
	release
	end

Route210_South_EventScript_SNPsyduck_Ask::
	.string "The PSYDUCK are standing firm. They\n"
	.string "aren’t inclined to move.\p"
	.string "Would you like to use the\n"
	.string "SecretPotion?$"

Route210_South_EventScript_SNPsyduck_Firm::
	msgbox Route210_South_EventScript_SNPsyduck_FirmT, MSGBOX_DEFAULT
	goto Route210_South_EventScript_SNPsyduck_End

Route210_South_EventScript_SNPsyduck_FirmT::
	.string "The PSYDUCK are standing firm. They\n"
	.string "aren’t inclined to move at all.$"

Route210_South_EventScript_SNPtACETRAINERF::
	msgbox Route210_South_EventScript_SNPtACETRAINERF_Text, MSGBOX_NPC
	end

Route210_South_EventScript_SNPtACETRAINERF_Text::
	.string "If they had to keep flying forever,\n"
	.string "bird POKéMON would eventually crash.$"

Route210_South_EventScript_PtSign1::
	msgbox Route210_South_Text_PtSign1, MSGBOX_SIGN
	end

Route210_South_Text_PtSign1::
	.string "Rt. 210 SOLACEON TOWN$"

Route210_South_EventScript_PtSign2::
	msgbox Route210_South_Text_PtSign2, MSGBOX_SIGN
	end

Route210_South_Text_PtSign2::
	.string "Café Cabin Freshly Squeezed Milk$"
