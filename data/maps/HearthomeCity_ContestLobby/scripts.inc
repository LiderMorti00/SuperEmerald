@ Super Emerald: Hearthome's Contest Hall uses Lilycove's contest lobby scripts (contests,
@ BERRY BLENDERS for POKéBLOCKS, contest artist). FLAG_SE_HEARTHOME_CONTEST sends the player
@ back here after a contest, and makes the opponents Sinnoh's GYM LEADERS and ELITE FOUR.
HearthomeCity_ContestLobby_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, HearthomeCity_ContestLobby_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LilycoveCity_ContestLobby_OnFrame
	.byte 0

HearthomeCity_ContestLobby_OnTransition:
	setflag FLAG_SE_HEARTHOME_CONTEST
	goto SE_ContestLobby_OnTransition
