#ifndef DATCALC_H
#define DATCALC_H

#include "datPersona.h"
#include "datUnit.h"

u8 Unit_GetLevel(UnitData* unit);
u16 Unit_GetHealth(UnitData* unit);
u16 Unit_GetSp(UnitData* unit);
void Unit_SetHealth(UnitData* unit, u16 health);
void Unit_SetSp(UnitData* unit, u16 sp);
void Unit_AddBattleFlags(UnitData* unit, u32 flags);
u32 Unit_GetBattleFlagsNoDown(UnitData* unit);
u32 Unit_GetBattleFlags(UnitData* unit);
void Unit_RemoveBattleFlags(UnitData* unit, u32 flags);
u8 Unit_HasBattleFlags(UnitData* unit, u32 flags);
u32 Unit_GetHeldWeaponType(UnitData* unit);
u8 Unit_IsUnitDead(UnitData* unit, s32 param_2);
void FUN_0030c440();

#endif