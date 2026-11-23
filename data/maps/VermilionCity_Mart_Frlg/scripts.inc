VermilionCity_Mart_Frlg_MapScripts::
	.byte 0

VermilionCity_Mart_EventScript_CooltrainerF::
	msgbox VermilionCity_Mart_Text_MonsGoodOrBadDependingOnTrainer, MSGBOX_NPC
	end

VermilionCity_Mart_EventScript_BaldingMan::
	msgbox VermilionCity_Mart_Text_TeamRocketAreWickedPeople, MSGBOX_NPC
	end

VermilionCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart VermilionCity_Mart_Items
	msgbox gText_PleaseComeAgain
	release
	end

	.align 2
VermilionCity_Mart_Items::
	.2byte ITEM_POKE_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_REPEL
	.2byte ITEM_NONE
	release
	end

VermilionCity_Mart_Text_TeamRocketAreWickedPeople::
	.string "There are wicked people who will use\n"
	.string "POKéMON for criminal acts.\p"
	.string "TEAM ROCKET trafficked in rare\n"
	.string "POKéMON, for example.\p"
	.string "They also abandoned POKéMON that\n"
	.string "they considered useless.\p"
	.string "That's the sort of horrid people\n"
	.string "they were, TEAM ROCKET.$"

VermilionCity_Mart_Text_MonsGoodOrBadDependingOnTrainer::
	.string "I think POKéMON can be good or\n"
	.string "bad. It depends on the TRAINER.$"

