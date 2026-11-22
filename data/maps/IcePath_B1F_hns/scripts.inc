IcePath_B1F_hns_MapScripts::
	.byte 0


IcePath_B1F_EventScript_Item_Iron::
	finditem ITEM_IRON
	end

IcePath_B1F_EventScript_Item_Revive::
	finditem ITEM_REVIVE
	end

IcePath_B1F_EventScript_Sign::
	msgbox IcePath_B1F_Text_Sign, MSGBOX_SIGN
	end

IcePath_B1F_Text_Sign::
	.string "Mind the holes in the ice!\p"
	.string "Use STRENGTH to push the boulders\n"
	.string "down to the floor below.$"

IcePath_B1F_EventScript_PuzzleSkipButton::
	lock
	msgbox IcePath_B1F_Text_PuzzleSkipButton, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, IcePath_B1F_EventScript_PuzzleSkipButtonNo
	warp MAP_ICE_PATH_B1F_HNS, 15, 12
	waitstate
	release
	end

IcePath_B1F_EventScript_PuzzleSkipButtonNo::
	release
	end

IcePath_B1F_Text_PuzzleSkipButton::
	.string "Would you like to skip this\n"
	.string "puzzle?$"
