SnowpointCity_sinnoh_MapScripts::
	.byte 0

SnowpointCity_EventScript_FerrySailor::
	lock
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, SnowpointCity_EventScript_FerryNotYet
	msgbox SnowpointCity_Text_SailToBattleZone, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SnowpointCity_EventScript_FerryNo
	msgbox SnowpointCity_Text_LetsSetSail, MSGBOX_DEFAULT
	closemessage
	warp MAP_FIGHT_AREA_SINNOH, 19, 18
	waitstate
	release
	end

SnowpointCity_Text_LetsSetSail::
	.string "Aye, aye, then! Let's set sail!$"

SnowpointCity_EventScript_FerryNo::
	msgbox SnowpointCity_Text_PtNpc1, MSGBOX_DEFAULT
	release
	end

SnowpointCity_Text_PtNpc1::
	.string "There is nothing exceptional here.\n"
	.string "That makes SNOWPOINT unique.\p"
	.string "There's nothing exceptional about me.\n"
	.string "That's what makes me stand out!$"

SnowpointCity_Text_SailToBattleZone::
	.string "What is it? Do you want to sail to the\n"
	.string "FIGHT AREA?$"

SnowpointCity_EventScript_FerryNotYet::
	msgbox SnowpointCity_Text_GreatTrainer, MSGBOX_DEFAULT
	release
	end

SnowpointCity_Text_GreatTrainer::
	.string "A great TRAINER recognized by the\n"
	.string "POKéMON LEAGUE…\p"
	.string "I look forward to carrying someone like\n"
	.string "that on this ship!$"

SnowpointCity_EventScript_PtNpc2::
	lock
	faceplayer
	msgbox SnowpointCity_Text_PtNpc2_0, MSGBOX_DEFAULT
	release
	end

SnowpointCity_Text_PtNpc2_0::
	.string "Brrr… This snowbound town is always\n"
	.string "freezing cold.\p"
	.string "But the spirits of the TRAINERS and\n"
	.string "their POKéMON burn hot and bright.\p"
	.string "Especially the GYM LEADER.$"

SnowpointCity_EventScript_PtNpc3::
	lock
	faceplayer
	msgbox SnowpointCity_Text_PtNpc3_0, MSGBOX_DEFAULT
	release
	end

SnowpointCity_Text_PtNpc3_0::
	.string "Your scarf looks nice and warm. I wish I\n"
	.string "had one like it.$"

SnowpointCity_EventScript_PtNpc4::
	msgbox SnowpointCity_Text_PtNpc4, MSGBOX_NPC
	end

SnowpointCity_Text_PtNpc4::
	.string "Only the chosen may enter the\n"
	.string "SNOWPOINT TEMPLE.\p"
	.string "…You're the CHAMPION from HOENN?\n"
	.string "Then you may pass. Take care inside.$"

SnowpointCity_EventScript_PtNpc5::
	lock
	faceplayer
	msgbox SnowpointCity_Text_PtNpc5_0, MSGBOX_DEFAULT
	release
	end

SnowpointCity_Text_PtNpc5_0::
	.string "CANDICE is teaching me about POKéMON.\p"
	.string "She says I have to start by making\n"
	.string "friends with POKéMON.$"

SnowpointCity_EventScript_SNPtSNOWPOINTNPCM::
	msgbox SnowpointCity_EventScript_SNPtSNOWPOINTNPCM_Text, MSGBOX_NPC
	end

SnowpointCity_EventScript_SNPtSNOWPOINTNPCM_Text::
	.string "POKéMON are said to have dragged\n"
	.string "SNOWPOINT CITY here.\p"
	.string "The SNOWPOINT TEMPLE is their resting\n"
	.string "place, they say.\p"
	.string "I want to take a look around in the\n"
	.string "SNOWPOINT TEMPLE.\p"
	.string "But only really tough TRAINERS are\n"
	.string "allowed inside.$"

SnowpointCity_EventScript_PtSign1::
	msgbox SnowpointCity_Text_PtSign1, MSGBOX_SIGN
	end

SnowpointCity_Text_PtSign1::
	.string "SNOWPOINT CITY City of Snow$"

SnowpointCity_EventScript_PtSign2::
	msgbox SnowpointCity_Text_PtSign2, MSGBOX_SIGN
	end

SnowpointCity_Text_PtSign2::
	.string "SNOWPOINT CITY POKéMON GYM LEADER:\n"
	.string "CANDICE The Diamond Dust Girl!$"
