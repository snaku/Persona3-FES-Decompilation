#include "datPersona.h"
#include "g_data.h"
#include "g_flags.h"
#include "datCalc.h"
#include "temporary.h"
#include "Kosaka/k_assert.h"

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

DatPc gPcs[PC_MAX - 1];

static DatUnit sHeroUnit;               // 00836224
static DatHeroStatus sHeroStatus;       // 00836260
static DatHeroEquipment sHeroEquip;     // 0083678c
static CalendarWork sCalendarWork;      // 0083679c
DatHeroPersona gHeroPersona;            // 00836ba8
static DatPersonaWork sCompendium[256]; // 00836e1c

static u32 gFlags[FLG_ARR_SIZE]; // 0083a21c. See 'flags.h' !!!
static u32 gIUnkArr[128];        // 0083a4dc


void FUN_00172890();
void FUN_00172e10();

// TODO
void FUN_0016f3e0(u32 idx, u32 value)
{
    K_ASSERT(idx <= 127, 2007);

    gIUnkArr[idx] = value;
}

// FUN_0016c860
u16 datGetPersonaId(u16 pcId)
{
    if (IS_HERO(pcId))
    {
        if (gHeroPersona.equippedPersona < ARRAY_SIZE(gHeroPersona.personas))
        {
            return gHeroPersona.personas[gHeroPersona.equippedPersona].id;
        }

        K_ASSERT(false, 633);
    }

    return gPcs[pcId].persona.id;
}

// FUN_0016cd60
DatUnit* datGetUnit(s16 pcId)
{
    if (IS_HERO(pcId))
    {
        return &sHeroUnit;
    }

    K_ASSERT(pcId < PC_MAX, 737);

    return &gPcs[pcId].unit;
}

// FUN_0016cdf0
void datInitUnit(u16 pcId)
{
    if (IS_HERO(pcId))
    {
        memset(&sHeroUnit, 0, sizeof(DatUnit));

        sHeroUnit.aiTactic = AI_TACTIC_ACT_FREELY;
        sHeroUnit.id = PC_HERO;
        sHeroUnit.flags = UNIT_FLAG_ACTIVE;

        return;
    }

    memset(&gPcs[pcId].unit, 0, sizeof(DatUnit));

    gPcs[pcId].unit.id = pcId;
    gPcs[pcId].unit.aiTactic = AI_TACTIC_ACT_FREELY;
    gPcs[pcId].unit.flags = UNIT_FLAG_ACTIVE;
}

// FUN_0016c470
u8 datGetLevel(u16 pcId)
{
    if (IS_HERO(pcId))
    {
        return datCalcGetLevel(&sHeroUnit);
    }

    return datCalcGetLevel(&gPcs[pcId].unit);
}

// FUN_0016c970
u32 datGetBadStatusNoDown(u16 pcId)
{
    if (IS_HERO(pcId))
    {
        return datCalcGetBadStatusNoDown(&sHeroUnit);
    }

    return datCalcGetBadStatusNoDown(&gPcs[pcId].unit);
}

// FUN_0016d8b0
void datSetBadStatus(u16 pcId, u32 flags)
{
    if (IS_HERO(pcId))
    {
        datCalcSetBadStatus(&sHeroUnit, flags);
        return;
    }

    datCalcSetBadStatus(&gPcs[pcId].unit, flags);
}

// FUN_0016d980
void datSetOldFatigueCounter(u16 pcId, u16 oldFatigueCounter)
{
    if (IS_HERO(pcId))
    {
        sHeroStatus.physicalState.oldFatigueCounter = oldFatigueCounter;
        return;
    }

    gPcs[pcId].physicalState.oldFatigueCounter = oldFatigueCounter;
}

// FUN_0016d9d0
void datClearBadStatus(u16 pcId, u32 flags)
{
    if (IS_HERO(pcId))
    {
        datCalcClearBadStatus(&sHeroUnit, flags);
        return;
    }

    datCalcClearBadStatus(&gPcs[pcId].unit, flags);
}

