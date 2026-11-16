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
	.string "My petals fell...$"

EternaCity_Gym_Text_CarolineIntro::
	.string "Welcome! Without further ado, let’s go!$"

EternaCity_Gym_EventScript_Jenna::
	trainerbattle_single TRAINER_OWEN_SINNOH, EternaCity_Gym_Text_JennaIntro, EternaCity_Gym_Text_JennaDefeat
	msgbox EternaCity_Gym_Text_JennaPost, MSGBOX_AUTOCLOSE
	end

EternaCity_Gym_Text_JennaPost::
	.string "FIRE and FLYING moves are strong\n"
	.string "against GRASS POKéMON.$"

EternaCity_Gym_Text_JennaDefeat::
	.string "Wilted...$"

EternaCity_Gym_Text_JennaIntro::
	.string "My Grass-type POKéMON can dole out\n"
	.string "some serious special attacks...\p"
	.string "I won’t let you win...easily!$"

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
	.string "You can’t win when you’re distracted by\n"
	.string "the lovely aromas of POKéMON!$"

EternaCity_Gym_Text_GardeniaPost::
	.string "Yup! If there’s one thing I can tell\n"
	.string "about you, it’s this!\p"
	.string "You and your POKéMON are gonna get\n"
	.string "even tougher, and I mean seriously!$"

SE_S_EternaCity_Gym_EternaCity_Gym_EventScript_Gardenia::
	msgbox EternaCity_Gym_Text_GardeniaPost, MSGBOX_NPC
	end

EternaCity_Gym_EventScript_Guide::
	lock
	faceplayer
	goto_if_set FLAG_SINNOH_BADGE2_GET, EternaCity_Gym_EventScript_GuideWon
	msgbox EternaCity_Gym_Text_Guide, MSGBOX_DEFAULT
	msgbox EternaCity_Gym_Text_SNGuideInfo, MSGBOX_DEFAULT
	release
	end

EternaCity_Gym_Text_SNGuideInfo::
	.string "Let me tell you about this Gym!\p"
	.string "The Gym Leader is GARDENIA, the\n"
	.string "Grass-Type Lover. Her Gym is an indoor\l"
	.string "garden full of trees and flower beds.\p"
	.string "She uses Grass-type POKéMON like\n"
	.string "TURTWIG, CHERRIM and ROSERADE.\p"
	.string "Grass types are weak to Fire, Flying,\n"
	.string "Ice, Poison and Bug moves!\p"
	.string "Her Trainers are waiting among the\n"
	.string "trees. Beat them on your way to\l"
	.string "GARDENIA!$"

EternaCity_Gym_Text_Guide::
	.string "Hey, there! How’s it going,\n"
	.string "Champ-to-be?\p"
	.string "I’m the Gym guide! I help out Trainers\n"
	.string "who come to challenge the Gym Leader.$"

EternaCity_Gym_EventScript_GuideWon::
	msgbox EternaCity_Gym_Text_GuideWon, MSGBOX_DEFAULT
	release
	end

EternaCity_Gym_Text_GuideWon::
	.string "Oh! {PLAYER}! You’ve beaten the Gym\n"
	.string "Leader!\p"
	.string "Your POKéMON look much tougher than\n"
	.string "when they went in, too!\p"
	.string "At least that’s how I see it!$"

EternaCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_SINNOH_BADGE2_GET, EternaCity_Gym_EventScript_GymStatuePostVictory
	msgbox EternaCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

EternaCity_Gym_Text_GymStatue::
	.string "Eterna City POKéMON Gym\n"
	.string "Leader: Gardenia\p"
	.string "Certified Trainers:\n"
	.string "{RIVAL}$"

EternaCity_Gym_EventScript_GymStatuePostVictory::
	msgbox EternaCity_Gym_Text_GymStatuePlayerWon, MSGBOX_DEFAULT
	releaseall
	end

EternaCity_Gym_Text_GymStatuePlayerWon::
	.string "Eterna City POKéMON Gym\n"
	.string "Leader: Gardenia\p"
	.string "Certified Trainers:\n"
	.string "{RIVAL}\n"
	.string "{PLAYER}$"
