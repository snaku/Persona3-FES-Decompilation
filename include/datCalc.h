#ifndef DATCALC_H
#define DATCALC_H

#include "datPersona.h"

u8 BtlActor_GetLevel(BattleActorData* btlActorData);
u16 BtlActor_GetHealth(BattleActorData* btlActorData);
u16 BtlActor_GetSp(BattleActorData* btlActorData);
void BtlActor_SetHealth(BattleActorData* btlAbtlActorDatactor, u16 health);
void BtlActor_SetSp(BattleActorData* btlActorData, u16 sp);
void BtlActor_AddBattleFlags(BattleActorData* btlActorData, u32 flags);
u32 BtlActor_GetBattleFlagsNoDown(BattleActorData* btlActorData);
u32 BtlActor_GetBattleFlags(BattleActorData* btlActorData);
void BtlActor_RemoveBattleFlags(BattleActorData* btlActorData, u32 flags);
u8 BtlActor_HasBattleFlags(BattleActorData* btlActorData, u32 flags);
u32 BtlActor_GetHeldWeaponType(BattleActorData* btlActorData);
u8 BtlActor_IsCharacterDead(BattleActorData* btlActorData, s32 param_2);
void FUN_0030c440();

#endif