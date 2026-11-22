@ Super Emerald: side quests of Johto, Kanto and Sinnoh.
@  Johto:  Rocket's return (VAR_SE_ROCKET_QUEST), the sick Miltank of Route 39 (VAR_SE_MOOMOO)
@  Kanto:  the Pewter Museum thief (VAR_SE_THIEF_QUEST), the restless spirits of Pokemon Tower (VAR_SE_SPIRIT_QUEST)
@  Sinnoh: Looker's last case (VAR_SE_GALACTIC_QUEST), the Rotom Catalog of the Old Chateau
@ The quest characters use FLAG_SE_QUEST_* flags: see sSEQuestObjects in event_object_movement.c.

@ ===========================================================================
@ JOHTO: Rocket's return
@ ===========================================================================
SE_EventScript_RocketOfficer::
	lock
	faceplayer
	switch VAR_SE_ROCKET_QUEST
	case 0, SE_EventScript_RocketOfficer0
	case 1, SE_EventScript_RocketOfficer1
	case 2, SE_EventScript_RocketOfficer2
	case 3, SE_EventScript_RocketOfficer3
	case 4, SE_EventScript_RocketOfficer4
	case 5, SE_EventScript_RocketOfficer5
	case 6, SE_EventScript_RocketOfficer6
	msgbox SE_Text_RocketOfficerDone, MSGBOX_DEFAULT
	release
	end
SE_EventScript_RocketOfficer0::
	msgbox SE_Text_RocketOfficer0, MSGBOX_DEFAULT
	release
	end
SE_EventScript_RocketOfficer1::
	msgbox SE_Text_RocketOfficer1, MSGBOX_DEFAULT
	release
	end
SE_EventScript_RocketOfficer2::
	msgbox SE_Text_RocketOfficer2, MSGBOX_DEFAULT
	release
	end
SE_EventScript_RocketOfficer3::
	msgbox SE_Text_RocketOfficer3, MSGBOX_DEFAULT
	release
	end

SE_EventScript_RocketOfficer4::
	msgbox SE_Text_RocketOfficer4, MSGBOX_DEFAULT
	release
	end
SE_EventScript_RocketOfficer5::
	msgbox SE_Text_RocketOfficer5, MSGBOX_DEFAULT
	release
	end
SE_EventScript_RocketOfficer6::
	msgbox SE_Text_RocketOfficer6, MSGBOX_DEFAULT
	release
	end

SE_EventScript_Proton::
	lock
	faceplayer
	msgbox SE_Text_ProtonIntro, MSGBOX_DEFAULT
	cleartrainerflag TRAINER_SE_PROTON_RETURN
	trainerbattle_no_intro TRAINER_SE_PROTON_RETURN, SE_Text_ProtonDefeat
	msgbox SE_Text_ProtonAfter, MSGBOX_DEFAULT
	giveitem ITEM_MAX_REVIVE, 2
	setvar VAR_SE_ROCKET_QUEST, 1
	goto SE_EventScript_QuestLeave

SE_EventScript_Petrel::
	lock
	faceplayer
	msgbox SE_Text_PetrelIntro, MSGBOX_DEFAULT
	cleartrainerflag TRAINER_SE_PETREL_RETURN
	trainerbattle_no_intro TRAINER_SE_PETREL_RETURN, SE_Text_PetrelDefeat
	msgbox SE_Text_PetrelAfter, MSGBOX_DEFAULT
	giveitem ITEM_PP_UP, 2
	setvar VAR_SE_ROCKET_QUEST, 2
	goto SE_EventScript_QuestLeave

SE_EventScript_Ariana::
	lock
	faceplayer
	msgbox SE_Text_ArianaIntro, MSGBOX_DEFAULT
	cleartrainerflag TRAINER_SE_ARIANA_RETURN
	trainerbattle_no_intro TRAINER_SE_ARIANA_RETURN, SE_Text_ArianaDefeat
	msgbox SE_Text_ArianaAfter, MSGBOX_DEFAULT
	giveitem ITEM_RARE_CANDY, 3
	setvar VAR_SE_ROCKET_QUEST, 3
	goto SE_EventScript_QuestLeave

SE_EventScript_Archer::
	lock
	faceplayer
	msgbox SE_Text_ArcherIntro, MSGBOX_DEFAULT
	cleartrainerflag TRAINER_SE_ARCHER_RETURN
	trainerbattle_no_intro TRAINER_SE_ARCHER_RETURN, SE_Text_ArcherDefeat
	msgbox SE_Text_ArcherAfter, MSGBOX_DEFAULT
	giveitem ITEM_EXP_CHARM
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_QuestBagFull
	msgbox SE_Text_ArcherBye, MSGBOX_DEFAULT
	setvar VAR_SE_ROCKET_QUEST, 4
	goto SE_EventScript_QuestLeave

