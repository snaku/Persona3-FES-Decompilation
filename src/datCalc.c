#include "datCalc.h"
#include <stdlib.h>

// FUN_002ffcc0
u8 Unit_GetLevel(UnitData* unit){
    u8 level;
    PersonaData* persona;

    if (!(unit->flags & 4) && !IS_HERO(unit->id))
    {
        persona = Persona_GetPersonaByCharacterId(unit->id);
        if (persona == NULL)
        {
            P3FES_ASSERT("datCalc.c", 66);
        }

        level = Persona_GetPersonaLevel(persona);
    }
    else 
    {
        level = unit->status.level;
    }

    if (level == 0)
    {
        P3FES_ASSERT("datCalc.c", 70);
    }

    return level;
}

// FUN_002ffd70
u16 Unit_GetHealth(UnitData* unit)
{
    return unit->status.health;
}

// FUN_002ffd80
u16 Unit_GetSp(UnitData* unit)
{
    return unit->status.sp;
}

// FUN_002ffd90
void Unit_SetHealth(UnitData* unit, u16 health)
{
    if (health > 999 && !(unit->flags & (1 << 2)))
    {
        health = 999;
    }

    unit->status.health = health;
}

// FUN_002ffdc0
void Unit_SetSp(UnitData* unit, u16 sp)
{
    if (sp > 999 && !(unit->flags & (1 << 2)))
    {
        sp = 999;
    }

    unit->status.sp = sp;
}

// FUN_003004f0
void Unit_AddBattleFlags(UnitData* unit, u32 flags)
{
    const u32 LOW_20_BITS = 0x000FFFFF;
    const u32 HIGH_12_BITS = 0xFFF00000;

    if (!(flags & LOW_20_BITS))
    {
        unit->status.flags = (unit->status.flags & HIGH_12_BITS) |
                                       (flags & LOW_20_BITS);
    }

    unit->status.flags |= (flags & HIGH_12_BITS);
}

// FUN_00300530
u32 Unit_GetBattleFlagsNoDown(UnitData* unit)
{
    // without bit 20 and over (so BATTLE_FLAG_DOWN)
    return unit->status.flags & 0x000FFFFF;
}

// FUN_00300550
u32 Unit_GetBattleFlags(UnitData* unit)
{
    return unit->status.flags;
}

// FUN_00300560
void Unit_RemoveBattleFlags(UnitData* unit, u32 flags)
{
    unit->status.flags &= ~flags;
}

// FUN_00300580
u8 Unit_HasBattleFlags(UnitData* unit, u32 flags)
{
    return (unit->status.flags & flags);
}

// FUN_00308c60
u32 Unit_GetHeldWeaponType(UnitData* unit)
{
    u16 heroWeaponIdx;
    u16 heroWeaponId;
    u16 heroWeaponUnkFlag;

    if (unit->flags & (1 << 2))
    {
        return WEAPON_TYPE_1H_SWORD;
    }

    switch (unit->id)
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
u8 Unit_IsCharacterDead(UnitData* unit, s32 param_2)
{
    u8 isDead;

    if (!Unit_HasBattleFlags(unit, BATTLE_FLAG_DEAD))
    {
        isDead = unit->status.health < 1;
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