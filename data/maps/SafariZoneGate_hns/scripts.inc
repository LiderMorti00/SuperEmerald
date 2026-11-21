SafariZoneGate_hns_MapScripts::
	.byte 0


SafariZoneGate_EventScript_Silent::
	lock
	faceplayer
	msgbox SafariZone_Text_SilentNPC, MSGBOX_DEFAULT
	closemessage
	release
	end

SafariZone_Text_SilentNPC::
	.string "………………\p"
	.string "(I am not a talker.)$"

SE_J_SafariZoneGate_hns_SafariZoneGate_EventScript_IncenseClerk::
	msgbox gText_HowMayIServeYou, MSGBOX_NPC
	end

SafariZoneGate_EventScript_VitaminGuru::
	lock
	faceplayer
	message SafariZoneGate_Text_VitaminGuruSellWhatYouNeed
	waitmessage
	pokemart SafariZoneGate_Pokemart_VitaminGuru
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2

SafariZoneGate_Pokemart_VitaminGuru::
	.2byte ITEM_PROTEIN
	.2byte ITEM_IRON
	.2byte ITEM_CARBOS
	.2byte ITEM_ZINC
	.2byte ITEM_CALCIUM
	.2byte ITEM_HP_UP
	.2byte ITEM_NONE
	release
	end

SafariZoneGate_Text_VitaminGuruSellWhatYouNeed::
	.string "I'm the ENERGY GURU! I'll go for it and\n"
	.string "sell you what you need!$"

SafariZoneGate_EventScript_SlowpokeLady::
	lock
	faceplayer
	msgbox SafariZone_Text_SlowpokeFan, MSGBOX_DEFAULT
	closemessage
	release
	end

SafariZone_Text_SlowpokeFan::
	.string "There are many POKéMON to choose from,\n"
	.string "but nothing beats the cuteness of\l"
	.string "SLOWPOKE.\p"
	.string "People often say that I look like one!$"

SafariZoneGate_EventScript_WorkerM::
	lock
	faceplayer
	msgbox SafariZone_Text_ForeignFeeling, MSGBOX_DEFAULT
	closemessage
	release
	end

SafariZone_Text_ForeignFeeling::
	.string "SAFARI ZONE…\n"
	.string "It makes me feel like I am in a\l"
	.string "foreign country.\p"
	.string "It brings up a strange feeling.$"

SafariZoneGate_EventScript_Girl::
	lock
	faceplayer
	msgbox SafariZone_Text_FirstCatch, MSGBOX_DEFAULT
	closemessage
	release
	end

SafariZone_Text_FirstCatch::
	.string "I have always wanted to catch my first\n"
	.string "POKéMON at the SAFARI ZONE.$"

SafariZoneGate_EventScript_Kangaskhan::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_KANGASKHAN, CRY_MODE_NORMAL
	msgbox SafariZone_Text_Kangaskhan, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SafariZone_Text_Kangaskhan::
	.string "KANGASKHAN: ………………$"

SafariZoneGate_EventScript_Engineer::
	lock
	faceplayer
	msgbox SafariZone_Text_JigglypuffTrainer, MSGBOX_DEFAULT
	closemessage
	release
	end

SafariZone_Text_JigglypuffTrainer::
	.string "This SAFARI ZONE is great!\n"
	.string "I just kept going after POKéMON!\p"
	.string "That made my JIGGLYPUFF upset though.$"
