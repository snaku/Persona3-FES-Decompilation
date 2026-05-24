#ifndef BATTLE_H
#define BATTLE_H

#include "Battle/btlMain.h"
#include "datUnit.h"

#define BTL_FLAG_ACTIVE      (1 << 0)  // 0x1. Currently in a battle. Destroy 'battle' task if not set
#define BTL_FLAG_IS_BOSS     (1 << 15) // 0x8000. Battle is a boss battle
#define BTL_FLAG_MULTI_ENEMY (1 << 16) // 0x10000. More than one enemy in the battle

#define BTL_CURRACTION 0   // current action playing
#define BTL_NEXTACTION 1   // next action playing
#define BTL_MAXACTIONS 12

typedef struct KwlnTask KwlnTask;
typedef struct BtlAction BtlAction;
typedef struct BtlUnit BtlUnit;

// 8 bytes
typedef struct BtlActionList
{
    BtlAction* head; // 0x00
    BtlAction* tail; // 0x04
} BtlActionList;

// 8 bytes
typedef struct BtlUnitList
{
    BtlUnit* head; // 0x00
    BtlUnit* tail; // 0x04
} BtlUnitList;

// 3440 bytes
typedef struct Battle
{
    u8 unkData1[0x0c];
    u32 flags;                            // 0x0c
    u8 unkData2[0x138];
    BtlActionList actionList;             // 0x148
    BtlUnitList unitList[UNIT_GENUS_MAX]; // 0x150
    u8 unkData3[0xf0];
    BtlAction* prevActionPlaying;         // 0x250. The action who played before current action
    BtlAction* actions[BTL_MAXACTIONS];   // 0x254
    BtlAction* unk_284[BTL_MAXACTIONS];   // 0x284
    BtlStateWork stateWork;               // 0x2b4
    u8 unkData6[0xa58];
    KwlnTask* btlTask;                    // 0xd18
    u8 unkData7[0x10];
    KwlnTask* btlPanelTask;               // 0xd2c
    u8 unkData8[0x40];
} Battle;

extern Battle* gBtl;

u64 btlGetUID();
KwlnTask* btlGetTask();
void btlSetIsBoss();

#endif