ValorLakefront_Restaurant_sinnoh_MapScripts::
	.byte 0


ValorLakefront_Restaurant_EventScript_SNT0::
	setvar VAR_0x8004, 0
	goto ValorLakefront_Restaurant_EventScript_SNTable

ValorLakefront_Restaurant_EventScript_SNTable::
	lockall
	special SinnohRestaurantCouple
	switch VAR_RESULT
	case 0, ValorLakefront_Restaurant_EventScript_SNC0
	case 1, ValorLakefront_Restaurant_EventScript_SNC1
	case 2, ValorLakefront_Restaurant_EventScript_SNC2
	case 3, ValorLakefront_Restaurant_EventScript_SNC3
	case 4, ValorLakefront_Restaurant_EventScript_SNC4
	case 5, ValorLakefront_Restaurant_EventScript_SNC5
	case 6, ValorLakefront_Restaurant_EventScript_SNC6
	case 7, ValorLakefront_Restaurant_EventScript_SNC7
	case 8, ValorLakefront_Restaurant_EventScript_SNC8
	releaseall
	end

ValorLakefront_Restaurant_EventScript_SNC8::
	goto_if_defeated TRAINER_MARLENE_SINNOH, ValorLakefront_Restaurant_EventScript_SNC8_Done
	specialvar VAR_RESULT, CountPartyAliveNonEggMons
	goto_if_lt VAR_RESULT, 2, ValorLakefront_Restaurant_EventScript_SNC8_Need
	special SinnohRestaurantVariant
	switch VAR_RESULT
	case 1, ValorLakefront_Restaurant_EventScript_SNC8_V1
	case 2, ValorLakefront_Restaurant_EventScript_SNC8_V2
	msgbox ValorLakefront_Restaurant_Text_SNREmilioIntro0, MSGBOX_DEFAULT
	faceplayer
	msgbox ValorLakefront_Restaurant_Text_SNREmilioAsk0, MSGBOX_YESNO
	goto ValorLakefront_Restaurant_EventScript_SNC8_Ans

ValorLakefront_Restaurant_EventScript_SNC8_Done::
	msgbox ValorLakefront_Restaurant_Text_SNREmilioDef0, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_EventScript_SNC8_Ans::
	goto_if_eq VAR_RESULT, NO, ValorLakefront_Restaurant_EventScript_SNC_End
	closemessage
	trainerbattle_two_trainers TRAINER_MARLENE_SINNOH, ValorLakefront_Restaurant_Text_SNREmilioLose, TRAINER_HELENE_SINNOH, ValorLakefront_Restaurant_Text_SNRKayleeLose
	special SinnohRestaurantVariant
	switch VAR_RESULT
	case 1, ValorLakefront_Restaurant_EventScript_SNC8_D1
	case 2, ValorLakefront_Restaurant_EventScript_SNC8_D2
	goto ValorLakefront_Restaurant_EventScript_SNC8_Done

ValorLakefront_Restaurant_EventScript_SNC8_D2::
	msgbox ValorLakefront_Restaurant_Text_SNRKayleeDef2, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_Text_SNRKayleeDef2::
	.string "Oh, dear, if we take in too many\n"
	.string "calories, we can always work them off\p"
	.string "by battling!$"

ValorLakefront_Restaurant_EventScript_SNC8_D1::
	msgbox ValorLakefront_Restaurant_Text_SNREmilioDef1, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_Text_SNREmilioDef1::
	.string "I feel compelled to analyze that which\n"
	.string "is unknown to me.\p"
	.string "By defining its composition, I feel\n"
	.string "reassured in my knowledge.$"

ValorLakefront_Restaurant_Text_SNRKayleeLose::
	.string "Oh!$"

ValorLakefront_Restaurant_Text_SNREmilioLose::
	.string "Oh!$"

ValorLakefront_Restaurant_EventScript_SNC_End::
	releaseall
	end

ValorLakefront_Restaurant_Text_SNREmilioDef0::
	.string "The results of that battle are\n"
	.string "insignificant. Let’s drink up.$"

ValorLakefront_Restaurant_Text_SNREmilioAsk0::
	.string "What is it? You are?\p"
	.string "... ...Oh, yes, a TRAINER.$"

ValorLakefront_Restaurant_Text_SNREmilioIntro0::
	.string "Hmm... This beverage’s coloration\n"
	.string "borders on the positively toxic...\p"
	.string "However, my analysis indicates that it\n"
	.string "is composed of natural ingredients.$"

ValorLakefront_Restaurant_EventScript_SNC8_V2::
	msgbox ValorLakefront_Restaurant_Text_SNRKayleeIntro2, MSGBOX_DEFAULT
	faceplayer
	msgbox ValorLakefront_Restaurant_Text_SNRKayleeAsk2, MSGBOX_YESNO
	goto ValorLakefront_Restaurant_EventScript_SNC8_Ans

ValorLakefront_Restaurant_Text_SNRKayleeAsk2::
	.string "Oh, what good timing!\p"
	.string "Would you join us for a quick battle?$"

ValorLakefront_Restaurant_Text_SNRKayleeIntro2::
	.string "There isn’t any point getting\n"
	.string "impatient over the food, dear.\p"
	.string "Isn’t this the sort of situation that\n"
	.string "you brought your POKéMON for?$"

ValorLakefront_Restaurant_EventScript_SNC8_V1::
	msgbox ValorLakefront_Restaurant_Text_SNREmilioIntro1, MSGBOX_DEFAULT
	faceplayer
	msgbox ValorLakefront_Restaurant_Text_SNREmilioAsk1, MSGBOX_YESNO
	goto ValorLakefront_Restaurant_EventScript_SNC8_Ans

ValorLakefront_Restaurant_Text_SNREmilioAsk1::
	.string "What is it now? Do you want me to\n"
	.string "analyze your skill level?$"

ValorLakefront_Restaurant_Text_SNREmilioIntro1::
	.string "Interesting... These hors d’oeuvres are\n"
	.string "fascinating.\p"
	.string "Plant fiber 20%, iron 5%, protein 35%.\n"
	.string "Curious and curiouser...$"

