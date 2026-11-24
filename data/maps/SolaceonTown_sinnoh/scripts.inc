SolaceonTown_sinnoh_MapScripts::
	.byte 0

SolaceonTown_EventScript_PtNpc1::
	lock
	faceplayer
	goto_if_set FLAG_SINNOH_BADGE3_GET, SolaceonTown_EventScript_PtNpc1_SNVar0
	msgbox SolaceonTown_Text_PtNpc1, MSGBOX_DEFAULT
	release
	end

SolaceonTown_Text_PtNpc1::
	.string "Howdy, traveling TRAINER. Take it easy,\n"
	.string "slow, and casual.$"

SolaceonTown_EventScript_PtNpc1_SNVar0::
	msgbox SolaceonTown_Text_PtNpc1_SNVar0, MSGBOX_DEFAULT
	release
	end

SolaceonTown_Text_PtNpc1_SNVar0::
	.string "Howdy, traveling TRAINER. There's\n"
	.string "nothing here.\p"
	.string "Well, nothing but plenty of time to\n"
	.string "think, anyway.\p"
	.string "Oh, right. We have the ruins here. Why\n"
	.string "not take a tour through that?$"

SolaceonTown_EventScript_PtNpc2::
	msgbox SolaceonTown_Text_PtNpc2, MSGBOX_NPC
	end

SolaceonTown_Text_PtNpc2::
	.string "I'm too little, so I don't know how to\n"
	.string "battle very good.\p"
	.string "The nice Day-Care Lady is raising my\n"
	.string "POKéMON for me.$"

SolaceonTown_EventScript_PtNpc3::
	msgbox SolaceonTown_Text_PtNpc3, MSGBOX_NPC
	end

SolaceonTown_Text_PtNpc3::
	.string "Breathing in this refreshing air… It\n"
	.string "perks up POKéMON, don't you think?$"

SolaceonTown_EventScript_PtNpc4::
	msgbox SolaceonTown_Text_PtNpc4, MSGBOX_NPC
	end

SolaceonTown_Text_PtNpc4::
	.string "Every Sunday, I visit the LOST TOWER…$"

SolaceonTown_EventScript_PtNpc5::
	msgbox SolaceonTown_Text_PtNpc5, MSGBOX_NPC
	end

SolaceonTown_Text_PtNpc5::
	.string "Your encounters with POKéMON can be\n"
	.string "considered your shared history.\p"
	.string "Your POKéDEX records the species\n"
	.string "you've caught.\p"
	.string "I like to keep a journal of where\n"
	.string "I met each of my partners, too.$"

SolaceonTown_EventScript_PtNpc6::
	msgbox SolaceonTown_Text_PtNpc6, MSGBOX_NPC
	end

SolaceonTown_Text_PtNpc6::
	.string "There used to be nothing here but a\n"
	.string "road that went straight through.\p"
	.string "Over time, POKéMON and people just\n"
	.string "gathered, and the town came to be.$"

SolaceonTown_EventScript_SNMon1Buneary::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_BUNEARY, CRY_MODE_NORMAL
	msgbox SolaceonTown_EventScript_SNMon1Buneary_Text, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SolaceonTown_EventScript_SNMon1Buneary_Text::
	.string "BUNEARY: Bun! BUNEARY!$"

SolaceonTown_EventScript_SNMon2Buneary::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_BUNEARY, CRY_MODE_NORMAL
	msgbox SolaceonTown_EventScript_SNMon2Buneary_Text, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SolaceonTown_EventScript_SNMon2Buneary_Text::
	.string "BUNEARY: Bun! BUNEARY!$"

SolaceonTown_EventScript_SNMonPachirisu::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PACHIRISU, CRY_MODE_NORMAL
	msgbox SolaceonTown_EventScript_SNMonPachirisu_Text, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SolaceonTown_EventScript_SNMonPachirisu_Text::
	.string "PACHIRISU: Pachi! Pachiri!$"

SolaceonTown_EventScript_PtSign1::
	msgbox SolaceonTown_Text_PtSign1, MSGBOX_SIGN
	end

SolaceonTown_Text_PtSign1::
	.string "SOLACEON TOWN Free of Worry!$"

SolaceonTown_EventScript_PtSign2::
	msgbox SolaceonTown_Text_PtSign2, MSGBOX_SIGN
	end

SolaceonTown_Text_PtSign2::
	.string "POKéMON Day Care Let Us Raise Your\n"
	.string "POKéMON$"

SolaceonTown_EventScript_PtSign3::
	msgbox SolaceonTown_Text_PtSign3, MSGBOX_SIGN
	end

SolaceonTown_Text_PtSign3::
	.string "POKéMON News Press Wanted: Pro\n"
	.string "POKéMON Catcher!$"
