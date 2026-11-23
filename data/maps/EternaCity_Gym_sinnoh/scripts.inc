EternaCity_Gym_sinnoh_MapScripts::
	.byte 0


EternaCity_Gym_EventScript_Caroline::
	trainerbattle_single TRAINER_VITO_SINNOH, EternaCity_Gym_Text_CarolineIntro, EternaCity_Gym_Text_CarolineDefeat
	msgbox EternaCity_Gym_Text_CarolinePost, MSGBOX_AUTOCLOSE
	end

EternaCity_Gym_Text_CarolinePost::
	.string "GARDENIA loves GRASS-type POKéMON\n"
	.string "more than anything.$"

EternaCity_Gym_Text_CarolineDefeat::
	.string "My petals fell…$"

EternaCity_Gym_Text_CarolineIntro::
	.string "Welcome! Without further ado, let's go!$"

EternaCity_Gym_EventScript_Jenna::
	trainerbattle_single TRAINER_OWEN_SINNOH, EternaCity_Gym_Text_JennaIntro, EternaCity_Gym_Text_JennaDefeat
	msgbox EternaCity_Gym_Text_JennaPost, MSGBOX_AUTOCLOSE
	end

EternaCity_Gym_Text_JennaPost::
	.string "FIRE and FLYING moves are strong\n"
	.string "against GRASS POKéMON.$"

EternaCity_Gym_Text_JennaDefeat::
	.string "Wilted…$"

EternaCity_Gym_Text_JennaIntro::
	.string "My Grass-type POKéMON can dole out\n"
	.string "some serious special attacks…\p"
	.string "I won't let you win…easily!$"

EternaCity_Gym_EventScript_Angela::
	trainerbattle_single TRAINER_WARREN_SINNOH, EternaCity_Gym_Text_AngelaIntro, EternaCity_Gym_Text_AngelaDefeat
	msgbox EternaCity_Gym_Text_AngelaPost, MSGBOX_AUTOCLOSE
	end

EternaCity_Gym_Text_AngelaPost::
	.string "GARDENIA's ROSERADE is her\n"
	.string "strongest POKéMON.$"

EternaCity_Gym_Text_AngelaDefeat::
	.string "You're really strong!$"

EternaCity_Gym_Text_AngelaIntro::
	.string "You can't win when you're distracted by\n"
	.string "the lovely aromas of POKéMON!$"

EternaCity_Gym_EventScript_Gardenia::
	goto_if_set FLAG_SYS_GAME_CLEAR, EternaCity_Gym_EventScript_SNRematch
	trainerbattle_single TRAINER_ALEXIA_SINNOH, EternaCity_Gym_Text_GardeniaIntro, EternaCity_Gym_Text_GardeniaDefeat, EternaCity_Gym_EventScript_GardeniaDefeated, NO_MUSIC
	goto_if_unset FLAG_SN_RECEIVED_TM_GIGA_DRAIN, EternaCity_Gym_EventScript_GiveTM
	msgbox EternaCity_Gym_Text_GardeniaPost, MSGBOX_DEFAULT
	release
	end

EternaCity_Gym_Text_GardeniaPost::
	.string "Yup! If there's one thing I can tell\n"
	.string "about you, it's this!\p"
	.string "You and your POKéMON are gonna get\n"
	.string "even tougher, and I mean seriously!$"

EternaCity_Gym_EventScript_GiveTM::
	msgbox EternaCity_Gym_Text_GiveTM, MSGBOX_DEFAULT
	giveitem ITEM_TM86
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SN_RECEIVED_TM_GIGA_DRAIN
	msgbox EternaCity_Gym_Text_TMInfo, MSGBOX_DEFAULT
	release
	end

EternaCity_Gym_Text_TMInfo::
	.string "That TM86 contains the move GRASS\n"
	.string "KNOT.\p"
	.string "It's one of my favorite moves.\p"
	.string "The heavier the foe, the more damage\n"
	.string "this move will cause.$"

EternaCity_Gym_Text_GiveTM::
	.string "With the Forest BADGE, your POKéMON\n"
	.string "can use the hidden move CUT outside\p"
	.string "of battle.\p"
	.string "I've also got something else. It's a\n"
	.string "gift from me!$"

EternaCity_Gym_EventScript_GardeniaDefeated::
	message EternaCity_Gym_Text_ReceivedBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_SINNOH_BADGE2_GET
	setvar VAR_SN_SINNOH_STORY, 27
	goto EternaCity_Gym_EventScript_GiveTM
	end

EternaCity_Gym_Text_ReceivedBadge::
	.string "{PLAYER} received the Forest BADGE\n"
	.string "from GARDENIA!$"

