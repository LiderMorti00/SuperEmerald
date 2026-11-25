GoldenrodCity_RadioTower_3F_hns_MapScripts::
	.byte 0

GoldenrodCity_RadioTower_3F_Text_CooltrainerFPleaseSave::
	.string "ARCHER of TEAM ROCKET went up to\n"
	.string "the fifth floor!\p"
	.string "He's taken over the broadcast\n"
	.string "room. Please hurry!$"

SE_J_GoldenrodCity_RadioTower_3F_hns_GoldenrodCity_RadioTower_3F_EventScript_Cooltrainer::
	goto_if_ne VAR_SE_ROCKET_QUEST, 3, SE_RadioTower3F_Calm_Script
	msgbox GoldenrodCity_RadioTower_3F_Text_CooltrainerFPleaseSave, MSGBOX_NPC
	end

GoldenrodCity_RadioTower_3F_EventScript_Nerd::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_3F_Text_SuperNerd, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_Text_SuperNerd::
	.string "We have recordings of the cries of\n"
	.string "all POKéMON that have been found.\p"
	.string "We must have over a thousand kinds.$"

GoldenrodCity_RadioTower_3F_EventScript_Sign2::
	lock
	msgbox GoldenrodCity_RadioTower_3F_Text_PokemonMusicSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_Text_PokemonMusicSign::
	.string "POKéMON MUSIC with Host DJ BEN$"

GoldenrodCity_RadioTower_3F_EventScript_Sign1::
	lock
	msgbox GoldenrodCity_RadioTower_3F_Text_PersonnelSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_Text_PersonnelSign::
	.string "3F PERSONNEL$"

GoldenrodCity_RadioTower_3F_EventScript_Gate::
	lock
	msgbox GoldenrodCity_RadioTower_3F_Text_CardKeySlot, MSGBOX_SIGN
	goto_if_set FLAG_HIDE_RADIOTOWER_GATE, GoldenrodCity_RadioTower_3F_EventScript_GateOpened
	checkitem ITEM_CARD_KEY
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_RadioTower_3F_EventScript_OpenGate
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_OpenGate::
	msgbox GoldenrodCity_RadioTower_3F_Text_InsertedCardKey, MSGBOX_SIGN
	call GoldenrodCity_RadioTower_3F_HideGate
	playse SE_CLICK
	special DrawWholeMapView
	msgbox GoldenrodCity_RadioTower_3F_Text_Open, MSGBOX_SIGN
	setflag FLAG_HIDE_RADIOTOWER_GATE
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_Text_Open::
	.string "The gate is open.$"

GoldenrodCity_RadioTower_3F_HideGate::
	setmetatile 25, 8, 0x335, FALSE
	setmetatile 25, 9, 0x335, FALSE

	setmetatile 26, 8, 0X334, FALSE
	setmetatile 26, 9, 0X334, FALSE

	setmetatile 27, 8, 0X334, FALSE
	setmetatile 27, 9, 0X334, FALSE

	setmetatile 28, 8, 0X334, FALSE
	setmetatile 28, 9, 0X334, FALSE

	setmetatile 29, 8, 0X334, FALSE
	setmetatile 29, 9, 0X334, FALSE

	setmetatile 30, 8, 0X334, FALSE
	setmetatile 30, 9, 0X334, FALSE

	setmetatile 31, 8, 0X334, FALSE
	setmetatile 31, 9, 0X334, FALSE
	return

GoldenrodCity_RadioTower_3F_Text_InsertedCardKey::
	.string "{PLAYER} inserted the CARD KEY.$"

GoldenrodCity_RadioTower_3F_EventScript_GateOpened::
	msgbox GoldenrodCity_RadioTower_3F_Text_Open, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_Text_CardKeySlot::
	.string "It's the CARD KEY slot.$"

SE_RadioTower3F_Calm_Script::
	msgbox SE_RadioTower3F_Calm_Text, MSGBOX_NPC
	end

SE_RadioTower3F_Calm_Text::
	.string "TEAM ROCKET took over this tower\n"
	.string "once. What a scare that was!\p"
	.string "Now it's back to business as usual.$"