@ ===========================================================================
@ JOHTO: the sick Miltank of Route 39
@ ===========================================================================
SE_EventScript_MoomooMiltank::
	lock
	faceplayer
	goto_if_ge VAR_SE_MOOMOO, 7, SE_EventScript_MoomooHealthy
	playmoncry SPECIES_MILTANK, CRY_MODE_WEAK
	msgbox SE_Text_MoomooSick, MSGBOX_DEFAULT
	waitmoncry
	checkitem ITEM_ORAN_BERRY
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_MoomooNoBerry
	msgbox SE_Text_MoomooFeed, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SE_EventScript_MoomooEnd
	removeitem ITEM_ORAN_BERRY
	addvar VAR_SE_MOOMOO, 1
	goto_if_ge VAR_SE_MOOMOO, 7, SE_EventScript_MoomooCured
	goto_if_ge VAR_SE_MOOMOO, 4, SE_EventScript_MoomooBetter
	msgbox SE_Text_MoomooAte, MSGBOX_DEFAULT
	release
	end
SE_EventScript_MoomooBetter::
	msgbox SE_Text_MoomooBetter, MSGBOX_DEFAULT
	release
	end
SE_EventScript_MoomooCured::
	playmoncry SPECIES_MILTANK, CRY_MODE_NORMAL
	msgbox SE_Text_MoomooCured, MSGBOX_DEFAULT
	waitmoncry
	release
	end
SE_EventScript_MoomooHealthy::
	playmoncry SPECIES_MILTANK, CRY_MODE_NORMAL
	msgbox SE_Text_MoomooHealthy, MSGBOX_DEFAULT
	waitmoncry
	release
	end
SE_EventScript_MoomooNoBerry::
	msgbox SE_Text_MoomooNoBerry, MSGBOX_DEFAULT
SE_EventScript_MoomooEnd::
	release
	end

SE_EventScript_MoomooTwins::
	lock
	faceplayer
	goto_if_ge VAR_SE_MOOMOO, 7, SE_EventScript_MoomooTwinsHappy
	msgbox SE_Text_MoomooTwinsSick, MSGBOX_DEFAULT
	release
	end
SE_EventScript_MoomooTwinsHappy::
	msgbox SE_Text_MoomooTwinsHappy, MSGBOX_DEFAULT
	release
	end

SE_EventScript_MoomooFarmer::
	lock
	faceplayer
	goto_if_ge VAR_SE_MOOMOO, 7, SE_EventScript_MoomooFarmerShop
	msgbox SE_Text_MoomooFarmerSick, MSGBOX_DEFAULT
	release
	end
SE_EventScript_MoomooFarmerShop::
	msgbox SE_Text_MoomooFarmerShop, MSGBOX_DEFAULT
	pokemart SE_MoomooFarmer_Mart
	msgbox SE_Text_MoomooFarmerBye, MSGBOX_DEFAULT
	release
	end

	.align 2
SE_MoomooFarmer_Mart:
	.2byte ITEM_MOOMOO_MILK
	pokemartlistend

SE_EventScript_MoomooFarmerWife::
	lock
	faceplayer
	goto_if_eq VAR_SE_MOOMOO, 9, SE_EventScript_MoomooGiveMilk
	goto_if_ge VAR_SE_MOOMOO, 8, SE_EventScript_MoomooFarmerWifeDone
	goto_if_ge VAR_SE_MOOMOO, 7, SE_EventScript_MoomooFarmerWifeThanks
	msgbox SE_Text_MoomooWifeSick, MSGBOX_DEFAULT
	release
	end
SE_EventScript_MoomooFarmerWifeThanks::
	msgbox SE_Text_MoomooWifeThanks, MSGBOX_DEFAULT
	giveitem ITEM_LEFTOVERS
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_QuestBagFull
	setvar VAR_SE_MOOMOO, 9
SE_EventScript_MoomooGiveMilk::
	giveitem ITEM_MOOMOO_MILK, 6
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_QuestBagFull
	setvar VAR_SE_MOOMOO, 8
	msgbox SE_Text_MoomooWifeAfter, MSGBOX_DEFAULT
	release
	end
SE_EventScript_MoomooFarmerWifeDone::
	msgbox SE_Text_MoomooWifeDone, MSGBOX_DEFAULT
	release
	end

