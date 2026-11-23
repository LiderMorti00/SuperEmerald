@ Super Emerald: the villain bases after the story.
@  Rocket's return goes on after Archer (VAR_SE_ROCKET_QUEST):
@   4 the Mahogany hideout (Johto): three grunts, then Archer and Ariana together
@   5 the Five Island Rocket Warehouse (Sevii): three grunts and Proton
@   6 the Celadon Rocket Hideout (Kanto): three grunts and Giovanni
@   7 done; the Silph Co. president gives a Porygon2
@  Looker's last case goes on after Charon (VAR_SE_GALACTIC_QUEST):
@   6 the Eterna Galactic Building: two grunts and a Galactic scientist
@   7 Cyrus in the Galactic HQ of Veilstone
@   8 done
@ The characters use FLAG_SE_QUEST_MAHOGANY..FLAG_SE_QUEST_CYRUS (sSEQuestObjects).

@ ===========================================================================
@ Rocket grunts
@ ===========================================================================
SE_EventScript_MahoganyGrunt1::
	trainerbattle_single TRAINER_SE_MAHOGANY_GRUNT_1, SE_Text_MahoganyGruntIntro, SE_Text_RocketGruntDefeat
	msgbox SE_Text_MahoganyGruntAfter, MSGBOX_AUTOCLOSE
	end
SE_EventScript_MahoganyGrunt2::
	trainerbattle_single TRAINER_SE_MAHOGANY_GRUNT_2, SE_Text_MahoganyGruntIntro2, SE_Text_RocketGruntDefeat
	msgbox SE_Text_MahoganyGruntAfter, MSGBOX_AUTOCLOSE
	end
SE_EventScript_MahoganyGrunt3::
	trainerbattle_single TRAINER_SE_MAHOGANY_GRUNT_3, SE_Text_MahoganyGruntIntro3, SE_Text_RocketGruntDefeat
	msgbox SE_Text_MahoganyGruntAfter3, MSGBOX_AUTOCLOSE
	end

SE_EventScript_WarehouseGrunt1::
	trainerbattle_single TRAINER_SE_WAREHOUSE_GRUNT_1, SE_Text_WarehouseGruntIntro, SE_Text_RocketGruntDefeat
	msgbox SE_Text_WarehouseGruntAfter, MSGBOX_AUTOCLOSE
	end
SE_EventScript_WarehouseGrunt2::
	trainerbattle_single TRAINER_SE_WAREHOUSE_GRUNT_2, SE_Text_WarehouseGruntIntro2, SE_Text_RocketGruntDefeat
	msgbox SE_Text_WarehouseGruntAfter, MSGBOX_AUTOCLOSE
	end
SE_EventScript_WarehouseGrunt3::
	trainerbattle_single TRAINER_SE_WAREHOUSE_GRUNT_3, SE_Text_WarehouseGruntIntro3, SE_Text_RocketGruntDefeat
	msgbox SE_Text_WarehouseGruntAfter3, MSGBOX_AUTOCLOSE
	end

SE_EventScript_CeladonGrunt1::
	trainerbattle_single TRAINER_SE_CELADON_GRUNT_1, SE_Text_CeladonGruntIntro, SE_Text_RocketGruntDefeat
	msgbox SE_Text_CeladonGruntAfter, MSGBOX_AUTOCLOSE
	end
SE_EventScript_CeladonGrunt2::
	trainerbattle_single TRAINER_SE_CELADON_GRUNT_2, SE_Text_CeladonGruntIntro2, SE_Text_RocketGruntDefeat
	msgbox SE_Text_CeladonGruntAfter, MSGBOX_AUTOCLOSE
	end
SE_EventScript_CeladonGrunt3::
	trainerbattle_single TRAINER_SE_CELADON_GRUNT_3, SE_Text_CeladonGruntIntro3, SE_Text_RocketGruntDefeat
	msgbox SE_Text_CeladonGruntAfter3, MSGBOX_AUTOCLOSE
	end

