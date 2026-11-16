Route32_hns_MapScripts::
	.byte 0


Route32_EventScript_BaldingMan::
	lock
	faceplayer
	msgbox Route32_Text_CooltrainerM_Experiences, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_ROUTE32_BALDINGMAN, DIR_EAST
	release
	end

Route32_Text_CooltrainerM_Experiences::
	.string "Your experiences in VIOLET CITY\n"
	.string "should be useful for your journey.$"

Route32_Text_RoarIntro::
	.string "WROOOOAR! PEOPLE RUN WHEN I\n"
	.string "ROAR! BUT YOU CAME LOOKING!\p"
	.string "THAT PLEASES ME! NOW TAKE THIS!$"

SE_J_Route32_hns_Route32_EventScript_Roar::
	msgbox Route32_Text_RoarIntro, MSGBOX_NPC
	end

Route32_EventScript_SuperPotion::
	finditem ITEM_SUPER_POTION
	end

Route32_EventScript_GreatBall::
	finditem ITEM_GREAT_BALL
	end

SE_J_Route32_hns_Route32_EventScript_Item_Bullet_Seed::
	end

Route32_EventScript_YoungsterAlbert::
	trainerbattle_single TRAINER_ALBERT_HNS, Route32_Text_YoungsterAlbert_Seen, Route32_Text_YoungsterAlbert_Beaten
	msgbox Route32_Text_YoungsterAlbert_After, MSGBOX_AUTOCLOSE
	end

Route32_Text_YoungsterAlbert_After::
	.string "I'm going to try to be the\n"
	.string "best with my favorites.\p"
	.string "I'm not using the same tough\n"
	.string "POKéMON as everyone else.$"

Route32_Text_YoungsterAlbert_Beaten::
	.string "You're strong!$"

Route32_Text_YoungsterAlbert_Seen::
	.string "I haven't seen you around before.\n"
	.string "So you think you are pretty tough?$"

Route32_EventScript_PicnickerLiz::
	trainerbattle_single TRAINER_LIZ_HNS, Route32_Text_PicnickerLiz1_Seen, Route32_Text_PicnickerLiz1_Beaten, Route32_EventScript_RegisterLiz
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route32_EventScript_RematchLiz
	msgbox Route32_Text_PicnickerLiz1_After, MSGBOX_AUTOCLOSE
	end

Route32_Text_PicnickerLiz1_After::
	.string "I was having a nice chat too.$"

Route32_EventScript_RematchLiz::
	trainerbattle_rematch TRAINER_LIZ_HNS, Route32_Text_LizRematchIntro, Route32_Text_LizRematchDefeat
	msgbox Route32_Text_LizPostRematch, MSGBOX_AUTOCLOSE
	end

Route32_Text_LizPostRematch::
	.string "I was having a nice chat too.$"

Route32_Text_LizRematchDefeat::
	.string "Oh! I've got to relieve\n"
	.string "my anger!$"

Route32_Text_LizRematchIntro::
	.string "Uh-huh. Yeah, and you know…\p"
	.string "Pardon? Battle? I'm on the phone.\n"
	.string "Oh, all right. But make it fast.$"

Route32_EventScript_RegisterLiz::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route32_Text_LizRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_LIZ_HNS
	release
	end

Route32_Text_LizRegister::
	.string "I was having a nice chat too.$"

Route32_Text_PicnickerLiz1_Beaten::
	.string "Oh! I've got to relieve\n"
	.string "my anger!$"

Route32_Text_PicnickerLiz1_Seen::
	.string "Uh-huh. Yeah, and you know…\p"
	.string "Pardon? Battle? I'm on the phone.\n"
	.string "Oh, all right. But make it fast.$"

Route32_EventScript_CamperRoland::
	trainerbattle_single TRAINER_ROLAND_HNS, Route32_Text_CamperRoland_Seen, Route32_Text_CamperRoland_Beaten
	msgbox Route32_Text_CamperRoland_After, MSGBOX_AUTOCLOSE
	end

Route32_Text_CamperRoland_After::
	.string "If you don't want to battle,\n"
	.string "just avoid eye contact.$"

Route32_Text_CamperRoland_Beaten::
	.string "Hmmm. This is disappointing.$"

Route32_Text_CamperRoland_Seen::
	.string "That glance… It's intriguing.$"

Route32_EventScript_FisherRalph::
	trainerbattle_single TRAINER_RALPH_HNS, Route32_Text_FisherRalph1_Seen, Route32_Text_FisherRalph1_Beaten, Route32_EventScript_RegisterRalph
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route32_EventScript_RematchRalph
	msgbox Route32_Text_FisherRalph1_After, MSGBOX_AUTOCLOSE
	end

Route32_Text_FisherRalph1_After::
	.string "Fishing is a lifelong\n"
	.string "passion.\p"
	.string "POKéMON are lifelong friends!$"

Route32_EventScript_RematchRalph::
	trainerbattle_rematch TRAINER_RALPH_HNS, Route32_Text_RalphRematchIntro, Route32_Text_RalphRematchDefeat
	msgbox Route32_Text_RalphPostRematch, MSGBOX_AUTOCLOSE
	end

Route32_Text_RalphPostRematch::
	.string "Fishing is a lifelong\n"
	.string "passion.\p"
	.string "POKéMON are lifelong friends!$"

Route32_Text_RalphRematchDefeat::
	.string "Tch! I tried to rush\n"
	.string "things…$"

Route32_Text_RalphRematchIntro::
	.string "I'm really good at both\n"
	.string "fishing and POKéMON.\p"
	.string "I'm not about to lose to any kid!$"