@ ===========================================================================
@ KANTO: the Pewter Museum thief
@ ===========================================================================
SE_EventScript_MuseumCurator::
	lock
	faceplayer
	switch VAR_SE_THIEF_QUEST
	case 0, SE_EventScript_MuseumCurator0
	case 1, SE_EventScript_MuseumCurator1
	case 2, SE_EventScript_MuseumCurator2
	case 3, SE_EventScript_MuseumCurator3
	case 5, SE_EventScript_MuseumGiveShard
	msgbox SE_Text_CuratorDone, MSGBOX_DEFAULT
	release
	end
SE_EventScript_MuseumCurator0::
	msgbox SE_Text_Curator0, MSGBOX_DEFAULT
	setvar VAR_SE_THIEF_QUEST, 1
	release
	end
SE_EventScript_MuseumCurator1::
	msgbox SE_Text_Curator1, MSGBOX_DEFAULT
	release
	end
SE_EventScript_MuseumCurator2::
	msgbox SE_Text_Curator2, MSGBOX_DEFAULT
	release
	end
SE_EventScript_MuseumCurator3::
	msgbox SE_Text_Curator3, MSGBOX_DEFAULT
	giveitem ITEM_OLD_AMBER
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_QuestBagFull
	setvar VAR_SE_THIEF_QUEST, 5
SE_EventScript_MuseumGiveShard::
	giveitem ITEM_COMET_SHARD
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_QuestBagFull
	setvar VAR_SE_THIEF_QUEST, 4
	msgbox SE_Text_CuratorReward, MSGBOX_DEFAULT
	release
	end

SE_EventScript_ThiefMtMoon::
	lock
	faceplayer
	playse SE_PIN
	applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox SE_Text_ThiefMtMoon, MSGBOX_DEFAULT
	setvar VAR_SE_THIEF_QUEST, 2
	goto SE_EventScript_QuestLeave

SE_EventScript_ThiefRoute24::
	lock
	faceplayer
	msgbox SE_Text_ThiefRoute24, MSGBOX_DEFAULT
	cleartrainerflag TRAINER_SE_MUSEUM_THIEF
	trainerbattle_no_intro TRAINER_SE_MUSEUM_THIEF, SE_Text_ThiefDefeat
	msgbox SE_Text_ThiefAfter, MSGBOX_DEFAULT
	setvar VAR_SE_THIEF_QUEST, 3
	goto SE_EventScript_QuestLeave

@ ===========================================================================
@ KANTO: the restless spirits of Pokemon Tower
@ ===========================================================================
SE_EventScript_SpiritElder::
	lock
	faceplayer
	switch VAR_SE_SPIRIT_QUEST
	case 0, SE_EventScript_SpiritElder0
	case 4, SE_EventScript_SpiritElder4
	case 5, SE_EventScript_SpiritElder5
	case 6, SE_EventScript_SpiritGiveTag
	case 7, SE_EventScript_SpiritGiveStone
	msgbox SE_Text_SpiritElderWaiting, MSGBOX_DEFAULT
	release
	end
SE_EventScript_SpiritElder0::
	msgbox SE_Text_SpiritElder0, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SE_EventScript_SpiritElderNo
	msgbox SE_Text_SpiritElderYes, MSGBOX_DEFAULT
	setvar VAR_SE_SPIRIT_QUEST, 1
	release
	end
SE_EventScript_SpiritElderNo::
	msgbox SE_Text_SpiritElderNo, MSGBOX_DEFAULT
	release
	end
SE_EventScript_SpiritElder4::
	msgbox SE_Text_SpiritElder4, MSGBOX_DEFAULT
	giveitem ITEM_REAPER_CLOTH
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_QuestBagFull
	setvar VAR_SE_SPIRIT_QUEST, 6
SE_EventScript_SpiritGiveTag::
	giveitem ITEM_SPELL_TAG
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_QuestBagFull
	setvar VAR_SE_SPIRIT_QUEST, 7
SE_EventScript_SpiritGiveStone::
	giveitem ITEM_DUSK_STONE
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_QuestBagFull
	setvar VAR_SE_SPIRIT_QUEST, 5
	msgbox SE_Text_SpiritElderBye, MSGBOX_DEFAULT
	release
	end
SE_EventScript_SpiritElder5::
	msgbox SE_Text_SpiritElder5, MSGBOX_DEFAULT
	release
	end

