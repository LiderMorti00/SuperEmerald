SnowpointCity_Gym_1F_sinnoh_MapScripts::
	.byte 0

@ Super Emerald: the three ice rooms are sliding ice (MB_ICE) with snow mounds as stoppers;
@ see tools/sfr/gyms/snowpoint.py. No scripts are needed: nothing breaks and nothing locks.

SnowpointCity_Gym_1F_EventScript_Leader::
	goto_if_set FLAG_SYS_GAME_CLEAR, SnowpointCity_Gym_1F_EventScript_SNRematch
	trainerbattle_single TRAINER_KAREN_5_SINNOH, SnowpointCity_Gym_1F_Text_LeaderIntro, SnowpointCity_Gym_1F_Text_LeaderDefeat, SnowpointCity_Gym_1F_EventScript_LeaderDefeated, NO_MUSIC
	goto_if_unset FLAG_RECEIVED_ITEM_TM72_FROM_CANDICE, SnowpointCity_Gym_1F_EventScript_GiveTM
	msgbox SnowpointCity_Gym_1F_Text_LeaderPostBattle, MSGBOX_DEFAULT
	release
	end

SnowpointCity_Gym_1F_Text_LeaderPostBattle::
	.string "Do you think I should try to act more\n"
	.string "like an Ice-type GYM LEADER?\p"
	.string "Like, do you think I should be more cool\n"
	.string "and distant?\p"
	.string "That sort of thing I have trouble with.$"

SnowpointCity_Gym_1F_EventScript_GiveTM::
	giveitem ITEM_TM72
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_ITEM_TM72_FROM_CANDICE
	msgbox SnowpointCity_Gym_1F_Text_ExplainTM, MSGBOX_DEFAULT
	release
	end

SnowpointCity_Gym_1F_Text_ExplainTM::
	.string "TM72 contains the move AVALANCHE.\p"
	.string "If the user takes damage, the move's\n"
	.string "power is doubled!\p"
	.string "Can you imagine what sort of focus\n"
	.string "you'd need to pull it off?$"

SnowpointCity_Gym_1F_EventScript_LeaderDefeated::
	setflag FLAG_SN_DEFEATED_SOOTOPOLIS_GYM
	message SnowpointCity_Gym_1F_Text_ReceivedBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox SnowpointCity_Gym_1F_Text_ExplainBadge, MSGBOX_DEFAULT
	setflag FLAG_SINNOH_BADGE7_GET
	settrainerflag TRAINER_ANNA_AND_MEG_1_SINNOH
	settrainerflag TRAINER_ANNA_AND_MEG_2_SINNOH
	settrainerflag TRAINER_ANNA_AND_MEG_3_SINNOH
	settrainerflag TRAINER_ANNA_AND_MEG_4_SINNOH
	settrainerflag TRAINER_ANNA_AND_MEG_5_SINNOH
	settrainerflag TRAINER_MIGUEL_1_SINNOH
	goto SnowpointCity_Gym_1F_EventScript_GiveTM

SnowpointCity_Gym_1F_Text_ExplainBadge::
	.string "That Icicle BADGE I just gave you?\p"
	.string "Because you have it, you can use the\n"
	.string "hidden move ROCK CLIMB anytime, even\p"
	.string "when you're not in a battle.\p"
	.string "Oh, and take this, too.$"

SnowpointCity_Gym_1F_Text_ReceivedBadge::
	.string "{PLAYER} received the Icicle BADGE\n"
	.string "from CANDICE.$"

SnowpointCity_Gym_1F_Text_LeaderDefeat::
	.string "Wow! You're great! You've earned my\n"
	.string "respect!\p"
	.string "I think your focus and will bowled us\n"
	.string "over totally.\p"
	.string "Oh, that's right! I'm supposed to give\n"
	.string "you this!$"

SnowpointCity_Gym_1F_Text_LeaderIntro::
	.string "You want to challenge CANDICE?\p"
	.string "Sure thing! I was waiting for someone\n"
	.string "tough!\p"
	.string "But I should tell you, I'm tough\n"
	.string "because I know how to focus.\p"
	.string "POKéMON, fashion, romance… It's all\n"
	.string "about focus!\p"
	.string "I'll show you just what I mean. Get\n"
	.string "ready to lose!$"

