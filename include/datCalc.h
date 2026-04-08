#ifndef DATCALC_H
#define DATCALC_H

#include "datPersona.h"

typedef struct DatUnit DatUnit;

u8 datCalcGetLevel(DatUnit* unit);
u16 datCalcGetHealth(DatUnit* unit);
u16 datCalcGetSp(DatUnit* unit);
void datCalcSetHealth(DatUnit* unit, u16 health);
void datCalcSetSp(DatUnit* unit, u16 sp);
void datCalcAddStatusFlags(DatUnit* unit, u32 flags);
u32 datCalcGetStatusFlagsNoDown(DatUnit* unit);
u32 datCalcGetStatusFlags(DatUnit* unit);
void datCalcRemoveStatusFlags(DatUnit* unit, u32 flags);
u8 datCalcChkStatusFlags(DatUnit* unit, u32 flags);
u32 datCalcGetHeldWeaponType(DatUnit* unit);
u8 datCalcCountEquipmentWithEffectById(u16 characterId, u16 effect);
u8 datCalcCountEquipmentWithEffect(DatUnit* unit, u16 effect);
u8 datCalcChkDead(DatUnit* unit, s32 param_2);

#endif