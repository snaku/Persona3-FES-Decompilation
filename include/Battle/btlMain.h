#ifndef BTLMAIN_H
#define BTLMAIN_H

#include "Utils.h"

typedef enum
{
    BTL_STATE_NULL,
    BTL_STATE_NON,
    BTL_STATE_INIT,
    BTL_STATE_SCENESET,
    BTL_STATE_UNITCREATE,
    BTL_STATE_UNITLOAD,
    BTL_STATE_START,
    BTL_STATE_ACTION,
    BTL_STATE_REVIVALMES,
    BTL_STATE_REVIVAL,
    BTL_STATE_WIN,
    BTL_STATE_ENEMYDEAD,
    BTL_STATE_CONDITION,
    BTL_STATE_LOSE,
    BTL_STATE_FADEOUT,
    BTL_STATE_END,
    BTL_STATE_RESULT,
    BTL_STATE_EXIT,
    BTL_STATE_TEST,
    BTL_STATE_MC
} BtlState;

// at least 12 bytes
typedef struct BtlStateWork
{
    u32 currState;  // 0x0. See enum 'BtlState'
    u32 stateToSet; // 0x4. See enum 'BtlState'
    u32 stateTimer; // 0x8. Reset on state change
} BtlStateWork;

void btlMainSetState(u32 state);
void btlMainUpdateState();
void btlMainSetStateNon();

void btlMainLoadScene();

#endif