LakeOfRage_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LakeOfRage_OnTransition
	.byte 0

@ Super Emerald: the lake has tides, like Shoal Cave (high from 9 to 15 and from 21 to 3)
LakeOfRage_OnTransition::
	special UpdateShoalTideFlag
	goto_if_set FLAG_SYS_SHOAL_TIDE, LakeOfRage_EventScript_SetHighTide
	setweather WEATHER_NONE
	setmaplayoutindex LAYOUT_LAKE_OF_RAGE_LOW_TIDE_HNS
	end

LakeOfRage_EventScript_SetHighTide::
	setmaplayoutindex LAYOUT_LAKE_OF_RAGE_HNS
	random 2
	goto_if_eq VAR_RESULT, 1, LakeOfRage_EventScript_ThunderStorm
	setweather WEATHER_NONE
	end

LakeOfRage_EventScript_ThunderStorm::
	setweather WEATHER_RAIN_THUNDERSTORM
	end


LakeOfRage_EventScript_Lass::
	msgbox LakeOfRage_Text_CooltrainerF, MSGBOX_NPC
	end

LakeOfRage_Text_CooltrainerF::
    .string "Did my eyes deceive me? I saw a\n"
    .string "red GYARADOS in the LAKE…\p"
    .string "But I thought GYARADOS were\n"
    .string "usually blue?$"

LakeOfRage_EventScript_Andre::
	trainerbattle_single TRAINER_ANDRE_HNS, LakeOfRage_Text_FisherAndreSeen, LakeOfRage_Text_FisherAndreBeaten
	msgbox LakeOfRage_Text_FisherAndreAfter, MSGBOX_AUTOCLOSE
	end

LakeOfRage_Text_FisherAndreAfter::
    .string "I won't lose as an angler! I catch\n"
    .string "POKéMON all day.$"

LakeOfRage_Text_FisherAndreBeaten::
    .string "I might be an expert angler, but\n"
    .string "I stink as a POKéMON TRAINER…$"

LakeOfRage_Text_FisherAndreSeen::
    .string "Let me battle with the POKéMON I\n"
    .string "just caught!$"

LakeOfRage_Text_LanceForcedToEvolve::
    .string "This lake is full of GYARADOS\n"
    .string "but nothing else…\p"
    .string "So the MAGIKARP are being forced\n"
    .string "to evolve…$"

SE_J_LakeOfRage_hns_LakeOfRage_EventScript_Lance::
	msgbox LakeOfRage_Text_LanceForcedToEvolve, MSGBOX_NPC
	end

LakeOfRage_Text_Gramps::
    .string "The GYARADOS are angry!\p"
    .string "It's a bad omen!$"

SE_J_LakeOfRage_hns_LakeOfRage_EventScript_Gramps::
	msgbox LakeOfRage_Text_Gramps, MSGBOX_NPC
	end

LakeOfRage_EventScript_Raymond::
	trainerbattle_single TRAINER_RAYMOND_HNS, LakeOfRage_Text_FisherRaymondSeen, LakeOfRage_Text_FisherRaymondBeaten
	msgbox LakeOfRage_Text_FisherRaymondAfter, MSGBOX_AUTOCLOSE
	end

LakeOfRage_Text_FisherRaymondAfter::
    .string "Why can't I catch any good\n"
    .string "POKéMON?$"

LakeOfRage_Text_FisherRaymondBeaten::
    .string "My line's all tangled up…$"

LakeOfRage_Text_FisherRaymondSeen::
    .string "No matter what I do, all I catch\n"
    .string "are the same POKéMON…$"

LakeOfRage_Text_MeetWesley::
    .string "WESLEY: Well, how do you do?\p"
    .string "I'm a member of the WEEKDAY family!\n"
    .string "Can you guess my favorite day?$"

SE_J_LakeOfRage_hns_LakeOfRage_EventScript_Wesley::
	msgbox LakeOfRage_Text_MeetWesley, MSGBOX_NPC
	end

LakeOfRage_EventScript_Lois::
	trainerbattle_single TRAINER_LOIS_HNS, LakeOfRage_Text_CooltrainerfLoisSeen, LakeOfRage_Text_CooltrainerfLoisBeaten
	msgbox LakeOfRage_Text_CooltrainerfLoisAfter, MSGBOX_AUTOCLOSE
	end

