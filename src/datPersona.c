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

    if (!(gPlayerData.personas[heroPersonaIdx].sUnk1 & 1))
    {
        persona = NULL;
    }
    else 
    {
        persona = &gPlayerData.personas[heroPersonaIdx];
    }
    
    return persona;
}