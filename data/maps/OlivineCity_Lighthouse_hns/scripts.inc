OlivineCity_Lighthouse_hns_MapScripts::
	.byte 0


OlivineLighthouse_EventScript_1FPokefanF::
	lock
	faceplayer
	msgbox OlivineLighthouse_Text_1FPokefanF, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineLighthouse_Text_1FPokefanF::
	.string "In the past, POKéMON used to light\n"
	.string "the sea around OLIVINE at night.\p"
	.string "The LIGHTHOUSE was built in honor\n"
	.string "of those noble POKéMON.$"

@2nd floor==============================================================================================================================

OlivineLighthouse_EventScript_1FSailor::
	lock
	faceplayer
	msgbox OlivineLighthouse_Text_1FSailor, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineLighthouse_Text_1FSailor::
	.string "People train at this LIGHTHOUSE.\p"
	.string "It's not easy to climb with all\n"
	.string "the TRAINERS waiting inside.$"

OlivineLighthouse_EventScript_Huey::
	trainerbattle_single TRAINER_HUEY_HNS, OlivineLighthouse_Text_SailorHueySeen, OlivineLighthouse_Text_SailorHueyBeaten, OlivineLighthouse_EventScript_RegisterHuey
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, OlivineLighthouse_EventScript_RematchHuey
	msgbox OlivineLighthouse_Text_SailorHueyAfter, MSGBOX_AUTOCLOSE
	end

OlivineLighthouse_Text_SailorHueyAfter::
	.string "What power! How would you like\n"
	.string "to sail the seas with me?$"

OlivineLighthouse_EventScript_RematchHuey::
	trainerbattle_rematch TRAINER_HUEY_HNS, OlivineLighthouse_Text_HueyRematchIntro, OlivineLighthouse_Text_HueyRematchDefeat
	msgbox OlivineLighthouse_Text_HueyPostRematch, MSGBOX_AUTOCLOSE
	end

OlivineLighthouse_Text_HueyPostRematch::
	.string "What power! How would you like\n"
	.string "to sail the seas with me?$"

OlivineLighthouse_Text_HueyRematchDefeat::
	.string "Urf!\n"
	.string "I lose!$"

OlivineLighthouse_Text_HueyRematchIntro::
	.string "Men of the sea are always\n"
	.string "spoiling for a good fight!$"

OlivineLighthouse_EventScript_RegisterHuey::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox OlivineLighthouse_Text_HueyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_HUEY_HNS
	release
	end

OlivineLighthouse_Text_HueyRegister::
	.string "What power! How would you like\n"
	.string "to sail the seas with me?$"

OlivineLighthouse_Text_SailorHueyBeaten::
	.string "Urf!\n"
	.string "I lose!$"

OlivineLighthouse_Text_SailorHueySeen::
	.string "Men of the sea are always\n"
	.string "spoiling for a good fight!$"

OlivineLighthouse_EventScript_GentlemanAlfred::
    trainerbattle_single TRAINER_ALFRED_HNS, OlivineLighthouse_Text_GentlemanAlfredSeen, OlivineLighthouse_Text_GentlemanAlfredBeaten
    msgbox OlivineLighthouse_Text_GentlemanAlfredAfter, MSGBOX_AUTOCLOSE
    end

OlivineLighthouse_Text_GentlemanAlfredAfter::
	.string "AMPHY is back on duty upstairs.\p"
	.string "The ships can see the light again.$"

@3rd floor==============================================================================================================================

OlivineLighthouse_Text_GentlemanAlfredBeaten::
	.string "Ah! I can see that you're\n"
	.string "serious.$"

OlivineLighthouse_Text_GentlemanAlfredSeen::
	.string "Hm? This is no place\n"
	.string "for playing.$"

OlivineLighthouse_EventScript_SailorTerrell::
    trainerbattle_single TRAINER_TERRELL_HNS, OlivineLighthouse_Text_SailorTerrellSeen, OlivineLighthouse_Text_SailorTerrellBeaten
    msgbox OlivineLighthouse_Text_SailorTerrellAfter, MSGBOX_AUTOCLOSE
    end

OlivineLighthouse_Text_SailorTerrellAfter::
	.string "Every time I return to OLIVINE,\n"
	.string "I visit the GYM.\p"
	.string "The GYM LEADER's POKéMON type\n"
	.string "changed without me noticing.$"

OlivineLighthouse_Text_SailorTerrellBeaten::
	.string "You are both kind and strong…$"

OlivineLighthouse_Text_SailorTerrellSeen::
	.string "Sailors are both kind and strong.\n"
	.string "How about you?$"

OlivineLighthouse_EventScript_BirdKeeperTheo::
    trainerbattle_single TRAINER_THEO_HNS, OlivineLighthouse_Text_BirdKeeperTheoSeen, OlivineLighthouse_Text_BirdKeeperTheoBeaten
    msgbox OlivineLighthouse_Text_BirdKeeperTheoAfter, MSGBOX_AUTOCLOSE
    end

OlivineLighthouse_Text_BirdKeeperTheoAfter::
	.string "I came to see AMPHY's light.\p"
	.string "Now I'm trying to find my way\n"
	.string "up to the lantern room.$"

OlivineLighthouse_Text_BirdKeeperTheoBeaten::
	.string "I'll let you get back to the climb…$"

OlivineLighthouse_Text_BirdKeeperTheoSeen::
	.string "Why are you here? Are you just\n"
	.string "going to gawk? I suggest you leave!$"

OlivineLighthouse_EventScript_GentlemanPreston::
    trainerbattle_single TRAINER_PRESTON_HNS, OlivineLighthouse_Text_GentlemanPrestonSeen, OlivineLighthouse_Text_GentlemanPrestonBeaten
    msgbox OlivineLighthouse_Text_GentlemanPrestonAfter, MSGBOX_AUTOCLOSE
    end

