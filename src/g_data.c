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

DatGlobal gGlobalWork; // 00833948

void FUN_00172890();
void FUN_00172e10();

// TODO
void FUN_0016f3e0(u32 idx, u32 value)
{
    K_ASSERT(idx <= 127, 2007);

    gGlobalWork.unk_0083a4dc[idx] = value;
}

// FUN_0016c860
u16 datGetPersonaId(u16 pcId)
{
    if (IS_HERO(pcId))
    {
        if (gGlobalWork.heroPersona.equippedPersona < ARRAY_SIZE(gGlobalWork.heroPersona.personas))
        {
            return gGlobalWork.heroPersona.personas[gGlobalWork.heroPersona.equippedPersona].id;
        }

        K_ASSERT(false, 633);
    }

    return gGlobalWork.pcs[pcId].persona.id;
}

// FUN_0016cd60
DatUnit* datGetUnit(s16 pcId)
{
    if (IS_HERO(pcId))
    {
        return &gGlobalWork.heroUnit;
    }

    K_ASSERT(pcId < PC_MAX, 737);

    return &gGlobalWork.pcs[pcId].unit;
}

// FUN_0016cdf0
void datInitUnit(s16 pcId)
{
    u32 idx;
    DatPc* pcsNoReserved;

    if (IS_HERO(pcId))
    {
        memset(&gGlobalWork.heroUnit, 0, sizeof(DatUnit));

        gGlobalWork.heroUnit.id = pcId;
        gGlobalWork.heroUnit.id2 = pcId;
        gGlobalWork.heroUnit.aiTactic = AI_TACTIC_ACT_FREELY;

        return;
    }

    idx = pcId - PC_YUKARI;
    pcsNoReserved = &gGlobalWork.pcs[PC_YUKARI];
    memset(&pcsNoReserved[idx].unit, 0, sizeof(DatUnit));

    gGlobalWork.pcs[pcId].unit.id = pcId;
    gGlobalWork.pcs[pcId].unit.id2 = pcId;
    gGlobalWork.pcs[pcId].unit.aiTactic = AI_TACTIC_ACT_FREELY;
}

// FUN_0016c470
u8 datGetLevel(u16 pcId)
{
    if (IS_HERO(pcId))
    {
        return datCalcGetLevel(&gGlobalWork.heroUnit);
    }

    return datCalcGetLevel(&gGlobalWork.pcs[pcId].unit);
}

// FUN_0016c970
u32 datGetBadStatusNoDown(u16 pcId)
{
    if (IS_HERO(pcId))
    {
        return datCalcGetBadStatusNoDown(&gGlobalWork.heroUnit);
    }

    return datCalcGetBadStatusNoDown(&gGlobalWork.pcs[pcId].unit);
}

// FUN_0016d8b0
void datSetBadStatus(u16 pcId, u32 flags)
{
    if (IS_HERO(pcId))
    {
        datCalcSetBadStatus(&gGlobalWork.heroUnit, flags);
        return;
    }

    datCalcSetBadStatus(&gGlobalWork.pcs[pcId].unit, flags);
}

// FUN_0016d980
void datSetOldFatigueCounter(u16 pcId, u16 oldFatigueCounter)
{
    if (IS_HERO(pcId))
    {
        gGlobalWork.heroStatus.physicalState.oldFatigueCounter = oldFatigueCounter;
        return;
    }

    gGlobalWork.pcs[pcId].physicalState.oldFatigueCounter = oldFatigueCounter;
}

// FUN_0016d9d0
void datClearBadStatus(u16 pcId, u32 flags)
{
    if (IS_HERO(pcId))
    {
        datCalcClearBadStatus(&gGlobalWork.heroUnit, flags);
        return;
    }

    datCalcClearBadStatus(&gGlobalWork.pcs[pcId].unit, flags);
}

// FUN_0016d2f0
u32 datGetExpUntilNextLevel(u16 pcId)
{
    u32 nextExpTmp;
    u32 nextExp = gGlobalWork.heroStatus.nextExp;
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
    nextExpTmp = gGlobalWork.heroStatus.nextExp;

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
        gGlobalWork.heroStatus.nextExp += expGain;
        count = 0;

        for (i = 0; i < ARRAY_SIZE(sPlayerExpThreshold); i++)
        {
            if (gGlobalWork.heroStatus.nextExp < sPlayerExpThreshold[i]) break;
            
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
        gGlobalWork.heroUnit.aiTactic = aiTacticId;
        return;
    }

    gGlobalWork.pcs[pcId].unit.aiTactic = aiTacticId;
}

// FUN_0016dd50
u32 datGetMoney()
{
    return gGlobalWork.heroMoney;
}

// FUN_0016dd60
s16 datGetPartyId(s32 idx)
{
    return gGlobalWork.partyIds[idx];
}

// FUN_0016e990
void datSetPartyId(s32 idx, s16 pcId)
{
    gGlobalWork.partyIds[idx] = pcId;
}

