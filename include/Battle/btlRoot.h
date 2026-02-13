#ifndef BTLROOT_H
#define BTLROOT_H

#include "Utils.h"

typedef struct BattleActor BattleActor;
typedef struct BattleActorCore BattleActorCore;

BattleActor* BtlRoot_CreateActor();
void BtlRoot_UpdateActors();
void BtlRoot_DestroyAllActors();
BattleActor* BtlRoot_GetActorByActorCore(BattleActorCore* btlActorCore);
BattleActor* BtlRoot_GetActorByActorId(u32 actorId);
BattleActor* BtlRoot_GetCurrActorPlaying();

#endif