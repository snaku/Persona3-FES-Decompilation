#include "datCalc.h"
#include <stdlib.h>

// FUN_002ffcc0
u8 BtlActor_GetLevel(BattleActorData* btlActor){
    u8 level;
    PersonaData* persona;

    if (!(btlActor->flags & 4) && !IS_HERO(btlActor->id))
    {
        persona = Persona_GetPersonaByCharacterId(btlActor->id);
        if (persona == NULL)
        {
            P3FES_ASSERT("datCalc.c", 66);
        }

        level = Persona_GetPersonaLevel(persona);
    }
    else 
    {
        level = btlActor->battleStatus.level;
    }

    if (level == 0)
    {
        P3FES_ASSERT("datCalc.c", 70);
    }

    return level;
}

// FUN_002ffd70
u16 BtlActor_GetHealth(BattleActorData* btlActor)
{
    return btlActor->battleStatus.health;
}

// FUN_002ffd80
u16 BtlActor_GetSp(BattleActorData* btlActor)
{
    return btlActor->battleStatus.sp;
}

// FUN_002ffd90
void BtlActor_SetHealth(BattleActorData* btlActor, u16 health)
{
    if (health > 999 && !(btlActor->flags & (1 << 2)))
    {
        health = 999;
    }

    btlActor->battleStatus.health = health;
}

// FUN_002ffdc0
void BtlActor_SetSp(BattleActorData* btlActor, u16 sp)
{
    if (sp > 999 && !(btlActor->flags & (1 << 2)))
    {
        sp = 999;
    }

    btlActor->battleStatus.sp = sp;
}

// FUN_003004f0
void BtlActor_AddBattleFlags(BattleActorData* btlActor, u32 flags)
{
    const u32 LOW_20_BITS = 0x000FFFFF;
    const u32 HIGH_12_BITS = 0xFFF00000;

    if (!(flags & LOW_20_BITS))
    {
        btlActor->battleStatus.flags = (btlActor->battleStatus.flags & HIGH_12_BITS) |
                                       (flags & LOW_20_BITS);
    }

    btlActor->battleStatus.flags |= (flags & HIGH_12_BITS);
}

// FUN_00300530
u32 BtlActor_GetBattleFlagsNoDown(BattleActorData* btlActor)
{
    // without bit 20 and over (so BATTLE_FLAG_DOWN)
    return btlActor->battleStatus.flags & 0x000FFFFF;
}

// FUN_00300550
u32 BtlActor_GetBattleFlags(BattleActorData* btlActor)
{
    return btlActor->battleStatus.flags;
}

// FUN_00300560
void BtlActor_RemoveBattleFlags(BattleActorData* btlActor, u32 flags)
{
    btlActor->battleStatus.flags &= ~flags;
}

// FUN_00300580
u8 BtlActor_HasBattleFlags(BattleActorData* btlActor, u32 flags)
{
    return (btlActor->battleStatus.flags & flags);
}

// FUN_00308c60
u32 BtlActor_GetHeldWeaponType(BattleActorData* btlActor)
{
    u16 heroWeaponIdx;
    u16 heroWeaponId;
    u16 heroWeaponUnkFlag;

    if (btlActor->flags & (1 << 2))
    {
        return WEAPON_TYPE_1H_SWORD;
    }

    switch (btlActor->id)
    {
        case CHARACTER_HERO:
            heroWeaponIdx = Character_GetEquipementIdx(CHARACTER_HERO, EQUIPEMENT_TYPE_WEAPON);
            heroWeaponId = Character_GetEquipementId(CHARACTER_HERO, heroWeaponIdx);
            // unkStruct = FUN_00170d60(heroWeaponId);
            // heroWeaponUnkFlag = unkStruct->flags;
            if (heroWeaponUnkFlag & (1 << 15) || heroWeaponUnkFlag & (1 << 7))
                return WEAPON_TYPE_KNIFE;
            if (heroWeaponUnkFlag & (1 << 14) || heroWeaponUnkFlag & (1 << 6))
                return WEAPON_TYPE_GUN;
            if (heroWeaponUnkFlag & (1 << 13) || heroWeaponUnkFlag & (1 << 5))
                return WEAPON_TYPE_FIST;
            if (heroWeaponUnkFlag & (1 << 12) || heroWeaponUnkFlag & (1 << 4))
                return WEAPON_TYPE_AXE;
            if (heroWeaponUnkFlag & (1 << 11) || heroWeaponUnkFlag & (1 << 3))
                return WEAPON_TYPE_SPEAR;
            if (heroWeaponUnkFlag & (1 << 10) || heroWeaponUnkFlag & (1 << 2))
                return WEAPON_TYPE_BOW;
            if (heroWeaponUnkFlag & (1 << 9) || heroWeaponUnkFlag & (1 << 1))
                return WEAPON_TYPE_1H_SWORD;
            if (heroWeaponUnkFlag & (1 << 8) || heroWeaponUnkFlag & (1 << 0))
                return WEAPON_TYPE_2H_SWORD;

            P3FES_ASSERT("datCalc.c", 4237);
        case CHARACTER_YUKARI:            return WEAPON_TYPE_BOW;
        case CHARACTER_AIGIS:             return WEAPON_TYPE_GUN;
        case CHARACTER_MITSURU:           return WEAPON_TYPE_1H_SWORD;
        case CHARACTER_JUNPEI:            return WEAPON_TYPE_2H_SWORD;
        case CHARACTER_FUUKA:             return WEAPON_TYPE_1H_SWORD;
        case CHARACTER_AKIHIKO:           return WEAPON_TYPE_FIST;
        case CHARACTER_KEN:               return WEAPON_TYPE_SPEAR;
        case CHARACTER_SHINJIRO_OR_METIS: return WEAPON_TYPE_AXE;
        case CHARACTER_KOROMARU:          return WEAPON_TYPE_KNIFE;
        default: 
            P3FES_ASSERT("datCalc.c", 4259);
            break;
    }

    return WEAPON_TYPE_1H_SWORD;
}

// FUN_0030b5a0
u8 BtlActor_IsCharacterDead(BattleActorData* btlActor, s32 param_2)
{
    u8 isDead;

    if (!BtlActor_HasBattleFlags(btlActor, BATTLE_FLAG_DEAD))
    {
        isDead = btlActor->battleStatus.health < 1;
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