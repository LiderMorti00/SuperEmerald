FightArea_sinnoh_MapScripts::
	.byte 0


FightArea_EventScript_PtNpc1::
	msgbox FightArea_Text_PtNpc1, MSGBOX_NPC
	end

FightArea_Text_PtNpc1::
	.string "Whenever I go to a new place, I get\n"
	.string "excited over what I might discover.\p"
	.string "But places I've visited before…\p"
	.string "Even those places thrill me with new\n"
	.string "discoveries!$"

FightArea_EventScript_PtNpc2::
	msgbox FightArea_Text_PtNpc2, MSGBOX_NPC
	end

FightArea_Text_PtNpc2::
	.string "Because of the volcano, the land\n"
	.string "around here is craggy.\p"
	.string "The rough terrain and all the ups and\n"
	.string "downs make it hard to hike.$"

FightArea_EventScript_PtNpc3::
	msgbox FightArea_Text_PtNpc3, MSGBOX_NPC
	end

FightArea_Text_PtNpc3::
	.string "The way the BATTLE TOWER looms…\p"
	.string "It really is a wall that stands before\n"
	.string "every TRAINER.$"

FightArea_EventScript_PtNpc4::
	msgbox FightArea_Text_PtNpc4, MSGBOX_NPC
	end

FightArea_Text_PtNpc4::
	.string "I've battled many TRAINERS over the\n"
	.string "years.\p"
	.string "I've gained some confidence in my\n"
	.string "skill levels, too.\p"
	.string "But the world is still a huge place.\n"
	.string "It's not easy to win in life!$"

FightArea_EventScript_PtNpc5::
	msgbox FightArea_Text_PtNpc5, MSGBOX_NPC
	end

FightArea_Text_PtNpc5::
	.string "The POKéMON LEAGUE's ELITE FOUR come\n"
	.string "here sometimes!$"

FightArea_EventScript_PtNpc6::
	msgbox FightArea_Text_PtNpc6, MSGBOX_NPC
	end

FightArea_Text_PtNpc6::
	.string "I like watching TRAINERS step off\n"
	.string "the ferry with their POKéMON.\p"
	.string "Yesterday I saw a species I'd only\n"
	.string "ever seen in a book!$"

FightArea_EventScript_PtNpc7::
	lock
	faceplayer
	msgbox FightArea_Text_PtNpc7, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FightArea_EventScript_PtNpc7_No
	msgbox FightArea_Text_PtNpc7_Yes, MSGBOX_DEFAULT
	closemessage
	warp MAP_SNOWPOINT_CITY_SINNOH, 5, 57
	waitstate
	release
	end

FightArea_Text_PtNpc7_Yes::
	.string "Aye, right! It's anchors aweigh, then!$"

FightArea_EventScript_PtNpc7_No::
	msgbox FightArea_Text_PtNpc7_No, MSGBOX_DEFAULT
	release
	end

FightArea_Text_PtNpc7_No::
	.string "Oh, right. You'd rather just fly\n"
	.string "everywhere in some big hurry.$"

FightArea_Text_PtNpc7::
	.string "What's up? Do you want to sail to\n"
	.string "SNOWPOINT CITY?$"

FightArea_EventScript_PtNpc8::
	msgbox FightArea_Text_PtNpc8, MSGBOX_NPC
	end

FightArea_Text_PtNpc8::
	.string "There's no end to becoming tough!\p"
	.string "I just made that up, but it sounds\n"
	.string "kind of cool, huh?$"

FightArea_EventScript_SNMulti::
	lock
	faceplayer
	msgbox FightArea_EventScript_SNMulti_B1, MSGBOX_DEFAULT
	msgbox FightArea_EventScript_SNMulti_B2, MSGBOX_DEFAULT
	msgbox FightArea_EventScript_SNMulti_F1, MSGBOX_DEFAULT
	msgbox FightArea_EventScript_SNMulti_V1, MSGBOX_DEFAULT
	msgbox FightArea_EventScript_SNMulti_B3, MSGBOX_DEFAULT
	msgbox FightArea_EventScript_SNMulti_F2, MSGBOX_DEFAULT
	msgbox FightArea_EventScript_SNMulti_V2, MSGBOX_DEFAULT
	msgbox FightArea_EventScript_SNMulti_B4, MSGBOX_DEFAULT
	closemessage
	switch VAR_SN_STARTER_MON
	case 1, FightArea_EventScript_SNMulti_P1
	case 2, FightArea_EventScript_SNMulti_P2
	setfollowernpc LOCALID_SN_FIGHTAREA_BARRY, FNPC_ALL_LAND, 0, PARTNER_BARRY_CHIMCHAR
	goto FightArea_EventScript_SNMulti_Battle

