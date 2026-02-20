#include "Battle/btlCtx.h"
#include "Battle/btlMain.h"
#include "Battle/btlState.h"
#include "temporary.h"

void BtlState_InitStateNon(BattleStateCtx* btlStateCtx);
u32 BtlState_UpdateStateNon(BattleStateCtx* btlStateCtx);
void BtlState_InitStateInit(BattleStateCtx* btlStateCtx);
u32 BtlState_UpdateStateInit(BattleStateCtx* btlStateCtx);
void BtlState_InitStateSceneSet(BattleStateCtx* btlStateCtx);
u32 BtlState_UpdateStateSceneSet(BattleStateCtx* btlStateCtx);
void BtlState_InitStateUnitCreate(BattleStateCtx* btlStateCtx);
u32 BtlState_UpdateStateUnitCreate(BattleStateCtx* btlStateCtx);
void BtlState_InitStateUnitLoad(BattleStateCtx* btlStateCtx);
u32 BtlState_UpdateStateUnitLoad(BattleStateCtx* btlStateCtx);
void BtlState_InitStateStart(BattleStateCtx* btlStateCtx);
u32 BtlState_UpdateStateStart(BattleStateCtx* btlStateCtx);
void BtlState_InitStateAction(BattleStateCtx* btlStateCtx);
u32 BtlState_UpdateStateAction(BattleStateCtx* btlStateCtx);
void BtlState_InitStateRevivalMes(BattleStateCtx* btlStateCtx);
u32 BtlState_UpdateStateRevivalMes(BattleStateCtx* btlStateCtx);
void BtlState_InitStateRevival(BattleStateCtx* btlStateCtx);
u32 BtlState_UpdateStateRevival(BattleStateCtx* btlStateCtx);
void BtlState_InitStateWin(BattleStateCtx* btlStateCtx);
u32 BtlState_UpdateStateWin(BattleStateCtx* btlStateCtx);
void BtlState_InitStateEnemyDead(BattleStateCtx* btlStateCtx);
u32 BtlState_UpdateStateEnemyDead(BattleStateCtx* btlStateCtx);
void BtlState_InitStateCondition(BattleStateCtx* btlStateCtx);
u32 BtlState_UpdateStateCondition(BattleStateCtx* btlStateCtx);
void BtlState_InitStateLose(BattleStateCtx* btlStateCtx);
u32 BtlState_UpdateStateLose(BattleStateCtx* btlStateCtx);
void BtlState_InitStateFadeOut(BattleStateCtx* btlStateCtx);
u32 BtlState_UpdateStateFadeOut(BattleStateCtx* btlStateCtx);
void BtlState_InitStateEnd(BattleStateCtx* btlStateCtx);
u32 BtlState_UpdateStateEnd(BattleStateCtx* btlStateCtx);
void BtlState_InitStateResult(BattleStateCtx* btlStateCtx);
u32 BtlState_UpdateStateResult(BattleStateCtx* btlStateCtx);
void BtlState_InitStateExit(BattleStateCtx* btlStateCtx);
u32 BtlState_UpdateStateExit(BattleStateCtx* btlStateCtx);
void BtlState_InitStateTest(BattleStateCtx* btlStateCtx);
u32 BtlState_UpdateStateTest(BattleStateCtx* btlStateCtx);
void BtlState_InitStateMcNop(BattleStateCtx* btlStateCtx);
u32 BtlState_UpdateStateMcNop(BattleStateCtx* btlStateCtx);

