OreburghMine_B2F_sinnoh_MapScripts::
	.byte 0

OreburghMine_B2F_EventScript_Mason::
	trainerbattle_single TRAINER_MARY_SINNOH, OreburghMine_B2F_Text_MasonIntro, OreburghMine_B2F_Text_MasonDefeat
	msgbox OreburghMine_B2F_Text_MasonPost, MSGBOX_AUTOCLOSE
	end

OreburghMine_B2F_Text_MasonPost::
	.string "OK, OK, time for work! I'll work up a\n"
	.string "thirst with my POKéMON!$"

OreburghMine_B2F_Text_MasonDefeat::
	.string "Well, now aren't you something!$"

OreburghMine_B2F_Text_MasonIntro::
	.string "I'm gonna let you in on a secret… I\n"
	.string "snuck my POKéMON to work!$"

OreburghMine_B2F_EventScript_Colin::
	trainerbattle_single TRAINER_ALIX_SINNOH, OreburghMine_B2F_Text_ColinIntro, OreburghMine_B2F_Text_ColinDefeat
	msgbox OreburghMine_B2F_Text_ColinPost, MSGBOX_AUTOCLOSE
	end

OreburghMine_B2F_Text_ColinPost::
	.string "I'd better get on back to work…\p"
	.string "You know, I'd rather be traveling\n"
	.string "around with POKéMON the way you do.$"

OreburghMine_B2F_Text_ColinDefeat::
	.string "Wahaha! Mercy, I cry mercy!$"

OreburghMine_B2F_Text_ColinIntro::
	.string "Fine, all righty then. Just a quick\n"
	.string "battle on my break!$"

OreburghMine_B2F_EventScript_Worker::
	msgbox OreburghMine_B2F_Text_Worker, MSGBOX_NPC
	end

OreburghMine_B2F_Text_Worker::
	.string "ROARK is always the first to start\n"
	.string "digging and the last to leave.\l"
	.string "He's a great boss!$"

OreburghMine_B2F_EventScript_Machop1::
	msgbox OreburghMine_B2F_Text_Machop1, MSGBOX_NPC
	end

OreburghMine_B2F_Text_Machop1::
	.string "MACHOP: MACHOP! Machoo!$"

OreburghMine_B2F_EventScript_Machop2::
	msgbox OreburghMine_B2F_Text_Machop2, MSGBOX_NPC
	end

OreburghMine_B2F_Text_Machop2::
	.string "MACHOP: Maaachop!$"

OreburghMine_B2F_EventScript_Machop3::
	msgbox OreburghMine_B2F_Text_Machop3, MSGBOX_NPC
	end

OreburghMine_B2F_Text_Machop3::
	.string "MACHOP: Mach! MACHOP!$"

OreburghMine_B2F_EventScript_PtNpc1::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MACHOP, CRY_MODE_NORMAL
	msgbox OreburghMine_B2F_Text_PtNpc1, MSGBOX_DEFAULT
	waitmoncry
	release
	end

OreburghMine_B2F_Text_PtNpc1::
	.string "MACHOP: Maaacho!$"
