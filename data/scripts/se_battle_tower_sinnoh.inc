@ Super Emerald: Sinnoh's Battle Tower runs Emerald's Battle Tower scripts. While
@ FLAG_SE_SINNOH_TOWER is set, their warps go to the Sinnoh maps and the Frontier Brain
@ is Tower Tycoon Palmer (see SE_GetBrainInfo in frontier_util.c).

SE_BattleTowerSinnoh_SetFlag::
	setflag FLAG_SE_SINNOH_TOWER
	end

SE_BattleTowerSinnoh_WarpToElevator::
	warp MAP_BATTLE_TOWE_ELEVATOR_SINNOH, 1, 6
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

SE_BattleTowerSinnoh_WarpToCorridor::
	warp MAP_BATTLE_TOWER_CORRIDOR_SINNOH, 8, 1
	waitstate
	return

SE_BattleTowerSinnoh_WarpToBattleRoom::
	warp MAP_BATTLE_TOWER_BATTLE_ROOM_SINNOH, 4, 8
	waitstate
	end

SE_BattleTowerSinnoh_WarpToLobbySingles::
	warp MAP_BATTLE_TOWER_SINNOH, 6, 6
	waitstate
	end

SE_BattleTowerSinnoh_WarpToLobbyDoubles::
	warp MAP_BATTLE_TOWER_SINNOH, 10, 6
	waitstate
	end

@ Frontier Brain texts: Anabel in Hoenn, Palmer in Sinnoh

SE_BattleTowerSinnoh_BrainGreeting::
	goto_if_set FLAG_SE_SINNOH_TOWER, SE_BattleTowerSinnoh_BrainGreeting_Palmer
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_GreetingsImAnabel, MSGBOX_DEFAULT
	return
SE_BattleTowerSinnoh_BrainGreeting_Palmer:
	msgbox SE_Text_PalmerGreeting, MSGBOX_DEFAULT
	return
SE_BattleTowerSinnoh_BrainSilverWon::
	goto_if_set FLAG_SE_SINNOH_TOWER, SE_BattleTowerSinnoh_BrainSilverWon_Palmer
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_AnabelTalentShallBeRecognized, MSGBOX_DEFAULT
	return
SE_BattleTowerSinnoh_BrainSilverWon_Palmer:
	msgbox SE_Text_PalmerSilverWon, MSGBOX_DEFAULT
	return
SE_BattleTowerSinnoh_BrainGoldIntro::
	goto_if_set FLAG_SE_SINNOH_TOWER, SE_BattleTowerSinnoh_BrainGoldIntro_Palmer
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_AnabelYouCameBack, MSGBOX_DEFAULT
	return
SE_BattleTowerSinnoh_BrainGoldIntro_Palmer:
	msgbox SE_Text_PalmerGoldIntro, MSGBOX_DEFAULT
	return
SE_BattleTowerSinnoh_BrainGoldWon::
	goto_if_set FLAG_SE_SINNOH_TOWER, SE_BattleTowerSinnoh_BrainGoldWon_Palmer
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_AnabelCongratsYourPassPlease, MSGBOX_DEFAULT
	return
SE_BattleTowerSinnoh_BrainGoldWon_Palmer:
	msgbox SE_Text_PalmerGoldWon, MSGBOX_DEFAULT
	return
SE_BattleTowerSinnoh_BrainSalonMaidenOnHerWay::
	goto_if_set FLAG_SE_SINNOH_TOWER, SE_BattleTowerSinnoh_BrainSalonMaidenOnHerWay_Palmer
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_SalonMaidenOnHerWay, MSGBOX_DEFAULT
	return
SE_BattleTowerSinnoh_BrainSalonMaidenOnHerWay_Palmer:
	msgbox SE_Text_PalmerOnHisWay, MSGBOX_DEFAULT
	return
SE_BattleTowerSinnoh_BrainLetMeSeeYourTalent::
	goto_if_set FLAG_SE_SINNOH_TOWER, SE_BattleTowerSinnoh_BrainLetMeSeeYourTalent_Palmer
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_LetMeSeeYourTalent, MSGBOX_DEFAULT
	return
