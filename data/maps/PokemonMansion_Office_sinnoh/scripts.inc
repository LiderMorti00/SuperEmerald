PokemonMansion_Office_sinnoh_MapScripts::
	.byte 0


PokemonMansion_Office_Text_SNEnvious::
	.string "Backlot: Er-hem!\p"
	.string "There’s a lot for me to be proud of\n"
	.string "inside, and outside, of this home...\p"
	.string "But what makes me the most proud is my\n"
	.string "trophy garden in the back!\p"
	.string "Why bother traveling afar when\n"
	.string "POKéMON are attracted by my garden?\p"
	.string "They come to me in hopes of seeing the\n"
	.string "garden!\p"
	.string "Well, doesn’t that make you envious?\n"
	.string "You are envious, yes?$"

SE_S_PokemonMansion_Office_PokemonMansion_Office_EventScript_SNBacklot::
	msgbox PokemonMansion_Office_Text_SNEnvious, MSGBOX_NPC
	end

PokemonMansion_Office_EventScript_PtNpc2::
	lock
	faceplayer
	goto_if_set FLAG_DAILY_SN_TROPHY, PokemonMansion_Office_EventScript_SNButlerSaw
	special IsNationalPokedexEnabled
	goto_if_eq VAR_RESULT, TRUE, PokemonMansion_Office_EventScript_SNButlerHow
	goto_if_set FLAG_SYS_GAME_CLEAR, PokemonMansion_Office_EventScript_SNButlerEnjoys
	msgbox PokemonMansion_Office_Text_SNWonderful, MSGBOX_DEFAULT
	release
	end

PokemonMansion_Office_Text_SNWonderful::
	.string "Butler: Master is a truly wonderful and\n"
	.string "generous person!\p"
	.string "It’s on his orders that the garden, his\n"
	.string "pride and joy, is open to all,\p"
	.string "even Trainers.$"

PokemonMansion_Office_EventScript_SNButlerEnjoys::
	msgbox PokemonMansion_Office_Text_SNEnjoys, MSGBOX_DEFAULT
	release
	end

PokemonMansion_Office_Text_SNEnjoys::
	.string "Butler: Master actually quite enjoys\n"
	.string "showing his prized garden to strong\p"
	.string "Trainers.$"

PokemonMansion_Office_EventScript_SNButlerHow::
	msgbox PokemonMansion_Office_Text_SNHowGarden, MSGBOX_DEFAULT
	release
	end

PokemonMansion_Office_Text_SNHowGarden::
	.string "Butler: How do you find it? Master’s\n"
	.string "upgraded trophy garden, I mean.\p"
	.string "You did notice the influx of quite rare\n"
	.string "POKéMON, yes?\p"
	.string "But that’s only to be expected. It’s\n"
	.string "Master’s trophy garden.$"

PokemonMansion_Office_EventScript_SNButlerSaw::
	msgbox PokemonMansion_Office_Text_PtNpc2, MSGBOX_DEFAULT
	release
	end

PokemonMansion_Office_Text_PtNpc2::
	.string "Butler: Did you see them? There were\n"
	.string "some POKéMON, weren’t there?\p"
	.string "But that’s only to be expected. It’s\n"
	.string "Master’s trophy garden.$"

PokemonMansion_Office_EventScript_PtNpc3::
	msgbox PokemonMansion_Office_Text_PtNpc3, MSGBOX_NPC
	end

PokemonMansion_Office_Text_PtNpc3::
	.string "You may look, but please refrain from\n"
	.string "touching this POKéMON statue.$"

PokemonMansion_Office_EventScript_PtSign1::
	msgbox PokemonMansion_Office_Text_PtSign1, MSGBOX_SIGN
	end

PokemonMansion_Office_Text_PtSign1::
	.string "It’s a very expensive-looking POKéMON\n"
	.string "statue...\p"
	.string "...! You got fingerprints on it...$"

PokemonMansion_Office_EventScript_PtSign2::
	msgbox PokemonMansion_Office_Text_PtSign2, MSGBOX_SIGN
	end

PokemonMansion_Office_Text_PtSign2::
	.string "It’s a very expensive-looking book on\n"
	.string "POKéMON.\p"
	.string "Would you like to read it?$"
