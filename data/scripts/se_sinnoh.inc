@ Super Emerald: Sinnoh (post-story free world, maps from LiderMorti00's Sinnoh repo)

@ ---------------------------------------------------------------------------
@ Norman's Canalave Ticket (after the Johto League) and the ship from Slateport
SE_EventScript_BirchCanalaveTicket::
	goto_if_unset FLAG_SE_JOHTO_LEAGUE_CLEARED, Common_EventScript_NopReturn
	goto_if_set FLAG_SE_RECEIVED_CANALAVE_TICKET, Common_EventScript_NopReturn
	msgbox SE_Text_BirchCanalaveTicket, MSGBOX_DEFAULT
	giveitem ITEM_CANALAVE_TICKET
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_BirchCanalaveTicketBagFull
	setflag FLAG_SE_RECEIVED_CANALAVE_TICKET
	msgbox SE_Text_BirchCanalaveTicketExplain, MSGBOX_DEFAULT
	release
	end

SE_EventScript_BirchCanalaveTicketBagFull::
	call Common_EventScript_BagIsFull
	release
	end

SE_Text_BirchCanalaveTicket:
	.string "PROF. BIRCH: {PLAYER}! You're the\n"
	.string "CHAMPION of JOHTO now, too?\l"
	.string "That's incredible!\p"
	.string "Listen, I have a friend who is a\n"
	.string "POKéMON PROFESSOR in SINNOH.\l"
	.string "His name is PROF. ROWAN.\p"
	.string "I told him all about you, and he\n"
	.string "said he'd love to meet you.\p"
	.string "So I got you this. Here!$"

SE_Text_BirchCanalaveTicketExplain:
	.string "PROF. BIRCH: That CANALAVE TICKET\n"
	.string "is for the ship from SLATEPORT to\l"
	.string "CANALAVE CITY, in SINNOH.\p"
	.string "PROF. ROWAN's lab is in SANDGEM\n"
	.string "TOWN. He looks stern, but he's a\l"
	.string "great researcher. Say hi for me!$"

SE_EventScript_SlateportOfferJohtoSinnoh::
	message SE_Text_SlateportWhere
	waitmessage
	dynmultipush SE_Text_ChoiceOlivine, 0
	dynmultipush SE_Text_ChoiceCanalave, 1
	dynmultistack 18, 6, FALSE, 2, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case 0, SE_EventScript_SlateportToOlivine
	case 1, SE_EventScript_SlateportToCanalave
	return

SE_EventScript_SlateportToCanalave::
	goto_if_ne VAR_SE_SINNOH_ARRIVAL, 0, SE_EventScript_SlateportToCanalaveGo
	setvar VAR_SE_SINNOH_ARRIVAL, 1
SE_EventScript_SlateportToCanalaveGo::
	call SlateportCity_Harbor_EventScript_BoardFerry
	setvar VAR_SE_CRUISE_DEST, 4
	goto SE_EventScript_BoardTidal
	waitstate
	release
	end

SE_Text_SlateportWhere:
	.string "Where would you like to sail?$"

SE_Text_ChoiceCanalave:
	.string "CANALAVE$"

@ ---------------------------------------------------------------------------
@ Canalave City: ships to other regions leave from the north port, where Dawn
@ welcomes the player
SE_EventScript_HideCanalaveDawn::
	setflag FLAG_SE_HIDE_CANALAVE_DAWN
	return

SE_EventScript_ShowCanalaveDawn::
	clearflag FLAG_SE_HIDE_CANALAVE_DAWN
	return

SE_EventScript_CanalaveDawnScene::
	lockall
	turnobject LOCALID_CANALAVE_SE_DAWN, DIR_NORTH
	turnobject LOCALID_PLAYER, DIR_SOUTH
	msgbox SE_Text_DawnWelcome, MSGBOX_DEFAULT
	closemessage
	setvar VAR_SE_SINNOH_ARRIVAL, 2
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_CANALAVE_SE_DAWN
	setflag FLAG_SE_HIDE_CANALAVE_DAWN
	fadescreen FADE_FROM_BLACK
	releaseall
	end

SE_Text_DawnWelcome:
	.string "Hi! You must be {PLAYER}!\p"
	.string "I'm DAWN. I help PROF. ROWAN with\n"
	.string "his research.\p"
	.string "Welcome to SINNOH! The PROFESSOR\n"
	.string "asked me to meet you at the port.\p"
	.string "His lab is in SANDGEM TOWN, far to\n"
	.string "the south. He has a POKéMON he'd\l"
	.string "like to give you.\p"
	.string "SINNOH has eight GYMS and its own\n"
	.string "POKéMON LEAGUE, too. Have fun!$"

SE_EventScript_CanalaveSailor::
	lock
	faceplayer
	setvar VAR_0x8008, 4
	goto SE_EventScript_ShipSailor
	end

SE_EventScript_CanalaveToSlateport::
	msgbox SFR_Text_VermilionSailorAllAboard, MSGBOX_DEFAULT
	closemessage
	playse SE_SHIP
	fadescreenspeed FADE_TO_BLACK, 12
	delay 60
	setvar VAR_SE_CRUISE_DEST, 2
	goto SE_EventScript_BoardTidal
	waitstate
	release
	end

SE_EventScript_CanalaveToOlivine::
	msgbox SFR_Text_VermilionSailorAllAboard, MSGBOX_DEFAULT
	closemessage
	playse SE_SHIP
	fadescreenspeed FADE_TO_BLACK, 12
	delay 60
	setvar VAR_SE_CRUISE_DEST, 1
	goto SE_EventScript_BoardTidal
	waitstate
	release
	end

@ ---------------------------------------------------------------------------
@ Sandgem Town: Professor Rowan gives a Sinnoh starter
SE_EventScript_Rowan::
	lock
	faceplayer
	goto_if_set FLAG_SE_RECEIVED_SINNOH_STARTER, SE_EventScript_RowanAfter
	msgbox SE_Text_RowanIntro, MSGBOX_DEFAULT
SE_EventScript_RowanChoose::
	message SE_Text_RowanWhich
	waitmessage
	dynmultipush SE_Text_ChoiceTurtwig, 0
	dynmultipush SE_Text_ChoiceChimchar, 1
	dynmultipush SE_Text_ChoicePiplup, 2
	dynmultistack 17, 4, FALSE, 3, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case 0, SE_EventScript_RowanTurtwig
	case 1, SE_EventScript_RowanChimchar
	case 2, SE_EventScript_RowanPiplup
	goto SE_EventScript_RowanChoose
	end

SE_EventScript_RowanTurtwig::
	setvar VAR_SE_SINNOH_STARTER, 1
	setvar VAR_SN_STARTER_MON, 0
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TURTWIG
	bufferspeciesname STR_VAR_1, SPECIES_TURTWIG
	givemon SPECIES_TURTWIG, 45, ITEM_EVERSTONE
	goto SE_EventScript_RowanGave

SE_EventScript_RowanChimchar::
	setvar VAR_SE_SINNOH_STARTER, 2
	setvar VAR_SN_STARTER_MON, 1
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_CHIMCHAR
	bufferspeciesname STR_VAR_1, SPECIES_CHIMCHAR
	givemon SPECIES_CHIMCHAR, 45, ITEM_EVERSTONE
	goto SE_EventScript_RowanGave

SE_EventScript_RowanPiplup::
	setvar VAR_SE_SINNOH_STARTER, 3
	setvar VAR_SN_STARTER_MON, 2
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_PIPLUP
	bufferspeciesname STR_VAR_1, SPECIES_PIPLUP
	givemon SPECIES_PIPLUP, 45, ITEM_EVERSTONE
	goto SE_EventScript_RowanGave

SE_EventScript_RowanGave::
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, SE_EventScript_RowanNoRoom
	playfanfare MUS_OBTAIN_ITEM
	message SE_Text_ReceivedSinnohStarter
	waitmessage
	waitfanfare
	setflag FLAG_SE_RECEIVED_SINNOH_STARTER
	msgbox SE_Text_RowanAfterGift, MSGBOX_DEFAULT
	release
	end

SE_EventScript_RowanNoRoom::
	msgbox SE_Text_RowanNoRoom, MSGBOX_DEFAULT
	release
	end

SE_EventScript_RowanAfter::
	msgbox SE_Text_RowanAfter, MSGBOX_DEFAULT
	release
	end

SE_EventScript_RowanAssistant::
	msgbox SE_Text_RowanAssistant, MSGBOX_NPC
	end

SE_Text_RowanIntro:
	.string "ROWAN: So you are NORMAN's child.\n"
	.string "I am PROF. ROWAN.\p"
	.string "The CHAMPION of HOENN and JOHTO…\n"
	.string "Your POKéMON trust you deeply.\p"
	.string "SINNOH's POKéMON should meet a\n"
	.string "TRAINER like you.\p"
	.string "Choose one of these three. They are\n"
	.string "strong, and each holds an EVERSTONE.$"

SE_Text_RowanWhich:
	.string "Which POKéMON will you take?$"

SE_Text_ChoiceTurtwig:
	.string "TURTWIG$"

SE_Text_ChoiceChimchar:
	.string "CHIMCHAR$"

SE_Text_ChoicePiplup:
	.string "PIPLUP$"

SE_Text_ReceivedSinnohStarter:
	.string "{PLAYER} received {STR_VAR_1}!$"

SE_Text_RowanAfterGift:
	.string "ROWAN: Take good care of it.\p"
	.string "SINNOH's GYM LEADERS and its\n"
	.string "POKéMON LEAGUE will test you well.$"

SE_Text_RowanNoRoom:
	.string "ROWAN: You have no room for another\n"
	.string "POKéMON. Make some room first.$"

SE_Text_RowanAfter:
	.string "ROWAN: POKéMON and people grow\n"
	.string "together. Remember that.$"

SE_Text_RowanAssistant:
	.string "DAWN: The PROFESSOR looks stern,\n"
	.string "but he's really kind!$"

@ ---------------------------------------------------------------------------
@ Lucas, the Sinnoh rival (he takes the starter strong against the player's)
@ VAR_SE_LUCAS_STATE: 1 after Sandgem, 2 after Hearthome, 3 after Victory Road.
SE_EventScript_LucasSandgemOnTransition::
	setflag FLAG_SE_HIDE_LUCAS_SANDGEM
	goto_if_unset FLAG_SE_RECEIVED_SINNOH_STARTER, Common_EventScript_NopReturn
	goto_if_ne VAR_SE_LUCAS_STATE, 0, Common_EventScript_NopReturn
	clearflag FLAG_SE_HIDE_LUCAS_SANDGEM
	return

SE_EventScript_LucasHearthomeOnTransition::
	setflag FLAG_SE_HIDE_LUCAS_HEARTHOME
	goto_if_ne VAR_SE_LUCAS_STATE, 1, Common_EventScript_NopReturn
	clearflag FLAG_SE_HIDE_LUCAS_HEARTHOME
	return

SE_EventScript_LucasVictoryRoadOnTransition::
	setflag FLAG_SE_HIDE_LUCAS_VICTORY_ROAD
	goto_if_unset FLAG_SE_RECEIVED_SINNOH_STARTER, Common_EventScript_NopReturn
	goto_if_ge VAR_SE_LUCAS_STATE, 3, Common_EventScript_NopReturn
	clearflag FLAG_SE_HIDE_LUCAS_VICTORY_ROAD
	return

SE_EventScript_LucasSandgem::
	lock
	faceplayer
	playbgm MUS_ENCOUNTER_BRENDAN, FALSE
	msgbox SE_Text_LucasSandgemIntro, MSGBOX_DEFAULT
	goto_if_eq VAR_SE_SINNOH_STARTER, 2, SE_EventScript_LucasSandgemEmpoleon
	goto_if_eq VAR_SE_SINNOH_STARTER, 3, SE_EventScript_LucasSandgemTorterra
	trainerbattle_no_intro TRAINER_SE_LUCAS_1_INFERNAPE, SE_Text_LucasSandgemDefeat
	goto SE_EventScript_LucasSandgemWon

SE_EventScript_LucasSandgemEmpoleon::
	trainerbattle_no_intro TRAINER_SE_LUCAS_1_EMPOLEON, SE_Text_LucasSandgemDefeat
	goto SE_EventScript_LucasSandgemWon

SE_EventScript_LucasSandgemTorterra::
	trainerbattle_no_intro TRAINER_SE_LUCAS_1_TORTERRA, SE_Text_LucasSandgemDefeat
	goto SE_EventScript_LucasSandgemWon

SE_EventScript_LucasSandgemWon::
	msgbox SE_Text_LucasSandgemAfter, MSGBOX_DEFAULT
	closemessage
	setvar VAR_SE_LUCAS_STATE, 1
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_SANDGEM_SE_LUCAS
	setflag FLAG_SE_HIDE_LUCAS_SANDGEM
	fadescreen FADE_FROM_BLACK
	release
	end

SE_EventScript_LucasHearthome::
	lock
	faceplayer
	playbgm MUS_ENCOUNTER_BRENDAN, FALSE
	msgbox SE_Text_LucasHearthomeIntro, MSGBOX_DEFAULT
	goto_if_eq VAR_SE_SINNOH_STARTER, 2, SE_EventScript_LucasHearthomeEmpoleon
	goto_if_eq VAR_SE_SINNOH_STARTER, 3, SE_EventScript_LucasHearthomeTorterra
	trainerbattle_no_intro TRAINER_SE_LUCAS_2_INFERNAPE, SE_Text_LucasHearthomeDefeat
	goto SE_EventScript_LucasHearthomeWon

SE_EventScript_LucasHearthomeEmpoleon::
	trainerbattle_no_intro TRAINER_SE_LUCAS_2_EMPOLEON, SE_Text_LucasHearthomeDefeat
	goto SE_EventScript_LucasHearthomeWon

SE_EventScript_LucasHearthomeTorterra::
	trainerbattle_no_intro TRAINER_SE_LUCAS_2_TORTERRA, SE_Text_LucasHearthomeDefeat
	goto SE_EventScript_LucasHearthomeWon

SE_EventScript_LucasHearthomeWon::
	msgbox SE_Text_LucasHearthomeAfter, MSGBOX_DEFAULT
	closemessage
	setvar VAR_SE_LUCAS_STATE, 2
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_HEARTHOME_SE_LUCAS
	setflag FLAG_SE_HIDE_LUCAS_HEARTHOME
	fadescreen FADE_FROM_BLACK
	release
	end

SE_EventScript_LucasVictoryRoad::
	lock
	faceplayer
	playbgm MUS_ENCOUNTER_BRENDAN, FALSE
	msgbox SE_Text_LucasVictoryRoadIntro, MSGBOX_DEFAULT
	goto_if_eq VAR_SE_SINNOH_STARTER, 2, SE_EventScript_LucasVictoryRoadEmpoleon
	goto_if_eq VAR_SE_SINNOH_STARTER, 3, SE_EventScript_LucasVictoryRoadTorterra
	trainerbattle_no_intro TRAINER_SE_LUCAS_3_INFERNAPE, SE_Text_LucasVictoryRoadDefeat
	goto SE_EventScript_LucasVictoryRoadWon

SE_EventScript_LucasVictoryRoadEmpoleon::
	trainerbattle_no_intro TRAINER_SE_LUCAS_3_EMPOLEON, SE_Text_LucasVictoryRoadDefeat
	goto SE_EventScript_LucasVictoryRoadWon

SE_EventScript_LucasVictoryRoadTorterra::
	trainerbattle_no_intro TRAINER_SE_LUCAS_3_TORTERRA, SE_Text_LucasVictoryRoadDefeat
	goto SE_EventScript_LucasVictoryRoadWon

SE_EventScript_LucasVictoryRoadWon::
	msgbox SE_Text_LucasVictoryRoadAfter, MSGBOX_DEFAULT
	closemessage
	setvar VAR_SE_LUCAS_STATE, 3
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_VICTORYROAD_SE_LUCAS
	setflag FLAG_SE_HIDE_LUCAS_VICTORY_ROAD
	fadescreen FADE_FROM_BLACK
	release
	end

SE_Text_LucasSandgemIntro:
	.string "Hey, you're {PLAYER}, right?\p"
	.string "I'm LUCAS. I help PROF. ROWAN\n"
	.string "with his POKéDEX.\p"
	.string "The PROFESSOR gave you a POKéMON?\n"
	.string "Then I got the one that beats it!\p"
	.string "Let's see how a CHAMPION battles!$"

SE_Text_LucasSandgemDefeat:
	.string "Wow… That's a CHAMPION for you.$"

SE_Text_LucasSandgemAfter:
	.string "I'll fill in the POKéDEX while you\n"
	.string "take on the GYMS.\p"
	.string "Next time, I'll be stronger!$"

SE_Text_LucasHearthomeIntro:
	.string "{PLAYER}! Here in HEARTHOME?\p"
	.string "I've been training all over SINNOH.\n"
	.string "Let's battle again!$"

SE_Text_LucasHearthomeDefeat:
	.string "Still not enough…$"

SE_Text_LucasHearthomeAfter:
	.string "You and your POKéMON really are\n"
	.string "something else.\p"
	.string "I'll see you near the POKéMON\n"
	.string "LEAGUE. Don't lose before then!$"

SE_Text_LucasVictoryRoadIntro:
	.string "There you are, {PLAYER}.\p"
	.string "The POKéMON LEAGUE is right behind\n"
	.string "me. One last battle before you go!$"

SE_Text_LucasVictoryRoadDefeat:
	.string "…Okay. You win, fair and square.$"

SE_Text_LucasVictoryRoadAfter:
	.string "Go show the ELITE FOUR and CYNTHIA\n"
	.string "what you can do.\p"
	.string "PROF. ROWAN will be proud of us both!$"

SE_EventScript_SinnohLeader_Roark::
	trainerbattle_single TRAINER_SE_LEADER_ROARK, SE_Text_RoarkIntro, SE_Text_RoarkDefeat, SE_EventScript_RoarkDefeated, NO_MUSIC
	goto_if_unset FLAG_SE_RECEIVED_SINNOH_TM1, SE_EventScript_RoarkGiveTM
	msgbox SE_Text_RoarkPost, MSGBOX_DEFAULT
	release
	end

SE_EventScript_RoarkDefeated::
	message SE_Text_ReceivedRoarkBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_SINNOH_BADGE1_GET
	goto SE_EventScript_RoarkGiveTM
	end

SE_EventScript_RoarkGiveTM::
	giveitem ITEM_TM_ROCK_TOMB
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SE_RECEIVED_SINNOH_TM1
	msgbox SE_Text_RoarkPost, MSGBOX_DEFAULT
	release
	end

SE_Text_RoarkIntro:
	.string "Welcome! I'm ROARK, the\nOREBURGH GYM LEADER.\pI heard a CHAMPION was coming.\nMy rock POKéMON are ready!$"

SE_Text_RoarkDefeat:
	.string "Whoa… You're the real deal.\nHere's the COAL BADGE!$"

SE_Text_RoarkPost:
	.string "Rock POKéMON are as tough as the\nOREBURGH MINE. Visit anytime!$"

SE_Text_ReceivedRoarkBadge:
	.string "{PLAYER} received the COAL BADGE\nfrom ROARK.$"

SE_EventScript_SinnohLeader_Gardenia::
	trainerbattle_single TRAINER_SE_LEADER_GARDENIA, SE_Text_GardeniaIntro, SE_Text_GardeniaDefeat, SE_EventScript_GardeniaDefeated, NO_MUSIC
	goto_if_unset FLAG_SE_RECEIVED_SINNOH_TM2, SE_EventScript_GardeniaGiveTM
	msgbox SE_Text_GardeniaPost, MSGBOX_DEFAULT
	release
	end

SE_EventScript_GardeniaDefeated::
	message SE_Text_ReceivedGardeniaBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_SINNOH_BADGE2_GET
	goto SE_EventScript_GardeniaGiveTM
	end

SE_EventScript_GardeniaGiveTM::
	giveitem ITEM_TM_SOLAR_BEAM
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SE_RECEIVED_SINNOH_TM2
	msgbox SE_Text_GardeniaPost, MSGBOX_DEFAULT
	release
	end

SE_Text_GardeniaIntro:
	.string "I'm GARDENIA, the ETERNA GYM LEADER!\pMy grass POKéMON have grown strong\njust like the ETERNA FOREST!$"

SE_Text_GardeniaDefeat:
	.string "Amazing! You deserve the FOREST\nBADGE!$"

SE_Text_GardeniaPost:
	.string "The ETERNA FOREST is my favorite\nplace. You should visit it!$"

SE_Text_ReceivedGardeniaBadge:
	.string "{PLAYER} received the FOREST BADGE\nfrom GARDENIA.$"

SE_EventScript_SinnohLeader_Maylene::
	trainerbattle_single TRAINER_SE_LEADER_MAYLENE, SE_Text_MayleneIntro, SE_Text_MayleneDefeat, SE_EventScript_MayleneDefeated, NO_MUSIC
	goto_if_unset FLAG_SE_RECEIVED_SINNOH_TM3, SE_EventScript_MayleneGiveTM
	msgbox SE_Text_MaylenePost, MSGBOX_DEFAULT
	release
	end

SE_EventScript_MayleneDefeated::
	message SE_Text_ReceivedMayleneBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_SINNOH_BADGE3_GET
	goto SE_EventScript_MayleneGiveTM
	end

SE_EventScript_MayleneGiveTM::
	giveitem ITEM_TM_BULK_UP
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SE_RECEIVED_SINNOH_TM3
	msgbox SE_Text_MaylenePost, MSGBOX_DEFAULT
	release
	end

SE_Text_MayleneIntro:
	.string "I'm MAYLENE, VEILSTONE's GYM LEADER.\pI train my body and spirit with my\nfighting POKéMON. Let's go!$"

SE_Text_MayleneDefeat:
	.string "I lost… Please take the COBBLE\nBADGE.$"

SE_Text_MaylenePost:
	.string "I still have a lot to learn.\nThank you for the battle.$"

SE_Text_ReceivedMayleneBadge:
	.string "{PLAYER} received the COBBLE BADGE\nfrom MAYLENE.$"

SE_EventScript_SinnohLeader_Wake::
	trainerbattle_single TRAINER_SE_LEADER_WAKE, SE_Text_WakeIntro, SE_Text_WakeDefeat, SE_EventScript_WakeDefeated, NO_MUSIC
	goto_if_unset FLAG_SE_RECEIVED_SINNOH_TM4, SE_EventScript_WakeGiveTM
	msgbox SE_Text_WakePost, MSGBOX_DEFAULT
	release
	end

SE_EventScript_WakeDefeated::
	message SE_Text_ReceivedWakeBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_SINNOH_BADGE4_GET
	goto SE_EventScript_WakeGiveTM
	end

SE_EventScript_WakeGiveTM::
	giveitem ITEM_TM_WATER_PULSE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SE_RECEIVED_SINNOH_TM4
	msgbox SE_Text_WakePost, MSGBOX_DEFAULT
	release
	end

SE_Text_WakeIntro:
	.string "WAHAHAHA! I'm CRASHER WAKE!\pMy water POKéMON will wash you\naway! Here comes the wave!$"

SE_Text_WakeDefeat:
	.string "You crashed right through me!\nThe FEN BADGE is yours!$"

SE_Text_WakePost:
	.string "WAHAHA! What a splash of a battle!$"

SE_Text_ReceivedWakeBadge:
	.string "{PLAYER} received the FEN BADGE\nfrom WAKE.$"

SE_EventScript_SinnohLeader_Fantina::
	trainerbattle_single TRAINER_SE_LEADER_FANTINA, SE_Text_FantinaIntro, SE_Text_FantinaDefeat, SE_EventScript_FantinaDefeated, NO_MUSIC
	goto_if_unset FLAG_SE_RECEIVED_SINNOH_TM5, SE_EventScript_FantinaGiveTM
	msgbox SE_Text_FantinaPost, MSGBOX_DEFAULT
	release
	end

SE_EventScript_FantinaDefeated::
	message SE_Text_ReceivedFantinaBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_SINNOH_BADGE5_GET
	goto SE_EventScript_FantinaGiveTM
	end

SE_EventScript_FantinaGiveTM::
	giveitem ITEM_TM_SHADOW_BALL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SE_RECEIVED_SINNOH_TM5
	msgbox SE_Text_FantinaPost, MSGBOX_DEFAULT
	release
	end

SE_Text_FantinaIntro:
	.string "I am FANTINA, HEARTHOME's GYM\nLEADER.\pMy ghost POKéMON will dance you\ninto defeat!$"

SE_Text_FantinaDefeat:
	.string "Magnifique! Take the RELIC BADGE.$"

SE_Text_FantinaPost:
	.string "Your POKéMON dance beautifully!$"

SE_Text_ReceivedFantinaBadge:
	.string "{PLAYER} received the RELIC BADGE\nfrom FANTINA.$"

SE_EventScript_SinnohLeader_Byron::
	trainerbattle_single TRAINER_SE_LEADER_BYRON, SE_Text_ByronIntro, SE_Text_ByronDefeat, SE_EventScript_ByronDefeated, NO_MUSIC
	goto_if_unset FLAG_SE_RECEIVED_SINNOH_TM6, SE_EventScript_ByronGiveTM
	msgbox SE_Text_ByronPost, MSGBOX_DEFAULT
	release
	end

SE_EventScript_ByronDefeated::
	message SE_Text_ReceivedByronBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_SINNOH_BADGE6_GET
	goto SE_EventScript_ByronGiveTM
	end

SE_EventScript_ByronGiveTM::
	giveitem ITEM_TM_IRON_TAIL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SE_RECEIVED_SINNOH_TM6
	msgbox SE_Text_ByronPost, MSGBOX_DEFAULT
	release
	end

SE_Text_ByronIntro:
	.string "I'm BYRON, CANALAVE's GYM LEADER\nand ROARK's father!\pMy steel POKéMON are unbreakable!$"

SE_Text_ByronDefeat:
	.string "Gwahaha! Splendid! The MINE\nBADGE is yours!$"

SE_Text_ByronPost:
	.string "Tell ROARK his father lost to\na great TRAINER!$"

SE_Text_ReceivedByronBadge:
	.string "{PLAYER} received the MINE BADGE\nfrom BYRON.$"

SE_EventScript_SinnohLeader_Candice::
	trainerbattle_single TRAINER_SE_LEADER_CANDICE, SE_Text_CandiceIntro, SE_Text_CandiceDefeat, SE_EventScript_CandiceDefeated, NO_MUSIC
	goto_if_unset FLAG_SE_RECEIVED_SINNOH_TM7, SE_EventScript_CandiceGiveTM
	msgbox SE_Text_CandicePost, MSGBOX_DEFAULT
	release
	end

SE_EventScript_CandiceDefeated::
	message SE_Text_ReceivedCandiceBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_SINNOH_BADGE7_GET
	goto SE_EventScript_CandiceGiveTM
	end

SE_EventScript_CandiceGiveTM::
	giveitem ITEM_TM_BLIZZARD
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SE_RECEIVED_SINNOH_TM7
	msgbox SE_Text_CandicePost, MSGBOX_DEFAULT
	release
	end

SE_Text_CandiceIntro:
	.string "I'm CANDICE, SNOWPOINT's GYM LEADER!\pFocus! My ice POKéMON are all\nfired up!$"

SE_Text_CandiceDefeat:
	.string "Wow, you're great! Here's the\nICICLE BADGE!$"

SE_Text_CandicePost:
	.string "I'll keep focusing hard!$"

SE_Text_ReceivedCandiceBadge:
	.string "{PLAYER} received the ICICLE BADGE\nfrom CANDICE.$"

SE_EventScript_SinnohLeader_Volkner::
	trainerbattle_single TRAINER_SE_LEADER_VOLKNER, SE_Text_VolknerIntro, SE_Text_VolknerDefeat, SE_EventScript_VolknerDefeated, NO_MUSIC
	goto_if_unset FLAG_SE_RECEIVED_SINNOH_TM8, SE_EventScript_VolknerGiveTM
	msgbox SE_Text_VolknerPost, MSGBOX_DEFAULT
	release
	end

SE_EventScript_VolknerDefeated::
	message SE_Text_ReceivedVolknerBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_SINNOH_BADGE8_GET
	goto SE_EventScript_VolknerGiveTM
	end

SE_EventScript_VolknerGiveTM::
	giveitem ITEM_TM_THUNDERBOLT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SE_RECEIVED_SINNOH_TM8
	msgbox SE_Text_VolknerPost, MSGBOX_DEFAULT
	release
	end

SE_Text_VolknerIntro:
	.string "I'm VOLKNER, SUNNYSHORE's GYM LEADER.\pI was bored of battles… Show me\nsomething that sparks!$"

SE_Text_VolknerDefeat:
	.string "…That was fun. You earned the\nBEACON BADGE.$"

SE_Text_VolknerPost:
	.string "Go on to the POKéMON LEAGUE.\nCYNTHIA is waiting.$"

SE_Text_ReceivedVolknerBadge:
	.string "{PLAYER} received the BEACON BADGE\nfrom VOLKNER.$"

@ ---------------------------------------------------------------------------
@ Pokémon League
SE_SinnohLeague_OnWarp::
	map_script_2 VAR_TEMP_1, 0, SE_SinnohLeague_TurnPlayerNorth
	.2byte 0

SE_SinnohLeague_TurnPlayerNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

SE_SinnohLeague_OpenDoor::
	setmetatile 6, 1, METATILE_EliteFour_OpenDoor_Frame, FALSE
	setmetatile 6, 2, METATILE_EliteFour_OpenDoor_Opening, FALSE
	return

SE_SinnohAaronRoom_OnLoad::
	call_if_set FLAG_SN_DEFEATED_ELITE_4_SIDNEY, SE_SinnohLeague_OpenDoor
	end

SE_SinnohBerthaRoom_OnLoad::
	call_if_set FLAG_SN_DEFEATED_ELITE_4_PHOEBE, SE_SinnohLeague_OpenDoor
	end

SE_SinnohFlintRoom_OnLoad::
	call_if_set FLAG_SN_DEFEATED_ELITE_4_GLACIA, SE_SinnohLeague_OpenDoor
	end

SE_SinnohLucianRoom_OnLoad::
	call_if_set FLAG_SN_DEFEATED_ELITE_4_DRAKE, SE_SinnohLeague_OpenDoor
	end

SE_SinnohNorthPC_OnTransition::
	setrespawn HEAL_LOCATION_POKEMON_LEAGUE_NORTH_SINNOH
	clearflag FLAG_SN_DEFEATED_ELITE_4_SIDNEY
	clearflag FLAG_SN_DEFEATED_ELITE_4_PHOEBE
	clearflag FLAG_SN_DEFEATED_ELITE_4_GLACIA
	clearflag FLAG_SN_DEFEATED_ELITE_4_DRAKE
	end

PokemonLeague_ChampionRoom_sinnoh_MapScripts::
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, SE_SinnohLeague_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SE_SinnohChampion_OnFrame
	.byte 0

SE_SinnohChampion_OnFrame::
	map_script_2 VAR_TEMP_1, 0, SE_SinnohChampion_EnterRoom
	.2byte 0

SE_SinnohChampion_EnterRoom::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_WalkUp4
	waitmovement 0
	delay 40
	applymovement LOCALID_PLAYER, SE_SinnohChampion_Movement_Approach
	waitmovement 0
	setvar VAR_TEMP_1, 1
	playbgm MUS_DPP_VS_CYNTHIA, FALSE
	msgbox SE_Text_CynthiaIntro, MSGBOX_DEFAULT
	goto_if_set FLAG_SE_SINNOH_LEAGUE_CLEARED, SE_SinnohChampion_Rematch
	trainerbattle_no_intro TRAINER_SE_CHAMPION_CYNTHIA, SE_Text_CynthiaDefeat
SE_SinnohChampion_AfterBattle::
	setflag FLAG_DAILY_SE_SINNOH_LEAGUE
	playse SE_DOOR
	setmetatile 6, 1, METATILE_EliteFour_OpenDoorChampion_Frame, FALSE
	setmetatile 6, 2, METATILE_EliteFour_OpenDoorChampion_Opening, FALSE
	special DrawWholeMapView
	msgbox SE_Text_CynthiaPost, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement LOCALID_SN_CHAMP_CYNTHIA, SE_SinnohChampion_Movement_CynthiaExitStart
	applymovement LOCALID_PLAYER, SE_SinnohChampion_Movement_Approach
	waitmovement 0
	applymovement LOCALID_SN_CHAMP_CYNTHIA, SE_SinnohChampion_Movement_CynthiaExit
	applymovement LOCALID_PLAYER, SE_SinnohChampion_Movement_PlayerExit
	waitmovement 0
	warp MAP_POKEMON_LEAGUE_HALL_OF_FAME_ROOM_SINNOH, 7, 16
	waitstate
	releaseall
	end

SE_SinnohChampion_Rematch::
	trainerbattle_no_intro TRAINER_SE_CHAMPION_CYNTHIA_REMATCH, SE_Text_CynthiaDefeat
	goto SE_SinnohChampion_AfterBattle

SE_SinnohChampion_Movement_Approach:
	walk_up
	walk_up
	step_end

SE_SinnohChampion_Movement_PlayerExit:
	walk_up
	delay_16
	walk_up
	delay_8
	set_invisible
	step_end

SE_SinnohChampion_Movement_CynthiaExitStart:
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

SE_SinnohChampion_Movement_CynthiaExit:
	walk_up
	delay_8
	set_invisible
	step_end

SE_Text_CynthiaIntro:
	.string "I'm CYNTHIA, the CHAMPION of the\n"
	.string "SINNOH POKéMON LEAGUE.\p"
	.string "I heard about you, {PLAYER}. The\n"
	.string "CHAMPION of HOENN and JOHTO…\p"
	.string "There's something about you that\n"
	.string "makes me want to battle with all\l"
	.string "my strength.\p"
	.string "As the CHAMPION, I accept your\n"
	.string "challenge!$"

SE_Text_CynthiaDefeat:
	.string "Just a moment ago, you were the\n"
	.string "most powerful challenger.\p"
	.string "And just now, you became the most\n"
	.string "powerful of all TRAINERS!$"

SE_Text_CynthiaPost:
	.string "CYNTHIA: That was wonderful.\p"
	.string "You and your POKéMON have a bond\n"
	.string "that I can feel from here.\p"
	.string "Come. Let's record your name in the\n"
	.string "HALL OF FAME.$"

PokemonLeague_HallOfFameRoom_sinnoh_MapScripts::
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, SE_SinnohLeague_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SE_SinnohHallOfFame_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, SE_SinnohHallOfFame_OnTransition
	.byte 0

SE_SinnohHallOfFame_OnTransition::
	setflag FLAG_SN_HIDE_HOF_ROWAN
	end

SE_SinnohHallOfFame_OnFrame::
	map_script_2 VAR_TEMP_1, 0, SE_SinnohHallOfFame_Enter
	.2byte 0

SE_SinnohHallOfFame_Enter::
	lockall
	applymovement LOCALID_SN_HOF_CYNTHIA, SE_SinnohHallOfFame_Movement_Walk
	applymovement LOCALID_PLAYER, SE_SinnohHallOfFame_Movement_Walk
	waitmovement 0
	applymovement LOCALID_SN_HOF_CYNTHIA, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox SE_Text_CynthiaHallOfFame, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SN_HOF_CYNTHIA, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 20
	setvar VAR_TEMP_1, 1
	setflag FLAG_SE_SINNOH_LEAGUE_CLEARED
	setflag FLAG_SN_ENTERED_ELITE_FOUR
	setrespawn HEAL_LOCATION_SANDGEM_TOWN_SINNOH
	fadescreenspeed FADE_TO_BLACK, 24
	special EnterHallOfFame
	waitstate
	releaseall
	end

SE_SinnohHallOfFame_Movement_Walk:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SE_Text_CynthiaHallOfFame:
	.string "CYNTHIA: This is where the names of\n"
	.string "the CHAMPIONS and their POKéMON\l"
	.string "are recorded forever.\p"
	.string "HOENN, JOHTO and now SINNOH…\n"
	.string "Your journey is truly legendary.$"

@ ---------------------------------------------------------------------------
@ Canalave City map scripts (Dawn's welcome)
CanalaveCity_sinnoh_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SE_CanalaveCity_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SE_CanalaveCity_OnFrame
	.byte 0

SE_CanalaveCity_OnTransition::
	setrespawn HEAL_LOCATION_CANALAVE_CITY_SINNOH
	end

SE_CanalaveCity_OnFrame::
	map_script_2 VAR_SE_SINNOH_ARRIVAL, 1, SE_EventScript_CanalaveDawnScene
	.2byte 0

@ ---------------------------------------------------------------------------
@ Runs on every map transition in Sinnoh (from script.c)
SE_EventScript_SinnohOnTransition::
	call_if_ne VAR_SE_SINNOH_ARRIVAL, 1, SE_EventScript_HideCanalaveDawn
	call_if_eq VAR_SE_SINNOH_ARRIVAL, 1, SE_EventScript_ShowCanalaveDawn
	call SE_EventScript_LucasSandgemOnTransition
	call SE_EventScript_LucasHearthomeOnTransition
	call SE_EventScript_LucasVictoryRoadOnTransition
	call SE_EventScript_SinnohLegendaries
	call SE_EventScript_RileyOnTransition
	end

@ ---------------------------------------------------------------------------
@ Riley waits outside Iron Island with the Riolu Egg (the story escort is skipped)
SE_EventScript_RileyOnTransition::
	setflag FLAG_SN_HIDE_IRON_RILEY
	goto_if_set FLAG_SN_RECEIVED_RIOLU_EGG, Common_EventScript_NopReturn
	clearflag FLAG_SN_HIDE_IRON_RILEY
	return

SE_EventScript_RileyEgg::
	lock
	faceplayer
	msgbox SE_Text_RileyEgg, MSGBOX_DEFAULT
	getpartysize
	goto_if_eq VAR_RESULT, PARTY_SIZE, SE_EventScript_RileyEggNoRoom
	giveegg SPECIES_RIOLU
	playfanfare MUS_OBTAIN_ITEM
	message SE_Text_RileyGotEgg
	waitfanfare
	waitmessage
	setflag FLAG_SN_RECEIVED_RIOLU_EGG
	msgbox SE_Text_RileyEggBye, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	setflag FLAG_SN_HIDE_IRON_RILEY
	fadescreen FADE_FROM_BLACK
	release
	end

SE_EventScript_RileyEggNoRoom::
	msgbox SE_Text_RileyEggNoRoom, MSGBOX_DEFAULT
	release
	end

SE_Text_RileyEgg:
	.string "RILEY: So you're the TRAINER who\n"
	.string "helped save SINNOH. I'm RILEY.\p"
	.string "I have a POKéMON EGG here.\n"
	.string "Would you take it with you?$"

SE_Text_RileyGotEgg:
	.string "{PLAYER} received an EGG from RILEY!$"

SE_Text_RileyEggBye:
	.string "RILEY: Show the POKéMON inside the\n"
	.string "EGG all sorts of new places.\p"
	.string "I'll be training at the BATTLEGROUND.\n"
	.string "Let's meet again!$"

SE_Text_RileyEggNoRoom:
	.string "RILEY: Your party is full.\n"
	.string "Come back when you have room.$"

@ Super Emerald: NPCs that had nothing to say
SE_EventScript_RowanAideA::
	msgbox SE_EventScript_RowanAideA_Text, MSGBOX_NPC
	end

SE_EventScript_RowanAideA_Text:
	.string "PROF. ROWAN studies how POKéMON\n"
	.string "evolve.\p"
	.string "He says evolution is a mystery\n"
	.string "we've barely begun to solve.$"

SE_EventScript_RowanAideB::
	msgbox SE_EventScript_RowanAideB_Text, MSGBOX_NPC
	end

SE_EventScript_RowanAideB_Text:
	.string "PROF. ROWAN looks scary, but he\n"
	.string "really cares about POKéMON!$"


@ ---------------------------------------------------------------
@ Super Emerald: access to the Hall of Origin, Rock Peak Ruins and
@ Iceberg Ruins (postgame, after the SINNOH LEAGUE)
@ ---------------------------------------------------------------
SE_EventScript_SpearPillarAltar::
	lockall
	goto_if_unset FLAG_SE_SINNOH_LEAGUE_CLEARED, SE_EventScript_SpearPillarAltarSealed
	goto_if_set FLAG_SN_DONE_ARCEUS, SE_EventScript_SpearPillarAltarQuiet
	msgbox SE_Text_SpearPillarAltarStairs, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SE_EventScript_RuinsEntranceEnd
	playse SE_M_DETECT
	waitse
	fadescreen FADE_TO_WHITE
	warp MAP_HALL_OF_ORIGIN_SINNOH, 0
	waitstate
	releaseall
	end

SE_EventScript_SpearPillarAltarSealed::
	msgbox SE_Text_SpearPillarAltarSealed, MSGBOX_DEFAULT
	releaseall
	end

SE_EventScript_SpearPillarAltarQuiet::
	msgbox SE_Text_SpearPillarAltarQuiet, MSGBOX_DEFAULT
	releaseall
	end

SE_EventScript_RockPeakRuinsEntrance::
	lockall
	goto_if_unset FLAG_SE_SINNOH_LEAGUE_CLEARED, SE_EventScript_RuinsEntranceSealed
	msgbox SE_Text_RockPeakRuinsEntrance, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SE_EventScript_RuinsEntranceEnd
	playse SE_EXIT
	warp MAP_ROCK_PEAK_RUINS_SINNOH, 0
	waitstate
	releaseall
	end

SE_EventScript_IcebergRuinsEntrance::
	lockall
	goto_if_unset FLAG_SE_SINNOH_LEAGUE_CLEARED, SE_EventScript_RuinsEntranceSealed
	msgbox SE_Text_IcebergRuinsEntrance, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SE_EventScript_RuinsEntranceEnd
	playse SE_EXIT
	warp MAP_ICEBERG_RUINS_SINNOH, 0
	waitstate
	releaseall
	end

SE_EventScript_RuinsEntranceSealed::
	msgbox SE_Text_RuinsEntranceSealed, MSGBOX_DEFAULT
SE_EventScript_RuinsEntranceEnd::
	releaseall
	end

SE_Text_SpearPillarAltarSealed:
	.string "An ancient altar stands here.\n"
	.string "It feels like it's waiting for\l"
	.string "someone worthy…$"

SE_Text_SpearPillarAltarStairs:
	.string "The altar is shining softly…\p"
	.string "A stairway of light seems to lead\n"
	.string "up into the sky.\p"
	.string "Climb the stairway?$"

SE_Text_SpearPillarAltarQuiet:
	.string "The altar is silent now.$"

SE_Text_RockPeakRuinsEntrance:
	.string "There's a hollow in the sand…\n"
	.string "An old doorway is hidden inside.\p"
	.string "Go down into the ruins?$"

SE_Text_IcebergRuinsEntrance:
	.string "A freezing wind blows out of a\n"
	.string "crack in the wall…\p"
	.string "Go into the crack?$"

SE_Text_RuinsEntranceSealed:
	.string "There are strange markings here.\n"
	.string "The way is sealed by an unknown\l"
	.string "power…$"