ValorLakefront_Restaurant_EventScript_SNC8_Need::
	msgbox ValorLakefront_Restaurant_Text_SNREmilioNeed, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_Text_SNREmilioNeed::
	.string "One POKéMON is insufficient if you\n"
	.string "want to battle against us.$"

ValorLakefront_Restaurant_EventScript_SNC7::
	goto_if_defeated TRAINER_JOHNSON_SINNOH, ValorLakefront_Restaurant_EventScript_SNC7_Done
	specialvar VAR_RESULT, CountPartyAliveNonEggMons
	goto_if_lt VAR_RESULT, 2, ValorLakefront_Restaurant_EventScript_SNC7_Need
	special SinnohRestaurantVariant
	switch VAR_RESULT
	case 1, ValorLakefront_Restaurant_EventScript_SNC7_V1
	case 2, ValorLakefront_Restaurant_EventScript_SNC7_V2
	msgbox ValorLakefront_Restaurant_Text_SNRKendrickIntro0, MSGBOX_DEFAULT
	faceplayer
	msgbox ValorLakefront_Restaurant_Text_SNRKendrickAsk0, MSGBOX_YESNO
	goto ValorLakefront_Restaurant_EventScript_SNC7_Ans

ValorLakefront_Restaurant_EventScript_SNC7_Done::
	msgbox ValorLakefront_Restaurant_Text_SNRKendrickDef0, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_EventScript_SNC7_Ans::
	goto_if_eq VAR_RESULT, NO, ValorLakefront_Restaurant_EventScript_SNC_End
	closemessage
	trainerbattle_two_trainers TRAINER_JOHNSON_SINNOH, ValorLakefront_Restaurant_Text_SNRKendrickLose, TRAINER_DEVAN_SINNOH, ValorLakefront_Restaurant_Text_SNRGabriellaLose
	special SinnohRestaurantVariant
	switch VAR_RESULT
	case 1, ValorLakefront_Restaurant_EventScript_SNC7_D1
	case 2, ValorLakefront_Restaurant_EventScript_SNC7_D2
	goto ValorLakefront_Restaurant_EventScript_SNC7_Done

ValorLakefront_Restaurant_EventScript_SNC7_D2::
	msgbox ValorLakefront_Restaurant_Text_SNRGabriellaDef2, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_Text_SNRGabriellaDef2::
	.string "If it’s not premonition, did you... Maybe\n"
	.string "come from the future?$"

ValorLakefront_Restaurant_EventScript_SNC7_D1::
	msgbox ValorLakefront_Restaurant_Text_SNRKendrickDef1, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_Text_SNRKendrickDef1::
	.string "I had a bad feeling about this\n"
	.string "TRAINER...$"

ValorLakefront_Restaurant_Text_SNRGabriellaLose::
	.string "Oh!$"

ValorLakefront_Restaurant_Text_SNRKendrickLose::
	.string "Oh!$"

ValorLakefront_Restaurant_Text_SNRKendrickDef0::
	.string "This is just a minor setback. I can\n"
	.string "easily make up for this!$"

ValorLakefront_Restaurant_Text_SNRKendrickAsk0::
	.string "Since I’ve been with her, I’ve been\n"
	.string "riding a hot streak on the markets.\p"
	.string "I’m surfing on a wave of good luck!\n"
	.string "You’re sure you want to battle us?$"

ValorLakefront_Restaurant_Text_SNRKendrickIntro0::
	.string "And another brilliant day on the\n"
	.string "markets! A toast to my Lady Luck!$"

ValorLakefront_Restaurant_EventScript_SNC7_V2::
	msgbox ValorLakefront_Restaurant_Text_SNRGabriellaIntro2, MSGBOX_DEFAULT
	faceplayer
	msgbox ValorLakefront_Restaurant_Text_SNRGabriellaAsk2, MSGBOX_YESNO
	goto ValorLakefront_Restaurant_EventScript_SNC7_Ans

ValorLakefront_Restaurant_Text_SNRGabriellaAsk2::
	.string "I’m convinced that he has some\n"
	.string "extrasensory power or something.\p"
	.string "I’m teaming up with a guy like that. Are\n"
	.string "you sure you want to do this?$"

ValorLakefront_Restaurant_Text_SNRGabriellaIntro2::
	.string "How can you guess right about\n"
	.string "everything all the time?\p"
	.string "Do you really have the power of\n"
	.string "premonition?$"

ValorLakefront_Restaurant_EventScript_SNC7_V1::
	msgbox ValorLakefront_Restaurant_Text_SNRKendrickIntro1, MSGBOX_DEFAULT
	faceplayer
	msgbox ValorLakefront_Restaurant_Text_SNRKendrickAsk1, MSGBOX_YESNO
	goto ValorLakefront_Restaurant_EventScript_SNC7_Ans

ValorLakefront_Restaurant_Text_SNRKendrickAsk1::
	.string "When I say “heart,” I don’t mean what\n"
	.string "that person’s thinking.\p"
	.string "It’s about how they want to be\n"
	.string "perceived.\p"
	.string "Do you... Would you like me to think of\n"
	.string "you as a tough TRAINER?$"

ValorLakefront_Restaurant_Text_SNRKendrickIntro1::
	.string "There’s no need for technique.\p"
	.string "You just have to read what’s in your\n"
	.string "opponent’s heart.$"

ValorLakefront_Restaurant_EventScript_SNC7_Need::
	msgbox ValorLakefront_Restaurant_Text_SNRKendrickNeed, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_Text_SNRKendrickNeed::
	.string "I’ll only say this once, so listen\n"
	.string "closely. I’ll even say it slowly.\p"
	.string "To battle against two TRAINERS, you\n"
	.string "need two or more POKéMON.\p"
	.string "Now if you were to bring more POKéMON,\n"
	.string "I could consider a battle...$"

ValorLakefront_Restaurant_EventScript_SNC6::
	goto_if_defeated TRAINER_BRANDI_SINNOH, ValorLakefront_Restaurant_EventScript_SNC6_Done
	specialvar VAR_RESULT, CountPartyAliveNonEggMons
	goto_if_lt VAR_RESULT, 2, ValorLakefront_Restaurant_EventScript_SNC6_Need
	special SinnohRestaurantVariant
	switch VAR_RESULT
	case 1, ValorLakefront_Restaurant_EventScript_SNC6_V1
	case 2, ValorLakefront_Restaurant_EventScript_SNC6_V2
	msgbox ValorLakefront_Restaurant_Text_SNRDarrylIntro0, MSGBOX_DEFAULT
	faceplayer
	msgbox ValorLakefront_Restaurant_Text_SNRDarrylAsk0, MSGBOX_YESNO
	goto ValorLakefront_Restaurant_EventScript_SNC6_Ans

