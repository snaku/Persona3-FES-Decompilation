#ifndef DATCALENDAR_H
#define DATCALENDAR_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;

typedef enum
{
    CALENDAR_TIME_NULL,
    CALENDAR_TIME_EARLY_MORNING,
    CALENDAR_TIME_MORNING,
    CALENDAR_TIME_LUNCH,
    CALENDAR_TIME_AFTERNOON,
    CALENDAR_TIME_AFTER_SCHOOL,
    CALENDAR_TIME_EVENING,
    CALENDAR_TIME_LATE_NIGHT,
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

typedef enum
{
    MOON_PHASE_WAXING_CRESCENT_1,
    MOON_PHASE_WAXING_CRESCENT_2,
    MOON_PHASE_WAXING_CRESCENT_3,
    MOON_PHASE_WAXING_CRESCENT_4,
    MOON_PHASE_WAXING_CRESCENT_5,
    MOON_PHASE_WAXING_CRESCENT_6,
    MOON_PHASE_FIRST_QUARTER,
    MOON_PHASE_WAXING_GIBBOUS_1,
    MOON_PHASE_WAXING_GIBBOUS_2,
    MOON_PHASE_WAXING_GIBBOUS_3,
    MOON_PHASE_WAXING_GIBBOUS_4,
    MOON_PHASE_WAXING_GIBBOUS_5,
    MOON_PHASE_WAXING_GIBBOUS_6,
    MOON_PHASE_WAXING_GIBBOUS_7,
    MOON_PHASE_FULL_MOON,
    MOON_PHASE_WANING_GIBBOUS_1,
    MOON_PHASE_WANING_GIBBOUS_2,
    MOON_PHASE_WANING_GIBBOUS_3,
    MOON_PHASE_WANING_GIBBOUS_4,
    MOON_PHASE_WANING_GIBBOUS_5,
    MOON_PHASE_WANING_GIBBOUS_6,
    MOON_PHASE_WANING_GIBBOUS_7,
    MOON_PHASE_LAST_QUARTER,
    MOON_PHASE_WANING_CRESCENT_1,
    MOON_PHASE_WANING_CRESCENT_2,
    MOON_PHASE_WANING_CRESCENT_3,
    MOON_PHASE_WANING_CRESCENT_4,
    MOON_PHASE_WANING_CRESCENT_5,
    MOON_PHASE_WANING_CRESCENT_6,
    MOON_PHASE_NEW_MOON
} MoonPhases;

typedef struct CalendarWork
{
    u16 daysSinceApr5;  // days since start of the game
    u8 time;
    u32 skipToTarget;   // 0 no skip, 1 skip
    u16 daysSkipTarget; // in days since april 5th (for example: daysSkipTarget = 40 -> will skip to may 15th)
    u8 timeSkipTarget;  // see enum 'CalendarTime'
} CalendarWork;

// TODO
typedef enum
{
    CALENDAR_TASK_STATE_INIT_DEBUG,   // Create a blue rectangle for the bg and a red cursor
    CALENDAR_TASK_STATE_UPDATE_DEBUG, 
} CalendarTaskState;

// 44 bytes
typedef struct CalendarTaskWork
{
    u32 state;        // 0x00. See enum 'CalendarTaskState'
    u8 unkData[0x28];
} CalendarTaskWork;

extern const u16 numOfDaysInMonths[12];

u32 clndGetMonthFromDaysSinceApr5(u16 daysSinceApr5);
u32 clndGetDaysSinceStartFromDate(u32 month, u32 day);
u32 clndGetCurrentMonth();
u32 clndGetDayOfMonthFromDaysSinceApr5(u16 daysSinceApr5);
u32 clndGetCurrentDay();
u32 clndGetWeekDay(u32 daysSinceApr5);
u32 clndGetCurrentWeekDay();
u8 clndIsHolidayOrSunday();
u8 clndIsDateInRange(u32 startMonth, u32 startDay, u32 endMonth, u32 endDay);
u8 clndIsDateInRangeFromDate(u32 monthToTest, u32 dayToTest, u32 startMonth, u32 startDay, u32 endMonth, u32 endDay);
u8 clndIsDateInRangeFromStart(u32 month, u32 day, u32 range);
KwlnTask* clndCreateTask();
u8 clndGetCurrentMoonPhase();
u8 clndGetMoonPhase(u32 daysSinceApr5);

u8 clndScrCmd_SET_DATE();

#endif