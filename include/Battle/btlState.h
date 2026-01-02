#ifndef BTLSTATE_H
#define BTLSTATE_H

#include "Utils.h"

typedef enum
{
    BTL_STATE_NULL,
    BTL_STATE_NON,
    BTL_STATE_INIT,
    BTL_STATE_SCENE_SET,
    BTL_STATE_UNIT_CREATE,
    BTL_STATE_UNIT_LOAD,
    BTL_STATE_START,
    BTL_STATE_ACTION,
    BTL_STATE_REVIVAL_MES,
    BTL_STATE_REVIVAL,
    BTL_STATE_WIN,
    BTL_STATE_ENEMY_DEAD,
    BTL_STATE_CONDITION,
    BTL_STATE_LOSE,
    BTL_STATE_FADE_OUT,
    BTL_STATE_END,
    BTL_STATE_RESULT,
    BTL_STATE_EXIT,
    BTL_STATE_TEST,
    BTL_STATE_MC_NOP
} BattleState;

typedef struct 
{
    u32 currState;  // 0x0. See enum 'BattleState'
    u32 stateToSet; // 0x4. See enum 'BattleState'
    u32 stateTimer; // 0x8. Reset on state change
} BattleStateCtx;

typedef struct 
{
    void (*BtlState_InitState)(BattleStateCtx* btlStateCtx);
    u32 (*BtlState_UpdateState)(BattleStateCtx* btlStateCtx);
    const char* name;
} BattleStateEntry;

extern BattleStateEntry gBattleStateTable[];

void BtlState_SetStateAndInit(u32 btlState);
void BtlState_ProcessBattleState();
void BtlState_SetStateNon();

#endif