SE_EventScript_Spirit1::
	lock
	faceplayer
	msgbox SE_Text_Spirit1, MSGBOX_DEFAULT
	cleartrainerflag TRAINER_SE_SPIRIT_CHANNELER_1
	trainerbattle_no_intro TRAINER_SE_SPIRIT_CHANNELER_1, SE_Text_SpiritDefeat
	msgbox SE_Text_Spirit1After, MSGBOX_DEFAULT
	setvar VAR_SE_SPIRIT_QUEST, 2
	goto SE_EventScript_QuestLeave

SE_EventScript_Spirit2::
	lock
	faceplayer
	msgbox SE_Text_Spirit2, MSGBOX_DEFAULT
	cleartrainerflag TRAINER_SE_SPIRIT_CHANNELER_2
	trainerbattle_no_intro TRAINER_SE_SPIRIT_CHANNELER_2, SE_Text_SpiritDefeat
	msgbox SE_Text_Spirit2After, MSGBOX_DEFAULT
	setvar VAR_SE_SPIRIT_QUEST, 3
	goto SE_EventScript_QuestLeave

SE_EventScript_Spirit3::
	lock
	faceplayer
	msgbox SE_Text_Spirit3, MSGBOX_DEFAULT
	cleartrainerflag TRAINER_SE_SPIRIT_CHANNELER_3
	trainerbattle_no_intro TRAINER_SE_SPIRIT_CHANNELER_3, SE_Text_SpiritDefeat
	msgbox SE_Text_Spirit3After, MSGBOX_DEFAULT
	setvar VAR_SE_SPIRIT_QUEST, 4
	goto SE_EventScript_QuestLeave

@ ===========================================================================
@ SINNOH: Looker's last case
@ ===========================================================================
SE_EventScript_LookerCase::
	lock
	faceplayer
	switch VAR_SE_GALACTIC_QUEST
	case 0, SE_EventScript_LookerCase0
	case 5, SE_EventScript_LookerCase5
	case 6, SE_EventScript_LookerCase6
	case 7, SE_EventScript_LookerCase7
	case 8, SE_EventScript_LookerCase8
	msgbox SE_Text_LookerHunting, MSGBOX_DEFAULT
	release
	end
SE_EventScript_LookerCase0::
	msgbox SE_Text_Looker0, MSGBOX_DEFAULT
	setvar VAR_SE_GALACTIC_QUEST, 1
	release
	end
SE_EventScript_LookerCase5::
	msgbox SE_Text_Looker5, MSGBOX_DEFAULT
	giveitem ITEM_OVAL_CHARM
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_QuestBagFull
	setvar VAR_SE_GALACTIC_QUEST, 6
	msgbox SE_Text_LookerNext, MSGBOX_DEFAULT
	release
	end
SE_EventScript_LookerCase6::
	msgbox SE_Text_Looker6, MSGBOX_DEFAULT
	release
	end
SE_EventScript_LookerCase7::
	msgbox SE_Text_Looker7, MSGBOX_DEFAULT
	release
	end
SE_EventScript_LookerCase8::
	msgbox SE_Text_LookerBye, MSGBOX_DEFAULT
	release
	end

SE_EventScript_Mars::
	lock
	faceplayer
	msgbox SE_Text_MarsIntro, MSGBOX_DEFAULT
	cleartrainerflag TRAINER_SE_MARS_RETURN
	trainerbattle_no_intro TRAINER_SE_MARS_RETURN, SE_Text_MarsDefeat
	msgbox SE_Text_MarsAfter, MSGBOX_DEFAULT
	setvar VAR_SE_GALACTIC_QUEST, 2
	goto SE_EventScript_QuestLeave

SE_EventScript_Jupiter::
	lock
	faceplayer
	msgbox SE_Text_JupiterIntro, MSGBOX_DEFAULT
	cleartrainerflag TRAINER_SE_JUPITER_RETURN
	trainerbattle_no_intro TRAINER_SE_JUPITER_RETURN, SE_Text_JupiterDefeat
	msgbox SE_Text_JupiterAfter, MSGBOX_DEFAULT
	setvar VAR_SE_GALACTIC_QUEST, 3
	goto SE_EventScript_QuestLeave

SE_EventScript_Saturn::
	lock
	faceplayer
	msgbox SE_Text_SaturnIntro, MSGBOX_DEFAULT
	cleartrainerflag TRAINER_SE_SATURN_RETURN
	trainerbattle_no_intro TRAINER_SE_SATURN_RETURN, SE_Text_SaturnDefeat
	msgbox SE_Text_SaturnAfter, MSGBOX_DEFAULT
	setvar VAR_SE_GALACTIC_QUEST, 4
	goto SE_EventScript_QuestLeave

