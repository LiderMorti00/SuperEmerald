@ Super Emerald: elevators of the Veilstone Dept. Store and the Sunyshore Vista Lighthouse.
@ The elevator's exit warps are dynamic: entering from a floor sets the dynamic warp to that
@ floor, and choosing a floor here changes it (setdynamicwarp), as in Lilycove.

SE_EventScript_ElevatorSetFloor::
	special SE_SetSinnohElevatorFloor
	return

SE_EventScript_ElevatorExit::
	special CloseDeptStoreElevatorWindow
	release
	end

SE_EventScript_ElevatorMove::
	special CloseDeptStoreElevatorWindow
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	waitse
	special MoveElevator
	waitstate
	setflag FLAG_TEMP_2
	return

@ Veilstone Dept. Store: 1F-5F
SE_EventScript_VeilstoneElevator::
	lock
	faceplayer
	call_if_unset FLAG_TEMP_2, SE_EventScript_ElevatorSetFloor
	copyvar VAR_0x8005, VAR_DEPT_STORE_FLOOR
	special ShowDeptStoreElevatorFloorSelect
	message SE_Text_ElevatorWhichFloor
	waitmessage
	setvar VAR_0x8007, DEPT_STORE_FLOORNUM_5F
	subvar VAR_0x8007, VAR_DEPT_STORE_FLOOR
	dynmultipush gText_5F, 0
	dynmultipush gText_4F, 1
	dynmultipush gText_3F, 2
	dynmultipush gText_2F, 3
	dynmultipush gText_1F, 4
	dynmultipush gText_Exit, 5
	dynmultistack 0, 0, FALSE, 6, FALSE, VAR_0x8007, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case 0, SE_EventScript_Veilstone5F
	case 1, SE_EventScript_Veilstone4F
	case 2, SE_EventScript_Veilstone3F
	case 3, SE_EventScript_Veilstone2F
	case 4, SE_EventScript_Veilstone1F
	goto SE_EventScript_ElevatorExit

SE_EventScript_Veilstone1F::
	setvar VAR_0x8006, DEPT_STORE_FLOORNUM_1F
	setdynamicwarp MAP_VEILSTONE_CITY_DEPARTMENT_STORE_1F_SINNOH, 6, 1
	goto SE_EventScript_VeilstoneRide
SE_EventScript_Veilstone2F::
	setvar VAR_0x8006, DEPT_STORE_FLOORNUM_2F
	setdynamicwarp MAP_VEILSTONE_CITY_DEPARTMENT_STORE_2F_SINNOH, 6, 1
	goto SE_EventScript_VeilstoneRide
SE_EventScript_Veilstone3F::
	setvar VAR_0x8006, DEPT_STORE_FLOORNUM_3F
	setdynamicwarp MAP_VEILSTONE_CITY_DEPARTMENT_STORE_3F_SINNOH, 6, 1
	goto SE_EventScript_VeilstoneRide
SE_EventScript_Veilstone4F::
	setvar VAR_0x8006, DEPT_STORE_FLOORNUM_4F
	setdynamicwarp MAP_VEILSTONE_CITY_DEPARTMENT_STORE_4F_SINNOH, 6, 1
	goto SE_EventScript_VeilstoneRide
SE_EventScript_Veilstone5F::
	setvar VAR_0x8006, DEPT_STORE_FLOORNUM_5F
	setdynamicwarp MAP_VEILSTONE_CITY_DEPARTMENT_STORE_5F_SINNOH, 6, 1
SE_EventScript_VeilstoneRide::
	goto_if_eq VAR_DEPT_STORE_FLOOR, VAR_0x8006, SE_EventScript_ElevatorExit
	call SE_EventScript_ElevatorMove
	copyvar VAR_DEPT_STORE_FLOOR, VAR_0x8006
	goto SE_EventScript_ElevatorExit

@ Vista Lighthouse: ground floor and top
SE_EventScript_LighthouseElevator::
	lock
	faceplayer
	call_if_unset FLAG_TEMP_2, SE_EventScript_ElevatorSetFloor
	copyvar VAR_0x8005, VAR_DEPT_STORE_FLOOR
	special ShowDeptStoreElevatorFloorSelect
	message SE_Text_ElevatorWhichFloor
	waitmessage
	setvar VAR_0x8007, 1
	call_if_eq VAR_DEPT_STORE_FLOOR, DEPT_STORE_FLOORNUM_ROOFTOP, SE_EventScript_LighthouseCursorTop
	dynmultipush SE_Text_LighthouseTop, 0
	dynmultipush gText_1F, 1
	dynmultipush gText_Exit, 2
	dynmultistack 0, 0, FALSE, 3, FALSE, VAR_0x8007, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case 0, SE_EventScript_LighthouseToTop
	case 1, SE_EventScript_LighthouseTo1F
	goto SE_EventScript_ElevatorExit

SE_EventScript_LighthouseCursorTop::
	setvar VAR_0x8007, 0
	return

SE_EventScript_LighthouseToTop::
	setvar VAR_0x8006, DEPT_STORE_FLOORNUM_ROOFTOP
	setdynamicwarp MAP_SUNYSHORE_CITY_VISTA_LIGHTHOUSE_SINNOH, 6, 7
	goto SE_EventScript_VeilstoneRide
SE_EventScript_LighthouseTo1F::
	setvar VAR_0x8006, DEPT_STORE_FLOORNUM_1F
	setdynamicwarp MAP_SUNYSHORE_CITY_SINNOH, 59, 44
	goto SE_EventScript_VeilstoneRide

SE_Text_LighthouseTop:
	.string "TOP$"

SE_Text_ElevatorWhichFloor:
	.string "Which floor would you like?$"
