Route213_sinnoh_MapScripts::
	.byte 0


Route213_EventScript_Sheltin::
	trainerbattle_single TRAINER_PAUL_SINNOH, Route213_Text_SheltinIntro, Route213_Text_SheltinDefeat
	msgbox Route213_Text_SheltinPost, MSGBOX_AUTOCLOSE
	end

Route213_Text_SheltinPost::
	.string "When you're out at sea, Water-type\n"
	.string "POKéMON look more lively.$"

Route213_Text_SheltinDefeat::
	.string "I lost at sea! But I swim here the\n"
	.string "whole year round!$"

Route213_Text_SheltinIntro::
	.string "I swim the whole year round. I'm not\n"
	.string "losing a battle at sea!$"

Route213_EventScript_Evan::
	trainerbattle_single TRAINER_GEORGIA_SINNOH, Route213_Text_EvanIntro, Route213_Text_EvanDefeat
	msgbox Route213_Text_EvanPost, MSGBOX_AUTOCLOSE
	end

Route213_Text_EvanPost::
	.string "Look at my lips... They're the color of\n"
	.string "prunes!$"

Route213_Text_EvanDefeat::
	.string "The chill of the sea, and the coldness\n"
	.string "of defeat...\p"
	.string "It's a double whammy.$"

Route213_Text_EvanIntro::
	.string "Brr... I'm starting to get chilly. I\n"
	.string "could use a win to get warmed up.$"

Route213_EventScript_Mary::
	trainerbattle_single TRAINER_KATE_AND_JOY_SINNOH, Route213_Text_MaryIntro, Route213_Text_MaryDefeat
	msgbox Route213_Text_MaryPost, MSGBOX_AUTOCLOSE
	end

Route213_Text_MaryPost::
	.string "There aren't many sea routes that you\n"
	.string "can swim in SINNOH.\p"
	.string "It makes me want to take a vacation in\n"
	.string "the Hoenn region.$"

Route213_Text_MaryDefeat::
	.string "What's saltier? My tears or the sea...$"

Route213_Text_MaryIntro::
	.string "Hello, there! Aren't you going to swim?$"

Route213_EventScript_Haley::
	trainerbattle_single TRAINER_VICTOR_SINNOH, Route213_Text_HaleyIntro, Route213_Text_HaleyDefeat
	msgbox Route213_Text_HaleyPost, MSGBOX_AUTOCLOSE
	end

Route213_Text_HaleyPost::
	.string "Maybe I should switch to surfing,\n"
	.string "too...$"

Route213_Text_HaleyDefeat::
	.string "You sure schooled me there.$"

Route213_Text_HaleyIntro::
	.string "Hi, wave-riding Trainer! How about a\n"
	.string "battle on the sea?$"

Route213_EventScript_Jared::
	trainerbattle_single TRAINER_COLTON_SINNOH, Route213_Text_JaredIntro, Route213_Text_JaredDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route213_EventScript_Jared_Rematch
	msgbox Route213_Text_JaredPost, MSGBOX_AUTOCLOSE
	end

Route213_Text_JaredPost::
	.string "Mom blew up my inflatable tube for me.\n"
	.string "I ran out of breath just opening it!$"

Route213_EventScript_Jared_Rematch::
	trainerbattle_rematch TRAINER_COLTON_SINNOH, Route213_Text_JaredIntro, Route213_Text_JaredDefeat
	msgbox Route213_Text_JaredPost, MSGBOX_AUTOCLOSE
	end

Route213_Text_JaredDefeat::
	.string "It's not easy trying to move holding\n"
	.string "on to this inflatable tube.$"

Route213_Text_JaredIntro::
	.string "Isn't this nice? I love my inflatable\n"
	.string "tube!$"

Route213_EventScript_Chelsea::
	trainerbattle_single TRAINER_VICTORIA_SINNOH, Route213_Text_ChelseaIntro, Route213_Text_ChelseaDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route213_EventScript_Chelsea_Rematch
	msgbox Route213_Text_ChelseaPost, MSGBOX_AUTOCLOSE
	end

Route213_Text_ChelseaPost::
	.string "That cloud looks like giant ice cream!\n"
	.string "I bet it tastes yummy!$"

Route213_EventScript_Chelsea_Rematch::
	trainerbattle_rematch TRAINER_VICTORIA_SINNOH, Route213_Text_ChelseaIntro, Route213_Text_ChelseaDefeat
	msgbox Route213_Text_ChelseaPost, MSGBOX_AUTOCLOSE
	end

Route213_Text_ChelseaDefeat::
	.string "Losing made me all hungry now.$"

Route213_Text_ChelseaIntro::
	.string "Ehehe... I can battle, too!$"

Route213_EventScript_Cyndy::
	trainerbattle_single TRAINER_VANESSA_SINNOH, Route213_Text_CyndyIntro, Route213_Text_CyndyDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route213_EventScript_Cyndy_Rematch
	msgbox Route213_Text_CyndyPost, MSGBOX_AUTOCLOSE
	end

Route213_Text_CyndyPost::
	.string "You're so much more of a Trainer than\n"
	.string "you look!$"

Route213_EventScript_Cyndy_Rematch::
	trainerbattle_rematch TRAINER_VANESSA_SINNOH, Route213_Text_CyndyIntro, Route213_Text_CyndyDefeat
	msgbox Route213_Text_CyndyPost, MSGBOX_AUTOCLOSE
	end

Route213_Text_CyndyDefeat::
	.string "Oh, my gosh! You attack that\n"
	.string "savagely?$"