SnowpointCity_Gym_1F_EventScript_SNRematch::
	lock
	faceplayer
	msgbox SnowpointCity_Gym_1F_EventScript_SNRematch_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SnowpointCity_Gym_1F_EventScript_SNRematch_No
	msgbox SnowpointCity_Gym_1F_EventScript_SNRematch_Go, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_KATELYN_5_SINNOH, SnowpointCity_Gym_1F_EventScript_SNRematch_Defeat
	msgbox SnowpointCity_Gym_1F_EventScript_SNRematch_After, MSGBOX_DEFAULT
	release
	end

SnowpointCity_Gym_1F_EventScript_SNRematch_After::
	.string "That was a great battle! Come back\n"
	.string "anytime for another match!$"

SnowpointCity_Gym_1F_EventScript_SNRematch_Defeat::
	.string "Amazing… You really are the CHAMPION!$"

SnowpointCity_Gym_1F_EventScript_SNRematch_Go::
	.string "Then I won't hold back this time!$"

SnowpointCity_Gym_1F_EventScript_SNRematch_No::
	msgbox SnowpointCity_Gym_1F_EventScript_SNRematch_NoT, MSGBOX_DEFAULT
	release
	end

SnowpointCity_Gym_1F_EventScript_SNRematch_NoT::
	.string "Come back whenever you're ready!$"

SnowpointCity_Gym_1F_EventScript_SNRematch_Ask::
	.string "CANDICE: You became the CHAMPION!\n"
	.string "Welcome back!\p"
	.string "I've been training even harder since\n"
	.string "our last battle.\p"
	.string "Will you battle me again?$"

SnowpointCity_Gym_1F_EventScript_PtGymGuide::
	lock
	faceplayer
	goto_if_set FLAG_SINNOH_BADGE7_GET, SnowpointCity_Gym_1F_EventScript_PtGymGuideAfter
	msgbox SnowpointCity_Gym_1F_Text_PtGymGuide, MSGBOX_DEFAULT
	msgbox SnowpointCity_Gym_1F_Text_SNGuideInfo, MSGBOX_DEFAULT
	release
	end

SnowpointCity_Gym_1F_Text_SNGuideInfo::
	.string "Let me tell you about this GYM!\p"
	.string "The GYM LEADER is CANDICE, the Diamond\n"
	.string "Dust Girl, who is all about focus!\p"
	.string "She uses Ice-type POKéMON like\n"
	.string "SNEASEL, PILOSWINE, ABOMASNOW and\l"
	.string "FROSLASS.\p"
	.string "Ice types are weak to Fire, Fighting,\n"
	.string "Rock and Steel moves!\p"
	.string "The rooms are slippery ice. Once you\n"
	.string "start sliding, only a snow mound or a\l"
	.string "wall will stop you.\p"
	.string "The small room is for practice. If you\n"
	.string "slide wrong, head back to the patch of\l"
	.string "snow by the stairs and try again.\p"
	.string "Her TRAINERS train in the basement.\n"
	.string "Take the ladder over there!$"

SnowpointCity_Gym_1F_Text_PtGymGuide::
	.string "Hey there, CHAMPION!\p"
	.string "I'm the GYM guide! I help out TRAINERS\n"
	.string "who come to challenge the GYM LEADER.$"

SnowpointCity_Gym_1F_EventScript_PtGymGuideAfter::
	msgbox SnowpointCity_Gym_1F_Text_PtGymGuideAfter, MSGBOX_DEFAULT
	release
	end

SnowpointCity_Gym_1F_Text_PtGymGuideAfter::
	.string "Oh! {PLAYER}! You've beaten the GYM\n"
	.string "LEADER!\p"
	.string "You were more focused than her, and\n"
	.string "your POKéMON picked up on it!$"

SnowpointCity_Gym_1F_EventScript_PtGymStatue::
	lockall
	goto_if_set FLAG_SINNOH_BADGE7_GET, SnowpointCity_Gym_1F_EventScript_PtGymStatueWon
	msgbox SnowpointCity_Gym_1F_Text_PtGymStatue, MSGBOX_DEFAULT
	releaseall
	end

SnowpointCity_Gym_1F_Text_PtGymStatue::
	.string "SNOWPOINT CITY POKéMON GYM\n"
	.string "LEADER: CANDICE$"

SnowpointCity_Gym_1F_EventScript_PtGymStatueWon::
	msgbox SnowpointCity_Gym_1F_Text_PtGymStatueWon, MSGBOX_DEFAULT
	releaseall
	end

SnowpointCity_Gym_1F_Text_PtGymStatueWon::
	.string "SNOWPOINT CITY POKéMON GYM\n"
	.string "LEADER: CANDICE\p"
	.string "Certified TRAINERS:\n"
	.string "{PLAYER}$"
