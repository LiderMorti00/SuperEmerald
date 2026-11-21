SproutTower_3F_hns_MapScripts::
	.byte 0


SproutTower_3F_EventScript_SageNeal::
	trainerbattle_single TRAINER_NEAL_HNS, SproutTower_Text_SageNeal_Seen, SproutTower_Text_SageNeal_Beaten
	msgbox SproutTower_Text_SageNeal_AfterBattle, MSGBOX_AUTOCLOSE
	end

SproutTower_Text_SageNeal_AfterBattle::
	.string "Let there be light on your\n"
	.string "journey.$"

SproutTower_Text_SageNeal_Beaten::
	.string "It is my head that is bright!$"

SproutTower_Text_SageNeal_Seen::
	.string "The ELDER's HM lights even\n"
	.string "pitch-black darkness.$"

SproutTower_3F_EventScript_SageJin::
	trainerbattle_single TRAINER_JIN_HNS, SproutTower_Text_SageJin_Seen, SproutTower_Text_SageJin_Beaten
	msgbox SproutTower_Text_SageJin_AfterBattle, MSGBOX_AUTOCLOSE
	end

SproutTower_Text_SageJin_AfterBattle::
	.string "As POKéMON grow stronger,\n"
	.string "so does the TRAINER.\p"
	.string "No, wait. As the TRAINER\n"
	.string "grows stronger, so do the\l"
	.string "POKéMON.$"

SproutTower_Text_SageJin_Beaten::
	.string "My training is incomplete…$"

SproutTower_Text_SageJin_Seen::
	.string "I train to find enlightenment\n"
	.string "in POKéMON!$"

SproutTower_3F_EventScript_SageTroy::
	trainerbattle_single TRAINER_TROY_HNS, SproutTower_Text_SageTroy_Seen, SproutTower_Text_SageTroy_Beaten
	msgbox SproutTower_Text_SageTroy_AfterBattle, MSGBOX_AUTOCLOSE
	end

SproutTower_Text_SageTroy_AfterBattle::
	.string "It is not far to the ELDER.$"

SproutTower_Text_SageTroy_Beaten::
	.string "Yes, your trust is real!$"

SproutTower_Text_SageTroy_Seen::
	.string "Let me see how much you trust\n"
	.string "your POKéMON.$"

SproutTower_Text_SageLi_Seen::
	.string "So good of you to come here!\p"
	.string "SPROUT TOWER is a place of\n"
	.string "training.\p"
	.string "People and POKéMON test their\n"
	.string "bonds to build a bright future\l"
	.string "together.\p"
	.string "I am the final test.\p"
	.string "Allow me to check the ties\n"
	.string "between your POKéMON and you!$"

SE_J_SproutTower_3F_hns_SproutTower_3F_EventScript_SageLi::
	msgbox SproutTower_Text_SageLi_Seen, MSGBOX_NPC
	end

SproutTower_3F_EventScript_EscapeRope::
	finditem ITEM_ESCAPE_ROPE
	end

SproutTower_3F_EventScript_Potion::
	finditem ITEM_POTION
	end

SproutTower_3F_EventScript_Painting::
	lock
	msgbox SproutTower_Text_3F_Painting, MSGBOX_AUTOCLOSE
	release
	end

SproutTower_Text_3F_Painting::
	.string "It's a powerful painting of a\n"
	.string "BELLSPROUT.$"
