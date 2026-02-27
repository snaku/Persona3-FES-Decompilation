#include "datPersona.h"
#include "g_data.h"
#include "temporary.h"

// FUN_001732f0
u8 Persona_GetPersonaLevel(PersonaData* persona)
{
    return persona->level;
}

// FUN_00173300
u8 Persona_GetPersonaLevelCharacterId(u16 characterId)
{
    PersonaData* persona = Persona_GetPersonaByCharacterId(characterId);
    return persona->level;
}

// FUN_00173330
u32 Persona_GetPersonaNextExp(PersonaData* persona)
{
    return persona->nextExp;
}

// FUN_00173370
u16* Persona_GetSkills(PersonaData* persona)
{
    return persona->skills;
}

// FUN_00173380
u16* Persona_GetSkillsByCharacterId(u16 characterId)
{
    PersonaData* persona = Persona_GetPersonaByCharacterId(characterId);

    return persona->skills;
}

// FUN_00173580
u16 Persona_GetTotalStat(PersonaData* persona, u16 statId)
{
    u16 naturalStat = Persona_GetNaturalStat(persona, statId);
    u16 bonusStat = Persona_GetBonusStat(persona, statId);
    u16 stat3 = Persona_GetStat3(persona, statId);

    u16 total = naturalStat + bonusStat + stat3;

    if (total > 99)
    {
        return 99;
    }

    return total;
}

// was probably inlined
u8 Persona_GetNaturalStat(PersonaData* persona, u16 statId)
{
    if (statId >= PERSONA_STAT_MAX)
    {
        P3FES_ASSERT("datPersona.c", 316);
    }

    return persona->naturalStats[statId];
}

// FUN_00173b00
u8 Persona_GetBonusStat(PersonaData* persona, u16 statId)
{
    if (statId >= PERSONA_STAT_MAX)
    {
        P3FES_ASSERT("datPersona.c", 454);
    }

    return persona->bonusStats[statId];
}

// FUN_00173b60
void Persona_SetBonusStatByCharacterId(u16 characterId, u16 statId, u8 amount)
{
    PersonaData* persona = Persona_GetPersonaByCharacterId(characterId);

    persona->bonusStats[statId] = amount;
}

// FUN_00173bb0
void Persona_AddToBonusStatByCharacterId(u16 characterId, u16 statId, s8 amount)
{
    PersonaData* persona = Persona_GetPersonaByCharacterId(characterId);

    persona->bonusStats[statId] += amount;
}

// FUN_00173c00
u8 Persona_GetStat3(PersonaData* persona, u16 statId)
{
    if (statId > PERSONA_STAT_LUCK)
    {
        P3FES_ASSERT("datPersona.c", 503);
    }

    return persona->stats3[statId];
}

// FUN_00174650
u16 Persona_AddToNaturalStat(PersonaData* persona, u16 statId, s8 amount)
{
    u8 statTotal;

    if (statId > PERSONA_STAT_LUCK)
    {
        P3FES_ASSERT("datPersona.c", 722);
    }
    
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
u16 Persona_AddToNaturalStatHeroPersonaIdx(u16 heroPersonaIdx, u16 statId, s8 amount)
{
    u8 statTotal;
    PersonaData* heroPersona = Persona_GetHeroPersona(heroPersonaIdx);

    if (heroPersona == NULL)
    {
        P3FES_ASSERT("datPersona.c", 747);
    }

    return Persona_AddToNaturalStat(heroPersona, statId, amount); // was inlined
}

// FUN_00174800
PersonaData* Persona_GetPersonaByCharacterId(u16 characterId)
{
    PersonaData* persona;

    if (IS_HERO(characterId))
    {
        persona = Persona_GetHeroPersona(gPlayerPersonaData.equippedPersona);
    }
    else 
    {
        if (characterId >= CHARACTER_MAX)
        {
            P3FES_ASSERT("datPersona.c", 779);
        }

        persona = &gCharacters[characterId].persona;
    }

    if (persona == NULL)
    {
        P3FES_ASSERT("datPersona.c", 783);
    }

    return persona;
}

// FUN_00174960
u8 Persona_IsHeroPersonaValid(u16 heroPersonaIdx)
{
    return (gPlayerPersonaData.personas[heroPersonaIdx].flags & PERSONA_FLAG_VALID);
}

// FUN_00174a90
PersonaData* Persona_GetHeroPersona(u16 heroPersonaIdx)
{
    PersonaData* persona;

    /* TODO
    if (((long)heroPersonaIdx < 0) || (uVar3 = FUN_00175410(), (long)(uVar3 & 0xffff) <= (long)heroPersonaIdx)) 
    {
        P3FES_ASSERT("datPersona.c", 848);
    }*/

    if (!Persona_IsHeroPersonaValid(heroPersonaIdx))
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
void Persona_ClearHeroPersonas()
{
    memset(gPlayerPersonaData.personas, 0, sizeof(gPlayerPersonaData.personas));
}

// FUN_001764b0
void Persona_AddExp(PersonaData* persona, u32 exp)
{
    if (exp < 0)
    {
        P3FES_ASSERT("datPersona.c", 1458);
    }

    persona->nextExp += exp;
}

// FUN_00176510
void Persona_MoveValidSkillsOnTop(PersonaData* persona)
{
    u32 skillIdx;
    u32 nextSkillIdx = 0;

    if (persona == NULL)
    {
        P3FES_ASSERT("datPersona.c", 1478);
    }

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
u8 Persona_SetSkill(PersonaData* persona, u16 skillId)
{
    s32 skillIdx;
    u16* skillSlot;

    if (persona == NULL || skillId == PERSONA_SKILL_SLASH_ATTACK)
    {
        P3FES_ASSERT("datPersona.c", 1546);
    }

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
u8 Persona_ResetSkill(PersonaData* persona, u16 skillId)
{
    u32 skillIdx;

    if (persona == NULL || skillId == PERSONA_SKILL_SLASH_ATTACK)
    {
        P3FES_ASSERT("datPersona.c", 1560);
    }

    for (skillIdx = 0; skillIdx < ARRAY_SIZE(persona->skills); skillIdx++)
    {
        if (persona->skills[skillIdx] == skillId)
        {
            persona->skills[skillIdx] = PERSONA_SKILL_SLASH_ATTACK;
            Persona_MoveValidSkillsOnTop(persona);
            return true;
        }
    }
    return false;
}

// FUN_00176990
s32 Persona_FindPersonaSkillIdx(PersonaData* persona, u16 skillId)
{
    s32 skillIdx = 0;

    if (persona == NULL || skillId == PERSONA_SKILL_SLASH_ATTACK)
    {
        P3FES_ASSERT("datPersona.c", 1588);
    }

    for (skillIdx = 0; skillIdx < ARRAY_SIZE(persona->skills); skillIdx++)
    {
        if (persona->skills[skillIdx] == skillId)
            return skillIdx;
    }

    return -1;
}

// FUN_00176a30
u32 Persona_CountValidSkills(PersonaData* persona)
{
    u32 skillIdx;
    u32 validSkills = 0;
    
    if (persona == NULL)
    {
        P3FES_ASSERT("datPersona.c", 1601);
    }

    for (skillIdx = 0; skillIdx < ARRAY_SIZE(persona->skills); skillIdx++)
    {
        if (persona->skills[skillIdx] != PERSONA_SKILL_SLASH_ATTACK)
            validSkills++;
    }

    return validSkills;
}