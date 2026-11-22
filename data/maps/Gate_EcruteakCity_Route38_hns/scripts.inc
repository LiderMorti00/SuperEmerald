Gate_EcruteakCity_Route38_hns_MapScripts::
	.byte 0


Route38_EventScript_Officer::
	lock
	faceplayer
	msgbox Route38_Text_EcruteakGateOfficer, MSGBOX_DEFAULT
	closemessage
	release
	end

Route38_Text_EcruteakGateOfficer::
	.string "The CHAMPION of HOENN, here on my\n"
	.string "shift! Welcome to ECRUTEAK.\p"
	.string "If you're heading west, ROUTE 38\n"
	.string "takes you toward MOOMOO FARM.$"