SE_EventScript_Charon::
	lock
	faceplayer
	msgbox SE_Text_CharonIntro, MSGBOX_DEFAULT
	cleartrainerflag TRAINER_SE_CHARON_RETURN
	trainerbattle_no_intro TRAINER_SE_CHARON_RETURN, SE_Text_CharonDefeat
	msgbox SE_Text_CharonAfter, MSGBOX_DEFAULT
	setvar VAR_SE_GALACTIC_QUEST, 5
	goto SE_EventScript_QuestLeave

@ ===========================================================================
@ SINNOH: the Rotom Catalog of the Old Chateau
@ ===========================================================================
SE_EventScript_RotomCollector::
	lock
	faceplayer
	goto_if_set FLAG_SE_RECEIVED_ROTOM_CATALOG, SE_EventScript_RotomCollectorDone
	msgbox SE_Text_RotomCollector, MSGBOX_DEFAULT
	checkspecies SPECIES_ROTOM
	goto_if_eq VAR_RESULT, TRUE, SE_EventScript_RotomCollectorShow
	checkspecies SPECIES_ROTOM_HEAT
	goto_if_eq VAR_RESULT, TRUE, SE_EventScript_RotomCollectorShow
	checkspecies SPECIES_ROTOM_WASH
	goto_if_eq VAR_RESULT, TRUE, SE_EventScript_RotomCollectorShow
	checkspecies SPECIES_ROTOM_FROST
	goto_if_eq VAR_RESULT, TRUE, SE_EventScript_RotomCollectorShow
	checkspecies SPECIES_ROTOM_FAN
	goto_if_eq VAR_RESULT, TRUE, SE_EventScript_RotomCollectorShow
	checkspecies SPECIES_ROTOM_MOW
	goto_if_eq VAR_RESULT, TRUE, SE_EventScript_RotomCollectorShow
	msgbox SE_Text_RotomCollectorNoRotom, MSGBOX_DEFAULT
	release
	end
SE_EventScript_RotomCollectorShow::
	msgbox SE_Text_RotomCollectorShow, MSGBOX_DEFAULT
	giveitem ITEM_ROTOM_CATALOG
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_QuestBagFull
	setflag FLAG_SE_RECEIVED_ROTOM_CATALOG
	msgbox SE_Text_RotomCollectorAfter, MSGBOX_DEFAULT
	release
	end
SE_EventScript_RotomCollectorDone::
	msgbox SE_Text_RotomCollectorDone, MSGBOX_DEFAULT
	release
	end

@ ===========================================================================
@ Texts
@ ===========================================================================
SE_Text_RocketOfficer0:
	.string "OFFICER: You're the new JOHTO\n"
	.string "CHAMPION, right? I need your help.\p"
	.string "TEAM ROCKET's old executives were\n"
	.string "seen in JOHTO again.\p"
	.string "One of them was hanging around the\n"
	.string "SLOWPOKE WELL in AZALEA TOWN.\l"
	.string "Could you check it out?$"

SE_Text_RocketOfficer1:
	.string "OFFICER: You beat PROTON? Great!\n"
	.string "Now someone saw PETREL at the\l"
	.string "LAKE OF RAGE. Please hurry!$"

SE_Text_RocketOfficer2:
	.string "OFFICER: ARIANA was seen going into\n"
	.string "the UNDERGROUND STORAGE here in\l"
	.string "GOLDENROD. Be careful!$"

SE_Text_RocketOfficer3:
	.string "OFFICER: Their leader, ARCHER, is in\n"
	.string "the RADIO TOWER again! It's the last\l"
	.string "one. You can do it!$"

SE_Text_RocketOfficer4:
	.string "OFFICER: ARCHER fled to MAHOGANY\n"
	.string "TOWN. They're using their old\l"
	.string "hideout under the souvenir shop!$"

SE_Text_RocketOfficer5:
	.string "OFFICER: Look for ROCKET supplies\n"
	.string "in the warehouse on FIVE ISLAND.\p"
	.string "If you need a ferry pass, BILL can\n"
	.string "help. His cottage is north of\l"
	.string "CERULEAN CITY.\p"
	.string "With his pass, take the ferry from\n"
	.string "VERMILION CITY.$"

SE_Text_RocketOfficer6:
	.string "OFFICER: GIOVANNI himself is back?!\n"
	.string "The old hideout under the CELADON\l"
	.string "GAME CORNER… Please, stop him!$"

SE_Text_RocketOfficerDone:
	.string "OFFICER: TEAM ROCKET is gone for\n"
	.string "good, thanks to you. JOHTO owes you\l"
	.string "one, CHAMPION!$"

