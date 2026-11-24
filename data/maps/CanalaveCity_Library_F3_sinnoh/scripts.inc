CanalaveCity_Library_F3_sinnoh_MapScripts::
	.byte 0

CanalaveCity_Library_F3_EventScript_PtNpc1::
	lock
	faceplayer
	goto_if_set FLAG_SN_LAKE_VALOR_EXPLODED_3, CanalaveCity_Library_F3_EventScript_PtNpc1_WasThatAnEarthquake
	msgbox CanalaveCity_Library_F3_Text_PtNpc1_0, MSGBOX_DEFAULT
	release
	end

CanalaveCity_Library_F3_Text_PtNpc1_0::
	.string "Every book contains someone's\n"
	.string "memories of various places and times.\p"
	.string "Libraries aren't just buildings where\n"
	.string "books are kept, you know.\p"
	.string "They're where different places and\n"
	.string "times are gathered together.$"

CanalaveCity_Library_F3_EventScript_PtNpc1_WasThatAnEarthquake::
	msgbox CanalaveCity_Library_F3_Text_PtNpc1_1, MSGBOX_DEFAULT
	release
	end

CanalaveCity_Library_F3_Text_PtNpc1_1::
	.string "W-was that an earthquake? I didn't\n"
	.string "imagine it?$"

CanalaveCity_Library_F3_EventScript_PtNpc2::
	lock
	faceplayer
	goto_if_set FLAG_SN_LAKE_VALOR_EXPLODED_3, CanalaveCity_Library_F3_EventScript_PtNpc2_ImFeelingWobbly
	msgbox CanalaveCity_Library_F3_Text_PtNpc2_0, MSGBOX_DEFAULT
	release
	end

CanalaveCity_Library_F3_Text_PtNpc2_0::
	.string "Someone's always checked out the book\n"
	.string "I want to read…$"

CanalaveCity_Library_F3_EventScript_PtNpc2_ImFeelingWobbly::
	msgbox CanalaveCity_Library_F3_Text_PtNpc2_1, MSGBOX_DEFAULT
	release
	end

CanalaveCity_Library_F3_Text_PtNpc2_1::
	.string "I'm feeling wobbly…\p"
	.string "Even though the tremor has ended, my\n"
	.string "knees still feel like jelly…$"

CanalaveCity_Library_F3_EventScript_PtSign1::
	goto CanalaveCity_Library_F3_EventScript_SNBookSinnohMyth
	end

CanalaveCity_Library_F3_EventScript_SNBookSinnohMyth::
	lockall
	msgbox CanalaveCity_Library_F3_Text_SNAskReadSinnohMyth, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CanalaveCity_Library_F3_EventScript_SNBookSinnohMyth_Back
	msgbox CanalaveCity_Library_F3_Text_SNSinnohMyth, MSGBOX_DEFAULT
	releaseall
	end

CanalaveCity_Library_F3_Text_SNSinnohMyth::
	.string "“SINNOH Myth”\p"
	.string "Betray not your anger, lest ??? will\n"
	.string "come.\p"
	.string "Weep not with sorrow, or ??? will draw\n"
	.string "near.\p"
	.string "When joy and enjoyment come natural\n"
	.string "as the very air, that is happiness.\p"
	.string "Let such be blessed by the hand of\n"
	.string "Master ???.\p"
	.string "Those words were spoken often as\n"
	.string "customary.$"

CanalaveCity_Library_F3_EventScript_SNBookSinnohMyth_Back::
	msgbox CanalaveCity_Library_F3_Text_SNPutSinnohMythBack, MSGBOX_DEFAULT
	releaseall
	end

CanalaveCity_Library_F3_Text_SNPutSinnohMythBack::
	.string "{PLAYER} put the book back.$"

CanalaveCity_Library_F3_Text_SNAskReadSinnohMyth::
	.string "This book is titled “SINNOH Myth.” Want\n"
	.string "to read it?$"

CanalaveCity_Library_F3_EventScript_PtSign2::
	goto CanalaveCity_Library_F3_EventScript_SNBookSinnohMyth
	end

CanalaveCity_Library_F3_EventScript_PtSign3::
	goto CanalaveCity_Library_F3_EventScript_SNBookSinnohRegionsMythology
	end

