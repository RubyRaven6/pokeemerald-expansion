# In-Game Clock Suite
This feature branch creates a system that operates practically independent of the real time clock. It also includes macros that allow developers to dynamically change the time and date within their game. If you wish to create a hack with real-time elements (i.e. tied to real-life time), do NOT use this feature branch, as it assumes you want to create an in-game time system (i.e. something more akin to Minecraft, SV, and PLA).

## Changes
### System of Time
In its current set up, the branch has a default of 28 day months, and 12 month years. Because all the months have the same length, all Weekdays also fall under the same day every month. Lastly, the maximum amount of years a game can have is 65,535.

### New Macros
- `addtime`
    - `addtime(years, month, days, hours, minutes, seconds)`
    - This macro allows you to add a number of specific units of time. For example, if you wanted to add a specific amount of time to the current time.
    - For example, `addtime(1, 10, 27, 5, 15, 0)` advances time by 1 year, 10 months, 27 days, 5 hours, 15 minutes, and 0 seconds.
    - This also accounts for overlap (i.e. when adding time would cause it to got to the next unit of time), as the next biggest unit of time will have 1 added to it as well, and the smaller unit will be reset to 0.
        - Example 1: `addtime(1, 366, 0, 0, 0, 0)` will add 2 years, as 366 days = 1 year.
        - Example 2: Current ingame time is at 0 years, and 11 months. `addtime(0, 1, 0, 0, 0, 0)` shifts the time to year 1 and month 0.
- `settime`
    - `settime(years, month, days, hours, minutes, seconds)`
    - This sets the in-game time to a specified time in-game.
    - For example `settime(1, 2, 3, 4, 5, 6)` will set the in-game time to Year 1, Month 2, Day 3, Hour 4, Minute 5, and Second 6.

- Specific Unit Macros
    - Each unit of time has their own `add` and `set` variants, except for seconds.
    - `addyear`, `addmonth`, `addday`, `addhour`, `addminute`
    - `setyear`, `setmonth`, `setday`, `sethour`, `setminute`

### Menu Clocks integration
It's fairly simple to integrate the In-Game clock with menu clocks, such as Pawkkie's. Simply change any references to `gLocalTime.###`, where ### is a unit such as hours (gLocalTime.hour, gLocalTime.minute), and replace it with a respective Get function. All of these can be found below:
- GetYear()
- GetMonth()
- GetDay()
- GetHour()
- GetMinute()
- GetSecond()
Of course, this is in any file **except** `rtc.c`.

### Wallclock
The wallclock has also been changed to reflect and manipulate the ingame time.

## Testing
If you want to test out the fake RTC, you can replace the Fat Man scripts in Littleroot Town with these:

