#include "g_data.h"
#include "datPersona.h"
#include "datCalc.h"

#include <stdlib.h>

const u8* courageLevelString[] =
{
    "Timid", "Ordinary", "Determined", "Though", "Fearless", "Badass"
};

const u8* charmLevelString[] =
{   
    "Plain", "Unpolished", "Confident", "Smooth", "Popular", "Charismatic"
};

const u8* academicLevelString[] = 
{
    "Slacker", "Average", "Above Average", "Smart", "Intelligent", "Genius"
};

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

static const u16 numOfDaysInMonths[12] =
{ /*JAN FEB MAR APR MAY JUN JUL AUG SEP OCT NOV DEC*/
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
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

static u32 gIUnkArr[128]; // TODO

// 007cdfa4. It's probably in a struct. See enum GameScenario
static u32 scenarioMode;

// TODO
void FUN_0016f3e0(u32 idx, u32 value)
{
    if (idx > 127)
    {
        P3FES_ASSERT("g_data.c", 2007);
    }

    gIUnkArr[idx] = value;
}

// FUN_00521408
void* P3FES_Memset(void* dst, u8 value, u32 size)
{
    // TODO

    for (u32 i = 0; i < size; i++)
    {
        ((u8*)dst)[i] = value;
    }

    return dst;
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

    return characters[characterId]->persona.id;
}

// FUN_0016cdf0
void FUN_0016cdf0(u16 characterId)
{
    if (IS_HERO(characterId))
    {
        P3FES_Memset(&gPlayerData, 0, 60);
        gPlayerData.character.battleStatus.aiTactic = AI_TACTIC_ACT_FREELY;
        gPlayerData.character.id = CHARACTER_HERO;
        gPlayerData.character.sUnk1 = 1;
    }
    else 
    {
        P3FES_Memset(characters[characterId], 0, 60);
        characters[characterId]->character.id = characterId;
        characters[characterId]->character.battleStatus.aiTactic = AI_TACTIC_ACT_FREELY;
        characters[characterId]->character.sUnk1 = 1;
    }
}

// FUN_0017d7f0
void Game_SetScenarioMode(u32 scenario)
{
    scenarioMode = scenario;
}

// FUN_0017d800
u32 Game_GetScenarioMode()
{
    return scenarioMode;
}

// FUN_0016cd60
CharacterHeader* Character_GetCharacterHeader(u16 characterId)
{
    if (IS_HERO(characterId))
    {
        return &gPlayerData.character;
    }

    if (characterId < MAX_CHARACTERS)
    {
        return &characters[characterId]->character;
    }

    P3FES_ASSERT("g_data.c", 737);
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

// FUN_0016f150
void Calendar_SetTime(u8 time)
{
    calendar.time = time;
}

u32 Calendar_GetCurrentDay(u32 monthAndDay)
{
    return (monthAndDay + CALENDAR_DAY_MAX) % CALENDAR_DAY_MAX;
}

// FUN_0016c470
u8 Character_GetLevel(u16 characterId)
{
    if (IS_HERO(characterId))
    {
        return Character_GetLevel_Impl(&gPlayerData.character);
    }
    else 
    {
        return Character_GetLevel_Impl(&characters[characterId]->character);
    }
}

// FUN_0016c970
u32 Character_GetBattleFlagsNoDown(u16 characterId)
{
    if (IS_HERO(characterId))
    {
        return Character_GetBattleFlagsNoDown_Impl(&gPlayerData.character);
    }
    else
    {
        return Character_GetBattleFlagsNoDown_Impl(&characters[characterId]->character);
    }
}

// FUN_0016d8b0
void Character_AddBattleFlags(u16 characterId, u32 flags)
{
    if (IS_HERO(characterId))
    {
        Character_AddBattleFlags_Impl(&gPlayerData.character, flags);
    }
    else
    {
        Character_AddBattleFlags_Impl(&characters[characterId]->character, flags);
    }
}

// FUN_0016d980
void Character_SetOldFatigueCounter(u16 characterId, u16 oldFatigueCounter)
{
    if (IS_HERO(characterId))
    {
        gPlayerData.physicalState.oldFatigueCounter = oldFatigueCounter;
        return;
    }

    characters[characterId]->physicalState.oldFatigueCounter = oldFatigueCounter;
}

// FUN_0016d9d0
void Character_RemoveBattleFlags(u16 characterId, u32 flags)
{
    if (IS_HERO(characterId))
    {
        Character_RemoveBattleFlags_Impl(&gPlayerData.character, flags);
    }
    else 
    {
        Character_RemoveBattleFlags_Impl(&characters[characterId]->character, flags);
    }
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
        gPlayerData.character.battleStatus.aiTactic = aiTacticId;
        return;
    }

    characters[characterId]->character.battleStatus.aiTactic = aiTacticId;
}

// FUN_0016dd80
u8 Character_GetAiTactic(u16 characterId)
{
    if (IS_HERO(characterId))
    {
        return gPlayerData.character.battleStatus.aiTactic;
    }

    return characters[characterId]->character.battleStatus.aiTactic;
}

// FUN_0016d6b0
void Character_SetPhysicalCondition(u16 characterId, u16 physicalCondition)
{
    u16 currentPhysicalCondition = gPlayerData.physicalState.physicalCondition;
    u16 oldFatigueCounter;

    if (!IS_HERO(characterId))
    {
        currentPhysicalCondition = characters[characterId]->physicalState.physicalCondition;
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
            oldFatigueCounter = characters[characterId]->physicalState.oldFatigueCounter;
        }

        Character_SetFatigueCounter(characterId, oldFatigueCounter);
    }

    currentPhysicalCondition = physicalCondition;

    if (!IS_HERO(characterId))
    {
        characters[characterId]->physicalState.physicalCondition = physicalCondition;
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

    characters[characterId]->physicalState.fatigueCounter = fatigueCounter;
}

void Character_SetHealth(u16 characterId, u16 health)
{
    u16 tmp = health;

    if (!IS_HERO(characterId))
    {
        characters[characterId]->character.battleStatus.health = health;
        tmp = gPlayerData.character.battleStatus.health;
    }

    gPlayerData.character.battleStatus.health = tmp;
}

// FUN_0016e920
void Character_SetActiveSocialLink(u16 activeSocialLink)
{
    gPlayerData.activeSocialLink = activeSocialLink;
}

// FUN_0016cfe0
void Character_SetAcademicPoint(u16 characterId, u16 academicPoint)
{
    if (academicPoint < SOCIAL_STAT_MIN_POINT || academicPoint > SOCIAL_STAT_MAX_POINT)
    {
        P3FES_ASSERT("g_data.c", 797);
    }

    if (!IS_HERO(characterId))
    {
        gPlayerData.socialStats.academicPoint = academicPoint;
        return;
    }

    characters[characterId]->socialStats.academicPoint = academicPoint;
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

    characters[characterId]->socialStats.charmPoint = charmPoint;
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

    characters[characterId]->socialStats.couragePoint = couragePoint;
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
        characters[characterId]->socialStats.academicPoint);
}

