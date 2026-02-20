#include "Battle/btlMain.h"
#include "Battle/btlCtx.h"
#include "kwln/kwlnTask.h"
#include "temporary.h"

BattleCtx* gBtlCtx; // 007ce3ec. NULL when not in a battle

// FUN_0027d880
KwlnTask* BtlMain_GetBtlTask()
{
    if (gBtlCtx == NULL)
    {
        return NULL;
    }

    return gBtlCtx->btlTask;
}

// FUN_0027d8b0
void BtlMain_SetBossBtlFlag()
{
    gBtlCtx->flags |= BATTLE_FLAG_IS_BOSS_BTL;
}