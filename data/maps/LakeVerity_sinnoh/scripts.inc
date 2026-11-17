LakeVerity_sinnoh_MapScripts::
	.byte 0


Sinnoh_EventScript_BufferCounterpartName::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Sinnoh_EventScript_BufferDawn
	bufferstring STR_VAR_1, Sinnoh_Text_Lucas
	return

Sinnoh_Text_Lucas::
	.string "LUCAS$"

Sinnoh_EventScript_BufferDawn::
	bufferstring STR_VAR_1, Sinnoh_Text_Dawn
	return

Sinnoh_Text_Dawn::
	.string "DAWN$"

LakeVerity_EventScript_Scene::
	lockall
	applymovement LOCALID_LAKE_BARRY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LakeVerity_Text_Cyrus, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_LAKE_BARRY, Common_Movement_FaceUp
	applymovement LOCALID_LAKE_CYRUS, LakeVerity_Movement_SNCyrusTurn
	waitmovement 0
	sn_walktoplayer LOCALID_LAKE_CYRUS, SN_SPEED_NORMAL
	waitmovement 0
	sn_playerface LOCALID_LAKE_CYRUS
	waitmovement LOCALID_PLAYER
	msgbox LakeVerity_Text_Cyrus2, MSGBOX_DEFAULT
	closemessage
	sn_walkto LOCALID_LAKE_CYRUS, 38, 43, SN_SPEED_NORMAL
	waitmovement 0
	removeobject LOCALID_LAKE_CYRUS
	applymovement LOCALID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	playmoncry SPECIES_MESPRIT, CRY_MODE_NORMAL
	waitmoncry
	msgbox LakeVerity_Text_Cry, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_LAKE_BARRY, Common_Movement_ExclamationMark
	waitmovement 0
	sn_walktoplayer LOCALID_LAKE_BARRY, SN_SPEED_FAST
	waitmovement 0
	sn_playerface LOCALID_LAKE_BARRY
	waitmovement LOCALID_PLAYER
	msgbox LakeVerity_Text_Barry, MSGBOX_DEFAULT
	closemessage
	sn_walkto LOCALID_LAKE_BARRY, 39, 43, SN_SPEED_FAST
	waitmovement 0
	removeobject LOCALID_LAKE_BARRY
	setflag FLAG_HIDE_LAKE_VERITY_ROWAN
	setvar VAR_SN_SINNOH_STORY, 7
	releaseall
	end

LakeVerity_Text_Barry::
	.string "{RIVAL}: What was that about? Weird\n"
	.string "guy...\p"
	.string "{RIVAL}: OK, {PLAYER}! Let’s catch\n"
	.string "that legendary POKéMON!\p"
	.string "{RIVAL}: ! Did you hear that,\n"
	.string "{PLAYER}?!\p"
	.string "That was the legendary POKéMON\n"
	.string "crying! That had to be it!\p"
	.string "OK! This is our chance! Let’s catch it!\p"
	.string "...Wait! What...?!\p"
	.string "We don’t have anything on us!\p"
	.string "You know, POKé BALLS! P-O-K-accent-E\n"
	.string "Balls!\p"
	.string "If we don’t have those, we can’t catch\n"
	.string "POKéMON or take them around with us!\p"
	.string "...Do you think PROF. ROWAN’d give us\n"
	.string "some if we asked him?\p"
	.string "You know, you remember what he said,\n"
	.string "don’t you?\p"
	.string "He said to visit him at his lab if we\n"
	.string "needed anything.\p"
	.string "OK, {PLAYER}! I’ll race you!\p"
	.string "First one to the professor’s lab in\n"
	.string "SANDGEM TOWN rules!$"

LakeVerity_Text_Cry::
	.string "Kyauuun!$"

LakeVerity_Text_Cyrus2::
	.string "???: Allow me to pass. Step aside.$"

LakeVerity_Movement_SNCyrusTurn::
	delay_16
	face_down
	delay_8
	step_end

LakeVerity_Text_Cyrus::
	.string "???: ...The flowing time... ...The\n"
	.string "expanding space...\p"
	.string "I will make it all mine one day... CYRUS\n"
	.string "is my name. Remember it...\p"
	.string "Until then, sleep while you can,\n"
	.string "legendary POKéMON of the lake bed...$"

LakeVerity_EventScript_SNVERITY_MARS::
	trainerbattle_single TRAINER_BENJAMIN_4_SINNOH, LakeVerity_EventScript_SNVERITY_MARS_Intro, LakeVerity_EventScript_SNVERITY_MARS_Defeat, LakeVerity_EventScript_SNVERITY_MARS_Won
	msgbox LakeVerity_EventScript_SNVERITY_MARS_Post, MSGBOX_AUTOCLOSE
	end

