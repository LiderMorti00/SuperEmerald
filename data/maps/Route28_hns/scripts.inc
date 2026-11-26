Route28_hns_MapScripts::
	.byte 0

SE_J_Route28_hns_Route28_EventScript_Item_Flamethrower::
	finditem ITEM_TM_FLAMETHROWER
	end

Route28_EventScript_Sign::
	msgbox Route28_Text_Sign, MSGBOX_SIGN
	end

Route28_Text_Sign::
	.string "ROUTE 28$"
