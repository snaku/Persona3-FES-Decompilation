#ifndef BTLMAIN_H
#define BTLMAIN_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;
typedef struct BattleCtx BattleCtx;

extern BattleCtx* gBtlCtx;

KwlnTask* BtlMain_GetBtlTask();
void BtlMain_SetBossBtlFlag();

#endif
