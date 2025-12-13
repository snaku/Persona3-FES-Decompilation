#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef unsigned char u8;
typedef signed char s8;

typedef unsigned short u16;
typedef signed short s16;

typedef unsigned long u32;
typedef signed long s32;

typedef unsigned long long u64;
typedef signed long long s64;

typedef float f32;
typedef double f64;

#define BATTLE_FLAG_CHARM    (1 << 0)  // 0x01
#define BATTLE_FLAG_DISTRESS (1 << 1)  // 0x02
#define BATTLE_FLAG_DIZZY    (1 << 2)  // 0x04
#define BATTLE_FLAG_FEAR     (1 << 3)  // 0x08
#define BATTLE_FLAG_RAGE     (1 << 4)  // 0x10
#define BATTLE_FLAG_FREEZE   (1 << 5)  // 0x20
#define BATTLE_FLAG_SHOCK    (1 << 6)  // 0x40
#define BATTLE_FLAG_POISON   (1 << 7)  // 0x80
#define BATTLE_FLAG_ORGIA    (1 << 8)  // 0x100
#define BATTLE_FLAG_OVERHEAT (1 << 9)  // 0x200
#define BATTLE_FLAG_DEAD     (1 << 19) // 0x80000
#define BATTLE_FLAG_DOWN     (1 << 20) // 0x100000

// 10 bytes
typedef struct
{
    u8 level;
    u16 health;
    u16 sp;
    int flags;   // See BATTLE_FLAG_*
    u8 aiTactic; // See enum AiTactic
} BattleStatus;

// 6 bytes
typedef struct
{
    u16 academicPoint;
    u16 charmPoint;
    u16 couragePoint;
} SocialStats;

// 6 bytes
typedef struct 
{
    u16 physicalCondition; // See enum CharacterPhysicalCondition
    u16 fatigueCounter;    // if 0, character will become tired
    u16 oldFatigueCounter; // value before entering tartarus
} PhysicalState;

// 15 bytes
typedef struct
{
    u16 sUnk1;
    u16 id;
    u16 sUnk2;
    BattleStatus battleStatus;
} CharacterHeader; 

// 5 bytes
typedef struct
{
    u8 strength;
    u8 magic;
    u8 endurance;
    u8 agility;
    u8 luck;
} PersonaStats;

// 36 bytes
typedef struct
{
    u16 sUnk1;
    u16 id;
    u8 level;
    u8 unkData[0x03];
    int nextExp;      // For characters other than HERO, their exp is linked to their persona
    u16 skills[8];
    PersonaStats stats;
} PersonaData; // For reference: Yukari = 008340ec

// 20 bytes (4 unk bytes are missing, will do it later)
typedef struct 
{
    u16 id;
    int type;
    u16 sUnk1;
    u16 firstStat;
    u16 secondStat;
    u16 sUnk2;
} EquipementData; 

// start: 0x0836224
typedef struct
{
    /*0x00*/ CharacterHeader character;
    /*0x10*/ u8 pad1[0x2B];
    /*0x3B*/ SocialStats socialStats;
    /*0x41*/ u32 nextExp;
    /*0x45*/ PhysicalState physicalState;
    /*0x4B*/ u16 activeSocialLink;
    /*0x4D*/ u8 socialLinkStat[0x1D];  // there is 22 social link but the array is 30 bytes
             u8 unkData[0x982];
             u16 equippedPersona;      // 0 to 12
             PersonaData personas[12]; // start: 00836ba8
    // TODO: The rest of the struct
} PlayerData;

// 868 bytes
typedef struct
{
    CharacterHeader character;
    SocialStats socialStats;
    u8 unkData1[0x06];
    PhysicalState physicalState;
    EquipementData equipements[4];
    u8 unkData2[0x4C];
    PersonaData persona;
    u8 unkData3[0x297]; // TODO
} CharacterData;

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
    CALENDAR_MONTH_DECEMBER
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

static const u16 numOfDaysInMonths[12] =
{  /*J   F   M   A   M   J   J   A   S   O   N   D*/
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

u32 Calendar_GetDaysSinceStart(u32 month, u32 day)
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
        if (m == CALENDAR_MONTH_DECEMBER + 1)
        {
            m = CALENDAR_MONTH_JANUARY;
        }
    }

    return dayAccumulator + day - 5; // - 5 because the game starts in april 5th
}

u32 Calendar_GetCurrentDay(u32 monthAndDay)
{
    return (monthAndDay + 7) % 7;
}

// FUN_0017e480
u32 Calendar_IsDateOutsideRange(u32 startMonth, u32 startDay, u32 endMonth, u32 endDay)
{
    u32 startDateIdx = Calendar_GetDaysSinceStart(startMonth, startDay);
    u32 endDateIdx = Calendar_GetDaysSinceStart(endMonth, endDay);
    u16 currentDate = 89;
    u8 a;

    // if current date is not at/after the start date
    // or current date is after end date
    if (currentDate < startDateIdx || endDateIdx < currentDate)
    {
        a = 0;
    }
    else 
    {
        a = 1;
    }

    return a;
}

// FUN_003004f0
void Character_AddBattleFlags_Impl(CharacterHeader* characterHeader, u32 flags)
{
    const u32 LOW_20_BITS = 0x000FFFFF;
    const u32 HIGH_12_BITS = 0xFFF00000;

    if ((flags & LOW_20_BITS) != 0)
    {
        characterHeader->battleStatus.flags = (characterHeader->battleStatus.flags & HIGH_12_BITS) | (flags & LOW_20_BITS);
    }

    characterHeader->battleStatus.flags |= (flags & HIGH_12_BITS);
}

PlayerData gPlayerData;

int main()
{
    u32 value = 0;
    value |= (1 << 1);
    value |= (1 << 2);
    value |= (1 << 3);
    value |= (1 << 4); // elizabeth requests
    value |= (1 << 5); // ?
    value |= (1 << 6); // compendium
    value |= (1 << 9);
    value |= (1 << 10);
    value |= (1 << 12);
    value |= (1 << 13);
    value |= (1 << 14);
    value |= (1 << 19);
    value |= (1 << 26);
    value |= (1 << 27);
    value |= (1 << 28);
    value |= (1 << 29);
    value |= (1 << 30);

    u8 b0 = value & 0xFF;
    u8 b1 = (value >> 8) & 0xFF;
    u8 b2 = (value >> 16) & 0xFF;
    u8 b3 = (value >> 24) & 0xFF;

    printf("value: %02x %02x %02x %02x", b0, b1, b2, b3);

    /*u32 test1 = Calendar_GetDaysSinceStart(CALENDAR_MONTH_JANUARY, 3);
    u32 test2 = Calendar_GetDaysSinceStart(CALENDAR_MONTH_APRIL, 6);

    printf("Date 1: %d\n", test1);
    printf("Date 2: %d\n", test2);

    u8 a = Calendar_IsDateOutsideRange(CALENDAR_MONTH_JUNE, 2, CALENDAR_MONTH_JULY, 2);
    //u32 b = Calendar_GetCurrentDay(50);

    printf("a = %d", a);*/

    return 0;
}