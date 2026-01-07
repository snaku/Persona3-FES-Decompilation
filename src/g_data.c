#include "datPersona.h"
#include "g_data.h"
#include "datCalc.h"
#include "temporary.h"

#include <stdlib.h>

// 005dc050, TODO
const u32 playerNextExpThreshold[MAX_CHARACTER_LEVEL] = 
{
    0x14, 0x2f, 0x63, 0xb9, 0x0138, 0x01EA, 0x02D6, 0x0406
};

// 0x5e3068
const u16 academicLevelThreshold[6] = { 0, 20, 80, 140, 200, 260 };
// 0x5e3078
const u16 charmLevelThreshold[6] = { 0, 15, 30, 45, 65, 80 };
// 0x5e3088
const u16 courageLevelThreshold[6] = { 0, 15, 30, 45, 65, 80 };

// 005e35ec. TODO
static const u8* nameTable[] =
{
    "Metis", "Aigis", "Mitsuru Kirijo", "Junpei Iori", "Fuuka Yamagishi", "Akihiko Sanada",
    "Ken Amada", "Shinjiro Aragaki", "Koromaru", "Shuji Ikutsuki", "Pharos", 
    "Ryoji Mochizuki", "Takeharu Kirijo", "Takaya", " ", "Chidori", "Natsuki Moriyama",
    "Bully Girl", "Bully Girl", "Bully Girl", "Punk", "Punk", "Punk", "Punk", 
    "Kazushi Miyamoto", "Yuko Nishiwaki", "Track Team"
};

// 005e4150
static const u8* physicalConditionsString[13] = 
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

// 0083a21c. See 'g_flags.h' !!!
static u32 gGlobalFlags[176];

// 0083a4dc
static u32 gIUnkArr[128]; // TODO

// TODO
void FUN_0016f3e0(u32 idx, u32 value)
{
    if (idx > 127)
    {
        P3FES_ASSERT("g_data.c", 2007);
    }

    gIUnkArr[idx] = value;
}

// FUN_0016c860 (idk why it's in g_data.c and not in datPersona.c)
u16 Persona_GetPersonaId(u16 characterId)
{
    if (IS_HERO(characterId))
    {
        if (gPlayerData.equippedPersona < ARRAY_SIZE(gPlayerData.personas))
        {
            return gPlayerData.personas[gPlayerData.equippedPersona].id;
        }

        P3FES_ASSERT("g_data.c", 633);
    }

    return gCharacters[characterId].persona.id;
}

// FUN_0016cdf0
void FUN_0016cdf0(u16 characterId)
{
    if (IS_HERO(characterId))
    {
        P3FES_Memset(&gPlayerData, 0, 60);
        gPlayerData.unit.status.aiTactic = AI_TACTIC_ACT_FREELY;
        gPlayerData.unit.id = CHARACTER_HERO;
        gPlayerData.unit.flags = UNIT_FLAG_ACTIVE;
    }
    else 
    {
        P3FES_Memset(&gCharacters[characterId], 0, 60);
        gCharacters[characterId].unit.id = characterId;
        gCharacters[characterId].unit.status.aiTactic = AI_TACTIC_ACT_FREELY;
        gCharacters[characterId].unit.flags = UNIT_FLAG_ACTIVE;
    }
}

// FUN_0017d7f0
void GlobalCtx_SetScenarioMode(u32 scenario)
{
    ctx.scenarioMode = scenario;
}

// FUN_0017d800
u32 GlobalCtx_GetScenarioMode()
{
    return ctx.scenarioMode;
}

// FUN_0016cd60
UnitData* Character_GetUnit(u16 characterId)
{
    if (IS_HERO(characterId))
    {
        return &gPlayerData.unit;
    }

    if (characterId < MAX_CHARACTERS)
    {
        return &gCharacters[characterId].unit;
    }

    P3FES_ASSERT("g_data.c", 737);
}

// FUN_0016c470
u8 Character_GetLevel(u16 characterId)
{
    if (IS_HERO(characterId))
    {
        return Unit_GetLevel(&gPlayerData.unit);
    }

    return Unit_GetLevel(&gCharacters[characterId].unit);
}

// FUN_0016c970
u32 Character_GetBattleFlagsNoDown(u16 characterId)
{
    if (IS_HERO(characterId))
    {
        return Unit_GetBattleFlagsNoDown(&gPlayerData.unit);
    }

    return Unit_GetBattleFlagsNoDown(&gCharacters[characterId].unit);
}

