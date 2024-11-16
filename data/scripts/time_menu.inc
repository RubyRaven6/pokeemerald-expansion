WaitingMenu::
	lockall
	dynmultichoice 1, 1, FALSE, 2, 0, DYN_MULTICHOICE_CB_NONE, WaitingMenu_Text_0, WaitingMenu_Text_1
	switch VAR_RESULT
	case 0, WaitingMenu_2
	case 1, WaitingMenu_3
	return

WaitingMenu_2:
	goto Add_Time
	return

WaitingMenu_3:
	goto Set_Time
	return


Add_Time:
	dynmultichoice 1, 1, FALSE, 2, 0, DYN_MULTICHOICE_CB_NONE, Add_Time_Text_0, Add_Time_Text_1
	switch VAR_RESULT
	case 0, Add_Time_2
	case 1, Add_Time_3
	return

Add_Time_2:
	goto Add_Days
	return

Add_Time_3:
	goto Add_Hours
	return


Add_Days:
	dynmultichoice 1, 1, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, Add_Days_Text_0, Add_Days_Text_1, Add_Days_Text_2
	switch VAR_RESULT
	case 0, Add_Days_2
	case 1, Add_Days_3
	case 2, Add_Days_4
	return

Add_Days_2:
	fadescreen FADE_TO_BLACK
	addday 1
	msgbox Add_Days_Text_3
	waitmessage
	closemessage
	fadescreen FADE_FROM_BLACK
	end

Add_Days_3:
	fadescreen FADE_TO_BLACK
	addday 6
	msgbox Add_Days_Text_3
	waitmessage
	closemessage
	fadescreen FADE_FROM_BLACK
	end

Add_Days_4:
	fadescreen FADE_TO_BLACK
	addday 12
	msgbox Add_Days_Text_3
	waitmessage
	closemessage
	fadescreen FADE_FROM_BLACK
	end


Add_Hours:
	dynmultichoice 1, 1, FALSE, 2, 0, DYN_MULTICHOICE_CB_NONE, Add_Days_Text_0, Add_Days_Text_1, Add_Days_Text_2
	switch VAR_RESULT
	case 0, Add_Hours_2
	case 1, Add_Hours_3
	case 2, Add_Hours_4
	return

Add_Hours_2:
	fadescreen FADE_TO_BLACK
	addhour 1
	msgbox Add_Days_Text_3
	waitmessage
	closemessage
	fadescreen FADE_FROM_BLACK
	end

Add_Hours_3:
	fadescreen FADE_TO_BLACK
	addhour 6
	msgbox Add_Days_Text_3
	waitmessage
	closemessage
	fadescreen FADE_FROM_BLACK
	end

Add_Hours_4:
	fadescreen FADE_TO_BLACK
	addhour 12
	msgbox Add_Days_Text_3
	waitmessage
	closemessage
	fadescreen FADE_FROM_BLACK
	end


WaitingMenu_Text_0:
	.string "Add time$"

WaitingMenu_Text_1:
	.string "Set time$"

Add_Time_Text_0:
	.string "Add Day$"

Add_Time_Text_1:
	.string "Add Hour$"

Add_Days_Text_0:
	.string "Add 1$"

Add_Days_Text_1:
	.string "Add 6$"

Add_Days_Text_2:
	.string "Add 12$"

Add_Days_Text_3:
	.string "You wait for a while…$"
