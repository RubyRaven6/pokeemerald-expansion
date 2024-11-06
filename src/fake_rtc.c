#include "global.h"
#include "string_util.h"
#include "strings.h"
#include "text.h"
#include "rtc.h"
#include "fake_rtc.h"
#include "event_data.h"

struct Time *FakeRtc_GetCurrentTime(void)
{
#if OW_USE_FAKE_RTC
    return &gSaveBlock3Ptr->fakeRTC;
#else
    return NULL;
#endif
}

void FakeRtc_GetRawInfo(struct SiiRtcInfo *rtc)
{
    struct Time *time = FakeRtc_GetCurrentTime();
    rtc->second = time->seconds;
    rtc->minute = time->minutes;
    rtc->hour = time->hours;
    rtc->day = time->days;
    rtc->month = time->months;
    rtc->year = time->years;
    rtc->dayOfWeek = time->dayOfWeek;
}

void FakeRtc_TickTimeForward(void)
{
    if (!OW_USE_FAKE_RTC)
        return;

    if (FlagGet(OW_FLAG_PAUSE_TIME))
        return;

    FakeRtc_AdvanceTimeBy(0, 0, 0, 0, 0, FakeRtc_GetSecondsRatio());

}

void FakeRtc_ResetDayCount(void)
{
    struct Time* time = FakeRtc_GetCurrentTime();
    time->days = 1;
    //RtcSetDayOfWeek(DAY_MONDAY);
}

void FakeRtc_AdvanceTimeBy(u32 years, u32 months, u32 days, u32 hours, u32 minutes, u32 seconds)
{
    struct Time* time = FakeRtc_GetCurrentTime();
    if (time->seconds < 0)
    {
        time->seconds += SECONDS_PER_MINUTE;
        --time->minutes;
    }

    if (time->minutes < 0)
    {
        time->minutes += MINUTES_PER_HOUR;
        --time->hours;
    }

    if (time->hours < 0)
    {
        time->hours += HOURS_PER_DAY;
        --time->days;
        --time->dayOfWeek;
    }

    if (time->dayOfWeek < 0)
    {
        time->dayOfWeek += DAYS_PER_WEEK;
    }

    if(time->days < 1)
    {
        time->days += DAYS_PER_MONTH;
        --time->months;
    }

    if (time->months < 1)
    {
        time->months += MONTHS_PER_YEAR;
        --time->years;
    }

    u32 dayOfWeek = time->dayOfWeek + days;
    seconds += time->seconds;
    minutes += time->minutes;
    hours += time->hours;
    days += time->days;
    months += time->months;
    years += time->years;

    while(seconds >= SECONDS_PER_MINUTE)
    {
        minutes++;
        seconds -= SECONDS_PER_MINUTE;
    }

    while(minutes >= MINUTES_PER_HOUR)
    {
        hours++;
        minutes -= MINUTES_PER_HOUR;
    }

    while(hours >= HOURS_PER_DAY)
    {
        days++;
        dayOfWeek++;
        hours -= HOURS_PER_DAY;
    }

    while(dayOfWeek >= DAYS_PER_WEEK)
    {
        dayOfWeek -= DAYS_PER_WEEK;
    }

    while(days > DAYS_PER_MONTH)
    {
        months++;
        days -= DAYS_PER_MONTH;
    }

    while(months > MONTHS_PER_YEAR)
    {
        years++;
        months -= MONTHS_PER_YEAR;
    }

    time->seconds = seconds;
    time->minutes = minutes;
    time->hours = hours;
    time->days = days;
    time->months = months;
    time->years = years;
    time->dayOfWeek = dayOfWeek;
}


void FakeRtc_ManuallySetTime(u32 year, u32 month, u32 day, u32 hour, u32 minute, u32 second)
{

    memset(FakeRtc_GetCurrentTime(), 0, sizeof(struct Time));
    struct Time* setTime = FakeRtc_GetCurrentTime();
    u8 weekday = ((day - 1) % 7);

    FlagToggle(OW_FLAG_PAUSE_TIME);
    MgbaPrintf(MGBA_LOG_DEBUG, "Seconds: %u", setTime->seconds);
    MgbaPrintf(MGBA_LOG_DEBUG, "Minutes: %u", setTime->minutes);
    MgbaPrintf(MGBA_LOG_DEBUG, "Hours: %u", setTime->hours);
    MgbaPrintf(MGBA_LOG_DEBUG, "Days: %u", setTime->days);
    MgbaPrintf(MGBA_LOG_DEBUG, "Day of week: %u", setTime->dayOfWeek);
    MgbaPrintf(MGBA_LOG_DEBUG, "Months: %u", setTime->months);
    MgbaPrintf(MGBA_LOG_DEBUG, "Years: %u", setTime->years);

    setTime->years = year;
    setTime->months = month;
    setTime->days = day; 
    setTime->hours = hour;
    setTime->minutes = minute;
    setTime->seconds = second;
    setTime->dayOfWeek = weekday;

    MgbaPrintf(MGBA_LOG_DEBUG, "Seconds after: %u", setTime->seconds);
    MgbaPrintf(MGBA_LOG_DEBUG, "Minutes after: %u", setTime->minutes);
    MgbaPrintf(MGBA_LOG_DEBUG, "Hours after: %u", setTime->hours);
    MgbaPrintf(MGBA_LOG_DEBUG, "Days after: %u", setTime->days);
    MgbaPrintf(MGBA_LOG_DEBUG, "Day of week: %u", setTime->dayOfWeek);
    MgbaPrintf(MGBA_LOG_DEBUG, "Months after: %u", setTime->months);
    MgbaPrintf(MGBA_LOG_DEBUG, "Years after: %u", setTime->years);
    FlagToggle(OW_FLAG_PAUSE_TIME);
}




// Edit RTC_CUSTOM to edit the custom ratio
u32 FakeRtc_GetSecondsRatio(void)
{
    return (OW_ALTERED_TIME_RATIO == GEN_8_PLA)   ? 60 :
           (OW_ALTERED_TIME_RATIO == GEN_9)       ? 20 :
           (OW_ALTERED_TIME_RATIO == RTC_CUSTOM)  ? 1 :
                                                    1;
}

STATIC_ASSERT((OW_FLAG_PAUSE_TIME == 0 || OW_USE_FAKE_RTC == TRUE), FakeRtcMustBeTrueToPauseTime);

void Script_PauseFakeRtc(void)
{
    FlagSet(OW_FLAG_PAUSE_TIME);
}

void Script_ResumeFakeRtc(void)
{
    FlagClear(OW_FLAG_PAUSE_TIME);
}

void Script_ToggleFakeRtc(void)
{
    FlagToggle(OW_FLAG_PAUSE_TIME);
}