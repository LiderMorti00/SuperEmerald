LavenderTown_House1_Frlg_MapScripts::
	.byte 0

LavenderTown_House1_EventScript_CooltrainerF::
	lock
	faceplayer
	goto_if_ge VAR_SE_SPIRIT_QUEST, 4, LavenderTown_House1_EventScript_CooltrainerFTowerCalm
	goto_if_set FLAG_RESCUED_MR_FUJI, LavenderTown_House1_EventScript_CooltrainerFGhostGone
	msgbox LavenderTown_House1_Text_RocketsKilledCubonesMother
	release
	end

LavenderTown_House1_EventScript_CooltrainerFGhostGone::
	msgbox LavenderTown_House1_Text_GhostOfPokemonTowerIsGone
	release
	end

LavenderTown_House1_EventScript_CooltrainerFTowerCalm::
	msgbox LavenderTown_House1_Text_TowerIsCalmAgain
	release
	end

LavenderTown_House1_EventScript_Cubone::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CUBONE, CRY_MODE_NORMAL
	msgbox LavenderTown_House1_Text_Cubone
	waitmoncry
	release
	end

LavenderTown_House1_Text_Cubone::
	.string "CUBONE: Kyarugoo!$"

LavenderTown_House1_Text_RocketsKilledCubonesMother::
	.string "Those horrible ROCKETS!\n"
	.string "They deserve no mercy!\p"
	.string "That poor CUBONE's mother…\p"
	.string "It was killed trying to escape from\n"
	.string "TEAM ROCKET.$"

LavenderTown_House1_Text_TowerIsCalmAgain::
	.string "POKéMON TOWER feels peaceful again.\p"
	.string "Someone must have soothed the\n"
	.string "restless spirits up there!$"

LavenderTown_House1_Text_GhostOfPokemonTowerIsGone::
	.string "The spirits in POKéMON TOWER still\n"
	.string "can't rest, they say.\p"
	.string "Even the CHANNELERS who went up to\n"
	.string "calm them haven't come back down…$"