SE_Text_ProtonIntro:
	.string "PROTON: You again? We're only here\n"
	.string "for a few SLOWPOKETAILS…\p"
	.string "TEAM ROCKET needs money to bring\n"
	.string "back GIOVANNI. Get lost!$"

SE_Text_ProtonDefeat:
	.string "Still the same nasty brat…$"

SE_Text_ProtonAfter:
	.string "PROTON: Fine, fine… But PETREL's plan\n"
	.string "at the LAKE OF RAGE will work!\p"
	.string "Here, take this junk and leave me\n"
	.string "alone!$"

SE_Text_PetrelIntro:
	.string "PETREL: The red GYARADOS made us\n"
	.string "famous once. Let's do it again!\p"
	.string "And you won't stop us this time!$"

SE_Text_PetrelDefeat:
	.string "Not again!$"

SE_Text_PetrelAfter:
	.string "PETREL: Okay, okay! I'm out!\p"
	.string "ARIANA is hiding our money under\n"
	.string "GOLDENROD. You'll never find it!$"

SE_Text_ArianaIntro:
	.string "ARIANA: So you're the one beating\n"
	.string "my boys. How annoying.\p"
	.string "This money is for GIOVANNI's return.\n"
	.string "I won't let you touch it!$"

SE_Text_ArianaDefeat:
	.string "You really are strong…$"

SE_Text_ArianaAfter:
	.string "ARIANA: ARCHER will finish this at\n"
	.string "the RADIO TOWER.\p"
	.string "Here. Consider it a gift from the\n"
	.string "losing side.$"

SE_Text_ArcherIntro:
	.string "ARCHER: So it's you. JOHTO's new\n"
	.string "CHAMPION… and HOENN's too, I hear.\p"
	.string "I'll broadcast one last call to\n"
	.string "GIOVANNI from this tower.\p"
	.string "Nothing will stop TEAM ROCKET's\n"
	.string "return! Not even you!$"

SE_Text_ArcherDefeat:
	.string "…So this is the end of TEAM ROCKET.$"

SE_Text_ArcherAfter:
	.string "ARCHER: Grr… GIOVANNI hasn't\n"
	.string "answered us… yet.\p"
	.string "Take this. We stole it from a lab\n"
	.string "in KANTO. I have no use for it now.$"

SE_Text_ArcherBye:
	.string "ARCHER: But this isn't over. We'll\n"
	.string "regroup where it all began…\p"
	.string "Don't follow us, CHAMPION!$"

SE_Text_MoomooSick:
	.string "MILTANK: …Moo…\n"
	.string "It looks very weak.$"

SE_Text_MoomooFeed:
	.string "Give an ORAN BERRY to MILTANK?$"

SE_Text_MoomooAte:
	.string "MILTANK ate the ORAN BERRY.\n"
	.string "It still looks a little weak…$"

SE_Text_MoomooBetter:
	.string "MILTANK ate the ORAN BERRY.\n"
	.string "It's looking a lot better!$"

SE_Text_MoomooCured:
	.string "MILTANK ate the ORAN BERRY.\p"
	.string "MILTANK: Mooo!\n"
	.string "MILTANK is full of energy again!$"

SE_Text_MoomooHealthy:
	.string "MILTANK: Mooo!\n"
	.string "It looks healthy and happy.$"

SE_Text_MoomooNoBerry:
	.string "Maybe an ORAN BERRY would help it…$"

SE_Text_MoomooTwinsSick:
	.string "MOOMOO is sick…\p"
	.string "She needs lots of ORAN BERRIES.\n"
	.string "Can you give her some?$"

SE_Text_MoomooTwinsHappy:
	.string "MOOMOO is all better!\n"
	.string "Thank you so much!$"

SE_Text_MoomooFarmerSick:
	.string "Our MILTANK's sick, so there's no\n"
	.string "MOOMOO MILK to sell right now.\p"
	.string "Our milk even goes out to KANTO,\n"
	.string "you know. We're in big trouble!$"

SE_Text_MoomooFarmerShop:
	.string "Thanks to you, MOOMOO's healthy\n"
	.string "again! Want some fresh MOOMOO MILK?$"

SE_Text_MoomooFarmerBye:
	.string "Give it to POKéMON to restore HP!$"

SE_Text_MoomooWifeSick:
	.string "MOOMOO won't give any milk…\n"
	.string "The twins say she needs BERRIES.$"

SE_Text_MoomooWifeThanks:
	.string "You cured MOOMOO? Bless you!\n"
	.string "Please, take these as thanks.$"

