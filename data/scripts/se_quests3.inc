@ Super Emerald: more side activities for Kanto and Johto.
@  Kanto: the Eevee fan of the Celadon Condominiums (FLAG_SE_EEVEE_FAN_*): show her every Eeveelution
@  Johto: the Type Master of the National Park (VAR_SE_TYPE_MASTER_DAY): a different type every day

@ ===========================================================================
@ KANTO: the Eevee fan
@ ===========================================================================
SE_EventScript_EeveeFan::
	lock
	faceplayer
	goto_if_set FLAG_SE_EEVEE_FAN_DONE, SE_EventScript_EeveeFanDone
	msgbox SE_Text_EeveeFanIntro, MSGBOX_DEFAULT
	setvar VAR_0x8008, 0
	goto_if_set FLAG_SE_EEVEE_FAN_VAPOREON, SE_EventScript_EeveeFanSkipVAPOREON
	checkspecies SPECIES_VAPOREON
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_EeveeFanSkipVAPOREON
	bufferspeciesname STR_VAR_1, SPECIES_VAPOREON
	msgbox SE_Text_EeveeFanShown, MSGBOX_DEFAULT
	giveitem ITEM_RARE_CANDY
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_EeveeFanBagFull
	setflag FLAG_SE_EEVEE_FAN_VAPOREON
	addvar VAR_0x8008, 1
SE_EventScript_EeveeFanSkipVAPOREON:
	goto_if_set FLAG_SE_EEVEE_FAN_JOLTEON, SE_EventScript_EeveeFanSkipJOLTEON
	checkspecies SPECIES_JOLTEON
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_EeveeFanSkipJOLTEON
	bufferspeciesname STR_VAR_1, SPECIES_JOLTEON
	msgbox SE_Text_EeveeFanShown, MSGBOX_DEFAULT
	giveitem ITEM_RARE_CANDY
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_EeveeFanBagFull
	setflag FLAG_SE_EEVEE_FAN_JOLTEON
	addvar VAR_0x8008, 1
SE_EventScript_EeveeFanSkipJOLTEON:
	goto_if_set FLAG_SE_EEVEE_FAN_FLAREON, SE_EventScript_EeveeFanSkipFLAREON
	checkspecies SPECIES_FLAREON
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_EeveeFanSkipFLAREON
	bufferspeciesname STR_VAR_1, SPECIES_FLAREON
	msgbox SE_Text_EeveeFanShown, MSGBOX_DEFAULT
	giveitem ITEM_RARE_CANDY
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_EeveeFanBagFull
	setflag FLAG_SE_EEVEE_FAN_FLAREON
	addvar VAR_0x8008, 1
SE_EventScript_EeveeFanSkipFLAREON:
	goto_if_set FLAG_SE_EEVEE_FAN_ESPEON, SE_EventScript_EeveeFanSkipESPEON
	checkspecies SPECIES_ESPEON
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_EeveeFanSkipESPEON
	bufferspeciesname STR_VAR_1, SPECIES_ESPEON
	msgbox SE_Text_EeveeFanShown, MSGBOX_DEFAULT
	giveitem ITEM_RARE_CANDY
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_EeveeFanBagFull
	setflag FLAG_SE_EEVEE_FAN_ESPEON
	addvar VAR_0x8008, 1
SE_EventScript_EeveeFanSkipESPEON:
	goto_if_set FLAG_SE_EEVEE_FAN_UMBREON, SE_EventScript_EeveeFanSkipUMBREON
	checkspecies SPECIES_UMBREON
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_EeveeFanSkipUMBREON
	bufferspeciesname STR_VAR_1, SPECIES_UMBREON
	msgbox SE_Text_EeveeFanShown, MSGBOX_DEFAULT
	giveitem ITEM_RARE_CANDY
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_EeveeFanBagFull
	setflag FLAG_SE_EEVEE_FAN_UMBREON
	addvar VAR_0x8008, 1
SE_EventScript_EeveeFanSkipUMBREON:
	goto_if_set FLAG_SE_EEVEE_FAN_LEAFEON, SE_EventScript_EeveeFanSkipLEAFEON
	checkspecies SPECIES_LEAFEON
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_EeveeFanSkipLEAFEON
	bufferspeciesname STR_VAR_1, SPECIES_LEAFEON
	msgbox SE_Text_EeveeFanShown, MSGBOX_DEFAULT
	giveitem ITEM_RARE_CANDY
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_EeveeFanBagFull
	setflag FLAG_SE_EEVEE_FAN_LEAFEON
	addvar VAR_0x8008, 1
SE_EventScript_EeveeFanSkipLEAFEON:
	goto_if_set FLAG_SE_EEVEE_FAN_GLACEON, SE_EventScript_EeveeFanSkipGLACEON
	checkspecies SPECIES_GLACEON
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_EeveeFanSkipGLACEON
	bufferspeciesname STR_VAR_1, SPECIES_GLACEON
	msgbox SE_Text_EeveeFanShown, MSGBOX_DEFAULT
	giveitem ITEM_RARE_CANDY
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_EeveeFanBagFull
	setflag FLAG_SE_EEVEE_FAN_GLACEON
	addvar VAR_0x8008, 1
SE_EventScript_EeveeFanSkipGLACEON:
	goto_if_set FLAG_SE_EEVEE_FAN_SYLVEON, SE_EventScript_EeveeFanSkipSYLVEON
	checkspecies SPECIES_SYLVEON
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_EeveeFanSkipSYLVEON
	bufferspeciesname STR_VAR_1, SPECIES_SYLVEON
	msgbox SE_Text_EeveeFanShown, MSGBOX_DEFAULT
	giveitem ITEM_RARE_CANDY
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_EeveeFanBagFull
	setflag FLAG_SE_EEVEE_FAN_SYLVEON
	addvar VAR_0x8008, 1
