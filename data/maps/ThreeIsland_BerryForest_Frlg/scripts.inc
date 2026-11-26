ThreeIsland_BerryForest_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ThreeIsland_BerryForest_OnTransition
	.byte 0

ThreeIsland_BerryForest_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_THREE_ISLAND_BERRY_FOREST
	setescapewarp MAP_THREE_ISLAND_BOND_BRIDGE, 12, 6
	end

ThreeIsland_BerryForest_EventScript_WelcomeSign::
	msgbox ThreeIsland_BerryForest_Text_WelcomeToBerryForest, MSGBOX_SIGN
	end

ThreeIsland_BerryForest_EventScript_BewareSign::
	msgbox ThreeIsland_BerryForest_Text_BewareWildBerryLovingMons, MSGBOX_SIGN
	end

ThreeIsland_BerryForest_Text_WelcomeToBerryForest::
	.string "Welcome to the BERRY FOREST\p"
	.string "Be friendly and share BERRIES with\n"
	.string "others and POKéMON.$"

ThreeIsland_BerryForest_Text_BewareWildBerryLovingMons::
	.string "Beware of wild, BERRY-loving\n"
	.string "POKéMON!$"

