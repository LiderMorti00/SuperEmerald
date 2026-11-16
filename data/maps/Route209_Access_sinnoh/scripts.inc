Route209_Access_sinnoh_MapScripts::
	.byte 0


Route209_Access_EventScript_PtNpc1::
	msgbox Route209_Access_Text_PtNpc1, MSGBOX_NPC
	end

Route209_Access_Text_PtNpc1::
	.string "There's a wrecked stone pillar up\n"
	.string "ahead.\p"
	.string "I wonder what it is? It's got me very\n"
	.string "curious.$"

Route209_Access_EventScript_SNBarry_Intro::
	.string "BARRY: Ta-daah! Kept me waiting again,\n"
	.string "{PLAYER}!\p"
	.string "Let’s see how much tougher you and I\n"
	.string "have gotten, right here and now!\p"
	.string "Hey, you’re a Trainer now. You’re\n"
	.string "expected to be ready for a battle.\p"
	.string "No whining! No waiting! Let’s get the\n"
	.string "show started!$"

SE_S_Route209_Access_Route209_Access_EventScript_SNBarry::
	msgbox Route209_Access_EventScript_SNBarry_Intro, MSGBOX_NPC
	end