// FUN_0016d2f0
u32 datGetExpUntilNextLevel(u16 pcId)
{
    u32 nextExpTmp;
    u32 nextExp = sHeroStatus.nextExp;
    DatPersonaWork* persona;
    u8 i;

    if (!IS_HERO(pcId))
    {
        persona = datPersonaGetByPcId(pcId);
        K_ASSERT(persona != NULL, 622);

        nextExp = datPersonaGetNextExp(persona);
    }

    for (i = 0; i < ARRAY_SIZE(sPlayerExpThreshold); i++)
    {
        if (nextExp < sPlayerExpThreshold[i]) break;
    }

    if (i == MAX_CHARACTER_LEVEL)
    {
        nextExp = 0;
    }

    K_ASSERT(i != 0 && i < MAX_CHARACTER_LEVEL, 876);

    nextExp = sPlayerExpThreshold[i];
    nextExpTmp = sHeroStatus.nextExp;

    nextExp -= nextExpTmp;

    return nextExp;
}

// FUN_0016d560
u8 datDidCharacterLevelUp(u16 pcId, u32 expGain)
{
    u8 level;
    u8 i;
    u8 count;

    if (IS_HERO(pcId))
    {
        sHeroStatus.nextExp += expGain;
        count = 0;

        for (i = 0; i < ARRAY_SIZE(sPlayerExpThreshold); i++)
        {
            if (sHeroStatus.nextExp < sPlayerExpThreshold[i]) break;
            
            count++;
        }

        if (i == MAX_CHARACTER_LEVEL)
            count = MAX_CHARACTER_LEVEL;
    }
    else 
    {
        K_ASSERT(false, 901);
    }

    level = datGetLevel(pcId);

    return count != level;
}

// FUN_0016dad0
void datSetAiTactic(u16 pcId, u8 aiTacticId)
{
    K_ASSERT(aiTacticId < AI_TACTIC_MAX, 999);

    if (IS_HERO(pcId))
    {
        sHeroUnit.aiTactic = aiTacticId;
        return;
    }

    gPcs[pcId].unit.aiTactic = aiTacticId;
}

// FUN_0016dd60
u16 datGetPartyId(s32 idx)
{
    // TODO

    return 0;
}

// FUN_0016dd80
u8 datGetAiTactic(u16 pcId)
{
    if (IS_HERO(pcId))
    {
        return sHeroUnit.aiTactic;
    }

    return gPcs[pcId].unit.aiTactic;
}

// FUN_0016d6b0
void datSetPhysicalCondition(u16 pcId, u16 physicalCondition)
{
    u16 currentPhysicalCondition = sHeroStatus.physicalState.physicalCondition;
    u16 oldFatigueCounter;

    if (!IS_HERO(pcId))
    {
        currentPhysicalCondition = gPcs[pcId].physicalState.physicalCondition;
    }

    if (currentPhysicalCondition != physicalCondition)
    {
        switch (physicalCondition)
        {
            case PHYSICAL_CONDITION_GOOD:
                FUN_0016f3e0(pcId + 15, 0);
                break;
            case PHYSICAL_CONDITION_GREAT:
                FUN_0016f3e0(pcId + 15, 1);
                FUN_0016f3e0(pcId + 25, 0); 
                break;
            case PHYSICAL_CONDITION_TIRED:
                FUN_0016f3e0(pcId + 15, 50);
                break;
            case PHYSICAL_CONDITION_SICK:
                FUN_0016f3e0(pcId + 15, 60);
                break;
        }
    }

    if (currentPhysicalCondition == PHYSICAL_CONDITION_TIRED && 
        physicalCondition != PHYSICAL_CONDITION_TIRED)
    {
        oldFatigueCounter = sHeroStatus.physicalState.oldFatigueCounter;

        if (!IS_HERO(pcId))
        {
            oldFatigueCounter = gPcs[pcId].physicalState.oldFatigueCounter;
        }

        datSetFatigueCounter(pcId, oldFatigueCounter);
    }

    currentPhysicalCondition = physicalCondition;

    if (!IS_HERO(pcId))
    {
        gPcs[pcId].physicalState.physicalCondition = physicalCondition;
        currentPhysicalCondition = sHeroStatus.physicalState.physicalCondition;
    }

    sHeroStatus.physicalState.physicalCondition = currentPhysicalCondition;
}

