MtMortar_B1F_hns_MapScripts::
	.byte 0


MountMortar4_Text_KiyoIntro::
	.string "Hey!\p"
	.string "I am the KARATE KING!\n"
	.string "I train alone here in the dark!\p"
	.string "You! Battle with me!\n"
	.string "Hwaaarggh!$"

SE_J_MtMortar_B1F_hns_MountMortar4_EventScript_Kiyo::
	msgbox MountMortar4_Text_KiyoIntro, MSGBOX_NPC
	end

MtMortar_B1F_EventScript_Item_PPUp::
    finditem ITEM_PP_UP
    end

MtMortar_B1F_EventScript_Item_MaxRevive::
    finditem ITEM_MAX_REVIVE
    end

MtMortar_B1F_EventScript_Item_Carbos::
    finditem ITEM_CARBOS
    end

MtMortar_B1F_EventScript_Item_MaxEther::
    finditem ITEM_MAX_ETHER
    end

MtMortar_B1F_EventScript_Item_HyperPotion::
    finditem ITEM_HYPER_POTION
    end
