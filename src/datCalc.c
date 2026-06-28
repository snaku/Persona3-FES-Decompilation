#include "g_data.h"
#include "datCalc.h"
#include "Kosaka/k_assert.h"
#include "Effect/effMisc.h"

static u32 sPrevPercentRand; // 007ce510

// FUN_002ffbc0
u32 datCalcRand(u32 max)
{
    u32 rand;

    K_ASSERT(max != 0, 26);

    if (max == DATCALC_RAND_PERCENT)
    {
        rand = (((effMiscRand(NULL) % 4096) + (effMiscRand(NULL) % 4096)) % 4096) / 41;
        
        if (sPrevPercentRand >= rand - 3 && 
            sPrevPercentRand <= rand + 3)
        {
            rand = (((effMiscRand(NULL) % 4096) + (effMiscRand(NULL) % 4096)) % 4096) / 41;
        }

        sPrevPercentRand = rand;
    }
    else
    {
        rand = effMiscRand(NULL) % max;
    }

    return rand;
}

// FUN_002ffcc0
u8 datCalcGetLevel(DatUnit* unit){
    u8 level;
    DatPersonaWork* persona;

    if (!(unit->flags & UNIT_FLAG_ENEMY) && !IS_HERO(unit->id))
    {
        persona = datPersonaGetByPcId(unit->id);
        K_ASSERT(persona != NULL, 66);

        level = datPersonaGetLevel(persona);
    }
    else 
    {
        level = unit->level;
    }

    K_ASSERT(level != 0, 70);

    return level;
}

// FUN_002ffd70
u16 datCalcGetHp(DatUnit* unit)
{
    return unit->hp;
}

// FUN_002ffd80
u16 datCalcGetSp(DatUnit* unit)
{
    return unit->sp;
}

// FUN_002ffd90
void datCalcSetHp(DatUnit* unit, u16 hp)
{
    if (hp > 999 && !(unit->flags & UNIT_FLAG_ENEMY))
    {
        hp = 999;
    }

    unit->hp = hp;
}

// FUN_002ffdc0
void datCalcSetSp(DatUnit* unit, u16 sp)
{
    if (sp > 999 && !(unit->flags & UNIT_FLAG_ENEMY))
    {
        sp = 999;
    }

    unit->sp = sp;
}

// FUN_002ffdf0
u16 datCalcGetMaxHp(DatUnit* unit)
{
    // TODO

    return 0;
}

// FUN_003004f0
void datCalcSetBadStatus(DatUnit* unit, u32 badStatus)
{
    if (!(badStatus & 0x000FFFFF))
    {
        unit->bad = (unit->bad & 0xFFF00000) |
                                       (badStatus & 0x000FFFFF);
    }

    unit->bad |= (badStatus & 0xFFF00000);
}

// FUN_00300530
u32 datCalcGetBadStatusNoDown(DatUnit* unit)
{
    return unit->bad & 0x000FFFFF;
}

// FUN_00300550
u32 datCalcGetBadStatus(DatUnit* unit)
{
    return unit->bad;
}

// FUN_00300560
void datCalcClearBadStatus(DatUnit* unit, u32 badStatus)
{
    unit->bad &= ~badStatus;
}

// FUN_00300580
u32 datCalcChkBadStatus(DatUnit* unit, u32 badStatus)
{
    return (unit->bad & badStatus);
}

// FUN_003005e0
u32 datCalcHasSkill(DatUnit* unit, u16 skillId)
{
    // TODO

    return false;
}

