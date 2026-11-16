LakeVerity_sinnoh_MapScripts::
	.byte 0


LakeVerity_Text_Cyrus::
	.string "???: ...The flowing time... ...The\n"
	.string "expanding space...\p"
	.string "I will make it all mine one day... Cyrus\n"
	.string "is my name. Remember it...\p"
	.string "Until then, sleep while you can,\n"
	.string "legendary POKéMON of the lake bed...$"

SE_S_LakeVerity_LakeVerity_EventScript_Scene::
	msgbox LakeVerity_Text_Cyrus, MSGBOX_NPC
	end

LakeVerity_EventScript_SNVERITY_MARS_Post::
	.string "Mars: The POKéMON of the three lakes\n"
	.string "are connected somehow.\p"
	.string "Thanks to Saturn’s grandstanding at\n"
	.string "Lake Valor, a cavern appeared here.\p"
	.string "It was the cavern where the POKéMON\n"
	.string "MESPRIT slept.\p"
	.string "MESPRIT appeared, too, probably to go\n"
	.string "help its friends.\p"
	.string "That worked out well for us. It was\n"
	.string "super easy to catch.\p"
	.string "So, now we’ve got them all: MESPRIT,\n"
	.string "“The Being of Emotion.”\p"
	.string "AZELF, “The Being of Willpower.”\p"
	.string "UXIE, “The Being of Intelligence.”\p"
	.string "Now that we have them all...\p"
	.string "You can look forward to what plans\n"
	.string "Team Galactic has for them!$"

SE_S_LakeVerity_LakeVerity_EventScript_SNVERITY_MARS::
	msgbox LakeVerity_EventScript_SNVERITY_MARS_Post, MSGBOX_NPC
	end

LakeVerity_EventScript_SNVERITY_GRUNT1::
	trainerbattle_single TRAINER_BENJAMIN_5_SINNOH, LakeVerity_EventScript_SNVERITY_GRUNT1_Intro, LakeVerity_EventScript_SNVERITY_GRUNT1_Defeat, LakeVerity_EventScript_SNVERITY_GRUNT1_Won
	msgbox LakeVerity_EventScript_SNVERITY_GRUNT1_Post, MSGBOX_AUTOCLOSE
	end

LakeVerity_EventScript_SNVERITY_GRUNT1_Post::
	.string "Mars will deal with you!$"

LakeVerity_EventScript_SNVERITY_GRUNT1_Won::
	lock
	msgbox LakeVerity_EventScript_SNVERITY_GRUNT1_Post, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	setflag FLAG_SN_HIDE_VERITY_GRUNT1
	fadescreen FADE_FROM_BLACK
	release
	end

LakeVerity_EventScript_SNVERITY_GRUNT1_Defeat::
	.string "Gah! Not again!$"

LakeVerity_EventScript_SNVERITY_GRUNT1_Intro::
	.string "Team Galactic is busy here! Get lost,\n"
	.string "kid!$"

LakeVerity_EventScript_SNVERITY_GRUNT2::
	trainerbattle_single TRAINER_ABIGAIL_1_SINNOH, LakeVerity_EventScript_SNVERITY_GRUNT2_Intro, LakeVerity_EventScript_SNVERITY_GRUNT2_Defeat, LakeVerity_EventScript_SNVERITY_GRUNT2_Won
	msgbox LakeVerity_EventScript_SNVERITY_GRUNT2_Post, MSGBOX_AUTOCLOSE
	end

LakeVerity_EventScript_SNVERITY_GRUNT2_Post::
	.string "Mars will deal with you!$"

LakeVerity_EventScript_SNVERITY_GRUNT2_Won::
	lock
	msgbox LakeVerity_EventScript_SNVERITY_GRUNT2_Post, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	setflag FLAG_SN_HIDE_VERITY_GRUNT2
	fadescreen FADE_FROM_BLACK
	release
	end

LakeVerity_EventScript_SNVERITY_GRUNT2_Defeat::
	.string "Gah! Not again!$"

LakeVerity_EventScript_SNVERITY_GRUNT2_Intro::
	.string "Team Galactic is busy here! Get lost,\n"
	.string "kid!$"

