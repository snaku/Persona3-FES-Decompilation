#include "g_data.h"

typedef struct
{
    s16 month;
    s16 day;
} Holiday;

// 005e3a40
static Holiday holidays[] = 
{
    {CALENDAR_MONTH_APRIL, 29}, {CALENDAR_MONTH_MAY, 2}, {CALENDAR_MONTH_MAY, 5},
    {CALENDAR_MONTH_JULY, 20}, {CALENDAR_MONTH_JULY, 21}, {CALENDAR_MONTH_JULY, 22},
    {CALENDAR_MONTH_JULY, 23}, {CALENDAR_MONTH_JULY, 26}, {CALENDAR_MONTH_JULY, 27},
    {CALENDAR_MONTH_JULY, 28}, {CALENDAR_MONTH_JULY, 29}, {CALENDAR_MONTH_JULY, 30},
    {CALENDAR_MONTH_JULY, 31}, {CALENDAR_MONTH_AUGUST, 1}, {CALENDAR_MONTH_AUGUST, 2},
    {CALENDAR_MONTH_AUGUST, 3}, {CALENDAR_MONTH_AUGUST, 4}, {CALENDAR_MONTH_AUGUST, 5},
    {CALENDAR_MONTH_AUGUST, 6}, {CALENDAR_MONTH_AUGUST, 7}, {CALENDAR_MONTH_AUGUST, 8},
    {CALENDAR_MONTH_AUGUST, 9}, {CALENDAR_MONTH_AUGUST, 10}, {CALENDAR_MONTH_AUGUST, 11},
    {CALENDAR_MONTH_AUGUST, 12}, {CALENDAR_MONTH_AUGUST, 13}, {CALENDAR_MONTH_AUGUST, 14} ,
    {CALENDAR_MONTH_AUGUST, 15}, {CALENDAR_MONTH_AUGUST, 16}, {CALENDAR_MONTH_AUGUST, 17},
    {CALENDAR_MONTH_AUGUST, 18}, {CALENDAR_MONTH_AUGUST, 19}, {CALENDAR_MONTH_AUGUST, 20},
    {CALENDAR_MONTH_AUGUST, 21}, {CALENDAR_MONTH_AUGUST, 23}, {CALENDAR_MONTH_AUGUST, 24},
    {CALENDAR_MONTH_AUGUST, 25}, {CALENDAR_MONTH_AUGUST, 26}, {CALENDAR_MONTH_AUGUST, 27},
    {CALENDAR_MONTH_AUGUST, 28}, {CALENDAR_MONTH_AUGUST, 29}, {CALENDAR_MONTH_AUGUST, 30},
    {CALENDAR_MONTH_AUGUST, 31}, {CALENDAR_MONTH_SEPTEMBER, 21}, {CALENDAR_MONTH_SEPTEMBER, 22},
    {CALENDAR_MONTH_SEPTEMBER, 23}, {CALENDAR_MONTH_OCTOBER, 12}, {CALENDAR_MONTH_NOVEMBER, 3},
    {CALENDAR_MONTH_NOVEMBER, 17}, {CALENDAR_MONTH_NOVEMBER, 18}, {CALENDAR_MONTH_NOVEMBER, 19},
    {CALENDAR_MONTH_NOVEMBER, 20}, {CALENDAR_MONTH_NOVEMBER, 23}, {CALENDAR_MONTH_DECEMBER, 23},
    {CALENDAR_MONTH_DECEMBER, 27}, {CALENDAR_MONTH_DECEMBER, 28}, {CALENDAR_MONTH_DECEMBER, 29},
    {CALENDAR_MONTH_DECEMBER, 30}, {CALENDAR_MONTH_DECEMBER, 31}, {CALENDAR_MONTH_JANUARY, 1},
    {CALENDAR_MONTH_JANUARY, 2}, {CALENDAR_MONTH_JANUARY, 3}, {CALENDAR_MONTH_JANUARY, 4},
    {CALENDAR_MONTH_JANUARY, 5}, {CALENDAR_MONTH_JANUARY, 6}, {CALENDAR_MONTH_JANUARY, 7},
    {CALENDAR_MONTH_JANUARY, 10}, {CALENDAR_MONTH_JANUARY, 11}, {CALENDAR_MONTH_FEBRUARY, 11},
    {CALENDAR_MONTH_MARCH, 22}, {0xFFFF, 0XFFFF},
};

