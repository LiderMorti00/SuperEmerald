GalacticHQ_Hall_sinnoh_MapScripts::
	.byte 0


GalacticHQ_Hall_EventScript_SNSpeech_T0::
	.string "Looker: Psst! Here. Over here.\p"
	.string "This gathering of the Team Galactic...\n"
	.string "What is the meaning of it?$"

SE_S_GalacticHQ_Hall_GalacticHQ_Hall_EventScript_SNSpeech::
	msgbox GalacticHQ_Hall_EventScript_SNSpeech_T0, MSGBOX_NPC
	end

GalacticHQ_Hall_EventScript_SNSpeech_Cyrus::
	msgbox GalacticHQ_Hall_EventScript_SNSpeech_T1, MSGBOX_NPC
	end

GalacticHQ_Hall_EventScript_SNSpeech_T1::
	.string "Cyrus: Fellow members of Team Galactic!\n"
	.string "Hear me!\p"
	.string "My name, as I appear to you today, is\n"
	.string "Cyrus.\p"
	.string "This world of ours is a crude one. In a\n"
	.string "word, it is incomplete.\p"
	.string "It has been, and always will be, a\n"
	.string "struggle to survive in this world.\p"
	.string "We humans and POKéMON are likewise\n"
	.string "incomplete.\p"
	.string "Because we are all so lacking, we fight,\n"
	.string "we maim... It is ugly.\p"
	.string "I hate the incompleteness.\p"
	.string "That we are all incomplete, I hate it\n"
	.string "with my entire body and being.\p"
	.string "The world should be complete. The world\n"
	.string "must change.$"

GalacticHQ_Hall_EventScript_SNSpeech_Grunt::
	msgbox GalacticHQ_Hall_EventScript_SNSpeech_T6, MSGBOX_NPC
	end

GalacticHQ_Hall_EventScript_SNSpeech_T6::
	.string "Grunt: Master Cyrus is the greatest!$"
