IronIsland_sinnoh_MapScripts::
	.byte 0


IronIsland_EventScript_SailorBack::
	lock
	faceplayer
	msgbox IronIsland_Text_SailorBack, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, IronIsland_EventScript_SailorBackNo
	msgbox CanalaveCity_Text_SailorAllAboard, MSGBOX_DEFAULT
	closemessage
	warp MAP_CANALAVE_CITY_SINNOH, 15, 47
	waitstate
	release
	end

IronIsland_EventScript_SailorBackNo::
	release
	end

IronIsland_Text_SailorBack::
	.string "Shall we head back to\n"
	.string "CANALAVE CITY?$"

IronIsland_EventScript_SNRiley::
	lock
	faceplayer
	msgbox IronIsland_EventScript_SNRiley_T1, MSGBOX_DEFAULT
	giveitem ITEM_HM_STRENGTH
	setflag FLAG_SN_RECEIVED_HM_STRENGTH
	goto_if_set FLAG_SINNOH_BADGE6_GET, IronIsland_EventScript_SNRiley_HasBadge
	msgbox IronIsland_EventScript_SNRiley_T2, MSGBOX_DEFAULT
	goto IronIsland_EventScript_SNRiley_Leave

IronIsland_EventScript_SNRiley_Leave::
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	setflag FLAG_SN_HIDE_IRON_RILEY
	fadescreen FADE_FROM_BLACK
	release
	end

IronIsland_EventScript_SNRiley_T2::
	.string "Riley: That Hidden Machine contains\n"
	.string "the move Strength.\p"
	.string "To use it out of battle, you need the\n"
	.string "Mine Badge from Canalave Gym.\p"
	.string "I’ll be training inside. You can join me\n"
	.string "if you’d like.$"

IronIsland_EventScript_SNRiley_HasBadge::
	msgbox IronIsland_EventScript_SNRiley_T3, MSGBOX_DEFAULT
	goto IronIsland_EventScript_SNRiley_Leave

IronIsland_EventScript_SNRiley_T3::
	.string "Riley: That Hidden Machine contains\n"
	.string "the move Strength.\p"
	.string "To use it out of battle, you need the\n"
	.string "Badge from Canalave Gym...\p"
	.string "Oh, never mind, you’ve already got the\n"
	.string "Mine Badge. My bad.\p"
	.string "I’ll be training inside. You can join me\n"
	.string "if you’d like.$"

IronIsland_EventScript_SNRiley_T1::
	.string "...You are?\p"
	.string "OK, you’re {PLAYER}. I’m Riley.\p"
	.string "I’m a Trainer, and yes, it is a bit odd\n"
	.string "that I would be training here.\p"
	.string "Anyway, it’s always nice to meet\n"
	.string "another Trainer. Here’s a gift.$"
