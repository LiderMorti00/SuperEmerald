EternaCity_Flat1_F1_sinnoh_MapScripts::
	.byte 0


EternaCity_Flat1_F1_EventScript_SNTradeCharap::
	lock
	faceplayer
	goto_if_set FLAG_SN_TRADE_CHARAP, EternaCity_Flat1_F1_EventScript_SNTradeCharap_Done
	ingame_trade INGAME_TRADE_CHARAP, EternaCity_Flat1_F1_EventScript_SNTradeCharap_Ask, EternaCity_Flat1_F1_EventScript_SNTradeCharap_No, EternaCity_Flat1_F1_EventScript_SNTradeCharap_Wrong, EternaCity_Flat1_F1_EventScript_SNTradeCharap_Thanks
	setflag FLAG_SN_TRADE_CHARAP
	release
	end

EternaCity_Flat1_F1_EventScript_SNTradeCharap_Thanks::
	.string "Thank you! Please take good care of my\n"
	.string "POKéMON!$"

EternaCity_Flat1_F1_EventScript_SNTradeCharap_Wrong::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox EternaCity_Flat1_F1_EventScript_SNTradeCharap_WrongT, MSGBOX_DEFAULT
	release
	end

EternaCity_Flat1_F1_EventScript_SNTradeCharap_WrongT::
	.string "That's not a {STR_VAR_1}…$"

EternaCity_Flat1_F1_EventScript_SNTradeCharap_No::
	msgbox EternaCity_Flat1_F1_EventScript_SNTradeCharap_NoT, MSGBOX_DEFAULT
	release
	end

EternaCity_Flat1_F1_EventScript_SNTradeCharap_NoT::
	.string "Oh… That's too bad.$"

EternaCity_Flat1_F1_EventScript_SNTradeCharap_Ask::
	.string "Do you have a {STR_VAR_1}? Would you\n"
	.string "trade it for my {STR_VAR_2}?$"

EternaCity_Flat1_F1_EventScript_SNTradeCharap_Done::
	msgbox EternaCity_Flat1_F1_EventScript_SNTradeCharap_DoneT, MSGBOX_DEFAULT
	release
	end

EternaCity_Flat1_F1_EventScript_SNTradeCharap_DoneT::
	.string "Our POKéMON are getting along great\n"
	.string "with their new TRAINERS, don't you\l"
	.string "think?$"

EternaCity_Flat1_F1_EventScript_PtNpc2::
	msgbox EternaCity_Flat1_F1_Text_PtNpc2, MSGBOX_NPC
	end

EternaCity_Flat1_F1_Text_PtNpc2::
	.string "Hi! I'm the building superintendent. I\n"
	.string "maintain a vigilant 24-hour watch!$"