// 00693760
BattleStateEntry gBattleStateTable[] = 
{
    {NULL, NULL, "NULL"},
    {BtlState_InitStateNon, BtlState_UpdateStateNon, "NON"},
    {BtlState_InitStateInit, BtlState_UpdateStateInit, "INIT"},
    {BtlState_InitStateSceneSet, BtlState_UpdateStateSceneSet, "SCENE SET"},
    {BtlState_InitStateUnitCreate, BtlState_UpdateStateUnitCreate, "UNIT CREATE"},
    {BtlState_InitStateUnitLoad, BtlState_UpdateStateUnitLoad, "UNIT LOAD"},
    {BtlState_InitStateStart, BtlState_UpdateStateStart, "START"},
    {BtlState_InitStateAction, BtlState_UpdateStateAction, "ACTION"},
    {BtlState_InitStateRevivalMes, BtlState_UpdateStateRevivalMes, "REVIVAL MES"},
    {BtlState_InitStateRevival, BtlState_UpdateStateRevival, "REVIVAL"},
    {BtlState_InitStateWin, BtlState_UpdateStateWin, "WIN"},
    {BtlState_InitStateEnemyDead, BtlState_UpdateStateEnemyDead, "ENEMY DEAD"},
    {BtlState_InitStateCondition, BtlState_UpdateStateCondition, "CONDITION"},
    {BtlState_InitStateLose, BtlState_UpdateStateLose, "LOSE"},
    {BtlState_InitStateFadeOut, BtlState_UpdateStateFadeOut, "FADE OUT"},
    {BtlState_InitStateEnd, BtlState_UpdateStateEnd, "END"},
    {BtlState_InitStateResult, BtlState_UpdateStateResult, "RESULT"},
    {BtlState_InitStateExit, BtlState_UpdateStateExit, "EXIT"},
    {BtlState_InitStateTest, BtlState_UpdateStateTest, "TEST"},
    {BtlState_InitStateMcNop, BtlState_UpdateStateMcNop, "MC NOP"}
};

// FUN_0029b0e0
void BtlState_InitStateNon(BattleStateCtx* btlStateCtx)
{
    // nothing
}
// FUN_0029b0f0
u32 BtlState_UpdateStateNon(BattleStateCtx* btlStateCtx)
{
    // OK
    return BTL_STATE_NULL;
}

// FUN_0029b100
void BtlState_InitStateInit(BattleStateCtx* btlStateCtx)
{
    // TODO
}
// FUN_0029b160
u32 BtlState_UpdateStateInit(BattleStateCtx* btlStateCtx)
{
    // OK
    return BTL_STATE_SCENE_SET;
}

// FUN_0029b170
void BtlState_InitStateSceneSet(BattleStateCtx* btlStateCtx)
{
    // TODO
}
// FUN_0029b190
u32 BtlState_UpdateStateSceneSet(BattleStateCtx* btlStateCtx)
{
    // TODO

    return BTL_STATE_NULL;
}

// FUN_0029b280
void BtlState_InitStateUnitCreate(BattleStateCtx* btlStateCtx)
{
    // TODO
}
// FUN_0029b760
u32 BtlState_UpdateStateUnitCreate(BattleStateCtx* btlStateCtx)
{
    // TODO

    return BTL_STATE_NULL;
}

// FUN_0029be40
void BtlState_InitStateUnitLoad(BattleStateCtx* btlStateCtx)
{
    // TODO
}
// FUN_0029c110
u32 BtlState_UpdateStateUnitLoad(BattleStateCtx* btlStateCtx)
{
    // TODO

    return BTL_STATE_NULL;
}

// FUN_0029c250
void BtlState_InitStateStart(BattleStateCtx* btlStateCtx)
{
    // TODO
}
// FUN_0029c290
u32 BtlState_UpdateStateStart(BattleStateCtx* btlStateCtx)
{
    // TODO

    return BTL_STATE_NULL;
}

// FUN_0029c330
void BtlState_InitStateAction(BattleStateCtx* btlStateCtx)
{
    // nothing
}
// FUN_0029c340
u32 BtlState_UpdateStateAction(BattleStateCtx* btlStateCtx)
{
    // TODO

    return BTL_STATE_NULL;
}

// FUN_0029c5d0
void BtlState_InitStateRevivalMes(BattleStateCtx* btlStateCtx)
{
    // TODO
}
// FUN_0029c680
u32 BtlState_UpdateStateRevivalMes(BattleStateCtx* btlStateCtx)
{
    // TODO

    return BTL_STATE_NULL;
}

// FUN_0029c700
void BtlState_InitStateRevival(BattleStateCtx* btlStateCtx)
{
    // TODO
}
// FUN_0029ccd0
u32 BtlState_UpdateStateRevival(BattleStateCtx* btlStateCtx)
{
    // TODO

    return BTL_STATE_NULL;
}

// FUN_0029ce90
void BtlState_InitStateWin(BattleStateCtx* btlStateCtx)
{
    // TODO
}
// FUN_0029d0d0
u32 BtlState_UpdateStateWin(BattleStateCtx* btlStateCtx)
{
    // TODO

    return BTL_STATE_NULL;
}

