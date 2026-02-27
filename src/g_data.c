#include "datPersona.h"
#include "g_data.h"
#include "g_flags.h"
#include "datCalc.h"
#include "temporary.h"

// 005dc050
static const u32 sPlayerExpThreshold[MAX_CHARACTER_LEVEL] = 
{
    0, 20, 47, 99, 185, 312, 490, 726, 1030,
    1410, 1873, 2429, 3085, 3851, 4735, 5744, 6888, 8174,
    9612, 11210, 12975, 14917, 17043, 19363, 21885, 24616, 27566,
    30742, 34154, 37810, 41717, 45885, 50321, 55035, 60035, 65328,
    70924, 76830, 83056, 89610, 96499, 103733, 111319, 119267, 127585,
    136280, 145362, 154838, // ! 005dc110 !
};

static const u16 academicLevelThreshold[6] = { 0, 20, 80, 140, 200, 260 }; // 005e3068
static const u16 charmLevelThreshold[6] =    { 0, 15, 30, 45, 65, 80 };    // 005e3078
static const u16 courageLevelThreshold[6] =  { 0, 15, 30, 45, 65, 80 };    // 005e3088

// 005e4150
static const char* physicalConditionsString[13] = 
{
    "You recovered from your cold.",
    "Your cold is not gone yet...",
    "Your cold worsened because you're tired.",
    "You've caught a cold.",
    "You've become tired.",
    "You're not tired anymore.",
    "Your condition improved because you rested.",
    "Your condition has improved.",
    "You are no longer in great condition.",
    "You're still tired",
    "You're no longer sick because you rested.",
    "You're no longer tired because you rested.",
    "The medicine cured your illness."
};

static u32 sScenarioMode; // 007cdfa4. See enum 'ScenarioMode'

CharacterData gCharacters[CHARACTER_MAX - 1];

static UnitData sPlayerUnit;                 // 00836224
static PlayerStatusData sPlayerStatusData;   // 00836260
static PlayerEquipmentData sPlayerEquipData; // 0083678c
static CalendarData sCalendarData;           // 0083679c
PlayerPersonaData gPlayerPersonaData;        // 00836ba8
static PersonaData sCompendium[256];         // 00836e1c

static u32 gGlobalFlags[176]; // 0083a21c. See 'g_flags.h' !!!
static u32 gIUnkArr[128];     // 0083a4dc


void FUN_00172890();
void FUN_00172e10();

// TODO
void FUN_0016f3e0(u32 idx, u32 value)
{
    if (idx > 127)
    {
        P3FES_ASSERT("g_data.c", 2007);
    }

    gIUnkArr[idx] = value;
}

// FUN_0016c860
u16 Persona_GetPersonaId(u16 characterId)
{
    if (IS_HERO(characterId))
    {
        if (gPlayerPersonaData.equippedPersona < ARRAY_SIZE(gPlayerPersonaData.personas))
        {
            return gPlayerPersonaData.personas[gPlayerPersonaData.equippedPersona].id;
        }

        P3FES_ASSERT("g_data.c", 633);
    }

    return gCharacters[characterId].persona.id;
}

// FUN_0016cd60
UnitData* Character_GetUnit(u16 characterId)
{
    if (IS_HERO(characterId))
    {
        return &sPlayerUnit;
    }

    if (characterId >= CHARACTER_MAX)
    {
        return &gCharacters[characterId].unit;
    }

    P3FES_ASSERT("g_data.c", 737);
}

// FUN_0016cdf0
void Character_InitUnitData(u16 characterId)
{
    if (IS_HERO(characterId))
    {
        memset(&sPlayerUnit, 0, sizeof(UnitData));

        sPlayerUnit.status.aiTactic = AI_TACTIC_ACT_FREELY;
        sPlayerUnit.id = CHARACTER_HERO;
        sPlayerUnit.flags = UNIT_FLAG_ACTIVE;

        return;
    }

    memset(&gCharacters[characterId], 0, sizeof(UnitData));

    gCharacters[characterId].unit.id = characterId;
    gCharacters[characterId].unit.status.aiTactic = AI_TACTIC_ACT_FREELY;
    gCharacters[characterId].unit.flags = UNIT_FLAG_ACTIVE;
}

