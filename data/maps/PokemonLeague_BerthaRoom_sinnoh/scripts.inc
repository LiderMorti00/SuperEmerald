PokemonLeague_BerthaRoom_sinnoh_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SE_SinnohBerthaRoom_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, SE_SinnohLeague_OnWarp
	.byte 0


PokemonLeague_BerthaRoom_EventScript_SNAfterBattle::
	goto PokemonLeague_BerthaRoom_EventScript_Defeated
	end

PokemonLeague_BerthaRoom_EventScript_Phoebe::
	lock
	faceplayer
	goto_if_set FLAG_SN_DEFEATED_ELITE_4_PHOEBE, PokemonLeague_BerthaRoom_EventScript_PostBattleSpeech
	playbgm MUS_ENCOUNTER_ELITE_FOUR, FALSE
	msgbox PokemonLeague_BerthaRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	goto_if_set FLAG_SE_SINNOH_LEAGUE_CLEARED, PokemonLeague_BerthaRoom_EventScript_SNRematchBattle
	trainerbattle_no_intro TRAINER_SE_ELITE_FOUR_BERTHA, PokemonLeague_BerthaRoom_Text_Defeat
	goto PokemonLeague_BerthaRoom_EventScript_SNAfterBattle

PokemonLeague_BerthaRoom_Text_Defeat::
	.string "You’re quite something, youngster.\p"
	.string "I like how you and your POKéMON earned\n"
	.string "the win by working as one.\p"
	.string "That’s what makes you so strong.\p"
	.string "Ahahaha! I think that you can go as\n"
	.string "far as you want.$"

PokemonLeague_BerthaRoom_EventScript_SNRematchBattle::
	trainerbattle_no_intro TRAINER_SE_ELITE_FOUR_BERTHA_REMATCH, PokemonLeague_BerthaRoom_Text_Defeat
	goto PokemonLeague_BerthaRoom_EventScript_SNAfterBattle

PokemonLeague_BerthaRoom_EventScript_Defeated::
	setflag FLAG_SN_DEFEATED_ELITE_4_PHOEBE
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox PokemonLeague_BerthaRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

PokemonLeague_BerthaRoom_Text_PostBattleSpeech::
	.string "The TRAINER in the next room is a much\n"
	.string "more formidable opponent.\p"
	.string "You really must have your wits about\n"
	.string "you.\p"
	.string "However, I think you can go as far as\n"
	.string "you desire. Ahahaha!$"

PokemonLeague_BerthaRoom_Text_IntroSpeech::
	.string "Well, well.\p"
	.string "You’re quite the adorable TRAINER, but\n"
	.string "you’ve also got a spine.\p"
	.string "Ahaha! I’m BERTHA.\p"
	.string "I have a preference for Ground-type\n"
	.string "POKéMON.\p"
	.string "Well, would you show this old lady how\n"
	.string "much you’ve learned?$"

PokemonLeague_BerthaRoom_EventScript_PostBattleSpeech::
	msgbox PokemonLeague_BerthaRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end
