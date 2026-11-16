VeilstoneCity_sinnoh_MapScripts::
	.byte 0


VeilstoneCity_EventScript_PtNpc1::
	msgbox VeilstoneCity_Text_PtNpc1, MSGBOX_NPC
	end

VeilstoneCity_Text_PtNpc1::
	.string "Yeah, TEAM GALACTIC is hiding all\n"
	.string "sorts of good stuff in their\l"
	.string "warehouse.\p"
	.string "I hear they even have a Hidden\n"
	.string "Machine in there!$"

VeilstoneCity_EventScript_PtNpc2::
	msgbox VeilstoneCity_Text_PtNpc2, MSGBOX_NPC
	end

VeilstoneCity_Text_PtNpc2::
	.string "The Game Corner is dangerous!\p"
	.string "Why is it dangerous? It's so fun, I\n"
	.string "lose track of time!$"

VeilstoneCity_EventScript_PtNpc3::
	msgbox VeilstoneCity_Text_PtNpc3, MSGBOX_NPC
	end

VeilstoneCity_Text_PtNpc3::
	.string "I got a TM as a prize from the Game\n"
	.string "Corner.\p"
	.string "I used it on my POKéMON right away!$"

VeilstoneCity_EventScript_PtNpc4::
	msgbox VeilstoneCity_Text_PtNpc4, MSGBOX_NPC
	end

VeilstoneCity_Text_PtNpc4::
	.string "I came to this city just so I could go\n"
	.string "shopping at the department store.\p"
	.string "But with all these rock walls around,\n"
	.string "this place feels kind of cold.$"

VeilstoneCity_EventScript_PtNpc5::
	msgbox VeilstoneCity_Text_PtNpc5, MSGBOX_NPC
	end

VeilstoneCity_Text_PtNpc5::
	.string "I bought a new parasol.\p"
	.string "But I don't want it to get rained on,\n"
	.string "so I watch the TV weather reports.$"

VeilstoneCity_EventScript_PtNpc6::
	msgbox VeilstoneCity_Text_PtNpc6, MSGBOX_NPC
	end

VeilstoneCity_Text_PtNpc6::
	.string "MAYLENE is VEILSTONE's Gym Leader.\n"
	.string "Then, there's Wake in PASTORIA...\p"
	.string "They're way too tough for me. I can't\n"
	.string "even come close to them.$"

VeilstoneCity_EventScript_PtNpc7::
	msgbox VeilstoneCity_Text_PtNpc7, MSGBOX_NPC
	end

VeilstoneCity_Text_PtNpc7::
	.string "Do you know where one might find a\n"
	.string "Coin Case?\p"
	.string "I heard that there's a clown giving 'em\n"
	.string "away, but...$"

VeilstoneCity_EventScript_PtNpc8::
	msgbox VeilstoneCity_Text_PtNpc8, MSGBOX_NPC
	end

VeilstoneCity_Text_PtNpc8::
	.string "A man spoke to me in a foreign\n"
	.string "language. He really surprised me!\p"
	.string "I think he was asking if I liked\n"
	.string "POKéMON or something.$"

VeilstoneCity_EventScript_PtNpc9::
	lock
	faceplayer
	msgbox VeilstoneCity_Text_PtNpc9, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, VeilstoneCity_EventScript_PtNpc9_No
	msgbox VeilstoneCity_Text_PtNpc9_Yes, MSGBOX_DEFAULT
	release
	end

VeilstoneCity_Text_PtNpc9_Yes::
	.string "Moi aussi! C'est génial!$"

VeilstoneCity_EventScript_PtNpc9_No::
	msgbox VeilstoneCity_Text_PtNpc9_No, MSGBOX_DEFAULT
	release
	end

VeilstoneCity_Text_PtNpc9_No::
	.string "J'ai du mal à te croire... Il n'y a qu'à\n"
	.string "vous regarder!$"

VeilstoneCity_Text_PtNpc9::
	.string "Salut, Trainer! Tu aimes les POKéMON?$"