// FUN_0016c470
u8 Character_GetLevel(u16 characterId)
{
    if (IS_HERO(characterId))
    {
        return Unit_GetLevel(&sPlayerUnit);
    }

    return Unit_GetLevel(&gCharacters[characterId].unit);
}

// FUN_0016c970
u32 Character_GetBattleFlagsNoDown(u16 characterId)
{
    if (IS_HERO(characterId))
    {
        return Unit_GetBattleFlagsNoDown(&sPlayerUnit);
    }

    return Unit_GetBattleFlagsNoDown(&gCharacters[characterId].unit);
}

// FUN_0016d8b0
void Character_AddBattleFlags(u16 characterId, u32 flags)
{
    if (IS_HERO(characterId))
    {
        Unit_AddBattleFlags(&sPlayerUnit, flags);
        return;
    }

    Unit_AddBattleFlags(&gCharacters[characterId].unit, flags);
}

// FUN_0016d980
void Character_SetOldFatigueCounter(u16 characterId, u16 oldFatigueCounter)
{
    if (IS_HERO(characterId))
    {
        sPlayerStatusData.physicalState.oldFatigueCounter = oldFatigueCounter;
        return;
    }

    gCharacters[characterId].physicalState.oldFatigueCounter = oldFatigueCounter;
}

// FUN_0016d9d0
void Character_RemoveBattleFlags(u16 characterId, u32 flags)
{
    if (IS_HERO(characterId))
    {
        Unit_RemoveBattleFlags(&sPlayerUnit, flags);
    }

    Unit_RemoveBattleFlags(&gCharacters[characterId].unit, flags);
}

// FUN_0016d2f0
u32 Character_GetExpUntilNextLevel(u16 characterId)
{
    u32 nextExpTmp;
    u32 nextExp = sPlayerStatusData.nextExp;
    PersonaData* persona;
    u8 i;

    if (!IS_HERO(characterId))
    {
        persona = Persona_GetPersonaByCharacterId(characterId);
        if (persona == NULL)
        {
            P3FES_ASSERT("g_data.c", 622);
        }

        nextExp = Persona_GetPersonaNextExp(persona);
    }

    for (i = 0; i < ARRAY_SIZE(sPlayerExpThreshold); i++)
    {
        if (nextExp < sPlayerExpThreshold[i]) break;
    }

    if (i == MAX_CHARACTER_LEVEL)
    {
        nextExp = 0;
    }

    if (i == 0 || i > MAX_CHARACTER_LEVEL)
    {
        P3FES_ASSERT("g_data.c", 876);
    }

    nextExp = sPlayerExpThreshold[i];
    nextExpTmp = sPlayerStatusData.nextExp;

    nextExp -= nextExpTmp;

    return nextExp;
}

// FUN_0016d560
u8 Character_DidCharacterLevelUp(u16 characterId, u32 expGain)
{
    u8 level;
    u8 i;
    u8 count;

    if (IS_HERO(characterId))
    {
        sPlayerStatusData.nextExp += expGain;
        count = 0;

        for (i = 0; i < ARRAY_SIZE(sPlayerExpThreshold); i++)
        {
            if (sPlayerStatusData.nextExp < sPlayerExpThreshold[i]) break;
            
            count++;
        }

        if (i == MAX_CHARACTER_LEVEL)
            count = MAX_CHARACTER_LEVEL;
    }
    else 
    {
        P3FES_ASSERT("g_data.c", 901);
    }

    level = Character_GetLevel(characterId);

    return count != level;
}

// FUN_0016dad0
void Character_SetAiTactic(u16 characterId, u8 aiTacticId)
{
    if (aiTacticId >= AI_TACTIC_MAX)
    {
        P3FES_ASSERT("g_data.c", 999);
    }

    if (IS_HERO(characterId))
    {
        sPlayerUnit.status.aiTactic = aiTacticId;
        return;
    }

    gCharacters[characterId].unit.status.aiTactic = aiTacticId;
}

// FUN_0016dd80
u8 Character_GetAiTactic(u16 characterId)
{
    if (IS_HERO(characterId))
    {
        return sPlayerUnit.status.aiTactic;
    }

    return gCharacters[characterId].unit.status.aiTactic;
}