SE_Text_MoomooWifeAfter:
	.string "Have your POKéMON hold LEFTOVERS and\n"
	.string "it'll slowly restore HP in battle.$"

SE_Text_MoomooWifeDone:
	.string "MOOMOO's milk is the best it's ever\n"
	.string "been. Come back anytime!$"

SE_Text_Curator0:
	.string "Oh, a CHAMPION! Please, you must\n"
	.string "help me!\p"
	.string "Our MOON STONE, the pride of this\n"
	.string "MUSEUM, was stolen last night!\p"
	.string "A guard saw a man in a striped shirt\n"
	.string "running toward MT. MOON.\l"
	.string "Could you look for him?$"

SE_Text_Curator1:
	.string "The thief ran toward MT. MOON.\n"
	.string "Please, find him!$"

SE_Text_Curator2:
	.string "He ran away again? He must be going\n"
	.string "north, past CERULEAN CITY!$"

SE_Text_Curator3:
	.string "Our MOON STONE! You got it back!\p"
	.string "I can't thank you enough. Please,\n"
	.string "take these from our collection.$"

SE_Text_CuratorReward:
	.string "The OLD AMBER holds an ancient\n"
	.string "POKéMON. A lab on CINNABAR ISLAND\l"
	.string "can bring it back to life!$"

SE_Text_CuratorDone:
	.string "Our MOON STONE is safe again.\n"
	.string "Thank you, CHAMPION!$"

SE_Text_ThiefMtMoon:
	.string "Huh?! Are you from the MUSEUM?\p"
	.string "You'll never catch me!\n"
	.string "Bye-bye!$"

SE_Text_ThiefRoute24:
	.string "You followed me all the way here?\n"
	.string "Fine! If I win, the MOON STONE is\l"
	.string "mine for good!$"

SE_Text_ThiefDefeat:
	.string "Okay, okay! I give up!$"

SE_Text_ThiefAfter:
	.string "Here, take the MOON STONE back to\n"
	.string "the MUSEUM. I'm done with stealing!$"

SE_Text_SpiritElder0:
	.string "Ah, you have a strong spirit.\p"
	.string "Since TEAM ROCKET's time, the\n"
	.string "spirits in POKéMON TOWER can't rest.\p"
	.string "Three channelers went up to calm\n"
	.string "them, but the spirits took them over.\p"
	.string "Will you go to the TOWER and free\n"
	.string "them with a POKéMON battle?$"

SE_Text_SpiritElderYes:
	.string "Thank you. The first one is on the\n"
	.string "3rd floor. Be careful in there.$"

SE_Text_SpiritElderNo:
	.string "I see… The spirits will wait.$"

SE_Text_SpiritElderWaiting:
	.string "The spirits still can't rest. Please,\n"
	.string "keep going up the POKéMON TOWER.$"

SE_Text_SpiritElder4:
	.string "The TOWER feels calm again.\n"
	.string "The spirits are finally at peace.\p"
	.string "Please take these. They were left in\n"
	.string "the TOWER long ago.$"

SE_Text_SpiritElderBye:
	.string "Some GHOST POKéMON evolve when traded\n"
	.string "holding a REAPER CLOTH, they say.$"

SE_Text_SpiritElder5:
	.string "Now the spirits can rest, and so\n"
	.string "can I. Thank you.$"

SE_Text_Spirit1:
	.string "…Leave… this place…\n"
	.string "…Or join us… forever…$"

SE_Text_Spirit2:
	.string "…Why do you climb…?\n"
	.string "…The dead… want silence…$"

SE_Text_Spirit3:
	.string "…This is the top…\n"
	.string "…There is no way back…$"

SE_Text_SpiritDefeat:
	.string "…Ah… I can see the light…$"

SE_Text_Spirit1After:
	.string "Wh-where am I? The spirit is gone…\n"
	.string "The others are still up there!$"

SE_Text_Spirit2After:
	.string "Thank you… One of us is still on the\n"
	.string "top floor. Please, save her!$"

SE_Text_Spirit3After:
	.string "It's over… The TOWER is quiet now.\n"
	.string "Please tell the elder in LAVENDER.$"

SE_Text_Looker0:
	.string "LOOKER: Ah, my friend! The CHAMPION\n"
	.string "of SINNOH, no less!\p"
	.string "TEAM GALACTIC's commanders have\n"
	.string "escaped. They want to finish CYRUS's\l"
	.string "plan using the three LAKES.\p"
	.string "MARS was last seen at LAKE VERITY.\n"
	.string "Will you help me one last time?$"