VeilstoneCity_EventScript_PtNpc10::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_SN_VEILSTONE_CITY_TM63, VeilstoneCity_EventScript_PtNpc10_EmbargoMakesItemsUnusable
	msgbox VeilstoneCity_Text_PtNpc10_0, MSGBOX_DEFAULT
	giveitem ITEM_TM63, 1
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_SN_VEILSTONE_CITY_TM63
	goto VeilstoneCity_EventScript_PtNpc10_EmbargoMakesItemsUnusable

VeilstoneCity_EventScript_PtNpc10_EmbargoMakesItemsUnusable::
	msgbox VeilstoneCity_Text_PtNpc10_1, MSGBOX_DEFAULT
	release
	end

VeilstoneCity_Text_PtNpc10_1::
	.string "If someone uses Embargo on your\n"
	.string "POKéMON, it becomes impossible to\p"
	.string "use any items on it.\p"
	.string "Anyway, enjoy your visit to Veilstone,\n"
	.string "the city of...well, stone.$"

VeilstoneCity_Text_PtNpc10_0::
	.string "Veilstone is the city of stone. We even\n"
	.string "have meteorites!\p"
	.string "This has nothing to do with anything,\n"
	.string "but take this Technical Machine!$"

VeilstoneCity_EventScript_SNGymCP::
	lock
	faceplayer
	checkplayergender
	goto_if_eq VAR_RESULT, FEMALE, VeilstoneCity_EventScript_SNGymCP_A_L
	msgbox VeilstoneCity_EventScript_SNGymCP_A_D, MSGBOX_DEFAULT
	goto VeilstoneCity_EventScript_SNGymCP_A_N

VeilstoneCity_EventScript_SNGymCP_A_N::
	checkplayergender
	goto_if_eq VAR_RESULT, FEMALE, VeilstoneCity_EventScript_SNGymCP_B_L
	msgbox VeilstoneCity_EventScript_SNGymCP_B_D, MSGBOX_DEFAULT
	goto VeilstoneCity_EventScript_SNGymCP_B_N

VeilstoneCity_EventScript_SNGymCP_B_N::
	release
	end

VeilstoneCity_EventScript_SNGymCP_B_D::
	.string "So, uh, {PLAYER}. Good luck on your Gym\n"
	.string "challenge.$"

VeilstoneCity_EventScript_SNGymCP_B_L::
	msgbox VeilstoneCity_EventScript_SNGymCP_B_Lu, MSGBOX_DEFAULT
	goto VeilstoneCity_EventScript_SNGymCP_B_N

VeilstoneCity_EventScript_SNGymCP_B_Lu::
	.string "So, uh, yeah, {PLAYER}. Good luck with\n"
	.string "the POKéMON Gym.$"

VeilstoneCity_EventScript_SNGymCP_A_D::
	.string "Dawn: {PLAYER}, are you going to take\n"
	.string "the Gym challenge?\p"
	.string "Gee, you keep getting tougher and\n"
	.string "tougher, don’t you?\p"
	.string "Me? Well, I went shopping at the\n"
	.string "department store, and...\p"
	.string "I mean, well, of course I’ve been\n"
	.string "working on my POKéDEX, but...$"

VeilstoneCity_EventScript_SNGymCP_A_L::
	msgbox VeilstoneCity_EventScript_SNGymCP_A_Lu, MSGBOX_DEFAULT
	goto VeilstoneCity_EventScript_SNGymCP_A_N

VeilstoneCity_EventScript_SNGymCP_A_Lu::
	.string "Lucas: Hey! {PLAYER}, are you going to\n"
	.string "take on the Gym Leader?\p"
	.string "Wow, you just keep getting tougher and\n"
	.string "tougher.\p"
	.string "Me? Well, I took a look in the Game\n"
	.string "Corner, and...\p"
	.string "I mean, yeah, of course I’ve been\n"
	.string "working on my POKéDEX, but...\p"
	.string "Anyway, keep it up!$"

