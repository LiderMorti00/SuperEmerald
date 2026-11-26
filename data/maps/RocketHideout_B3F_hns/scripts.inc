RocketHideout_B3F_hns_MapScripts::
	.byte 0

RocketHideout_B3F_EventScript_Item_Protein::
	finditem ITEM_PROTEIN
	end

RocketHideout_B3F_EventScript_Item_IceHeal::
	finditem ITEM_ICE_HEAL
	end

RocketHideout_B3F_EventScript_Item_HyperPotion::
	finditem ITEM_HYPER_POTION
	end

RocketHideout_B3F_EventScript_Item_GuardSpec::
	finditem ITEM_GUARD_SPEC
	end

RocketHideout_B3F_EventScript_Item_FullHeal::
	finditem ITEM_FULL_HEAL
	end

RocketHideout_B3F_Text_B3FLockedDoorNeedsPassword::
    .string "The door's closed…\p"
    .string "It needs two passwords to open.$"

SE_J_RocketHideout_B3F_hns_RocketHideout_B3F_EventScript_Door::
	msgbox RocketHideout_B3F_Text_B3FLockedDoorNeedsPassword, MSGBOX_SIGN
	end