LakeVerity_EventScript_SNVERITY_MARS_Post::
	.string "MARS: The POKéMON of the three lakes\n"
	.string "are connected somehow.\p"
	.string "Thanks to SATURN’s grandstanding at\n"
	.string "LAKE VALOR, a cavern appeared here.\p"
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
	.string "TEAM GALACTIC has for them!$"

LakeVerity_EventScript_SNVERITY_MARS_Won::
	lock
	msgbox LakeVerity_Text_SNMarsDefeat2, MSGBOX_DEFAULT
	msgbox LakeVerity_EventScript_SNVERITY_MARS_Post, MSGBOX_DEFAULT
	msgbox LakeVerity_Text_SNPullingOut, MSGBOX_DEFAULT
	closemessage
	sn_walkto VAR_LAST_TALKED, 39, 43, SN_SPEED_FAST, 0, 0, 0
	waitmovement 0
	removeobject VAR_LAST_TALKED
	setflag FLAG_SN_HIDE_VERITY_MARS
	call Sinnoh_EventScript_BufferCounterpartName
	msgbox LakeVerity_Text_SNAfterMars1, MSGBOX_DEFAULT
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LakeVerity_Text_SNAfterMars2_ScrD
	call_if_eq VAR_RESULT, FEMALE, LakeVerity_Text_SNAfterMars2_ScrL
	release
	end

LakeVerity_Text_SNAfterMars2_ScrL::
	msgbox LakeVerity_Text_SNAfterMars2_Lu, MSGBOX_DEFAULT
	return

LakeVerity_Text_SNAfterMars2_Lu::
	.string "{STR_VAR_1}: {PLAYER}, what’s Team\n"
	.string "GALACTIC up to?\p"
	.string "They’d better not harm the POKéMON\n"
	.string "they took from the lakes...$"

LakeVerity_Text_SNAfterMars2_ScrD::
	checkplayergender
	call_if_eq VAR_RESULT, FEMALE, LakeVerity_Text_SNAfterMars2_SNLucasCall
	call_if_ne VAR_RESULT, FEMALE, LakeVerity_Text_SNAfterMars2_SNDawnCall
	return

LakeVerity_Text_SNAfterMars2_SNDawnCall::
	msgbox LakeVerity_Text_SNAfterMars2, MSGBOX_DEFAULT
	return

LakeVerity_Text_SNAfterMars2::
	.string "{STR_VAR_1}: {PLAYER}, what is Team\n"
	.string "GALACTIC up to?\p"
	.string "Are the abducted POKéMON of the lakes\n"
	.string "going to be OK?$"

LakeVerity_Text_SNAfterMars2_SNLucasCall::
	msgbox LakeVerity_Text_SNAfterMars2_SNLu, MSGBOX_DEFAULT
	return

LakeVerity_Text_SNAfterMars2_SNLu::
	.string "{STR_VAR_1}: {PLAYER}, what’s Team\n"
	.string "GALACTIC up to?\p"
	.string "They’d better not harm the POKéMON\n"
	.string "they took from the lakes...$"

LakeVerity_Text_SNAfterMars1::
	.string "ROWAN: I see... This also occurred at\n"
	.string "LAKE VALOR...\p"
	.string "Another legendary POKéMON was taken\n"
	.string "away by TEAM GALACTIC...\p"
	.string "Both of you went up against\n"
	.string "full-fledged criminals...\p"
	.string "The fact that you’re unharmed is\n"
	.string "reason enough to celebrate.\p"
	.string "...But what about {RIVAL}?\p"
	.string "What is happening at LAKE ACUITY? Is\n"
	.string "{RIVAL} safe?\p"
	.string "ROWAN: {PLAYER}, I need you to go to\n"
	.string "LAKE ACUITY right away.\p"
	.string "I’m worried about {RIVAL}.$"

LakeVerity_Text_SNPullingOut::
	.string "Team! We’re pulling out! The boss is\n"
	.string "waiting at the HQ!$"

LakeVerity_Text_SNMarsDefeat2::
	.string "MARS: So, first the windworks, and now\n"
	.string "LAKE VERITY that I owe you for!\p"
	.string "This shouldn’t be happening to Team\n"
	.string "GALACTIC’s COMMANDER...\p"
	.string "...Calm down, MARS... I’ve done my part in\n"
	.string "all of this...\p"
	.string "My mission was to transport the lake’s\n"
	.string "POKéMON to our HQ...\p"
	.string "...That’s right! I accomplished my\n"
	.string "mission without a problem!$"

LakeVerity_EventScript_SNVERITY_MARS_Defeat::
	.string "I lost again...$"

LakeVerity_EventScript_SNVERITY_MARS_Intro::
	.string "MARS: That face...! It brings back bad\n"
	.string "memories!\p"
	.string "I’m talking about the windworks!\p"
	.string "I caught a whole lot of trouble for\n"
	.string "that little incident.\p"
	.string "What’s with that look on your face?\n"
	.string "You do remember me, don’t you?\p"
	.string "Fine, whatever. I’ll tell you who I am\n"
	.string "again!\p"
	.string "I’m MARS, one of TEAM GALACTIC’s\n"
	.string "COMMANDERS.\p"
	.string "So, what is it? Are you some\n"
	.string "lovey-dovey couple to the rescue?\p"
	.string "Not a chance! Not even a teeny one!\n"
	.string "You’re all going down!$"

