PokemonMansion_sinnoh_MapScripts::
	.byte 0


PokemonMansion_EventScript_PtNpc1::
	msgbox PokemonMansion_Text_PtNpc1, MSGBOX_NPC
	end

PokemonMansion_Text_PtNpc1::
	.string "Mr. Backlot is the master of this\n"
	.string "mansion. This is his office.$"

PokemonMansion_EventScript_PtNpc2::
	msgbox PokemonMansion_Text_PtNpc2, MSGBOX_NPC
	end

PokemonMansion_Text_PtNpc2::
	.string "This is the way out to the trophy\n"
	.string "garden.\p"
	.string "The garden is open for all visitors to\n"
	.string "enjoy.\p"
	.string "However, please beware--wild POKéMON\n"
	.string "may appear in the garden.$"

PokemonMansion_Text_SNMExplain::
	.string "Welcome.\p"
	.string "Here, you may challenge the mansion’s\n"
	.string "pride--the five Trainer maids.\p"
	.string "The challenge is to beat all five of us\n"
	.string "in a row without a break.\p"
	.string "In addition to beating us, if you can\n"
	.string "beat us in a specific number of turns,\p"
	.string "there will be a special gift.\p"
	.string "Incidentally, a turn refers to the time\n"
	.string "it takes for a Trainer and the\l"
	.string "opponent\p"
	.string "to each make an action.\p"
	.string "In this case, action refers to making a\n"
	.string "POKéMON use a move, using an item, or\p"
	.string "switching a POKéMON.\p"
	.string "And now...$"

SE_S_PokemonMansion_PokemonMansion_EventScript_PtNpc3::
	msgbox PokemonMansion_Text_SNMExplain, MSGBOX_NPC
	end

PokemonMansion_EventScript_PtNpc4::
	msgbox PokemonMansion_Text_PtNpc4, MSGBOX_NPC
	end

PokemonMansion_Text_PtNpc4::
	.string "I’m so sorry. Everything beyond this\n"
	.string "point is strictly off-limits.\p"
	.string "Please, you really mustn’t. Mr. Backlot\n"
	.string "will be so cross with me!$"

PokemonMansion_EventScript_PtNpc5::
	lock
	faceplayer
	msgbox PokemonMansion_Text_PtNpc5_0, MSGBOX_DEFAULT
	release
	end

PokemonMansion_Text_PtNpc5_0::
	.string "The expensive-looking book Mr. Backlot\n"
	.string "has... It tugs at my attention.$"
