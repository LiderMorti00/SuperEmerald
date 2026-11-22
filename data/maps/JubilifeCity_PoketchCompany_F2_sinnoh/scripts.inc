JubilifeCity_PoketchCompany_F2_sinnoh_MapScripts::
	.byte 0


JubilifeCity_PoketchCompany_F2_EventScript_PtNpc1::
	msgbox JubilifeCity_PoketchCompany_F2_Text_PtNpc1, MSGBOX_NPC
	end

JubilifeCity_PoketchCompany_F2_Text_PtNpc1::
	.string "We'll try to think like a TRAINER and\n"
	.string "find what POKéNAV apps would be good.$"

JubilifeCity_PoketchCompany_F2_EventScript_PtNpc2::
	msgbox JubilifeCity_PoketchCompany_F2_Text_PtNpc2, MSGBOX_NPC
	end

JubilifeCity_PoketchCompany_F2_Text_PtNpc2::
	.string "My child runs the POKéNAV branch\n"
	.string "here in JUBILIFE.\p"
	.string "We get visitors from HOENN who\n"
	.string "already know every menu.\p"
	.string "I still ask for help finding the\n"
	.string "map sometimes!$"

JubilifeCity_PoketchCompany_F2_EventScript_PtNpc3::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CLEFAIRY, CRY_MODE_NORMAL
	msgbox JubilifeCity_PoketchCompany_F2_Text_PtNpc3, MSGBOX_DEFAULT
	waitmoncry
	release
	end

JubilifeCity_PoketchCompany_F2_Text_PtNpc3::
	.string "CLEFAIRY: Cleffy?$"

JubilifeCity_PoketchCompany_F2_EventScript_PtNpc4::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PACHIRISU, CRY_MODE_NORMAL
	msgbox JubilifeCity_PoketchCompany_F2_Text_PtNpc4, MSGBOX_DEFAULT
	waitmoncry
	release
	end

JubilifeCity_PoketchCompany_F2_Text_PtNpc4::
	.string "PACHIRISU: Patchii?$"
