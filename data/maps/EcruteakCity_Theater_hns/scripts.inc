EcruteakCity_Theater_hns_MapScripts::
	.byte 0

EcruteakCity_Theater_Text_KimonoDone::
	.string "We are rehearsing a dance.$"

SE_J_EcruteakCity_Theater_hns_EcruteakCity_Theater_EventScript_KimonoGirl::
	msgbox EcruteakCity_Theater_Text_KimonoDone, MSGBOX_NPC
	end

EcruteakCity_Theater_Text_Kimono::
	.string "For KIMONO GIRLS like me,\n"
	.string "dancing is everything.\p"
	.string "I have never gone a day\n"
	.string "without a dance practice.\p"
	.string "POKéMON are the same.\n"
	.string "They grow with you little\l"
	.string "by little each day.$"

SE_J_EcruteakCity_Theater_hns_EcruteakCity_Theater_EventScript_Zuki::
	msgbox EcruteakCity_Theater_Text_Kimono, MSGBOX_NPC
	end

EcruteakCity_Theater_Text_Granny::
	.string "That man's always with his\n"
	.string "PSYDUCK.\p"
	.string "Says he wants a POKéMON that\n"
	.string "can SURF and dance.\p"
	.string "Is he trying to make a POKéMON\n"
	.string "that stars in synchronized\l"
	.string "swimming?$"

SE_J_EcruteakCity_Theater_hns_EcruteakCity_Theater_EventScript_Granny::
	msgbox EcruteakCity_Theater_Text_Granny, MSGBOX_NPC
	end

EcruteakCity_Theater_Text_SurfGuyAfter::
	.string "Not only are the KIMONO GIRLS\n"
	.string "great dancers, they're also\l"
	.string "skilled at POKéMON.\p"
	.string "But they battle only for good\n"
	.string "reasons.\p"
	.string "I don't know if you could beat\n"
	.string "them if they showed their skill…$"

SE_J_EcruteakCity_Theater_hns_EcruteakCity_Theater_EventScript_SurfGuy::
	msgbox EcruteakCity_Theater_Text_SurfGuyAfter, MSGBOX_NPC
	end

EcruteakCity_Theater_Text_Boy::
	.string "I tried to follow their steps once.\p"
	.string "By the time I turned around, the\n"
	.string "KIMONO GIRLS had finished the dance!$"

SE_J_EcruteakCity_Theater_hns_EcruteakCity_Theater_EventScript_Boy::
	msgbox EcruteakCity_Theater_Text_Boy, MSGBOX_NPC
	end

EcruteakCity_Theater_EventScript_Psyduck::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PSYDUCK, CRY_MODE_NORMAL
	msgbox EcruteakCity_Theater_Text_Psyduck, MSGBOX_DEFAULT
	waitmoncry
	release
	end

EcruteakCity_Theater_Text_Psyduck::
	.string "PSYDUCK: Dau dau!$"

EcruteakCity_Theater_Text_Gramps::
	.string "The KIMONO GIRLS are so\n"
	.string "beautiful…\p"
	.string "But they have to go through\n"
	.string "rigorous training.\p"
	.string "And they have to learn to follow\n"
	.string "customs before appearing in\l"
	.string "public.\p"
	.string "But if you love something,\n"
	.string "anything is possible.$"

SE_J_EcruteakCity_Theater_hns_EcruteakCity_Theater_EventScript_Gramps::
	msgbox EcruteakCity_Theater_Text_Gramps, MSGBOX_NPC
	end

EcruteakCity_Theater_Text_Girl::
	.string "The KIMONO GIRLS are my big\n"
	.string "sisters! I'll be like them one\l"
	.string "day!$"

SE_J_EcruteakCity_Theater_hns_EcruteakCity_Theater_EventScript_Girl::
	msgbox EcruteakCity_Theater_Text_Girl, MSGBOX_NPC
	end

EcruteakCity_Theater_EventScript_FancyPanel::
	lock
	msgbox EcruteakCity_Theater_Text_FancyPanel, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Theater_Text_FancyPanel::
	.string "It's a fancy panel that's\n"
	.string "decorated with flowers.$"