Route32_EventScript_RegisterRalph::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route32_Text_RalphRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_RALPH_HNS
	release
	end

Route32_Text_RalphRegister::
	.string "Fishing is a lifelong\n"
	.string "passion.\p"
	.string "POKéMON are lifelong friends!$"

Route32_Text_FisherRalph1_Beaten::
	.string "Tch! I tried to rush\n"
	.string "things…$"

Route32_Text_FisherRalph1_Seen::
	.string "I'm really good at both\n"
	.string "fishing and POKéMON.\p"
	.string "I'm not about to lose to any kid!$"

Route32_EventScript_FisherHenry::
	trainerbattle_single TRAINER_HENRY_HNS, Route32_Text_FisherHenry_Seen, Route32_Text_FisherHenry_Beaten
	msgbox Route32_Text_FisherHenry_After, MSGBOX_AUTOCLOSE
	end

Route32_Text_FisherHenry_After::
	.string "Freshly caught POKéMON are\n"
	.string "no match for properly raised ones.$"

Route32_Text_FisherHenry_Beaten::
	.string "SPLASH?$"

Route32_Text_FisherHenry_Seen::
	.string "My POKéMON? Freshly caught!$"

Route32_EventScript_FisherJustin::
	trainerbattle_single TRAINER_JUSTIN_HNS, Route32_Text_FisherJustin_Seen, Route32_Text_FisherJustin_Beaten
	msgbox Route32_Text_FisherJustin_After, MSGBOX_AUTOCLOSE
	end

Route32_Text_FisherJustin_After::
	.string "Calm, collected… The essence of\n"
	.string "fishing and POKéMON is the same.$"

Route32_Text_FisherJustin_Beaten::
	.string "Sploosh!$"

Route32_Text_FisherJustin_Seen::
	.string "Whoa!\p"
	.string "You made me lose that fish!$"

Route32_EventScript_YoungsterGordon::
	trainerbattle_single TRAINER_GORDON_HNS, Route32_Text_YoungsterGordon_Seen, Route32_Text_YoungsterGordon_Beaten
	msgbox Route32_Text_YoungsterGordon_After, MSGBOX_AUTOCLOSE
	end

Route32_Text_YoungsterGordon_After::
	.string "The grass is full of\n"
	.string "clingy things.$"

Route32_Text_YoungsterGordon_Beaten::
	.string "Darn. I thought I could win.$"

Route32_Text_YoungsterGordon_Seen::
	.string "I found some good POKéMON\n"
	.string "in the grass!\p"
	.string "I think they'll do it for me!$"

Route32_EventScript_SlowpokeTail::
	lock
	faceplayer
	msgbox Route32_Text_SlowpokeTailOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Route32_EventScript_SlowpokeTail2
	msgbox Route32_Text_RefusedSlowpokeTail, MSGBOX_DEFAULT
	closemessage
	release
	end

Route32_Text_RefusedSlowpokeTail::
	.string "You don't want it?\n"
	.string "Then scram. Shoo!$"

Route32_EventScript_SlowpokeTail2::
	msgbox Route32_Text_ThoughtKidsLoaded, MSGBOX_DEFAULT
	closemessage
	release
	end

Route32_Text_ThoughtKidsLoaded::
	.string "Tch! I thought kids\n"
	.string "these days were loaded…$"

Route32_Text_SlowpokeTailOffer::
	.string "How would you like to have this\n"
	.string "tasty, nutritious SLOWPOKETAIL?\p"
	.string "For you right now, just\n"
	.string "¥1,000,000!\p"
	.string "You'll want this!$"

Route32_EventScript_GreatBallII::
	finditem ITEM_GREAT_BALL
	end

Route32_EventScript_BirdkeeperPeter::
	trainerbattle_single TRAINER_PETER_HNS, Route32_Text_BirdKeeperPeter_Seen, Route32_Text_BirdKeeperPeter_Beaten
	msgbox Route32_Text_BirdKeeperPeter_After, MSGBOX_AUTOCLOSE
	end

Route32_Text_BirdKeeperPeter_After::
	.string "I should train again at the\n"
	.string "GYM in VIOLET CITY.$"

Route32_Text_BirdKeeperPeter_Beaten::
	.string "I know what my weaknesses are.$"

Route32_Text_BirdKeeperPeter_Seen::
	.string "That BADGE! It's from VIOLET CITY!\n"
	.string "You beat FALKNER?$"

Route32_Text_MeetFrieda::
	.string "FRIEDA: Yahoo!\p"
	.string "I'm FRIEDA of the WEEKDAY FAMILY!\n"
	.string "Nice to meet you!\p"
	.string "If you can guess my favorite day,\n"
	.string "I'll give you a reward.$"

SE_J_Route32_hns_Route32_EventScript_Frieda::
	msgbox Route32_Text_MeetFrieda, MSGBOX_NPC
	end

Route32_EventScript_Sign1::
	lock
	msgbox Route32_Text_Sign1, MSGBOX_SIGN
	closemessage
	release
	end

Route32_Text_Sign1::
	.string "ROUTE 32\p"
	.string "VIOLET CITY - AZALEA TOWN$"

Route32_EventScript_Sign2::
	lock
	msgbox Route32_Text_Sign2, MSGBOX_SIGN
	closemessage
	release
	end

Route32_Text_Sign2::
	.string "RUINS OF ALPH\n"
	.string "EAST ENTRANCE$"

Route32_EventScript_Sign3::
	lock
	msgbox Route32_Text_Sign3, MSGBOX_SIGN
	closemessage
	release
	end

Route32_Text_Sign3::
	.string "UNION CAVE\n"
	.string "AHEAD$"
