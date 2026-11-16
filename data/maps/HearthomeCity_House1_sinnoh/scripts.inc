HearthomeCity_House1_sinnoh_MapScripts::
	.byte 0


HearthomeCity_House1_EventScript_SNBebe_T1::
	.string "Bebe: Hi! I’m Bebe. I’m the one who made\n"
	.string "the POKéMON Storage System!\p"
	.string "There’s a POKéMON here I’d like you to\n"
	.string "raise. It’s an EEVEE. Would you like it?$"

SE_S_HearthomeCity_House1_HearthomeCity_House1_EventScript_SNBebe::
	msgbox HearthomeCity_House1_EventScript_SNBebe_T1, MSGBOX_NPC
	end
