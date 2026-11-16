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
	.string "commemorate, too...$"

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
	.string "Hmm... Insufficiently raised?$"

OreburghGate_1F_Text_CurtisIntro::
	.string "We Trainers will accept challenges\n"
	.string "anywhere! It's what we do.$"

OreburghGate_1F_EventScript_PtNpc1::
	msgbox OreburghGate_1F_Text_PtNpc1, MSGBOX_NPC
	end

OreburghGate_1F_Text_PtNpc1::
	.string "Oh! Good golly! That's OREBURGH CITY's\n"
	.string "Gym Badge!\p"
	.string "All right! Now you can use the hidden\n"
	.string "move Rock Smash on small boulders!$"

OreburghGate_1F_Text_Hiker::
	.string "That sparkling new POKéTCH! Your\n"
	.string "awkwardness as a traveler!\p"
	.string "Hmm... You’re still a pretty new Trainer,\n"
	.string "aren’t you?\p"
	.string "But it’s all good! You’re a new fellow\n"
	.string "friend of POKéMON!\p"
	.string "So, let me make a gift of this Hidden\n"
	.string "Machine to you!$"

SE_S_OreburghGate_1F_OreburghGate_1F_EventScript_HikerHM::
	msgbox OreburghGate_1F_Text_Hiker, MSGBOX_NPC
	end