// FUN_0016dd80
u8 datGetAiTactic(u16 pcId)
{
    if (IS_HERO(pcId))
    {
        return gGlobalWork.heroUnit.aiTactic;
    }

    return gGlobalWork.pcs[pcId].unit.aiTactic;
}

// FUN_0016d6b0
void datSetPhysicalCondition(u16 pcId, u16 physicalCondition)
{
    u16 currentPhysicalCondition = gGlobalWork.heroStatus.physicalState.physicalCondition;
    u16 oldFatigueCounter;

    if (!IS_HERO(pcId))
    {
        currentPhysicalCondition = gGlobalWork.pcs[pcId].physicalState.physicalCondition;
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
        oldFatigueCounter = gGlobalWork.heroStatus.physicalState.oldFatigueCounter;

        if (!IS_HERO(pcId))
        {
            oldFatigueCounter = gGlobalWork.pcs[pcId].physicalState.oldFatigueCounter;
        }

        datSetFatigueCounter(pcId, oldFatigueCounter);
    }

    currentPhysicalCondition = physicalCondition;

    if (!IS_HERO(pcId))
    {
        gGlobalWork.pcs[pcId].physicalState.physicalCondition = physicalCondition;
        currentPhysicalCondition = gGlobalWork.heroStatus.physicalState.physicalCondition;
    }

    gGlobalWork.heroStatus.physicalState.physicalCondition = currentPhysicalCondition;
}

// FUN_0016d930
void datSetFatigueCounter(u16 pcId, u16 fatigueCounter)
{
    if (IS_HERO(pcId))
    {
        gGlobalWork.heroStatus.physicalState.fatigueCounter = fatigueCounter;
        return;
    }

    gGlobalWork.pcs[pcId].physicalState.fatigueCounter = fatigueCounter;
}

void datSetHp(u16 pcId, u16 hp)
{
    u16 tmp = hp;

    if (!IS_HERO(pcId))
    {
        gGlobalWork.pcs[pcId].unit.hp = hp;
        tmp = gGlobalWork.heroUnit.hp;
    }

    gGlobalWork.heroUnit.hp = tmp;
}

// FUN_0016e920
void datSetActiveSocialLink(u16 activeSocialLink)
{
    gGlobalWork.heroStatus.activeSocialLink = activeSocialLink;
}

// FUN_0016ef20
s16 datGetDaysSinceApr5()
{
    return gGlobalWork.calendarWork.daysSinceApr5;
}

// FUN_0016ef30
s8 datGetTime()
{
    return gGlobalWork.calendarWork.time;
}

// FUN_0016ef40
s16 datGetDaysSkipTarget()
{
    return gGlobalWork.calendarWork.daysSkipTarget;
}

// FUN_0016ef50
s8 datGetTimeSkipTarget()
{
    return gGlobalWork.calendarWork.timeSkipTarget;
}

// FUN_0016ef60
u32 datGetSkipToTarget()
{
    return gGlobalWork.calendarWork.skipToTarget;
}

// FUN_0016cfe0
void datSetAcademicPoint(u16 pcId, u16 academicPoint)
{
    K_ASSERT(academicPoint > SOCIAL_STAT_MIN_POINT && academicPoint < SOCIAL_STAT_MAX_POINT, 797);

    if (IS_HERO(pcId))
    {
        gGlobalWork.heroStatus.socialStats.academicPoint = academicPoint;
        return;
    }

    gGlobalWork.pcs[pcId].socialStats.academicPoint = academicPoint;
}

// FUN_0016d090
void datSetCharmPoint(u16 pcId, u16 charmPoint)
{
    K_ASSERT(charmPoint > SOCIAL_STAT_MIN_POINT && charmPoint < SOCIAL_STAT_MAX_POINT, 808);

    if (IS_HERO(pcId))
    {
        datGetCharmLevel(gGlobalWork.heroStatus.socialStats.charmPoint); // ??
        gGlobalWork.heroStatus.socialStats.charmPoint = charmPoint;
        datGetCharmLevel(charmPoint); // ??
        return;
    }

    gGlobalWork.pcs[pcId].socialStats.charmPoint = charmPoint;
}

// FUN_0016d160
void datSetCouragePoint(u16 pcId, u16 couragePoint)
{
    K_ASSERT(couragePoint > SOCIAL_STAT_MIN_POINT && couragePoint < SOCIAL_STAT_MAX_POINT, 828);

    if (IS_HERO(pcId))
    {
        datGetCourageLevel(gGlobalWork.heroStatus.socialStats.couragePoint); // ??
        gGlobalWork.heroStatus.socialStats.couragePoint = couragePoint;
        datGetCourageLevel(couragePoint); // ??
        return;
    }

    gGlobalWork.pcs[pcId].socialStats.couragePoint = couragePoint;
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
        gGlobalWork.heroStatus.socialStats.academicPoint,
        gGlobalWork.pcs[pcId].socialStats.academicPoint);
}