ValorLakefront_Restaurant_EventScript_SNC6_Done::
	msgbox ValorLakefront_Restaurant_Text_SNRDarrylDef0, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_EventScript_SNC6_Ans::
	goto_if_eq VAR_RESULT, NO, ValorLakefront_Restaurant_EventScript_SNC_End
	closemessage
	trainerbattle_two_trainers TRAINER_BRANDI_SINNOH, ValorLakefront_Restaurant_Text_SNRDarrylLose, TRAINER_MELINA_SINNOH, ValorLakefront_Restaurant_Text_SNRValerieLose
	special SinnohRestaurantVariant
	switch VAR_RESULT
	case 1, ValorLakefront_Restaurant_EventScript_SNC6_D1
	case 2, ValorLakefront_Restaurant_EventScript_SNC6_D2
	goto ValorLakefront_Restaurant_EventScript_SNC6_Done

ValorLakefront_Restaurant_EventScript_SNC6_D2::
	msgbox ValorLakefront_Restaurant_Text_SNRValerieDef2, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_Text_SNRValerieDef2::
	.string "Do you know what the most important\n"
	.string "thing is for gourmet reporting?\p"
	.string "It’s a...thesaurus-like vocabulary!$"

ValorLakefront_Restaurant_EventScript_SNC6_D1::
	msgbox ValorLakefront_Restaurant_Text_SNRDarrylDef1, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_Text_SNRDarrylDef1::
	.string "Photographing food isn’t easy. It’s\n"
	.string "actually very technical.$"

ValorLakefront_Restaurant_Text_SNRValerieLose::
	.string "Oh!$"

ValorLakefront_Restaurant_Text_SNRDarrylLose::
	.string "Oh!$"

ValorLakefront_Restaurant_Text_SNRDarrylDef0::
	.string "Oh, man... Our drinks are lukewarm now.$"

ValorLakefront_Restaurant_Text_SNRDarrylAsk0::
	.string "Hunh? You’re inviting us to battle at a\n"
	.string "time like this?$"

ValorLakefront_Restaurant_Text_SNRDarrylIntro0::
	.string "Let’s start with a shot of the drinks\n"
	.string "as a camera test.$"

ValorLakefront_Restaurant_EventScript_SNC6_V2::
	msgbox ValorLakefront_Restaurant_Text_SNRValerieIntro2, MSGBOX_DEFAULT
	faceplayer
	msgbox ValorLakefront_Restaurant_Text_SNRValerieAsk2, MSGBOX_YESNO
	goto ValorLakefront_Restaurant_EventScript_SNC6_Ans

ValorLakefront_Restaurant_Text_SNRValerieAsk2::
	.string "It’s not easy trying to describe food\n"
	.string "while you’re eating.\p"
	.string "But I can battle anytime during\n"
	.string "filming!$"

ValorLakefront_Restaurant_Text_SNRValerieIntro2::
	.string "Chomp!\p"
	.string "Mmm... This is... Light, and yet rich\n"
	.string "flavored...\p"
	.string "It delectably melts away...\p"
	.string "A hint of an aftertaste, yet crisp...\p"
	.string "Neither too sweet nor too bitter...\p"
	.string "My words can’t do this justice!$"

ValorLakefront_Restaurant_EventScript_SNC6_V1::
	msgbox ValorLakefront_Restaurant_Text_SNRDarrylIntro1, MSGBOX_DEFAULT
	faceplayer
	msgbox ValorLakefront_Restaurant_Text_SNRDarrylAsk1, MSGBOX_YESNO
	goto ValorLakefront_Restaurant_EventScript_SNC6_Ans

ValorLakefront_Restaurant_Text_SNRDarrylAsk1::
	.string "Thanks, that was quick!\p"
	.string "...Wait, where’s the mist spray? Oh, you\n"
	.string "want a battle?\p"
	.string "Whatever, then. I’m up for your\n"
	.string "challenge!$"

ValorLakefront_Restaurant_Text_SNRDarrylIntro1::
	.string "Hey, these appetizers sure do look\n"
	.string "delicious.\p"
	.string "Will someone bring me a mist spray so\n"
	.string "they look even fresher?$"

ValorLakefront_Restaurant_EventScript_SNC6_Need::
	msgbox ValorLakefront_Restaurant_Text_SNRDarrylNeed, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_Text_SNRDarrylNeed::
	.string "Yeah? What’s up? Did you want to be on\n"
	.string "TV, too?\p"
	.string "Oh, right, sorry! You wanted to battle!\p"
	.string "You’ll be battling the two of us. You\n"
	.string "need at least two POKéMON.$"

ValorLakefront_Restaurant_EventScript_SNC5::
	goto_if_defeated TRAINER_MAKAYLA_SINNOH, ValorLakefront_Restaurant_EventScript_SNC5_Done
	specialvar VAR_RESULT, CountPartyAliveNonEggMons
	goto_if_lt VAR_RESULT, 2, ValorLakefront_Restaurant_EventScript_SNC5_Need
	special SinnohRestaurantVariant
	switch VAR_RESULT
	case 1, ValorLakefront_Restaurant_EventScript_SNC5_V1
	case 2, ValorLakefront_Restaurant_EventScript_SNC5_V2
	msgbox ValorLakefront_Restaurant_Text_SNREmanuelIntro0, MSGBOX_DEFAULT
	faceplayer
	msgbox ValorLakefront_Restaurant_Text_SNREmanuelAsk0, MSGBOX_YESNO
	goto ValorLakefront_Restaurant_EventScript_SNC5_Ans

