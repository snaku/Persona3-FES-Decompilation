#ifndef BTLMAIN_H
#define BTLMAIN_H

#include "Utils.h"

typedef struct BattleActor BattleActor;

BattleActor* BtlMain_CreateActor();
void BtlMain_UpdateActors();
BattleActor* BtlMain_GetCurrActorPlaying();

#endif
