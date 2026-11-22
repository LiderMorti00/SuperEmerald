MtCoronet_1F_TunnelRoom_sinnoh_MapScripts::
	.byte 0


MtCoronet_1F_TunnelRoom_EventScript_Grunt::
	trainerbattle_single TRAINER_BROOKE_3_SINNOH, MtCoronet_1F_TunnelRoom_Text_GruntIntro, MtCoronet_1F_TunnelRoom_Text_GruntDefeat
	msgbox MtCoronet_1F_TunnelRoom_Text_GruntPost, MSGBOX_AUTOCLOSE
	end

MtCoronet_1F_TunnelRoom_Text_GruntPost::
	.string "MT. CORONET…\p"
	.string "I might be just a grunt, but even I can\n"
	.string "tell it has a weird energy!$"

MtCoronet_1F_TunnelRoom_Text_GruntDefeat::
	.string "Where do you get that power?!$"

MtCoronet_1F_TunnelRoom_Text_GruntIntro::
	.string "A TRAINER? All the way down here?\n"
	.string "OK, let's see how tough you are.$"

MtCoronet_1F_TunnelRoom_EventScript_Grunt2::
	trainerbattle_single TRAINER_BROOKE_4_SINNOH, MtCoronet_1F_TunnelRoom_Text_Grunt2Intro, MtCoronet_1F_TunnelRoom_Text_Grunt2Defeat
	msgbox MtCoronet_1F_TunnelRoom_Text_Grunt2Post, MSGBOX_AUTOCLOSE
	end

MtCoronet_1F_TunnelRoom_Text_Grunt2Post::
	.string "The closer you are to the peak, the\n"
	.string "closer you are to space!\p"
	.string "I still come up here to think about\n"
	.string "what TEAM GALACTIC left behind.$"

MtCoronet_1F_TunnelRoom_Text_Grunt2Defeat::
	.string "You turned the tables on me… I call\n"
	.string "interference…$"

MtCoronet_1F_TunnelRoom_Text_Grunt2Intro::
	.string "TEAM GALACTIC may be finished, but\n"
	.string "I can still battle!$"

MtCoronet_1F_TunnelRoom_EventScript_Grunt3::
	trainerbattle_single TRAINER_BROOKE_5_SINNOH, MtCoronet_1F_TunnelRoom_Text_Grunt3Intro, MtCoronet_1F_TunnelRoom_Text_Grunt3Defeat
	msgbox MtCoronet_1F_TunnelRoom_Text_Grunt3Post, MSGBOX_AUTOCLOSE
	end

MtCoronet_1F_TunnelRoom_Text_Grunt3Post::
	.string "Someone's joy is another person's\n"
	.string "sorrow…\p"
	.string "Everyone be happy and laughing? How\n"
	.string "ridiculous!\p"
	.string "TEAM GALACTIC should be doing all the\n"
	.string "laughing!$"

MtCoronet_1F_TunnelRoom_Text_Grunt3Defeat::
	.string "See? You've left me brokenhearted,\n"
	.string "too…$"

MtCoronet_1F_TunnelRoom_Text_Grunt3Intro::
	.string "Say, listen, do you realize you're\n"
	.string "breaking hearts by being successful?\p"
	.string "Some of us still haven't moved on\n"
	.string "since TEAM GALACTIC fell.$"

MtCoronet_1F_TunnelRoom_EventScript_PtNpc1::
	msgbox MtCoronet_1F_TunnelRoom_Text_PtNpc1, MSGBOX_NPC
	end

MtCoronet_1F_TunnelRoom_Text_PtNpc1::
	.string "I used to wear a GALACTIC uniform.\p"
	.string "I come here to hike now. I knew\n"
	.string "these tunnels better than I knew\l"
	.string "what our boss was planning.\p"
	.string "Some of the others still train here.\n"
	.string "I just like the quiet.$"