@ ===========================================================================
@ Mahogany hideout: Archer and Ariana
@ ===========================================================================
SE_EventScript_RocketFinal::
	lock
	faceplayer
	goto_if_defeated TRAINER_SE_ARIANA_FINAL, SE_EventScript_RocketFinal_Reward
	msgbox SE_Text_RocketFinalIntro, MSGBOX_DEFAULT
	special HasEnoughMonsForDoubleBattle
	goto_if_ne VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS, SE_EventScript_RocketFinalNeedTwo
	closemessage
	cleartrainerflag TRAINER_SE_ARCHER_FINAL
	cleartrainerflag TRAINER_SE_ARIANA_FINAL
	trainerbattle_two_trainers_sn TRAINER_SE_ARCHER_FINAL, SE_Text_ArcherFinalDefeat, TRAINER_SE_ARIANA_FINAL, SE_Text_ArianaFinalDefeat
SE_EventScript_RocketFinal_Reward::
	msgbox SE_Text_RocketFinalAfter, MSGBOX_DEFAULT
	givemon SPECIES_LARVITAR, 50
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, SE_EventScript_BaseRewardNoRoom
	bufferspeciesname STR_VAR_1, SPECIES_LARVITAR
	call SE_EventScript_BaseMonReceived
	msgbox SE_Text_RocketFinalBye, MSGBOX_DEFAULT
	closemessage
	setvar VAR_SE_ROCKET_QUEST, 5
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_SE_FINAL_ARCHER
	removeobject LOCALID_SE_FINAL_ARIANA
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

SE_EventScript_RocketFinalNeedTwo::
	msgbox SE_Text_RocketFinalNeedTwo, MSGBOX_DEFAULT
	release
	end

@ ===========================================================================
@ Five Island warehouse: Proton
@ ===========================================================================
SE_EventScript_WarehouseProton::
	lock
	faceplayer
	goto_if_defeated TRAINER_SE_WAREHOUSE_ADMIN, SE_EventScript_WarehouseProton_Reward
	msgbox SE_Text_WarehouseProtonIntro, MSGBOX_DEFAULT
	closemessage
	cleartrainerflag TRAINER_SE_WAREHOUSE_ADMIN
	trainerbattle_no_intro TRAINER_SE_WAREHOUSE_ADMIN, SE_Text_WarehouseProtonDefeat
SE_EventScript_WarehouseProton_Reward::
	msgbox SE_Text_WarehouseProtonAfter, MSGBOX_DEFAULT
	call_if_unset FLAG_CAN_USE_ROCKET_HIDEOUT_LIFT, SE_EventScript_WarehouseProtonCheckKeySpace
	giveitem ITEM_CHOICE_SCARF
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_QuestBagFull
	msgbox SE_Text_WarehouseProtonBye, MSGBOX_DEFAULT
	@ the Celadon hideout was never opened in this save (Kanto starts after its story): open it,
	@ and give the LIFT KEY, since its grunt is gone
	setflag FLAG_OPENED_ROCKET_HIDEOUT
	goto_if_set FLAG_CAN_USE_ROCKET_HIDEOUT_LIFT, SE_EventScript_WarehouseProtonDone
	giveitem ITEM_LIFT_KEY
	setflag FLAG_CAN_USE_ROCKET_HIDEOUT_LIFT
	setflag FLAG_HIDE_LIFT_KEY
SE_EventScript_WarehouseProtonDone::
	setvar VAR_SE_ROCKET_QUEST, 6
	goto SE_EventScript_QuestLeave

SE_EventScript_WarehouseProtonCheckKeySpace::
	checkitemspace ITEM_LIFT_KEY
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_QuestBagFull
	return

@ ===========================================================================
@ Celadon hideout: Giovanni
@ ===========================================================================
SE_EventScript_GiovanniFinal::
	lock
	faceplayer
	goto_if_defeated TRAINER_SE_GIOVANNI_FINAL, SE_EventScript_GiovanniFinal_Reward
	msgbox SE_Text_GiovanniFinalIntro, MSGBOX_DEFAULT
	closemessage
	cleartrainerflag TRAINER_SE_GIOVANNI_FINAL
	trainerbattle_no_intro TRAINER_SE_GIOVANNI_FINAL, SE_Text_GiovanniFinalDefeat
SE_EventScript_GiovanniFinal_Reward::
	msgbox SE_Text_GiovanniFinalAfter, MSGBOX_DEFAULT
	giveitem ITEM_MASTER_BALL
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_QuestBagFull
	msgbox SE_Text_GiovanniFinalBye, MSGBOX_DEFAULT
	setvar VAR_SE_ROCKET_QUEST, 7
	goto SE_EventScript_QuestLeave

