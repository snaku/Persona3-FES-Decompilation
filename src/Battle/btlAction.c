#include "Battle/btlAction.h"
#include "datCalc.h"

void BtlAction_InitStateNon(BattleActionStruct* btlAction);
void BtlAction_UpdateStateNon(BattleActionStruct* btlAction);
void BtlAction_InitStateStandBy(BattleActionStruct* btlAction);
void BtlAction_UpdateStateStandBy(BattleActionStruct* btlAction);
void BtlAction_InitStateStart(BattleActionStruct* btlAction);
void BtlAction_UpdateStateStart(BattleActionStruct* btlAction);

typedef struct
{
    void (*BtlAction_InitState)(BattleActionStruct* btlAction);
    void (*BtlAction_UpdateState)(BattleActionStruct* btlAction);
    const char* name;
} BattleActionStateEntry;

static BattleActionStateEntry gActionStateTable[] = 
{
    {BtlAction_InitStateNon, BtlAction_UpdateStateNon, "NON"},
    {BtlAction_InitStateStandBy, BtlAction_UpdateStateStandBy, "STANDBY"},
    {BtlAction_InitStateStart, BtlAction_UpdateStateStart, "START"},
};

// FUN_0028a990
void BtlAction_InitStateNon(BattleActionStruct* btlAction)
{
    // nothing
}
// FUN_0028a9a0
void BtlAction_UpdateStateNon(BattleActionStruct* btlAction)
{
    // nothing
}

// FUN_0028a9b0
void BtlAction_InitStateStandBy(BattleActionStruct* btlAction)
{
    // nothing
}
// FUN_0028a9c0
void BtlAction_UpdateStateStandBy(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_0028aa20
void BtlAction_InitStateStart(BattleActionStruct* btlAction)
{
    // TODO
}
// FUN_0028b230
void BtlAction_UpdateStateStart(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_00289860
u8 BtlAction_CheckPlayWeaponIdleAnim(BattleActionStruct* btlAction)
{
    // TODO

    if (btlAction->idleWeaponAnimTimer <= 0)
    {

    }
    if (btlAction->idleWeaponAnimTimer == 0)
    {

    }

    btlAction->idleWeaponAnimTimer--;
    return false;
}

// FUN_00299d60
void BtlAction_SetStateAndExecute(BattleActionStruct* btlAction, u16 btlState)
{
    btlAction->oldState = btlAction->currState;
    btlAction->currState = btlState;
    btlAction->unkTimer = 0;

    gActionStateTable[btlState].BtlAction_InitState(btlAction);
}