PokemonLeague_AaronRoom_sinnoh_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SE_SinnohAaronRoom_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, SE_SinnohLeague_OnWarp
	.byte 0


PokemonLeague_AaronRoom_EventScript_SNAfterBattle::
	goto PokemonLeague_AaronRoom_EventScript_Defeated
	end

PokemonLeague_AaronRoom_EventScript_Sidney::
	lock
	faceplayer
	goto_if_set FLAG_SN_DEFEATED_ELITE_4_SIDNEY, PokemonLeague_AaronRoom_EventScript_PostBattleSpeech
	playbgm MUS_ENCOUNTER_ELITE_FOUR, FALSE
	msgbox PokemonLeague_AaronRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	goto_if_set FLAG_SE_SINNOH_LEAGUE_CLEARED, PokemonLeague_AaronRoom_EventScript_SNRematchBattle
	trainerbattle_no_intro TRAINER_SE_ELITE_FOUR_AARON, PokemonLeague_AaronRoom_Text_Defeat
	goto PokemonLeague_AaronRoom_EventScript_SNAfterBattle

PokemonLeague_AaronRoom_Text_Defeat::
	.string "I lost with the most beautiful and\n"
	.string "toughest of the bug POKéMON...\p"
	.string "We lost because I wasn’t good enough...\p"
	.string "That’s it! Back to training camp! Let’s\n"
	.string "hear it for me!\p"
	.string "No... That was wrong... Anyway... Go on to\n"
	.string "the next room!\p"
	.string "Three Trainers are waiting for you.\n"
	.string "They’re all tougher than me.$"

PokemonLeague_AaronRoom_EventScript_SNRematchBattle::
	trainerbattle_no_intro TRAINER_SE_ELITE_FOUR_AARON_REMATCH, PokemonLeague_AaronRoom_Text_Defeat
	goto PokemonLeague_AaronRoom_EventScript_SNAfterBattle

PokemonLeague_AaronRoom_EventScript_Defeated::
	setflag FLAG_SN_DEFEATED_ELITE_4_SIDNEY
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox PokemonLeague_AaronRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

PokemonLeague_AaronRoom_Text_PostBattleSpeech::
	.string "Go on, go to the next room.\p"
	.string "I’m going to become a top-level Trainer\n"
	.string "who can’t be outclassed with\p"
	.string "my beautiful and tough bug POKéMON!$"

PokemonLeague_AaronRoom_Text_IntroSpeech::
	.string "Hello! Welcome to the POKéMON League!\p"
	.string "I’m Aaron of the Elite Four. It’s good\n"
	.string "to meet you.\p"
	.string "Oh, I should explain, I’m a huge fan of\n"
	.string "bug POKéMON.\p"
	.string "Bug POKéMON are nasty-mean, and yet\n"
	.string "they’re beautiful, too...\p"
	.string "Would you like to know why I take on\n"
	.string "challengers here?\p"
	.string "It’s because I want to become perfect,\n"
	.string "just like my bug POKéMON!\p"
	.string "OK! Let me take you on!$"

PokemonLeague_AaronRoom_EventScript_PostBattleSpeech::
	msgbox PokemonLeague_AaronRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end
