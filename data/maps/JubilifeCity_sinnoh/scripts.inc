JubilifeCity_sinnoh_MapScripts::
	.byte 0


JubilifeCity_EventScript_PtNpc1::
	msgbox JubilifeCity_Text_PtNpc1, MSGBOX_NPC
	end

JubilifeCity_Text_PtNpc1::
	.string "When you walk with your POKéMON, they\n"
	.string "gradually grow friendlier.$"

JubilifeCity_EventScript_PtNpc2::
	msgbox JubilifeCity_Text_PtNpc2, MSGBOX_NPC
	end

JubilifeCity_Text_PtNpc2::
	.string "Hiya, where'd you come from?\p"
	.string "...\p"
	.string "TWINLEAF TOWN, huh... It's a nice place.\n"
	.string "Quiet and all.\p"
	.string "JUBILIFE CITY is a big place, so it\n"
	.string "might be a bit of a shock to you.$"

JubilifeCity_EventScript_PtNpc3::
	msgbox JubilifeCity_Text_PtNpc3, MSGBOX_NPC
	end

JubilifeCity_Text_PtNpc3::
	.string "The TRAINERS' SCHOOL is where I\n"
	.string "learned everything I know!$"

JubilifeCity_EventScript_PtNpc4::
	msgbox JubilifeCity_Text_PtNpc4, MSGBOX_NPC
	end

JubilifeCity_Text_PtNpc4::
	.string "Did you see me on TV? I was in an\n"
	.string "interview!$"

JubilifeCity_EventScript_PtNpc5::
	lock
	faceplayer
	msgbox JubilifeCity_Text_PtNpc5, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, JubilifeCity_EventScript_PtNpc5_No
	msgbox JubilifeCity_Text_PtNpc5_Yes, MSGBOX_DEFAULT
	release
	end

JubilifeCity_Text_PtNpc5_Yes::
	.string "Ah, I see! You are knowledgeable!\p"
	.string "I imagine you wouldn't see the need to\n"
	.string "visit the Trainers' School, then.\p"
	.string "But do visit if you have the time. You\n"
	.string "may discover something new!$"

JubilifeCity_EventScript_PtNpc5_No::
	msgbox JubilifeCity_Text_PtNpc5_No, MSGBOX_DEFAULT
	release
	end

JubilifeCity_Text_PtNpc5_No::
	.string "Oh, you're not knowledgeable... But not\n"
	.string "to worry!\p"
	.string "There's the Trainers' School.\p"
	.string "The school will teach you the basics\n"
	.string "of POKéMON.$"

JubilifeCity_Text_PtNpc5::
	.string "Hello, Trainer! Do you know much about\n"
	.string "POKéMON?$"

JubilifeCity_EventScript_PtNpc6::
	msgbox JubilifeCity_Text_PtNpc6, MSGBOX_NPC
	end

JubilifeCity_Text_PtNpc6::
	.string "OK, set six POKé BALLS in my belt...\p"
	.string "Yeah, that'll do it. At most, you can\n"
	.string "have six POKéMON with you.$"

JubilifeCity_EventScript_PtNpc7::
	lock
	faceplayer
	goto_if_set FLAG_SINNOH_BADGE1_GET, JubilifeCity_EventScript_PtNpc7_SNVar0
	msgbox JubilifeCity_Text_PtNpc7, MSGBOX_DEFAULT
	release
	end

JubilifeCity_Text_PtNpc7::
	.string "JUBILIFE CITY's built on land they\n"
	.string "carved out of a mountain.\p"
	.string "The people and POKéMON of OREBURGH\n"
	.string "CITY helped out with that\l"
	.string "undertaking.$"

JubilifeCity_EventScript_PtNpc7_SNVar0::
	msgbox JubilifeCity_Text_PtNpc7_SNVar0, MSGBOX_DEFAULT
	release
	end

JubilifeCity_Text_PtNpc7_SNVar0::
	.string "Hello! Let me ask you, have you paid a\n"
	.string "visit to the TV station?\p"
	.string "If you’ve never been, you owe it to\n"
	.string "yourself to make the trip.\p"
	.string "And, if you’ve been there before, it\n"
	.string "never hurts to visit again.\p"
	.string "After all, you can be a star! Or at\n"
	.string "least dream of being one!$"

JubilifeCity_EventScript_PtNpc8::
	msgbox JubilifeCity_Text_PtNpc8, MSGBOX_NPC
	end

JubilifeCity_Text_PtNpc8::
	.string "Want to battle? Just kidding! I'm\n"
	.string "waiting for a friend.$"

JubilifeCity_EventScript_PtNpc9::
	msgbox JubilifeCity_Text_PtNpc9, MSGBOX_NPC
	end

JubilifeCity_Text_PtNpc9::
	.string "Trading POKéMON means connecting\n"
	.string "with friends, both old and new.\p"
	.string "That's awesome!$"

JubilifeCity_EventScript_PtNpc10::
	msgbox JubilifeCity_Text_PtNpc10, MSGBOX_NPC
	end

JubilifeCity_Text_PtNpc10::
	.string "I'm trading POKéMON with my buddy!$"

