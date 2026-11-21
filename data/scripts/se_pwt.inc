@ Super Emerald: Pokemon World Tournament (Johto, Route 40).
@ The PWT maps have their own copies of the Battle Dome scripts (data/maps/PokemonWorldTournament*);
@ the C side knows it's the PWT by the map the player is on (SE_IsPwt).
@ See src/se_pwt.c.

@ The save holds the Dome records of one facility at a time; the other's are kept in vars
@ (see SE_SwapDomeData). PWT lobby: PWT records. Hoenn's Dome lobby and the PWT outside: Hoenn's.
SE_Pwt_UsePwtRecords::
	special SE_EnterPwt
	end

SE_Dome_UseHoennRecords::
	special SE_LeavePwt
	end

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
	goto_if_ge VAR_RESULT, SE_PWT_CUPS_COUNT, PokemonWorldTournamentLobby_EventScript_CancelChallenge
	copyvar VAR_SE_PWT_CUP, VAR_RESULT
	special SE_PwtBufferCupName
	msgbox SE_Text_PwtCupChosen, MSGBOX_DEFAULT
	setvar VAR_RESULT, FRONTIER_LVL_50
	goto PokemonWorldTournamentLobby_EventScript_CheckEligible

@ First win of each cup: a prize typical of the region
SE_Pwt_GiveCupPrize::
	special SE_PwtGetCupPrize
	goto_if_eq VAR_RESULT, FALSE, SE_Pwt_GiveCupPrizeEnd
	special SE_PwtBufferCupName
	msgbox SE_Text_PwtFirstWinPrize, MSGBOX_DEFAULT
	giveitem VAR_0x8004
	goto_if_eq VAR_RESULT, FALSE, SE_Pwt_GiveCupPrizeBagFull
	special SE_PwtSetCupPrizeReceived
SE_Pwt_GiveCupPrizeEnd:
	return
SE_Pwt_GiveCupPrizeBagFull:
	msgbox SE_Text_PwtPrizeBagFull, MSGBOX_DEFAULT
	return

SE_Pwt_ExplainCups::
	msgbox SE_Text_PwtExplainCups, MSGBOX_DEFAULT
	return

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

SE_Text_PwtFirstWinPrize:
	.string "This is your first win in the\n"
	.string "{STR_VAR_3}!\p"
	.string "Please accept this special prize!$"

SE_Text_PwtPrizeBagFull:
	.string "Oh, your BAG is full…\n"
	.string "Win this cup again to get your prize!$"