// FUN_0016d6b0
void Character_SetPhysicalCondition(u16 characterId, u16 physicalCondition)
{
    u16 currentPhysicalCondition = sPlayerStatusData.physicalState.physicalCondition;
    u16 oldFatigueCounter;

    if (!IS_HERO(characterId))
    {
        currentPhysicalCondition = gCharacters[characterId].physicalState.physicalCondition;
    }

    if (currentPhysicalCondition != physicalCondition)
    {
        switch (physicalCondition)
        {
            case PHYSICAL_CONDITION_GOOD:
                FUN_0016f3e0(characterId + 15, 0);
                break;
            case PHYSICAL_CONDITION_GREAT:
                FUN_0016f3e0(characterId + 15, 1);
                FUN_0016f3e0(characterId + 25, 0); 
                break;
            case PHYSICAL_CONDITION_TIRED:
                FUN_0016f3e0(characterId + 15, 50);
                break;
            case PHYSICAL_CONDITION_SICK:
                FUN_0016f3e0(characterId + 15, 60);
                break;
        }
    }

    if (currentPhysicalCondition == PHYSICAL_CONDITION_TIRED && 
        physicalCondition != PHYSICAL_CONDITION_TIRED)
    {
        oldFatigueCounter = sPlayerStatusData.physicalState.oldFatigueCounter;

        if (!IS_HERO(characterId))
        {
            oldFatigueCounter = gCharacters[characterId].physicalState.oldFatigueCounter;
        }

        Character_SetFatigueCounter(characterId, oldFatigueCounter);
    }

    currentPhysicalCondition = physicalCondition;

    if (!IS_HERO(characterId))
    {
        gCharacters[characterId].physicalState.physicalCondition = physicalCondition;
        currentPhysicalCondition = sPlayerStatusData.physicalState.physicalCondition;
    }

    sPlayerStatusData.physicalState.physicalCondition = currentPhysicalCondition;
}

// FUN_0016d930
void Character_SetFatigueCounter(u16 characterId, u16 fatigueCounter)
{
    if (IS_HERO(characterId))
    {
        sPlayerStatusData.physicalState.fatigueCounter = fatigueCounter;
        return;
    }

    gCharacters[characterId].physicalState.fatigueCounter = fatigueCounter;
}

void Character_SetHealth(u16 characterId, u16 health)
{
    u16 tmp = health;

    if (!IS_HERO(characterId))
    {
        gCharacters[characterId].unit.status.health = health;
        tmp = sPlayerUnit.status.health;
    }

    sPlayerUnit.status.health = tmp;
}

// FUN_0016e920
void Character_SetActiveSocialLink(u16 activeSocialLink)
{
    sPlayerStatusData.activeSocialLink = activeSocialLink;
}

// FUN_0016ef20
u16 CalendarData_GetDaysSinceApr5()
{
    return sCalendarData.daysSinceApr5;
}

// FUN_0016ef30
u8 CalendarData_GetTime()
{
    return sCalendarData.time;
}

// FUN_0016ef40
u16 CalendarData_GetDaysSkipTarget()
{
    return sCalendarData.daysSkipTarget;
}

// FUN_0016ef50
u8 CalendarData_GetTimeSkipTarget()
{
    return sCalendarData.timeSkipTarget;
}

// FUN_0016ef60
u32 CalendarData_GetSkipToTarget()
{
    return sCalendarData.skipToTarget;
}

// FUN_0016cfe0
void Character_SetAcademicPoint(u16 characterId, u16 academicPoint)
{
    if (academicPoint < SOCIAL_STAT_MIN_POINT || academicPoint > SOCIAL_STAT_MAX_POINT)
    {
        P3FES_ASSERT("g_data.c", 797);
    }

    if (IS_HERO(characterId))
    {
        sPlayerStatusData.socialStats.academicPoint = academicPoint;
        return;
    }

    gCharacters[characterId].socialStats.academicPoint = academicPoint;
}

// FUN_0016d090
void Character_SetCharmPoint(u16 characterId, u16 charmPoint)
{
    if (charmPoint < SOCIAL_STAT_MIN_POINT || charmPoint > SOCIAL_STAT_MAX_POINT)
    {
        P3FES_ASSERT("g_data.c", 808);
    }

    if (IS_HERO(characterId))
    {
        Character_GetCharmLevel(sPlayerStatusData.socialStats.charmPoint); // ??
        sPlayerStatusData.socialStats.charmPoint = charmPoint;
        Character_GetCharmLevel(charmPoint); // ??
        return;
    }

    gCharacters[characterId].socialStats.charmPoint = charmPoint;
}

