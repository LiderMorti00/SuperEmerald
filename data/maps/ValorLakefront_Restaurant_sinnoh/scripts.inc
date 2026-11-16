ValorLakefront_Restaurant_sinnoh_MapScripts::
	.byte 0


ValorLakefront_Restaurant_Text_SNREmilioIntro0::
	.string "Hmm... This beverage’s coloration\n"
	.string "borders on the positively toxic...\p"
	.string "However, my analysis indicates that it\n"
	.string "is composed of natural ingredients.$"

SE_S_ValorLakefront_Restaurant_ValorLakefront_Restaurant_EventScript_SNT0::
	msgbox ValorLakefront_Restaurant_Text_SNREmilioIntro0, MSGBOX_NPC
	end

SE_S_ValorLakefront_Restaurant_ValorLakefront_Restaurant_EventScript_SNT1::
	msgbox ValorLakefront_Restaurant_Text_SNREmilioIntro0, MSGBOX_NPC
	end

SE_S_ValorLakefront_Restaurant_ValorLakefront_Restaurant_EventScript_SNT2::
	msgbox ValorLakefront_Restaurant_Text_SNREmilioIntro0, MSGBOX_NPC
	end

SE_S_ValorLakefront_Restaurant_ValorLakefront_Restaurant_EventScript_SNT3::
	msgbox ValorLakefront_Restaurant_Text_SNREmilioIntro0, MSGBOX_NPC
	end

SE_S_ValorLakefront_Restaurant_ValorLakefront_Restaurant_EventScript_SNT4::
	msgbox ValorLakefront_Restaurant_Text_SNREmilioIntro0, MSGBOX_NPC
	end

ValorLakefront_Restaurant_EventScript_SNPtWAITER::
	msgbox ValorLakefront_Restaurant_Text_SNRWaiter, MSGBOX_NPC
	end

@ Cada mesa: VAR_0x8004 = mesa; el special pone en VAR_RESULT la pareja de hoy (0-8)

ValorLakefront_Restaurant_Text_SNRWaiter::
	.string "At our restaurant, you can enjoy more\n"
	.string "than just exquisite dining.\p"
	.string "You may also partake in battles. Bon\n"
	.string "appetit!$"
