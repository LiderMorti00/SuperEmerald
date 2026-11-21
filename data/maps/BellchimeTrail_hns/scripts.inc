BellchimeTrail_hns_MapScripts::
	.byte 0


EcruteakBellchimeTrail_EventScript_Item_BigMushroom::
	finditem ITEM_BIG_MUSHROOM
	end

BellchimeTrail_EventScript_Morty::
	lock
	faceplayer
	msgbox BellchimeTrail_Text_Morty, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_BELLCHIME_MORTY
	removeobject LOCALID_BELLCHIME_MORTY
	fadescreenswapbuffers FADE_FROM_BLACK
	clearflag FLAG_HIDE_DOJO_MORTY
	release
	end

BellchimeTrail_Text_Morty::
	.string "MORTY: The legendary POKéMON\n"
	.string "did not choose me…\p"
	.string "But that does not mean that I\n"
	.string "have lost out on my future.\p"
	.string "I will continue my training until I\n"
	.string "I discover a new future for me.\p"
	.string "If you seek another battle, find\n"
	.string "me at the FIGHTING DOJO.$"
