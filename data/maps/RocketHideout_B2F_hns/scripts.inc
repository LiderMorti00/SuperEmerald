RocketHideout_B2F_hns_MapScripts::
	.byte 0


SE_J_RocketHideout_B2F_hns_RocketHideout_B2F_EventScript_Electrode::
	end

RocketHideout_B2F_EventScript_Grunt14::
	trainerbattle_single TRAINER_GRUNT_14_HNS, RocketHideout_B2F_Text_GruntM17Seen, RocketHideout_B2F_Text_GruntM17Beaten
	msgbox RocketHideout_B2F_Text_GruntM17After, MSGBOX_AUTOCLOSE
	end

RocketHideout_B2F_Text_GruntM17After::
    .string "Heh, I'm just a GRUNT.\p"
    .string "I don't know the password.\n"
    .string "Too bad for you.$"

RocketHideout_B2F_Text_GruntM17Beaten::
    .string "What? I lost?$"

RocketHideout_B2F_Text_GruntM17Seen::
    .string "The door won't open?\p"
    .string "Well, duh. It has to have a\n"
    .string "password that only TEAM ROCKET\l"
    .string "knows.$"

RocketHideout_B2F_EventScript_Grunt15::
	trainerbattle_single TRAINER_GRUNT_15_HNS, RocketHideout_B2F_Text_GruntM18Seen, RocketHideout_B2F_Text_GruntM18Beaten
	msgbox RocketHideout_B2F_Text_GruntM18After, MSGBOX_AUTOCLOSE
	end

RocketHideout_B2F_Text_GruntM18After::
    .string "I got wiped out on the last\n"
    .string "mission by a kid too.\p"
    .string "When we were abducting POKéMON,\n"
    .string "this kid with long red hair and\l"
    .string "mean-looking eyes just\l"
    .string "creamed me…$"

RocketHideout_B2F_Text_GruntM18Beaten::
    .string "I knew I'd lose…$"

RocketHideout_B2F_Text_GruntM18Seen::
    .string "Oh, a kid? I don't really like\n"
    .string "this, but eliminate you I must.$"

RocketHideout_B2F_EventScript_Grunt16::
	trainerbattle_single TRAINER_GRUNT_16_HNS, RocketHideout_B2F_Text_GruntM19Seen, RocketHideout_B2F_Text_GruntM19Beaten
	msgbox RocketHideout_B2F_Text_GruntM19After, MSGBOX_AUTOCLOSE
	end

RocketHideout_B2F_Text_GruntM19After::
    .string "Heh, only the boss knows the\n"
    .string "password for that door.\p"
    .string "Where's the boss? Who knows?\n"
    .string "Go look for yourself.$"

RocketHideout_B2F_Text_GruntM19Beaten::
    .string "Grrrr…$"

RocketHideout_B2F_Text_GruntM19Seen::
    .string "You rotten little pest!$"

SE_J_RocketHideout_B2F_hns_RocketHideout_EventScript_Item_Thief::
	end

RocketHideout_B2F_Text_LanceChooseMons::
    .string "LANCE: Quickly {PLAYER}, choose\n"
	.string "your POKéMON!$"

SE_J_RocketHideout_B2F_hns_RocketHideout_B2F_EventScript_ReadyForBattlePrompt::
	msgbox RocketHideout_B2F_Text_LanceChooseMons, MSGBOX_NPC
	end
