FiveIsland_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FiveIsland_OnTransition
	.byte 0

FiveIsland_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_FIVE_ISLAND
	end

FiveIsland_EventScript_IslandSign::
	msgbox FiveIsland_Text_IslandSign, MSGBOX_SIGN
	end

FiveIsland_EventScript_BugCatcher::
	goto_if_ge VAR_SE_ROCKET_QUEST, 6, FiveIsland_EventScript_BugCatcherAfterQuest
	goto_if_lt VAR_SE_ROCKET_QUEST, 5, FiveIsland_EventScript_BugCatcherBeforeQuest
	msgbox FiveIsland_Text_WeirdBuildingInMeadow, MSGBOX_NPC
	end

FiveIsland_EventScript_BugCatcherAfterQuest::
	msgbox FiveIsland_Text_MeadowIsQuietAgain, MSGBOX_NPC
	end

FiveIsland_EventScript_BugCatcherBeforeQuest::
	msgbox FiveIsland_Text_EmptyWarehouseInMeadow, MSGBOX_NPC
	end

FiveIsland_Text_EmptyWarehouseInMeadow::
	.string "There's a big empty warehouse in the\n"
	.string "MEADOW. Nobody's used it in years.\p"
	.string "It's kind of spooky, but I still go\n"
	.string "and play there.$"

FiveIsland_Text_MeadowIsQuietAgain::
	.string "Those creepy guys left the MEADOW!\n"
	.string "I can play there again. Yay!$"

FiveIsland_EventScript_Fisher::
	goto_if_ge VAR_SE_ROCKET_QUEST, 6, FiveIsland_EventScript_FisherAfterQuest
	goto_if_lt VAR_SE_ROCKET_QUEST, 5, FiveIsland_EventScript_FisherBeforeQuest
	msgbox FiveIsland_Text_BeenGettingBusierAroundHere, MSGBOX_NPC
	end

FiveIsland_EventScript_FisherAfterQuest::
	msgbox FiveIsland_Text_FishAreBack, MSGBOX_NPC
	end

FiveIsland_EventScript_FisherBeforeQuest::
	msgbox FiveIsland_Text_QuietDayForFishing, MSGBOX_NPC
	end

FiveIsland_Text_QuietDayForFishing::
	.string "It's nice and quiet out here.\n"
	.string "Perfect weather for fishing!$"

FiveIsland_Text_FishAreBack::
	.string "Things have calmed down around here\n"
	.string "lately. The fish are biting again!$"

FiveIsland_Text_IslandSign::
	.string "FIVE ISLAND\n"
	.string "Chrono Island: Where Time Goes$"

FiveIsland_Text_WeirdBuildingInMeadow::
	.string "Oh, this stinks. I wanted to play in\n"
	.string "the MEADOW.\p"
	.string "But they put up a weird building\n"
	.string "on it, so I can't play there.$"

FiveIsland_Text_BeenGettingBusierAroundHere::
	.string "It's been getting busier around\n"
	.string "these parts lately.\p"
	.string "I haven't been catching many good\n"
	.string "fish lately, either.$"

