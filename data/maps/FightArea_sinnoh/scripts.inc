FightArea_sinnoh_MapScripts::
	.byte 0


FightArea_EventScript_PtNpc1::
	msgbox FightArea_Text_PtNpc1, MSGBOX_NPC
	end

FightArea_Text_PtNpc1::
	.string "Whenever I go to a new place, I get\n"
	.string "excited over what I might discover.\p"
	.string "But places I've visited before...\p"
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
	.string "The way the Battle Tower looms...\p"
	.string "It really is a wall that stands before\n"
	.string "every Trainer.$"

FightArea_EventScript_PtNpc4::
	msgbox FightArea_Text_PtNpc4, MSGBOX_NPC
	end

FightArea_Text_PtNpc4::
	.string "I've battled many Trainers over the\n"
	.string "years.\p"
	.string "I've gained some confidence in my\n"
	.string "skill levels, too.\p"
	.string "But the world is still a huge place.\n"
	.string "It's not easy to win in life!$"

FightArea_EventScript_PtNpc5::
	msgbox FightArea_Text_PtNpc5, MSGBOX_NPC
	end

FightArea_Text_PtNpc5::
	.string "The POKéMON LEAGUE's Elite Four come\n"
	.string "here sometimes!$"

FightArea_EventScript_PtNpc6::
	msgbox FightArea_Text_PtNpc6, MSGBOX_NPC
	end

FightArea_Text_PtNpc6::
	.string "Your POKéMON are from SINNOH, aren't\n"
	.string "they?\p"
	.string "They're not what we're used to seeing\n"
	.string "around here.$"

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

FightArea_EventScript_SNMulti_B1::
	.string "BARRY: Oh, hey, {PLAYER}! What took you\n"
	.string "so long?\p"
	.string "I’m fining you $100 million!\p"
	.string "Actually, never mind the fine. Come\n"
	.string "with me, will ya?$"

SE_S_FightArea_FightArea_EventScript_SNMulti::
	msgbox FightArea_EventScript_SNMulti_B1, MSGBOX_NPC
	end

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
	.string "Hmm! A Super Rod is really good!\p"
	.string "Wouldn’t you agree?$"

FightArea_EventScript_SNFisher_After::
	.string "What’s that? Any advice for fishing?\p"
	.string "Well, I’ll tell you. It’s all about the\n"
	.string "rod and technique!$"

FightArea_EventScript_SNMulti_Palmer::
	msgbox FightArea_EventScript_SNMulti_P2T, MSGBOX_NPC
	end

FightArea_EventScript_SNMulti_P2T::
	.string "BARRY, your mother told me you’d gone\n"
	.string "off to the Battle Zone.\p"
	.string "So I had to come running looking for\n"
	.string "you.\p"
	.string "So, are you two going to take the\n"
	.string "Battle Frontier challenge?\p"
	.string "The Frontier has five facilities that\n"
	.string "are all dedicated to battling.\p"
	.string "Each one has a unique set of rules, so\n"
	.string "they’re all different.\p"
	.string "Of course, you have to be good to win\n"
	.string "at any of them.\p"
	.string "Anyway, I’m satisfied to see that\n"
	.string "you’re both doing well.\p"
	.string "I’ll go back to my usual place in the\n"
	.string "Battle Tower.\p"
	.string "I’ll be looking forward to your\n"
	.string "challenge.$"

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
	.string "You’re something special, aren’t you?\n"
	.string "Beating an Elite Four like that.\p"
	.string "Oh, right, howdy. The name’s Buck.\p"
	.string "I’m usually training at the Survival\n"
	.string "Area or Stark Mountain.\p"
	.string "You should come up there. You’ll get\n"
	.string "toughened up for sure!$"