CanalaveCity_Library_F3_EventScript_SNBookSinnohRegionsMythology::
	lockall
	msgbox CanalaveCity_Library_F3_Text_SNAskReadSinnohRegionsMythology, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CanalaveCity_Library_F3_EventScript_SNBookSinnohRegionsMythology_Back
	msgbox CanalaveCity_Library_F3_Text_SNSinnohRegionsMythology, MSGBOX_DEFAULT
	releaseall
	end

CanalaveCity_Library_F3_Text_SNSinnohRegionsMythology::
	.string "“SINNOH Region's Mythology”\p"
	.string "Long ago, when SINNOH had just been\n"
	.string "made, POKéMON and humans led\p"
	.string "separate lives.\p"
	.string "That is not to say they did not help\n"
	.string "each other. No, indeed they did.\p"
	.string "They supplied each other with goods,\n"
	.string "and supported each other.\p"
	.string "A POKéMON proposed to the others to\n"
	.string "always be ready to help humans.\p"
	.string "It asked that POKéMON be ready to\n"
	.string "appear before humans always.\p"
	.string "Thus, to this day, POKéMON appear to us\n"
	.string "if we venture into tall grass.$"

CanalaveCity_Library_F3_EventScript_SNBookSinnohRegionsMythology_Back::
	msgbox CanalaveCity_Library_F3_Text_SNPutSinnohRegionsMythologyBack, MSGBOX_DEFAULT
	releaseall
	end

CanalaveCity_Library_F3_Text_SNPutSinnohRegionsMythologyBack::
	.string "{PLAYER} put the book back.$"

CanalaveCity_Library_F3_Text_SNAskReadSinnohRegionsMythology::
	.string "This book is titled “SINNOH Region's\n"
	.string "Mythology.” Want to read it?$"

CanalaveCity_Library_F3_EventScript_PtSign4::
	goto CanalaveCity_Library_F3_EventScript_SNBookSinnohRegionsMythology
	end

CanalaveCity_Library_F3_EventScript_PtSign5::
	goto CanalaveCity_Library_F3_EventScript_SNBookSinnohsMyth
	end

CanalaveCity_Library_F3_EventScript_SNBookSinnohsMyth::
	lockall
	msgbox CanalaveCity_Library_F3_Text_SNAskReadSinnohsMyth, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CanalaveCity_Library_F3_EventScript_SNBookSinnohsMyth_Back
	msgbox CanalaveCity_Library_F3_Text_SNSinnohsMyth, MSGBOX_DEFAULT
	releaseall
	end

CanalaveCity_Library_F3_Text_SNSinnohsMyth::
	.string "“SINNOH's Myth”\p"
	.string "Three POKéMON there were.\p"
	.string "Into the lakes they dove. Deep, deep,\n"
	.string "drawing no breath.\p"
	.string "Deeper, deeper they dove. Into\n"
	.string "suffocating depths they dove.\p"
	.string "Deeper, then deepest they alight. From\n"
	.string "the lake floor they rise.\p"
	.string "Bearing with them the power to make\n"
	.string "vast lands, they rise again.$"

CanalaveCity_Library_F3_EventScript_SNBookSinnohsMyth_Back::
	msgbox CanalaveCity_Library_F3_Text_SNPutSinnohsMythBack, MSGBOX_DEFAULT
	releaseall
	end

CanalaveCity_Library_F3_Text_SNPutSinnohsMythBack::
	.string "{PLAYER} put the book back.$"

CanalaveCity_Library_F3_Text_SNAskReadSinnohsMyth::
	.string "This book is titled “SINNOH's Myth.”\n"
	.string "Want to read it?$"

CanalaveCity_Library_F3_EventScript_PtSign6::
	goto CanalaveCity_Library_F3_EventScript_SNBookSinnohsMyth
	end

CanalaveCity_Library_F3_EventScript_PtSign7::
	goto CanalaveCity_Library_F3_EventScript_SNBookVeilstonesMyth
	end

CanalaveCity_Library_F3_EventScript_SNBookVeilstonesMyth::
	lockall
	msgbox CanalaveCity_Library_F3_Text_SNAskReadVeilstonesMyth, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CanalaveCity_Library_F3_EventScript_SNBookVeilstonesMyth_Back
	msgbox CanalaveCity_Library_F3_Text_SNVeilstonesMyth1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CanalaveCity_Library_F3_EventScript_SNBookVeilstonesMyth_Back
	msgbox CanalaveCity_Library_F3_Text_SNVeilstonesMyth2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CanalaveCity_Library_F3_EventScript_SNBookVeilstonesMyth_Back
	msgbox CanalaveCity_Library_F3_Text_SNVeilstonesMyth3, MSGBOX_DEFAULT
	releaseall
	end

