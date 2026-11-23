Route227_House_sinnoh_MapScripts::
	.byte 0


Route227_House_EventScript_PtNpc1::
	lock
	faceplayer
	msgbox Route227_House_Text_PtNpc1, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox Route227_House_Text_Rested, MSGBOX_DEFAULT
	release
	end

Route227_House_Text_Rested::
	.string "There! Your POKéMON look full of\n"
	.string "energy again. Take care out there!$"

Route227_House_Text_PtNpc1::
	.string "Oh, dear, are your POKéMON feeling\n"
	.string "tired?\p"
	.string "You should rest up. Yes, good idea!\n"
	.string "Rest up here!$"
