VerdanturfTown_WandasHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VerdanturfTown_WandasHouse_OnTransition
	.byte 0

@ Super Emerald: WALLY comes home after his journey through JOHTO, KANTO and SINNOH
VerdanturfTown_WandasHouse_OnTransition:
	call_if_ge VAR_SE_WALLY_QUEST, 3, VerdanturfTown_WandasHouse_EventScript_WallyIsHome
	end

VerdanturfTown_WandasHouse_EventScript_WallyIsHome::
	clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLY
	return

VerdanturfTown_WandasHouse_EventScript_Wally::
	lock
	faceplayer
	goto_if_ge VAR_SE_WALLY_QUEST, 3, VerdanturfTown_WandasHouse_EventScript_WallyBackHome
	goto_if_set FLAG_WALLY_SPEECH, VerdanturfTown_WandasHouse_EventScript_WallyShortSpeech
	msgbox VerdanturfTown_WandasHouse_Text_StrongerSpeech, MSGBOX_DEFAULT
	setflag FLAG_WALLY_SPEECH
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallyShortSpeech::
	msgbox VerdanturfTown_WandasHouse_Text_StrongerSpeechShort, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncle::
	lock
	faceplayer
	goto_if_ge VAR_SE_WALLY_QUEST, 3, VerdanturfTown_WandasHouse_EventScript_WallysUncleHome
	goto_if_ge VAR_SE_WALLY_QUEST, 1, VerdanturfTown_WandasHouse_EventScript_WallysUncleLetters
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, VerdanturfTown_WandasHouse_EventScript_WallysUncleEverGrande
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WallysUncleSlippedOff
	msgbox VerdanturfTown_WandasHouse_Text_WallysNextDoor, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncleSlippedOff::
	msgbox VerdanturfTown_WandasHouse_Text_WallySlippedOff, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncleEverGrande::
	msgbox VerdanturfTown_WandasHouse_Text_WallyGoneThatFar, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WandasBoyfriend::
	msgbox VerdanturfTown_WandasHouse_Text_CanSeeGirlfriendEveryDay, MSGBOX_NPC
	end

VerdanturfTown_WandasHouse_EventScript_Wanda::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WandaDontWorry
	goto_if_set FLAG_DEFEATED_WALLY_MAUVILLE, VerdanturfTown_WandasHouse_EventScript_MeetWanda
	msgbox VerdanturfTown_WandasHouse_Text_DontWorryAboutWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_MeetWanda::
	msgbox VerdanturfTown_WandasHouse_Text_MeetWanda, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WandaDontWorry::
	msgbox VerdanturfTown_WandasHouse_Text_DontWorryAboutWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAunt::
	lock
	faceplayer
	goto_if_ge VAR_SE_WALLY_QUEST, 3, VerdanturfTown_WandasHouse_EventScript_WallysAuntHome
	goto_if_ge VAR_SE_WALLY_QUEST, 1, VerdanturfTown_WandasHouse_EventScript_WallysAuntLetters
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, VerdanturfTown_WandasHouse_EventScript_WallysAuntEverGrande
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WallysAuntAnythingHappened
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_WandasHouse_EventScript_WallysAuntTunnelOpen
	msgbox VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendDriven, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntTunnelOpen::
	msgbox VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendWasDigging, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntAnythingHappened::
	msgbox VerdanturfTown_WandasHouse_Text_IfAnythingHappenedToWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntEverGrande::
	msgbox VerdanturfTown_WandasHouse_Text_WallyWasInEverGrande, MSGBOX_DEFAULT
	release
	end

@ Super Emerald: WALLY's journey (VAR_SE_WALLY_QUEST)
VerdanturfTown_WandasHouse_EventScript_WallyBackHome::
	msgbox VerdanturfTown_WandasHouse_Text_WallyBackHome, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncleLetters::
	msgbox VerdanturfTown_WandasHouse_Text_WallysUncleLetters, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncleHome::
	msgbox VerdanturfTown_WandasHouse_Text_WallysUncleHome, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntLetters::
	msgbox VerdanturfTown_WandasHouse_Text_WallysAuntLetters, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntHome::
	msgbox VerdanturfTown_WandasHouse_Text_WallysAuntHome, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_Text_WallyBackHome:
	.string "WALLY: {PLAYER}! Welcome!\p"
	.string "JOHTO, KANTO, SINNOH…\n"
	.string "I really saw the world, just like\l"
	.string "you did.\p"
	.string "My uncle says I've never looked so\n"
	.string "healthy. GALLADE and I will keep\l"
	.string "training here for now.\p"
	.string "Thank you for taking me along on that\n"
	.string "first trip, {PLAYER}.$"

