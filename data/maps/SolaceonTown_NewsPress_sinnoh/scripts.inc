SolaceonTown_NewsPress_sinnoh_MapScripts::
	.byte 0


SolaceonTown_NewsPress_EventScript_SNEditor_Ask::
	.string "I’m the editor of the Sinnoh Now\n"
	.string "newspaper! For today’s edition, I need\l"
	.string "a photo of a {STR_VAR_1}.\p"
	.string "If you have one with you, show it to me!$"

SE_S_SolaceonTown_NewsPress_SolaceonTown_NewsPress_EventScript_SNEditor::
	msgbox SolaceonTown_NewsPress_EventScript_SNEditor_Ask, MSGBOX_NPC
	end

SolaceonTown_NewsPress_EventScript_PtNpc2::
	lock
	faceplayer
	msgbox SolaceonTown_NewsPress_Text_PtNpc2_0, MSGBOX_DEFAULT
	release
	end

SolaceonTown_NewsPress_Text_PtNpc2_0::
	.string "The Sinnoh region’s newspaper is tiny,\n"
	.string "but it has many fans.\p"
	.string "That newspaper is printed right here!$"
