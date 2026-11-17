SandgemTown_RivalHouse_F1_sinnoh_MapScripts::
	.byte 0


SandgemTown_RivalHouse_F1_EventScript_PtNpc1::
	lock
	faceplayer
	goto_if_set FLAG_SYS_NATIONAL_DEX, SandgemTown_RivalHouse_F1_EventScript_SNNational
	msgbox SandgemTown_RivalHouse_F1_Text_PtNpc1, MSGBOX_DEFAULT
	release
	end

SandgemTown_RivalHouse_F1_Text_PtNpc1::
	.string "Ah, so that ROWAN fellow is back? He's\n"
	.string "quite the remarkable man.\p"
	.string "He's been studying POKéMON since way,\n"
	.string "way back.\p"
	.string "My son and grandchild help ROWAN with\n"
	.string "his studies now.$"

SandgemTown_RivalHouse_F1_EventScript_SNNational::
	msgbox SandgemTown_RivalHouse_F1_Text_SNNational, MSGBOX_DEFAULT
	release
	end

SandgemTown_RivalHouse_F1_Text_SNNational::
	.string "Oh, my! You’ve got a National POKéDEX?\p"
	.string "How fantastic is that?!\p"
	.string "ROWAN should be delighted. It will\n"
	.string "greatly help his research.\p"
	.string "But, young TRAINER... You should know\n"
	.string "this.\p"
	.string "In this world, there are 300... No, 400...\p"
	.string "No, no, no! There’re a lot more kinds of\n"
	.string "POKéMON than that!$"

SandgemTown_RivalHouse_F1_Text_SNSwarm1::
	.string "Oh, hi, {PLAYER}!\p"
	.string "There was news on TV saying there is a\n"
	.string "massive outbreak of POKéMON!\p"
	.string "That’d be great for filling up your\n"
	.string "POKéDEX!$"

SE_S_SandgemTown_RivalHouse_F1_SandgemTown_RivalHouse_F1_EventScript_PtNpc2::
	msgbox SandgemTown_RivalHouse_F1_Text_SNSwarm1, MSGBOX_NPC
	end