LakeVerity_EventScript_SNVERITY_GRUNT1::
	trainerbattle_single TRAINER_BENJAMIN_5_SINNOH, LakeVerity_EventScript_SNVERITY_GRUNT1_Intro, LakeVerity_EventScript_SNVERITY_GRUNT1_Defeat, LakeVerity_EventScript_SNVERITY_GRUNT1_Won
	msgbox LakeVerity_EventScript_SNVERITY_GRUNT1_Post, MSGBOX_AUTOCLOSE
	end

LakeVerity_EventScript_SNVERITY_GRUNT1_Post::
	.string "MARS will deal with you!$"

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
	.string "TEAM GALACTIC is busy here! Get lost,\n"
	.string "kid!$"

LakeVerity_EventScript_SNVERITY_GRUNT2::
	trainerbattle_single TRAINER_ABIGAIL_1_SINNOH, LakeVerity_EventScript_SNVERITY_GRUNT2_Intro, LakeVerity_EventScript_SNVERITY_GRUNT2_Defeat, LakeVerity_EventScript_SNVERITY_GRUNT2_Won
	msgbox LakeVerity_EventScript_SNVERITY_GRUNT2_Post, MSGBOX_AUTOCLOSE
	end

LakeVerity_EventScript_SNVERITY_GRUNT2_Post::
	.string "MARS will deal with you!$"

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
	.string "TEAM GALACTIC is busy here! Get lost,\n"
	.string "kid!$"

LakeVerity_EventScript_SNVERITY_GRUNT3::
	trainerbattle_single TRAINER_ABIGAIL_2_SINNOH, LakeVerity_EventScript_SNVERITY_GRUNT3_Intro, LakeVerity_EventScript_SNVERITY_GRUNT3_Defeat, LakeVerity_EventScript_SNVERITY_GRUNT3_Won
	msgbox LakeVerity_EventScript_SNVERITY_GRUNT3_Post, MSGBOX_AUTOCLOSE
	end

LakeVerity_EventScript_SNVERITY_GRUNT3_Post::
	.string "MARS will deal with you!$"

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
	.string "TEAM GALACTIC is busy here! Get lost,\n"
	.string "kid!$"

LakeVerity_EventScript_SNVERITY_GRUNT4::
	trainerbattle_single TRAINER_ABIGAIL_3_SINNOH, LakeVerity_EventScript_SNVERITY_GRUNT4_Intro, LakeVerity_EventScript_SNVERITY_GRUNT4_Defeat, LakeVerity_EventScript_SNVERITY_GRUNT4_Won
	msgbox LakeVerity_EventScript_SNVERITY_GRUNT4_Post, MSGBOX_AUTOCLOSE
	end

LakeVerity_EventScript_SNVERITY_GRUNT4_Post::
	.string "MARS will deal with you!$"

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
	.string "TEAM GALACTIC is busy here! Get lost,\n"
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
	.string "ROWAN: Ah, {PLAYER}! What timing!\p"
	.string "Those TEAM GALACTIC scoundrels are\n"
	.string "after the legendary POKéMON!\p"
	.string "You’ve got to help DAWN!$"

LakeVerity_EventScript_SNRowanLucas::
	msgbox LakeVerity_Text_SNHelpLucas, MSGBOX_DEFAULT
	return

LakeVerity_Text_SNHelpLucas::
	.string "ROWAN: Ah, {PLAYER}! What timing!\p"
	.string "Those TEAM GALACTIC scoundrels are\n"
	.string "after the legendary POKéMON!\p"
	.string "{PLAYER}, help us! You’ve got to help\n"
	.string "LUCAS!$"

LakeVerity_EventScript_SNCounterpart::
	lock
	faceplayer
	checkplayergender
	goto_if_eq VAR_RESULT, FEMALE, LakeVerity_EventScript_SNCounterpartLucas
	msgbox LakeVerity_Text_SNDawn, MSGBOX_DEFAULT
	release
	end

LakeVerity_Text_SNDawn::
	.string "DAWN: {PLAYER}! It’s T-TEAM GALACTIC!\p"
	.string "They’re taking the POKéMON of the\n"
	.string "lake...\p"
	.string "I... I couldn’t beat this person...$"

LakeVerity_EventScript_SNCounterpartLucas::
	msgbox LakeVerity_Text_SNLucas, MSGBOX_DEFAULT
	release
	end

LakeVerity_Text_SNLucas::
	.string "LUCAS: It’s TEAM GALACTIC! They took\n"
	.string "the POKéMON of the lake...\p"
	.string "This woman... I lost to her, but just\n"
	.string "barely!$"