ValorLakefront_Restaurant_EventScript_SNC5_Done::
	msgbox ValorLakefront_Restaurant_Text_SNREmanuelDef0, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_EventScript_SNC5_Ans::
	goto_if_eq VAR_RESULT, NO, ValorLakefront_Restaurant_EventScript_SNC_End
	closemessage
	trainerbattle_two_trainers TRAINER_MAKAYLA_SINNOH, ValorLakefront_Restaurant_Text_SNREmanuelLose, TRAINER_AISHA_SINNOH, ValorLakefront_Restaurant_Text_SNRBlytheLose
	special SinnohRestaurantVariant
	switch VAR_RESULT
	case 1, ValorLakefront_Restaurant_EventScript_SNC5_D1
	case 2, ValorLakefront_Restaurant_EventScript_SNC5_D2
	goto ValorLakefront_Restaurant_EventScript_SNC5_Done

ValorLakefront_Restaurant_EventScript_SNC5_D2::
	msgbox ValorLakefront_Restaurant_Text_SNRBlytheDef2, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_Text_SNRBlytheDef2::
	.string "Next time, let’s come with everyone.\n"
	.string "The baby, too!$"

ValorLakefront_Restaurant_EventScript_SNC5_D1::
	msgbox ValorLakefront_Restaurant_Text_SNREmanuelDef1, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_Text_SNREmanuelDef1::
	.string "Let’s get over the sting of this loss\n"
	.string "by enjoying this delicious meal!$"

ValorLakefront_Restaurant_Text_SNRBlytheLose::
	.string "Oh!$"

ValorLakefront_Restaurant_Text_SNREmanuelLose::
	.string "Oh!$"

ValorLakefront_Restaurant_Text_SNREmanuelDef0::
	.string "The house will be a lot noisier when the\n"
	.string "baby comes home with Mommy.$"

ValorLakefront_Restaurant_Text_SNREmanuelAsk0::
	.string "My wife’s in the hospital waiting for\n"
	.string "the baby to arrive.\p"
	.string "Since I can’t cook, I came here with my\n"
	.string "daughter.\p"
	.string "How would you like a battle with us\n"
	.string "before we eat?$"

ValorLakefront_Restaurant_Text_SNREmanuelIntro0::
	.string "Here’s a toast for MOM. May she always\n"
	.string "be healthy!$"

ValorLakefront_Restaurant_EventScript_SNC5_V2::
	msgbox ValorLakefront_Restaurant_Text_SNRBlytheIntro2, MSGBOX_DEFAULT
	faceplayer
	msgbox ValorLakefront_Restaurant_Text_SNRBlytheAsk2, MSGBOX_YESNO
	goto ValorLakefront_Restaurant_EventScript_SNC5_Ans

ValorLakefront_Restaurant_Text_SNRBlytheAsk2::
	.string "Mommy gave me my POKéMON. Want to see\n"
	.string "how tough they are?$"

ValorLakefront_Restaurant_Text_SNRBlytheIntro2::
	.string "I wish Mommy were here to eat with us...$"

ValorLakefront_Restaurant_EventScript_SNC5_V1::
	msgbox ValorLakefront_Restaurant_Text_SNREmanuelIntro1, MSGBOX_DEFAULT
	faceplayer
	msgbox ValorLakefront_Restaurant_Text_SNREmanuelAsk1, MSGBOX_YESNO
	goto ValorLakefront_Restaurant_EventScript_SNC5_Ans

ValorLakefront_Restaurant_Text_SNREmanuelAsk1::
	.string "I’m no cook, I’ll admit that freely.\p"
	.string "But battling POKéMON... There’s\n"
	.string "something I’m comfortable with.$"

ValorLakefront_Restaurant_Text_SNREmanuelIntro1::
	.string "Wow... Look at these appetizers. This is\n"
	.string "just so extravagant.$"

ValorLakefront_Restaurant_EventScript_SNC5_Need::
	msgbox ValorLakefront_Restaurant_Text_SNREmanuelNeed, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_Text_SNREmanuelNeed::
	.string "My daughter and I always battle\n"
	.string "together, none of that one-on-one.$"

ValorLakefront_Restaurant_EventScript_SNC4::
	goto_if_defeated TRAINER_MAY_RUSTBORO_TORCHIC_SINNOH, ValorLakefront_Restaurant_EventScript_SNC4_Done
	specialvar VAR_RESULT, CountPartyAliveNonEggMons
	goto_if_lt VAR_RESULT, 2, ValorLakefront_Restaurant_EventScript_SNC4_Need
	special SinnohRestaurantVariant
	switch VAR_RESULT
	case 1, ValorLakefront_Restaurant_EventScript_SNC4_V1
	case 2, ValorLakefront_Restaurant_EventScript_SNC4_V2
	msgbox ValorLakefront_Restaurant_Text_SNREstebanIntro0, MSGBOX_DEFAULT
	faceplayer
	msgbox ValorLakefront_Restaurant_Text_SNREstebanAsk0, MSGBOX_YESNO
	goto ValorLakefront_Restaurant_EventScript_SNC4_Ans

ValorLakefront_Restaurant_EventScript_SNC4_Done::
	msgbox ValorLakefront_Restaurant_Text_SNREstebanDef0, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_EventScript_SNC4_Ans::
	goto_if_eq VAR_RESULT, NO, ValorLakefront_Restaurant_EventScript_SNC_End
	closemessage
	trainerbattle_two_trainers TRAINER_MAY_RUSTBORO_TORCHIC_SINNOH, ValorLakefront_Restaurant_Text_SNREstebanLose, TRAINER_FABIAN_SINNOH, ValorLakefront_Restaurant_Text_SNRMeredithLose
	special SinnohRestaurantVariant
	switch VAR_RESULT
	case 1, ValorLakefront_Restaurant_EventScript_SNC4_D1
	case 2, ValorLakefront_Restaurant_EventScript_SNC4_D2
	goto ValorLakefront_Restaurant_EventScript_SNC4_Done

ValorLakefront_Restaurant_EventScript_SNC4_D2::
	msgbox ValorLakefront_Restaurant_Text_SNRMeredithDef2, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_Text_SNRMeredithDef2::
	.string "Is the dessert coming soon?$"

ValorLakefront_Restaurant_EventScript_SNC4_D1::
	msgbox ValorLakefront_Restaurant_Text_SNREstebanDef1, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_Text_SNREstebanDef1::
	.string "We’re going to eat this delicious stuff\n"
	.string "now. Bye-bye!$"