// FUN_0016d160
void Character_SetCouragePoint(u16 characterId, u16 couragePoint)
{
    if (couragePoint < SOCIAL_STAT_MIN_POINT || couragePoint > SOCIAL_STAT_MAX_POINT)
    {
        P3FES_ASSERT("g_data.c", 828);
    }

    if (IS_HERO(characterId))
    {
        Character_GetCourageLevel(sPlayerStatusData.socialStats.couragePoint); // ??
        sPlayerStatusData.socialStats.couragePoint = couragePoint;
        Character_GetCourageLevel(couragePoint); // ??
        return;
    }

    gCharacters[characterId].socialStats.couragePoint = couragePoint;
}

static inline u16 Inl_Character_GetSocialStatPoint(u16 characterId, u16 baseHeroPoint, u16 baseOtherCharPoint)
{
    u16 point = baseHeroPoint;

    if (!IS_HERO(characterId))
    {
        point = baseOtherCharPoint;
    }

    return point;
}

// FUN_0016c6f0
u16 Character_GetAcademicPoint(u16 characterId)
{
    return Inl_Character_GetSocialStatPoint(
        characterId,
        sPlayerStatusData.socialStats.academicPoint,
        gCharacters[characterId].socialStats.academicPoint);
}

// FUN_0016c6f0
u16 Character_GetCharmPoint(u16 characterId)
{
    return Inl_Character_GetSocialStatPoint(
        characterId,
        sPlayerStatusData.socialStats.charmPoint,
        gCharacters[characterId].socialStats.charmPoint);
}

u16 Character_GetCouragePoint(u16 characterId)
{
    return Inl_Character_GetSocialStatPoint(
        characterId,
        sPlayerStatusData.socialStats.couragePoint,
        gCharacters[characterId].socialStats.couragePoint);
}

// TODO
void FUN_0016ca90(u16 characterId, u16 param_2)
{
    u16 oldFatigueCounter = sPlayerStatusData.physicalState.oldFatigueCounter;
    u16 fatigueCounter = sPlayerStatusData.physicalState.fatigueCounter;
    s32 uVar3;

    if (!IS_HERO(characterId))
    {
        oldFatigueCounter = gCharacters[characterId].physicalState.oldFatigueCounter;
        fatigueCounter = gCharacters[characterId].physicalState.fatigueCounter;
    }

    uVar3 = fatigueCounter + param_2;

    if (uVar3 < 0)
    {
        uVar3 = 0;
    }
    else if (oldFatigueCounter < uVar3)
    {
        uVar3 = fatigueCounter;
    }

    Character_SetFatigueCounter(characterId, uVar3);
}

// FUN_0016c7e0
u32 Character_GetNextExp(u16 characterId)
{
    PersonaData* persona;

    if (IS_HERO(characterId))
    {
        return sPlayerStatusData.nextExp;
    }

    persona = Persona_GetPersonaByCharacterId(characterId);
    if (persona == NULL)
    {
        P3FES_ASSERT("g_data.c", 622);
    }

    return Persona_GetPersonaNextExp(persona);
}

// FUN_0016c920
u16 Character_GetPhysicalCondition(u16 characterId)
{
    if (IS_HERO(characterId))
    {
        return sPlayerStatusData.physicalState.physicalCondition;
    }

    return gCharacters[characterId].physicalState.physicalCondition;
}

// FUN_0016dd40
u16 Player_GetActiveSocialLink()
{
    return sPlayerStatusData.activeSocialLink;
}

// FUN_0016dba0
u8 Player_GetSocialLinkLevel(u16 socialLink)
{
    return sPlayerStatusData.socialLinkStat[socialLink];
}

// FUN_0016e100
u8 Player_SocialLinkLevelIsNotZero(u16 socialLink)
{
    if (socialLink < SOCIAL_LINK_SEES || socialLink > SOCIAL_LINK_NYX_TEAM)
    {
        P3FES_ASSERT("g_data.c", 1429);
    }

    return sPlayerStatusData.socialLinkStat[socialLink] > 0;
}