@ Called by the Silph Co. president: once Giovanni is beaten, he gives a Porygon2 (once)
SE_EventScript_SilphPresidentGift::
	goto_if_lt VAR_SE_ROCKET_QUEST, 7, SE_EventScript_SilphPresidentGiftNone
	goto_if_set FLAG_SE_SILPH_GIFT, SE_EventScript_SilphPresidentGiftNone
	msgbox SE_Text_SilphPresidentGift, MSGBOX_DEFAULT
	givemon SPECIES_PORYGON2, 50, ITEM_DUBIOUS_DISC
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, SE_EventScript_BaseRewardNoRoom
	bufferspeciesname STR_VAR_1, SPECIES_PORYGON2
	call SE_EventScript_BaseMonReceived
	setflag FLAG_SE_SILPH_GIFT
	msgbox SE_Text_SilphPresidentGiftAfter, MSGBOX_DEFAULT
	release
	end
SE_EventScript_SilphPresidentGiftNone::
	return

@ ===========================================================================
@ Galactic grunts, the Eterna scientist and Cyrus
@ ===========================================================================
SE_EventScript_EternaGrunt1::
	trainerbattle_single TRAINER_SE_ETERNA_GRUNT_1, SE_Text_EternaGruntIntro, SE_Text_GalacticGruntDefeat
	msgbox SE_Text_EternaGruntAfter, MSGBOX_AUTOCLOSE
	end
SE_EventScript_EternaGrunt2::
	trainerbattle_single TRAINER_SE_ETERNA_GRUNT_2, SE_Text_EternaGruntIntro2, SE_Text_GalacticGruntDefeat
	msgbox SE_Text_EternaGruntAfter2, MSGBOX_AUTOCLOSE
	end

SE_EventScript_EternaScientist::
	lock
	faceplayer
	goto_if_defeated TRAINER_SE_ETERNA_SCIENTIST, SE_EventScript_EternaScientist_Reward
	msgbox SE_Text_EternaScientistIntro, MSGBOX_DEFAULT
	closemessage
	cleartrainerflag TRAINER_SE_ETERNA_SCIENTIST
	trainerbattle_no_intro TRAINER_SE_ETERNA_SCIENTIST, SE_Text_EternaScientistDefeat
SE_EventScript_EternaScientist_Reward::
	msgbox SE_Text_EternaScientistAfter, MSGBOX_DEFAULT
	givemon SPECIES_GIBLE, 50
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, SE_EventScript_BaseRewardNoRoom
	bufferspeciesname STR_VAR_1, SPECIES_GIBLE
	call SE_EventScript_BaseMonReceived
	msgbox SE_Text_EternaScientistBye, MSGBOX_DEFAULT
	setvar VAR_SE_GALACTIC_QUEST, 7
	goto SE_EventScript_QuestLeave

SE_EventScript_CyrusFinal::
	lock
	faceplayer
	goto_if_defeated TRAINER_SE_CYRUS_FINAL, SE_EventScript_CyrusFinal_Reward
	msgbox SE_Text_CyrusFinalIntro, MSGBOX_DEFAULT
	closemessage
	cleartrainerflag TRAINER_SE_CYRUS_FINAL
	trainerbattle_no_intro TRAINER_SE_CYRUS_FINAL, SE_Text_CyrusFinalDefeat
SE_EventScript_CyrusFinal_Reward::
	msgbox SE_Text_CyrusFinalAfter, MSGBOX_DEFAULT
	giveitem ITEM_GOLD_BOTTLE_CAP
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_QuestBagFull
	msgbox SE_Text_CyrusFinalBye, MSGBOX_DEFAULT
	setvar VAR_SE_GALACTIC_QUEST, 8
	goto SE_EventScript_QuestLeave

@ ===========================================================================
@ Shared
@ ===========================================================================
SE_EventScript_BaseMonReceived::
	playfanfare MUS_OBTAIN_ITEM
	message SE_Text_BaseMonReceived
	waitmessage
	waitfanfare
	return

