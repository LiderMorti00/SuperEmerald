VeilstoneCity_PrizeExchange_sinnoh_MapScripts::
	.byte 0


VeilstoneCity_PrizeExchange_EventScript_PtNpc1::
	msgbox VeilstoneCity_PrizeExchange_Text_PtNpc1, MSGBOX_NPC
	end

VeilstoneCity_PrizeExchange_Text_PtNpc1::
	.string "Welcome!\p"
	.string "You may exchange your Coins for\n"
	.string "fabulous prizes here!$"

VeilstoneCity_PrizeExchange_EventScript_PtNpc2::
	msgbox VeilstoneCity_PrizeExchange_Text_PtNpc2, MSGBOX_NPC
	end

VeilstoneCity_PrizeExchange_Text_PtNpc2::
	.string "I used to be able to tell what type\n"
	.string "a POKéMON's Hidden Power would be.\p"
	.string "…But lately my own hidden power has\n"
	.string "gone quiet. How sad!$"

VeilstoneCity_PrizeExchange_EventScript_PtNpc3::
	lock
	faceplayer
	msgbox VeilstoneCity_PrizeExchange_Text_PtNpc3_0, MSGBOX_DEFAULT
	release
	end

VeilstoneCity_PrizeExchange_Text_PtNpc3_0::
	.string "They have prizes I really want. But\n"
	.string "Coins, I have none!$"