FightArea_EventScript_SNMulti_Battle::
	trainerbattle_two_trainers_sn TRAINER_ANGELINA_SINNOH, FightArea_EventScript_SNMulti_DF, TRAINER_KAI_SINNOH, FightArea_EventScript_SNMulti_DV
	destroyfollowernpc
	setobjectxyperm LOCALID_SN_FIGHTAREA_BARRY, 49, 10
	clearflag FLAG_SN_HIDE_FA_MULTI
	addobject LOCALID_SN_FIGHTAREA_BARRY
	msgbox FightArea_EventScript_SNMulti_F3, MSGBOX_DEFAULT
	msgbox FightArea_EventScript_SNMulti_V3, MSGBOX_DEFAULT
	msgbox FightArea_EventScript_SNMulti_V4, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_SN_FA_FLINT
	removeobject LOCALID_SN_FA_VOLKNER
	fadescreen FADE_FROM_BLACK
	msgbox FightArea_EventScript_SNMulti_B5, MSGBOX_DEFAULT
	closemessage
	playse SE_BANG
	clearflag FLAG_SN_HIDE_FA_PALMER
	addobject LOCALID_SN_FA_PALMER
	msgbox FightArea_EventScript_SNMulti_Thud, MSGBOX_DEFAULT
	msgbox FightArea_EventScript_SNMulti_P0, MSGBOX_DEFAULT
	msgbox FightArea_EventScript_SNMulti_B6, MSGBOX_DEFAULT
	msgbox FightArea_EventScript_SNMulti_P1T, MSGBOX_DEFAULT
	msgbox FightArea_EventScript_SNMulti_P2T, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_SN_FA_PALMER
	setflag FLAG_SN_HIDE_FA_PALMER
	fadescreen FADE_FROM_BLACK
	msgbox FightArea_EventScript_SNMulti_B7, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_SN_FIGHT_MULTI_DONE
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_SN_FIGHTAREA_BARRY
	setflag FLAG_SN_HIDE_FA_MULTI
	clearflag FLAG_SN_HIDE_FA_BUCK
	addobject LOCALID_SN_FA_BUCK
	fadescreen FADE_FROM_BLACK
	release
	end

FightArea_EventScript_SNMulti_B7::
	.string "BARRY: My dad is cool, huh? I mean, when\n"
	.string "it gets right down to it.\p"
	.string "You think so too, right?\p"
	.string "He's a Frontier Brain, after all. He's\n"
	.string "the Tower Tycoon!\p"
	.string "I want to be cool like my dad!\p"
	.string "{PLAYER}, that's the one reason I\n"
	.string "decided to become a TRAINER!$"

FightArea_EventScript_SNMulti_P2T::
	.string "BARRY, your mother told me you'd gone\n"
	.string "off to the BATTLE ZONE.\p"
	.string "So I had to come running looking for\n"
	.string "you.\p"
	.string "So, are you two going to take the\n"
	.string "BATTLE FRONTIER challenge?\p"
	.string "The Frontier has five facilities that\n"
	.string "are all dedicated to battling.\p"
	.string "Each one has a unique set of rules, so\n"
	.string "they're all different.\p"
	.string "Of course, you have to be good to win\n"
	.string "at any of them.\p"
	.string "Anyway, I'm satisfied to see that\n"
	.string "you're both doing well.\p"
	.string "I'll go back to my usual place in the\n"
	.string "BATTLE TOWER.\p"
	.string "I'll be looking forward to your\n"
	.string "challenge.$"

FightArea_EventScript_SNMulti_P1T::
	.string "PALMER: Huh? Ah!\p"
	.string "If it isn't BARRY! You've grown all\n"
	.string "sturdy!\p"
	.string "And {PLAYER}, too! I haven't seen you in\n"
	.string "a long time, either!$"

FightArea_EventScript_SNMulti_B6::
	.string "BARRY: What the…\p"
	.string "…Daddy?!$"

FightArea_EventScript_SNMulti_P0::
	.string "What's this all about?!$"

FightArea_EventScript_SNMulti_Thud::
	.string "Thud!!$"

FightArea_EventScript_SNMulti_B5::
	.string "BARRY: See? I got a lot tougher, yeah?\p"
	.string "OK, I'm off to the Fronti…$"

FightArea_EventScript_SNMulti_V4::
	.string "VOLKNER: Hahaha! That was a blast!\p"
	.string "Our combination came up short, but\n"
	.string "you're also a lot tougher as well.\p"
	.string "Promise me we'll do this again. I'll see\n"
	.string "to taking this husk home.$"

FightArea_EventScript_SNMulti_V3::
	.string "VOLKNER: Hey! Don't burn out on us! Now\n"
	.string "you're just getting in the way.$"

FightArea_EventScript_SNMulti_F3::
	.string "FLINT: … …\p"
	.string "… …\p"
	.string "… …$"

FightArea_EventScript_SNMulti_DV::
	.string "VOLKNER: Now that was electrifying!$"

FightArea_EventScript_SNMulti_DF::
	.string "FLINT: Burned out…$"

FightArea_EventScript_SNMulti_P2::
	setfollowernpc LOCALID_SN_FIGHTAREA_BARRY, FNPC_ALL_LAND, 0, PARTNER_BARRY_TURTWIG
	goto FightArea_EventScript_SNMulti_Battle