CanalaveCity_Library_F3_Text_SNVeilstonesMyth3::
	.string "To the skies, the young man shouted\n"
	.string "his dismay.\p"
	.string "“In having found the sword, I have\n"
	.string "lost so much.\p"
	.string "“Gorged with power, I grew blind to\n"
	.string "POKéMON being alive.\p"
	.string "“I will never fall savage again. This\n"
	.string "sword I denounce and forsake.\p"
	.string "“I plead for forgiveness, for I was but\n"
	.string "a fool.”\p"
	.string "So saying, the young man hurled the\n"
	.string "sword to the ground, snapping it.\p"
	.string "Seeing this, the POKéMON disappeared\n"
	.string "to a place beyond seeing…$"

CanalaveCity_Library_F3_EventScript_SNBookVeilstonesMyth_Back::
	msgbox CanalaveCity_Library_F3_Text_SNPutVeilstonesMythBack, MSGBOX_DEFAULT
	releaseall
	end

CanalaveCity_Library_F3_Text_SNPutVeilstonesMythBack::
	.string "{PLAYER} put the book back.$"

CanalaveCity_Library_F3_Text_SNVeilstonesMyth2::
	.string "The young man, seeking the missing\n"
	.string "POKéMON, journeyed afar.\p"
	.string "Long did he search. And far and wide,\n"
	.string "too, until one he did find.\p"
	.string "Asked he, “Why do you hide?” To which\n"
	.string "the POKéMON replied…\p"
	.string "“If you bear your sword to bring harm\n"
	.string "upon us, with claws and\p"
	.string "fangs, we will exact a toll.\p"
	.string "“From your kind we will take our toll,\n"
	.string "for it must be done.\p"
	.string "“Done it must be to guard ourselves\n"
	.string "and for it, I apologize.”\p"
	.string "…Would you like to keep reading?$"

CanalaveCity_Library_F3_Text_SNVeilstonesMyth1::
	.string "“VEILSTONE's Myth”\p"
	.string "A young man, callow and foolish in\n"
	.string "innocence, came to own a sword.\p"
	.string "With it, he smote POKéMON, which gave\n"
	.string "sustenance, with carefree abandon.\p"
	.string "Those not taken as food, he discarded,\n"
	.string "with no afterthought.\p"
	.string "The following year, no POKéMON\n"
	.string "appeared. Larders grew bare.\p"
	.string "…Would you like to keep reading?$"

CanalaveCity_Library_F3_Text_SNAskReadVeilstonesMyth::
	.string "This book is titled “VEILSTONE's Myth.”\n"
	.string "Want to read it?$"

CanalaveCity_Library_F3_EventScript_PtSign8::
	goto CanalaveCity_Library_F3_EventScript_SNBookVeilstonesMyth
	end

CanalaveCity_Library_F3_EventScript_PtSign9::
	goto CanalaveCity_Library_F3_EventScript_SNBookTheOriginalStory
	end

CanalaveCity_Library_F3_EventScript_SNBookTheOriginalStory::
	lockall
	msgbox CanalaveCity_Library_F3_Text_SNAskReadTheOriginalStory, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CanalaveCity_Library_F3_EventScript_SNBookTheOriginalStory_Back
	msgbox CanalaveCity_Library_F3_Text_SNTheOriginalStory1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CanalaveCity_Library_F3_EventScript_SNBookTheOriginalStory_Back
	msgbox CanalaveCity_Library_F3_Text_SNTheOriginalStory2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CanalaveCity_Library_F3_EventScript_SNBookTheOriginalStory_Back
	msgbox CanalaveCity_Library_F3_Text_SNTheOriginalStory3, MSGBOX_DEFAULT
	releaseall
	end

CanalaveCity_Library_F3_Text_SNTheOriginalStory3::
	.string "The two beings wished, and from them,\n"
	.string "matter came to be.\p"
	.string "The three living things wished, and\n"
	.string "from them, spirit came to be.\p"
	.string "The world created, the Original One\n"
	.string "took to unyielding sleep…$"

CanalaveCity_Library_F3_EventScript_SNBookTheOriginalStory_Back::
	msgbox CanalaveCity_Library_F3_Text_SNPutTheOriginalStoryBack, MSGBOX_DEFAULT
	releaseall
	end

