SSAqua_CaptainsRoom_hns_MapScripts::
	.byte 0


SSAqua_CaptainsRoom_EventScript_Captain::
	msgbox SSAqua_CaptainsRoom_Text_CaptainHowDoYouLike, MSGBOX_NPC
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
