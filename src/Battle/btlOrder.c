#include "Battle/battle.h"
#include "Battle/btlAction.h"
#include "temporary.h"

// FUN_0029b090
void btlOrderInit()
{
    memset(&gBtl->order, 0, sizeof(BtlOrder));
}

// FUN_0029a2c0
u32 btlOrderAdd(BtlAction* action)
{
    BtlAction** actions;
    BtlAction* curr;
    s32 i;

    actions = gBtl->order.actions;
    for (i = 0; i < BTL_MAXACTIONS; i++)
    {
        curr = *actions;
        if (curr != NULL)
        {
            actions++;
        }
        else
        {
            break;
        }
    }

    if (i == BTL_MAXACTIONS)
    {
        return false;
    }

    *actions = action;

    return true;
}

// FUN_0029ad20
BtlAction* btlOrderGetPlaying()
{
    BtlAction* action;

    action = gBtl->order.actions2[BTLORDER_CURRENT];
    if (action == NULL)
    {
        action = gBtl->order.actions[BTLORDER_CURRENT];
    }

    return action;
}

// FUN_0029ad50
BtlAction* btlOrderGetPrevPlaying()
{
    return gBtl->order.prevActionPlaying;
}

// FUN_0029ad60
BtlAction* btlOrderGetActionByIdx(u16 idx)
{
    if (idx >= BTL_MAXACTIONS)
    {
        return NULL;
    }

    return gBtl->order.actions[idx];
}

// FUN_0029ada0
BtlUnit* btlOrderGetUnitByIdx(u16 idx)
{
    BtlAction* action;

    if (idx >= BTL_MAXACTIONS)
    {
        action = NULL;
    }
    else
    {
        action = gBtl->order.actions[idx];
    }

    if (action == NULL)
    {
        return NULL;
    }

    return action->unit;
}