ValorLakefront_Restaurant_Text_SNRMeredithLose::
	.string "Oh!$"

ValorLakefront_Restaurant_Text_SNREstebanLose::
	.string "Oh!$"

ValorLakefront_Restaurant_Text_SNREstebanDef0::
	.string "I don’t get it. Grown-ups always have a\n"
	.string "toast before eating.\p"
	.string "What’s that for? And I don’t see any\n"
	.string "bread?$"

ValorLakefront_Restaurant_Text_SNREstebanAsk0::
	.string "Oh, hi, TRAINER!\p"
	.string "Want to battle POKéMON with us before\n"
	.string "we have a yummy meal?$"

ValorLakefront_Restaurant_Text_SNREstebanIntro0::
	.string "What should I have today? Juice, ice\n"
	.string "cream, cake, and, and...$"

ValorLakefront_Restaurant_EventScript_SNC4_V2::
	msgbox ValorLakefront_Restaurant_Text_SNRMeredithIntro2, MSGBOX_DEFAULT
	faceplayer
	msgbox ValorLakefront_Restaurant_Text_SNRMeredithAsk2, MSGBOX_YESNO
	goto ValorLakefront_Restaurant_EventScript_SNC4_Ans

ValorLakefront_Restaurant_Text_SNRMeredithAsk2::
	.string "Oh? A battle, you say? Well, certainly.\n"
	.string "Why not?$"

ValorLakefront_Restaurant_Text_SNRMeredithIntro2::
	.string "This is a special occasion, Esteban.\p"
	.string "This is to celebrate your great grades!$"

ValorLakefront_Restaurant_EventScript_SNC4_V1::
	msgbox ValorLakefront_Restaurant_Text_SNREstebanIntro1, MSGBOX_DEFAULT
	faceplayer
	msgbox ValorLakefront_Restaurant_Text_SNREstebanAsk1, MSGBOX_YESNO
	goto ValorLakefront_Restaurant_EventScript_SNC4_Ans

ValorLakefront_Restaurant_Text_SNREstebanAsk1::
	.string "I do my homework while eating. I can\n"
	.string "battle anytime!$"

ValorLakefront_Restaurant_Text_SNREstebanIntro1::
	.string "Wow, they bring out things one dish at\n"
	.string "a time!\p"
	.string "It’s not like how it is at home!$"

ValorLakefront_Restaurant_EventScript_SNC4_Need::
	msgbox ValorLakefront_Restaurant_Text_SNREstebanNeed, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_Text_SNREstebanNeed::
	.string "If you have two POKéMON, I’ll take you\n"
	.string "on with my mom.$"

ValorLakefront_Restaurant_EventScript_SNC3::
	goto_if_defeated TRAINER_PAT_SINNOH, ValorLakefront_Restaurant_EventScript_SNC3_Done
	specialvar VAR_RESULT, CountPartyAliveNonEggMons
	goto_if_lt VAR_RESULT, 2, ValorLakefront_Restaurant_EventScript_SNC3_Need
	special SinnohRestaurantVariant
	switch VAR_RESULT
	case 1, ValorLakefront_Restaurant_EventScript_SNC3_V1
	case 2, ValorLakefront_Restaurant_EventScript_SNC3_V2
	msgbox ValorLakefront_Restaurant_Text_SNREugeneIntro0, MSGBOX_DEFAULT
	faceplayer
	msgbox ValorLakefront_Restaurant_Text_SNREugeneAsk0, MSGBOX_YESNO
	goto ValorLakefront_Restaurant_EventScript_SNC3_Ans

ValorLakefront_Restaurant_EventScript_SNC3_Done::
	msgbox ValorLakefront_Restaurant_Text_SNREugeneDef0, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_EventScript_SNC3_Ans::
	goto_if_eq VAR_RESULT, NO, ValorLakefront_Restaurant_EventScript_SNC_End
	closemessage
	trainerbattle_two_trainers TRAINER_PAT_SINNOH, ValorLakefront_Restaurant_Text_SNREugeneLose, TRAINER_MAY_RUSTBORO_TREECKO_SINNOH, ValorLakefront_Restaurant_Text_SNRAlisonLose
	special SinnohRestaurantVariant
	switch VAR_RESULT
	case 1, ValorLakefront_Restaurant_EventScript_SNC3_D1
	case 2, ValorLakefront_Restaurant_EventScript_SNC3_D2
	goto ValorLakefront_Restaurant_EventScript_SNC3_Done

ValorLakefront_Restaurant_EventScript_SNC3_D2::
	msgbox ValorLakefront_Restaurant_Text_SNRAlisonDef2, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_Text_SNRAlisonDef2::
	.string "The meal was delicious, and our battle\n"
	.string "was so much fun.\p"
	.string "I really insist that we split the bill.$"

ValorLakefront_Restaurant_EventScript_SNC3_D1::
	msgbox ValorLakefront_Restaurant_Text_SNREugeneDef1, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_Text_SNREugeneDef1::
	.string "ALISON, seeing your smiling face...\p"
	.string "I can’t tell if these appetizers are\n"
	.string "delicious or not!$"

ValorLakefront_Restaurant_Text_SNRAlisonLose::
	.string "Oh!$"

ValorLakefront_Restaurant_Text_SNREugeneLose::
	.string "Oh!$"

ValorLakefront_Restaurant_Text_SNREugeneDef0::
	.string "Oh, no, I’m sorry we lost. ALISON, you’re\n"
	.string "not upset?$"

ValorLakefront_Restaurant_Text_SNREugeneAsk0::
	.string "She’s the girl from the POKéMON-goods\n"
	.string "shop I go to all the time.\p"
	.string "We’re incredibly happy together. Would\n"
	.string "you like to battle us?$"

ValorLakefront_Restaurant_Text_SNREugeneIntro0::
	.string "ALISON, um, I, er... Thank you for coming\n"
	.string "today...\p"
	.string "Should we make a toast?$"

ValorLakefront_Restaurant_EventScript_SNC3_V2::
	msgbox ValorLakefront_Restaurant_Text_SNRAlisonIntro2, MSGBOX_DEFAULT
	faceplayer
	msgbox ValorLakefront_Restaurant_Text_SNRAlisonAsk2, MSGBOX_YESNO
	goto ValorLakefront_Restaurant_EventScript_SNC3_Ans

