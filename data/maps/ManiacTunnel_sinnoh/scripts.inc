ManiacTunnel_sinnoh_MapScripts::
	.byte 0


ManiacTunnel_Text_SNGoCatch::
	.string "Everyone calls me the Ruin Maniac. I\n"
	.string "don’t care what they call me.\p"
	.string "I’ll just keep on chipping away at the\n"
	.string "rock wall little by little.\p"
	.string "Do you know why? I’m a Ruin Maniac who\n"
	.string "is fascinated by the UNOWN.\p"
	.string "I know it’s a little sudden, but how\n"
	.string "about you and me have a race?\p"
	.string "You go and catch the UNOWN, and I’ll\n"
	.string "keep digging away.\p"
	.string "We’ll have a race to see who can get\n"
	.string "done faster.$"

SE_S_ManiacTunnel_ManiacTunnel_EventScript_SNManiac::
	msgbox ManiacTunnel_Text_SNGoCatch, MSGBOX_NPC
	end

ManiacTunnel_EventScript_SNWall::
	msgbox ManiacTunnel_Text_SNWall, MSGBOX_SIGN
	end

ManiacTunnel_Text_SNWall::
	.string "The Ruin Maniac is still digging\n"
	.string "through this rock wall.\p"
	.string "It seems he needs more UNOWN to keep\n"
	.string "going...$"
