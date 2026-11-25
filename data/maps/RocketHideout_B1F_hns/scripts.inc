RocketHideout_B1F_hns_MapScripts::
	.byte 0

RocketHideout_B1F_EventScript_Item_HyperPotion::
	finditem ITEM_HYPER_POTION
	end

RocketHideout_B1F_EventScript_Item_Revive::
	finditem ITEM_REVIVE
	end

RocketHideout_B1F_EventScript_Item_BigNugget::
	finditem ITEM_BIG_NUGGET
	end

RocketHideout_B1F_EventScript_DummyPanel::
	msgbox RocketHideout_B1F_Text_NothingThere, MSGBOX_SIGN
	end

RocketHideout_B1F_Text_NothingThere::
	.string "A strange panel… Nothing here.$"

RocketHideout_B1F_Text_SecretSwitch::
    .string "A secret switch! Better press it.$"

SE_J_RocketHideout_B1F_hns_RocketHideout_B1F_EventScript_Switch::
	msgbox RocketHideout_B1F_Text_SecretSwitch, MSGBOX_SIGN
	end

RocketHideout_B1F_EventScript_Persian::
	msgbox RocketHideout_B1F_Text_SecurityCameraStatue, MSGBOX_NPC
	end

RocketHideout_B1F_Text_SecurityCameraStatue::
    .string "It's a PERSIAN statue…$"
