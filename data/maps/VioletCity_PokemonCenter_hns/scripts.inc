VioletCity_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VioletCity_PokemonCenter_hns_OnTransition
	.byte 0

VioletCity_PokemonCenter_hns_OnTransition:
	setrespawn HEAL_LOCATION_VIOLET_CITY_HNS
	end


VioletCity_PokemonCenter_EventScript_Gentleman::
	lock
	faceplayer
	msgbox VioletCity_PokeCenter_Text_Gentleman, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_PokeCenter_Text_Gentleman::
	.string "It was around three years ago.\p"
	.string "TEAM ROCKET was up to no good\n"
	.string "with POKéMON.\p"
	.string "But justice prevailed--a young\n"
	.string "kid broke 'em up.$"

VioletCity_PokemonCenter_EventScript_Man::
	lock
	faceplayer
	msgbox VioletCity_PokeCenter_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_PokeCenter_Text_Youngster::
	.string "POKéMON are smart. They won't\n"
	.string "obey a TRAINER they don't respect.\p"
	.string "Without the right GYM BADGES,\n"
	.string "they will just do as they please.$"

VioletCity_PokemonCenter_EVentScript_Kid::
	lock
	faceplayer
	msgbox VioletCity_PokeCenter_Text_GameboyKid, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_PokeCenter_Text_GameboyKid::
	.string "A guy named BILL made the\n"
	.string "POKéMON PC storage system.$"

VioletCity_PokeCenter_Text_ElmsAideNoRoom::
	.string "{PLAYER}, long time, no see.\p"
	.string "PROF.ELM asked me to find you.\p"
	.string "He has another favor to ask.\p"
	.string "Would you take the POKéMON EGG?\p"
	.string "Oh, wait… You need to make room\n"
	.string "in your party first.$"

SE_J_VioletCity_PokemonCenter_hns_VioletCity_PokemonCenter_EventScript_Aide::
	msgbox VioletCity_PokeCenter_Text_ElmsAideNoRoom, MSGBOX_NPC
	end

VioletCity_PokemonCenter_Text_BookshelfWoman::
	lock
	faceplayer
	msgbox VioletCity_PokeCenter_Text_BooksAreGreat, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_PokeCenter_Text_BooksAreGreat::
	.string "While my POKéMON are recovering\n"
	.string "I love to read a good book.$"
