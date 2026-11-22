IcePath_1F_hns_MapScripts::
	.byte 0


IcePath_1F_EventScript_Item_PpUp::
	finditem ITEM_PP_UP
	end

SE_J_IcePath_1F_hns_IcePath_1F_EventScript_Item_HM_Waterfall::
	finditem ITEM_HM_WATERFALL
	end

IcePath_1F_EventScript_Item_Protein::
	finditem ITEM_PROTEIN
	end

IcePath_1F_Text_Stuck1::
    .string "Me oh my… Is that you, {PLAYER}?\n"
    .string "Fancy meeting you here!\p"
    .string "To tell the truth… my sandals are\n"
    .string "frozen on the ice, and I am stuck.\p"
    .string "In other words, my flip-flops are\n"
    .string "quick-frozen to the ground.\p"
    .string "Tee hee.\p"
    .string "Well, it's no laughing matter.\p"
    .string "Would you come around and push\n"
    .string "my back?$"

SE_J_IcePath_1F_hns_IcePath_1F_EventScript_KimonoGirl::
	msgbox IcePath_1F_Text_Stuck1, MSGBOX_NPC
	end