// FUN_0016cb80
u16 Character_GetEquipmentIdx(u16 characterId, u16 equipmentType)
{
    if (IS_HERO(characterId))
    {
        return sPlayerEquipData.equipmentsIdx[equipmentType];
    }

    return gCharacters[characterId].equipmentsIdx[equipmentType];
}

// FUN_0016ef70. Updates 'daysSinceApr5' and sets the correct 'G_FLAG_DAY_*' flags
void CalendarData_SetDaysSinceApr5(u16 daysSinceApr5)
{
    u32 currentWeekDay;
    u8 holidayOrSunday;

    Global_SetGlobalFlag(G_FLAG_DAY_IS_MONDAY, false);
    Global_SetGlobalFlag(G_FLAG_DAY_IS_TUESDAY, false);
    Global_SetGlobalFlag(G_FLAG_DAY_IS_WEDNESDAY, false);
    Global_SetGlobalFlag(G_FLAG_DAY_IS_THURSDAY, false);
    Global_SetGlobalFlag(G_FLAG_DAY_IS_FRIDAY, false);
    Global_SetGlobalFlag(G_FLAG_DAY_IS_SATURDAY, false);
    Global_SetGlobalFlag(G_FLAG_DAY_IS_SUNDAY, false);
    Global_SetGlobalFlag(G_FLAG_DAY_IS_DAYOFF, false);

    if (daysSinceApr5 != sCalendarData.daysSinceApr5)
    {
        FUN_00172890(); 
        FUN_00172e10();
        Global_SetGlobalFlag(2444, false);
    }

    sCalendarData.daysSinceApr5 = daysSinceApr5;

    currentWeekDay = Calendar_GetCurrentWeekDay();
    switch (currentWeekDay)
    {
        case CALENDAR_DAY_SUNDAY:    Global_SetGlobalFlag(G_FLAG_DAY_IS_SUNDAY, true);    break;
        case CALENDAR_DAY_MONDAY:    Global_SetGlobalFlag(G_FLAG_DAY_IS_MONDAY, true);    break;
        case CALENDAR_DAY_TUESDAY:   Global_SetGlobalFlag(G_FLAG_DAY_IS_TUESDAY, true);   break;
        case CALENDAR_DAY_WEDNESDAY: Global_SetGlobalFlag(G_FLAG_DAY_IS_WEDNESDAY, true); break;
        case CALENDAR_DAY_THURSDAY:  Global_SetGlobalFlag(G_FLAG_DAY_IS_THURSDAY, true);  break;
        case CALENDAR_DAY_FRIDAY:    Global_SetGlobalFlag(G_FLAG_DAY_IS_FRIDAY, true);    break;
        case CALENDAR_DAY_SATURDAY:  Global_SetGlobalFlag(G_FLAG_DAY_IS_SATURDAY, true);  break;
    }

    holidayOrSunday = Calendar_IsHolidayOrSunday();
    if (holidayOrSunday)
    {
        Global_SetGlobalFlag(G_FLAG_DAY_IS_DAYOFF, true);
    }
}

// FUN_0016f150
void CalendarData_SetTime(u8 time)
{
    sCalendarData.time = time;
}

// FUN_0016f160
void CalendarData_SetDaysSkipTarget(u16 days)
{
    sCalendarData.daysSkipTarget = days;
}

// FUN_0016f170
void CalendarData_SetTimeSkipTarget(u8 time)
{
    sCalendarData.timeSkipTarget = time;
}

// FUN_0016f180
void CalendarData_SetSkipToTarget(u32 val)
{
    sCalendarData.skipToTarget = val;
}

// FUN_0016f1f0. See 'g_flags.h' !!!
void Global_SetGlobalFlag(u32 bit, u8 enabled)
{
    u32 bitField;
    s32 idx;

    // 5632 is the total number of bit 
    // (There are 176 u32 in the array. u32 = 4 bytes = 32 bit. 32 * 176 = 5632)
    if ((s32)bit < 0 || (s32)bit >= 5632)
    {
        P3FES_ASSERT("g_data.c", 1933);
    }

    if (bit == 4982)
    {
        FUN_005225a8("hit \n");
    }

    idx = bit >> 5;
    if ((s32)bit < 0)
    {
        idx = (s32)(bit + 0x1f) >> 5;
    }

    bitField = bit & 0x1f;
    if ((s32)bit < 0 && bitField != 0)
    {
        bitField -= 32;
    }

    bitField = 1 << (bitField & 0x1f);
    if (enabled)
    {
        gGlobalFlags[idx] |= bitField;
        return;
    }
    
    gGlobalFlags[idx] &= ~bitField;
}

