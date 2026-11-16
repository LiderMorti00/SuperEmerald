CanalaveCity_House3_sinnoh_MapScripts::
	.byte 0


CanalaveCity_House3_Text_SNWingGlows::
	.string "The little boy is thrashing about in his\n"
	.string "sleep.\p"
	.string "{PLAYER}’s Lunar Wing began to glow...\p"
	.string "The boy’s sleeping face became\n"
	.string "untroubled and serene!$"

SE_S_CanalaveCity_House3_CanalaveCity_House3_EventScript_PtNpc1::
	msgbox CanalaveCity_House3_Text_SNWingGlows, MSGBOX_NPC
	end

CanalaveCity_House3_EventScript_PtNpc2::
	lock
	faceplayer
	goto_if_set FLAG_SN_ELDRITCH_SON_WOKE, CanalaveCity_House3_EventScript_SNMomThanks
	goto_if_set FLAG_SYS_GAME_CLEAR, CanalaveCity_House3_EventScript_SNMomWorried
	msgbox CanalaveCity_House3_Text_SNEnergy, MSGBOX_DEFAULT
	release
	end

CanalaveCity_House3_Text_SNEnergy::
	.string "Our boy has too much energy! ...That’s\n"
	.string "the best way to be!$"

CanalaveCity_House3_EventScript_SNMomWorried::
	msgbox CanalaveCity_House3_Text_PtNpc2, MSGBOX_DEFAULT
	release
	end

CanalaveCity_House3_Text_PtNpc2::
	.string "I never thought our boy would fall into\n"
	.string "this endless nightmare...\p"
	.string "It’s happened in the past in Canalave...\p"
	.string "There were people who never woke up\n"
	.string "from their nightmares...\p"
	.string "...That is, until they were awoken using\n"
	.string "something called the Lunar Wing.\p"
	.string "My husband went to find a Lunar Wing\n"
	.string "on Fullmoon Island, but he failed...\p"
	.string "Does it take a Trainer to do that? We\n"
	.string "feel so frustrated by this...$"

CanalaveCity_House3_EventScript_SNMomThanks::
	msgbox CanalaveCity_House3_Text_SNCantThank, MSGBOX_DEFAULT
	release
	end

CanalaveCity_House3_Text_SNCantThank::
	.string "Thank you! We can’t thank you enough,\n"
	.string "but thank you!$"
