#include "comuData.h"
#include "g_data.h"

#include <stdlib.h>

static const u8* daysStrings[CALENDAR_DAY_MAX] =
{
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};

// 006a3ca0 (ultimate social link personas)
static const u8* ultSLPersonasStrings[22] = 
{
    "Susano-o", "Surt", "Scathach",
    "Alilat", "Odin", "Kohryu",
    "Cybele", "Thor", "Melchizedek",
    "Arahabaki", "Norn", "Siegfried",
    "Attis", "Thanatos", "Yurlungur",
    "Beelzebub", "Chi You", "Helel",
    "Sandalaphon", "Asura", "Messiah",
    "Metatron"
};

// 006a3b40 (Will see were those strings are used in game later)
static const u8* unkStrings1[5] = 
{
    "A perfect gift to capture a woman's heart!",
    "This'll make you much stronger!",
    "Provides excellent protection!",
    "Functional and fashionable!",
    "Guaranteed to make your friends jealous!"
};

// FUN_003c4130
u8* Day_GetCurrentDayString(u32 month, u32 day)
{
    u8* dayString;
    u32 currentDay;

    currentDay = Calendar_GetDaysSinceStartFromDate(month, day);
    currentDay = Calendar_GetWeekDay(currentDay);

    switch(currentDay)
    {
        case CALENDAR_DAY_SUNDAY:
            dayString = daysStrings[CALENDAR_DAY_SUNDAY];
            break;
        case CALENDAR_DAY_MONDAY:
            dayString = daysStrings[CALENDAR_DAY_MONDAY];
            break;
        case CALENDAR_DAY_TUESDAY:
            dayString = daysStrings[CALENDAR_DAY_TUESDAY];
            break;
        case CALENDAR_DAY_WEDNESDAY:
            dayString = daysStrings[CALENDAR_DAY_WEDNESDAY];
            break;
        case CALENDAR_DAY_THURSDAY:
            dayString = daysStrings[CALENDAR_DAY_THURSDAY];
            break;
        case CALENDAR_DAY_FRIDAY:
            dayString = daysStrings[CALENDAR_DAY_FRIDAY];
            break;
        case CALENDAR_DAY_SATURDAY:
            dayString = daysStrings[CALENDAR_DAY_SATURDAY];
            break;
        default:
            P3FES_ASSERT("comuData.c", 136);
            dayString = NULL;
    }

    return dayString;
}

// FUN_003c4210
u8* ComuData_FUN_003c4210(u32 idx)
{
    if (idx > ARRAY_SIZE(unkStrings1))
    {
        P3FES_ASSERT("comuData.c", 147);
    }

    return unkStrings1[idx];
}

u8* ComuData_GetUltSLPersonasString(u32 idx)
{
    idx--;
    if (idx < 0 || idx > ARRAY_SIZE(ultSLPersonasStrings) - 1)
    {
        P3FES_ASSERT("comuData.c", 198);
    }

    return ultSLPersonasStrings[idx];
}