GoldenrodCity_RadioTower_5F_hns_MapScripts::
	.byte 0

GoldenrodCity_RadioTower_5F_EventScript_Ben::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_5F_Text_Ben, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_5F_Text_Ben::
	.string "BEN: Do you listen to our music?$"
