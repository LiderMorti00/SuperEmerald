BurnedTower_1F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, BurnedTower_1F_OnLoad
	.byte 0

@ Super Emerald: post-story Burned Tower, the floor has fallen in (Heart & Soul)
BurnedTower_1F_OnLoad::
	setmetatile 16, 12, 0x37E, FALSE
	end


BurnedTower_1F_EventScript_Eusine::
	lock
	faceplayer
	msgbox BurnedTower_1FEusineText, MSGBOX_DEFAULT
	closemessage
	release
	end

BurnedTower_1FEusineText::
	.string "EUSINE: I heard SUICUNE might\n"
	.string "be in this BURNED TOWER, so I\l"
	.string "came to check it out.\p"
	.string "But where exactly could it be?$"

BurnedTower_1F_EventScript_Morty::
	lock
	faceplayer
	msgbox BurnedTower_1FMortyText, MSGBOX_DEFAULT
	closemessage
	release
	end

BurnedTower_1FMortyText::
	.string "MORTY: ECRUTEAK's GYM LEADER\n"
	.string "has to study what are said to\l"
	.string "be the legendary POKéMON--\l"
	.string "SUICUNE, ENTEI and RAIKOU.\p"
	.string "EUSINE is here, so I've\n"
	.string "decided to investigate the\l"
	.string "TOWER with him.$"

BurnedTower_1F_EventScript_Nard::
	trainerbattle_single TRAINER_NARD_HNS, BurnedTower_Text_NardSeen, BurnedTower_Text_NardBeaten
	msgbox BurnedTower_Text_NardAfter, MSGBOX_AUTOCLOSE
	end

BurnedTower_Text_NardAfter::
	.string "The reason this tower's burned is\n"
	.string "that it was hit by lightning.\p"
	.string "The fire I'm breathing is tiny\n"
	.string "in comparison...$"

BurnedTower_Text_NardBeaten::
	.string "Thanks for such a heated battle!$"

BurnedTower_Text_NardSeen::
	.string "Don't worry!\p"
	.string "We fire-breathers know the true\n"
	.string "power of fire better than anyone!$"

BurnedTower_1F_EventScript_Richardo::
	trainerbattle_single TRAINER_RICHARDO_HNS, BurnedTower_Text_RichardoSeen, BurnedTower_Text_RichardoBeaten
	msgbox BurnedTower_Text_RichardoAfter, MSGBOX_AUTOCLOSE
	end

BurnedTower_Text_RichardoAfter::
	.string "Maybe a life of crime isn't for\n"
	.string "me...$"

BurnedTower_Text_RichardoBeaten::
	.string "Pfffffffffffffff.$"

BurnedTower_Text_RichardoSeen::
	.string "I'm practicing my stealing in the\n"
	.string "BURNED TOWER! Don't try\l"
	.string "this at home!$"

BurnedTower_1F_EventScript_Item_HpUp::
	finditem ITEM_HP_UP
	end

BurnedTower_1F_EventScript_Item_Ether::
	finditem ITEM_ETHER
	end
