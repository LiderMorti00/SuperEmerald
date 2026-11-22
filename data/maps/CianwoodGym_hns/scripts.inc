CianwoodGym_hns_MapScripts::
	.byte 0


CianwoodGym_Text_ChuckIntro1::
	.string "WAHAHAH!\p"
	.string "So you've come this far!\p"
	.string "Let me tell you, I'm tough!\p"
	.string "My POKéMON will crush stones and\n"
	.string "shatter bones!\p"
	.string "Watch this!$"

SE_J_CianwoodGym_hns_CianwoodGym_EventScript_Chuck::
	msgbox CianwoodGym_Text_ChuckIntro1, MSGBOX_NPC
	end

CianwoodGym_EventScript_Nob::
	trainerbattle_single TRAINER_NOB_HNS, CianwoodGym_Text_BlackbeltNobSeen, CianwoodGym_Text_BlackbeltNobBeaten
	msgbox CianwoodGym_Text_BlackbeltNobAfter, MSGBOX_AUTOCLOSE
	end

CianwoodGym_Text_BlackbeltNobAfter::
	.string "I lost! I'm speechless!$"

CianwoodGym_Text_BlackbeltNobBeaten::
	.string "…$"

CianwoodGym_Text_BlackbeltNobSeen::
	.string "Words are useless.\n"
	.string "Let your fists do the talking!$"

CianwoodGym_EventScript_Yoshi::
	trainerbattle_single TRAINER_YOSHI_HNS, CianwoodGym_Text_BlackbeltYoshiSeen, CianwoodGym_Text_BlackbeltYoshiBeaten
	msgbox CianwoodGym_Text_BlackbeltYoshiAfter, MSGBOX_AUTOCLOSE
	end

CianwoodGym_Text_BlackbeltYoshiAfter::
	.string "You seem to have a strong bond\n"
	.string "with your POKéMON too!$"

CianwoodGym_Text_BlackbeltYoshiBeaten::
	.string "This isn't real!$"

CianwoodGym_Text_BlackbeltYoshiSeen::
	.string "My POKéMON and I are bound togeth-\n"
	.string "er by friendship.\p"
	.string "Our bond will never be broken!$"

CianwoodGym_EventScript_Lao::
	trainerbattle_single TRAINER_LAO_HNS, CianwoodGym_Text_BlackbeltLaoSeen, CianwoodGym_Text_BlackbeltLaoBeaten
	msgbox CianwoodGym_Text_BlackbeltLaoAfter, MSGBOX_AUTOCLOSE
	end

CianwoodGym_Text_BlackbeltLaoAfter::
	.string "Fighting POKéMON are afraid of\n"
	.string "psychics…$"

CianwoodGym_Text_BlackbeltLaoBeaten::
	.string "That's shocking!$"

CianwoodGym_Text_BlackbeltLaoSeen::
	.string "We martial artists fear nothing!$"

CianwoodGym_EventScript_Lung::
	trainerbattle_single TRAINER_LUNG_HNS, CianwoodGym_Text_BlackbeltLungSeen, CianwoodGym_Text_BlackbeltLungBeaten
	msgbox CianwoodGym_Text_BlackbeltLungAfter, MSGBOX_AUTOCLOSE
	end

CianwoodGym_Text_BlackbeltLungAfter::
	.string "My POKéMON lost…\n"
	.string "My… my pride is shattered…$"

CianwoodGym_Text_BlackbeltLungBeaten::
	.string "I got shattered!$"

CianwoodGym_Text_BlackbeltLungSeen::
	.string "My raging fists will shatter your\n"
	.string "POKéMON!$"

CianwoodGym_EventScript_Statue::
	lock
	goto_if_set FLAG_JOHTO_BADGE5_GET, CianwoodGym_EventScript_Statue2
	msgbox CianwoodGym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodGym_Text_GymStatue::
	.string "CIANWOOD CITY POKéMON GYM$"

CianwoodGym_EventScript_Statue2::
	msgbox CianwoodGym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodGym_Text_GymStatueCertified::
	.string "CIANWOOD CITY POKéMON GYM\p"
	.string "CHUCK'S CERTIFIED TRAINERS:\n"
	.string "{PLAYER}$"
