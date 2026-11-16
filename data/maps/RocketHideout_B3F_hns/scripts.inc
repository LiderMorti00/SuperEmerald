RocketHideout_B3F_hns_MapScripts::
	.byte 0


RocketHideout_B3F_EventScript_Murkrow::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MURKROW, CRY_MODE_NORMAL
	msgbox RocketHideout_B3F_Text_MurkrowSpeak1, MSGBOX_DEFAULT
	waitmoncry
	release
	end

RocketHideout_B3F_Text_MurkrowSpeak1::
    .string "MURKROW: Hail GIOVANNI.$"

RocketHideout_B3F_Text_GruntF5Seen::
    .string "Do I know the password?\p"
    .string "Maybe.\p"
    .string "But no weakling's going to get\n"
    .string "it!$"

RocketHideout_B3F_Text_GruntF5Beaten::
    .string "All right. Stop. I'll tell you.$"

SE_J_RocketHideout_B3F_hns_RocketHideout_B3F_EventScript_GruntF5::
	trainerbattle_single TRAINER_GRUNT_29_HNS, RocketHideout_B3F_Text_GruntF5Seen, RocketHideout_B3F_Text_GruntF5Beaten
	end

RocketHideout_B3F_EventScript_RocketKO::
	lock
	faceplayer
	msgbox RocketHideout_B3F_Text_B3FRocket, MSGBOX_DEFAULT
	release
	end

RocketHideout_B3F_Text_B3FRocket::
    .string "Urrggh… The guy in the cape is\n"
    .string "incredibly tough…$"

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

RocketHideout_B3F_Text_GruntM28Seen::
    .string "Hyuck-hyuck-hyuck!\p"
    .string "I remember you from the well!\p"
    .string "You're challenging me again?\p"
    .string "Hah! You're nuts, but you have\n"
    .string "guts!\p"
    .string "I'll warn you, I got better!\p"
    .string "If you can beat me, I'll tell\l"
    .string "you a password to the boss'\n"
    .string "room!$"

RocketHideout_B3F_Text_GruntM28Beaten::
    .string "Hyuck-hyuck-hyuck! You're good!$"

SE_J_RocketHideout_B3F_hns_RocketHideout_B3F_EventScript_Eto::
	trainerbattle_single TRAINER_ETO_2_HNS, RocketHideout_B3F_Text_GruntM28Seen, RocketHideout_B3F_Text_GruntM28Beaten
	end

RocketHideout_B3F_EventScript_Mitch::
	trainerbattle_single TRAINER_MITCH_HNS, RocketHideout_B3F_Text_ScientistMitchSeen, RocketHideout_B3F_Text_ScientistMitchBeaten
	msgbox RocketHideout_B3F_Text_ScientistMitchAfter, MSGBOX_AUTOCLOSE
	end

RocketHideout_B3F_Text_ScientistMitchAfter::
    .string "If we turn up the power of our\n"
    .string "radio signal for broadcast\l"
    .string "nationwide…\p"
    .string "The very thought excites me!$"

RocketHideout_B3F_Text_ScientistMitchBeaten::
    .string "Thinking is my strong suit, not\n"
    .string "battling.$"

RocketHideout_B3F_Text_ScientistMitchSeen::
    .string "I don't care that POKéMON are hurt\n"
    .string "by our experiment.$"

RocketHideout_B3F_EventScript_Item_FullHeal::
	finditem ITEM_FULL_HEAL
	end

RocketHideout_B3F_EventScript_Ross::
	trainerbattle_single TRAINER_ROSS_HNS, RocketHideout_B3F_Text_ScientistRossSeen, RocketHideout_B3F_Text_ScientistRossBeaten
	msgbox RocketHideout_B3F_Text_ScientistRossAfter, MSGBOX_AUTOCLOSE
	end

RocketHideout_B3F_Text_ScientistRossAfter::
    .string "A radio signal that drives\n"
    .string "POKéMON mad…\p"
    .string "My experiment is a complete\n"
    .string "success.\p"
    .string "My promotion is assured. This\n"
    .string "loss means absolutely nothing.$"

RocketHideout_B3F_Text_ScientistRossBeaten::
    .string "A mere tactical error cost me…$"

RocketHideout_B3F_Text_ScientistRossSeen::
    .string "I used to work for SILPH, but now\n"
    .string "I run research for TEAM ROCKET.\p"
    .string "A meddlesome child like you needs\n"
    .string "to be punished.$"

RocketHideout_B3F_Text_PetrelIntro::
    .string "Muhahaha, we've been waiting\n"
    .string "for you. So, you are {PLAYER}...\p"
    .string "Me? You don't know who I am?\n"
    .string "It is me, GIOVANNI.\p"
    .string "The majestic GIOVANNI himself!\n"
    .string "Wahahaha!$"

SE_J_RocketHideout_B3F_hns_RocketHideout_B3F_EventScript_Giovanni::
	msgbox RocketHideout_B3F_Text_PetrelIntro, MSGBOX_NPC
	end

RocketHideout_B3F_Text_B3FLockedDoorNeedsPassword::
    .string "The door's closed…\p"
    .string "It needs two passwords to open.$"

SE_J_RocketHideout_B3F_hns_RocketHideout_B3F_EventScript_Door::
	msgbox RocketHideout_B3F_Text_B3FLockedDoorNeedsPassword, MSGBOX_SIGN
	end
