PokemonLeague_FlintRoom_sinnoh_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SE_SinnohFlintRoom_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, SE_SinnohLeague_OnWarp
	.byte 0


PokemonLeague_FlintRoom_EventScript_SNAfterBattle::
	goto PokemonLeague_FlintRoom_EventScript_Defeated
	end

PokemonLeague_FlintRoom_EventScript_Glacia::
	lock
	faceplayer
	goto_if_set FLAG_SN_DEFEATED_ELITE_4_GLACIA, PokemonLeague_FlintRoom_EventScript_PostBattleSpeech
	playbgm MUS_ENCOUNTER_ELITE_FOUR, FALSE
	msgbox PokemonLeague_FlintRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	goto_if_set FLAG_SE_SINNOH_LEAGUE_CLEARED, PokemonLeague_FlintRoom_EventScript_SNRematchBattle
	trainerbattle_no_intro TRAINER_SE_ELITE_FOUR_FLINT, PokemonLeague_FlintRoom_Text_Defeat
	goto PokemonLeague_FlintRoom_EventScript_SNAfterBattle

PokemonLeague_FlintRoom_Text_Defeat::
	.string "… …\p"
	.string "… …\p"
	.string "… …\p"
	.string "…Whew… …Burnt right down to\n"
	.string "cinders…$"

PokemonLeague_FlintRoom_EventScript_SNRematchBattle::
	trainerbattle_no_intro TRAINER_SE_ELITE_FOUR_FLINT_REMATCH, PokemonLeague_FlintRoom_Text_Defeat
	goto PokemonLeague_FlintRoom_EventScript_SNAfterBattle

PokemonLeague_FlintRoom_EventScript_Defeated::
	setflag FLAG_SN_DEFEATED_ELITE_4_GLACIA
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox PokemonLeague_FlintRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

PokemonLeague_FlintRoom_Text_PostBattleSpeech::
	.string "… …\p"
	.string "… …\p"
	.string "… …\p"
	.string "…Keep going…$"

PokemonLeague_FlintRoom_Text_IntroSpeech::
	.string "…$"

PokemonLeague_FlintRoom_EventScript_PostBattleSpeech::
	msgbox PokemonLeague_FlintRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end
