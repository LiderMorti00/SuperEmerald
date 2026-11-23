FiveIsland_House2_Frlg_MapScripts::
	.byte 0

FiveIsland_House2_EventScript_OldMan::
	goto_if_ge VAR_SE_ROCKET_QUEST, 6, FiveIsland_House2_EventScript_OldManAfterQuest
	goto_if_lt VAR_SE_ROCKET_QUEST, 5, FiveIsland_House2_EventScript_OldManBeforeQuest
	msgbox FiveIsland_House2_Text_MeadowBelongedToFamily, MSGBOX_NPC
	end

FiveIsland_House2_EventScript_OldManAfterQuest::
	msgbox FiveIsland_House2_Text_ThugsAreGone, MSGBOX_NPC
	end

FiveIsland_House2_EventScript_OldManBeforeQuest::
	msgbox FiveIsland_House2_Text_EmptyWarehouse, MSGBOX_NPC
	end

FiveIsland_House2_Text_EmptyWarehouse::
	.string "That MEADOW has belonged to our\n"
	.string "family for generations.\p"
	.string "Some shady company put a warehouse\n"
	.string "on it years ago, then left it empty.\p"
	.string "I'd like to see it torn down.$"

FiveIsland_House2_Text_ThugsAreGone::
	.string "That MEADOW has belonged to our\n"
	.string "family for generations.\p"
	.string "Those thugs are gone at last.\n"
	.string "Thank you, young TRAINER!$"

FiveIsland_House2_Text_MeadowBelongedToFamily::
	.string "That MEADOW has belonged to our\n"
	.string "family for generations.\p"
	.string "I should have had a giant mansion\n"
	.string "built on it.\p"
	.string "It would be preferable to having\n"
	.string "those thugs run wild on it!$"