// FUN_0016c6f0
u16 Character_GetCharmPoint(u16 characterId)
{
    return Inl_Character_GetSocialStatPoint(
        characterId,
        gPlayerData.socialStats.charmPoint,
        characters[characterId]->socialStats.charmPoint);
}

u16 Character_GetCouragePoint(u16 characterId)
{
    return Inl_Character_GetSocialStatPoint(
        characterId,
        gPlayerData.socialStats.couragePoint,
        characters[characterId]->socialStats.couragePoint);
}

// TODO
void FUN_0016ca90(u16 characterId, u16 param_2)
{
    u16 oldFatigueCounter = gPlayerData.physicalState.oldFatigueCounter;
    u16 fatigueCounter = gPlayerData.physicalState.fatigueCounter;
    s32 uVar3;

    if (!IS_HERO(characterId))
    {
        oldFatigueCounter = characters[characterId]->physicalState.oldFatigueCounter;
        fatigueCounter = characters[characterId]->physicalState.fatigueCounter;
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
u16 Character_GetEquipementIdx(u16 characterId, u16 equipementType)
{
    if (IS_HERO(characterId))
    {
        return gPlayerData.equipementsData.equipementsIdx[equipementType];
    }

    return characters[characterId]->equipementsIdx[equipementType];
}

// FUN_0016f630
u16 Character_GetEquipementId(u16 characterId, u16 equipementIdx)
{
    // TODO
    if (characterId == -1) // ?
    {
        // return (&DAT_00833e80)[equipementIdx * 10];
    }
    else if (IS_HERO(characterId))
    {
        return gPlayerData.equipementsData.equipements[equipementIdx].id;
    }
    else if (characterId <= 255)
    {
        return characters[characterId]->equipements[equipementIdx].id;
    }

    // return (&DAT_007fd6c8 + equipementIdx * 0x14 + characterId * 0x364);
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

    return characters[characterId]->physicalState.physicalCondition;
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
        printf("no exist comu %s %d", "g_data.c", 1568);
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

    if (!(gPlayerData.compendium[idx].flags & 1))
    {
        return NULL;
    }
    else 
    {
        return &gPlayerData.compendium[idx];
    }
}

// FUN_0017d8b0
u8 Calendar_GetDaysSinceStartFromDate(u32 month, u32 day)
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

// FUN_0017e480
u8 Calendar_IsDateOutsideRange(u32 startMonth, u32 startDay, u32 endMonth, u32 endDay)
{
    u32 startDate = Calendar_GetDaysSinceStartFromDate(startMonth, startDay);
    u32 endDate = Calendar_GetDaysSinceStartFromDate(endMonth, endDay);
    u16 currDaysSinceApr5 = Calendar_GetDaysSinceApr5();
    u8 isOutsideRange;

    if (currDaysSinceApr5 < startDate || endDate < currDaysSinceApr5)
    {
        isOutsideRange = false;
    }
    else 
    {
        isOutsideRange = true;
    }

    return isOutsideRange;
}

// FUN_0011a870
const u8* gData_getCourageLevelString(u16 idx)
{
    return courageLevelString[idx];
}
const u8* gData_getCharmLevelString(u16 idx)
{
    return charmLevelString[idx];
}
const u8* gData_getAcademicLevelString(u16 idx)
{
    return academicLevelString[idx];
}

void P3FES_ASSERT(const u8* file, const u32 line)
{
    // Probably an assert function. 
    // It's empty because it's only used if the game was compiled in debug
    // which is not the case here.
    return;
}