FightArea_EventScript_SNMulti_P1::
	setfollowernpc LOCALID_SN_FIGHTAREA_BARRY, FNPC_ALL_LAND, 0, PARTNER_BARRY_PIPLUP
	goto FightArea_EventScript_SNMulti_Battle

FightArea_EventScript_SNMulti_B4::
	.string "BARRY: Come on, let's show them how\n"
	.string "tough we really are!$"

FightArea_EventScript_SNMulti_V2::
	.string "VOLKNER: I don't know how I managed to\n"
	.string "get myself into this, but…\p"
	.string "Show me the skills that got you\n"
	.string "through the POKéMON LEAGUE!$"

FightArea_EventScript_SNMulti_F2::
	.string "FLINT: This situation just cooks! The\n"
	.string "drama and tension sizzles!\p"
	.string "FLINT, the fiery master of fire\n"
	.string "POKéMON, is going to put you to the\l"
	.string "test!\p"
	.string "Let FLINT see how hot your spirit\n"
	.string "burns!$"

FightArea_EventScript_SNMulti_B3::
	.string "BARRY: Yeah, that's what I'm talking\n"
	.string "about!\p"
	.string "So there's an ELITE FOUR and a GYM\n"
	.string "LEADER. We can whoop 'em!$"

FightArea_EventScript_SNMulti_V1::
	.string "VOLKNER: You only want to go into the\n"
	.string "Frontier, don't you?\p"
	.string "I'm sorry about my friend. He's off on\n"
	.string "his own thing…$"

FightArea_EventScript_SNMulti_F1::
	.string "FLINT: Yo, TRAINER! It's been too long,\n"
	.string "amigo!\p"
	.string "Now I don't know what your pal speedy\n"
	.string "there's been spouting…\p"
	.string "But we're not doing this out of spite\n"
	.string "or anything bad natured like that.\p"
	.string "The BATTLE FRONTIER behind us is where\n"
	.string "the best TRAINERS gather.\p"
	.string "We're being kind enough to let you see\n"
	.string "if you're up to the challenge!\p"
	.string "You really ought to be grateful!$"

FightArea_EventScript_SNMulti_B2::
	.string "BARRY: {PLAYER}, I tried to get into the\n"
	.string "BATTLE FRONTIER,\p"
	.string "which happens to be right here.\p"
	.string "Then these guys came along and got in\n"
	.string "my face about it.\p"
	.string "Like, they're saying they want to test\n"
	.string "me if I'm good enough and all that.\p"
	.string "Like, as if I need to prove anything.\n"
	.string "So, let's team up.\p"
	.string "Like we did at the SPEAR PILLAR. Let's\n"
	.string "show those guys how good we are!$"

FightArea_EventScript_SNMulti_B1::
	.string "BARRY: Oh, hey, {PLAYER}! What took you\n"
	.string "so long?\p"
	.string "I'm fining you $100 million!\p"
	.string "Actually, never mind the fine. Come\n"
	.string "with me, will ya?$"

FightArea_EventScript_SNFisher_Done::
	msgbox FightArea_EventScript_SNFisher_After, MSGBOX_DEFAULT
	release
	end

FightArea_EventScript_SNFisher::
	lock
	faceplayer
	goto_if_set FLAG_SN_RECEIVED_SUPER_ROD, FightArea_EventScript_SNFisher_Done
	msgbox FightArea_EventScript_SNFisher_Ask, MSGBOX_YESNO
	giveitem ITEM_SUPER_ROD
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SN_RECEIVED_SUPER_ROD
	goto FightArea_EventScript_SNFisher_Done

FightArea_EventScript_SNFisher_Ask::
	.string "Hmm! A SUPER ROD is really good!\p"
	.string "Wouldn't you agree?$"

FightArea_EventScript_SNFisher_After::
	.string "What's that? Any advice for fishing?\p"
	.string "Well, I'll tell you. It's all about the\n"
	.string "rod and technique!$"

FightArea_EventScript_SNMulti_Palmer::
	msgbox FightArea_EventScript_SNMulti_P2T, MSGBOX_NPC
	end

FightArea_EventScript_SNMulti_Buck::
	lock
	faceplayer
	msgbox FightArea_EventScript_SNMulti_K1, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_SN_FA_MET_BUCK
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_SN_FA_BUCK
	setflag FLAG_SN_HIDE_FA_BUCK
	fadescreen FADE_FROM_BLACK
	release
	end

FightArea_EventScript_SNMulti_K1::
	.string "Hey, hey. I just watched you two\n"
	.string "battle.\p"
	.string "You're something special, aren't you?\n"
	.string "Beating an ELITE FOUR like that.\p"
	.string "Oh, right, howdy. The name's BUCK.\p"
	.string "I'm usually training at the SURVIVAL\n"
	.string "AREA or STARK MOUNTAIN.\p"
	.string "You should come up there. You'll get\n"
	.string "toughened up for sure!$"