// FUN_0029cde0
void BtlState_InitStateEnemyDead(BattleStateCtx* btlStateCtx)
{
    // TODO
}
// FUN_0029ce20
u32 BtlState_UpdateStateEnemyDead(BattleStateCtx* btlStateCtx)
{
    // TODO

    return BTL_STATE_NULL;
}

// FUN_0029d1f0
void BtlState_InitStateCondition(BattleStateCtx* btlStateCtx)
{
    // TODO
}
// FUN_0029d6e0
u32 BtlState_UpdateStateCondition(BattleStateCtx* btlStateCtx)
{
    // TODO

    return BTL_STATE_NULL;
}

// FUN_0029d720
void BtlState_InitStateLose(BattleStateCtx* btlStateCtx)
{
    // nothing
}
// FUN_0029d730
u32 BtlState_UpdateStateLose(BattleStateCtx* btlStateCtx)
{
    if (btlStateCtx->stateTimer >= 31)
    {
        return BTL_STATE_FADE_OUT;
    }

    return BTL_STATE_NULL;
}

// FUN_0029d760
void BtlState_InitStateFadeOut(BattleStateCtx* btlStateCtx)
{
    // TODO
}
// FUN_0029d800
u32 BtlState_UpdateStateFadeOut(BattleStateCtx* btlStateCtx)
{
    // TODO

    return BTL_STATE_NULL;
}

// FUN_0029d870
void BtlState_InitStateEnd(BattleStateCtx* btlStateCtx)
{
    // TODO
}
// FUN_0029db60
u32 BtlState_UpdateStateEnd(BattleStateCtx* btlStateCtx)
{
    // TODO

    return BTL_STATE_NULL;
}

// FUN_0029dbf0
void BtlState_InitStateResult(BattleStateCtx* btlStateCtx)
{
    // TODO
}
// FUN_0029dc20
u32 BtlState_UpdateStateResult(BattleStateCtx* btlStateCtx)
{
    // TODO

    return BTL_STATE_NULL;
}

// FUN_0029dcf0
void BtlState_InitStateExit(BattleStateCtx* btlStateCtx)
{
    // TODO
}
// FUN_0029dd50
u32 BtlState_UpdateStateExit(BattleStateCtx* btlStateCtx)
{
    // TODO

    return BTL_STATE_NULL;
}

// FUN_0029ddb0
void BtlState_InitStateTest(BattleStateCtx* btlStateCtx)
{
    // nothing
}
// FUN_0029ddc0
u32 BtlState_UpdateStateTest(BattleStateCtx* btlStateCtx)
{
    // TODO

    return BTL_STATE_INIT;
}

// FUN_0029de00
void BtlState_InitStateMcNop(BattleStateCtx* btlStateCtx)
{
    // nothing
}
// FUN_0029de10
u32 BtlState_UpdateStateMcNop(BattleStateCtx* btlStateCtx)
{
    // OK
    return BTL_STATE_NULL;
}

// FUN_0029de20
void BtlState_SetStateAndInit(u32 btlState)
{
    gBtlCtx->btlStateCtx.currState = btlState;
    gBtlCtx->btlStateCtx.stateTimer = 0;
    
    gBattleStateTable[gBtlCtx->btlStateCtx.currState].BtlState_InitState(&gBtlCtx->btlStateCtx);
}

// FUN_0029de80
void BtlState_ProcessBattleState()
{
    u32 newState;

    if (gBtlCtx->btlStateCtx.stateToSet != BTL_STATE_NULL)
    {
        BtlState_SetStateAndInit(gBtlCtx->btlStateCtx.stateToSet); // was inlined

        gBtlCtx->btlStateCtx.stateToSet = BTL_STATE_NULL;
    }

    newState = gBattleStateTable[gBtlCtx->btlStateCtx.currState].BtlState_UpdateState(&gBtlCtx->btlStateCtx);

    if (newState != BTL_STATE_NULL)
    {
        gBtlCtx->btlStateCtx.stateToSet = newState;
    }

    gBtlCtx->btlStateCtx.stateTimer++;
}

// FUN_0029df40. Called when 'btlCtx' is allocated
void BtlState_SetStateNon()
{
    BtlState_SetStateAndInit(BTL_STATE_NON); // was inlined

    gBtlCtx->btlStateCtx.stateToSet = BTL_STATE_NULL;
}