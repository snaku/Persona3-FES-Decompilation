#include "g_data.h"

const u16 numOfDaysInMonths[12] =
{ /*JAN FEB MAR APR MAY JUN JUL AUG SEP OCT NOV DEC*/
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

// FUN_0017d8b0
u32 Calendar_GetDaysSinceStartFromDate(u32 month, u32 day)
{
    u32 m = CALENDAR_MONTH_APRIL;
    u32 dayAccumulator = 0;

    while (month != CALENDAR_MONTH_APRIL)
    {
        dayAccumulator += numOfDaysInMonths[m - 1];
        m++;
        month--;

        if (month == 0)
        {
            month = CALENDAR_MONTH_DECEMBER;
        }
        if (m > CALENDAR_MONTH_DECEMBER)
        {
            m = CALENDAR_MONTH_JANUARY;
        }
    }

    return dayAccumulator + day - 5; // - 5 because the game starts in april 5th
}

// FUN_0017d9c0
u32 Calendar_GetDayOfMonthFromDaysSinceApr5(u16 daysSinceApr5)
{
    u16 month = CALENDAR_MONTH_APRIL;

    while (numOfDaysInMonths[month] <= daysSinceApr5)
    {
        daysSinceApr5 -= numOfDaysInMonths[month];
        month++;

        if (month >= CALENDAR_MONTH_MAX)
        {
            month = CALENDAR_MONTH_JANUARY;
        }
    }

    return daysSinceApr5 + 1;
}

// FUN_0017da40. Return the current day of the month
u32 Calendar_GetCurrentDay()
{
    u16 daysSinceApr5 = Calendar_GetDaysSinceApr5();
    u16 month = CALENDAR_MONTH_APRIL;

    while (numOfDaysInMonths[month] <= daysSinceApr5)
    {
        daysSinceApr5 -= numOfDaysInMonths[month];
        month++;

        if (month >= CALENDAR_MONTH_MAX)
        {
            month = CALENDAR_MONTH_JANUARY;
        }
    }

    return daysSinceApr5 + 1;
}

// FUN_0017dae0
u32 Calendar_GetWeekDay(u32 daysSinceApr5)
{
    return (daysSinceApr5 + CALENDAR_DAY_MAX) % CALENDAR_DAY_MAX;
}

// FUN_0017db00
u32 Calendar_GetCurrentWeekDay()
{
    u16 daysSinceApr5 = Calendar_GetDaysSinceApr5();

    return Calendar_GetWeekDay(daysSinceApr5); // was inlined
}

// FUN_0017e480
u8 Calendar_IsDateInRange(u32 startMonth, u32 startDay, u32 endMonth, u32 endDay)
{
    u32 startDate = Calendar_GetDaysSinceStartFromDate(startMonth, startDay);
    u32 endDate = Calendar_GetDaysSinceStartFromDate(endMonth, endDay);
    u16 currDaysSinceApr5 = Calendar_GetDaysSinceApr5();

    if (currDaysSinceApr5 < startDate || endDate < currDaysSinceApr5)
    {
        return false;
    }

    return true;
}

// FUN_0017e520
u8 Calendar_IsDateInRangeFromDate(u32 monthToTest, u32 dayToTest,
                                  u32 startMonth, u32 startDay,
                                  u32 endMonth, u32 endDay)
{
    u32 startDate = Calendar_GetDaysSinceStartFromDate(startMonth, startDay);
    u32 endDate = Calendar_GetDaysSinceStartFromDate(endMonth, endDay);
    u32 testDate = Calendar_GetDaysSinceStartFromDate(monthToTest, dayToTest);

    if (testDate < startDate || endDate < testDate)
    {
        return false;
    }

    return true;
}

// FUN_0017e5d0
u8 Calendar_IsDateInRangeFromStart(u32 month, u32 day, u32 range)
{
    u32 startDate;
    u32 endDate;
    u16 daysSinceApr5;

    if (range == 0)
    {
        P3FES_LOG1("Calender chk range is 0");
        return false;
    }

    startDate = Calendar_GetDaysSinceStartFromDate(month, day);
    endDate = startDate + range - 1;
    daysSinceApr5 = Calendar_GetDaysSinceApr5();

    if (daysSinceApr5 < startDate || endDate < daysSinceApr5)
    {
        return false;
    }

    return true;
}