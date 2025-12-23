#ifndef DATCALC_H
#define DATCALC_H

#include "datPersona.h"

u8 BtlActor_GetLevel(BattleActorData* btlActor);
u16 BtlActor_GetHealth(BattleActorData* btlActor);
u16 BtlActor_GetSp(BattleActorData* btlActor);
void BtlActor_SetHealth(BattleActorData* btlActor);
void BtlActor_SetSp(BattleActorData* btlActor, u16 sp);
void BtlActor_AddBattleFlags(BattleActorData* btlActor, u32 flags);
u32 BtlActor_GetBattleFlagsNoDown(BattleActorData* btlActor);
u32 BtlActor_GetBattleFlags(BattleActorData* btlActor);
void BtlActor_RemoveBattleFlags(BattleActorData* btlActor, u32 flags);
u8 BtlActor_HasBattleFlags(BattleActorData* btlActor, u32 flags);
u32 BtlActor_GetHeldWeaponType(BattleActorData* btlActor);
u8 BtlActor_IsCharacterDead(BattleActorData* btlActor, s32 param_2);
void FUN_0030c440();

#endif