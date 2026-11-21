RuinsOfAlph_Lab_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RuinsOfAlph_Lab_OnTransition
	.byte 0


RuinsOfAlph_Lab_EventScript_Scientist2::
	lock
	faceplayer
	msgbox RuinsOfAlph_Lab_Text_Scientist2, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_Lab_Text_Scientist2::
	.string "There are odd patterns drawn on\n"
	.string "on the walls of the RUINS.\p"
	.string "They must be the keys for\n"
	.string "unraveling the RUINS' mystery.$"

RuinsOfAlph_Lab_EventScript_Scientist1::
	lock
	faceplayer
	msgbox RuinsOfAlph_Lab_Text_Scientist1, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_Lab_Text_Scientist1::
	.string "The RUINS are about 1500 years old.\p"
	.string "But it's not known why they were\n"
	.string "built--or by whom.$"

RuinsOfAlph_Lab_Text_DevelopDeviceToResurrectFossils::
	.string "I've been trying to develop a device\n"
	.string "that resurrects POKéMON from fossils…\p"
	.string "And, it's working!$"

@ Super Emerald: the lab revives every kind of fossil (like Devon in Rustboro).
@ The POKéMON is ready once the player has left the lab.
RuinsOfAlph_Lab_OnTransition::
	call_if_eq VAR_SE_ALPH_FOSSIL_STATE, 1, RuinsOfAlph_Lab_EventScript_FossilReady
	end

RuinsOfAlph_Lab_EventScript_FossilReady::
	setvar VAR_SE_ALPH_FOSSIL_STATE, 2
	return

SE_J_RuinsOfAlph_Lab_hns_RuinsOfAlph_Lab_EventScript_FossilScientist::
	lock
	faceplayer
	goto_if_eq VAR_SE_ALPH_FOSSIL_STATE, 2, RuinsOfAlph_Lab_EventScript_FossilGive
	goto_if_eq VAR_SE_ALPH_FOSSIL_STATE, 1, RuinsOfAlph_Lab_EventScript_FossilWorking
	msgbox RuinsOfAlph_Lab_Text_DevelopDeviceToResurrectFossils, MSGBOX_DEFAULT
	call RuinsOfAlph_Lab_EventScript_AskOmanyte
	call RuinsOfAlph_Lab_EventScript_AskKabuto
	call RuinsOfAlph_Lab_EventScript_AskAerodactyl
	call RuinsOfAlph_Lab_EventScript_AskLileep
	call RuinsOfAlph_Lab_EventScript_AskAnorith
	call RuinsOfAlph_Lab_EventScript_AskCranidos
	call RuinsOfAlph_Lab_EventScript_AskShieldon
	call RuinsOfAlph_Lab_EventScript_AskTirtouga
	call RuinsOfAlph_Lab_EventScript_AskArchen
	call RuinsOfAlph_Lab_EventScript_AskTyrunt
	call RuinsOfAlph_Lab_EventScript_AskAmaura
	msgbox RuinsOfAlph_Lab_Text_BringFossil, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_Lab_EventScript_FossilWorking::
	msgbox RuinsOfAlph_Lab_Text_FossilWorking, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_Lab_EventScript_FossilGive::
	getpartysize
	goto_if_eq VAR_RESULT, PARTY_SIZE, RuinsOfAlph_Lab_EventScript_FossilNoRoom
	bufferspeciesname STR_VAR_1, VAR_SE_ALPH_FOSSIL_SPECIES
	msgbox RuinsOfAlph_Lab_Text_FossilDone, MSGBOX_DEFAULT
	givemon VAR_SE_ALPH_FOSSIL_SPECIES, 20
	playfanfare MUS_OBTAIN_ITEM
	message RuinsOfAlph_Lab_Text_ReceivedFossilMon
	waitmessage
	waitfanfare
	setvar VAR_SE_ALPH_FOSSIL_STATE, 0
	release
	end