// FUN_0016d930
void datSetFatigueCounter(u16 pcId, u16 fatigueCounter)
{
    if (IS_HERO(pcId))
    {
        sHeroStatus.physicalState.fatigueCounter = fatigueCounter;
        return;
    }

    gPcs[pcId].physicalState.fatigueCounter = fatigueCounter;
}

void datSetHp(u16 pcId, u16 hp)
{
    u16 tmp = hp;

    if (!IS_HERO(pcId))
    {
        gPcs[pcId].unit.hp = hp;
        tmp = sHeroUnit.hp;
    }

    sHeroUnit.hp = tmp;
}

// FUN_0016e920
void datSetActiveSocialLink(u16 activeSocialLink)
{
    sHeroStatus.activeSocialLink = activeSocialLink;
}

// FUN_0016ef20
s16 datGetDaysSinceApr5()
{
    return sCalendarWork.daysSinceApr5;
}

// FUN_0016ef30
s8 datGetTime()
{
    return sCalendarWork.time;
}

// FUN_0016ef40
s16 datGetDaysSkipTarget()
{
    return sCalendarWork.daysSkipTarget;
}

// FUN_0016ef50
s8 datGetTimeSkipTarget()
{
    return sCalendarWork.timeSkipTarget;
}

// FUN_0016ef60
u32 datGetSkipToTarget()
{
    return sCalendarWork.skipToTarget;
}

// FUN_0016cfe0
void datSetAcademicPoint(u16 pcId, u16 academicPoint)
{
    K_ASSERT(academicPoint > SOCIAL_STAT_MIN_POINT && academicPoint < SOCIAL_STAT_MAX_POINT, 797);

    if (IS_HERO(pcId))
    {
        sHeroStatus.socialStats.academicPoint = academicPoint;
        return;
    }

    gPcs[pcId].socialStats.academicPoint = academicPoint;
}

// FUN_0016d090
void datSetCharmPoint(u16 pcId, u16 charmPoint)
{
    K_ASSERT(charmPoint > SOCIAL_STAT_MIN_POINT && charmPoint < SOCIAL_STAT_MAX_POINT, 808);

    if (IS_HERO(pcId))
    {
        datGetCharmLevel(sHeroStatus.socialStats.charmPoint); // ??
        sHeroStatus.socialStats.charmPoint = charmPoint;
        datGetCharmLevel(charmPoint); // ??
        return;
    }

    gPcs[pcId].socialStats.charmPoint = charmPoint;
}

// FUN_0016d160
void datSetCouragePoint(u16 pcId, u16 couragePoint)
{
    K_ASSERT(couragePoint > SOCIAL_STAT_MIN_POINT && couragePoint < SOCIAL_STAT_MAX_POINT, 828);

    if (IS_HERO(pcId))
    {
        datGetCourageLevel(sHeroStatus.socialStats.couragePoint); // ??
        sHeroStatus.socialStats.couragePoint = couragePoint;
        datGetCourageLevel(couragePoint); // ??
        return;
    }

    gPcs[pcId].socialStats.couragePoint = couragePoint;
}

static inline u16 Inl_Character_GetSocialStatPoint(u16 pcId, u16 baseHeroPoint, u16 baseOtherCharPoint)
{
    u16 point = baseHeroPoint;

    if (!IS_HERO(pcId))
    {
        point = baseOtherCharPoint;
    }

    return point;
}

// FUN_0016c6f0
u16 datGetAcademicPoint(u16 pcId)
{
    return Inl_Character_GetSocialStatPoint(
        pcId,
        sHeroStatus.socialStats.academicPoint,
        gPcs[pcId].socialStats.academicPoint);
}

// FUN_0016c6f0
u16 datGetCharmPoint(u16 pcId)
{
    return Inl_Character_GetSocialStatPoint(
        pcId,
        sHeroStatus.socialStats.charmPoint,
        gPcs[pcId].socialStats.charmPoint);
}

u16 datGetCouragePoint(u16 pcId)
{
    return Inl_Character_GetSocialStatPoint(
        pcId,
        sHeroStatus.socialStats.couragePoint,
        gPcs[pcId].socialStats.couragePoint);
}

