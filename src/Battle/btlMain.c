#include "Battle/btlMain.h"
#include "Battle/btlCtx.h"
#include "kwln/kwlnTask.h"
#include "temporary.h"

// FUN_0027d880
KwlnTask* BtlMain_GetBtlTask()
{
    if (ctx.btlCtx == NULL)
    {
        return NULL;
    }

    return ctx.btlCtx->btlTask;
}

// FUN_0027d8b0
void BtlMain_SetBossBtlFlag()
{
    ctx.btlCtx->flags |= BATTLE_FLAG_IS_BOSS_BTL;
}