VeilstoneCity_EventScript_SNGymWake::
	lock
	faceplayer
	msgbox VeilstoneCity_EventScript_SNGymWake_T1, MSGBOX_DEFAULT
	msgbox VeilstoneCity_EventScript_SNGymWake_T2, MSGBOX_DEFAULT
	msgbox VeilstoneCity_EventScript_SNGymWake_T3, MSGBOX_DEFAULT
	release
	end

VeilstoneCity_EventScript_SNGymWake_T3::
	.string "Whoops! I’d better tell you who I am!\p"
	.string "I’m the triple-threat Gym Leader in\n"
	.string "POKéMON, wrestling, and song.\p"
	.string "I’m Crasher Wake of Pastoria Gym! We’ll\n"
	.string "meet again!$"

VeilstoneCity_EventScript_SNGymWake_T2::
	.string "Hello, dude and young lady! You’re\n"
	.string "challenging the Gym Leader,\p"
	.string "are you?\p"
	.string "Let me tell you now, she’s young, but\n"
	.string "she’s a born genius.\p"
	.string "I tried training with her, and I was\n"
	.string "stunned by how tough she was!$"

VeilstoneCity_EventScript_SNGymWake_T1::
	.string "The ring is my roiling sea.\n"
	.string "The towering waves shaped me.\p"
	.string "Crash! Crash! Crasher Wake! Crash!\n"
	.string "Crash! Crasher Wake!\p"
	.string "I’m the tidal wave of power to wash you\n"
	.string "away!\p"
	.string "Put out the fire, Crasher Wake! Run\n"
	.string "from electricity, Crasher Wake!\p"
	.string "Ah, ah, aaaah! The ring is my sea.$"

VeilstoneCity_EventScript_SNWHGrunt0::
	msgbox VeilstoneCity_EventScript_SNWHGrunt0_T, MSGBOX_NPC
	end

VeilstoneCity_EventScript_SNWHGrunt0_T::
	.string "Grunt 1: Hey, you! Yeah, you!\p"
	.string "This is Team Galactic’s warehouse! It\n"
	.string "ain’t no playground for kids!$"

VeilstoneCity_EventScript_SNWHGrunt1::
	msgbox VeilstoneCity_EventScript_SNWHGrunt1_T, MSGBOX_NPC
	end

VeilstoneCity_EventScript_SNWHGrunt1_T::
	.string "Grunt 2: This is the awesome Team\n"
	.string "Galactic’s awesome warehouse!\p"
	.string "A little kid like you should be playing\n"
	.string "at the POKéMON Gym.\p"
	.string "After all, the Gym Leader happens to be\n"
	.string "a kid just like you!$"

VeilstoneCity_EventScript_SNWHCP_Ask_D::
	.string "Dawn: Hi, {PLAYER}! Please, can you help\n"
	.string "me?\p"
	.string "Do you remember Team Galactic? Those\n"
	.string "horrible people?\p"
	.string "They tried to steal Prof. Rowan’s\n"
	.string "research results in Jubilife, remember?\p"
	.string "I ran into them, and they took away my\n"
	.string "POKéDEX.\p"
	.string "Please, I need your help. Team up and\n"
	.string "battle with me!$"

SE_S_VeilstoneCity_VeilstoneCity_EventScript_SNWHCP::
	msgbox VeilstoneCity_EventScript_SNWHCP_Ask_D, MSGBOX_NPC
	end

VeilstoneCity_EventScript_SNWHLookerTalk::
	msgbox VeilstoneCity_EventScript_SNWHCP_L3, MSGBOX_NPC
	end

VeilstoneCity_EventScript_SNWHCP_L3::
	.string "Looker: It is of no matter.\p"
	.string "Of more interest is the criminal\n"
	.string "behavior of the Team Galactic.\p"
	.string "They attempt to steal the belongings\n"
	.string "of a child?\p"
	.string "The scale of their criminality, it seems\n"
	.string "rather minuscule.\p"
	.string "The triviality of their action makes\n"
	.string "them more sinister, perhaps.\p"
	.string "Their warehouse needs investigation.\n"
	.string "Come with me, and we’ll take a look!$"

