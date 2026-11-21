RocketHideout_B1F_hns_MapScripts::
	.byte 0


RocketHideout_B1F_EventScript_TrainerJed::
	trainerbattle_single TRAINER_JED_HNS, RocketHideout_B1F_Text_ScientistJedSeen, RocketHideout_B1F_Text_ScientistJedBeaten
	msgbox RocketHideout_B1F_Text_ScientistJedAfter, MSGBOX_AUTOCLOSE
	end

RocketHideout_B1F_Text_ScientistJedAfter::
    .string "All right. I'll divulge a secret\n"
    .string "about our hideout.\p"
    .string "That thing on the floor up ahead\n"
    .string "is a warp panel.\p"
    .string "If you step on it, you'll be\n"
    .string "warped back to the entrance.$"

RocketHideout_B1F_Text_ScientistJedBeaten::
    .string "I get it…$"

RocketHideout_B1F_Text_ScientistJedSeen::
    .string "This was once a ninja hideout.\p"
    .string "There are traps to confound\n"
    .string "intruders like you.$"

RocketHideout_B1F_EventScript_Item_HyperPotion::
	finditem ITEM_HYPER_POTION
	end

RocketHideout_B1F_EventScript_Item_Revive::
	finditem ITEM_REVIVE
	end

RocketHideout_B1F_EventScript_Item_BigNugget::
	finditem ITEM_BIG_NUGGET
	end

RocketHideout_B1F_EventScript_Rocket16::
	trainerbattle_single TRAINER_GRUNT_13_HNS, RocketHideout_B1F_Text_GruntM16Seen, RocketHideout_B1F_Text_GruntM16Beaten
	msgbox RocketHideout_B1F_Text_GruntM16After, MSGBOX_AUTOCLOSE
	end

RocketHideout_B1F_Text_GruntM16After::
    .string "I don't even know where the traps\n"
    .string "are planted.\p"
    .string "You'll just have to collect your\n"
    .string "courage and walk.$"

RocketHideout_B1F_Text_GruntM16Beaten::
    .string "Kaboom!$"

RocketHideout_B1F_Text_GruntM16Seen::
    .string "Heheh. Feeling lucky, punk?$"

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