const u16 numOfDaysInMonths[12] =
{ /*JAN FEB MAR APR MAY JUN JUL AUG SEP OCT NOV DEC*/
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

// 005e38d0. Moon phases for every day (april 5th 2009 to march 31st 2010)
static const u8 daysMoonPhases[] =
{
    // Cycle 1: april 5th 2009 to april 25th 2009
    MOON_PHASE_WAXING_GIBBOUS_4, MOON_PHASE_WAXING_GIBBOUS_5, MOON_PHASE_WAXING_GIBBOUS_6,
    MOON_PHASE_WAXING_GIBBOUS_7, MOON_PHASE_FULL_MOON, MOON_PHASE_WANING_GIBBOUS_1,
    MOON_PHASE_WANING_GIBBOUS_1, MOON_PHASE_WANING_GIBBOUS_2, MOON_PHASE_WANING_GIBBOUS_3,
    MOON_PHASE_WANING_GIBBOUS_4, MOON_PHASE_WANING_GIBBOUS_5, MOON_PHASE_WANING_GIBBOUS_6,
    MOON_PHASE_WANING_GIBBOUS_7, MOON_PHASE_LAST_QUARTER, MOON_PHASE_WANING_CRESCENT_1, 
    MOON_PHASE_WANING_CRESCENT_2, MOON_PHASE_WANING_CRESCENT_3, MOON_PHASE_WANING_CRESCENT_4, 
    MOON_PHASE_WANING_CRESCENT_5, MOON_PHASE_WANING_CRESCENT_6, MOON_PHASE_NEW_MOON,
    
    // Cycle 2: april 26th 2009 to may 24th 2009
    MOON_PHASE_WAXING_CRESCENT_1, MOON_PHASE_WAXING_CRESCENT_2, MOON_PHASE_WAXING_CRESCENT_3,
    MOON_PHASE_WAXING_CRESCENT_4, MOON_PHASE_WAXING_CRESCENT_5, MOON_PHASE_WAXING_CRESCENT_6,
    MOON_PHASE_FIRST_QUARTER, MOON_PHASE_WAXING_GIBBOUS_1, MOON_PHASE_WAXING_GIBBOUS_2, 
    MOON_PHASE_WAXING_GIBBOUS_3, MOON_PHASE_WAXING_GIBBOUS_4, MOON_PHASE_WAXING_GIBBOUS_5,
    MOON_PHASE_WAXING_GIBBOUS_6, MOON_PHASE_FULL_MOON, MOON_PHASE_WANING_GIBBOUS_1,
    MOON_PHASE_WANING_GIBBOUS_2, MOON_PHASE_WANING_GIBBOUS_3, MOON_PHASE_WANING_GIBBOUS_4,
    MOON_PHASE_WANING_GIBBOUS_5, MOON_PHASE_WANING_GIBBOUS_6, MOON_PHASE_WANING_GIBBOUS_7,
    MOON_PHASE_LAST_QUARTER, MOON_PHASE_WANING_CRESCENT_1, MOON_PHASE_WANING_CRESCENT_2,
    MOON_PHASE_WANING_CRESCENT_3, MOON_PHASE_WANING_CRESCENT_4, MOON_PHASE_WANING_CRESCENT_5,
    MOON_PHASE_WANING_CRESCENT_6, MOON_PHASE_NEW_MOON

    // TODO: Other cycles
};

// FUN_0017d830
u32 Calendar_GetMonthFromDaysSinceApr5(u16 daysSinceApr5)
{
    u16 month = CALENDAR_MONTH_APRIL;

    daysSinceApr5 += 4;

    while (numOfDaysInMonths[month] <= daysSinceApr5)
    {
        daysSinceApr5 -= numOfDaysInMonths[month];
        month++;

        if (month >= CALENDAR_MONTH_DECEMBER)
        {
            month = CALENDAR_MONTH_JANUARY;
        }
    }

    return month;
}

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

// FUN_0017d920
u32 Calendar_GetCurrentMonth()
{
    u16 daysSinceApr5 = Calendar_GetDaysSinceApr5() + 4;
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

    return month;
}

// FUN_0017d9c0
u32 Calendar_GetDayOfMonthFromDaysSinceApr5(u16 daysSinceApr5)
{
    u16 month = CALENDAR_MONTH_APRIL;
    
    daysSinceApr5 += 4;

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
    u16 daysSinceApr5 = Calendar_GetDaysSinceApr5() + 4;
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

// FUN_0017dcf0
u8 Calendar_IsHolidayOrSunday()
{
    u16 daysSinceApr5 = Calendar_GetDaysSinceApr5();
    u32 currDayOfMonth;
    u32 currMonth;

    if (Calendar_GetWeekDay(daysSinceApr5) == CALENDAR_DAY_SUNDAY)
    {
        return true;
    }

    currMonth = Calendar_GetMonthFromDaysSinceApr5(daysSinceApr5);
    currDayOfMonth = Calendar_GetDayOfMonthFromDaysSinceApr5(daysSinceApr5);

    for (u16 i = 0; i < 0x164; i++)
    {
        if (holidays[i].month == -1) break;
        if (currMonth == holidays[i].month && currDayOfMonth == holidays[i].day)
        {
            return true;
        }
    }

    return false;
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