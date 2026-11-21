@ Super Emerald: Pokemon World Tournament (Johto, Route 40).
@ The PWT maps are copies of the Battle Dome ones and use its scripts: FLAG_SE_PWT is set in the
@ PWT lobby (SE_EnterPwt) and cleared outside and in Hoenn's Dome lobby (SE_LeavePwt). While it's
@ set, the Dome engine uses the PWT roster and the warps below lead to the PWT maps.
@ See src/se_pwt.c.

SE_Pwt_EnterOnTransition::
	special SE_EnterPwt
	end

SE_Pwt_LeaveOnTransition::
	special SE_LeavePwt
	end

@ "BATTLE DOME" in the Dome texts is {STR_VAR_3}
SE_Pwt_BufferDomeName::
	goto_if_set FLAG_SE_PWT, SE_Pwt_BufferPwtName
	bufferstring STR_VAR_3, SE_Text_BattleDomeName
	return
SE_Pwt_BufferPwtName:
	bufferstring STR_VAR_3, SE_Text_PwtName
	return

SE_Pwt_ShowDomePlayer::
	goto_if_set FLAG_SE_PWT, SE_Pwt_ShowPwtPlayer
	showobjectat LOCALID_DOME_PLAYER, MAP_BATTLE_FRONTIER_BATTLE_DOME_BATTLE_ROOM
	return
SE_Pwt_ShowPwtPlayer:
	showobjectat LOCALID_DOME_PLAYER, MAP_POKEMON_WORLD_TOURNAMENT_ROOM
	return

SE_Pwt_HideDomePlayer::
	goto_if_set FLAG_SE_PWT, SE_Pwt_HidePwtPlayer
	hideobjectat LOCALID_DOME_PLAYER, MAP_BATTLE_FRONTIER_BATTLE_DOME_BATTLE_ROOM
	return
SE_Pwt_HidePwtPlayer:
	hideobjectat LOCALID_DOME_PLAYER, MAP_POKEMON_WORLD_TOURNAMENT_ROOM
	return

@ Lobby: choose the cup instead of the level mode (always level 50)
SE_Pwt_ChooseCup::
	message SE_Text_PwtWhichCup
	waitmessage
	dynmultipush SE_Text_CupKanto, SE_PWT_CUP_KANTO
	dynmultipush SE_Text_CupJohto, SE_PWT_CUP_JOHTO
	dynmultipush SE_Text_CupHoenn, SE_PWT_CUP_HOENN
	dynmultipush SE_Text_CupSinnoh, SE_PWT_CUP_SINNOH
	dynmultipush SE_Text_CupKalos, SE_PWT_CUP_KALOS
	dynmultipush SE_Text_CupChampions, SE_PWT_CUP_CHAMPIONS
	dynmultipush SE_Text_CupWorld, SE_PWT_CUP_WORLD
	dynmultipush gText_Cancel, SE_PWT_CUPS_COUNT
	dynmultistack 0, 0, FALSE, 5, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto_if_ge VAR_RESULT, SE_PWT_CUPS_COUNT, BattleFrontier_BattleDomeLobby_EventScript_CancelChallenge
	copyvar VAR_SE_PWT_CUP, VAR_RESULT
	special SE_PwtBufferCupName
	msgbox SE_Text_PwtCupChosen, MSGBOX_DEFAULT
	setvar VAR_RESULT, FRONTIER_LVL_50
	goto BattleFrontier_BattleDomeLobby_EventScript_CheckEligible

SE_Pwt_ExplainCups::
	msgbox SE_Text_PwtExplainCups, MSGBOX_DEFAULT
	return

@ Warps of the Dome scripts while in the PWT
SE_PwtWarp_1::
	warp MAP_POKEMON_WORLD_TOURNAMENT_CORRIDOR, 23, 6
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

SE_PwtWarp_2::
	warp MAP_POKEMON_WORLD_TOURNAMENT_PRE_BATTLE_ROOM, 5, 7
	waitstate
	end

SE_PwtWarp_3::
	warp MAP_POKEMON_WORLD_TOURNAMENT_ROOM, 9, 5
	setvar VAR_TEMP_0, 0
	waitstate
	end

SE_PwtWarp_4::
	warp MAP_POKEMON_WORLD_TOURNAMENT_PRE_BATTLE_ROOM, 5, 3
	waitstate
	end

SE_PwtWarp_5::
	warp MAP_POKWMON_WORLD_TOURNAMENT_LOBBY, 5, 11
	waitstate
	end

SE_PwtWarp_6::
	warp MAP_POKWMON_WORLD_TOURNAMENT_LOBBY, 17, 11
	waitstate
	end

SE_Text_BattleDomeName:
	.string "BATTLE DOME$"
SE_Text_PwtName:
	.string "PWT$"
SE_Text_CupKanto:
	.string "KANTO LEADERS$"
SE_Text_CupJohto:
	.string "JOHTO LEADERS$"
SE_Text_CupHoenn:
	.string "HOENN LEADERS$"
SE_Text_CupSinnoh:
	.string "SINNOH LEADERS$"
SE_Text_CupKalos:
	.string "KALOS LEADERS$"
SE_Text_CupChampions:
	.string "CHAMPIONS$"
SE_Text_CupWorld:
	.string "WORLD LEADERS$"

SE_Text_PwtWhichCup:
	.string "Which tournament would you like\n"
	.string "to enter?$"

SE_Text_PwtCupChosen:
	.string "The {STR_VAR_3}!\p"
	.string "In the POKéMON WORLD TOURNAMENT,\n"
	.string "every POKéMON battles at level 50.$"

SE_Text_PwtExplainCups:
	.string "At the POKéMON WORLD TOURNAMENT,\n"
	.string "you face the GYM LEADERS, ELITE FOUR\l"
	.string "and CHAMPIONS of every region!\p"
	.string "In the LEADERS cups you battle the\n"
	.string "stars of KANTO, JOHTO, HOENN, SINNOH\l"
	.string "or KALOS.\p"
	.string "The CHAMPIONS CUP gathers the\n"
	.string "CHAMPIONS, and in the WORLD LEADERS\l"
	.string "CUP anyone could be your opponent.\p"
	.string "Every POKéMON is set to level 50\n"
	.string "while battling, whatever its level.\p"
	.string "Win the tournament to earn\n"
	.string "BATTLE POINTS!$"
