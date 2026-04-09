#include "g_data.h"
#include "datCalc.h"
#include "Kosaka/k_assert.h"

// FUN_002ffcc0
u8 datCalcGetLevel(DatUnit* unit){
    u8 level;
    DatPersonaWork* persona;

    if (!(unit->flags & UNIT_FLAG_ENEMY) && !IS_HERO(unit->id))
    {
        persona = datPersonaGetByCharacterId(unit->id);
        K_ASSERT(persona != NULL, 66);

        level = datPersonaGetLevel(persona);
    }
    else 
    {
        level = unit->status.level;
    }

    K_ASSERT(level != 0, 70);

    return level;
}

// FUN_002ffd70
u16 datCalcGetHealth(DatUnit* unit)
{
    return unit->status.health;
}

// FUN_002ffd80
u16 datCalcGetSp(DatUnit* unit)
{
    return unit->status.sp;
}

// FUN_002ffd90
void datCalcSetHealth(DatUnit* unit, u16 health)
{
    if (health > 999 && !(unit->flags & UNIT_FLAG_ENEMY))
    {
        health = 999;
    }

    unit->status.health = health;
}

// FUN_002ffdc0
void datCalcSetSp(DatUnit* unit, u16 sp)
{
    if (sp > 999 && !(unit->flags & UNIT_FLAG_ENEMY))
    {
        sp = 999;
    }

    unit->status.sp = sp;
}

// FUN_003004f0
void datCalcSetBadStatus(DatUnit* unit, u32 badStatus)
{
    if (!(badStatus & 0x000FFFFF))
    {
        unit->status.bad = (unit->status.bad & 0xFFF00000) |
                                       (badStatus & 0x000FFFFF);
    }

    unit->status.bad |= (badStatus & 0xFFF00000);
}

// FUN_00300530
u32 datCalcGetBadStatusNoDown(DatUnit* unit)
{
    return unit->status.bad & 0x000FFFFF;
}

// FUN_00300550
u32 datCalcGetBadStatus(DatUnit* unit)
{
    return unit->status.bad;
}

// FUN_00300560
void datCalcClearBadStatus(DatUnit* unit, u32 badStatus)
{
    unit->status.bad &= ~badStatus;
}

// FUN_00300580
u8 datCalcChkBadStatus(DatUnit* unit, u32 badStatus)
{
    return (unit->status.bad & badStatus);
}

// FUN_00308c60
u32 datCalcGetHeldWeaponType(DatUnit* unit)
{
    // WIP

    u16 heroWeaponIdx;
    u16 heroWeaponId;
    u16 heroWeaponUnkFlag;

    if (unit->flags & UNIT_FLAG_ENEMY)
    {
        return WEAPON_TYPE_1H_SWORD;
    }

    switch (unit->id)
    {
        case CHARACTER_HERO:
            heroWeaponIdx = datGetEquipmentIdx(CHARACTER_HERO, EQUIPMENT_TYPE_WEAPON);
            heroWeaponId = datGetEquipmentId(CHARACTER_HERO, heroWeaponIdx);
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

            K_Assert("datCalc.c", 4237);
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
            K_Assert("datCalc.c", 4259);
            break;
    }

    return WEAPON_TYPE_1H_SWORD;
}

// FUN_00300870. Return the number of equipments with the effect
u8 datCalcCountEquipmentWithEffectById(u16 characterId, u16 effect)
{
    u8 equipWithEffectNum = 0;
    u16 equipIdx;
    u8 equipEffect;

    K_ASSERT(characterId < CHARACTER_MAX, 646);

    // weapon
    equipIdx = datGetEquipmentIdx(characterId, EQUIPMENT_TYPE_WEAPON);
    equipEffect = datGetEquipmentEffect(characterId, equipIdx);
    if (effect == equipEffect) equipWithEffectNum++;

    // armor
    equipIdx = datGetEquipmentIdx(characterId, EQUIPMENT_TYPE_ARMOR);
    equipEffect = datGetEquipmentEffect(characterId, equipIdx);
    if (effect == equipEffect) equipWithEffectNum++;

    // boots
    equipIdx = datGetEquipmentIdx(characterId, EQUIPMENT_TYPE_BOOTS);
    equipEffect = datGetEquipmentEffect(characterId, equipIdx);
    if (effect == equipEffect) equipWithEffectNum++;

    return equipWithEffectNum;
}

// FUN_003009a0. Return the number of equipments with the effect
u8 datCalcCountEquipmentWithEffect(DatUnit* unit, u16 effect)
{
    if (unit->flags & UNIT_FLAG_ENEMY)
    {
        return 0;
    }

    return datCalcCountEquipmentWithEffectById(unit->id, effect); // was probably inlined
}

// FUN_0030b5a0
u8 datCalcChkDead(DatUnit* unit, s32 param_2)
{
    u8 isDead;

    if (!datCalcChkStatusFlags(unit, UNIT_BADSTATUS_DEAD))
    {
        isDead = unit->status.health < 1;
    }
    else
    {
        isDead = true;
    }

    return isDead;
}