ValorLakefront_Restaurant_Text_SNRAlisonAsk2::
	.string "If I team up with my date, it could be\n"
	.string "an interesting combination.\p"
	.string "I think we could battle in an intriguing\n"
	.string "manner. Do you?$"

ValorLakefront_Restaurant_Text_SNRAlisonIntro2::
	.string "Eugene, I think you’re a little awkward,\n"
	.string "but you’re very earnest.$"

ValorLakefront_Restaurant_EventScript_SNC3_V1::
	msgbox ValorLakefront_Restaurant_Text_SNREugeneIntro1, MSGBOX_DEFAULT
	faceplayer
	msgbox ValorLakefront_Restaurant_Text_SNREugeneAsk1, MSGBOX_YESNO
	goto ValorLakefront_Restaurant_EventScript_SNC3_Ans

ValorLakefront_Restaurant_Text_SNREugeneAsk1::
	.string "Are you ALISON’s fan, too?$"

ValorLakefront_Restaurant_Text_SNREugeneIntro1::
	.string "If my POKéMON buddies hear I went on a\n"
	.string "date with you, ALISON...\p"
	.string "They’re probably going to hate me for\n"
	.string "it...$"

ValorLakefront_Restaurant_EventScript_SNC3_Need::
	msgbox ValorLakefront_Restaurant_Text_SNREugeneNeed, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_Text_SNREugeneNeed::
	.string "If you want to battle us, you have to\n"
	.string "have two POKéMON.$"

ValorLakefront_Restaurant_EventScript_SNC2::
	goto_if_defeated TRAINER_CALE_SINNOH, ValorLakefront_Restaurant_EventScript_SNC2_Done
	specialvar VAR_RESULT, CountPartyAliveNonEggMons
	goto_if_lt VAR_RESULT, 2, ValorLakefront_Restaurant_EventScript_SNC2_Need
	special SinnohRestaurantVariant
	switch VAR_RESULT
	case 1, ValorLakefront_Restaurant_EventScript_SNC2_V1
	case 2, ValorLakefront_Restaurant_EventScript_SNC2_V2
	msgbox ValorLakefront_Restaurant_Text_SNRLeonardoIntro0, MSGBOX_DEFAULT
	faceplayer
	msgbox ValorLakefront_Restaurant_Text_SNRLeonardoAsk0, MSGBOX_YESNO
	goto ValorLakefront_Restaurant_EventScript_SNC2_Ans

ValorLakefront_Restaurant_EventScript_SNC2_Done::
	msgbox ValorLakefront_Restaurant_Text_SNRLeonardoDef0, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_EventScript_SNC2_Ans::
	goto_if_eq VAR_RESULT, NO, ValorLakefront_Restaurant_EventScript_SNC_End
	closemessage
	trainerbattle_two_trainers TRAINER_CALE_SINNOH, ValorLakefront_Restaurant_Text_SNRLeonardoLose, TRAINER_MYLES_SINNOH, ValorLakefront_Restaurant_Text_SNRRebeccaLose
	special SinnohRestaurantVariant
	switch VAR_RESULT
	case 1, ValorLakefront_Restaurant_EventScript_SNC2_D1
	case 2, ValorLakefront_Restaurant_EventScript_SNC2_D2
	goto ValorLakefront_Restaurant_EventScript_SNC2_Done

ValorLakefront_Restaurant_EventScript_SNC2_D2::
	msgbox ValorLakefront_Restaurant_Text_SNRRebeccaDef2, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_Text_SNRRebeccaDef2::
	.string "Battling is fine, of course.\p"
	.string "But for me, I would rather be out\n"
	.string "enjoying good meals.$"

ValorLakefront_Restaurant_EventScript_SNC2_D1::
	msgbox ValorLakefront_Restaurant_Text_SNRLeonardoDef1, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_Text_SNRLeonardoDef1::
	.string "Well, so much for that.\p"
	.string "We’ll keep a stiff upper lip and look\n"
	.string "forward to enjoying the main course.$"

ValorLakefront_Restaurant_Text_SNRRebeccaLose::
	.string "Oh!$"

ValorLakefront_Restaurant_Text_SNRLeonardoLose::
	.string "Oh!$"

ValorLakefront_Restaurant_Text_SNRLeonardoDef0::
	.string "Well, so much for that. Let’s try to\n"
	.string "enjoy the rest of our meal.$"

ValorLakefront_Restaurant_Text_SNRLeonardoAsk0::
	.string "Since I took my retirement, I’ve been\n"
	.string "traveling with my wife.\p"
	.string "We both enjoy searching for delicious\n"
	.string "dining experiences.\p"
	.string "You seem to enjoy battling with\n"
	.string "POKéMON. Am I right?$"

ValorLakefront_Restaurant_Text_SNRLeonardoIntro0::
	.string "Let me propose a toast to many more\n"
	.string "happy years together.$"

ValorLakefront_Restaurant_EventScript_SNC2_V2::
	msgbox ValorLakefront_Restaurant_Text_SNRRebeccaIntro2, MSGBOX_DEFAULT
	faceplayer
	msgbox ValorLakefront_Restaurant_Text_SNRRebeccaAsk2, MSGBOX_YESNO
	goto ValorLakefront_Restaurant_EventScript_SNC2_Ans

ValorLakefront_Restaurant_Text_SNRRebeccaAsk2::
	.string "Would you like to sample a bite?\p"
	.string "... Oh, right. POKéMON?$"

ValorLakefront_Restaurant_Text_SNRRebeccaIntro2::
	.string "...! This sauce!\p"
	.string "It’s a spicy sauce in HOENN style made\n"
	.string "from grated Cheri Berries!$"

ValorLakefront_Restaurant_EventScript_SNC2_V1::
	msgbox ValorLakefront_Restaurant_Text_SNRLeonardoIntro1, MSGBOX_DEFAULT
	faceplayer
	msgbox ValorLakefront_Restaurant_Text_SNRLeonardoAsk1, MSGBOX_YESNO
	goto ValorLakefront_Restaurant_EventScript_SNC2_Ans

