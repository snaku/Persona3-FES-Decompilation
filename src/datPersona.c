#include "datPersona.h"
#include <stdlib.h>

// FUN_001732f0
u8 Persona_GetPersonaLevel(PersonaData* persona)
{
    return persona->level;
}

// FUN_00173330
u32 Persona_GetPersonaNextExp(PersonaData* persona)
{
    return persona->nextExp;
}

// FUN_00174800
PersonaData* Persona_GetPersonaByCharacterId(u16 characterId)
{
    PersonaData* persona;

    if (IS_HERO(characterId))
    {
        persona = Persona_GetHeroPersona(gPlayerData.equippedPersona);
    }
    else 
    {
        if (characterId > MAX_CHARACTERS)
        {
            P3FES_ASSERT("datPersona.c", 779);
        }

        persona = &characters[characterId]->persona;
    }

    if (persona == NULL)
    {
        P3FES_ASSERT("datPersona.c", 783);
    }

    return persona;
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

    if (!(gPlayerData.personas[heroPersonaIdx].flags & 1))
    {
        persona = NULL;
    }
    else 
    {
        persona = &gPlayerData.personas[heroPersonaIdx];
    }
    
    return persona;
}

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
    u32 skillIdx;

    if (persona == NULL || skillId == PERSONA_SKILL_SLASH_ATTACK)
    {
        P3FES_ASSERT("datPersona.c", 1546);
    }

    for (skillIdx = 0; skillIdx < ARRAY_SIZE(persona); skillIdx++)
    {
        if (persona->skills[skillIdx] == PERSONA_SKILL_SLASH_ATTACK)
        {
            persona->skills[skillIdx] = skillId;
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