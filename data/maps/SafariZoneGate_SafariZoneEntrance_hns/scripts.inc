SafariZoneGate_SafariZoneEntrance_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SE_JohtoSafari_OnFrame
	.byte 0


SafariZoneGate_SafariZoneEntrance_Text_Baoba::
	.string "Hi {PLAYER}!\p"
	.string "How are you enjoying the SAFARI\n"
	.string "ZONE?$"

SE_J_SafariZoneGate_SafariZoneEntrance_hns_SafariZoneGate_SafariZoneEntrance_EventScript_Baoba::
	msgbox SafariZoneGate_SafariZoneEntrance_Text_Baoba, MSGBOX_NPC
	end

SafariZoneGate_SafariZoneEntrance_EventScript_Boy::
	lock
	faceplayer
	checkitem ITEM_POKEBLOCK_CASE
	goto_if_eq VAR_RESULT, FALSE, SafariZoneGate_SafariZoneEntrance_EventScript_BoyGiveExtraPokeblockCase
	msgbox SafariZoneGate_SafariZoneEntrance_Text_Boy, MSGBOX_DEFAULT
	closemessage
	release
	end

SafariZoneGate_SafariZoneEntrance_Text_Boy::
	.string "Do you know about POKéBLOCK\n"
	.string "feeders?\p"
	.string "Putting a POKéBLOCK in the feeder\n"
	.string "brings out POKéMON with HIDDEN\l"
	.string "ABILITIES!\p"
	.string "The type of POKéBLOCK also affects\n"
	.string "the POKéMON's nature.\p"
	.string "And best of all, the type of POKéBLOCK\n"
	.string "you use can attract POKéMON with\l"
	.string "perfect IVs!\p"
	.string "Those charts on the wall have all\n"
	.string "the details.$"

SafariZoneGate_SafariZoneEntrance_EventScript_BoyGiveExtraPokeblockCase::
	msgbox SafariZoneGate_SafariZoneEntrance_Text_BoyGiveCase, MSGBOX_DEFAULT
	giveitem ITEM_POKEBLOCK_CASE
	closemessage
	release
	end

SafariZoneGate_SafariZoneEntrance_Text_BoyGiveCase::
	.string "Here, you seem like you need this.$"

SE_J_SafariZoneGate_SafariZoneEntrance_hns_SafariZoneGate_SafariZoneEntrance_EventScript_Chart1::
	end

SE_J_SafariZoneGate_SafariZoneEntrance_hns_SafariZoneGate_SafariZoneEntrance_EventScript_Chart2::
	end

SafariZoneGate_SafariZoneEntrance_EventScript_Engineer::
	lock
	faceplayer
	msgbox SafariZoneGate_SafariZoneEntrance_Text_Engineer, MSGBOX_DEFAULT
	closemessage
	release
	end

SafariZoneGate_SafariZoneEntrance_Text_Engineer::
	.string "Sorry TRAINER, this area is still\n"
	.string "under construction. Check back\l"
	.string "later!$"
