SSAqua_CaptainsRoom_hns_MapScripts::
	.byte 0


SSAqua_CaptainsRoom_EventScript_Captain::
	goto_if_eq VAR_TEMP_0, 1, SSAqua_CaptainsRoom_EventScrip_CaptainAfter
	msgbox SSAqua_CaptainsRoom_Text_CaptainExhausting, MSGBOX_NPC
	setvar VAR_TEMP_0, 1
	goto SSAqua_CaptainsRoom_EventScrip_CaptainAfter

SSAqua_CaptainsRoom_Text_CaptainExhausting::
	.string "Whew! Thanks for coming along.\p"
	.string "Keeping that little girl amused\n"
	.string "was exhausting.$"

SSAqua_CaptainsRoom_EventScrip_CaptainAfter::
	msgbox SSAqua_CaptainsRoom_Text_CaptainHowDoYouLike, MSGBOX_DEFAULT
	closemessage
	end

SSAqua_CaptainsRoom_Text_CaptainHowDoYouLike::
	.string "How do you like S.S.AQUA's ride?\p"
	.string "She practically skates across\n"
	.string "the waves.$"

SSAqua_CaptainsRoom_Text_GranddaughterCaptainPlayWithMe::
	.string "CAPTAIN, play with me, please?\p"
	.string "I'm bored! I want to play more!$"

SE_J_SSAqua_CaptainsRoom_hns_SSAqua_CaptainsRoom_EventScript_Granddaughter::
	msgbox SSAqua_CaptainsRoom_Text_GranddaughterCaptainPlayWithMe, MSGBOX_NPC
	end
