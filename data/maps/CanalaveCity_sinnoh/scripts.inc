

CanalaveCity_EventScript_PtNpc1::
	lock
	faceplayer
	call CanalaveCity_EventScript_SNExploded
	goto_if_eq VAR_RESULT, TRUE, CanalaveCity_EventScript_PtNpc1_SNVar0
	msgbox CanalaveCity_Text_PtNpc1, MSGBOX_DEFAULT
	release
	end

CanalaveCity_Text_PtNpc1::
	.string "What's up? Your clothes look damp.\p"
	.string "Maybe you took the boat to Iron\n"
	.string "Island to get a Hidden Machine, right?$"

CanalaveCity_EventScript_PtNpc1_SNVar0::
	msgbox CanalaveCity_EventScript_PtNpc1_Text_SNVar0, MSGBOX_DEFAULT
	release
	end

CanalaveCity_EventScript_PtNpc1_Text_SNVar0::
	.string "The tremor earlier was no quake. It\n"
	.string "seems it was a mysterious explosion!$"

CanalaveCity_EventScript_SNExplodedEnd::
	return

CanalaveCity_EventScript_SNExploded::
	setvar VAR_RESULT, FALSE
	goto_if_ne VAR_SN_SINNOH_STORY, 31, CanalaveCity_EventScript_SNExplodedEnd
	goto_if_set FLAG_SN_RECEIVED_GALACTIC_KEY, CanalaveCity_EventScript_SNExplodedEnd
	setvar VAR_RESULT, TRUE
	goto CanalaveCity_EventScript_SNExplodedEnd

CanalaveCity_EventScript_PtNpc2::
	lock
	faceplayer
	call CanalaveCity_EventScript_SNExploded
	goto_if_eq VAR_RESULT, TRUE, CanalaveCity_EventScript_PtNpc2_SNVar0
	msgbox CanalaveCity_Text_PtNpc2, MSGBOX_DEFAULT
	release
	end

CanalaveCity_Text_PtNpc2::
	.string "My PSYDUCK is very close to me. That\n"
	.string "makes its Return move powerful!$"

CanalaveCity_EventScript_PtNpc2_SNVar0::
	msgbox CanalaveCity_EventScript_PtNpc2_Text_SNVar0, MSGBOX_DEFAULT
	release
	end

CanalaveCity_EventScript_PtNpc2_Text_SNVar0::
	.string "E-even PS-PSYDUCK’s Future Sight\n"
	.string "couldn’t foretell that tremor!$"

CanalaveCity_EventScript_PtNpc3_Base::
	msgbox CanalaveCity_Text_PtNpc3, MSGBOX_DEFAULT
	release
	end

CanalaveCity_EventScript_PtNpc3::
	lock
	faceplayer
	call CanalaveCity_EventScript_SNExploded
	goto_if_eq VAR_RESULT, TRUE, CanalaveCity_EventScript_PtNpc3_SNVar0
	goto_if_unset FLAG_SINNOH_BADGE6_GET, CanalaveCity_EventScript_PtNpc3_Base
	goto_if_lt VAR_SN_SINNOH_STORY, 31, CanalaveCity_EventScript_PtNpc3_SNVar1
	goto CanalaveCity_EventScript_PtNpc3_Base

CanalaveCity_EventScript_PtNpc3_SNVar1::
	msgbox CanalaveCity_EventScript_PtNpc3_Text_SNVar1, MSGBOX_DEFAULT
	release
	end

CanalaveCity_EventScript_PtNpc3_Text_SNVar1::
	.string "There’s a really impatient-looking boy\n"
	.string "hanging out in front of the library.\p"
	.string "He’s so jittery, just seeing him makes\n"
	.string "me feel twitchy.$"

CanalaveCity_Text_PtNpc3::
	.string "Welcome to CANALAVE CITY, the Canal\n"
	.string "City!\p"
	.string "In the old days, this port used to be a\n"
	.string "hub of cargo transportation.$"

CanalaveCity_EventScript_PtNpc3_SNVar0::
	msgbox CanalaveCity_EventScript_PtNpc3_Text_SNVar0, MSGBOX_DEFAULT
	release
	end

