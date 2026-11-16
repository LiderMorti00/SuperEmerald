SlowpokeWell_B1F_hns_MapScripts::
	.byte 0


SlowpokeWell_B1F_EventScript_Kurt::
	lock
	msgbox SlowpokeWell_B1F_Text_KurtIntro, MSGBOX_DEFAULT
	closemessage
	end

SlowpokeWell_B1F_Text_KurtIntro::
	.string "KURT: Hey there, {PLAYER}!\p"
	.string "The guard up top took off when\n"
	.string "I shouted at him.\p"
	.string "But then I took a tumble down\n"
	.string "the WELL.\p"
	.string "I slammed down hard on my back,\n"
	.string "so I can't move.\p"
	.string "Rats! If I were fit, my POKéMON\n"
	.string "would've punished them…\p"
	.string "Ah, it can't be helped.\p"
	.string "{PLAYER}, show them how gutsy\n"
	.string "you are in my place!$"

SlowpokeWell_B1F_EventScript_Grunt21::
	trainerbattle_single TRAINER_GRUNT_21_HNS, SlowpokeWell_B1F_Text_GruntM29Seen, SlowpokeWell_B1F_Text_GruntM29Beaten
	msgbox SlowpokeWell_B1F_Text_GruntM29After, MSGBOX_AUTOCLOSE
	end

SlowpokeWell_B1F_Text_GruntM29After::
	.string "Sure, we've been hacking the\n"
	.string "tails off SLOWPOKE and selling\l"
	.string "them.\p"
	.string "Everything we do is for profit.\p"
	.string "That's right! We're TEAM ROCKET,\n"
	.string "and we'll do anything for money!$"

SlowpokeWell_B1F_Text_GruntM29Beaten::
	.string "Arrgh! This is NOT my day!$"

SlowpokeWell_B1F_Text_GruntM29Seen::
	.string "Darn! I was standing guard up\n"
	.string "top when some old coot yelled\l"
	.string "at me.\p"
	.string "He startled me so much that\n"
	.string "I fell down here.\p"
	.string "I think I'll vent my anger by\n"
	.string "taking it out on you!$"

SlowpokeWell_B1F_EventScript_Grunt22F::
	trainerbattle_single TRAINER_GRUNT_22_HNS, SlowpokeWell_B1F_Text_GruntF1Seen, SlowpokeWell_B1F_Text_GruntF1Beaten
	msgbox SlowpokeWell_B1F_Text_GruntF1After, MSGBOX_AUTOCLOSE
	end

SlowpokeWell_B1F_Text_GruntF1After::
	.string "SLOWPOKETAILS grow back fast!\p"
	.string "What's wrong with selling them?$"

SlowpokeWell_B1F_Text_GruntF1Beaten::
	.string "You rotten brat!$"

SlowpokeWell_B1F_Text_GruntF1Seen::
	.string "Stop taking TAILS?\p"
	.string "Yeah, just try to defeat all\n"
	.string "of us!$"

SlowpokeWell_B1F_Text_ProtonSeen::
	.string "What do you want?\p"
	.string "If you interrupt our work,\n"
	.string "don't expect any mercy!$"

SE_J_SlowpokeWell_B1F_hns_SlowpokeWell_B1F_EventScript_Proton::
	msgbox SlowpokeWell_B1F_Text_ProtonSeen, MSGBOX_NPC
	end

SlowpokeWell_B1F_EventScript_Eto::
	trainerbattle_single TRAINER_ETO_HNS, SlowpokeWell_B1F_Text_GruntM2Seen, SlowpokeWell_B1F_Text_GruntM2Beaten
	msgbox SlowpokeWell_B1F_Text_GruntM2After, MSGBOX_AUTOCLOSE
	end

SlowpokeWell_B1F_Text_GruntM2After::
	.string "We need the money,\n"
	.string "but selling SLOWPOKETAILS?\p"
	.string "It's tough being a ROCKET GRUNT!$"

SlowpokeWell_B1F_Text_GruntM2Beaten::
	.string "Hyuck…\n"
	.string "Too strong…$"

SlowpokeWell_B1F_Text_GruntM2Seen::
	.string "Hyuck-hyuck-hyuck!\n"
	.string "Quit taking SLOWPOKETAILS?\p"
	.string "You're nuts!\n"
	.string "If we obeyed you, TEAM ROCKET's\l"
	.string "rep would be ruined!$"

SlowpokeWell_B1F_EventScript_Item_Super_Potion_1::
	finditem ITEM_SUPER_POTION
	end

SlowpokeWell_B1F_EventScript_Item_Super_Potion_2::
	finditem ITEM_SUPER_POTION
	end

SlowpokeWell_B1F_EventScript_Item_Great_Ball::
	finditem ITEM_GREAT_BALL
	end

SlowpokeWell_B1F_EventScript_Item_Full_Heal::
	finditem ITEM_FULL_HEAL
	end
