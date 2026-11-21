Twinleaf_Town_RivalsHouse_F1_sinnoh_MapScripts::
	.byte 0


Twinleaf_Town_RivalsHouse_F1_EventScript_PtNpc1::
	lock
	faceplayer
	goto_if_lt VAR_SN_SINNOH_STORY, 2, Twinleaf_Town_RivalsHouse_F1_EventScript_PtNpc1_S0
	goto_if_lt VAR_SN_SINNOH_STORY, 4, Twinleaf_Town_RivalsHouse_F1_EventScript_PtNpc1_S1
	goto_if_unset FLAG_SINNOH_BADGE1_GET, Twinleaf_Town_RivalsHouse_F1_EventScript_PtNpc1_S2
	msgbox Twinleaf_Town_RivalsHouse_F1_Text_SNTookOff, MSGBOX_DEFAULT
	release
	end

Twinleaf_Town_RivalsHouse_F1_Text_SNTookOff::
	.string "{RIVAL}’s mom: My {RIVAL} took\n"
	.string "off like a rocket as usual.\p"
	.string "He was shouting something about\n"
	.string "becoming the greatest TRAINER ever...\p"
	.string "He just can’t sit still, that boy. I\n"
	.string "wonder who he takes after?$"

Twinleaf_Town_RivalsHouse_F1_EventScript_PtNpc1_S2::
	msgbox Twinleaf_Town_RivalsHouse_F1_Text_SNFriends, MSGBOX_DEFAULT
	release
	end

Twinleaf_Town_RivalsHouse_F1_Text_SNFriends::
	.string "{RIVAL}’s mom: Oh, you’ve become\n"
	.string "friends with a POKéMON, too.$"

Twinleaf_Town_RivalsHouse_F1_EventScript_PtNpc1_S1::
	msgbox Twinleaf_Town_RivalsHouse_F1_Text_SNRocketed, MSGBOX_DEFAULT
	release
	end

Twinleaf_Town_RivalsHouse_F1_Text_SNRocketed::
	.string "{RIVAL}’s mom: That kid rocketed off\n"
	.string "again like usual.\p"
	.string "I’d guess he would be out on ROUTE 201\n"
	.string "by now?\p"
	.string "He just can’t sit still, that boy. I\n"
	.string "wonder who he takes after?$"

Twinleaf_Town_RivalsHouse_F1_EventScript_PtNpc1_S0::
	msgbox Twinleaf_Town_RivalsHouse_F1_Text_SNLooking, MSGBOX_DEFAULT
	release
	end

Twinleaf_Town_RivalsHouse_F1_Text_SNLooking::
	.string "{RIVAL}’s mom: Oh, hello! You're the\n"
	.string "TRAINER from HOENN, aren't you?\p"
	.string "Are you looking for {RIVAL}?\p"
	.string "He was gone for a second, but then he\n"
	.string "came running right back home.\p"
	.string "He just can’t sit still, that boy. I\n"
	.string "wonder who he takes after?$"