// FUN_0016f2e0
void Global_ResetGlobalFlags()
{
    u32 i;

    for (i = 0; i < ARRAY_SIZE(gGlobalFlags); i++)
    {
        gGlobalFlags[i] = 0;
    }
}

// FUN_0016f630
u16 Character_GetEquipmentId(u16 characterId, u16 equipmentIdx)
{
    // TODO
    
    if (characterId == -1) // ?
    {
        // return (&DAT_00833e80)[equipmentIdx * 10];
    }
    else if (IS_HERO(characterId))
    {
        return sPlayerEquipData.equipments[equipmentIdx].id;
    }
    else if (characterId <= 255)
    {
        return gCharacters[characterId].equipments[equipmentIdx].id;
    }

    // return (&DAT_007fd6c8 + equipmentIdx * 0x14 + characterId * 0x364);
}

// FUN_0016f900
u8 Character_GetEquipmentEffect(u16 characterId, u16 equipmentIdx)
{
    if (characterId == -1)
    {
        // return (&DAT_00833e89)[characterId * 0x14];
    }
    else if (IS_HERO(characterId))
    {
        return sPlayerEquipData.equipments[equipmentIdx].effect;
    }
    else if (characterId <= 255)
    {
        return gCharacters[characterId].equipments[equipmentIdx].effect;
    }

    // return (equpementIdx * 0x14 + characterId * 0x364 + 0x7fd6d1);
}

// FUN_00172890
void FUN_00172890()
{
    // TODO
}

// FUN_00172e10
void FUN_00172e10()
{
    // TODO
}

void Character_InitPersona(u32 characterId)
{
    if (IS_HERO(characterId))
    {
        gPlayerPersonaData.equippedPersona = -1;
        memset(gPlayerPersonaData.personas, 0, sizeof(gPlayerPersonaData.personas));

        return;
    }

    memset(&gCharacters[characterId].persona, 0, sizeof(PersonaData));
}

// FUN_00175c70
void Compendium_Init()
{
    memset(sCompendium, 0, sizeof(sCompendium));
}

static inline u16 Inl_Character_GetSocialStatLevel(u16 point, const u16* threshold, u32 size)
{
    u16 idx = size - 1;

    while (point < threshold[idx])
        idx--;

    return idx;
}

// FUN_00177280
u16 Character_GetAcademicLevel(u16 academicPoint)
{
    return Inl_Character_GetSocialStatLevel(academicPoint, academicLevelThreshold, 6);
}

// FUN_001772f0
u16 Character_GetCharmLevel(u16 charmPoint)
{
    return Inl_Character_GetSocialStatLevel(charmPoint, charmLevelThreshold, 6);
}

// FUN_00177360
u16 Character_GetCourageLevel(u16 couragePoint)
{
    return Inl_Character_GetSocialStatLevel(couragePoint, courageLevelThreshold, 6);
}

// FUN_0017c8c0
PersonaData* Compendium_GetPersonaByIdx(s32 idx)
{
    if (idx < 0 || idx >= 256)
    {
        P3FES_ASSERT("g_data.c", 6177);
    }

    if (!(sCompendium[idx].flags & PERSONA_FLAG_VALID))
    {
        return NULL;
    }

    return &sCompendium[idx];
}

// FUN_0017d7f0
void Global_SetScenarioMode(u32 scenario)
{
    sScenarioMode = scenario;
}

// FUN_0017d800
u32 Global_GetScenarioMode()
{
    return sScenarioMode;
}



// !! FUNCTIONS TO MOVE LATER !!

void P3FES_ASSERT(const char* file, const u32 line)
{
    // Probably an assert function. 
    // It's empty because it's only used if the game was compiled in debug
    // which is not the case here.
    return;
}

// FUN_001052b0
void FUN_001052b0(const char* fmt, ...)
{
    // ...
}

// FUN_005225a8
void FUN_005225a8(const char* fmt, ...)
{
    // ...
}