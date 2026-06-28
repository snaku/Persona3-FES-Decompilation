#ifndef DATCALC_H
#define DATCALC_H

#include "datPersona.h"

#define DATCALC_RAND_PERCENT 100

#define PASSIVESKILL_FLAG_REGENERATE1   (1 << 0) // 0x01
#define PASSIVESKILL_FLAG_REGENERATE2   (1 << 1) // 0x02
#define PASSIVESKILL_FLAG_REGENERATE3   (1 << 2) // 0x04
#define PASSIVESKILL_FLAG_INVIGORATE1   (1 << 3) // 0x08
#define PASSIVESKILL_FLAG_INVIGORATE2   (1 << 4) // 0x10
#define PASSIVESKILL_FLAG_INVIGORATE3   (1 << 5) // 0x20
#define PASSIVESKILL_FLAG_SPRINGOFLIFE1 (1 << 6) // 0x40. Junpei
#define PASSIVESKILL_FLAG_SPRINGOFLIFE2 (1 << 7) // 0x80. Chidori

typedef struct DatUnit DatUnit;

u32 datCalcRand(u32 max);

u8 datCalcGetLevel(DatUnit* unit);
u16 datCalcGetHp(DatUnit* unit);
u16 datCalcGetSp(DatUnit* unit);
void datCalcSetHp(DatUnit* unit, u16 hp);
void datCalcSetSp(DatUnit* unit, u16 sp);
u16 datCalcGetMaxHp(DatUnit* unit);
void datCalcSetBadStatus(DatUnit* unit, u32 flags);
u32 datCalcGetBadStatus(DatUnit* unit);
u32 datCalcGetBadStatusNoDown(DatUnit* unit);
void datCalcClearBadStatus(DatUnit* unit, u32 flags);
u32 datCalcChkBadStatus(DatUnit* unit, u32 flags);
u32 datCalcHasSkill(DatUnit* unit, u16 skillId);
u8 datCalcCountEquipmentWithEffectById(u16 pcId, u16 effect);
u8 datCalcCountEquipmentWithEffect(DatUnit* unit, u16 effect);
u32 datCalcGetPassiveSkillFlags(DatUnit* unit);
u32 datCalcGetHeldWeaponType(DatUnit* unit);
u32 datCalcIsDead(const DatUnit* unit, s32 hpDelta);
u32 datCalcIsLowHp(DatUnit* unit);

#endif