RuinsOfAlph_Lab_EventScript_FossilNoRoom::
	msgbox RuinsOfAlph_Lab_Text_FossilNoRoom, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_Lab_EventScript_StartRevive::
	setvar VAR_SE_ALPH_FOSSIL_STATE, 1
	msgbox RuinsOfAlph_Lab_Text_FossilTakes, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_Lab_EventScript_Fossils::
	lock
	msgbox RuinsOfAlph_Lab_Text_Fossils, MSGBOX_DEFAULT
	closemessage
	release
	end

RuinsOfAlph_Lab_Text_Fossils::
	.string "Fossils found within the RUINS.\n"
	.string "Maybe there are more somewhere…$"

SE_J_RuinsOfAlph_Lab_hns_EventScript_FakePC::
	msgbox Text_BootUpPC, MSGBOX_SIGN
	end

RuinsOfAlph_Lab_EventScript_AskOmanyte::
	checkitem ITEM_HELIX_FOSSIL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_NopReturn
	bufferitemname STR_VAR_1, ITEM_HELIX_FOSSIL
	msgbox RuinsOfAlph_Lab_Text_ReviveThisFossil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Common_EventScript_NopReturn
	removeitem ITEM_HELIX_FOSSIL
	setvar VAR_SE_ALPH_FOSSIL_SPECIES, SPECIES_OMANYTE
	goto RuinsOfAlph_Lab_EventScript_StartRevive

RuinsOfAlph_Lab_EventScript_AskKabuto::
	checkitem ITEM_DOME_FOSSIL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_NopReturn
	bufferitemname STR_VAR_1, ITEM_DOME_FOSSIL
	msgbox RuinsOfAlph_Lab_Text_ReviveThisFossil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Common_EventScript_NopReturn
	removeitem ITEM_DOME_FOSSIL
	setvar VAR_SE_ALPH_FOSSIL_SPECIES, SPECIES_KABUTO
	goto RuinsOfAlph_Lab_EventScript_StartRevive

RuinsOfAlph_Lab_EventScript_AskAerodactyl::
	checkitem ITEM_OLD_AMBER
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_NopReturn
	bufferitemname STR_VAR_1, ITEM_OLD_AMBER
	msgbox RuinsOfAlph_Lab_Text_ReviveThisFossil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Common_EventScript_NopReturn
	removeitem ITEM_OLD_AMBER
	setvar VAR_SE_ALPH_FOSSIL_SPECIES, SPECIES_AERODACTYL
	goto RuinsOfAlph_Lab_EventScript_StartRevive

RuinsOfAlph_Lab_EventScript_AskLileep::
	checkitem ITEM_ROOT_FOSSIL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_NopReturn
	bufferitemname STR_VAR_1, ITEM_ROOT_FOSSIL
	msgbox RuinsOfAlph_Lab_Text_ReviveThisFossil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Common_EventScript_NopReturn
	removeitem ITEM_ROOT_FOSSIL
	setvar VAR_SE_ALPH_FOSSIL_SPECIES, SPECIES_LILEEP
	goto RuinsOfAlph_Lab_EventScript_StartRevive

RuinsOfAlph_Lab_EventScript_AskAnorith::
	checkitem ITEM_CLAW_FOSSIL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_NopReturn
	bufferitemname STR_VAR_1, ITEM_CLAW_FOSSIL
	msgbox RuinsOfAlph_Lab_Text_ReviveThisFossil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Common_EventScript_NopReturn
	removeitem ITEM_CLAW_FOSSIL
	setvar VAR_SE_ALPH_FOSSIL_SPECIES, SPECIES_ANORITH
	goto RuinsOfAlph_Lab_EventScript_StartRevive

RuinsOfAlph_Lab_EventScript_AskCranidos::
	checkitem ITEM_SKULL_FOSSIL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_NopReturn
	bufferitemname STR_VAR_1, ITEM_SKULL_FOSSIL
	msgbox RuinsOfAlph_Lab_Text_ReviveThisFossil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Common_EventScript_NopReturn
	removeitem ITEM_SKULL_FOSSIL
	setvar VAR_SE_ALPH_FOSSIL_SPECIES, SPECIES_CRANIDOS
	goto RuinsOfAlph_Lab_EventScript_StartRevive