JubilifeCity_EventScript_PtNpc11::
	msgbox JubilifeCity_Text_PtNpc11, MSGBOX_NPC
	end

JubilifeCity_Text_PtNpc11::
	.string "I made my POKéMON hold an item before\n"
	.string "trading it.\p"
	.string "That will make the other Trainer\n"
	.string "double happy!$"

JubilifeCity_EventScript_Dawn::
	msgbox JubilifeCity_Text_SNJFollowD, MSGBOX_NPC
	end

JubilifeCity_Text_SNJFollowD::
	.string "Oh, I know! Don’t you think it’s better\n"
	.string "to know more about POKéMON?\p"
	.string "Sure it is! I know just the place.\p"
	.string "Come on! Don’t be shy. Follow me!$"

JubilifeCity_EventScript_Clown1::
	lock
	faceplayer
	checkitem ITEM_COUPON_1
	goto_if_eq VAR_RESULT, TRUE, JubilifeCity_EventScript_ClownDone
	goto_if_set FLAG_SYS_POKENAV_GET, JubilifeCity_EventScript_ClownDone
	msgbox JubilifeCity_Text_ClownQuiz1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, JubilifeCity_EventScript_ClownWrong
	msgbox JubilifeCity_Text_ClownRight, MSGBOX_DEFAULT
	giveitem ITEM_COUPON_1
	goto JubilifeCity_EventScript_ClownRight

JubilifeCity_EventScript_ClownRight::
	msgbox JubilifeCity_Text_ClownRight2, MSGBOX_DEFAULT
	release
	end

JubilifeCity_Text_ClownRight2::
	.string "Collect all three COUPONS and\n"
	.string "bring them to the POKéNAV\l"
	.string "COMPANY's president!$"

JubilifeCity_Text_ClownRight::
	.string "Correct! Here's your COUPON!$"

JubilifeCity_EventScript_ClownWrong::
	msgbox JubilifeCity_Text_ClownWrong, MSGBOX_DEFAULT
	release
	end

JubilifeCity_Text_ClownWrong::
	.string "Ooh, so close! Think it over and\n"
	.string "try again!$"

JubilifeCity_Text_ClownQuiz1::
	.string "POKéNAV campaign quiz! Answer\n"
	.string "correctly to win a COUPON!\p"
	.string "Does a POKéMON grow by defeating\n"
	.string "others and gaining EXP. Points?$"

JubilifeCity_EventScript_ClownDone::
	msgbox JubilifeCity_Text_ClownDone, MSGBOX_DEFAULT
	release
	end

JubilifeCity_Text_ClownDone::
	.string "You already have my COUPON! Go\n"
	.string "find the others!$"

JubilifeCity_EventScript_Clown2::
	lock
	faceplayer
	checkitem ITEM_COUPON_2
	goto_if_eq VAR_RESULT, TRUE, JubilifeCity_EventScript_ClownDone
	goto_if_set FLAG_SYS_POKENAV_GET, JubilifeCity_EventScript_ClownDone
	msgbox JubilifeCity_Text_ClownQuiz2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, JubilifeCity_EventScript_ClownWrong
	msgbox JubilifeCity_Text_ClownRight, MSGBOX_DEFAULT
	giveitem ITEM_COUPON_2
	goto JubilifeCity_EventScript_ClownRight

JubilifeCity_Text_ClownQuiz2::
	.string "POKéNAV campaign quiz time!\p"
	.string "Just like POKéMON have types, do\n"
	.string "moves have types too?$"

JubilifeCity_EventScript_Clown3::
	lock
	faceplayer
	checkitem ITEM_COUPON_3
	goto_if_eq VAR_RESULT, TRUE, JubilifeCity_EventScript_ClownDone
	goto_if_set FLAG_SYS_POKENAV_GET, JubilifeCity_EventScript_ClownDone
	msgbox JubilifeCity_Text_ClownQuiz3, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, JubilifeCity_EventScript_ClownWrong
	msgbox JubilifeCity_Text_ClownRight, MSGBOX_DEFAULT
	giveitem ITEM_COUPON_3
	goto JubilifeCity_EventScript_ClownRight

JubilifeCity_Text_ClownQuiz3::
	.string "Last POKéNAV campaign quiz! Ready?\p"
	.string "Can a POKéMON hold an item?$"

JubilifeCity_EventScript_Rowan::


JubilifeCity_EventScript_Looker::
	lock
	faceplayer
	msgbox JubilifeCity_Text_Looker, MSGBOX_DEFAULT
	release
	end

JubilifeCity_Text_Looker::
	.string "Looker: Hello, my friend. Have you\n"
	.string "visited the Trainers’ School?\p"
	.string "Did your friend not guide you there\n"
	.string "earlier?$"

