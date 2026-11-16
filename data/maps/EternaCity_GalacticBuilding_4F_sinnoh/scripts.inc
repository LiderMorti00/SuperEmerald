EternaCity_GalacticBuilding_4F_sinnoh_MapScripts::
	.byte 0


EternaCity_GalacticBuilding_4F_Text_JupiterIntro::
	.string "Eh? Did you want something?\p"
	.string "How silly of me to even ask. You want\n"
	.string "to free the POKéMON.\p"
	.string "Fine! I, JUPITER, will deal with you.$"

SE_S_EternaCity_GalacticBuilding_4F_EternaCity_GalacticBuilding_4F_EventScript_Jupiter::
	msgbox EternaCity_GalacticBuilding_4F_Text_JupiterIntro, MSGBOX_NPC
	end

EternaCity_GalacticBuilding_4F_EventScript_Clefairy::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CLEFAIRY, CRY_MODE_NORMAL
	msgbox EternaCity_GalacticBuilding_4F_Text_ClefairyCry, MSGBOX_DEFAULT
	waitmoncry
	release
	end

EternaCity_GalacticBuilding_4F_Text_ClefairyCry::
	.string "CLEFAIRY: Pi...$"

EternaCity_GalacticBuilding_4F_EventScript_Buneary::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_BUNEARY, CRY_MODE_NORMAL
	msgbox EternaCity_GalacticBuilding_4F_Text_BunearyCry, MSGBOX_DEFAULT
	waitmoncry
	release
	end

EternaCity_GalacticBuilding_4F_Text_BunearyCry::
	.string "BUNEARY: Myun...$"

EternaCity_GalacticBuilding_4F_EventScript_Owner::
	msgbox EternaCity_GalacticBuilding_4F_Text_OwnerWorried, MSGBOX_NPC
	end

EternaCity_GalacticBuilding_4F_Text_OwnerWorried::
	.string "What is it with this TEAM GALACTIC?\p"
	.string "Why did they take our POKéMON? What\n"
	.string "are they trying to accomplish?$"