RuinsOfAlph_Lab_EventScript_AskShieldon::
	checkitem ITEM_ARMOR_FOSSIL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_NopReturn
	bufferitemname STR_VAR_1, ITEM_ARMOR_FOSSIL
	msgbox RuinsOfAlph_Lab_Text_ReviveThisFossil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Common_EventScript_NopReturn
	removeitem ITEM_ARMOR_FOSSIL
	setvar VAR_SE_ALPH_FOSSIL_SPECIES, SPECIES_SHIELDON
	goto RuinsOfAlph_Lab_EventScript_StartRevive

RuinsOfAlph_Lab_EventScript_AskTirtouga::
	checkitem ITEM_COVER_FOSSIL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_NopReturn
	bufferitemname STR_VAR_1, ITEM_COVER_FOSSIL
	msgbox RuinsOfAlph_Lab_Text_ReviveThisFossil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Common_EventScript_NopReturn
	removeitem ITEM_COVER_FOSSIL
	setvar VAR_SE_ALPH_FOSSIL_SPECIES, SPECIES_TIRTOUGA
	goto RuinsOfAlph_Lab_EventScript_StartRevive

RuinsOfAlph_Lab_EventScript_AskArchen::
	checkitem ITEM_PLUME_FOSSIL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_NopReturn
	bufferitemname STR_VAR_1, ITEM_PLUME_FOSSIL
	msgbox RuinsOfAlph_Lab_Text_ReviveThisFossil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Common_EventScript_NopReturn
	removeitem ITEM_PLUME_FOSSIL
	setvar VAR_SE_ALPH_FOSSIL_SPECIES, SPECIES_ARCHEN
	goto RuinsOfAlph_Lab_EventScript_StartRevive

RuinsOfAlph_Lab_EventScript_AskTyrunt::
	checkitem ITEM_JAW_FOSSIL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_NopReturn
	bufferitemname STR_VAR_1, ITEM_JAW_FOSSIL
	msgbox RuinsOfAlph_Lab_Text_ReviveThisFossil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Common_EventScript_NopReturn
	removeitem ITEM_JAW_FOSSIL
	setvar VAR_SE_ALPH_FOSSIL_SPECIES, SPECIES_TYRUNT
	goto RuinsOfAlph_Lab_EventScript_StartRevive

RuinsOfAlph_Lab_EventScript_AskAmaura::
	checkitem ITEM_SAIL_FOSSIL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_NopReturn
	bufferitemname STR_VAR_1, ITEM_SAIL_FOSSIL
	msgbox RuinsOfAlph_Lab_Text_ReviveThisFossil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Common_EventScript_NopReturn
	removeitem ITEM_SAIL_FOSSIL
	setvar VAR_SE_ALPH_FOSSIL_SPECIES, SPECIES_AMAURA
	goto RuinsOfAlph_Lab_EventScript_StartRevive

RuinsOfAlph_Lab_Text_ReviveThisFossil:
	.string "Oh! That's a {STR_VAR_1}!\n"
	.string "Shall I bring it back to life?$"

RuinsOfAlph_Lab_Text_BringFossil:
	.string "If you find a fossil, bring it to me.\n"
	.string "I can revive any kind of fossil!$"

RuinsOfAlph_Lab_Text_FossilTakes:
	.string "Leave it to me! It will take a little\n"
	.string "while. Go for a walk and come back!$"

RuinsOfAlph_Lab_Text_FossilWorking:
	.string "The machine is still working.\n"
	.string "Please come back a bit later.$"

RuinsOfAlph_Lab_Text_FossilDone:
	.string "There you are! The fossil came back\n"
	.string "to life as {STR_VAR_1}!$"

RuinsOfAlph_Lab_Text_ReceivedFossilMon:
	.string "{PLAYER} received {STR_VAR_1}!$"

RuinsOfAlph_Lab_Text_FossilNoRoom:
	.string "Your party is full. Come back when\n"
	.string "you have room for one more POKéMON.$"
