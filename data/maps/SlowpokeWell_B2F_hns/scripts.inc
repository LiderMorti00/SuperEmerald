SlowpokeWell_B2F_hns_MapScripts::
	.byte 0


SlowpokeWell_Text_Slowking::
	.string "SLOWKING: ........................$"

SE_J_SlowpokeWell_B2F_hns_SlowpokeWell_EventScript_Slowking::
	msgbox SlowpokeWell_Text_Slowking, MSGBOX_NPC
	end

SlowpokeWell_EventScript_Item_Kings_Rock::
	finditem ITEM_KINGS_ROCK
	end