SE_Text_LookerHunting:
	.string "LOOKER: Check all three LAKES:\n"
	.string "VERITY, ACUITY and VALOR.\p"
	.string "And their scientist, CHARON, may be\n"
	.string "hiding in the GALACTIC WAREHOUSE\l"
	.string "here in VEILSTONE!$"

SE_Text_Looker5:
	.string "LOOKER: You caught CHARON! But his\n"
	.string "notes worry me…\p"
	.string "The INTERNATIONAL POLICE thanks you.\n"
	.string "Please, accept this.$"

SE_Text_LookerNext:
	.string "LOOKER: With that charm, POKéMON\n"
	.string "EGGS will be found more often at the\l"
	.string "DAY CARE.\p"
	.string "Now, CHARON's notes speak of a\n"
	.string "scientist working for CYRUS himself!\p"
	.string "He is hiding in the old GALACTIC\n"
	.string "BUILDING of ETERNA CITY. Go!$"

SE_Text_Looker6:
	.string "LOOKER: The scientist is in the\n"
	.string "GALACTIC BUILDING of ETERNA CITY.\l"
	.string "Be careful, my friend!$"

SE_Text_Looker7:
	.string "LOOKER: CYRUS is back?! In the\n"
	.string "GALACTIC HQ, here in VEILSTONE?\p"
	.string "This is beyond the INTERNATIONAL\n"
	.string "POLICE. Only you can face him!$"

SE_Text_LookerBye:
	.string "LOOKER: CYRUS gave up for good…\n"
	.string "The case of TEAM GALACTIC is closed\l"
	.string "at last, thanks to you.\p"
	.string "Now I must go. Another region needs\n"
	.string "LOOKER! Farewell, my friend!$"

SE_Text_MarsIntro:
	.string "MARS: Oh, it's you! I've been waiting\n"
	.string "to pay you back!\p"
	.string "CYRUS is gone, but his dream isn't!$"

SE_Text_MarsDefeat:
	.string "Ugh! You're even stronger now!$"

SE_Text_MarsAfter:
	.string "MARS: JUPITER is at LAKE ACUITY.\n"
	.string "She won't go easy on you!$"

SE_Text_JupiterIntro:
	.string "JUPITER: You beat MARS? Then I'll\n"
	.string "freeze you out right here!$"

SE_Text_JupiterDefeat:
	.string "How annoying…$"

SE_Text_JupiterAfter:
	.string "JUPITER: SATURN is at LAKE VALOR.\n"
	.string "Go on, if you can.$"

SE_Text_SaturnIntro:
	.string "SATURN: I thought it would be you.\p"
	.string "Honestly, I don't believe in CYRUS's\n"
	.string "plan anymore. But I'll battle you to\l"
	.string "see if I'm right to quit.$"

SE_Text_SaturnDefeat:
	.string "…Yes. I think I'm done.$"

SE_Text_SaturnAfter:
	.string "SATURN: CHARON is the one pushing\n"
	.string "this. He's in the GALACTIC WAREHOUSE\l"
	.string "in VEILSTONE. Stop him.$"

SE_Text_CharonIntro:
	.string "CHARON: Heh heh heh… You found me.\p"
	.string "With CYRUS gone, TEAM GALACTIC is\n"
	.string "mine! The LAKE trio will obey ME!$"

SE_Text_CharonDefeat:
	.string "Wh-what?! My genius, defeated?!$"

SE_Text_CharonAfter:
	.string "CHARON: Fine… I'll go quietly.\n"
	.string "LOOKER is waiting outside, isn't he?$"

SE_Text_RotomCollector:
	.string "I collect old appliances. This\n"
	.string "CHATEAU has an old TV that people\l"
	.string "say moves on its own at night…\p"
	.string "If you ever catch the ghost in it,\n"
	.string "please show it to me!$"

SE_Text_RotomCollectorNoRotom:
	.string "It's in the room upstairs, I think.\n"
	.string "Go and look, if you dare!$"

SE_Text_RotomCollectorShow:
	.string "That's ROTOM! It can get inside\n"
	.string "appliances and change its form!\p"
	.string "Here, take my catalog. With it,\n"
	.string "ROTOM can enter any appliance!$"

SE_Text_RotomCollectorAfter:
	.string "Use the ROTOM CATALOG from your BAG\n"
	.string "to choose ROTOM's appliance.$"

SE_Text_RotomCollectorDone:
	.string "How's ROTOM? Has it tried the\n"
	.string "lawn mower yet?$"