// FUN_0016c6f0
u16 datGetCharmPoint(u16 pcId)
{
    return Inl_Character_GetSocialStatPoint(
        pcId,
        gGlobalWork.heroStatus.socialStats.charmPoint,
        gGlobalWork.pcs[pcId].socialStats.charmPoint);
}

u16 datGetCouragePoint(u16 pcId)
{
    return Inl_Character_GetSocialStatPoint(
        pcId,
        gGlobalWork.heroStatus.socialStats.couragePoint,
        gGlobalWork.pcs[pcId].socialStats.couragePoint);
}

// TODO
void FUN_0016ca90(u16 pcId, u16 param_2)
{
    u16 oldFatigueCounter = gGlobalWork.heroStatus.physicalState.oldFatigueCounter;
    u16 fatigueCounter = gGlobalWork.heroStatus.physicalState.fatigueCounter;
    s32 uVar3;

    if (!IS_HERO(pcId))
    {
        oldFatigueCounter = gGlobalWork.pcs[pcId].physicalState.oldFatigueCounter;
        fatigueCounter = gGlobalWork.pcs[pcId].physicalState.fatigueCounter;
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
        return gGlobalWork.heroStatus.nextExp;
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
        return gGlobalWork.heroStatus.physicalState.physicalCondition;
    }

    return gGlobalWork.pcs[pcId].physicalState.physicalCondition;
}

// FUN_0016dd40
u16 datGetActiveSocialLink()
{
    return gGlobalWork.heroStatus.activeSocialLink;
}

// FUN_0016dba0
u8 datGetSocialLinkLevel(u16 socialLink)
{
    return gGlobalWork.heroStatus.socialLinkStat[socialLink];
}

// FUN_0016e100
u8 datSocialLinkLevelIsNotZero(u16 socialLink)
{
    K_ASSERT(socialLink > SOCIAL_LINK_SEES && socialLink < SOCIAL_LINK_NYX_TEAM, 1429);

    return gGlobalWork.heroStatus.socialLinkStat[socialLink] > 0;
}

// FUN_0016cb80
u16 datGetEquipmentIdx(u16 pcId, u16 equipmentType)
{
    if (IS_HERO(pcId))
    {
        return gGlobalWork.heroEquip.equipmentsIdx[equipmentType];
    }

    return gGlobalWork.pcs[pcId].equipmentsIdx[equipmentType];
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

    if (daysSinceApr5 != gGlobalWork.calendarWork.daysSinceApr5)
    {
        FUN_00172890(); 
        FUN_00172e10();
        datSetFlag(2444, false);
    }

    gGlobalWork.calendarWork.daysSinceApr5 = daysSinceApr5;

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
    gGlobalWork.calendarWork.time = time;
}

// FUN_0016f160
void datSetDaysSkipTarget(s16 days)
{
    gGlobalWork.calendarWork.daysSkipTarget = days;
}

// FUN_0016f170
void datSetTimeSkipTarget(s8 time)
{
    gGlobalWork.calendarWork.timeSkipTarget = time;
}

// FUN_0016f180
void datSetSkipToTarget(u32 val)
{
    gGlobalWork.calendarWork.skipToTarget = val;
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
        gGlobalWork.flags[idx] |= mask;
        return;
    }

    gGlobalWork.flags[idx] &= ~mask;
}

// FUN_0016f2e0
void datClearFlagAll()
{
    s32 i;
    u32* flags;

    i = 0;
    flags = gGlobalWork.flags;
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
        return gGlobalWork.heroEquip.equipments[equipmentIdx].id;
    }
    else if (pcId <= 255)
    {
        return gGlobalWork.pcs[pcId].equipments[equipmentIdx].id;
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
        return gGlobalWork.heroEquip.equipments[equipmentIdx].effect;
    }
    else if (pcId <= 255)
    {
        return gGlobalWork.pcs[pcId].equipments[equipmentIdx].effect;
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
        gGlobalWork.heroPersona.equippedPersona = -1;
        memset(gGlobalWork.heroPersona.personas, 0, sizeof(gGlobalWork.heroPersona.personas));

        return;
    }

    memset(&gGlobalWork.pcs[pcId].persona, 0, sizeof(DatPersonaWork));
}

// FUN_00175c70
void datCompendiumInit()
{
    memset(gGlobalWork.compendium, 0, sizeof(gGlobalWork.compendium));
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

// FUN_0017b170
u32 datGetTotalBtl()
{
    return gGlobalWork.totalBtl;
}

// FUN_0017c8c0
DatPersonaWork* datGetPersonaByCompendium(s32 idx)
{
    K_ASSERT(idx > 0 && idx < 256, 6177);

    if (!(gGlobalWork.compendium[idx].flags & PERSONA_FLAG_VALID))
    {
        return NULL;
    }

    return &gGlobalWork.compendium[idx];
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