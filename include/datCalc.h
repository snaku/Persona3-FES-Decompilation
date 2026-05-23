#ifndef DATCALC_H
#define DATCALC_H

#include "datPersona.h"

#define DATCALC_RAND_PERCENT 100

typedef struct DatUnit DatUnit;

u32 datCalcRand(u32 max);

u8 datCalcGetLevel(DatUnit* unit);
u16 datCalcGetHealth(DatUnit* unit);
u16 datCalcGetSp(DatUnit* unit);
void datCalcSetHealth(DatUnit* unit, u16 health);
void datCalcSetSp(DatUnit* unit, u16 sp);
void datCalcSetBadStatus(DatUnit* unit, u32 flags);
u32 datCalcGetBadStatus(DatUnit* unit);
u32 datCalcGetBadStatusNoDown(DatUnit* unit);
void datCalcClearBadStatus(DatUnit* unit, u32 flags);
u8 datCalcChkBadStatus(DatUnit* unit, u32 flags);
u32 datCalcGetHeldWeaponType(DatUnit* unit);
u8 datCalcCountEquipmentWithEffectById(u16 characterId, u16 effect);
u8 datCalcCountEquipmentWithEffect(DatUnit* unit, u16 effect);
u32 datCalcChkDead(const DatUnit* unit, s32 hpDelta);

#endif