Route213_Text_CyndyIntro::
	.string "Let me demonstrate my technique. It's\n"
	.string "how this grown-up battles.$"

Route213_EventScript_Kenneth::
	trainerbattle_single TRAINER_VICKY_SINNOH, Route213_Text_KennethIntro, Route213_Text_KennethDefeat
	msgbox Route213_Text_KennethPost, MSGBOX_AUTOCLOSE
	end

Route213_Text_KennethPost::
	.string "Go on. Don't be shy about going up to\n"
	.string "people to hear what they have to\l"
	.string "say...\p"
	.string "Just don't you talk to me.$"

Route213_Text_KennethDefeat::
	.string "You need to have more respect for a\n"
	.string "grown-up...$"

Route213_Text_KennethIntro::
	.string "Waah! Now! Just now! I was just about\n"
	.string "to reel it in!$"

Route213_EventScript_Paul::
	trainerbattle_single TRAINER_QUINCY_SINNOH, Route213_Text_PaulIntro, Route213_Text_PaulDefeat
	msgbox Route213_Text_PaulPost, MSGBOX_AUTOCLOSE
	end

Route213_Text_PaulPost::
	.string "Maybe I'll go work out down at the\n"
	.string "restaurant again.\p"
	.string "That place gets different people in\n"
	.string "every day, and they all like battles.$"

Route213_Text_PaulDefeat::
	.string "You're good, pip-squeak!$"

Route213_Text_PaulIntro::
	.string "Traveling alone, are you? That's\n"
	.string "impressive! How about we battle?$"

Route213_EventScript_PtNpc1::
	msgbox Route213_Text_PtNpc1, MSGBOX_NPC
	end

Route213_Text_PtNpc1::
	.string "There's a fancy hotel in a fancy place\n"
	.string "with a fancy restaurant.\p"
	.string "The fancy restaurant's filled with\n"
	.string "fancy people who think of themselves\l"
	.string "as being too fancy to battle alone.$"

Route213_EventScript_PtNpc2::
	msgbox Route213_Text_PtNpc2, MSGBOX_NPC
	end

Route213_Text_PtNpc2::
	.string "I'd rather be in a pool than the sea.\p"
	.string "The salty tang of the sea tastes like\n"
	.string "my tears after a hard day at work...$"

Route213_EventScript_PtNpc3::
	msgbox Route213_Text_PtNpc3, MSGBOX_NPC
	end

Route213_Text_PtNpc3::
	.string "There's something on top of this big\n"
	.string "cliff here!\p"
	.string "My instincts tell me that, but how am I\n"
	.string "supposed to climb up?$"

Route213_EventScript_SNBomb::
	lock
	msgbox Route213_EventScript_SNBomb_T1, MSGBOX_DEFAULT
	faceplayer
	msgbox Route213_EventScript_SNBomb_T2, MSGBOX_DEFAULT
	msgbox Route213_EventScript_SNBomb_T3, MSGBOX_DEFAULT
	release
	end

Route213_EventScript_SNBomb_T3::
	.string "But, boy, this Galactic Bomb packs a\n"
	.string "pretty big wallop.\p"
	.string "With this baby here there’s not much we\n"
	.string "can’t blow up.\p"
	.string "I wonder what they have planned for\n"
	.string "this?$"

Route213_EventScript_SNBomb_T2::
	.string "Graw! You were eavesdropping! I was\n"
	.string "just thinking out loud!\p"
	.string "But I’m not going to waste my energy\n"
	.string "knocking you around...$"

Route213_EventScript_SNBomb_T1::
	.string "We needed the energy from the Valley\n"
	.string "Windworks to make this...\p"
	.string "It would take a scientific genius to\n"
	.string "make something like this...\p"
	.string "Therefore, our boss, who made this, is a\n"
	.string "scientific mechanical genius!$"

Route213_EventScript_SNBomb_L1::
	.string "Looker: Hello, my friend!\p"
	.string "The cargo that the Team Galactic\n"
	.string "brought is worrisome, so I have come.\p"
	.string "...You say the cargo, it was a bomb? And\n"
	.string "there was an explosion?\p"
	.string "The explosion was at the Great Marsh?\p"
	.string "Furthermore, you are pursuing a man... A\n"
	.string "man with funny bowl-cut hair.\p"
	.string "In an outfit that is very strange?\p"
	.string "In other words, that is the Team\n"
	.string "Galactic!$"

SE_S_Route213_Route213_EventScript_SNBomb_Looker::
	msgbox Route213_EventScript_SNBomb_L1, MSGBOX_NPC
	end

SE_S_Route213_Route213_EventScript_SNHoneyTree::
	msgbox SN_HoneyTree_Text_Wait, MSGBOX_NPC
	end

Route213_EventScript_PtSign1::
	msgbox Route213_Text_PtSign1, MSGBOX_SIGN
	end

Route213_Text_PtSign1::
	.string "Rt. 213 PASTORIA CITY$"

Route213_EventScript_PtSign2::
	msgbox Route213_Text_PtSign2, MSGBOX_SIGN
	end

Route213_Text_PtSign2::
	.string "Dr. Footstep's House Footprints\n"
	.string "Reveal All$"

Route213_EventScript_PtSign3::
	msgbox Route213_Text_PtSign3, MSGBOX_SIGN
	end

Route213_Text_PtSign3::
	.string "Hotel Grand Lake Another World on\n"
	.string "LAKE VALOR$"