JubilifeCity_EventScript_President::
	lock
	faceplayer
	goto_if_set FLAG_SYS_POKENAV_GET, JubilifeCity_EventScript_PresidentAfter
	checkitem ITEM_COUPON_1
	goto_if_eq VAR_RESULT, FALSE, JubilifeCity_EventScript_PresidentNoCoupons
	checkitem ITEM_COUPON_2
	goto_if_eq VAR_RESULT, FALSE, JubilifeCity_EventScript_PresidentNoCoupons
	checkitem ITEM_COUPON_3
	goto_if_eq VAR_RESULT, FALSE, JubilifeCity_EventScript_PresidentNoCoupons
	msgbox JubilifeCity_Text_PresidentCoupons, MSGBOX_DEFAULT
	removeitem ITEM_COUPON_1
	removeitem ITEM_COUPON_2
	removeitem ITEM_COUPON_3
	playfanfare MUS_OBTAIN_ITEM
	message JubilifeCity_Text_ReceivedPokenav
	waitfanfare
	waitmessage
	setflag FLAG_SYS_POKENAV_GET
	setflag FLAG_SN_RECEIVED_POKENAV
	call_if_eq VAR_SN_SINNOH_STORY, 15, JubilifeCity_EventScript_SetStory16
	msgbox JubilifeCity_Text_PresidentPokenav, MSGBOX_DEFAULT
	release
	end

JubilifeCity_Text_PresidentPokenav::
	.string "The POKéNAV has a map and much\n"
	.string "more. It will help you on your\l"
	.string "journey!$"

JubilifeCity_EventScript_SetStory16::
	setvar VAR_SN_SINNOH_STORY, 16
	return

JubilifeCity_Text_ReceivedPokenav::
	.string "{PLAYER} received the POKéNAV!$"

JubilifeCity_Text_PresidentCoupons::
	.string "Wonderful! You found all three\n"
	.string "COUPONS! Here's your prize!$"

JubilifeCity_EventScript_PresidentNoCoupons::
	msgbox JubilifeCity_Text_PresidentNoCoupons, MSGBOX_DEFAULT
	release
	end

JubilifeCity_Text_PresidentNoCoupons::
	.string "Find all three clowns and bring me\n"
	.string "their COUPONS. They're somewhere\l"
	.string "in JUBILIFE!$"

JubilifeCity_EventScript_PresidentAfter::
	msgbox JubilifeCity_Text_PresidentAfter, MSGBOX_DEFAULT
	release
	end

JubilifeCity_Text_PresidentAfter::
	.string "How do you like your POKéNAV? Use\n"
	.string "it well!$"

JubilifeCity_EventScript_Sign10::
	msgbox JubilifeCity_Text_Sign10, MSGBOX_SIGN
	end

JubilifeCity_Text_Sign10::
	.string "JUBILIFE CITY\p"
	.string "The most modern city in Sinnoh.$"

JubilifeCity_EventScript_Sign8::
	msgbox JubilifeCity_Text_Sign8, MSGBOX_SIGN
	end

JubilifeCity_Text_Sign8::
	.string "TRAINERS' SCHOOL\p"
	.string "Learn the basics of POKéMON\n"
	.string "battling!$"

JubilifeCity_EventScript_Sign2::
	msgbox JubilifeCity_Text_Sign2, MSGBOX_SIGN
	end

JubilifeCity_Text_Sign2::
	.string "POKéNAV COMPANY\p"
	.string "Making life easier for Trainers\n"
	.string "everywhere.$"

JubilifeCity_EventScript_Sign3::
	msgbox JubilifeCity_Text_Sign3, MSGBOX_SIGN
	end

JubilifeCity_Text_Sign3::
	.string "JUBILIFE TV\p"
	.string "Broadcasting across all of Sinnoh.$"

JubilifeCity_EventScript_Sign1::
	msgbox JubilifeCity_Text_Sign1, MSGBOX_SIGN
	end

JubilifeCity_Text_Sign1::
	.string "JUBILIFE CITY\p"
	.string "The most modern city in Sinnoh.$"

JubilifeCity_EventScript_Sign5::
	msgbox JubilifeCity_Text_Sign5, MSGBOX_SIGN
	end

JubilifeCity_Text_Sign5::
	.string "JUBILIFE CITY\p"
	.string "The most modern city in Sinnoh.$"

JubilifeCity_EventScript_Sign6::
	msgbox JubilifeCity_Text_Sign6, MSGBOX_SIGN
	end

JubilifeCity_Text_Sign6::
	.string "JUBILIFE CITY\p"
	.string "The most modern city in Sinnoh.$"

JubilifeCity_EventScript_Sign7::
	msgbox JubilifeCity_Text_Sign7, MSGBOX_SIGN
	end

JubilifeCity_Text_Sign7::
	.string "JUBILIFE CITY\p"
	.string "The most modern city in Sinnoh.$"

JubilifeCity_EventScript_Sign4::
	msgbox JubilifeCity_Text_Sign4, MSGBOX_SIGN
	end

JubilifeCity_Text_Sign4::
	.string "CONDOMINIUMS$"

JubilifeCity_EventScript_Sign9::
	msgbox JubilifeCity_Text_Sign9, MSGBOX_SIGN
	end

JubilifeCity_Text_Sign9::
	.string "JUBILIFE CITY\p"
	.string "The most modern city in Sinnoh.$"
