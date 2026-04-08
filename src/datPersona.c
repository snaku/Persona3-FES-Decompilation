#include "datPersona.h"
#include "g_data.h"
#include "temporary.h"
#include "Kosaka/k_assert.h"

// FUN_001732f0
u8 datPersonaGetLevel(DatPersonaWork* persona)
{
    return persona->level;
}

// FUN_00173300
u8 datPersonaGetLevelCharacterId(u16 characterId)
{
    DatPersonaWork* persona = datPersonaGetPersonaByCharacterId(characterId);
    return persona->level;
}

// FUN_00173330
u32 datPersonaGetNextExp(DatPersonaWork* persona)
{
    return persona->nextExp;
}

// FUN_00173370
u16* datPersonaGetSkills(DatPersonaWork* persona)
{
    return persona->skills;
}

// FUN_00173380
u16* datPersonaGetSkillsByCharacterId(u16 characterId)
{
    DatPersonaWork* persona = datPersonaGetPersonaByCharacterId(characterId);

    return persona->skills;
}

// FUN_00173580
u16 datPersonaGetTotalStat(DatPersonaWork* persona, u16 statId)
{
    u16 naturalStat = datPersonaGetNaturalStat(persona, statId);
    u16 bonusStat = datPersonaGetBonusStat(persona, statId);
    u16 stat3 = datPersonaGetStat3(persona, statId);

    u16 total = naturalStat + bonusStat + stat3;

    if (total > 99)
    {
        return 99;
    }

    return total;
}

// was probably inlined
u8 datPersonaGetNaturalStat(DatPersonaWork* persona, u16 statId)
{
    K_ASSERT(statId < PERSONA_STAT_MAX, 316);

    return persona->naturalStats[statId];
}

// FUN_00173b00
u8 datPersonaGetBonusStat(DatPersonaWork* persona, u16 statId)
{
    K_ASSERT(statId < PERSONA_STAT_MAX, 454);

    return persona->bonusStats[statId];
}

// FUN_00173b60
void datPersonaSetBonusStatByCharacterId(u16 characterId, u16 statId, u8 amount)
{
    DatPersonaWork* persona = datPersonaGetPersonaByCharacterId(characterId);

    persona->bonusStats[statId] = amount;
}

// FUN_00173bb0
void datPersonaAddToBonusStatByCharacterId(u16 characterId, u16 statId, s8 amount)
{
    DatPersonaWork* persona = datPersonaGetPersonaByCharacterId(characterId);

    persona->bonusStats[statId] += amount;
}

// FUN_00173c00
u8 datPersonaGetStat3(DatPersonaWork* persona, u16 statId)
{
    K_ASSERT(statId <= PERSONA_STAT_LUCK, 503);

    return persona->stats3[statId];
}

// FUN_00174650
u16 datPersonaAddToNaturalStat(DatPersonaWork* persona, u16 statId, s8 amount)
{
    u8 statTotal;

    K_ASSERT(statId <= PERSONA_STAT_LUCK, 722);
    
    statTotal = persona->naturalStats[statId] + amount;
    if (statTotal < 100)
    {
        if (statTotal < 0)
        {
            statTotal = 0;
        }
    }
    else 
    {
        statTotal = 99;
    }

    persona->naturalStats[statId] = statTotal;

    return statTotal;
}

// FUN_00174710
u16 datPersonaAddToNaturalStatHeroPersona(u16 heroPersonaIdx, u16 statId, s8 amount)
{
    u8 statTotal;
    DatPersonaWork* heroPersona = datPersonaGetHeroPersona(heroPersonaIdx);

    K_ASSERT(heroPersona != NULL, 747);

    return datPersonaAddToNaturalStat(heroPersona, statId, amount); // was inlined
}

// FUN_00174800
DatPersonaWork* datPersonaGetByCharacterId(u16 characterId)
{
    DatPersonaWork* persona;

    if (IS_HERO(characterId))
    {
        persona = datPersonaGetHeroPersona(gPlayerPersonaData.equippedPersona);
    }
    else 
    {
        K_ASSERT(characterId < CHARACTER_MAX, 779);

        persona = &gCharacters[characterId].persona;
    }

    K_ASSERT(persona != NULL, 783);

    return persona;
}

// FUN_00174960
u8 datPersonaHeroPersonaValid(u16 heroPersonaIdx)
{
    return (gPlayerPersonaData.personas[heroPersonaIdx].flags & PERSONA_FLAG_VALID);
}

