PokemonWorldTournament_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SE_Dome_UseHoennRecords
	.byte 0

PokemonWorldTournament_Johto_EventScript_Sign::
	msgbox PokemonWorldTournament_Johto_Text_Sign, MSGBOX_SIGN
	end

PokemonWorldTournament_Johto_Text_Sign:
	.string "POKéMON WORLD TOURNAMENT\n"
	.string "The stars of every region gather here!$"
