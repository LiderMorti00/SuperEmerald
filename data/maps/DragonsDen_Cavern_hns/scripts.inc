DragonsDen_Cavern_hns_MapScripts::
	.byte 0

DragonsDen_Cavern_EventScript_Darin::
	trainerbattle_single TRAINER_DARIN_HNS, DragonsDen_Cavern_Text_CooltrainermDarinSeen, DragonsDen_Cavern_Text_CooltrainermDarinBeaten
	msgbox DragonsDen_Cavern_Text_CooltrainermDarinAfter, MSGBOX_AUTOCLOSE
	end

DragonsDen_Cavern_Text_CooltrainermDarinAfter::
    .string "The SHRINE ahead is home to the\n"
    .string "MASTER of our dragon-user clan.\p"
    .string "You're not allowed to just go in!$"

DragonsDen_Cavern_Text_CooltrainermDarinBeaten::
    .string "S-strong!$"

DragonsDen_Cavern_Text_CooltrainermDarinSeen::
    .string "You! How dare you enter\n"
    .string "uninvited!$"

DragonsDen_Cavern_EventScript_TwinPia::
	trainerbattle_double TRAINER_LEA_AND_PIA_HNS, DragonsDen_Cavern_Text_TwinsLeaandPia2Seen, DragonsDen_Cavern_Text_TwinsLeaandPia2Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox DragonsDen_Cavern_Text_TwinsLeaandPia2After, MSGBOX_DEFAULT
	release
	end

DragonsDen_Cavern_Text_TwinsLeaandPia2After::
    .string "We'll tell on you.\p"
    .string "MASTER will be angry with you.$"

DragonsDen_Cavern_Text_TwinsLeaandPia2Beaten::
    .string "Meanie.$"

DragonsDen_Cavern_Text_TwinsLeaandPia2Seen::
    .string "Who are you?$"

DragonsDen_Cavern_EventScript_TwinLea::
	trainerbattle_double TRAINER_LEA_AND_PIA_HNS, DragonsDen_Cavern_Text_TwinsLeaandPia1Seen, DragonsDen_Cavern_Text_TwinsLeaandPia1Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox DragonsDen_Cavern_Text_TwinsLeaandPia1After, MSGBOX_DEFAULT
	release
	end

DragonsDen_Cavern_Text_TwinsLeaandPia1After::
    .string "It was like having to battle\n"
    .string "LANCE.$"

DragonsDen_Cavern_Text_TwinsLeaandPia1Beaten::
    .string "Ouchies.$"

DragonsDen_Cavern_Text_TwinsLeaandPia1Seen::
    .string "It's a stranger we don't know.$"

DragonsDen_Cavern_EventScript_Cara::
	trainerbattle_single TRAINER_CARA_HNS, DragonsDen_Cavern_Text_CooltrainerfCaraSeen, DragonsDen_Cavern_Text_CooltrainerfCaraBeaten
	msgbox DragonsDen_Cavern_Text_CooltrainerfCaraAfter, MSGBOX_AUTOCLOSE
	end

DragonsDen_Cavern_Text_CooltrainerfCaraAfter::
    .string "Soon I'm going to get permission\n"
    .string "from our MASTER to use dragons.\p"
    .string "When I do, I'm going to become an\n"
    .string "admirable dragon TRAINER and gain\l"
    .string "our MASTER's approval.$"

DragonsDen_Cavern_Text_CooltrainerfCaraBeaten::
    .string "Oh yikes, I lost!$"

DragonsDen_Cavern_Text_CooltrainerfCaraSeen::
    .string "You shouldn't be in here!$"

DragonsDen_Cavern_EventScript_Item_PP_Max::
	finditem ITEM_PP_MAX
	end

DragonsDen_Cavern_EventScript_Item_Max_Potion::
	finditem ITEM_MAX_POTION
	end

DragonsDen_Cavern_EventScript_Item_Dragon_Fang::
	finditem ITEM_DRAGON_FANG
	end
