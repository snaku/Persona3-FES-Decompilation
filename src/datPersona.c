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

// FUN_00176990
s32 Persona_FindPersonaSkillIdx(PersonaData* persona, u16 skillId)
{
    s32 skillIdx = 0;

    if (persona == NULL || skillId == 0)
    {
        P3FES_ASSERT("datPersona.c", 1588);
    }

    while (true)
    {
        if (skillIdx > 7) return -1; // max idx is 7
        if (persona->skills[skillIdx] == skillId) break;

        skillIdx++;
    }

    return skillIdx;
}