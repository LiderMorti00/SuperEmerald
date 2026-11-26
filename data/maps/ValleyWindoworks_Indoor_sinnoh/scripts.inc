ValleyWindoworks_Indoor_sinnoh_MapScripts::
	.byte 0

ValleyWindoworks_Indoor_EventScript_Worker::
	lock
	faceplayer
	goto_if_ge VAR_SN_SINNOH_STORY, 22, ValleyWindoworks_Indoor_EventScript_WorkerAfter
	msgbox ValleyWindoworks_Indoor_Text_WorkerHelp, MSGBOX_DEFAULT
	release
	end

ValleyWindoworks_Indoor_Text_WorkerHelp::
	.string "Please… stop them!$"

ValleyWindoworks_Indoor_EventScript_WorkerAfter::
	msgbox ValleyWindoworks_Indoor_Text_WorkerAfter, MSGBOX_DEFAULT
	release
	end

ValleyWindoworks_Indoor_Text_WorkerAfter::
	.string "Papa: Oh, yes, a balloon POKéMON\n"
	.string "appears in front of the windworks.\p"
	.string "It's always a certain day of the week,\n"
	.string "but I'm not sure which day.\p"
	.string "Could its appearance have something\n"
	.string "to do with this windworks using\p"
	.string "wind-generated energy?$"

