SnowpointCity_PokemonCenter_1F_sinnoh_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SE_SnowpointCity_PC_OnTransition
	.byte 0


SnowpointCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_SNOWPOINT_CITY_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

SnowpointCity_PokemonCenter_1F_EventScript_PtNpc1::
	lock
	faceplayer
	msgbox SnowpointCity_PokemonCenter_1F_Text_PtNpc1_0, MSGBOX_DEFAULT
	release
	end

SnowpointCity_PokemonCenter_1F_Text_PtNpc1_0::
	.string "You know how there are many Ice-type\n"
	.string "POKéMON around SNOWPOINT CITY?\p"
	.string "I wonder if they also live in the\n"
	.string "temple?$"

SnowpointCity_PokemonCenter_1F_EventScript_PtNpc2::
	lock
	faceplayer
	msgbox SnowpointCity_PokemonCenter_1F_Text_PtNpc2_0, MSGBOX_DEFAULT
	release
	end

SnowpointCity_PokemonCenter_1F_Text_PtNpc2_0::
	.string "Sound gets swallowed up by the snow.\n"
	.string "That’s why it’s very quiet here.$"

SnowpointCity_PokemonCenter_1F_EventScript_PtNpc3::
	lock
	faceplayer
	playmoncry SPECIES_PSYDUCK, CRY_MODE_NORMAL
	msgbox SnowpointCity_PokemonCenter_1F_Text_PtNpc3_0, MSGBOX_DEFAULT
	release
	end

SnowpointCity_PokemonCenter_1F_Text_PtNpc3_0::
	.string "PSYDUCK: Gaga guwawa!$"

SnowpointCity_PokemonCenter_1F_EventScript_PtNpc4::
	goto_if_set FLAG_SINNOH_BADGE7_GET, SnowpointCity_PokemonCenter_1F_EventScript_SNMayleneAfter
	msgbox SnowpointCity_PokemonCenter_1F_Text_SNMayleneBefore, MSGBOX_NPC
	end

SnowpointCity_PokemonCenter_1F_Text_SNMayleneBefore::
	.string "MAYLENE: Brrr...\p"
	.string "Oh, hi, {PLAYER}! Are you taking the GYM\n"
	.string "challenge now?\p"
	.string "I’m hoping to see CANDICE soon, but I’m\n"
	.string "staying put until I warm up again first.\p"
	.string "Oh, you should know that CANDICE is a\n"
	.string "user of Ice-type POKéMON.\p"
	.string "I really admire CANDICE. She’s so\n"
	.string "studious.\p"
	.string "She wanted to practice against me to\n"
	.string "learn about the Fighting type.\p"
	.string "It’s because the Ice type matches up\n"
	.string "badly against the Fighting type.$"

SnowpointCity_PokemonCenter_1F_EventScript_SNMayleneAfter::
	msgbox SnowpointCity_PokemonCenter_1F_Text_PtNpc4, MSGBOX_NPC
	end

SnowpointCity_PokemonCenter_1F_Text_PtNpc4::
	.string "MAYLENE: Oh! That’s the Icicle BADGE!\n"
	.string "You must have beaten CANDICE.\p"
	.string "With that BADGE, aren’t you allowed to\n"
	.string "use the hidden move Rock Climb?\p"
	.string "Rock Climb can be learned by Rock-type\n"
	.string "or Fighting-type POKéMON, I think.$"

SE_SnowpointCity_PC_OnTransition::
	setrespawn HEAL_LOCATION_SNOWPOINT_CITY_SINNOH
	end
