#ifndef DATCALENDAR_H
#define DATCALENDAR_H

#include "Utils.h"

typedef enum
{
    CALENDAR_TIME_LATE_NIGHT1,
    CALENDAR_TIME_EARLY_MORNING,
    CALENDAR_TIME_MORNING,
    CALENDAR_TIME_LUNCH,
    CALENDAR_TIME_AFTERNOON,
    CALENDAR_TIME_AFTER_SCHOOL,
    CALENDAR_TIME_EVENING,
    CALENDAR_TIME_LATE_NIGHT2,
    CALENDAR_TIME_DARK_HOUR
} CalendarTime;

typedef enum
{
    CALENDAR_MONTH_JANUARY = 1,
    CALENDAR_MONTH_FEBRUARY,
    CALENDAR_MONTH_MARCH,
    CALENDAR_MONTH_APRIL,
    CALENDAR_MONTH_MAY,
    CALENDAR_MONTH_JUNE,
    CALENDAR_MONTH_JULY,
    CALENDAR_MONTH_AUGUST,
    CALENDAR_MONTH_SEPTEMBER,
    CALENDAR_MONTH_OCTOBER,
    CALENDAR_MONTH_NOVEMBER,
    CALENDAR_MONTH_DECEMBER,
    CALENDAR_MONTH_MAX
} CalendarMonths;

typedef enum
{
    CALENDAR_DAY_SUNDAY,
    CALENDAR_DAY_MONDAY,
    CALENDAR_DAY_TUESDAY,
    CALENDAR_DAY_WEDNESDAY,
    CALENDAR_DAY_THURSDAY,
    CALENDAR_DAY_FRIDAY,
    CALENDAR_DAY_SATURDAY,
    CALENDAR_DAY_MAX
} CalendarDays;

typedef struct
{
    u16 daysSinceApr5; // 0083679c
    u8 time;
    // TODO: unk data after time
} CalendarData;

extern const u16 numOfDaysInMonths[12];

u32 Calendar_GetDaysSinceStartFromDate(u32 month, u32 day);
u32 Calendar_GetCurrentDay();
u32 Calendar_GetWeekDay(u32 daysSinceApr5);
u32 Calendar_GetCurrentWeekDay();
u8 Calendar_IsDateInRange(u32 startMonth, u32 startDay, u32 endMonth, u32 endDay);
u8 Calendar_IsDateInRangeFromDate(u32 monthToTest, u32 dayToTest, u32 startMonth, u32 startDay, u32 endMonth, u32 endDay);
u8 Calendar_IsDateInRangeFromStart(u32 month, u32 day, u32 range);

#endif