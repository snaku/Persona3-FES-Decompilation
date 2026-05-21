#include "Battle/battle.h"
#include "temporary.h"

void btlMainInitStateNon(BtlStateWork* work);
u32 btlMainUpdateStateNon(BtlStateWork* work);
void btlMainInitStateInit(BtlStateWork* work);
u32 btlMainUpdateStateInit(BtlStateWork* work);
void btlMainInitStateSceneSet(BtlStateWork* work);
u32 btlMainUpdateStateSceneSet(BtlStateWork* work);
void btlMainInitStateUnitCreate(BtlStateWork* work);
u32 btlMainUpdateStateUnitCreate(BtlStateWork* work);
void btlMainInitStateUnitLoad(BtlStateWork* work);
u32 btlMainUpdateStateUnitLoad(BtlStateWork* work);
void btlMainInitStateStart(BtlStateWork* work);
u32 btlMainUpdateStateStart(BtlStateWork* work);
void btlMainInitStateAction(BtlStateWork* work);
u32 btlMainUpdateStateAction(BtlStateWork* work);
void btlMainInitStateRevivalMes(BtlStateWork* work);
u32 btlMainUpdateStateRevivalMes(BtlStateWork* work);
void btlMainInitStateRevival(BtlStateWork* work);
u32 btlMainUpdateStateRevival(BtlStateWork* work);
void btlMainInitStateWin(BtlStateWork* work);
u32 btlMainUpdateStateWin(BtlStateWork* work);
void btlMainInitStateEnemyDead(BtlStateWork* work);
u32 btlMainUpdateStateEnemyDead(BtlStateWork* work);
void btlMainInitStateCondition(BtlStateWork* work);
u32 btlMainUpdateStateCondition(BtlStateWork* work);
void btlMainInitStateLose(BtlStateWork* work);
u32 btlMainUpdateStateLose(BtlStateWork* work);
void btlMainInitStateFadeOut(BtlStateWork* work);
u32 btlMainUpdateStateFadeOut(BtlStateWork* work);
void btlMainInitStateEnd(BtlStateWork* work);
u32 btlMainUpdateStateEnd(BtlStateWork* work);
void btlMainInitStateResult(BtlStateWork* work);
u32 btlMainUpdateStateResult(BtlStateWork* work);
void btlMainInitStateExit(BtlStateWork* work);
u32 btlMainUpdateStateExit(BtlStateWork* work);
void btlMainInitStateTest(BtlStateWork* work);
u32 btlMainUpdateStateTest(BtlStateWork* work);
void btlMainInitStateMcNop(BtlStateWork* work);
u32 btlMainUpdateStateMcNop(BtlStateWork* work);

// 00693760
BtlStateEntry gBattleStateTable[] = 
{
    {NULL, NULL, "NULL"},
    {btlMainInitStateNon, btlMainUpdateStateNon, "NON"},
    {btlMainInitStateInit, btlMainUpdateStateInit, "INIT"},
    {btlMainInitStateSceneSet, btlMainUpdateStateSceneSet, "SCENE SET"},
    {btlMainInitStateUnitCreate, btlMainUpdateStateUnitCreate, "UNIT CREATE"},
    {btlMainInitStateUnitLoad, btlMainUpdateStateUnitLoad, "UNIT LOAD"},
    {btlMainInitStateStart, btlMainUpdateStateStart, "START"},
    {btlMainInitStateAction, btlMainUpdateStateAction, "ACTION"},
    {btlMainInitStateRevivalMes, btlMainUpdateStateRevivalMes, "REVIVAL MES"},
    {btlMainInitStateRevival, btlMainUpdateStateRevival, "REVIVAL"},
    {btlMainInitStateWin, btlMainUpdateStateWin, "WIN"},
    {btlMainInitStateEnemyDead, btlMainUpdateStateEnemyDead, "ENEMY DEAD"},
    {btlMainInitStateCondition, btlMainUpdateStateCondition, "CONDITION"},
    {btlMainInitStateLose, btlMainUpdateStateLose, "LOSE"},
    {btlMainInitStateFadeOut, btlMainUpdateStateFadeOut, "FADE OUT"},
    {btlMainInitStateEnd, btlMainUpdateStateEnd, "END"},
    {btlMainInitStateResult, btlMainUpdateStateResult, "RESULT"},
    {btlMainInitStateExit, btlMainUpdateStateExit, "EXIT"},
    {btlMainInitStateTest, btlMainUpdateStateTest, "TEST"},
    {btlMainInitStateMcNop, btlMainUpdateStateMcNop, "MC NOP"}
};

// FUN_0029b0e0
void btlMainInitStateNon(BtlStateWork* work)
{
    // nothing
}
// FUN_0029b0f0
u32 btlMainUpdateStateNon(BtlStateWork* work)
{
    // OK
    return BTL_STATE_NULL;
}

// FUN_0029b100
void btlMainInitStateInit(BtlStateWork* work)
{
    // TODO
}
// FUN_0029b160
u32 btlMainUpdateStateInit(BtlStateWork* work)
{
    // OK
    return BTL_STATE_SCENESET;
}

// FUN_0029b170
void btlMainInitStateSceneSet(BtlStateWork* work)
{
    // TODO
}
// FUN_0029b190
u32 btlMainUpdateStateSceneSet(BtlStateWork* work)
{
    // TODO

    return BTL_STATE_NULL;
}

