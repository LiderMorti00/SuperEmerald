BurnedTower_B1F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SE_EventScript_BurnedTowerB1FOnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SE_BurnedTowerB1F_OnFrame
	.byte 0

BurnedTower_B1F_EventScript_Item_UltraBall::
	finditem ITEM_ULTRA_BALL
	end

SE_J_BurnedTower_B1F_hns_BurnedTower_B1F_EventScript_Item_Taunt::
	finditem ITEM_TM_TAUNT
	end

SE_BurnedTowerB1F_OnFrame:
	map_script_2 VAR_TEMP_1, 0, SE_EventScript_BurnedTowerBeasts
	.2byte 0
