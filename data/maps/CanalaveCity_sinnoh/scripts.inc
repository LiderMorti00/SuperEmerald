

CanalaveCity_Text_PtNpc1::
	.string "What's up? Your clothes look damp.\p"
	.string "Maybe you took the boat to Iron\n"
	.string "Island to get a Hidden Machine, right?$"

SE_S_CanalaveCity_CanalaveCity_EventScript_PtNpc1::
	msgbox CanalaveCity_Text_PtNpc1, MSGBOX_NPC
	end

CanalaveCity_Text_PtNpc2::
	.string "My PSYDUCK is very close to me. That\n"
	.string "makes its Return move powerful!$"

SE_S_CanalaveCity_CanalaveCity_EventScript_PtNpc2::
	msgbox CanalaveCity_Text_PtNpc2, MSGBOX_NPC
	end

CanalaveCity_EventScript_PtNpc3_Text_SNVar1::
	.string "There’s a really impatient-looking boy\n"
	.string "hanging out in front of the library.\p"
	.string "He’s so jittery, just seeing him makes\n"
	.string "me feel twitchy.$"

SE_S_CanalaveCity_CanalaveCity_EventScript_PtNpc3::
	msgbox CanalaveCity_EventScript_PtNpc3_Text_SNVar1, MSGBOX_NPC
	end

CanalaveCity_Text_PtNpc4::
	.string "I'm going to study at the library.\p"
	.string "I've taken an interest in the subject\n"
	.string "of time and space.$"

SE_S_CanalaveCity_CanalaveCity_EventScript_PtNpc4::
	msgbox CanalaveCity_Text_PtNpc4, MSGBOX_NPC
	end

CanalaveCity_Text_PtNpc5::
	.string "The Gym Leader and Trainers of this\n"
	.string "Gym often go out to Iron Island.\p"
	.string "They not only train their POKéMON, but\n"
	.string "they work out as well.$"

SE_S_CanalaveCity_CanalaveCity_EventScript_PtNpc5::
	msgbox CanalaveCity_Text_PtNpc5, MSGBOX_NPC
	end

CanalaveCity_Text_SNGoingToFullmoon::
	.string "...You.... You’re going to Fullmoon Island\n"
	.string "for us?$"

SE_S_CanalaveCity_CanalaveCity_EventScript_SailorEldritch::
	msgbox CanalaveCity_Text_SNGoingToFullmoon, MSGBOX_NPC
	end

CanalaveCity_EventScript_PtNpc6::
	lock
	faceplayer
	goto_if_set FLAG_SN_LAKE_VALOR_EXPLODED_4, CanalaveCity_EventScript_PtNpc6_PsyduckCryGuaagwa
	msgbox CanalaveCity_Text_PtNpc6_0, MSGBOX_DEFAULT
	goto CanalaveCity_EventScript_PtNpc6_NPCEnd

CanalaveCity_EventScript_PtNpc6_NPCEnd::
	release
	end

CanalaveCity_Text_PtNpc6_0::
	.string "PSYDUCK: Gua?$"

CanalaveCity_EventScript_PtNpc6_PsyduckCryGuaagwa::
	msgbox CanalaveCity_Text_PtNpc6_1, MSGBOX_DEFAULT
	goto CanalaveCity_EventScript_PtNpc6_NPCEnd

CanalaveCity_Text_PtNpc6_1::
	.string "PSYDUCK: Gua! Gua! Gwa? Guaa!\n"
	.string "Guuagwa?!$"

CanalaveCity_EventScript_SNBarry_Intro::
	.string "BARRY: Whoops! Hey, {PLAYER}!\p"
	.string "You’re going to challenge the Gym\n"
	.string "Leader up past here, eh?\p"
	.string "Someone should check to see if you’re\n"
	.string "ready for this challenge!\p"
	.string "That someone is me! With my brand-new\n"
	.string "Gym Badge!$"

SE_S_CanalaveCity_CanalaveCity_EventScript_SNBarry::
	msgbox CanalaveCity_EventScript_SNBarry_Intro, MSGBOX_NPC
	end

CanalaveCity_EventScript_SNExpRowan::
	msgbox CanalaveCity_Text_SNRowanTalk, MSGBOX_NPC
	end

CanalaveCity_Text_SNRowanTalk::
	.string "Rowan: Hmm...\p"
	.string "What is taking place at Lake Valor...\n"
	.string "You must find out!\p"
	.string "But before you go, let me stress: don’t\n"
	.string "get in over your head.\p"
	.string "We will try to join you as soon as we\n"
	.string "inspect Lake Verity.$"

CanalaveCity_EventScript_SNExpCounterpart::
	lock
	faceplayer
	checkplayergender
	call_if_eq VAR_RESULT, MALE, CanalaveCity_EventScript_SNDawnTalk
	call_if_eq VAR_RESULT, FEMALE, CanalaveCity_EventScript_SNLucasTalk
	release
	end

CanalaveCity_EventScript_SNLucasTalk::
	msgbox CanalaveCity_Text_SNLucasTalk, MSGBOX_DEFAULT
	return

CanalaveCity_Text_SNLucasTalk::
	.string "Lucas: We’re going to investigate Lake\n"
	.string "Verity before we join you.\p"
	.string "Don’t try to be a hero if anything\n"
	.string "crazy happens.$"

CanalaveCity_EventScript_SNDawnTalk::
	msgbox CanalaveCity_Text_SNDawnTalk, MSGBOX_DEFAULT
	return

CanalaveCity_Text_SNDawnTalk::
	.string "Dawn: We’re going off to Lake Verity\n"
	.string "first...\p"
	.string "Don’t do anything rash if something\n"
	.string "does happen.$"

CanalaveCity_EventScript_PtSign1::
	msgbox CanalaveCity_Text_PtSign1, MSGBOX_SIGN
	end

CanalaveCity_Text_PtSign1::
	.string "CANALAVE Library$"

CanalaveCity_EventScript_PtSign2::
	msgbox CanalaveCity_Text_PtSign2, MSGBOX_SIGN
	end

CanalaveCity_Text_PtSign2::
	.string "CANALAVE CITY POKéMON Gym Leader:\n"
	.string "BYRON The Man with the Steel Body!$"

CanalaveCity_EventScript_PtSign3::
	msgbox CanalaveCity_Text_PtSign3, MSGBOX_SIGN
	end

CanalaveCity_Text_PtSign3::
	.string "CANALAVE Dock$"

CanalaveCity_EventScript_PtSign4::
	msgbox CanalaveCity_Text_PtSign4, MSGBOX_SIGN
	end

CanalaveCity_Text_PtSign4::
	.string "CANALAVE CITY Cargo Port$"

CanalaveCity_EventScript_PtSign5::
	msgbox CanalaveCity_Text_PtSign5, MSGBOX_SIGN
	end

CanalaveCity_Text_PtSign5::
	.string "Sailor Eldritch's House$"

CanalaveCity_EventScript_PtSign6::
	msgbox CanalaveCity_Text_PtSign6, MSGBOX_SIGN
	end

CanalaveCity_Text_PtSign6::
	.string "Harbor Inn A Roost for Restless\n"
	.string "Sailors “Enjoy sweet dreams in our\l"
	.string "sumptuous beds!”$"

CanalaveCity_Text_SailorAllAboard::
	.string "All right! All aboard!$"
