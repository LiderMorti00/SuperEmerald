SnowpointCity_House1_sinnoh_MapScripts::
	.byte 0


SnowpointCity_House1_EventScript_SNTradeGaspar_WrongT::
	.string "That’s not a {STR_VAR_1}...$"

SE_S_SnowpointCity_House1_SnowpointCity_House1_EventScript_SNTradeGaspar::
	msgbox SnowpointCity_House1_EventScript_SNTradeGaspar_WrongT, MSGBOX_NPC
	end

SnowpointCity_House1_EventScript_PtNpc2::
	msgbox SnowpointCity_House1_Text_PtNpc2, MSGBOX_NPC
	end

SnowpointCity_House1_Text_PtNpc2::
	.string "Thanks to POKéMON, we got to be\n"
	.string "friends, didn’t we?$"
