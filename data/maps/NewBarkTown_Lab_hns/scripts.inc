NewBarkTown_Lab_hns_MapScripts::
	.byte 0


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
	msgbox NewBarkTown_Lab_Text_ShowTogepi1, MSGBOX_NPC
	end

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
