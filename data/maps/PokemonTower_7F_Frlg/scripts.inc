PokemonTower_7F_Frlg_MapScripts::
	.byte 0

PokemonTower_7F_EventScript_MrFuji::
	lock
	faceplayer
	famechecker FAMECHECKER_MRFUJI, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	setflag FLAG_HIDE_TOWER_FUJI
	clearflag FLAG_HIDE_POKEHOUSE_FUJI
	setflag FLAG_RESCUED_MR_FUJI
	msgbox PokemonTower_7F_Text_MrFujiThankYouFollowMe
	closemessage
	warp MAP_LAVENDER_TOWN_VOLUNTEER_POKEMON_HOUSE, 4, 7
	waitstate
	release
	end

PokemonTower_7F_EventScript_Unused::
	release
	end

PokemonTower_7F_Text_MrFujiThankYouFollowMe::
	.string "MR. FUJI: Heh?\n"
	.string "You came to save me?\p"
	.string "Thank you. But, I came here of my\n"
	.string "own free will.\p"
	.string "I came to calm the spirit of\n"
	.string "CUBONE's mother.\p"
	.string "I think MAROWAK's spirit has\n"
	.string "finally left us.\p"
	.string "I must thank you for your kind\n"
	.string "concern.\p"
	.string "Follow me to my home, POKéMON\n"
	.string "HOUSE, at the foot of this tower.$"