// FUN_0016d8b0
void Character_AddBattleFlags(u16 characterId, u32 flags)
{
    if (IS_HERO(characterId))
    {
        Unit_AddBattleFlags(&gPlayerData.unit, flags);
        return;
    }

    Unit_AddBattleFlags(&gCharacters[characterId].unit, flags);
}

// FUN_0016d980
void Character_SetOldFatigueCounter(u16 characterId, u16 oldFatigueCounter)
{
    if (IS_HERO(characterId))
    {
        gPlayerData.physicalState.oldFatigueCounter = oldFatigueCounter;
        return;
    }

    gCharacters[characterId].physicalState.oldFatigueCounter = oldFatigueCounter;
}

// FUN_0016d9d0
void Character_RemoveBattleFlags(u16 characterId, u32 flags)
{
    if (IS_HERO(characterId))
    {
        Unit_RemoveBattleFlags(&gPlayerData.unit, flags);
    }

    Unit_RemoveBattleFlags(&gCharacters[characterId].unit, flags);
}

// FUN_0016d2f0
u32 Character_GetExpUntilNextLevel(u16 characterId)
{
    u32 nextExpTmp;
    u32 nextExp = gPlayerData.nextExp;
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

    for (i = 0; i < ARRAY_SIZE(playerNextExpThreshold); i++)
    {
        if (nextExp < playerNextExpThreshold[i]) break;
    }

    if (i == MAX_CHARACTER_LEVEL)
    {
        nextExp = 0;
    }

    if (i == 0 || i > MAX_CHARACTER_LEVEL)
    {
        P3FES_ASSERT("g_data.c", 876);
    }

    nextExp = playerNextExpThreshold[i];
    nextExpTmp = gPlayerData.nextExp;

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
        gPlayerData.nextExp += expGain;
        count = 0;

        for (i = 0; i < ARRAY_SIZE(playerNextExpThreshold); i++)
        {
            if (gPlayerData.nextExp < playerNextExpThreshold[i]) break;
            
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
    if (aiTacticId > MAX_AI_TACTIC_ID)
    {
        P3FES_ASSERT("g_data.c", 999);
    }

    if (IS_HERO(characterId))
    {
        gPlayerData.unit.status.aiTactic = aiTacticId;
        return;
    }

    gCharacters[characterId].unit.status.aiTactic = aiTacticId;
}

// FUN_0016dd80
u8 Character_GetAiTactic(u16 characterId)
{
    if (IS_HERO(characterId))
    {
        return gPlayerData.unit.status.aiTactic;
    }

    return gCharacters[characterId].unit.status.aiTactic;
}

// FUN_0016d6b0
void Character_SetPhysicalCondition(u16 characterId, u16 physicalCondition)
{
    u16 currentPhysicalCondition = gPlayerData.physicalState.physicalCondition;
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
        oldFatigueCounter = gPlayerData.physicalState.oldFatigueCounter;

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
        currentPhysicalCondition = gPlayerData.physicalState.physicalCondition;
    }

    gPlayerData.physicalState.physicalCondition = currentPhysicalCondition;
}

// FUN_0016d930
void Character_SetFatigueCounter(u16 characterId, u16 fatigueCounter)
{
    if (IS_HERO(characterId))
    {
        gPlayerData.physicalState.fatigueCounter = fatigueCounter;
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
        tmp = gPlayerData.unit.status.health;
    }

    gPlayerData.unit.status.health = tmp;
}

// FUN_0016e920
void Character_SetActiveSocialLink(u16 activeSocialLink)
{
    gPlayerData.activeSocialLink = activeSocialLink;
}

// FUN_0016ef20
u16 Calendar_GetDaysSinceApr5()
{
    return calendar.daysSinceApr5;
}

// FUN_0016ef30
u8 Calendar_GetTime()
{
    return calendar.time;
}

// FUN_0016ef40
u16 Calendar_GetDaysSkipTarget()
{
    return calendar.daysSkipTarget;
}

// FUN_0016ef50
u8 Calendar_GetTimeSkipTarget()
{
    return calendar.timeSkipTarget;
}

// FUN_0016ef60
u32 Calendar_GetSkipToTarget()
{
    return calendar.skipToTarget;
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
        gPlayerData.socialStats.academicPoint = academicPoint;
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
        Character_GetCharmLevel(gPlayerData.socialStats.charmPoint); // ??
        gPlayerData.socialStats.charmPoint = charmPoint;
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
        Character_GetCourageLevel(gPlayerData.socialStats.couragePoint); // ??
        gPlayerData.socialStats.couragePoint = couragePoint;
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
        gPlayerData.socialStats.academicPoint,
        gCharacters[characterId].socialStats.academicPoint);
}