ValorLakefront_Restaurant_Text_SNRLeonardoAsk1::
	.string "When you get to be an accomplished\n"
	.string "gourmet like myself, one can tell at\p"
	.string "a glance if a dish is delicious or not.\p"
	.string "You would battle against such a\n"
	.string "discerning gourmet?$"

ValorLakefront_Restaurant_Text_SNRLeonardoIntro1::
	.string "Hmm! Now, this is special!\p"
	.string "It appears as if it were only grazed\n"
	.string "with fire, but in reality, much\p"
	.string "care has gone into its preparation!$"

ValorLakefront_Restaurant_EventScript_SNC2_Need::
	msgbox ValorLakefront_Restaurant_Text_SNRLeonardoNeed, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_Text_SNRLeonardoNeed::
	.string "If your intention is to test your skill\n"
	.string "on us, I daresay you ought to\p"
	.string "bring at least another POKéMON.$"

ValorLakefront_Restaurant_EventScript_SNC1::
	goto_if_defeated TRAINER_LEONEL_SINNOH, ValorLakefront_Restaurant_EventScript_SNC1_Done
	specialvar VAR_RESULT, CountPartyAliveNonEggMons
	goto_if_lt VAR_RESULT, 2, ValorLakefront_Restaurant_EventScript_SNC1_Need
	special SinnohRestaurantVariant
	switch VAR_RESULT
	case 1, ValorLakefront_Restaurant_EventScript_SNC1_V1
	case 2, ValorLakefront_Restaurant_EventScript_SNC1_V2
	msgbox ValorLakefront_Restaurant_Text_SNRRomanIntro0, MSGBOX_DEFAULT
	faceplayer
	msgbox ValorLakefront_Restaurant_Text_SNRRomanAsk0, MSGBOX_YESNO
	goto ValorLakefront_Restaurant_EventScript_SNC1_Ans

ValorLakefront_Restaurant_EventScript_SNC1_Done::
	msgbox ValorLakefront_Restaurant_Text_SNRRomanDef0, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_EventScript_SNC1_Ans::
	goto_if_eq VAR_RESULT, NO, ValorLakefront_Restaurant_EventScript_SNC_End
	closemessage
	trainerbattle_two_trainers TRAINER_LEONEL_SINNOH, ValorLakefront_Restaurant_Text_SNRRomanLose, TRAINER_CALLIE_SINNOH, ValorLakefront_Restaurant_Text_SNRKylieLose
	special SinnohRestaurantVariant
	switch VAR_RESULT
	case 1, ValorLakefront_Restaurant_EventScript_SNC1_D1
	case 2, ValorLakefront_Restaurant_EventScript_SNC1_D2
	goto ValorLakefront_Restaurant_EventScript_SNC1_Done

ValorLakefront_Restaurant_EventScript_SNC1_D2::
	msgbox ValorLakefront_Restaurant_Text_SNRKylieDef2, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_Text_SNRKylieDef2::
	.string "Your father’s cooking has a very\n"
	.string "magical quality to it.\p"
	.string "It seems to perk people up with energy.$"

ValorLakefront_Restaurant_EventScript_SNC1_D1::
	msgbox ValorLakefront_Restaurant_Text_SNRRomanDef1, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_Text_SNRRomanDef1::
	.string "Finally. Now we can go about enjoying\n"
	.string "our meal without disruption.$"

ValorLakefront_Restaurant_Text_SNRKylieLose::
	.string "Oh!$"

ValorLakefront_Restaurant_Text_SNRRomanLose::
	.string "Oh!$"

ValorLakefront_Restaurant_Text_SNRRomanDef0::
	.string "We’ve lost, but let’s make a toast to\n"
	.string "our future together anyway!$"

ValorLakefront_Restaurant_Text_SNRRomanAsk0::
	.string "What is it? A battle? Bahaha... You\n"
	.string "think you can beat me?$"

ValorLakefront_Restaurant_Text_SNRRomanIntro0::
	.string "Actually, my father happens to be the\n"
	.string "chef here.$"

ValorLakefront_Restaurant_EventScript_SNC1_V2::
	msgbox ValorLakefront_Restaurant_Text_SNRKylieIntro2, MSGBOX_DEFAULT
	faceplayer
	msgbox ValorLakefront_Restaurant_Text_SNRKylieAsk2, MSGBOX_YESNO
	goto ValorLakefront_Restaurant_EventScript_SNC1_Ans

ValorLakefront_Restaurant_Text_SNRKylieAsk2::
	.string "Eating this fabulous meal has really\n"
	.string "lifted my spirits.\p"
	.string "Join us for a battle?$"

ValorLakefront_Restaurant_Text_SNRKylieIntro2::
	.string "This succulent flavor! It reminds me of\n"
	.string "a world trip I took.\p"
	.string "My father and I traveled everywhere\n"
	.string "dining at only the best restaurants.$"

ValorLakefront_Restaurant_EventScript_SNC1_V1::
	msgbox ValorLakefront_Restaurant_Text_SNRRomanIntro1, MSGBOX_DEFAULT
	faceplayer
	msgbox ValorLakefront_Restaurant_Text_SNRRomanAsk1, MSGBOX_YESNO
	goto ValorLakefront_Restaurant_EventScript_SNC1_Ans

ValorLakefront_Restaurant_Text_SNRRomanAsk1::
	.string "...Are you maybe asking me for a battle?\p"
	.string "Well, certainly! I never back down from\n"
	.string "a challenge!$"

ValorLakefront_Restaurant_Text_SNRRomanIntro1::
	.string "I have to hand it to my father-- these\n"
	.string "hors d’oeuvres are delicious!$"

ValorLakefront_Restaurant_EventScript_SNC1_Need::
	msgbox ValorLakefront_Restaurant_Text_SNRRomanNeed, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_Text_SNRRomanNeed::
	.string "If you want to challenge us, bring some\n"
	.string "more POKéMON.$"