// FUN_00300870. Return the number of equipments with the effect
u8 datCalcCountEquipmentWithEffectById(u16 pcId, u16 effect)
{
    u8 equipWithEffectNum = 0;
    u16 equipIdx;
    u8 equipEffect;

    K_ASSERT(pcId < PC_MAX, 646);

    // weapon
    equipIdx = datGetEquipmentIdx(pcId, EQUIPMENT_TYPE_WEAPON);
    equipEffect = datGetEquipmentEffect(pcId, equipIdx);
    if (effect == equipEffect) equipWithEffectNum++;

    // armor
    equipIdx = datGetEquipmentIdx(pcId, EQUIPMENT_TYPE_ARMOR);
    equipEffect = datGetEquipmentEffect(pcId, equipIdx);
    if (effect == equipEffect) equipWithEffectNum++;

    // boots
    equipIdx = datGetEquipmentIdx(pcId, EQUIPMENT_TYPE_BOOTS);
    equipEffect = datGetEquipmentEffect(pcId, equipIdx);
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

// FUN_00300d80
u32 datCalcGetPassiveSkillFlags(DatUnit* unit)
{
    u32 flags;

    flags = 0;

    if (datCalcHasSkill(unit, SKILL_REGENERATE1))
    {
        flags |= PASSIVESKILL_FLAG_REGENERATE1;
    }
    if (datCalcHasSkill(unit, SKILL_REGENERATE2))
    {
        flags |= PASSIVESKILL_FLAG_REGENERATE2;
    }
    if (datCalcHasSkill(unit, SKILL_REGENERATE3))
    {
        flags |= PASSIVESKILL_FLAG_REGENERATE3;
    }

    if (datCalcHasSkill(unit, SKILL_INVIGORATE1))
    {
        flags |= PASSIVESKILL_FLAG_INVIGORATE1;
    }
    if (datCalcHasSkill(unit, SKILL_INVIGORATE2))
    {
        flags |= PASSIVESKILL_FLAG_INVIGORATE2;
    }
    if (datCalcHasSkill(unit, SKILL_INVIGORATE3))
    {
        flags |= PASSIVESKILL_FLAG_INVIGORATE3;
    }

    if (datCalcHasSkill(unit, SKILL_SPRINGOFLIFE1))
    {
        flags |= PASSIVESKILL_FLAG_SPRINGOFLIFE1;
    }
    if (datCalcHasSkill(unit, SKILL_SPRINGOFLIFE2))
    {
        flags |= PASSIVESKILL_FLAG_SPRINGOFLIFE2;
    }

    return flags;
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
        case PC_HERO:
            heroWeaponIdx = datGetEquipmentIdx(PC_HERO, EQUIPMENT_TYPE_WEAPON);
            heroWeaponId = datGetEquipmentId(PC_HERO, heroWeaponIdx);
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

            K_ASSERT(false, 4237);
        case PC_YUKARI:            return WEAPON_TYPE_BOW;
        case PC_AIGIS:             return WEAPON_TYPE_GUN;
        case PC_MITSURU:           return WEAPON_TYPE_1H_SWORD;
        case PC_JUNPEI:            return WEAPON_TYPE_2H_SWORD;
        case PC_FUUKA:             return WEAPON_TYPE_1H_SWORD;
        case PC_AKIHIKO:           return WEAPON_TYPE_FIST;
        case PC_KEN:               return WEAPON_TYPE_SPEAR;
        case PC_SHINJIRO_OR_METIS: return WEAPON_TYPE_AXE;
        case PC_KOROMARU:          return WEAPON_TYPE_KNIFE;
        default: 
            K_ASSERT(false, 4259);
            break;
    }

    return WEAPON_TYPE_1H_SWORD;
}

// FUN_0030b5a0
u32 datCalcIsDead(const DatUnit* unit, s32 hpDelta)
{
    if (unit->bad & UNIT_BADSTATUS_DEAD ? 1 : 0)
    {
        return true;
    }

    return (unit->hp + hpDelta) <= 0;
}

// FUN_0030b5e0
u32 datCalcIsLowHp(DatUnit* unit)
{
    u16 hp;

    hp = unit->hp;

    return ((hp * 100) / datCalcGetMaxHp(unit)) < 26; // is hp below 26%
}