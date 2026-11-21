FightArea_House2_sinnoh_MapScripts::
	.byte 0


FightArea_House2_EventScript_PtNpc1::
	lock
	faceplayer
	msgbox FightArea_House2_Text_PtNpc1_0, MSGBOX_DEFAULT
	release
	end

FightArea_House2_Text_PtNpc1_0::
	.string "The BATTLE ZONE used to attract only\n"
	.string "the hardiest of the TRAINERS.\p"
	.string "They were considered eccentric for\n"
	.string "gathering at a place like this.\p"
	.string "It's hard to believe how much it's\n"
	.string "changed since then.\p"
	.string "Places like the FIGHT AREA and the\n"
	.string "SURVIVAL AREA just seemed to spring\p"
	.string "up overnight.$"

FightArea_House2_EventScript_PtNpc2::
	lock
	faceplayer
	playmoncry SPECIES_TORCHIC, CRY_MODE_NORMAL
	msgbox FightArea_House2_Text_PtNpc2_0, MSGBOX_DEFAULT
	release
	end

FightArea_House2_Text_PtNpc2_0::
	.string "TORCHIC: Chiic chic!$"

FightArea_House2_EventScript_PtNpc3::
	lock
	faceplayer
	msgbox FightArea_House2_Text_PtNpc3_0, MSGBOX_DEFAULT
	release
	end

FightArea_House2_Text_PtNpc3_0::
	.string "He was one of those early eccentrics\n"
	.string "who were around during the early days\p"
	.string "of the BATTLE ZONE. Well, I was too.$"

FightArea_House2_EventScript_PtNpc4::
	msgbox FightArea_House2_Text_PtNpc4, MSGBOX_NPC
	end

FightArea_House2_Text_PtNpc4::
	.string "I am the Item Expert! I have mastery in\n"
	.string "the way of items!\p"
	.string "Your POKéMON… Do they hold items?\p"
	.string "The better the item they hold, the\n"
	.string "stronger they become.\p"
	.string "There are items that are worthy of my\n"
	.string "recommendation. Care to know?$"
