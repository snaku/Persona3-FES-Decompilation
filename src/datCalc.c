#include "datCalc.h"
#include <stdlib.h>

// FUN_002ffcc0
u8 Character_GetLevel_Impl(CharacterHeader* characterHeader){
    u8 level;
    PersonaData* persona;

    if (!(characterHeader->sUnk1 & 4) && !IS_HERO(characterHeader->id))
    {
        persona = Persona_GetPersonaByCharacterId(characterHeader->id);
        if (persona == NULL)
        {
            P3FES_ASSERT("datCalc.c", 66);
        }

        level = Persona_GetPersonaLevel(persona);
    }
    else 
    {
        level = characterHeader->battleStatus.level;
    }

    if (level == 0)
    {
        P3FES_ASSERT("datCalc.c", 70);
    }

    return level;
}

// FUN_003004f0
void Character_AddBattleFlags_Impl(CharacterHeader* characterHeader, u32 flags)
{
    const u32 LOW_20_BITS = 0x000FFFFF;
    const u32 HIGH_12_BITS = 0xFFF00000;

    if ((flags & LOW_20_BITS) != 0)
    {
        characterHeader->battleStatus.flags = (characterHeader->battleStatus.flags & HIGH_12_BITS) | (flags & LOW_20_BITS);
    }

    characterHeader->battleStatus.flags |= (flags & HIGH_12_BITS);
}

// FUN_00300530
u32 Character_GetBattleFlagsNoDown_Impl(CharacterHeader* characerHeader)
{
    // without bit 20 and over (so BATTLE_FLAG_DOWN)
    return characerHeader->battleStatus.flags & 0x000FFFFF;
}

// FUN_00300550
u32 Character_GetBattleFlags(CharacterHeader* characterHeader)
{
    return characterHeader->battleStatus.flags;
}

// FUN_00300560
void Character_RemoveBattleFlags_Impl(CharacterHeader* characterHeader, u32 flags)
{
    characterHeader->battleStatus.flags &= ~flags;
}

// FUN_00300580
u8 Character_HasBattleFlags(CharacterHeader* characterHeader, u32 flags)
{
    return (characterHeader->battleStatus.flags & flags);
}

// FUN_0030b5a0
u8 Character_IsCharacterDead(CharacterHeader* characterHeader, s32 param_2)
{
    u8 isDead;

    if (!Character_HasBattleFlags(characterHeader, BATTLE_FLAG_DEAD))
    {
        isDead = characterHeader->battleStatus.health < 1;
    }
    else
    {
        isDead = true;
    }

    return isDead;
}

void FUN_0030c440()
{
    // TODO
    for (u16 i = CHARACTER_HERO; i < CHARACTER_MAX; i++)
    {
        // FUN_0030c490
    }
}