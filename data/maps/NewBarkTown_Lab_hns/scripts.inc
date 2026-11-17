NewBarkTown_Lab_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NewBarkTown_Lab_hns_OnTransition
	.byte 0

NewBarkTown_Lab_hns_OnTransition:
	setrespawn HEAL_LOCATION_NEW_BARK_TOWN_HNS
	end


NewBarkTown_EventScript_Aide1::
	lock
	faceplayer
	msgbox NewBarkTown_Lab_Text_AideAlwaysBusy, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_Text_AideAlwaysBusy::
	.string "There are only three of us, so\n"
	.string "we're always busy.$"

NewBarkTown_Lab_Text_ShowTogepi1::
	.string "ELM: {PLAYER}, you look great!$"

SE_J_NewBarkTown_Lab_hns_NewBarkTown_Lab_EventScript_Elm::
	lock
	faceplayer
	goto_if_unset FLAG_SE_JOHTO_LEAGUE_CLEARED, NewBarkTown_Lab_EventScript_ElmTalk
	checkitem ITEM_PASS
	goto_if_eq VAR_RESULT, TRUE, NewBarkTown_Lab_EventScript_ElmTalk
	msgbox NewBarkTown_Lab_Text_ElmPass, MSGBOX_DEFAULT
	giveitem ITEM_PASS
	msgbox NewBarkTown_Lab_Text_ElmPassAfter, MSGBOX_DEFAULT
	release
	end

NewBarkTown_Lab_EventScript_ElmTalk::
	msgbox NewBarkTown_Lab_Text_ShowTogepi1, MSGBOX_DEFAULT
	release
	end

NewBarkTown_Lab_Text_ElmPass:
	.string "ELM: {PLAYER}! You beat the JOHTO\n"
	.string "LEAGUE? Congratulations!\p"
	.string "Here, this is a little present.\n"
	.string "It's a PASS for the MAGNET TRAIN.$"

NewBarkTown_Lab_Text_ElmPassAfter:
	.string "ELM: The MAGNET TRAIN leaves from\n"
	.string "GOLDENROD CITY and goes all the way\l"
	.string "to SAFFRON CITY in KANTO.\p"
	.string "Go and see what POKéMON live there!$"

NewBarkTown_Lab_Text_AideSave::
	.string "Don't forget to save your game\n"
	.string "regularly!\p"
	.string "Press the START button, then\n"
	.string "SAVE the game!$"

SE_J_NewBarkTown_Lab_hns_NewBarkTown_EventScript_Aide2::
	msgbox NewBarkTown_Lab_Text_AideSave, MSGBOX_NPC
	end

NewBarkTown_Lab_Text_ShouldntTouch::
	.string "Probably shouldn't touch!$"

SE_J_NewBarkTown_Lab_hns_NewBarkTown_Lab_EventScript_ChikoritaBall::
	msgbox NewBarkTown_Lab_Text_ShouldntTouch, MSGBOX_NPC
	end

SE_J_NewBarkTown_Lab_hns_NewBarkTown_Lab_EventScript_CyndaquilBall::
	msgbox NewBarkTown_Lab_Text_ShouldntTouch, MSGBOX_NPC
	end

SE_J_NewBarkTown_Lab_hns_NewBarkTown_Lab_EventScript_TotodileBall::
	msgbox NewBarkTown_Lab_Text_ShouldntTouch, MSGBOX_NPC
	end

NewBarkTown_Lab_EventScript_HealingMachine1::
	lock
	goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_HealingMachine2
	msgbox LittlerootTown_ProfessorBirchsLab_Text_SeriousLookingMachine, MSGBOX_SIGN
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_HealingMachine2::
	call Common_EventScript_OutOfCenterPartyHeal
	release
	end
