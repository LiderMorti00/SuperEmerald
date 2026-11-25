SilphCo_2F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SilphCo_2F_OnLoad
	.byte 0

SilphCo_2F_OnLoad::
	call_if_unset FLAG_SILPH_2F_DOOR_1, EventScript_Close2FDoor1
	call_if_unset FLAG_SILPH_2F_DOOR_2, EventScript_Close2FDoor2
	end

SilphCo_2F_EventScript_ThunderWaveTutor::
	goto EventScript_ThunderWaveTutor
	end

SilphCo_2F_EventScript_FloorSign::
	msgbox SilphCo_2F_Text_FloorSign, MSGBOX_SIGN
	end

Text_ThunderWaveTeach::
	.string "Welcome to SILPH!\p"
	.string "We work with all sorts of POKéMON\n"
	.string "here. I teach moves in my spare time.\p"
	.string "Would you like me to teach one of\n"
	.string "yours THUNDER WAVE?$"

Text_ThunderWaveDeclined::
	.string "Oh…\n"
	.string "But THUNDER WAVE is convenient…$"

Text_ThunderWaveWhichMon::
	.string "Which POKéMON should I teach\n"
	.string "THUNDER WAVE?$"

Text_ThunderWaveTaught::
	.string "THUNDER WAVE causes paralysis in\n"
	.string "the target POKéMON.\p"
	.string "A paralyzed POKéMON may be unable\n"
	.string "to move in battle.\p"
	.string "It's an ELECTRIC-type move, so it\n"
	.string "won't work on some POKéMON.$"

SilphCo_2F_Text_FloorSign::
	.string "SILPH CO. HEAD OFFICE\n"
	.string "2F$"