SE_EventScript_EeveeFanSkipSYLVEON:
	goto_if_eq VAR_0x8008, 0, SE_EventScript_EeveeFanNothing
	goto_if_unset FLAG_SE_EEVEE_FAN_VAPOREON, SE_EventScript_EeveeFanMore
	goto_if_unset FLAG_SE_EEVEE_FAN_JOLTEON, SE_EventScript_EeveeFanMore
	goto_if_unset FLAG_SE_EEVEE_FAN_FLAREON, SE_EventScript_EeveeFanMore
	goto_if_unset FLAG_SE_EEVEE_FAN_ESPEON, SE_EventScript_EeveeFanMore
	goto_if_unset FLAG_SE_EEVEE_FAN_UMBREON, SE_EventScript_EeveeFanMore
	goto_if_unset FLAG_SE_EEVEE_FAN_LEAFEON, SE_EventScript_EeveeFanMore
	goto_if_unset FLAG_SE_EEVEE_FAN_GLACEON, SE_EventScript_EeveeFanMore
	goto_if_unset FLAG_SE_EEVEE_FAN_SYLVEON, SE_EventScript_EeveeFanMore
	msgbox SE_Text_EeveeFanAll, MSGBOX_DEFAULT
	giveitem ITEM_ABILITY_PATCH
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_EeveeFanBagFull
	setflag FLAG_SE_EEVEE_FAN_DONE
	msgbox SE_Text_EeveeFanThanks, MSGBOX_DEFAULT
	release
	end
SE_EventScript_EeveeFanMore:
	msgbox SE_Text_EeveeFanMore, MSGBOX_DEFAULT
	release
	end
SE_EventScript_EeveeFanNothing:
	msgbox SE_Text_EeveeFanNothing, MSGBOX_DEFAULT
	release
	end
SE_EventScript_EeveeFanBagFull:
	msgbox SE_Text_QuestBagFull, MSGBOX_DEFAULT
	release
	end
SE_EventScript_EeveeFanDone:
	msgbox SE_Text_EeveeFanThanks, MSGBOX_DEFAULT
	release
	end

SE_Text_EeveeFanIntro:
	.string "I adore EEVEE! It can become so many\n"
	.string "different POKéMON!\p"
	.string "Show me every evolution of EEVEE\n"
	.string "and I'll give you a little present!$"
SE_Text_EeveeFanShown:
	.string "Oh my! That's a {STR_VAR_1}!\n"
	.string "Isn't it just gorgeous?\p"
	.string "Here, take this for showing me!$"
SE_Text_EeveeFanNothing:
	.string "Hmm… You don't have any EEVEE\n"
	.string "evolution I haven't seen yet.\p"
	.string "Put one in your party and come back!$"
SE_Text_EeveeFanMore:
	.string "There are still more evolutions of\n"
	.string "EEVEE I want to see!\p"
	.string "VAPOREON, JOLTEON, FLAREON, ESPEON,\n"
	.string "UMBREON, LEAFEON, GLACEON, SYLVEON…\p"
	.string "Come back when you've got another!$"
SE_Text_EeveeFanAll:
	.string "That's all eight of them!\n"
	.string "You truly are an EEVEE master!\p"
	.string "Please take my most precious treasure.\n"
	.string "It can change a POKéMON's ability!$"
SE_Text_EeveeFanThanks:
	.string "Thanks to you, I've seen every EEVEE\n"
	.string "evolution. I'm so happy!$"

@ ===========================================================================
@ JOHTO: the Type Master
@ ===========================================================================
SE_EventScript_TypeMaster::
	lock
	faceplayer
	special SE_GetDailyType
	goto_if_eq VAR_RESULT, TRUE, SE_EventScript_TypeMasterDone
	msgbox SE_Text_TypeMasterAsk, MSGBOX_DEFAULT
	special SE_CheckPartyHasType
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_TypeMasterNone
	msgbox SE_Text_TypeMasterGood, MSGBOX_DEFAULT
	giveitem VAR_0x8005
	goto_if_eq VAR_RESULT, FALSE, SE_EventScript_EeveeFanBagFull
	special SE_SetDailyTypeDone
	msgbox SE_Text_TypeMasterTomorrow, MSGBOX_DEFAULT
	release
	end
SE_EventScript_TypeMasterNone:
	msgbox SE_Text_TypeMasterNone, MSGBOX_DEFAULT
	release
	end
SE_EventScript_TypeMasterDone:
	msgbox SE_Text_TypeMasterTomorrow, MSGBOX_DEFAULT
	release
	end

SE_Text_TypeMasterAsk:
	.string "I'm the TYPE MASTER! Every day I want\n"
	.string "to see a POKéMON of a different type.\p"
	.string "Today's type is {STR_VAR_1}!\n"
	.string "Do you have one with you?$"
SE_Text_TypeMasterGood:
	.string "Splendid! A fine {STR_VAR_1}-type\n"
	.string "POKéMON! You deserve a reward!$"
SE_Text_TypeMasterNone:
	.string "You don't have a {STR_VAR_1}-type\n"
	.string "POKéMON in your party…\p"
	.string "Bring one before the day is over!$"
SE_Text_TypeMasterTomorrow:
	.string "Come back tomorrow! I'll want to see\n"
	.string "a POKéMON of another type!$"
