CianwoodHouse3_hns_MapScripts::
	.byte 0


CianwoodCity_Text_ManiacAskShuckle::
	.string "I, I'm in shock!\p"
	.string "A guy about your age with piercing\n"
	.string "eyes and long hair came in.\p"
	.string "He scared me into giving him my\n"
	.string "prized POKéMON!\p"
	.string "I still have one left, but what if\n"
	.string "he comes back?\p"
	.string "You look strong. Could you look\n"
	.string "after my POKéMON for a while?$"

SE_J_CianwoodHouse3_hns_CianwoodCity_EventScript_Kirk::
	msgbox CianwoodCity_Text_ManiacAskShuckle, MSGBOX_NPC
	end
