OlivineCity_Gym_hns_MapScripts::
	.byte 0


OlivineCity_Gym_Text_JasmineSteelTypeIntro::
	.string "…Thank you for your help at the\n"
	.string "LIGHTHOUSE…\p"
	.string "But this is different.\n"
	.string "Please allow me to introduce myself.\p"
	.string "I am JASMINE, a GYM LEADER.\n"
	.string "I use the STEEL-type.\p"
	.string "…Do you know about the STEEL-type?\p"
	.string "It's a type that was only recently\n"
	.string "discovered.\p"
	.string "…Um… May I begin?$"

SE_J_OlivineCity_Gym_hns_OlivineCity_Gym_EventScript_Jasmine::
	msgbox OlivineCity_Gym_Text_JasmineSteelTypeIntro, MSGBOX_NPC
	end

OlivineCity_Gym_EventScript_Lass::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_OLIVINE_CITY_GYM, OlivineCity_Gym_EventScript_Lass2
	msgbox OlivineCity_Gym_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Gym_Text_Lass::
	.string "Giggle...\n"
	.string "I know how capable you are\l"
	.string "from the LIGHTHOUSE.\p"
	.string "It's time you showed that side of\n"
	.string "yourself to JASMINE! Good luck!$"

OlivineCity_Gym_EventScript_Lass2::
	msgbox OlivineCity_Gym_Text_Lass2, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Gym_Text_Lass2::
	.string "You are amazing...\n"
	.string "You should aim even higher, since\l"
	.string "you have such potential.\p"
	.string "Have you been to MAHOGANY TOWN?$"

OlivineCity_Gym_EventScript_Gent::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_OLIVINE_CITY_GYM, OlivineCity_Gym_EventScript_Gent2
	msgbox OlivineCity_Gym_Text_Gent, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Gym_Text_Gent::
	.string "I knew you'd come here.\p"
	.string "Thank you for helping the GYM LEADER,\n"
	.string "but battle is a separate matter.\p"
	.string "Go for it!$"

OlivineCity_Gym_EventScript_Gent2::
	msgbox OlivineCity_Gym_Text_Gent2, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Gym_Text_Gent2::
	.string "Impressive!\n"
	.string "You should continue your journey to\l"
	.string "different places.\p"
	.string "Since you can use SURF, why don't you\n"
	.string "try it on the LAKE OF RAGE?$"

OlivineCity_Gym_Text_GymGuideText::
	.string "JASMINE uses the newly discovered\n"
	.string "STEEL-type.\p"
	.string "She's known for having not one,\n"
	.string "but two aces.\p"
	.string "The first is a metal bug that can\n"
	.string "use a technique to boost its ATTACK.\p"
	.string "While fire will hurt it, it can\n"
	.string "sometimes endure powerful blows.\p"
	.string "The second is a giant iron snake\n"
	.string "with lots of powerful moves.\p"
	.string "Approach it with caution.\p"
	.string "It may look slow, but I've seen it\n"
	.string "strike first with shocking displays\l"
	.string "of SPEED.$"

SE_J_OlivineCity_Gym_hns_OlivineCity_Gym_EventScript_GymGuide::
	msgbox OlivineCity_Gym_Text_GymGuideText, MSGBOX_NPC
	end

OlivineCity_Gym_EventScript_Statue::
	lock
	goto_if_set FLAG_DEFEATED_OLIVINE_CITY_GYM, OlivineCity_Gym_EventScript_Statue2
	msgbox OlivineCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Gym_Text_GymStatue::
	.string "OLIVINE CITY POKéMON GYM$"

OlivineCity_Gym_EventScript_Statue2::
	msgbox OlivineCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Gym_Text_GymStatueCertified::
	.string "OLIVINE CITY POKéMON GYM\p"
	.string "JASMINE'S CERTIFIED TRAINERS:\n"
	.string "{PLAYER}$"
