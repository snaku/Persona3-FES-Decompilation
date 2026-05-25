#ifndef BTLTARGET_H
#define BTLTARGET_H

#include "Utils.h"

typedef struct BtlAction BtlAction;

// 80 bytes
typedef struct BtlTarget
{
    BtlAction* targetedActions[12]; // 0x00
    s16 unk_30;                     // 0x30
    u16 targetedCount;              // 0x32
    u16 commandId;                  // 0x34. Current command in target mode (attack, skills, ...)
    u16 specificId;                 // 0x36. Id depending of the current command. Ex: if the cmd is item, then it will be the item id
    u16 unk_38;
    u8 unkData1[0x04];
    u16 unk_3e[3];                  // 0x3e
    u16 oldCommandId;               // 0x44
    u16 oldSpecificId;              // 0x46
    u8 unkData2[0x08];
} BtlTarget;

void btlTargetInit(BtlTarget* target);

#endif