ResortArea_RibbonSyndicate_F2_sinnoh_MapScripts::
	.byte 0


ResortArea_RibbonSyndicate_F2_Text_SNSpaAsk::
	.string "How may we serve you today? Perhaps a\n"
	.string "spa treatment?\p"
	.string "Our spa treatment will make your\n"
	.string "{STR_VAR_1} grow more friendly.\p"
	.string "Would you care to have a spa\n"
	.string "treatment, {PLAYER}?$"

SE_S_ResortArea_RibbonSyndicate_F2_ResortArea_RibbonSyndicate_F2_EventScript_SNSpa::
	msgbox ResortArea_RibbonSyndicate_F2_Text_SNSpaAsk, MSGBOX_NPC
	end

ResortArea_RibbonSyndicate_F2_EventScript_PtNpc2::
	lock
	faceplayer
	msgbox ResortArea_RibbonSyndicate_F2_Text_PtNpc2_0, MSGBOX_DEFAULT
	release
	end

ResortArea_RibbonSyndicate_F2_Text_PtNpc2_0::
	.string "Our service is very exclusive. We only\n"
	.string "accept five members a day.$"

ResortArea_RibbonSyndicate_F2_EventScript_PtNpc3::
	msgbox ResortArea_RibbonSyndicate_F2_Text_PtNpc3, MSGBOX_NPC
	end

ResortArea_RibbonSyndicate_F2_Text_PtNpc3::
	.string "Oh, I do apologize.\p"
	.string "We can only provide one spa session a\n"
	.string "day to our members.$"

ResortArea_RibbonSyndicate_F2_EventScript_PtNpc4::
	lock
	faceplayer
	msgbox ResortArea_RibbonSyndicate_F2_Text_PtNpc4_0, MSGBOX_DEFAULT
	release
	end

ResortArea_RibbonSyndicate_F2_Text_PtNpc4_0::
	.string "We’ve developed a reputation for\n"
	.string "bringing our members closer to\p"
	.string "their POKéMON.$"
