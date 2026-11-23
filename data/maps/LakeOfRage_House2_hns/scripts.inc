LakeOfRage_House2_hns_MapScripts::
	.byte 0


LakeOfRage_House2_Text_MenInBlack::
    .string "The LAKE hasn't been normal since\n"
    .string "those men wearing black arrived.$"

SE_J_LakeOfRage_House2_hns_LakeOfRage_House2_EventScript_Fisher::
	goto_if_ne VAR_SE_ROCKET_QUEST, 1, SE_LakeOfRageHouse2_Calm_Script
	msgbox LakeOfRage_House2_Text_MenInBlack, MSGBOX_NPC
	end

SE_LakeOfRageHouse2_Calm_Script::
	msgbox SE_LakeOfRageHouse2_Calm_Text, MSGBOX_NPC
	end

SE_LakeOfRageHouse2_Calm_Text::
	.string "The LAKE is calm again.\n"
	.string "The fishing's been great lately!$"
