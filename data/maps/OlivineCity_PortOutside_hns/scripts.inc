OlivineCity_PortOutside_hns_MapScripts::
	.byte 0


OlivineCity_PortOutside_EventScript_Fisherman1::
	lock
	faceplayer
	goto_if_set FLAG_SE_JOHTO_LEAGUE_CLEARED, OlivineCity_PortOutside_EventScript_AquaAvailable
	msgbox OlivineCity_PortOutside_Text_PortFisherman1, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_PortOutside_Text_PortFisherman1::
	.string "The S.S. TIDAL sails to SLATEPORT.\p"
	.string "Ask the sailor inside if you're\n"
	.string "heading back to HOENN.$"

OlivineCity_PortOutside_EventScript_AquaAvailable::
	msgbox OlivineCity_PortOutside_Text_AquaAvailable, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_PortOutside_Text_AquaAvailable::
	.string "Heading for KANTO, CHAMPION?\p"
	.string "The S.S. AQUA sails to VERMILION.\n"
	.string "Ask the sailor inside about it.$"

OlivineCity_PortOutside_EventScript_Fisherman2::
	lock
	faceplayer
	msgbox OlivineCity_PortOutside_Text_Fisherman2, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_PortOutside_Text_Fisherman2::
	.string "Aw yeah, I'm fishin'.$"

OlivineCity_PortOutside_EventScript_Sabrina::
    lock
    faceplayer
    msgbox OlivineCity_PortOutside_Text_Sabrina, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    setflag FLAG_HIDE_OLIVINE_SABRINA
    removeobject LOCALID_OLIVINE_SABRINA
    fadescreenswapbuffers FADE_FROM_BLACK
    clearflag FLAG_HIDE_DOJO_SABRINA
    release
    end

OlivineCity_PortOutside_Text_Sabrina::
    .string "SABRINA: Out of the blue,\n"
	.string "I get the urge to see the ocean.\p"
	.string "I'll see you at the FIGHTING\n"
	.string "DOJO.$"