LakeVerity_EventScript_SNVERITY_GRUNT3::
	trainerbattle_single TRAINER_ABIGAIL_2_SINNOH, LakeVerity_EventScript_SNVERITY_GRUNT3_Intro, LakeVerity_EventScript_SNVERITY_GRUNT3_Defeat, LakeVerity_EventScript_SNVERITY_GRUNT3_Won
	msgbox LakeVerity_EventScript_SNVERITY_GRUNT3_Post, MSGBOX_AUTOCLOSE
	end

LakeVerity_EventScript_SNVERITY_GRUNT3_Post::
	.string "Mars will deal with you!$"

LakeVerity_EventScript_SNVERITY_GRUNT3_Won::
	lock
	msgbox LakeVerity_EventScript_SNVERITY_GRUNT3_Post, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	setflag FLAG_SN_HIDE_VERITY_GRUNT3
	fadescreen FADE_FROM_BLACK
	release
	end

LakeVerity_EventScript_SNVERITY_GRUNT3_Defeat::
	.string "Gah! Not again!$"

LakeVerity_EventScript_SNVERITY_GRUNT3_Intro::
	.string "Team Galactic is busy here! Get lost,\n"
	.string "kid!$"

LakeVerity_EventScript_SNVERITY_GRUNT4::
	trainerbattle_single TRAINER_ABIGAIL_3_SINNOH, LakeVerity_EventScript_SNVERITY_GRUNT4_Intro, LakeVerity_EventScript_SNVERITY_GRUNT4_Defeat, LakeVerity_EventScript_SNVERITY_GRUNT4_Won
	msgbox LakeVerity_EventScript_SNVERITY_GRUNT4_Post, MSGBOX_AUTOCLOSE
	end

LakeVerity_EventScript_SNVERITY_GRUNT4_Post::
	.string "Mars will deal with you!$"

LakeVerity_EventScript_SNVERITY_GRUNT4_Won::
	lock
	msgbox LakeVerity_EventScript_SNVERITY_GRUNT4_Post, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	setflag FLAG_SN_HIDE_VERITY_GRUNT4
	fadescreen FADE_FROM_BLACK
	release
	end

LakeVerity_EventScript_SNVERITY_GRUNT4_Defeat::
	.string "Gah! Not again!$"

LakeVerity_EventScript_SNVERITY_GRUNT4_Intro::
	.string "Team Galactic is busy here! Get lost,\n"
	.string "kid!$"

LakeVerity_EventScript_SNRowan::
	lock
	faceplayer
	call LakeVerity_EventScript_SNRowanTalk
	release
	end

LakeVerity_EventScript_SNRowanTalk::
	checkplayergender
	goto_if_eq VAR_RESULT, FEMALE, LakeVerity_EventScript_SNRowanLucas
	msgbox LakeVerity_Text_SNHelpDawn, MSGBOX_DEFAULT
	return

LakeVerity_Text_SNHelpDawn::
	.string "Rowan: Ah, {PLAYER}! What timing!\p"
	.string "Those Team Galactic scoundrels are\n"
	.string "after the legendary POKéMON!\p"
	.string "You’ve got to help Dawn!$"

LakeVerity_EventScript_SNRowanLucas::
	msgbox LakeVerity_Text_SNHelpLucas, MSGBOX_DEFAULT
	return

LakeVerity_Text_SNHelpLucas::
	.string "Rowan: Ah, {PLAYER}! What timing!\p"
	.string "Those Team Galactic scoundrels are\n"
	.string "after the legendary POKéMON!\p"
	.string "{PLAYER}, help us! You’ve got to help\n"
	.string "Lucas!$"

LakeVerity_EventScript_SNCounterpart::
	lock
	faceplayer
	checkplayergender
	goto_if_eq VAR_RESULT, FEMALE, LakeVerity_EventScript_SNCounterpartLucas
	msgbox LakeVerity_Text_SNDawn, MSGBOX_DEFAULT
	release
	end

LakeVerity_Text_SNDawn::
	.string "Dawn: {PLAYER}! It’s T-Team Galactic!\p"
	.string "They’re taking the POKéMON of the\n"
	.string "lake...\p"
	.string "I... I couldn’t beat this person...$"

LakeVerity_EventScript_SNCounterpartLucas::
	msgbox LakeVerity_Text_SNLucas, MSGBOX_DEFAULT
	release
	end

LakeVerity_Text_SNLucas::
	.string "Lucas: It’s Team Galactic! They took\n"
	.string "the POKéMON of the lake...\p"
	.string "This woman... I lost to her, but just\n"
	.string "barely!$"
