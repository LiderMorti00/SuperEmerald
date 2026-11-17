PokemonLeague_LucianRoom_sinnoh_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SE_SinnohLucianRoom_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, SE_SinnohLeague_OnWarp
	.byte 0


PokemonLeague_LucianRoom_EventScript_SNAfterBattle::
	goto PokemonLeague_LucianRoom_EventScript_Defeated
	end

PokemonLeague_LucianRoom_EventScript_Drake::
	lock
	faceplayer
	goto_if_set FLAG_SN_DEFEATED_ELITE_4_DRAKE, PokemonLeague_LucianRoom_EventScript_PostBattleSpeech
	playbgm MUS_ENCOUNTER_ELITE_FOUR, FALSE
	msgbox PokemonLeague_LucianRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	goto_if_set FLAG_SE_SINNOH_LEAGUE_CLEARED, PokemonLeague_LucianRoom_EventScript_SNRematchBattle
	trainerbattle_no_intro TRAINER_SE_ELITE_FOUR_LUCIAN, PokemonLeague_LucianRoom_Text_Defeat
	goto PokemonLeague_LucianRoom_EventScript_SNAfterBattle

PokemonLeague_LucianRoom_Text_Defeat::
	.string "Congratulations. You’ve now beaten\n"
	.string "the ELITE FOUR.\p"
	.string "However, that doesn’t mean you’re done\n"
	.string "with the POKéMON LEAGUE.\p"
	.string "There remains the CHAMPION.\p"
	.string "I should warn you--the CHAMPION is far\n"
	.string "stronger than the ELITE FOUR.\p"
	.string "Now, go on. Step through the doorway\n"
	.string "to your final battle.$"

PokemonLeague_LucianRoom_EventScript_SNRematchBattle::
	trainerbattle_no_intro TRAINER_SE_ELITE_FOUR_LUCIAN_REMATCH, PokemonLeague_LucianRoom_Text_Defeat
	goto PokemonLeague_LucianRoom_EventScript_SNAfterBattle

PokemonLeague_LucianRoom_EventScript_Defeated::
	setvar VAR_0x8004, FANCOUNTER_DEFEATED_DRAKE
	special Script_TryGainNewFanFromCounter
	setflag FLAG_SN_DEFEATED_ELITE_4_DRAKE
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox PokemonLeague_LucianRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

PokemonLeague_LucianRoom_Text_PostBattleSpeech::
	.string "I’ll be reading books until the next\n"
	.string "challenger arrives.\p"
	.string "That will calm my nerves, so that I may\n"
	.string "deal with all situations without\p"
	.string "panicking.$"

PokemonLeague_LucianRoom_Text_IntroSpeech::
	.string "Ah, you timed your arrival well.\p"
	.string "I’ve just finished reading a book, you\n"
	.string "see.\p"
	.string "Allow me to introduce myself.\p"
	.string "I am LUCIAN. I am a user of the Psychic\n"
	.string "type.\p"
	.string "I must say, you’ve already proven\n"
	.string "yourself to be outstanding by coming\p"
	.string "this far.\p"
	.string "They say I am the toughest of the\n"
	.string "ELITE FOUR.\p"
	.string "I’m afraid I will have to go all out\n"
	.string "against you to live up to that\p"
	.string "reputation.$"

PokemonLeague_LucianRoom_EventScript_PostBattleSpeech::
	msgbox PokemonLeague_LucianRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end