VerdanturfTown_WandasHouse_Text_WallysUncleLetters:
	.string "UNCLE: WALLY sends us letters from\n"
	.string "the other regions!\p"
	.string "To think that frail boy would cross\n"
	.string "the sea all by himself…\p"
	.string "He wrote that he keeps meeting you\n"
	.string "on the road. Look after him, okay?$"

VerdanturfTown_WandasHouse_Text_WallysUncleHome:
	.string "UNCLE: WALLY's back from his journey,\n"
	.string "and he's bursting with stories.\p"
	.string "He says every one of them has you\n"
	.string "in it, {PLAYER}!$"

VerdanturfTown_WandasHouse_Text_WallysAuntLetters:
	.string "WALLY wrote to us from a faraway\n"
	.string "region!\p"
	.string "I sent the news to his parents in\n"
	.string "PETALBURG right away.$"

VerdanturfTown_WandasHouse_Text_WallysAuntHome:
	.string "WALLY came home safe and sound.\n"
	.string "His parents in PETALBURG were so\l"
	.string "relieved.$"

VerdanturfTown_WandasHouse_Text_StrongerSpeech:
	.string "WALLY: I lost to you, {PLAYER}, but I'm\n"
	.string "not feeling down anymore.\p"
	.string "Because I have a new purpose in life.\n"
	.string "Together with my RALTS, I'm going\l"
	.string "to challenge POKéMON GYMS and become\l"
	.string "a great TRAINER.\p"
	.string "Please watch me, {PLAYER}.\n"
	.string "I'm going to be stronger than you.\p"
	.string "When I do, I'm going to challenge you\n"
	.string "to another battle.$"

VerdanturfTown_WandasHouse_Text_StrongerSpeechShort:
	.string "WALLY: Please watch me, {PLAYER}.\n"
	.string "I'm going to get stronger than you.\p"
	.string "When I do, I'm going to challenge you\n"
	.string "to another battle.$"

VerdanturfTown_WandasHouse_Text_WallysNextDoor:
	.string "UNCLE: Oh! {PLAYER}{KUN}!\n"
	.string "WALLY's next door.\p"
	.string "But, boy, there's something I have to\n"
	.string "tell you.\p"
	.string "This natural environment is doing\n"
	.string "wonders for WALLY's health.\p"
	.string "Maybe it's not just the environment.\n"
	.string "It could be POKéMON that are giving\l"
	.string "the boy hope.$"

VerdanturfTown_WandasHouse_Text_WallySlippedOff:
	.string "WALLY's gone away…\n"
	.string "He slipped off on his own…$"

VerdanturfTown_WandasHouse_Text_WallyGoneThatFar:
	.string "UNCLE: Is that right?\n"
	.string "WALLY's gone away that far all by\l"
	.string "himself…\p"
	.string "Well, I have to give him credit--he is\n"
	.string "my little brother's son.$"

VerdanturfTown_WandasHouse_Text_MeetWanda:
	.string "WANDA: You are?\n"
	.string "Oh, right, I get it!\p"
	.string "You're the {PLAYER} who WALLY was\n"
	.string "telling me about.\p"
	.string "I'm WALLY's cousin.\n"
	.string "Glad to meet you!\p"
	.string "I think WALLY's become a lot more lively\n"
	.string "and healthy since he came here.$"

VerdanturfTown_WandasHouse_Text_DontWorryAboutWally:
	.string "WANDA: Don't worry about WALLY.\n"
	.string "He'll be just fine.\p"
	.string "I know my little cousin, and he has\n"
	.string "POKéMON with him, too.$"

VerdanturfTown_WandasHouse_Text_CanSeeGirlfriendEveryDay:
	.string "Thanks to you, I can see my girlfriend\n"
	.string "every day.\l"
	.string "Happy? You bet I am!$"

VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendDriven:
	.string "My daughter's boyfriend is a very\n"
	.string "driven and passionate sort of person.\p"
	.string "He's been digging a tunnel nonstop\n"
	.string "just so he can see my daughter.\p"
	.string "My daughter's a little concerned,\n"
	.string "so she goes out to the tunnel a lot.$"

VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendWasDigging:
	.string "It's amazing. My daughter's boyfriend\n"
	.string "was digging the tunnel by hand!\p"
	.string "It's so incredible!$"

VerdanturfTown_WandasHouse_Text_IfAnythingHappenedToWally:
	.string "If anything were to happen to WALLY,\n"
	.string "I would never be able to look his\l"
	.string "parents in PETALBURG in the eye…$"

VerdanturfTown_WandasHouse_Text_WallyWasInEverGrande:
	.string "WALLY was in EVER GRANDE?\p"
	.string "His parents in PETALBURG would be\n"
	.string "astonished to hear that!$"