VeilstoneCity_EventScript_SNKeyGrunt_T::
	.string "Hey! It’s you!\p"
	.string "I bet you don’t remember me, but I sure\n"
	.string "remember you!\p"
	.string "Because of you, they took my CLEFAIRY\n"
	.string "away...\p"
	.string "My partner called it quits and went\n"
	.string "back to his old country...\p"
	.string "Waah! I know nothing! I don’t know\n"
	.string "anything about any Storage Key!$"

SE_S_VeilstoneCity_VeilstoneCity_EventScript_SNKeyGrunt::
	msgbox VeilstoneCity_EventScript_SNKeyGrunt_T, MSGBOX_NPC
	end

VeilstoneCity_EventScript_SNKeyGrunt_L1::
	.string "Ah-hah! You leave this to me!\p"
	.string "The Storage Key for entering the Team\n"
	.string "Galactic hideout, I have right here.\p"
	.string "A frontal assault, it is not possible.\n"
	.string "But we can enter their hideout.\p"
	.string "Well? Will you enter the hideout? You\n"
	.string "have your reasons, yes?$"

SE_S_VeilstoneCity_VeilstoneCity_EventScript_SNKeyGrunt_Looker::
	msgbox VeilstoneCity_EventScript_SNKeyGrunt_L1, MSGBOX_NPC
	end

VeilstoneCity_EventScript_PtSign1::
	msgbox VeilstoneCity_Text_PtSign1, MSGBOX_SIGN
	end

VeilstoneCity_Text_PtSign1::
	.string "VEILSTONE CITY Hewn from Rock$"

VeilstoneCity_EventScript_PtSign2::
	msgbox VeilstoneCity_Text_PtSign2, MSGBOX_SIGN
	end

VeilstoneCity_Text_PtSign2::
	.string "GALACTIC Warehouse NO TRESPASSING!$"

VeilstoneCity_EventScript_PtSign3::
	msgbox VeilstoneCity_Text_PtSign3, MSGBOX_SIGN
	end

VeilstoneCity_Text_PtSign3::
	.string "GALACTIC VEILSTONE Building We Dream\n"
	.string "of the Universe!$"

VeilstoneCity_EventScript_PtSign4::
	msgbox VeilstoneCity_Text_PtSign4, MSGBOX_SIGN
	end

VeilstoneCity_Text_PtSign4::
	.string "VEILSTONE Department Store A Shop\n"
	.string "Full of Dreams!$"

VeilstoneCity_EventScript_PtSign5::
	msgbox VeilstoneCity_Text_PtSign5, MSGBOX_SIGN
	end

VeilstoneCity_Text_PtSign5::
	.string "VEILSTONE CITY POKéMON Gym Leader:\n"
	.string "MAYLENE The Barefoot, Fighting\l"
	.string "Genius!$"

VeilstoneCity_EventScript_PtSign6::
	msgbox VeilstoneCity_Text_PtSign6, MSGBOX_SIGN
	end

VeilstoneCity_Text_PtSign6::
	.string "VEILSTONE Game Corner Aim for an\n"
	.string "Explosion of Luck!$"

VeilstoneCity_EventScript_PtSign7::
	msgbox VeilstoneCity_Text_PtSign7, MSGBOX_SIGN
	end

VeilstoneCity_Text_PtSign7::
	.string "Prize Exchange Coins Exchanged for\n"
	.string "Prizes!$"

VeilstoneCity_EventScript_PtSign8::
	msgbox VeilstoneCity_Text_PtSign8, MSGBOX_SIGN
	end

VeilstoneCity_Text_PtSign8::
	.string "Visit Beautiful LAKE VALOR! Right off\n"
	.string "Rt. 214!$"
