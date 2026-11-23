OreburghGate_1F_sinnoh_MapScripts::
	.byte 0


OreburghGate_1F_EventScript_Diana::
	trainerbattle_single TRAINER_AUTUMN_SINNOH, OreburghGate_1F_Text_DianaIntro, OreburghGate_1F_Text_DianaDefeat
	msgbox OreburghGate_1F_Text_DianaPost, MSGBOX_AUTOCLOSE
	end

OreburghGate_1F_Text_DianaPost::
	.string "Getting through that cave feels like\n"
	.string "an adventure.$"

OreburghGate_1F_Text_DianaDefeat::
	.string "Well, I guess losing is something to\n"
	.string "commemorate, too…$"

OreburghGate_1F_Text_DianaIntro::
	.string "To celebrate my getting through this\n"
	.string "cave, I'm going to battle you!$"

OreburghGate_1F_EventScript_Curtis::
	trainerbattle_single TRAINER_TED_SINNOH, OreburghGate_1F_Text_CurtisIntro, OreburghGate_1F_Text_CurtisDefeat
	msgbox OreburghGate_1F_Text_CurtisPost, MSGBOX_AUTOCLOSE
	end

OreburghGate_1F_Text_CurtisPost::
	.string "POKéMON can appear anywhere in a\n"
	.string "cave. It's not like the tall grass by\l"
	.string "roads.$"

OreburghGate_1F_Text_CurtisDefeat::
	.string "Hmm… Insufficiently raised?$"

OreburghGate_1F_Text_CurtisIntro::
	.string "We TRAINERS will accept challenges\n"
	.string "anywhere! It's what we do.$"

OreburghGate_1F_EventScript_PtNpc1::
	goto_if_unset FLAG_SINNOH_BADGE1_GET, SE_OreburghGateHiker_NoBadge_Script
	msgbox OreburghGate_1F_Text_PtNpc1, MSGBOX_NPC
	end

OreburghGate_1F_Text_PtNpc1::
	.string "Oh! Good golly! That's OREBURGH CITY's\n"
	.string "GYM BADGE!\p"
	.string "All right! Now you can use the hidden\n"
	.string "move ROCK SMASH on small boulders!$"

OreburghGate_1F_EventScript_HikerHM::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_OREBURGH_GATE_HM, OreburghGate_1F_EventScript_HikerAfter
	msgbox OreburghGate_1F_Text_Hiker, MSGBOX_DEFAULT
	giveitem ITEM_HM_ROCK_SMASH
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_OREBURGH_GATE_HM
	msgbox OreburghGate_1F_Text_HikerAfter, MSGBOX_DEFAULT
	release
	end

OreburghGate_1F_Text_HikerAfter::
	.string "That Hidden Machine, or HM for short,\n"
	.string "contains the hidden move ROCK SMASH.\p"
	.string "A POKéMON learning ROCK SMASH can\n"
	.string "smash small boulders in the field.\p"
	.string "But the TRAINER has to have the GYM\n"
	.string "BADGE from OREBURGH CITY.\p"
	.string "If you don't have that BADGE, you can't\n"
	.string "make a POKéMON use the hidden\p"
	.string "move ROCK SMASH outside of battle.$"

OreburghGate_1F_Text_Hiker::
	.string "That POKéNAV! That look on your face!\n"
	.string "You're new around here, aren't you?\p"
	.string "Hmm… You're still pretty new to\n"
	.string "SINNOH, aren't you?\p"
	.string "But it's all good! You're a new fellow\n"
	.string "friend of POKéMON!\p"
	.string "So, let me make a gift of this Hidden\n"
	.string "Machine to you!$"

OreburghGate_1F_EventScript_HikerAfter::
	msgbox OreburghGate_1F_Text_HikerAfter, MSGBOX_DEFAULT
	release
	end

SE_OreburghGateHiker_NoBadge_Script::
	msgbox SE_OreburghGateHiker_NoBadge_Text, MSGBOX_NPC
	end

SE_OreburghGateHiker_NoBadge_Text::
	.string "Have you been to OREBURGH CITY's GYM?\p"
	.string "With its GYM BADGE, you can use the\n"
	.string "hidden move ROCK SMASH on small\l"
	.string "boulders!$"
