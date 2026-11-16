EternaCity_Flat1_F1_sinnoh_MapScripts::
	.byte 0


EternaCity_Flat1_F1_EventScript_SNTradeCharap_WrongT::
	.string "That’s not a {STR_VAR_1}...$"

SE_S_EternaCity_Flat1_F1_EternaCity_Flat1_F1_EventScript_SNTradeCharap::
	msgbox EternaCity_Flat1_F1_EventScript_SNTradeCharap_WrongT, MSGBOX_NPC
	end

EternaCity_Flat1_F1_EventScript_PtNpc2::
	msgbox EternaCity_Flat1_F1_Text_PtNpc2, MSGBOX_NPC
	end

EternaCity_Flat1_F1_Text_PtNpc2::
	.string "Hi! I'm the building superintendent. I\n"
	.string "maintain a vigilant 24-hour watch!$"
