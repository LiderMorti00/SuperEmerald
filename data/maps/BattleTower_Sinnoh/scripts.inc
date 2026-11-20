@ Super Emerald: Sinnoh's Battle Tower (Battle Park). It runs Emerald's Battle Tower scripts;
@ FLAG_SE_SINNOH_TOWER makes their warps lead to the Sinnoh maps and Palmer the Frontier Brain.
@ Only single and double battles are offered here.
BattleTower_Sinnoh_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattleTowerLobby_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, BattleTower_Sinnoh_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleTowerLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleTowerLobby_OnWarp
	.byte 0

BattleTower_Sinnoh_OnTransition:
	setflag FLAG_SE_SINNOH_TOWER
	special SE_UseSinnohTowerData
	goto SE_BattleTowerLobby_OnTransition
