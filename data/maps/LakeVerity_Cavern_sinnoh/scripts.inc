LakeVerity_Cavern_sinnoh_MapScripts::
	.byte 0


LakeVerity_Cavern_EventScript_SNMESPRIT_TFled::
	.string "MESPRIT fled!\p"
	.string "It seems to be wandering all over\n"
	.string "Sinnoh!$"

SE_S_LakeVerity_Cavern_LakeVerity_Cavern_EventScript_SNMESPRIT::
	msgbox LakeVerity_Cavern_EventScript_SNMESPRIT_TFled, MSGBOX_NPC
	end

LakeVerity_Cavern_Text_SNRowan1::
	.string "Rowan: ... ...\p"
	.string "{PLAYER}, that was MESPRIT, wasn’t it?\p"
	.string "You’ve accomplished what I’d asked you\n"
	.string "to do at the Canalave Library...\p"
	.string "I asked you to get data on the POKéMON\n"
	.string "of the lake, and you did.\p"
	.string "But it didn’t provide any answers\n"
	.string "about the mysteries of evolution.\p"
	.string "I still don’t know why some POKéMON\n"
	.string "evolve and others don’t.\p"
	.string "Ultimately, it only deepened the\n"
	.string "mystery.\p"
	.string "But having mysteries to solve... That\n"
	.string "adds to my enjoyment!$"

SE_S_LakeVerity_Cavern_LakeVerity_Cavern_EventScript_SNRowan::
	msgbox LakeVerity_Cavern_Text_SNRowan1, MSGBOX_NPC
	end