CanalaveCity_EventScript_PtNpc3_Text_SNVar0::
	.string "What was that tremor? I thought Mt.\n"
	.string "CORONET erupted!$"

CanalaveCity_EventScript_PtNpc4::
	lock
	faceplayer
	call CanalaveCity_EventScript_SNExploded
	goto_if_eq VAR_RESULT, TRUE, CanalaveCity_EventScript_PtNpc4_SNVar0
	msgbox CanalaveCity_Text_PtNpc4, MSGBOX_DEFAULT
	release
	end

CanalaveCity_Text_PtNpc4::
	.string "I'm going to study at the library.\p"
	.string "I've taken an interest in the subject\n"
	.string "of time and space.$"

CanalaveCity_EventScript_PtNpc4_SNVar0::
	msgbox CanalaveCity_EventScript_PtNpc4_Text_SNVar0, MSGBOX_DEFAULT
	release
	end

CanalaveCity_EventScript_PtNpc4_Text_SNVar0::
	.string "Hey, hey! Old dude and kids! Did you\n"
	.string "hear?!\p"
	.string "They’re saying there was a huge\n"
	.string "explosion at LAKE VALOR!\p"
	.string "But, I hear everything’s fine now. I\n"
	.string "guess it was just a lot of noise.$"

CanalaveCity_EventScript_PtNpc5::
	lock
	faceplayer
	call CanalaveCity_EventScript_SNExploded
	goto_if_eq VAR_RESULT, TRUE, CanalaveCity_EventScript_PtNpc5_SNVar0
	msgbox CanalaveCity_Text_PtNpc5, MSGBOX_DEFAULT
	release
	end

CanalaveCity_Text_PtNpc5::
	.string "The GYM LEADER and TRAINERS of this\n"
	.string "GYM often go out to IRON ISLAND.\p"
	.string "They not only train their POKéMON, but\n"
	.string "they work out as well.$"

CanalaveCity_EventScript_PtNpc5_SNVar0::
	msgbox CanalaveCity_EventScript_PtNpc5_Text_SNVar0, MSGBOX_DEFAULT
	release
	end

CanalaveCity_EventScript_PtNpc5_Text_SNVar0::
	.string "I’m flabbergasted! What could explode\n"
	.string "at LAKE VALOR?$"

CanalaveCity_EventScript_SailorEldritch::
	lock
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, CanalaveCity_EventScript_SNEldritchMenu
	goto_if_set FLAG_SN_ELDRITCH_SON_WOKE, CanalaveCity_EventScript_SNEldritchWoke
	checkitem ITEM_LUNAR_WING
	goto_if_eq VAR_RESULT, TRUE, CanalaveCity_EventScript_SNEldritchTakeWing
	goto_if_set FLAG_SN_ELDRITCH_ASKED, CanalaveCity_EventScript_SNEldritchMenu
	setflag FLAG_SN_ELDRITCH_ASKED
	msgbox CanalaveCity_Text_SNGoingToFullmoon, MSGBOX_DEFAULT
	msgbox CanalaveCity_Text_SNCountingOnYou, MSGBOX_DEFAULT
	goto CanalaveCity_EventScript_SNEldritchMenu

CanalaveCity_EventScript_SailorMenu::
	dynmultipush CanalaveCity_Text_DestCancel, 3
	dynmultistack 0, 0, FALSE, 4, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case 0, CanalaveCity_EventScript_SailIronIsland
	case 1, CanalaveCity_EventScript_SailFullmoon
	case 2, CanalaveCity_EventScript_SailNewmoon
	msgbox CanalaveCity_Text_TellWheneverSetSail, MSGBOX_DEFAULT
	release
	end

CanalaveCity_EventScript_SNEldritchMenu::
	msgbox CanalaveCity_Text_DoYouWannaSetSail, MSGBOX_DEFAULT
	dynmultipush CanalaveCity_Text_DestIronIsland, 0
	goto_if_unset FLAG_SYS_GAME_CLEAR, CanalaveCity_EventScript_SailorMenu
	dynmultipush CanalaveCity_Text_DestFullmoon, 1
	dynmultipush CanalaveCity_Text_DestNewmoon, 2
	goto CanalaveCity_EventScript_SailorMenu