SE_EventScript_BaseRewardNoRoom::
	msgbox SE_Text_BaseRewardNoRoom, MSGBOX_DEFAULT
	release
	end

@ ===========================================================================
@ Texts
@ ===========================================================================
SE_Text_BaseMonReceived:
	.string "{PLAYER} received {STR_VAR_1}!$"

SE_Text_BaseRewardNoRoom:
	.string "Your party and your PC boxes are\n"
	.string "full… Make some room first!$"

SE_Text_RocketGruntDefeat:
	.string "Gah! The CHAMPION again?!$"

SE_Text_MahoganyGruntIntro:
	.string "This hideout is ours again!\n"
	.string "Nobody gets past me!$"

SE_Text_MahoganyGruntIntro2:
	.string "ARCHER said TEAM ROCKET is coming\n"
	.string "back for real this time!$"

SE_Text_MahoganyGruntIntro3:
	.string "Intruder! You won't reach the\n"
	.string "executives!$"

SE_Text_MahoganyGruntAfter:
	.string "Our executives are on the bottom\n"
	.string "floor. They'll crush you!$"

SE_Text_MahoganyGruntAfter3:
	.string "The stairs on the left lead to\n"
	.string "ARCHER's room… Oops.$"

SE_Text_RocketFinalIntro:
	.string "ARCHER: So you followed us all the\n"
	.string "way to MAHOGANY.\p"
	.string "ARIANA: This hideout is where it all\n"
	.string "began. It's where we'll rise again!\p"
	.string "ARCHER: Two against one, CHAMPION.\n"
	.string "Let's see you handle that!$"

SE_Text_RocketFinalNeedTwo:
	.string "ARIANA: Only one POKéMON that can\n"
	.string "fight? Come back with two, at least!$"

SE_Text_ArcherFinalDefeat:
	.string "ARCHER: Impossible… Again?!$"

SE_Text_ArianaFinalDefeat:
	.string "ARIANA: Ugh! You're a nightmare!$"

SE_Text_RocketFinalAfter:
	.string "ARCHER: …Fine. You win.\p"
	.string "We were raising this LARVITAR to be\n"
	.string "the strongest POKéMON of TEAM\l"
	.string "ROCKET. Take it. It likes you better.$"

SE_Text_RocketFinalBye:
	.string "ARIANA: GIOVANNI answered at last.\n"
	.string "PROTON has his supplies in a\l"
	.string "warehouse on FIVE ISLAND.\p"
	.string "ARCHER: Those crates are all he\n"
	.string "needs to start over.\p"
	.string "Our boss is waiting in KANTO.\n"
	.string "You'll never find him!$"

SE_Text_WarehouseGruntIntro:
	.string "This warehouse is off limits!\n"
	.string "Get out of here!$"

SE_Text_WarehouseGruntIntro2:
	.string "These crates are for GIOVANNI.\n"
	.string "Hands off!$"

SE_Text_WarehouseGruntIntro3:
	.string "PROTON is in charge here.\n"
	.string "You'll have to beat me first!$"

SE_Text_WarehouseGruntAfter:
	.string "Once GIOVANNI is back, we'll take\n"
	.string "KANTO and JOHTO in one go!$"

SE_Text_WarehouseGruntAfter3:
	.string "PROTON is guarding the stolen goods\n"
	.string "at the back of the warehouse.$"

SE_Text_WarehouseProtonIntro:
	.string "PROTON: You again? Do you enjoy\n"
	.string "ruining everything?\p"
	.string "This time I'm not losing. The boss\n"
	.string "is counting on me!$"

SE_Text_WarehouseProtonDefeat:
	.string "Why does this keep happening?!$"

SE_Text_WarehouseProtonAfter:
	.string "PROTON: Fine, fine… Take one of\n"
	.string "these. We have no use for it now.$"

SE_Text_WarehouseProtonBye:
	.string "PROTON: The boss is in the old\n"
	.string "hideout under the CELADON GAME\l"
	.string "CORNER. Go, if you're so brave.\p"
	.string "Here, the key to its lift. He'll\n"
	.string "teach you what real power is!$"

SE_Text_CeladonGruntIntro:
	.string "GIOVANNI is back! TEAM ROCKET is\n"
	.string "back! You're too late!$"

