#ifndef BTLMAIN_H
#define BTLMAIN_H

#include "Utils.h"

typedef struct BattleActor BattleActor;
typedef struct BattleActorCore BattleActorCore;

BattleActor* BtlMain_CreateActor();
void BtlMain_UpdateActors();
void BtlMain_DestroyAllActors();
BattleActor* BtlMain_GetActorByActorCore(BattleActorCore* btlActorCore);
BattleActor* BtlMain_GetCurrActorPlaying();

#endif
