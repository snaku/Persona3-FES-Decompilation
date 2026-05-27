#ifndef BTLORDER_H
#define BTLORDER_H

#include "Utils.h"

typedef struct BtlAction BtlAction;
typedef struct BtlUnit BtlUnit;

#define BTLORDER_CURRENT 0
#define BTLORDER_NEXT    1

// 108 bytes
typedef struct BtlOrder
{
    u16 flags;                    // 0x00
    u32 turnNo;                   // 0x04
    BtlAction* prevActionPlaying; // 0x250. The action who played before current action
    BtlAction* actions[12];       // 0x254
    BtlAction* actions2[12];      // 0x284. ??
} BtlOrder;

void btlOrderInit();
u32 btlOrderRemoveAction(BtlAction** actions, u32 arrSize, BtlAction* action);
u32 btlOrderAddAction(BtlAction* action);
BtlAction* btlOrderGetActionPlaying();
BtlAction* btlOrderGetPrevActionPlaying();
BtlAction* btlOrderGetActionByIdx(u16 idx);
BtlUnit* btlOrderGetUnitByIdx(u16 idx);

#endif