EternaCity_Gym_Text_GardeniaDefeat::
	.string "I might've said it before, but you're\n"
	.string "really tough!\p"
	.string "Wasn't it hard for you to raise your\n"
	.string "POKéMON to be so good?\p"
	.string "I guess that's a measure of how much\n"
	.string "you love your POKéMON.\p"
	.string "In recognition of that, I proudly grant\n"
	.string "you this!$"

EternaCity_Gym_Text_GardeniaIntro::
	.string "You kept me waiting!\p"
	.string "I'm ETERNA's GYM LEADER, GARDENIA, the\n"
	.string "Grass-type master!\p"
	.string "When I first saw you, I was convinced\n"
	.string "you'd find your way to me.\p"
	.string "My hunch was right on the money. You\n"
	.string "have a winning aura about you.\p"
	.string "So, anyway, this will be fun. Let's have\n"
	.string "our battle!$"

EternaCity_Gym_EventScript_SNRematch::
	lock
	faceplayer
	msgbox EternaCity_Gym_EventScript_SNRematch_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EternaCity_Gym_EventScript_SNRematch_No
	msgbox EternaCity_Gym_EventScript_SNRematch_Go, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ISAIAH_5_SINNOH, EternaCity_Gym_EventScript_SNRematch_Defeat
	msgbox EternaCity_Gym_EventScript_SNRematch_After, MSGBOX_DEFAULT
	release
	end

EternaCity_Gym_EventScript_SNRematch_After::
	.string "That was a great battle! Come back\n"
	.string "anytime for another match!$"

EternaCity_Gym_EventScript_SNRematch_Defeat::
	.string "Amazing… You really are the CHAMPION!$"

EternaCity_Gym_EventScript_SNRematch_Go::
	.string "Then I won't hold back this time!$"

EternaCity_Gym_EventScript_SNRematch_No::
	msgbox EternaCity_Gym_EventScript_SNRematch_NoT, MSGBOX_DEFAULT
	release
	end

EternaCity_Gym_EventScript_SNRematch_NoT::
	.string "Come back whenever you're ready!$"

EternaCity_Gym_EventScript_SNRematch_Ask::
	.string "GARDENIA: You became the CHAMPION!\n"
	.string "Welcome back!\p"
	.string "I've been training even harder since\n"
	.string "our last battle.\p"
	.string "Will you battle me again?$"

EternaCity_Gym_EventScript_Guide::
	lock
	faceplayer
	goto_if_set FLAG_SINNOH_BADGE2_GET, EternaCity_Gym_EventScript_GuideWon
	msgbox EternaCity_Gym_Text_Guide, MSGBOX_DEFAULT
	msgbox EternaCity_Gym_Text_SNGuideInfo, MSGBOX_DEFAULT
	release
	end

EternaCity_Gym_Text_SNGuideInfo::
	.string "Let me tell you about this GYM!\p"
	.string "The GYM LEADER is GARDENIA, the\n"
	.string "Grass-Type Lover. Her GYM is an indoor\l"
	.string "garden full of trees and flower beds.\p"
	.string "She uses Grass-type POKéMON like\n"
	.string "TURTWIG, CHERRIM and ROSERADE.\p"
	.string "Grass types are weak to Fire, Flying,\n"
	.string "Ice, Poison and Bug moves!\p"
	.string "Her TRAINERS are waiting among the\n"
	.string "trees. Beat them on your way to\l"
	.string "GARDENIA!$"

EternaCity_Gym_Text_Guide::
	.string "Hey, there! How's it going,\n"
	.string "CHAMP-to-be?\p"
	.string "I'm the GYM guide! I help out TRAINERS\n"
	.string "who come to challenge the GYM LEADER.$"

EternaCity_Gym_EventScript_GuideWon::
	msgbox EternaCity_Gym_Text_GuideWon, MSGBOX_DEFAULT
	release
	end

EternaCity_Gym_Text_GuideWon::
	.string "Oh! {PLAYER}! You've beaten the GYM\n"
	.string "LEADER!\p"
	.string "Your POKéMON look much tougher than\n"
	.string "when they went in, too!\p"
	.string "At least that's how I see it!$"

EternaCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_SINNOH_BADGE2_GET, EternaCity_Gym_EventScript_GymStatuePostVictory
	msgbox EternaCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

EternaCity_Gym_Text_GymStatue::
	.string "ETERNA CITY POKéMON GYM\n"
	.string "LEADER: GARDENIA$"

EternaCity_Gym_EventScript_GymStatuePostVictory::
	msgbox EternaCity_Gym_Text_GymStatuePlayerWon, MSGBOX_DEFAULT
	releaseall
	end

EternaCity_Gym_Text_GymStatuePlayerWon::
	.string "ETERNA CITY POKéMON GYM\n"
	.string "LEADER: GARDENIA\p"
	.string "Certified TRAINERS:\n"
	.string "{PLAYER}$"
