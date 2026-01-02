#include "Battle/btlState.h"
#include "temporary.h"

#include <stdlib.h>

// 00693760
BattleStateEntry gBattleStateTable[] = 
{
    {NULL, NULL, "NULL"}
};

// FUN_0029de80
void BtlState_ProcessBattleState()
{
    u32 newState;

    if (ctx.btlCtx->btlStateCtx.stateToSet != BTL_STATE_NULL)
    {
        ctx.btlCtx->btlStateCtx.currState = ctx.btlCtx->btlStateCtx.stateToSet;
        ctx.btlCtx->btlStateCtx.stateTimer = 0;
        gBattleStateTable[ctx.btlCtx->btlStateCtx.currState].BtlState_InitState(&ctx.btlCtx->btlStateCtx);
        ctx.btlCtx->btlStateCtx.stateToSet = BTL_STATE_NULL;
    }

    newState = gBattleStateTable[ctx.btlCtx->btlStateCtx.currState].BtlState_UpdateState(&ctx.btlCtx->btlStateCtx);

    if (newState != BTL_STATE_NULL)
    {
        ctx.btlCtx->btlStateCtx.stateToSet = newState;
    }

    ctx.btlCtx->btlStateCtx.stateTimer++;
}
