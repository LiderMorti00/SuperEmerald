SpearPillar_sinnoh_MapScripts::
	.byte 0


SpearPillar_Text_SNGruntsIntro::
	.string "Our boss is about to do something\n"
	.string "spectacular!\p"
	.string "Don’t get in the way! Of course you\n"
	.string "will, won’t you?\p"
	.string "That’s why the two of us will team up to\n"
	.string "take you down in an epic duel!$"

SE_S_SpearPillar_SpearPillar_EventScript_SNSPGrunts::
	msgbox SpearPillar_Text_SNGruntsIntro, MSGBOX_NPC
	end

SpearPillar_EventScript_SNSPCommanders_T1::
	.string "Mars: Where do you think you’re going?\n"
	.string "I won’t let you disturb our boss.\p"
	.string "If you’re not going to listen, you’ll\n"
	.string "have to go through me first.\p"
	.string "After all, you’ve made me look bad more\n"
	.string "times than I care to remember!$"

SE_S_SpearPillar_SpearPillar_EventScript_SNSPCommanders::
	msgbox SpearPillar_EventScript_SNSPCommanders_T1, MSGBOX_NPC
	end

SpearPillar_EventScript_SNCyrus_T1::
	.string "Cyrus: ... ...\p"
	.string "Everything is ready for the creation\n"
	.string "of a new world.\p"
	.string "Now, all will end. And everything will\n"
	.string "begin.\p"
	.string "With this, the Red Chain made from the\n"
	.string "crystals of the three lake POKéMON...\p"
	.string "And this, the Red Chain I replicated\n"
	.string "with technological means...\p"
	.string "With these Red Chains I will pry open\n"
	.string "the portal to another dimension.\p"
	.string "I command that you unleash your power\n"
	.string "for me...$"

SE_S_SpearPillar_SpearPillar_EventScript_SNCyrus::
	msgbox SpearPillar_EventScript_SNCyrus_T1, MSGBOX_NPC
	end

SpearPillar_EventScript_SNDIALGA::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DIALGA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_DIALGA, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SpearPillar_EventScript_SNDIALGA_Ran
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SpearPillar_EventScript_SNDIALGA_Ran
	setflag FLAG_SN_DONE_DIALGA
	setflag FLAG_SN_HIDE_DIALGA
	goto Common_EventScript_RemoveStaticPokemon
	end

SpearPillar_EventScript_SNDIALGA_Ran::
	setvar VAR_0x8004, SPECIES_DIALGA
	goto Common_EventScript_LegendaryFlewAway
	end

SpearPillar_EventScript_SNPALKIA::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PALKIA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_PALKIA, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SpearPillar_EventScript_SNPALKIA_Ran
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SpearPillar_EventScript_SNPALKIA_Ran
	setflag FLAG_SN_DONE_PALKIA
	setflag FLAG_SN_HIDE_PALKIA
	goto Common_EventScript_RemoveStaticPokemon
	end

SpearPillar_EventScript_SNPALKIA_Ran::
	setvar VAR_0x8004, SPECIES_PALKIA
	goto Common_EventScript_LegendaryFlewAway
	end

SpearPillar_EventScript_SNSPBarryTalk::
	lock
	faceplayer
	msgbox SpearPillar_EventScript_SNSPCommanders_T9, MSGBOX_DEFAULT
	release
	end

SpearPillar_EventScript_SNSPCommanders_T9::
	.string "BARRY: Hey, {PLAYER}! This is it! It’s\n"
	.string "your show now!$"