CanalaveCity_Text_DestNewmoon::
	.string "NEWMOON ISLAND$"

CanalaveCity_Text_DestFullmoon::
	.string "FULLMOON ISLAND$"

CanalaveCity_Text_TellWheneverSetSail::
	.string "You just tell me whenever you need to\n"
	.string "set sail!$"

CanalaveCity_EventScript_SailNewmoon::
	msgbox CanalaveCity_Text_SailorAllAboard, MSGBOX_DEFAULT
	closemessage
	warp MAP_NEWMOON_ISLAND_SINNOH, 23, 20
	waitstate
	release
	end

CanalaveCity_Text_SailorAllAboard::
	.string "All right! All aboard!$"

CanalaveCity_EventScript_SailFullmoon::
	msgbox CanalaveCity_Text_SailorAllAboard, MSGBOX_DEFAULT
	closemessage
	warp MAP_FULLMOON_ISLAND_SINNOH, 8, 20
	waitstate
	release
	end

CanalaveCity_EventScript_SailIronIsland::
	msgbox CanalaveCity_Text_SailorAllAboard, MSGBOX_DEFAULT
	closemessage
	warp MAP_IRON_ISLAND_SINNOH, 4, 22
	waitstate
	release
	end

CanalaveCity_Text_DestCancel::
	.string "CANCEL$"

CanalaveCity_Text_DestIronIsland::
	.string "IRON ISLAND$"

CanalaveCity_Text_DoYouWannaSetSail::
	.string "Ahoy! I’m ELDRITCH, a sailor. Do you\n"
	.string "wanna set sail?$"

CanalaveCity_Text_SNCountingOnYou::
	.string "We’re both counting on you!\p"
	.string "Only you can awaken my son from his\n"
	.string "awful nightmare...\p"
	.string "Please, I need the Lunar Wing from\n"
	.string "FULLMOON ISLAND to awaken him!\p"
	.string "I went, but I failed to find it...$"

CanalaveCity_Text_SNGoingToFullmoon::
	.string "...You.... You’re going to FULLMOON ISLAND\n"
	.string "for us?$"

CanalaveCity_EventScript_SNEldritchTakeWing::
	msgbox CanalaveCity_Text_SNTakeLunarWing, MSGBOX_DEFAULT
	release
	end

CanalaveCity_Text_SNTakeLunarWing::
	.string "That Lunar Wing... Please! Take it to my\n"
	.string "son...$"

CanalaveCity_EventScript_SNEldritchWoke::
	goto_if_set FLAG_SN_ELDRITCH_THANKED, CanalaveCity_EventScript_SNEldritchMenu
	setflag FLAG_SN_ELDRITCH_THANKED
	msgbox CanalaveCity_Text_SNComeSailWithMe, MSGBOX_DEFAULT
	goto CanalaveCity_EventScript_SNEldritchMenu

CanalaveCity_Text_SNComeSailWithMe::
	.string "Seeing you back to normal makes me\n"
	.string "feel great!\p"
	.string "I’ve regained my spirit as a Sailor!\n"
	.string "Come sail with me later!$"

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

CanalaveCity_EventScript_SNBarry_B0::
	trainerbattle_no_intro TRAINER_ELLIOT_5_SINNOH, CanalaveCity_EventScript_SNBarry_Defeat
	goto CanalaveCity_EventScript_SNBarry_After

CanalaveCity_EventScript_SNBarry::
	lock
	faceplayer
	checkitem ITEM_HM_STRENGTH
	goto_if_eq VAR_RESULT, FALSE, CanalaveCity_EventScript_SNBarry_NoHM
	msgbox CanalaveCity_EventScript_SNBarry_Intro, MSGBOX_DEFAULT
	closemessage
	switch VAR_SN_STARTER_MON
	case 0, CanalaveCity_EventScript_SNBarry_B0
	case 1, CanalaveCity_EventScript_SNBarry_B1
	case 2, CanalaveCity_EventScript_SNBarry_B2
	goto CanalaveCity_EventScript_SNBarry_B0