SE_BattleTowerSinnoh_BrainLetMeSeeYourTalent_Palmer:
	msgbox SE_Text_PalmerLetsGo, MSGBOX_DEFAULT
	return
SE_BattleTowerSinnoh_BrainUntilNextTime::
	goto_if_set FLAG_SE_SINNOH_TOWER, SE_BattleTowerSinnoh_BrainUntilNextTime_Palmer
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_UntilNextTime, MSGBOX_DEFAULT
	return
SE_BattleTowerSinnoh_BrainUntilNextTime_Palmer:
	msgbox SE_Text_PalmerUntilNextTime, MSGBOX_DEFAULT
	return
SE_BattleTowerSinnoh_BrainLetsBeginShallWe::
	goto_if_set FLAG_SE_SINNOH_TOWER, SE_BattleTowerSinnoh_BrainLetsBeginShallWe_Palmer
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_LetsBeginShallWe, MSGBOX_DEFAULT
	return
SE_BattleTowerSinnoh_BrainLetsBeginShallWe_Palmer:
	msgbox SE_Text_PalmerLetsGoGold, MSGBOX_DEFAULT
	return
SE_BattleTowerSinnoh_BrainWishICouldBattleYouAgain::
	goto_if_set FLAG_SE_SINNOH_TOWER, SE_BattleTowerSinnoh_BrainWishICouldBattleYouAgain_Palmer
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_WishICouldBattleYouAgain, MSGBOX_DEFAULT
	return
SE_BattleTowerSinnoh_BrainWishICouldBattleYouAgain_Palmer:
	msgbox SE_Text_PalmerWishBattleAgain, MSGBOX_DEFAULT
	return

SE_BattleTowerSinnoh_BrainReadyMessage::
	goto_if_set FLAG_SE_SINNOH_TOWER, SE_BattleTowerSinnoh_BrainReadyMessage_Palmer
	message BattleFrontier_BattleTowerBattleRoom_Text_ReadyForSalonMaiden
	return
SE_BattleTowerSinnoh_BrainReadyMessage_Palmer:
	message SE_Text_PalmerReady
	return

SE_Text_PalmerOnHisWay:
	.string "Excuse me, but…\p"
	.string "Our TOWER TYCOON, PALMER, is on his\n"
	.string "way here in hopes of battling you.\p"
	.string "He should be arriving very shortly.$"

SE_Text_PalmerReady:
	.string "You will be facing the TOWER TYCOON.\n"
	.string "Are you prepared?$"

SE_Text_PalmerGreeting:
	.string "Hey! I'm PALMER, the TOWER TYCOON!\p"
	.string "I keep hearing about a trainer who\n"
	.string "became CHAMPION in four regions.\p"
	.string "Is that really you? Ha! Then I can't\n"
	.string "wait any longer!\p"
	.string "Trainers who've come this far always\n"
	.string "make my heart pound!$"

SE_Text_PalmerLetsGo:
	.string "Show me everything you've got!$"

SE_Text_PalmerSilverWon:
	.string "PALMER: Ha! That was a fantastic\n"
	.string "battle! You earned this.\p"
	.string "Let me see your FRONTIER PASS!$"

SE_Text_PalmerUntilNextTime:
	.string "Keep on winning, and I'll be back\n"
	.string "with my true team.\p"
	.string "See you at the top of the TOWER!$"

SE_Text_PalmerGoldIntro:
	.string "PALMER: You came back! I knew you\n"
	.string "would!\p"
	.string "This time I'm using my strongest\n"
	.string "POKéMON. No holding back!$"

SE_Text_PalmerLetsGoGold:
	.string "Here I come!$"

SE_Text_PalmerGoldWon:
	.string "PALMER: Bravo! You're the strongest\n"
	.string "trainer I've ever faced!\p"
	.string "Your FRONTIER PASS, please!$"

SE_Text_PalmerWishBattleAgain:
	.string "Ha ha! My son BARRY is going to be\n"
	.string "so jealous when I tell him about this!\p"
	.string "Come back anytime. I'd love to battle\n"
	.string "you again!$"
