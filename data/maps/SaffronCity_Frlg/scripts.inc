SaffronCity_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SaffronCity_OnTransition
	.byte 0

SaffronCity_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_SAFFRON_CITY
	end

@ Super Emerald: HGSS look, texts from Pokemon Heart & Soul (tools/sfr/hns/import_kanto_hgss.py)

SE_KH_SaffronCity_Frlg_Lass1A::
	msgbox SE_KH_SaffronCity_Frlg_Lass1A_Text, MSGBOX_NPC
	end

SE_KH_SaffronCity_Frlg_Lass1A_Text:
	.string "The COPYCAT girl looked unhappy.\p"
	.string "She said she lost her favorite\n"
	.string "POKé DOLL--CLEFAIRY.$"

SE_KH_SaffronCity_Frlg_Lass2::
	msgbox SE_KH_SaffronCity_Frlg_Lass2_Text, MSGBOX_NPC
	end

SE_KH_SaffronCity_Frlg_Lass2_Text:
	.string "Our city was featured on a radio\n"
	.string "program.\p"
	.string "It's nice to hear praise for your\n"
	.string "city, but it's a bit embarrassing\l"
	.string "too.$"

SE_KH_SaffronCity_Frlg_Youngster2::
	msgbox SE_KH_SaffronCity_Frlg_Youngster2_Text, MSGBOX_NPC
	end

SE_KH_SaffronCity_Frlg_Youngster2_Text:
	.string "There's a FIGHTING DOJO right next\n"
	.string "to the GYM.\p"
	.string "TRAINERS gather there from all\n"
	.string "over the place.$"

SE_KH_SaffronCity_Frlg_PokefanM::
	msgbox SE_KH_SaffronCity_Frlg_PokefanM_Text, MSGBOX_NPC
	end

SE_KH_SaffronCity_Frlg_PokefanM_Text:
	.string "You came out from JOHTO?\p"
	.string "You can zip back home by hopping\n"
	.string "on the MAGNET TRAIN.$"

SE_KH_SaffronCity_Frlg_CooltrainerF::
	msgbox SE_KH_SaffronCity_Frlg_CooltrainerF_Text, MSGBOX_NPC
	end

SE_KH_SaffronCity_Frlg_CooltrainerF_Text:
	.string "This is SILPH CO., famous for\n"
	.string "POKéMON merchandise.\p"
	.string "In the past, TEAM ROCKET wanted\n"
	.string "the company because of that.$"

SE_KH_SaffronCity_Frlg_Youngster1::
	msgbox SE_KH_SaffronCity_Frlg_Youngster1_Text, MSGBOX_NPC
	end

SE_KH_SaffronCity_Frlg_Youngster1_Text:
	.string "Going into an alley for the first\n"
	.string "time makes me sorta anxious.$"

SE_KH_SaffronCity_Frlg_Fisher::
	msgbox SE_KH_SaffronCity_Frlg_Fisher_Text, MSGBOX_NPC
	end

SE_KH_SaffronCity_Frlg_Fisher_Text:
	.string "Chew… Chew…\p"
	.string "I hear a powerful ELECTRIC POKéMON\n"
	.string "nests at the POWER PLANT.\p"
	.string "Chew… Chew… Haaah, I'm full!$"

SE_KH_SaffronCity_Frlg_CooltrainerM::
	msgbox SE_KH_SaffronCity_Frlg_CooltrainerM_Text, MSGBOX_NPC
	end

SE_KH_SaffronCity_Frlg_CooltrainerM_Text:
	.string "I went to the GYM, raring for\n"
	.string "battles against TRAINERS…\p"
	.string "It turns out, I stumbled into the\n"
	.string "unused GYM next door.\p"
	.string "Boy, I was pretty embarrassed.$"

SE_KH_SaffronCity_Frlg_Elli::
	msgbox SE_KH_SaffronCity_Frlg_Elli_Text, MSGBOX_NPC
	end

SE_KH_SaffronCity_Frlg_Elli_Text:
	.string "I love VULPIX! :D$"

SE_KH_SaffronCity_Frlg_Vulpix::
	msgbox SE_KH_SaffronCity_Frlg_Vulpix_Text, MSGBOX_NPC
	end

SE_KH_SaffronCity_Frlg_Vulpix_Text:
	.string "VULPIX: Vullll Pix!$"

SE_KH_SaffronCity_Frlg_MagnetTrainSign::
	msgbox SE_KH_SaffronCity_Frlg_MagnetTrainSign_Text, MSGBOX_SIGN
	end

SE_KH_SaffronCity_Frlg_MagnetTrainSign_Text:
	.string "SAFFRON CITY\n"
	.string "MAGNET TRAIN STATION$"

SE_KH_SaffronCity_Frlg_MrPsychicSign::
	msgbox SE_KH_SaffronCity_Frlg_MrPsychicSign_Text, MSGBOX_SIGN
	end

SE_KH_SaffronCity_Frlg_MrPsychicSign_Text:
	.string "MR.PSYCHIC'S\n"
	.string "HOUSE$"

SE_KH_SaffronCity_Frlg_SilphCoSign::
	msgbox SE_KH_SaffronCity_Frlg_SilphCoSign_Text, MSGBOX_SIGN
	end

SE_KH_SaffronCity_Frlg_SilphCoSign_Text:
	.string "SILPH CO. OFFICE BUILDING$"

SE_KH_SaffronCity_Frlg_DojoSign::
	msgbox SE_KH_SaffronCity_Frlg_DojoSign_Text, MSGBOX_SIGN
	end

SE_KH_SaffronCity_Frlg_DojoSign_Text:
	.string "FIGHTING DOJO$"

SE_KH_SaffronCity_Frlg_GymSign::
	msgbox SE_KH_SaffronCity_Frlg_GymSign_Text, MSGBOX_SIGN
	end

SE_KH_SaffronCity_Frlg_GymSign_Text:
	.string "SAFFRON CITY POKéMON GYM\n"
	.string "LEADER: SABRINA\l"
	.string "The Master of PSYCHIC POKéMON!$"

SE_KH_SaffronCity_Frlg_CitySign::
	msgbox SE_KH_SaffronCity_Frlg_CitySign_Text, MSGBOX_SIGN
	end

SE_KH_SaffronCity_Frlg_CitySign_Text:
	.string "SAFFRON CITY\n"
	.string "Shining, Golden Land of Commerce$"