CanalaveCity_EventScript_SNBarry_B2::
	trainerbattle_no_intro TRAINER_BENJAMIN_2_SINNOH, CanalaveCity_EventScript_SNBarry_Defeat
	goto CanalaveCity_EventScript_SNBarry_After

CanalaveCity_EventScript_SNBarry_After::
	msgbox CanalaveCity_EventScript_SNBarry_Post, MSGBOX_DEFAULT
	closemessage
	sn_walkto VAR_LAST_TALKED, 3, 25, SN_SPEED_FAST, 0, 0, 0
	waitmovement VAR_LAST_TALKED
	removeobject VAR_LAST_TALKED
	setflag FLAG_SN_HIDE_CANAL_BARRY
	release
	end

CanalaveCity_EventScript_SNBarry_Post::
	.string "BARRY: Yeah, yeah, you’re just a bit\n"
	.string "better than me, as usual.\p"
	.string "But listen up!\p"
	.string "Let me tell you who’s going to take on\n"
	.string "the POKéMON LEAGUE and become the\p"
	.string "CHAMPION.\p"
	.string "You guessed right! It’s going to be me!\p"
	.string "Anyway, you should go to IRON ISLAND\n"
	.string "and toughen up some more.\p"
	.string "Yeah, train at IRON ISLAND! That’s what\n"
	.string "I did before going to the GYM!$"

CanalaveCity_EventScript_SNBarry_Defeat::
	.string "BARRY: Argh! Not again!$"

CanalaveCity_EventScript_SNBarry_B1::
	trainerbattle_no_intro TRAINER_BENJAMIN_1_SINNOH, CanalaveCity_EventScript_SNBarry_Defeat
	goto CanalaveCity_EventScript_SNBarry_After

CanalaveCity_EventScript_SNBarry_Intro::
	.string "BARRY: Whoops! Hey, {PLAYER}!\p"
	.string "You’re going to challenge the GYM\n"
	.string "LEADER up past here, eh?\p"
	.string "Someone should check to see if you’re\n"
	.string "ready for this challenge!\p"
	.string "That someone is me! With my brand-new\n"
	.string "GYM BADGE!$"

CanalaveCity_EventScript_SNBarry_NoHM::
	msgbox CanalaveCity_EventScript_SNBarry_NoHMT, MSGBOX_DEFAULT
	release
	end

CanalaveCity_EventScript_SNBarry_NoHMT::
	.string "BARRY: Hey, you’re here! Finally!\p"
	.string "Oh, but what the...\p"
	.string "Aww, you haven’t gone to IRON ISLAND,\n"
	.string "have you?\p"
	.string "You didn’t get the HM Strength, did\n"
	.string "you?\p"
	.string "Aww, sheesh! I’ll wait here for you!\n"
	.string "Hurry up and go already!$"

CanalaveCity_EventScript_SNExpRowan::
	msgbox CanalaveCity_Text_SNRowanTalk, MSGBOX_NPC
	end

CanalaveCity_Text_SNRowanTalk::
	.string "ROWAN: Hmm...\p"
	.string "What is taking place at LAKE VALOR...\n"
	.string "You must find out!\p"
	.string "But before you go, let me stress: don’t\n"
	.string "get in over your head.\p"
	.string "We will try to join you as soon as we\n"
	.string "inspect LAKE VERITY.$"

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
	.string "LUCAS: We’re going to investigate Lake\n"
	.string "VERITY before we join you.\p"
	.string "Don’t try to be a hero if anything\n"
	.string "crazy happens.$"

CanalaveCity_EventScript_SNDawnTalk::
	msgbox CanalaveCity_Text_SNDawnTalk, MSGBOX_DEFAULT
	return

CanalaveCity_Text_SNDawnTalk::
	.string "DAWN: We’re going off to LAKE VERITY\n"
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
	.string "CANALAVE CITY POKéMON GYM LEADER:\n"
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
	.string "Sailor ELDRITCH's House$"

CanalaveCity_EventScript_PtSign6::
	msgbox CanalaveCity_Text_PtSign6, MSGBOX_SIGN
	end

CanalaveCity_Text_PtSign6::
	.string "Harbor Inn A Roost for Restless\n"
	.string "Sailors “Enjoy sweet dreams in our\l"
	.string "sumptuous beds!”$"