LakeOfRage_Text_CooltrainerfLoisAfter::
    .string "Come to think of it, I've seen a\n"
    .string "pink BUTTERFREE.$"

LakeOfRage_Text_CooltrainerfLoisBeaten::
    .string "Good going!$"

LakeOfRage_Text_CooltrainerfLoisSeen::
    .string "What happened to the red\n"
    .string "GYARADOS?\p"
    .string "It's gone?\p"
    .string "Oh, darn. I came here for\n"
    .string "nothing?\p"
    .string "I know--let's battle!$"

LakeOfRage_Text_GyaradosCry::
    .string "GYARADOS: Gyashaa!$"

SE_J_LakeOfRage_hns_LakeOfRage_EventScript_Gyarados::
	msgbox LakeOfRage_Text_GyaradosCry, MSGBOX_NPC
	end

LakeOfRage_EventScript_Aaron::
	trainerbattle_single TRAINER_AARON_HNS, LakeOfRage_Text_CooltrainermAaronSeen, LakeOfRage_Text_CooltrainermAaronBeaten
	msgbox LakeOfRage_Text_CooltrainermAaronAfter, MSGBOX_AUTOCLOSE
	end

LakeOfRage_Text_CooltrainermAaronAfter::
    .string "POKéMON and their TRAINER become\n"
    .string "powerful through constant battling.$"

LakeOfRage_Text_CooltrainermAaronBeaten::
    .string "Whew… Good battle.$"

LakeOfRage_Text_CooltrainermAaronSeen::
    .string "If a TRAINER spots another TRAINER,\n"
    .string "he has to make a challenge.\p"
    .string "That is our destiny.$"

LakeOfRage_EventScript_Item_Full_Restore::
	finditem ITEM_FULL_RESTORE
	end

SE_J_LakeOfRage_hns_LakeOfRage_EventScript_Item_Secret_Power::
	finditem ITEM_TM_SECRET_POWER
	end

LakeOfRage_EventScript_Item_Red_Flute::
	finditem ITEM_RED_FLUTE
	end

LakeOfRage_EventScript_Nerd::
	msgbox LakeOfRage_Text_SuperNerd, MSGBOX_NPC
	end

LakeOfRage_Text_SuperNerd::
    .string "I heard this lake was made by\n"
    .string "rampaging GYARADOS.\p"
    .string "I wonder if there is any\n"
    .string "connection to their mass outbreak\l"
    .string "now?$"

LakeOfRage_EventScript_Dragonite::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DRAGONITE, CRY_MODE_NORMAL
	msgbox LakeOfRage_Text_Dragonite, MSGBOX_DEFAULT
	waitmoncry
	turnobject LOCALID_LAKEOFRAGE_DRAGONITE, DIR_WEST
	release
	end

LakeOfRage_Text_Dragonite::
	.string "DRAGONITE: Gyafooha!$"

LakeOfRage_EventScript_Pryce::
    lock
    faceplayer
    msgbox LakeOfRage_Text_Pryce, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    setflag FLAG_HIDE_LAKE_PRYCE
    removeobject LOCALID_LAKE_PRYCE
    fadescreenswapbuffers FADE_FROM_BLACK
    clearflag FLAG_HIDE_DOJO_PRYCE
    release
    end

LakeOfRage_Text_Pryce::
    .string "{PLAYER}.\p"
    .string "Even here, the cold keeps me sharp.\p"
    .string "If you wish to battle again, come\n"
    .string "to the FIGHTING DOJO.$"

LakeOfRage_EventScript_Sign1::
	msgbox LakeOfRage_Text_Sign, MSGBOX_SIGN
	end

LakeOfRage_Text_Sign::
    .string "LAKE OF RAGE,\n"
    .string "also known as GYARADOS LAKE.$"

LakeOfRage_EventScript_Sign2::
	msgbox LakeOfRage_Text_FishingGuruSign, MSGBOX_SIGN
	end

LakeOfRage_Text_FishingGuruSign::
    .string "FISHING GURU'S HOUSE$"
