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

IronIsland_EventScript_SNRiley_T1::
	.string "...You are?\p"
	.string "OK, you’re {PLAYER}. I’m Riley.\p"
	.string "I’m a Trainer, and yes, it is a bit odd\n"
	.string "that I would be training here.\p"
	.string "Anyway, it’s always nice to meet\n"
	.string "another Trainer. Here’s a gift.$"

SE_S_IronIsland_IronIsland_EventScript_SNRiley::
	msgbox IronIsland_EventScript_SNRiley_T1, MSGBOX_NPC
	end