### What to Remove
```diff

	setobjectxy LOCALID_BIRCH, 14, 10
	end

- LittlerootTown_EventScript_FatMan::
-	msgbox LittlerootTown_Text_CanUsePCToStoreItems, MSGBOX_NPC
-	end

LittlerootTown_EventScript_Boy::
	msgbox LittlerootTown_Text_BirchSpendsDaysInLab, MSGBOX_NPC
	end

@@ -957,11 +954,6 @@ LittlerootTown_Text_ComeHomeIfAnythingHappens:

	.string "Go on, go get them, honey!$"

- LittlerootTown_Text_CanUsePCToStoreItems:
-	.string "If you use a PC, you can store items\n"
-	.string "and POKéMON.\p"
-	.string "The power of science is staggering!$"

 LittlerootTown_Text_BirchSpendsDaysInLab:
	.string "PROF. BIRCH spends days in his LAB\n"
```
### Poryscript
```
script LittlerootTown_EventScript_FatMan{
    lockall
    faceplayer
	msgbox(LittlerootTown_Text_CanUsePCToStoreItems, MSGBOX_DEFAULT)
    pausefakertc
    dynmultichoice(5, 1, FALSE, 5, 1, DYN_MULTICHOICE_CB_NONE, "Add time", "Set Time")
    switch(var(VAR_RESULT)){
        case 0:
            call(LittlerootTown_EventScript_AddTimeChoice)
            waitmessage
            closemessage
        case 1:
            call(LittlerootTown_EventScript_SetTimeChoice)
            waitmessage
            closemessage
    }
    resumefakertc
	end
}

script LittlerootTown_EventScript_AddTimeChoice{
    dynmultichoice(10, 1, FALSE, 5, 1, DYN_MULTICHOICE_CB_NONE, "Add 1 to all time units", "Add 1 year", "Add 1 month", "Add 1 day", "Add 1 hour", "Add 1 minute")
    switch(var(VAR_RESULT)){
        case 0:
            addtime(1, 1, 1, 1, 1, 1)
            return
        case 1:
            addyear(1)
            return
        case 2:
            addmonth(1)
            return
        case 3:
            addday(1)
            return
        case 4:
            addhour(1)
            return
        case 5:
            addminute(1)
            return
    }
}

script LittlerootTown_EventScript_SetTimeChoice{
    dynmultichoice(10, 1, FALSE, 5, 1, DYN_MULTICHOICE_CB_NONE, "Set to specific time", "Set to year 5", "Set to month 8", "Set to day 21", "Set to hour 10", "Set to minute 45")
    switch(var(VAR_RESULT)){
        case 0:
            settime(40, 6, 9, 16, 41, 0)
        case 1:
            setyear(5)
            return
        case 2:
            setmonth(8)
            return
        case 3:
            setday(21)
            return
        case 4:
            sethour(10)
            return
        case 5:
            setminute(45)
            return
    }
}

text(local) LittlerootTown_Text_CanUsePCToStoreItems{
	"With the In-Game Time Suite, you can\n"
	"control in-game time however you like!\p"
	"What would you like to do?"
}
```
### Native Scripting
```
LittlerootTown_EventScript_FatMan::
	lockall
	faceplayer
	msgbox LittlerootTown_Text_CanUsePCToStoreItems, MSGBOX_DEFAULT
	pausefakertc
	dynmultichoice 5, 1, FALSE, 5, 1, DYN_MULTICHOICE_CB_NONE, LittlerootTown_EventScript_FatMan_Text_0, LittlerootTown_EventScript_FatMan_Text_1
	switch VAR_RESULT
	case 0, LittlerootTown_EventScript_FatMan_3
	case 1, LittlerootTown_EventScript_FatMan_4
LittlerootTown_EventScript_FatMan_1:
	resumefakertc
	end

LittlerootTown_EventScript_FatMan_3:
	call LittlerootTown_EventScript_AddTimeChoice
	waitmessage
	closemessage
	goto LittlerootTown_EventScript_FatMan_1

LittlerootTown_EventScript_FatMan_4:
	call LittlerootTown_EventScript_SetTimeChoice
	waitmessage
	closemessage
	goto LittlerootTown_EventScript_FatMan_1


LittlerootTown_EventScript_AddTimeChoice::
	dynmultichoice 10, 1, FALSE, 5, 1, DYN_MULTICHOICE_CB_NONE, LittlerootTown_EventScript_AddTimeChoice_Text_0, LittlerootTown_EventScript_AddTimeChoice_Text_1, LittlerootTown_EventScript_AddTimeChoice_Text_2, LittlerootTown_EventScript_AddTimeChoice_Text_3, LittlerootTown_EventScript_AddTimeChoice_Text_4, LittlerootTown_EventScript_AddTimeChoice_Text_5
	switch VAR_RESULT
	case 0, LittlerootTown_EventScript_AddTimeChoice_2
	case 1, LittlerootTown_EventScript_AddTimeChoice_3
	case 2, LittlerootTown_EventScript_AddTimeChoice_4
	case 3, LittlerootTown_EventScript_AddTimeChoice_5
	case 4, LittlerootTown_EventScript_AddTimeChoice_6
	case 5, LittlerootTown_EventScript_AddTimeChoice_7
	return

LittlerootTown_EventScript_AddTimeChoice_2:
	addtime 1, 1, 1, 1, 1, 1
	return

LittlerootTown_EventScript_AddTimeChoice_3:
	addyear 1
	return

LittlerootTown_EventScript_AddTimeChoice_4:
	addmonth 1
	return

LittlerootTown_EventScript_AddTimeChoice_5:
	addday 1
	return

LittlerootTown_EventScript_AddTimeChoice_6:
	addhour 1
	return

LittlerootTown_EventScript_AddTimeChoice_7:
	addminute 1
	return


LittlerootTown_EventScript_SetTimeChoice::
	dynmultichoice 10, 1, FALSE, 5, 1, DYN_MULTICHOICE_CB_NONE, LittlerootTown_EventScript_SetTimeChoice_Text_0, LittlerootTown_EventScript_SetTimeChoice_Text_1, LittlerootTown_EventScript_SetTimeChoice_Text_2, LittlerootTown_EventScript_SetTimeChoice_Text_3, LittlerootTown_EventScript_SetTimeChoice_Text_4, LittlerootTown_EventScript_SetTimeChoice_Text_5
	switch VAR_RESULT
	case 0, LittlerootTown_EventScript_SetTimeChoice_2
	case 1, LittlerootTown_EventScript_SetTimeChoice_3
	case 2, LittlerootTown_EventScript_SetTimeChoice_4
	case 3, LittlerootTown_EventScript_SetTimeChoice_5
	case 4, LittlerootTown_EventScript_SetTimeChoice_6
	case 5, LittlerootTown_EventScript_SetTimeChoice_7
	return

LittlerootTown_EventScript_SetTimeChoice_2:
	settime 40, 6, 9, 16, 41, 0
	return

LittlerootTown_EventScript_SetTimeChoice_3:
	setyear 5
	return

LittlerootTown_EventScript_SetTimeChoice_4:
	setmonth 8
	return

LittlerootTown_EventScript_SetTimeChoice_5:
	setday 21
	return

LittlerootTown_EventScript_SetTimeChoice_6:
	sethour 10
	return

LittlerootTown_EventScript_SetTimeChoice_7:
	setminute 45
	return


LittlerootTown_EventScript_FatMan_Text_0:
	.string "Add time$"

LittlerootTown_EventScript_FatMan_Text_1:
	.string "Set Time$"

LittlerootTown_EventScript_AddTimeChoice_Text_0:
	.string "Add 1 to all time units$"

LittlerootTown_EventScript_AddTimeChoice_Text_1:
	.string "Add 1 year$"

LittlerootTown_EventScript_AddTimeChoice_Text_2:
	.string "Add 1 month$"

LittlerootTown_EventScript_AddTimeChoice_Text_3:
	.string "Add 1 day$"

LittlerootTown_EventScript_AddTimeChoice_Text_4:
	.string "Add 1 hour$"

LittlerootTown_EventScript_AddTimeChoice_Text_5:
	.string "Add 1 minute$"

LittlerootTown_EventScript_SetTimeChoice_Text_0:
	.string "Set to specific time$"

LittlerootTown_EventScript_SetTimeChoice_Text_1:
	.string "Set to year 5$"

LittlerootTown_EventScript_SetTimeChoice_Text_2:
	.string "Set to month 8$"

LittlerootTown_EventScript_SetTimeChoice_Text_3:
	.string "Set to day 21$"

LittlerootTown_EventScript_SetTimeChoice_Text_4:
	.string "Set to hour 10$"

LittlerootTown_EventScript_SetTimeChoice_Text_5:
	.string "Set to minute 45$"

LittlerootTown_Text_CanUsePCToStoreItems:
	.string "With the In-Game Time Suite, you can\n"
	.string "control in-game time however you like!\p"
	.string "What would you like to do?$"
```

## Credits
- Start Menu Clock by Citrus Bolt, edit by PCG

## Special thanks:
- Mako for originally cracking how fake RTC and RTC originally interacted, and how to divorce them.
- RavePossum and SBird for teaching me how to write the script commands, and when to switch to using macro callnatives for them instead.