CanalaveCity_Library_F3_Text_SNPutTheOriginalStoryBack::
	.string "{PLAYER} put the book back.$"

CanalaveCity_Library_F3_Text_SNTheOriginalStory2::
	.string "From itself, two beings the Original\n"
	.string "One did make.\p"
	.string "Time started to spin. Space began to\n"
	.string "expand.\p"
	.string "From itself again, three living things\n"
	.string "the Original One did make.\p"
	.string "…Would you like to keep reading?$"

CanalaveCity_Library_F3_Text_SNTheOriginalStory1::
	.string "In the beginning, there was only a\n"
	.string "churning turmoil of chaos.\p"
	.string "At the heart of chaos, where all things\n"
	.string "became one, appeared an EGG.\p"
	.string "Having tumbled from the vortex, the\n"
	.string "Egg gave rise to the Original One.\p"
	.string "…Would you like to keep reading?$"

CanalaveCity_Library_F3_Text_SNAskReadTheOriginalStory::
	.string "This ancient book is titled “The\n"
	.string "Original Story.” Want to read it?$"

CanalaveCity_Library_F3_EventScript_PtSign10::
	goto CanalaveCity_Library_F3_EventScript_SNBookTheOriginalStory
	end

CanalaveCity_Library_F3_EventScript_PtSign11::
	goto CanalaveCity_Library_F3_EventScript_SNBookHorrificMyth
	end

CanalaveCity_Library_F3_EventScript_SNBookHorrificMyth::
	lockall
	msgbox CanalaveCity_Library_F3_Text_SNAskReadHorrificMyth, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CanalaveCity_Library_F3_EventScript_SNBookHorrificMyth_Back
	msgbox CanalaveCity_Library_F3_Text_SNHorrificMyth, MSGBOX_DEFAULT
	releaseall
	end

CanalaveCity_Library_F3_Text_SNHorrificMyth::
	.string "Look not into the POKéMON's eyes.\p"
	.string "In but an instant, you'll have no\n"
	.string "recollection of who you are.\p"
	.string "Return home, but how? When there is\n"
	.string "nothing to remember?\p"
	.string "Dare not touch the POKéMON's body.\p"
	.string "In but three short days, all emotions\n"
	.string "will drain away.\p"
	.string "Above all, above all, harm not the\n"
	.string "POKéMON.\p"
	.string "In a scant five days, the offender will\n"
	.string "grow immobile in entirety.$"

CanalaveCity_Library_F3_EventScript_SNBookHorrificMyth_Back::
	msgbox CanalaveCity_Library_F3_Text_SNPutHorrificMythBack, MSGBOX_DEFAULT
	releaseall
	end

CanalaveCity_Library_F3_Text_SNPutHorrificMythBack::
	.string "{PLAYER} put the book back.$"

CanalaveCity_Library_F3_Text_SNAskReadHorrificMyth::
	.string "This book is titled “A Horrific Myth.”\n"
	.string "Want to read it?$"

CanalaveCity_Library_F3_EventScript_PtSign12::
	goto CanalaveCity_Library_F3_EventScript_SNBookHorrificMyth
	end

CanalaveCity_Library_F3_EventScript_PtSign13::
	goto CanalaveCity_Library_F3_EventScript_SNBookSinnohFolkStories
	end

CanalaveCity_Library_F3_EventScript_SNBookSinnohFolkStories::
	lockall
	msgbox CanalaveCity_Library_F3_Text_SNSinnohFolkStories, MSGBOX_DEFAULT
	message CanalaveCity_Library_F3_Text_SNReadWhichStory
	waitmessage
	dynmultichoice 0, 0, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, CanalaveCity_Library_F3_Text_SNPart1, CanalaveCity_Library_F3_Text_SNPart2, CanalaveCity_Library_F3_Text_SNPart3, CanalaveCity_Library_F3_Text_SNExit
	switch VAR_RESULT
	case 0, CanalaveCity_Library_F3_EventScript_SNBookSinnohFolkStories_1
	case 1, CanalaveCity_Library_F3_EventScript_SNBookSinnohFolkStories_2
	case 2, CanalaveCity_Library_F3_EventScript_SNBookSinnohFolkStories_3
	msgbox CanalaveCity_Library_F3_Text_SNPutSinnohFolkStoriesBack, MSGBOX_DEFAULT
	releaseall
	end