// FUN_00174a90
DatPersonaWork* datPersonaGetHeroPersona(u16 heroPersonaIdx)
{
    DatPersonaWork* persona;

    /* TODO
    if (((long)heroPersonaIdx < 0) || (uVar3 = FUN_00175410(), (long)(uVar3 & 0xffff) <= (long)heroPersonaIdx)) 
    {
        K_Assert("datPersona.c", 848);
    }*/

    if (!datPersonaIsHeroPersonaValid(heroPersonaIdx))
    {
        persona = NULL;
    }
    else 
    {
        persona = &gPlayerPersonaData.personas[heroPersonaIdx];
    }
    
    return persona;
}

// FUN_001757f0
void datPersonaClearHeroPersonas()
{
    memset(gPlayerPersonaData.personas, 0, sizeof(gPlayerPersonaData.personas));
}

// FUN_001764b0
void datPersonaAddExp(DatPersonaWork* persona, u32 exp)
{
    K_ASSERT(exp > 0, 1458);

    persona->nextExp += exp;
}

// FUN_00176510
void datPersonaMoveValidSkillsOnTop(DatPersonaWork* persona)
{
    u32 skillIdx;
    u32 nextSkillIdx = 0;

    K_ASSERT(persona != NULL, 1478);

    for (skillIdx = 0; skillIdx < ARRAY_SIZE(persona->skills); skillIdx++)
    {
        if (persona->skills[skillIdx] == PERSONA_SKILL_SLASH_ATTACK)
        {
            nextSkillIdx = skillIdx + 1;

            while (nextSkillIdx < ARRAY_SIZE(persona->skills) &&
                  (persona->skills[nextSkillIdx] == PERSONA_SKILL_SLASH_ATTACK))
            {
                nextSkillIdx++;
            }

            if (nextSkillIdx == ARRAY_SIZE(persona->skills)) return;
        }

        if (skillIdx != nextSkillIdx)
        {
            persona->skills[skillIdx] = persona->skills[nextSkillIdx];
            persona->skills[nextSkillIdx] = PERSONA_SKILL_SLASH_ATTACK;
        }
    }
}

// FUN_00176840
u8 datPersonaSetSkill(DatPersonaWork* persona, u16 skillId)
{
    s32 skillIdx;
    u16* skillSlot;

    K_ASSERT(persona != NULL && skillId != PERSONA_SKILL_SLASH_ATTACK, 1546);

    for (skillIdx = 0; skillIdx < PERSONA_MAX_SKILLS; skillIdx++)
    {
        skillSlot = &persona->skills[skillIdx];
        if (*skillSlot == PERSONA_SKILL_SLASH_ATTACK)
        {
            *skillSlot = skillId;
            return true;
        }
    }

    return false;
}

// FUN_001768e0
u8 datPersonaResetSkill(DatPersonaWork* persona, u16 skillId)
{
    u32 skillIdx;

    K_ASSERT(persona != NULL && skillId != PERSONA_SKILL_SLASH_ATTACK, 1560);

    for (skillIdx = 0; skillIdx < ARRAY_SIZE(persona->skills); skillIdx++)
    {
        if (persona->skills[skillIdx] == skillId)
        {
            persona->skills[skillIdx] = PERSONA_SKILL_SLASH_ATTACK;
            datPersonaMoveValidSkillsOnTop(persona);
            return true;
        }
    }
    return false;
}

// FUN_00176990
s32 datPersonaFindSkillIdx(DatPersonaWork* persona, u16 skillId)
{
    s32 skillIdx = 0;

    K_ASSERT(persona != NULL && skillId != PERSONA_SKILL_SLASH_ATTACK, 1588);

    for (skillIdx = 0; skillIdx < ARRAY_SIZE(persona->skills); skillIdx++)
    {
        if (persona->skills[skillIdx] == skillId)
            return skillIdx;
    }

    return -1;
}

// FUN_00176a30
u32 datPersonaCountValidSkills(DatPersonaWork* persona)
{
    u32 skillIdx;
    u32 validSkills = 0;

    K_ASSERT(persona != NULL, 1601);

    for (skillIdx = 0; skillIdx < ARRAY_SIZE(persona->skills); skillIdx++)
    {
        if (persona->skills[skillIdx] != PERSONA_SKILL_SLASH_ATTACK)
            validSkills++;
    }

    return validSkills;
}