// TODO
void FUN_0016ca90(u16 pcId, u16 param_2)
{
    u16 oldFatigueCounter = sHeroStatus.physicalState.oldFatigueCounter;
    u16 fatigueCounter = sHeroStatus.physicalState.fatigueCounter;
    s32 uVar3;

    if (!IS_HERO(pcId))
    {
        oldFatigueCounter = gPcs[pcId].physicalState.oldFatigueCounter;
        fatigueCounter = gPcs[pcId].physicalState.fatigueCounter;
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

    datSetFatigueCounter(pcId, uVar3);
}

// FUN_0016c7e0
u32 datGetNextExp(u16 pcId)
{
    DatPersonaWork* persona; // per

    if (IS_HERO(pcId))
    {
        return sHeroStatus.nextExp;
    }

    persona = datPersonaGetByPcId(pcId);
    K_ASSERT(persona != NULL, 622);

    return datPersonaGetNextExp(persona);
}

// FUN_0016c920
u16 datGetPhysicalCondition(u16 pcId)
{
    if (IS_HERO(pcId))
    {
        return sHeroStatus.physicalState.physicalCondition;
    }

    return gPcs[pcId].physicalState.physicalCondition;
}

// FUN_0016dd40
u16 datGetActiveSocialLink()
{
    return sHeroStatus.activeSocialLink;
}

// FUN_0016dba0
u8 datGetSocialLinkLevel(u16 socialLink)
{
    return sHeroStatus.socialLinkStat[socialLink];
}

// FUN_0016e100
u8 datSocialLinkLevelIsNotZero(u16 socialLink)
{
    K_ASSERT(socialLink > SOCIAL_LINK_SEES && socialLink < SOCIAL_LINK_NYX_TEAM, 1429);

    return sHeroStatus.socialLinkStat[socialLink] > 0;
}

// FUN_0016cb80
u16 datGetEquipmentIdx(u16 pcId, u16 equipmentType)
{
    if (IS_HERO(pcId))
    {
        return sHeroEquip.equipmentsIdx[equipmentType];
    }

    return gPcs[pcId].equipmentsIdx[equipmentType];
}

// FUN_0016ef70. Updates 'daysSinceApr5' and sets the correct 'FLG_DAY_*' flags
void datSetDaysSinceApr5(s16 daysSinceApr5)
{
    u32 currentWeekDay;
    u8 holidayOrSunday;

    datSetFlag(FLG_DAY_IS_MONDAY, false);
    datSetFlag(FLG_DAY_IS_TUESDAY, false);
    datSetFlag(FLG_DAY_IS_WEDNESDAY, false);
    datSetFlag(FLG_DAY_IS_THURSDAY, false);
    datSetFlag(FLG_DAY_IS_FRIDAY, false);
    datSetFlag(FLG_DAY_IS_SATURDAY, false);
    datSetFlag(FLG_DAY_IS_SUNDAY, false);
    datSetFlag(FLG_DAY_IS_DAYOFF, false);

    if (daysSinceApr5 != sCalendarWork.daysSinceApr5)
    {
        FUN_00172890(); 
        FUN_00172e10();
        datSetFlag(2444, false);
    }

    sCalendarWork.daysSinceApr5 = daysSinceApr5;

    currentWeekDay = datGetCurrentWeekDay();
    switch (currentWeekDay)
    {
        case CALENDAR_DAY_SUNDAY:    datSetFlag(FLG_DAY_IS_SUNDAY, true);    break;
        case CALENDAR_DAY_MONDAY:    datSetFlag(FLG_DAY_IS_MONDAY, true);    break;
        case CALENDAR_DAY_TUESDAY:   datSetFlag(FLG_DAY_IS_TUESDAY, true);   break;
        case CALENDAR_DAY_WEDNESDAY: datSetFlag(FLG_DAY_IS_WEDNESDAY, true); break;
        case CALENDAR_DAY_THURSDAY:  datSetFlag(FLG_DAY_IS_THURSDAY, true);  break;
        case CALENDAR_DAY_FRIDAY:    datSetFlag(FLG_DAY_IS_FRIDAY, true);    break;
        case CALENDAR_DAY_SATURDAY:  datSetFlag(FLG_DAY_IS_SATURDAY, true);  break;
    }

    holidayOrSunday = clndIsHolidayOrSunday();
    if (holidayOrSunday)
    {
        datSetFlag(FLG_DAY_IS_DAYOFF, true);
    }
}

// FUN_0016f150
void datSetTime(s8 time)
{
    sCalendarWork.time = time;
}

// FUN_0016f160
void datSetDaysSkipTarget(s16 days)
{
    sCalendarWork.daysSkipTarget = days;
}

// FUN_0016f170
void datSetTimeSkipTarget(s8 time)
{
    sCalendarWork.timeSkipTarget = time;
}

// FUN_0016f180
void datSetSkipToTarget(u32 val)
{
    sCalendarWork.skipToTarget = val;
}

// FUN_0016f190
u32 datGetFlag(s32 bit)
{
    // TODO

    return false;
}

// FUN_0016f1f0. See 'g_flags.h' !!!
void datSetFlag(s32 bit, u8 enabled)
{
    s32 mask;
    s32 idx;

    K_ASSERT(bit >= 0 && bit < FLG_MAX, 1933);

    if (bit == 4982)
    {
        printf("hit \n");
    }

    idx = bit / 32;
    mask = bit % 32;
    mask = 1 << mask;
    
    if (enabled)
    {
        gFlags[idx] |= mask;
        return;
    }

    gFlags[idx] &= ~mask;
}

// FUN_0016f2e0
void datClearFlagAll()
{
    s32 i;
    u32* flags;

    i = 0;
    flags = gFlags;
    for (; i < FLG_ARR_SIZE; i++)
    {
        flags[i] = 0;
    }
}

// FUN_0016f630
u16 datGetEquipmentId(u16 pcId, u16 equipmentIdx)
{
    // TODO
    
    if (pcId == -1) // ?
    {
        // return (&DAT_00833e80)[equipmentIdx * 10];
    }
    else if (IS_HERO(pcId))
    {
        return sHeroEquip.equipments[equipmentIdx].id;
    }
    else if (pcId <= 255)
    {
        return gPcs[pcId].equipments[equipmentIdx].id;
    }

    // return (&DAT_007fd6c8 + equipmentIdx * 0x14 + pcId * 0x364);
}

// FUN_0016f900
u8 datGetEquipmentEffect(u16 pcId, u16 equipmentIdx)
{
    if (pcId == -1)
    {
        // return (&DAT_00833e89)[pcId * 0x14];
    }
    else if (IS_HERO(pcId))
    {
        return sHeroEquip.equipments[equipmentIdx].effect;
    }
    else if (pcId <= 255)
    {
        return gPcs[pcId].equipments[equipmentIdx].effect;
    }

    // return (equpementIdx * 0x14 + pcId * 0x364 + 0x7fd6d1);
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

void datInitPersona(u32 pcId)
{
    if (IS_HERO(pcId))
    {
        gHeroPersona.equippedPersona = -1;
        memset(gHeroPersona.personas, 0, sizeof(gHeroPersona.personas));

        return;
    }

    memset(&gPcs[pcId].persona, 0, sizeof(DatPersonaWork));
}

// FUN_00175c70
void datCompendiumInit()
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
u16 datGetAcademicLevel(u16 academicPoint)
{
    return Inl_Character_GetSocialStatLevel(academicPoint, academicLevelThreshold, 6);
}

// FUN_001772f0
u16 datGetCharmLevel(u16 charmPoint)
{
    return Inl_Character_GetSocialStatLevel(charmPoint, charmLevelThreshold, 6);
}

// FUN_00177360
u16 datGetCourageLevel(u16 couragePoint)
{
    return Inl_Character_GetSocialStatLevel(couragePoint, courageLevelThreshold, 6);
}

// FUN_0017c8c0
DatPersonaWork* datGetPersonaByCompendium(s32 idx)
{
    K_ASSERT(idx > 0 && idx < 256, 6177);

    if (!(sCompendium[idx].flags & PERSONA_FLAG_VALID))
    {
        return NULL;
    }

    return &sCompendium[idx];
}

// FUN_0017d7f0
void datSetScenarioMode(u32 scenario)
{
    sScenarioMode = scenario;
}

// FUN_0017d800
u32 datGetScenarioMode()
{
    return sScenarioMode;
}