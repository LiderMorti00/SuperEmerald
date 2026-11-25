GoldenrodCity_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SE_EventScript_OroGoldenrodOnTransition
	.byte 0

GoldenrodCity_EventScript_Lass::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Text_Lass::
	.string "That man inside rates your\n"
	.string "POKéMON nicknames.\p"
	.string "He can even rename them.$"

GoldenrodCity_EventScript_Hiker::
	lock
	faceplayer
	goto_if_set FLAG_DAY_POKEMON, GoldenrodCity_EventScript_Hiker2
	msgbox GoldenrodCity_Text_HikerDay, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Text_HikerDay::
	.string "When I went into the GAME CORNER\n"
	.string "it was night time… How long was I\l"
	.string "in there?!$"

GoldenrodCity_EventScript_Hiker2::
	msgbox GoldenrodCity_Text_HikerNight, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Text_HikerNight::
	.string "When I went into the GAME CORNER\n"
	.string "it was day time… How long was I\l"
	.string "in there?!$"

GoldenrodCity_EventScript_Gramps::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Gramps, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Text_Gramps::
	.string "Whew! This town is so big,\n"
	.string "I can't find anything at all.$"

GoldenrodCity_EventScript_Youngster::
	msgbox GoldenrodCity_Text_Youngster1, MSGBOX_NPC
	end

GoldenrodCity_Text_Youngster1::
	.string "I know there's a new BIKE SHOP,\n"
	.string "but I can't find it anywhere.$"

GoldenrodCity_EventScript_Youngster2::
	msgbox GoldenrodCity_Text_Youngster2, MSGBOX_NPC
	end

GoldenrodCity_Text_Youngster2::
	.string "E-he-he-he…\p"
	.string "I got in trouble for playing in\n"
	.string "the DEPT.STORE basement.$"

GoldenrodCity_EventScript_CooltrainerF::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_GOLDENROD_ROCKET_SCOUT, GoldenrodCity_EventScript_CooltrainerFCleared
	msgbox GoldenrodCity_Text_CooltrainerF1, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Text_CooltrainerF1::
	.string "Is that man in black dressed up\n"
	.string "like a TEAM ROCKET member?\p"
	.string "How silly!$"

GoldenrodCity_EventScript_CooltrainerFCleared::
	goto_if_eq VAR_SE_ROCKET_QUEST, 0, SE_GoldenrodCooltrainer_Rumor_Script
	msgbox GoldenrodCity_Text_CooltrainerF1_Cleared, MSGBOX_NPC
	end

GoldenrodCity_Text_CooltrainerF1_Cleared::
	.string "Was that man in black really part\n"
	.string "of TEAM ROCKET? I can't believe it!$"

GoldenrodCity_Text_RocketScout1::
	.string "So this is the RADIO TOWER…$"

SE_J_GoldenrodCity_hns_GoldenrodCity_EventScript_RocketScout::
	msgbox GoldenrodCity_Text_RocketScout1, MSGBOX_NPC
	end

GoldenrodCity_EventScript_PokefanM::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Text_PokefanM::
	.string "They built the new RADIO TOWER\n"
	.string "to replace the old creaky one.$"

GoldenrodCity_EventScript_Snubbull::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SNUBBULL, CRY_MODE_NORMAL
	msgbox GoldenrodCity_Text_Snubbull, MSGBOX_DEFAULT
	waitmoncry
	release
	end

GoldenrodCity_Text_Snubbull::
	.string "SNUBBULL: SNUUUBUUUULL!$"

GoldenrodCity_EventScript_Mime::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MR_MIME, CRY_MODE_NORMAL
	msgbox GoldenrodCity_Text_MrMime, MSGBOX_DEFAULT
	waitmoncry
	release
	end

GoldenrodCity_Text_MrMime::
	.string "……………………….$"

GoldenrodCity_EventScript_Woman::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Woman, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Text_Woman::
	.string "I used to train in WHITNEY's GYM,\n"
	.string "but all her crying gave me a\l"
	.string "headache.$"

GoldenrodCity_EventScript_Beauty::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Beauty, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Text_Beauty::
	.string "This is the GOLDENROD GYM!\p"
	.string "Our leader WHITNEY is the cutest\n"
	.string "GYM LEADER in all of JOHTO!$"

GoldenrodCity_EventScript_SignRadio::
	lock
	msgbox GoldenrodCity_Text_RadioTowerSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_Text_RadioTowerSign::
	.string "GOLDENROD CITY RADIO TOWER$"

GoldenrodCity_EventScript_SignGameCorner::
	lock
	msgbox GoldenrodCity_Text_GameCornerSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_Text_GameCornerSign::
	.string "Your Playground!\p"
	.string "GOLDENROD CITY GAME CORNER$"

GoldenrodCity_EventScript_SignTrain::
	lock
	msgbox GoldenrodCity_Text_StationSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_Text_StationSign::
	.string "GOLDENROD CITY STATION$"

GoldenrodCity_EventScript_SignUnderground::
	lock
	msgbox GoldenrodCity_Text_UndergroundSouthSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_Text_UndergroundSouthSign::
	.string "UNDERGROUND ENTRANCE$"

GoldenrodCity_EventScript_SignBike::
	lock
	msgbox GoldenrodCity_Text_BikeShopSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_Text_BikeShopSign::
	.string "The World is a Cycle Path!\n"
	.string "BIKE SHOP$"

GoldenrodCity_EventScript_SignGym::
	lock
	msgbox GoldenrodCity_Text_GymSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_Text_GymSign::
	.string "GOLDENROD CITY POKéMON GYM\n"
	.string "LEADER: WHITNEY\p"
	.string "The Incredibly Pretty Girl!$"

GoldenrodCity_EventScript_SignFlower::
	lock
	msgbox GoldenrodCity_Text_FlowerShopSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_Text_FlowerShopSign::
	.string "Blooming Beautiful FLOWER SHOP$"

GoldenrodCity_EventScript_SignDept::
	lock
	msgbox GoldenrodCity_Text_DeptStoreSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_Text_DeptStoreSign::
	.string "Full Selection of POKéMON Goods!\p"
	.string "GOLDENROD CITY DEPT.STORE$"

GoldenrodCity_EventScript_NameRaterSign::
	msgbox GoldenrodCity_Text_NameRaterSign, MSGBOX_SIGN
	end

GoldenrodCity_Text_NameRaterSign::
	.string "NAME RATER\p"
	.string "Get Your POKéMON Nicknames Rated$"

SE_GoldenrodCooltrainer_Rumor_Script::
	msgbox SE_GoldenrodCooltrainer_Rumor_Text, MSGBOX_NPC
	end

SE_GoldenrodCooltrainer_Rumor_Text::
	.string "Did you hear? Some of TEAM ROCKET's\n"
	.string "old bosses were seen in JOHTO again!\p"
	.string "I hope it's just a rumor…$"