// FUN_0029b280
void btlMainInitStateUnitCreate(BtlStateWork* work)
{
    // TODO
}
// FUN_0029b760
u32 btlMainUpdateStateUnitCreate(BtlStateWork* work)
{
    // TODO

    return BTL_STATE_NULL;
}

// FUN_0029be40
void btlMainInitStateUnitLoad(BtlStateWork* work)
{
    // TODO
}
// FUN_0029c110
u32 btlMainUpdateStateUnitLoad(BtlStateWork* work)
{
    // TODO

    return BTL_STATE_NULL;
}

// FUN_0029c250
void btlMainInitStateStart(BtlStateWork* work)
{
    // TODO
}
// FUN_0029c290
u32 btlMainUpdateStateStart(BtlStateWork* work)
{
    // TODO

    return BTL_STATE_NULL;
}

// FUN_0029c330
void btlMainInitStateAction(BtlStateWork* work)
{
    // nothing
}
// FUN_0029c340
u32 btlMainUpdateStateAction(BtlStateWork* work)
{
    // TODO

    return BTL_STATE_NULL;
}

// FUN_0029c5d0
void btlMainInitStateRevivalMes(BtlStateWork* work)
{
    // TODO
}
// FUN_0029c680
u32 btlMainUpdateStateRevivalMes(BtlStateWork* work)
{
    // TODO

    return BTL_STATE_NULL;
}

// FUN_0029c700
void btlMainInitStateRevival(BtlStateWork* work)
{
    // TODO
}
// FUN_0029ccd0
u32 btlMainUpdateStateRevival(BtlStateWork* work)
{
    // TODO

    return BTL_STATE_NULL;
}

// FUN_0029ce90
void btlMainInitStateWin(BtlStateWork* work)
{
    // TODO
}
// FUN_0029d0d0
u32 btlMainUpdateStateWin(BtlStateWork* work)
{
    // TODO

    return BTL_STATE_NULL;
}

// FUN_0029cde0
void btlMainInitStateEnemyDead(BtlStateWork* work)
{
    // TODO
}
// FUN_0029ce20
u32 btlMainUpdateStateEnemyDead(BtlStateWork* work)
{
    // TODO

    return BTL_STATE_NULL;
}

// FUN_0029d1f0
void btlMainInitStateCondition(BtlStateWork* work)
{
    // TODO
}
// FUN_0029d6e0
u32 btlMainUpdateStateCondition(BtlStateWork* work)
{
    // TODO

    return BTL_STATE_NULL;
}

// FUN_0029d720
void btlMainInitStateLose(BtlStateWork* work)
{
    // nothing
}
// FUN_0029d730
u32 btlMainUpdateStateLose(BtlStateWork* work)
{
    if (work->stateTimer >= 31)
    {
        return BTL_STATE_FADEOUT;
    }

    return BTL_STATE_NULL;
}

// FUN_0029d760
void btlMainInitStateFadeOut(BtlStateWork* work)
{
    // TODO
}
// FUN_0029d800
u32 btlMainUpdateStateFadeOut(BtlStateWork* work)
{
    // TODO

    return BTL_STATE_NULL;
}

// FUN_0029d870
void btlMainInitStateEnd(BtlStateWork* work)
{
    // TODO
}
// FUN_0029db60
u32 btlMainUpdateStateEnd(BtlStateWork* work)
{
    // TODO

    return BTL_STATE_NULL;
}

// FUN_0029dbf0
void btlMainInitStateResult(BtlStateWork* work)
{
    // TODO
}
// FUN_0029dc20
u32 btlMainUpdateStateResult(BtlStateWork* work)
{
    // TODO

    return BTL_STATE_NULL;
}

// FUN_0029dcf0
void btlMainInitStateExit(BtlStateWork* work)
{
    // TODO
}
// FUN_0029dd50
u32 btlMainUpdateStateExit(BtlStateWork* work)
{
    // TODO

    return BTL_STATE_NULL;
}

// FUN_0029ddb0
void btlMainInitStateTest(BtlStateWork* work)
{
    // nothing
}
// FUN_0029ddc0
u32 btlMainUpdateStateTest(BtlStateWork* work)
{
    // TODO

    return BTL_STATE_INIT;
}

// FUN_0029de00
void btlMainInitStateMcNop(BtlStateWork* work)
{
    // nothing
}
// FUN_0029de10
u32 btlMainUpdateStateMcNop(BtlStateWork* work)
{
    // OK
    return BTL_STATE_NULL;
}

// FUN_0029de20
void btlMainSetStateAndInit(u32 state)
{
    gBtl->stateWork.currState = state;
    gBtl->stateWork.stateTimer = 0;
    
    gBattleStateTable[gBtl->stateWork.currState].init(&gBtl->stateWork);
}

// FUN_0029de80
void btlMainUpdateState()
{
    u32 newState;

    if (gBtl->stateWork.stateToSet != BTL_STATE_NULL)
    {
        btlMainSetStateAndInit(gBtl->stateWork.stateToSet); // was inlined

        gBtl->stateWork.stateToSet = BTL_STATE_NULL;
    }

    newState = gBattleStateTable[gBtl->stateWork.currState].update(&gBtl->stateWork);

    if (newState != BTL_STATE_NULL)
    {
        gBtl->stateWork.stateToSet = newState;
    }

    gBtl->stateWork.stateTimer++;
}

// FUN_0029df40. Called when 'btlCtx' is allocated
void btlMainSetStateNon()
{
    btlMainSetStateAndInit(BTL_STATE_NON); // was inlined

    gBtl->stateWork.stateToSet = BTL_STATE_NULL;
}