// FUN_0016c6f0
u16 Character_GetCharmPoint(u16 characterId)
{
    return Inl_Character_GetSocialStatPoint(
        characterId,
        gPlayerData.socialStats.charmPoint,
        gCharacters[characterId].socialStats.charmPoint);
}

u16 Character_GetCouragePoint(u16 characterId)
{
    return Inl_Character_GetSocialStatPoint(
        characterId,
        gPlayerData.socialStats.couragePoint,
        gCharacters[characterId].socialStats.couragePoint);
}

// TODO
void FUN_0016ca90(u16 characterId, u16 param_2)
{
    u16 oldFatigueCounter = gPlayerData.physicalState.oldFatigueCounter;
    u16 fatigueCounter = gPlayerData.physicalState.fatigueCounter;
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

// FUN_0016cb80
u16 Character_GetEquipmentIdx(u16 characterId, u16 equipmentType)
{
    if (IS_HERO(characterId))
    {
        return gPlayerData.equipmentsData.equipmentsIdx[equipmentType];
    }

    return gCharacters[characterId].equipmentsIdx[equipmentType];
}

// FUN_0016f150
void Calendar_SetTime(u8 time)
{
    calendar.time = time;
}

// FUN_0016f160
void Calendar_SetDaysSkipTarget(u16 days)
{
    calendar.daysSkipTarget = days;
}

// FUN_0016f170
void Calendar_SetTimeSkipTarget(u8 time)
{
    calendar.timeSkipTarget = time;
}

// FUN_0016f180
void Calendar_SetSkipToTarget(u32 val)
{
    calendar.skipToTarget = val;
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
        P3FES_LOG3("hit \n");
    }

    idx = bit / 32;
    if ((s32)bit < 0)
    {
        idx = (s32)(bit + 0x1f) / 32;
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
    for (u32 i = 0; i < ARRAY_SIZE(gGlobalFlags); i++)
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
        return gPlayerData.equipmentsData.equipments[equipmentIdx].id;
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
        return gPlayerData.equipmentsData.equipments[equipmentIdx].effect;
    }
    else if (characterId <= 255)
    {
        return gCharacters[characterId].equipments[equipmentIdx].effect;
    }

    // return (equpementIdx * 0x14 + characterId * 0x364 + 0x7fd6d1);
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

// FUN_0016c7e0
u32 Character_GetNextExp(u16 characterId)
{
    PersonaData* persona;

    if (IS_HERO(characterId))
    {
        return gPlayerData.nextExp;
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
        return gPlayerData.physicalState.physicalCondition;
    }

    return gCharacters[characterId].physicalState.physicalCondition;
}

// FUN_0016dd40
u16 Player_GetActiveSocialLink()
{
    return gPlayerData.activeSocialLink;
}

// FUN_0016dba0
u8 Player_GetSocialLinkLevel(u16 socialLink)
{
    return gPlayerData.socialLinkStat[socialLink];
}

// FUN_0016e100
u8 Player_SocialLinkLevelIsNotZero(u16 socialLink)
{
    if (socialLink < SOCIAL_LINK_SEES || socialLink > SOCIAL_LINK_NYX_TEAM)
    {
        P3FES_ASSERT("g_data.c", 1429);
    }

    return gPlayerData.socialLinkStat[socialLink] > 0;
}

// TODO
void FUN_0016e670(u16 socialLink)
{
    if (socialLink < SOCIAL_LINK_SEES || socialLink > SOCIAL_LINK_NYX_TEAM)
    {
    }

    if (Player_GetSocialLinkLevel(socialLink) < 1)
    {
        //printf("no exist comu %s %d", "g_data.c", 1568);
    }
    else
    {
        
    }
}

// FUN_0017c8c0
PersonaData* Player_GetPersonaByCompendiumIdx(u32 idx)
{
    if (idx < 0 || idx > 255)
    {
        P3FES_ASSERT("g_data.c", 6177);
    }

    if (!(gPlayerData.compendium[idx].flags & PERSONA_FLAG_VALID))
    {
        return NULL;
    }

    return &gPlayerData.compendium[idx];
}

void P3FES_ASSERT(const u8* file, const u32 line)
{
    // Probably an assert function. 
    // It's empty because it's only used if the game was compiled in debug
    // which is not the case here.
    return;
}

// FUN_001052b0
void P3FES_LOG1(const char* fmt, ...)
{
    // ...
}

// FUN_005225a8
void P3FES_LOG3(const char* fmt, ...)
{
    // ...
}