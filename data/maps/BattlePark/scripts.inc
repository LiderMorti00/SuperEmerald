@ Super Emerald: Battle Park (outside Sinnoh's Battle Tower). NPCs from Pokémon Diamond's
@ Battle Park (pret/pokediamond, zone 309 / message bank 281), adapted to this game.
BattlePark_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SE_BattleTowerSinnoh_OnTransitionOutside
	.byte 0

BattlePark_EventScript_TowerSign::
	msgbox BattlePark_Text_TowerSign, MSGBOX_SIGN
	end

BattlePark_EventScript_AceTrainerM::
	msgbox BattlePark_Text_AceTrainerM, MSGBOX_NPC
	end

BattlePark_EventScript_AceTrainerF::
	msgbox BattlePark_Text_AceTrainerF, MSGBOX_NPC
	end

BattlePark_EventScript_RichBoy::
	msgbox BattlePark_Text_RichBoy, MSGBOX_NPC
	end

BattlePark_EventScript_Babysitter::
	msgbox BattlePark_Text_Babysitter, MSGBOX_NPC
	end

BattlePark_EventScript_Kid::
	msgbox BattlePark_Text_Kid, MSGBOX_NPC
	end

BattlePark_EventScript_BattleGirl::
	msgbox BattlePark_Text_BattleGirl, MSGBOX_NPC
	end

BattlePark_EventScript_Maniac::
	msgbox BattlePark_Text_Maniac, MSGBOX_NPC
	end

BattlePark_EventScript_Gentleman::
	msgbox BattlePark_Text_Gentleman, MSGBOX_NPC
	end

BattlePark_Text_TowerSign:
	.string "BATTLE TOWER\n"
	.string "Gather, All Ye Greatest!$"

BattlePark_Text_AceTrainerM:
	.string "In the BATTLE ROOMS, the seventh\n"
	.string "TRAINER you face is the room's boss.\p"
	.string "You'll need to stay focused if you\n"
	.string "want to win!$"

BattlePark_Text_AceTrainerF:
	.string "If you get a big win streak at the\n"
	.string "BATTLE TOWER, you get to battle\l"
	.string "some real superstars.$"

BattlePark_Text_RichBoy:
	.string "Mwahahaha! We earned a lot of BP\n"
	.string "at the BATTLE TOWER.\p"
	.string "Now I can trade them for loads of\n"
	.string "prizes at HOENN's BATTLE FRONTIER!$"

BattlePark_Text_Kid:
	.string "Aah.$"

BattlePark_Text_Babysitter:
	.string "I'm a babysitting TRAINER!\p"
	.string "I'm off to the BATTLE TOWER\n"
	.string "with my beloved son!$"

BattlePark_Text_BattleGirl:
	.string "I heard that the world's best\n"
	.string "gather here for battles.\p"
	.string "This is my chance to get global\n"
	.string "fame and recognition!$"

BattlePark_Text_Maniac:
	.string "The types of POKéMON!\p"
	.string "The moves to be taught and used!\p"
	.string "The items to be held!\p"
	.string "To become number one here, there is\n"
	.string "no detail that can be overlooked!$"

BattlePark_Text_Gentleman:
	.string "I'd love to team up with a BEAUTY\n"
	.string "for a MULTI BATTLE.\p"
	.string "But this TOWER only has SINGLE\n"
	.string "and DOUBLE BATTLES… How sad.$"