OlivineLighthouse_Text_GentlemanPrestonAfter::
	.string "JASMINE used to use ROCK-type\n"
	.string "POKéMON like ONIX.$"

@4th floor==============================================================================================================================

OlivineLighthouse_Text_GentlemanPrestonBeaten::
	.string "…sigh… I must train some more…$"

OlivineLighthouse_Text_GentlemanPrestonSeen::
	.string "I travel the world to train my\n"
	.string "POKéMON. I wish to battle you.$"

OlivineLighthouse_EventScript_SailorKent::
    trainerbattle_single TRAINER_KENT_HNS, OlivineLighthouse_Text_SailorKentSeen, OlivineLighthouse_Text_SailorKentBeaten
    msgbox OlivineLighthouse_Text_SailorKentAfter, MSGBOX_AUTOCLOSE
    end

OlivineLighthouse_Text_SailorKentAfter::
	.string "The pharmacy in CIANWOOD helped\n"
	.string "AMPHY get back on its feet.$"

OlivineLighthouse_Text_SailorKentBeaten::
	.string "I can't manage a smile either…$"

OlivineLighthouse_Text_SailorKentSeen::
	.string "JASMINE used to spend whole nights\n"
	.string "here looking after AMPHY.\p"
	.string "I'd do the same for my POKéMON!$"

OlivineLighthouse_EventScript_LassConnie::
    trainerbattle_single TRAINER_CONNIE_HNS, OlivineLighthouse_Text_LassConnieSeen, OlivineLighthouse_Text_LassConnieBeaten
    msgbox OlivineLighthouse_Text_LassConnieAfter, MSGBOX_AUTOCLOSE
    end

OlivineLighthouse_Text_LassConnieAfter::
	.string "I'm glad AMPHY is well enough to\n"
	.string "light the sea again.\p"
	.string "JASMINE can get back to her GYM.$"

@5th floor==============================================================================================================================

OlivineLighthouse_Text_LassConnieBeaten::
	.string "Aaack! My POKéMON!$"

OlivineLighthouse_Text_LassConnieSeen::
	.string "I'm heading upstairs to see AMPHY.\p"
	.string "How about a battle on the way?$"

OlivineLighthouse_EventScript_BirdKeeperDenis::
    trainerbattle_single TRAINER_DENIS_HNS, OlivineLighthouse_Text_BirdKeeperDenisSeen, OlivineLighthouse_Text_BirdKeeperDenisBeaten
    msgbox OlivineLighthouse_Text_BirdKeeperDenisAfter, MSGBOX_AUTOCLOSE
    end

OlivineLighthouse_Text_BirdKeeperDenisAfter::
	.string "My POKéMON learned how to use FLY in\n"
	.string "CIANWOOD.\p"
	.string "Well, since I'm a loser, I'll FLY\n"
	.string "across the sea…$"

@6th floor==============================================================================================================================

OlivineLighthouse_Text_BirdKeeperDenisBeaten::
	.string "Oops… They crashed…$"

OlivineLighthouse_Text_BirdKeeperDenisSeen::
	.string "We're pretty high up here. My bird\n"
	.string "POKéMON are in prime form.$"

OlivineLighthouse_EventScript_SailorErnest::
    trainerbattle_single TRAINER_ERNEST_HNS, OlivineLighthouse_Text_SailorErnestSeen, OlivineLighthouse_Text_SailorErnestBeaten
    msgbox OlivineLighthouse_Text_SailorErnestAfter, MSGBOX_AUTOCLOSE
    end

OlivineLighthouse_Text_SailorErnestAfter::
	.string "A GYM LEADER isn't just about being\n"
	.string "strong.\p"
	.string "A LEADER also needs to be\n"
	.string "compassionate.$"

OlivineLighthouse_Text_SailorErnestBeaten::
	.string "Whoa, whoa. You're overwhelming!$"

OlivineLighthouse_Text_SailorErnestSeen::
	.string "I was going to challenge JASMINE\n"
	.string "at the GYM after my shift.\p"
	.string "Care to help me warm up?$"

OlivineLighthouse_Text_JasmineCianwoodPharmacy::
	.string "JASMINE: …This POKéMON always kept\n"
	.string "the sea lit at night.\p"
	.string "…But it suddenly got sick… It's\n"
	.string "gasping for air…\p"
	.string "…I understand that there is a\n"
	.string "wonderful PHARMACY in CIANWOOD…\p"
	.string "But that's across the sea…\n"
	.string "And I can't leave AMPHY unattended…$"

SE_J_OlivineCity_Lighthouse_hns_OlivineLighthouse_EventScript_Jasmine::
	msgbox OlivineLighthouse_Text_JasmineCianwoodPharmacy, MSGBOX_NPC
	end

OlivineLighthouse_Text_AmphyPaluPalulu::
	.string "AMPHY: Palu! Palulu!$"

SE_J_OlivineCity_Lighthouse_hns_OlivineLighthouse_EventScript_Ampharos::
	msgbox OlivineLighthouse_Text_AmphyPaluPalulu, MSGBOX_NPC
	end

OlivineLighthouse_EventScript_Item_Protein::
    finditem ITEM_PROTEIN
    end

OlivineLighthouse_EventScript_Item_HyperPotion::
    finditem ITEM_HYPER_POTION
    end

SE_J_OlivineCity_Lighthouse_hns_OlivineLighthouse_EventScript_Item_TMSwagger::
	end

OlivineLighthouse_EventScript_Item_RareCandy::
    finditem ITEM_RARE_CANDY
    end

OlivineLighthouse_EventScript_Item_Ether::
    finditem ITEM_ETHER
    end