SE_Text_CeladonGruntIntro2:
	.string "The boss doesn't want visitors.\n"
	.string "Especially not you!$"

SE_Text_CeladonGruntIntro3:
	.string "You beat our executives? Then I'm\n"
	.string "the last wall before the boss!$"

SE_Text_CeladonGruntAfter:
	.string "Just wait until the boss sees you…$"

SE_Text_CeladonGruntAfter3:
	.string "The boss is waiting on the lowest\n"
	.string "floor…$"

SE_Text_GiovanniFinalIntro:
	.string "GIOVANNI: So you're the CHAMPION who\n"
	.string "beat my executives in JOHTO.\p"
	.string "I left TEAM ROCKET once because a\n"
	.string "child defeated me.\p"
	.string "I came back to see if that child was\n"
	.string "a fluke. Show me your power!$"

SE_Text_GiovanniFinalDefeat:
	.string "…I see. It was no fluke.$"

SE_Text_GiovanniFinalAfter:
	.string "GIOVANNI: Your bond with your\n"
	.string "POKéMON is stronger than my ambition.\p"
	.string "Take this MASTER BALL we took from\n"
	.string "SILPH. A true TRAINER should have it.$"

SE_Text_GiovanniFinalBye:
	.string "GIOVANNI: TEAM ROCKET is finished.\n"
	.string "I'll train alone, far from here.\p"
	.string "Until we meet again, CHAMPION.$"

SE_Text_SilphPresidentGift:
	.string "PRESIDENT: I heard the news!\n"
	.string "You stopped GIOVANNI for good!\p"
	.string "SILPH can finally work in peace.\n"
	.string "Please, accept our latest creation!$"

SE_Text_SilphPresidentGiftAfter:
	.string "PRESIDENT: That PORYGON2 was made\n"
	.string "right here at SILPH.\p"
	.string "It holds a DUBIOUS DISC… Our\n"
	.string "engineers say it does something odd.$"

SE_Text_GalacticGruntDefeat:
	.string "No way! TEAM GALACTIC can't lose!$"

SE_Text_EternaGruntIntro:
	.string "This building still belongs to\n"
	.string "TEAM GALACTIC! Get lost!$"

SE_Text_EternaGruntIntro2:
	.string "Our scientist is working upstairs.\n"
	.string "Don't you dare disturb him!$"

SE_Text_EternaGruntAfter:
	.string "We're just following orders…$"

SE_Text_EternaGruntAfter2:
	.string "The scientist is on the top floor.\p"
	.string "He got a message signed by our\n"
	.string "old boss. It gave me chills.\p"
	.string "No one had heard from him since\n"
	.string "he vanished at SPEAR PILLAR.$"

SE_Text_EternaScientistIntro:
	.string "TRAVIS: CHARON's\n"
	.string "assistant? No, I work for CYRUS!\p"
	.string "CYRUS came back from the other world.\n"
	.string "I won't let you get in his way!$"

SE_Text_EternaScientistDefeat:
	.string "My calculations were off…$"

SE_Text_EternaScientistAfter:
	.string "TRAVIS: CYRUS wanted this\n"
	.string "GIBLE for his new team…\p"
	.string "Take it. It never liked me anyway.$"

SE_Text_EternaScientistBye:
	.string "TRAVIS: CYRUS is waiting\n"
	.string "in his old office, at the GALACTIC\l"
	.string "HQ in VEILSTONE.$"

SE_Text_CyrusFinalIntro:
	.string "CYRUS: So you are the one who\n"
	.string "stopped my commanders again.\p"
	.string "I saw a world without spirit,\n"
	.string "without strife. And yet…\p"
	.string "I came back. I must know why.\n"
	.string "Perhaps battling you will tell me.$"

SE_Text_CyrusFinalDefeat:
	.string "…This feeling. I remember it.$"

SE_Text_CyrusFinalAfter:
	.string "CYRUS: The strength of your spirit…\n"
	.string "It is what I tried to erase.\p"
	.string "Perhaps I was the one who was wrong.\n"
	.string "Take this. I no longer need it.$"

SE_Text_CyrusFinalBye:
	.string "CYRUS: TEAM GALACTIC is over.\n"
	.string "Tell LOOKER he can rest.\p"
	.string "Farewell… CHAMPION.$"
