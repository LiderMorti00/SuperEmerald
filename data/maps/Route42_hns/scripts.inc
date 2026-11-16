Route42_hns_MapScripts::
	.byte 0


Route42_EventScript_Item_SuperPotion::
	finditem ITEM_SUPER_POTION
	end

Route42_EventScript_Item_UltraBall::
	finditem ITEM_ULTRA_BALL
	end

Route42_Text_FisherTullyAfter::
	.string "I want to become the trainer\n"
	.string "CHAMP using the POKéMON I\l"
	.string "caught myself.\p"
	.string "That's the best part of fishing!$"

SE_J_Route42_hns_Route42_EventScript_Tully::
	msgbox Route42_Text_FisherTullyAfter, MSGBOX_NPC
	end

Route42_EventScript_Shane::
	trainerbattle_single TRAINER_SHANE_HNS, Route42_Text_PokemaniacShaneSeen, Route42_Text_PokemaniacShaneBeaten
	msgbox Route42_Text_PokemaniacShaneAfter, MSGBOX_AUTOCLOSE
	end

Route42_Text_PokemaniacShaneAfter::
	.string "You're working on a POKéDEX?\p"
	.string "Wow, you must know some\n"
	.string "pretty rare POKéMON!\p"
	.string "May I please see it?\n"
	.string "Please?$"

Route42_Text_PokemaniacShaneBeaten::
	.string "I should have used my\n"
	.string "MOON STONE…$"

Route42_Text_PokemaniacShaneSeen::
	.string "HEY!\p"
	.string "This is my secret place!\n"
	.string "Get lost, you outsider!$"

Route42_EventScript_Ben::
	trainerbattle_single TRAINER_BENJAMIN_HNS, Route42_Text_HikerBenjaminSeen, Route42_Text_HikerBenjaminBeaten
	msgbox Route42_Text_HikerBenjaminAfter, MSGBOX_AUTOCLOSE
	end

Route42_Text_HikerBenjaminAfter::
	.string "Losing feels insignificant\n"
	.string "if you look up at the big sky!$"

Route42_Text_HikerBenjaminBeaten::
	.string "Gahahah! That was a good\n"
	.string "battle!$"

Route42_Text_HikerBenjaminSeen::
	.string "Ah, it's good to be outside!\n"
	.string "I feel so free!$"

SE_J_Route42_hns_Route42_EventScript_Item_Shadow_Claw::
	end

Route42_EventScript_MortarSign::
	lock
	msgbox Route42_Text_MtMortarSign1, MSGBOX_SIGN
	closemessage
	release
	end

Route42_Text_MtMortarSign1::
	.string "MT.MORTAR\p"
	.string "WATERFALL CAVE INSIDE$"

Route42_EventScript_Sign::
	lock
	msgbox Route42_Text_Sign1, MSGBOX_SIGN
	closemessage
	release
	end

Route42_Text_Sign1::
	.string "ROUTE 42\p"
	.string "ECRUTEAK CITY - MAHOGANY TOWN$"
