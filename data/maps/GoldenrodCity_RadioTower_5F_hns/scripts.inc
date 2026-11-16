GoldenrodCity_RadioTower_5F_hns_MapScripts::
	.byte 0


GoldenrodCity_RadioTower_5F_Text_FakeDirector1::
	.string "Y-you! You came to rescue me?$"

SE_J_GoldenrodCity_RadioTower_5F_hns_GoldenrodCity_RadioTower_5F_EventScript_Petrel::
	msgbox GoldenrodCity_RadioTower_5F_Text_FakeDirector1, MSGBOX_NPC
	end

GoldenrodCity_RadioTower_5F_Text_RocketBossSeen::
	.string "Oh? You managed to get this far?\p"
	.string "You must be quite the trainer.\p"
	.string "We intend to take over this RADIO\n"
	.string "STATION and announce our comeback.\p"
	.string "That should bring our boss GIOVANNI\n"
	.string "back from his solitary training.\p"
	.string "We are going to regain our former\n"
	.string "glory...\p"
	.string "I won't allow you to interfere with\n"
	.string "our meticulous plans!$"

SE_J_GoldenrodCity_RadioTower_5F_hns_GoldenrodCity_RadioTower_5F_EventScript_Archer::
	msgbox GoldenrodCity_RadioTower_5F_Text_RocketBossSeen, MSGBOX_NPC
	end

GoldenrodRaidoTower4_EventScript_ARIANA::
	trainerbattle_single TRAINER_ARIANA_2_HNS GoldenrodCity_RadioTower_5F_Text_ExecutiveF1Seen, GoldenrodCity_RadioTower_5F_Text_ExecutiveF1Beaten
	msgbox GoldenrodCity_RadioTower_5F_Text_ExecutiveF1After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_RadioTower_5F_Text_ExecutiveF1After::
	.string "{PLAYER}, isn't it?\p"
	.string "A brat like you won't appreciate\n"
	.string "the magnificence of TEAM ROCKET.\p"
	.string "That's too bad. I really admire\n"
	.string "your power.$"

GoldenrodCity_RadioTower_5F_Text_ExecutiveF1Beaten::
	.string "This can't be happening!\p"
	.string "I fought hard, but I still lost…\p"
	.string "I'm so sorry GIOVANNI…$"

GoldenrodCity_RadioTower_5F_Text_ExecutiveF1Seen::
	.string "Remember me from the HIDEOUT in\n"
	.string "MAHOGANY TOWN?\p"
	.string "My boss scolded me but I'm stronger.\p"
	.string "I lost then, but I won't this time.$"

GoldenrodCity_RadioTower_5F_EventScript_Petrel2::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_5F_Text_FakeDirectorAfter2, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_5F_Text_FakeDirectorAfter2::
	.string "The boss stashed the DIRECTOR in\n"
	.string "the UNDERGROUND WAREHOUSE.\p"
	.string "It's at the far end of the UNDER-\n"
	.string "GROUND.\p"
	.string "You can use the BASEMENT KEY to\n"
	.string "get to the UNDERGROUND WAREHOUSE.\p"
	.string "But I doubt you'll get that far.$"

@=======[STUDIO]==============================================================================================================================

GoldenrodCity_RadioTower_5F_EventScript_Ben::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_5F_Text_Ben, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_5F_Text_Ben::
	.string "BEN: Do you listen to our music?$"
