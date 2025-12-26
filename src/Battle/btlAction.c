#include "Battle/btlAction.h"

typedef struct
{
    void (*btlActionFunc)(BattleActionStruct* btlAction);
    const char* name;
} BattleActionStateEntry;

static BattleActionStateEntry gActionStateTable[] = 
{
    // TODO
};

// FUN_00299d60
void BtlAction_SetStateAndExecute(BattleActionStruct* btlAction, u16 btlState)
{
    btlAction->oldState = btlAction->currState;
    btlAction->currState = btlState;
    btlAction->unk_1C = 0;

    gActionStateTable[btlState].btlActionFunc(btlAction);
}