SurvivalArea_sinnoh_MapScripts::
	.byte 0


SurvivalArea_EventScript_PtNpc1::
	msgbox SurvivalArea_Text_PtNpc1, MSGBOX_NPC
	end

SurvivalArea_Text_PtNpc1::
	.string "I'm taking the Frontier challenges to\n"
	.string "score some commemorative prints.$"

SurvivalArea_EventScript_PtNpc2::
	msgbox SurvivalArea_Text_PtNpc2, MSGBOX_NPC
	end

SurvivalArea_Text_PtNpc2::
	.string "Trainers who lose at the Battle\n"
	.string "Frontier come here to train.$"

SurvivalArea_EventScript_PtNpc3::
	msgbox SurvivalArea_Text_PtNpc3, MSGBOX_NPC
	end

SurvivalArea_Text_PtNpc3::
	.string "Hey, traveling Trainer. Is your big Bag\n"
	.string "full of items?\p"
	.string "Or is it full of dreams?$"

SurvivalArea_EventScript_PtNpc4::
	msgbox SurvivalArea_Text_PtNpc4, MSGBOX_NPC
	end

SurvivalArea_Text_PtNpc4::
	.string "I'm a Cameraman, obviously.\p"
	.string "Have you seen that TV program,\n"
	.string "“Search for the Red GYARADOS!”?\p"
	.string "Yeah, that outstanding documentary!\n"
	.string "I filmed that!$"

SurvivalArea_EventScript_SNBarry_Intro::
	.string "BARRY: Hey, {PLAYER}! You aren’t the\n"
	.string "only one getting tougher!\p"
	.string "I’ll prove it to you! Let’s go!$"

SE_S_SurvivalArea_SurvivalArea_EventScript_SNBarry::
	msgbox SurvivalArea_EventScript_SNBarry_Intro, MSGBOX_NPC
	end

SurvivalArea_EventScript_SNBuck::
	lock
	faceplayer
	msgbox SurvivalArea_Text_SNBuck, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_SN_SURVIVAL_BUCK
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_SN_SURV_BUCK
	setflag FLAG_SN_HIDE_SURV_BUCK
	fadescreen FADE_FROM_BLACK
	release
	end

SurvivalArea_Text_SNBuck::
	.string "Buck: Yo, if it isn’t {PLAYER}!\p"
	.string "This! It’s my place! Drop in, hey?$"

SurvivalArea_EventScript_PtSign1::
	msgbox SurvivalArea_Text_PtSign1, MSGBOX_SIGN
	end

SurvivalArea_Text_PtSign1::
	.string "Survival Area Staging Point$"