CanalaveCity_Library_F3_Text_SNPutSinnohFolkStoriesBack::
	.string "{PLAYER} put the book back.$"

CanalaveCity_Library_F3_EventScript_SNBookSinnohFolkStories_3::
	msgbox CanalaveCity_Library_F3_Text_SNSinnohFolkStory3, MSGBOX_DEFAULT
	releaseall
	end

CanalaveCity_Library_F3_Text_SNSinnohFolkStory3::
	.string "“SINNOH Folk Story 3”\p"
	.string "There once were POKéMON that became\n"
	.string "very close to humans.\p"
	.string "There once were humans and POKéMON\n"
	.string "that ate together at the same table.\p"
	.string "It was a time when there existed no\n"
	.string "differences to distinguish the two.$"

CanalaveCity_Library_F3_EventScript_SNBookSinnohFolkStories_2::
	msgbox CanalaveCity_Library_F3_Text_SNSinnohFolkStory2, MSGBOX_DEFAULT
	releaseall
	end

CanalaveCity_Library_F3_Text_SNSinnohFolkStory2::
	.string "“SINNOH Folk Story 2”\p"
	.string "There lived a POKéMON in a forest.\p"
	.string "In the forest, the POKéMON shed its\n"
	.string "hide to sleep as a human.\p"
	.string "Awakened, the human dons the POKéMON\n"
	.string "hide to roam villages.$"

CanalaveCity_Library_F3_EventScript_SNBookSinnohFolkStories_1::
	msgbox CanalaveCity_Library_F3_Text_SNSinnohFolkStory1, MSGBOX_DEFAULT
	releaseall
	end

CanalaveCity_Library_F3_Text_SNSinnohFolkStory1::
	.string "“SINNOH Folk Story 1”\p"
	.string "Pick clean the bones of POKéMON\n"
	.string "caught in the sea or stream.\p"
	.string "Thank them for the meals they provide,\n"
	.string "and pick their bones clean.\p"
	.string "When the bones are as clean as can be,\n"
	.string "set them free in the water from\p"
	.string "which they came.\p"
	.string "The POKéMON will return, fully fleshed,\n"
	.string "and it begins anew.$"

CanalaveCity_Library_F3_Text_SNExit::
	.string "EXIT$"

CanalaveCity_Library_F3_Text_SNPart3::
	.string "PART 3$"

CanalaveCity_Library_F3_Text_SNPart2::
	.string "PART 2$"

CanalaveCity_Library_F3_Text_SNPart1::
	.string "PART 1$"

CanalaveCity_Library_F3_Text_SNReadWhichStory::
	.string "Which story would you like to read?$"

CanalaveCity_Library_F3_Text_SNSinnohFolkStories::
	.string "This book is titled “SINNOH Folk\n"
	.string "Stories.”$"

CanalaveCity_Library_F3_EventScript_PtSign14::
	goto CanalaveCity_Library_F3_EventScript_SNBookSinnohFolkStories
	end

CanalaveCity_Library_F3_EventScript_PtSign15::
	msgbox CanalaveCity_Library_F3_Text_PtSign15, MSGBOX_SIGN
	end

CanalaveCity_Library_F3_Text_PtSign15::
	.string "On this floor, you will find many books\n"
	.string "on the myths and legends of\p"
	.string "the SINNOH region.$"

CanalaveCity_Library_F3_EventScript_PtSign16::
	goto CanalaveCity_Library_F3_EventScript_SNBookTheOriginalStory
	end

CanalaveCity_Library_F3_EventScript_PtSign17::
	goto CanalaveCity_Library_F3_EventScript_SNBookTheOriginalStory
	end

CanalaveCity_Library_F3_EventScript_PtSign18::
	goto CanalaveCity_Library_F3_EventScript_SNBookTheOriginalStory
	end

CanalaveCity_Library_F3_EventScript_PtSign19::
	goto CanalaveCity_Library_F3_EventScript_SNBookHorrificMyth
	end

CanalaveCity_Library_F3_EventScript_PtSign20::
	goto CanalaveCity_Library_F3_EventScript_SNBookHorrificMyth
	end

CanalaveCity_Library_F3_EventScript_PtSign21::
	goto CanalaveCity_Library_F3_EventScript_SNBookSinnohFolkStories
	end

CanalaveCity_Library_F3_EventScript_PtSign22::
	goto CanalaveCity_Library_F3_EventScript_SNBookSinnohFolkStories
	end
