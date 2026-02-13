#include "Battle/btlMain.h"
#include "Battle/btlCtx.h"
#include "temporary.h"

// FUN_0027d8b0
void BtlMain_SetBossBtlFlag()
{
    ctx.btlCtx->flags |= BATTLE_FLAG_IS_BOSS_BTL;
}