ValorLakefront_Restaurant_EventScript_SNC0::
	goto_if_defeated TRAINER_DAYTON_SINNOH, ValorLakefront_Restaurant_EventScript_SNC0_Done
	specialvar VAR_RESULT, CountPartyAliveNonEggMons
	goto_if_lt VAR_RESULT, 2, ValorLakefront_Restaurant_EventScript_SNC0_Need
	special SinnohRestaurantVariant
	switch VAR_RESULT
	case 1, ValorLakefront_Restaurant_EventScript_SNC0_V1
	case 2, ValorLakefront_Restaurant_EventScript_SNC0_V2
	msgbox ValorLakefront_Restaurant_Text_SNRIsmaelIntro0, MSGBOX_DEFAULT
	faceplayer
	msgbox ValorLakefront_Restaurant_Text_SNRIsmaelAsk0, MSGBOX_YESNO
	goto ValorLakefront_Restaurant_EventScript_SNC0_Ans

ValorLakefront_Restaurant_EventScript_SNC0_Done::
	msgbox ValorLakefront_Restaurant_Text_SNRIsmaelDef0, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_EventScript_SNC0_Ans::
	goto_if_eq VAR_RESULT, NO, ValorLakefront_Restaurant_EventScript_SNC_End
	closemessage
	trainerbattle_two_trainers TRAINER_DAYTON_SINNOH, ValorLakefront_Restaurant_Text_SNRIsmaelLose, TRAINER_RACHEL_SINNOH, ValorLakefront_Restaurant_Text_SNRHarleyLose
	special SinnohRestaurantVariant
	switch VAR_RESULT
	case 1, ValorLakefront_Restaurant_EventScript_SNC0_D1
	case 2, ValorLakefront_Restaurant_EventScript_SNC0_D2
	goto ValorLakefront_Restaurant_EventScript_SNC0_Done

ValorLakefront_Restaurant_EventScript_SNC0_D2::
	msgbox ValorLakefront_Restaurant_Text_SNRHarleyDef2, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_Text_SNRHarleyDef2::
	.string "The models of great paintings were\n"
	.string "often rather plump.\p"
	.string "That means I can keep eating without\n"
	.string "obsessing over my figure!$"

ValorLakefront_Restaurant_EventScript_SNC0_D1::
	msgbox ValorLakefront_Restaurant_Text_SNRIsmaelDef1, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_Text_SNRIsmaelDef1::
	.string "My hors d’oeuvres have gone cold...$"

ValorLakefront_Restaurant_Text_SNRHarleyLose::
	.string "Oh!$"

ValorLakefront_Restaurant_Text_SNRIsmaelLose::
	.string "Oh!$"

ValorLakefront_Restaurant_Text_SNRIsmaelDef0::
	.string "Though we lost our battle... A toast to\n"
	.string "your beauty, that no\p"
	.string "painting could ever hope to capture!$"

ValorLakefront_Restaurant_Text_SNRIsmaelAsk0::
	.string "What is it? Do you wish for a battle?$"

ValorLakefront_Restaurant_Text_SNRIsmaelIntro0::
	.string "With someone as beautiful as you for\n"
	.string "my model, I am sure to paint\p"
	.string "a masterpiece!$"

ValorLakefront_Restaurant_EventScript_SNC0_V2::
	msgbox ValorLakefront_Restaurant_Text_SNRHarleyIntro2, MSGBOX_DEFAULT
	faceplayer
	msgbox ValorLakefront_Restaurant_Text_SNRHarleyAsk2, MSGBOX_YESNO
	goto ValorLakefront_Restaurant_EventScript_SNC0_Ans

ValorLakefront_Restaurant_Text_SNRHarleyAsk2::
	.string "I feel guilty just eating all this\n"
	.string "delicious food like this.\p"
	.string "I’ll join in the battle, too!$"

ValorLakefront_Restaurant_Text_SNRHarleyIntro2::
	.string "Today’s main dish is scrumptiously\n"
	.string "delicious!\p"
	.string "If I can keep eating this food, I’ll\n"
	.string "model anytime I can!$"

ValorLakefront_Restaurant_EventScript_SNC0_V1::
	msgbox ValorLakefront_Restaurant_Text_SNRIsmaelIntro1, MSGBOX_DEFAULT
	faceplayer
	msgbox ValorLakefront_Restaurant_Text_SNRIsmaelAsk1, MSGBOX_YESNO
	goto ValorLakefront_Restaurant_EventScript_SNC0_Ans

ValorLakefront_Restaurant_Text_SNRIsmaelAsk1::
	.string "What is it? Are you feeling hungry,\n"
	.string "too?\p"
	.string "Oh, I see, that’s not it! You wanted a\n"
	.string "battle!$"

ValorLakefront_Restaurant_Text_SNRIsmaelIntro1::
	.string "There is no price too high for the sake\n"
	.string "of my art...\p"
	.string "That said, my oh my, these meals look\n"
	.string "awfully pricey...$"

ValorLakefront_Restaurant_EventScript_SNC0_Need::
	msgbox ValorLakefront_Restaurant_Text_SNRIsmaelNeed, MSGBOX_DEFAULT
	releaseall
	end

ValorLakefront_Restaurant_Text_SNRIsmaelNeed::
	.string "Before we make our toast, I’d hoped for\n"
	.string "a battle...\p"
	.string "However, you seem to be short a\n"
	.string "POKéMON for that.$"

ValorLakefront_Restaurant_EventScript_SNT1::
	setvar VAR_0x8004, 1
	goto ValorLakefront_Restaurant_EventScript_SNTable

ValorLakefront_Restaurant_EventScript_SNT2::
	setvar VAR_0x8004, 2
	goto ValorLakefront_Restaurant_EventScript_SNTable

ValorLakefront_Restaurant_EventScript_SNT3::
	setvar VAR_0x8004, 3
	goto ValorLakefront_Restaurant_EventScript_SNTable

ValorLakefront_Restaurant_EventScript_SNT4::
	setvar VAR_0x8004, 4
	goto ValorLakefront_Restaurant_EventScript_SNTable

ValorLakefront_Restaurant_EventScript_SNPtWAITER::
	msgbox ValorLakefront_Restaurant_Text_SNRWaiter, MSGBOX_NPC
	end

@ Cada mesa: VAR_0x8004 = mesa; el special pone en VAR_RESULT la pareja de hoy (0-8)

ValorLakefront_Restaurant_Text_SNRWaiter::
	.string "At our restaurant, you can enjoy more\n"
	.string "than just exquisite dining.\p"
	.string "You may also partake in battles. Bon\n"
	.string "appetit!$"
