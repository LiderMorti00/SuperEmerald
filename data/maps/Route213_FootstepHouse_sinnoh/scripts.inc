Route213_FootstepHouse_sinnoh_MapScripts::
	.byte 0


Route213_FootstepHouse_EventScript_PtNpc1::
	lock
	faceplayer
	msgbox Route213_FootstepHouse_Text_PtNpc1, MSGBOX_DEFAULT
	goto VerdanturfTown_FriendshipRatersHouse_EventScript_RateLeadMon
	end

Route213_FootstepHouse_Text_PtNpc1::
	.string "Dr. Footstep: Do you want to know the\n"
	.string "feelings of your POKéMON?\p"
	.string "Let your lead POKéMON walk in front\n"
	.string "of me…\p"
	.string "From its footprints, I can tell how\n"
	.string "it feels about you!$"
