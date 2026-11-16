Route30_MrPokemonsHouse_hns_MapScripts::
	.byte 0


MrPokemonHouse_Text_AlwaysNewDiscoveries::
	.string "Life is delightful!\n"
	.string "Always, new discoveries to be made.$"

SE_J_Route30_MrPokemonsHouse_hns_MrPokemonHouse_EventScript_MrPokemon::
	msgbox MrPokemonHouse_Text_AlwaysNewDiscoveries, MSGBOX_NPC
	end

MrPokemonHouse_EventScript_Coins::
	lock
	msgbox MrPokemonHouse_Text_StrangeCoins, MSGBOX_SIGN
	release
	end

MrPokemonHouse_Text_StrangeCoins::
	.string "A whole pile of strange coins!\p"
	.string "Maybe they're from another\n"
	.string "country…$"

MrPokemonHouse_EventScript_Magazine::
	lock
	msgbox MrPokemonHouse_Text_ForeignMagazines, MSGBOX_SIGN
	release
	end

MrPokemonHouse_Text_ForeignMagazines::
	.string "It's packed with foreign\n"
	.string "magazines.\p"
	.string "Can't even read their titles…$"
