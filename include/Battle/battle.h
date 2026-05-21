#ifndef BATTLE_H
#define BATTLE_H

#include "Battle/btlMain.h"

typedef struct KwlnTask KwlnTask;
typedef struct BattleCtx BattleCtx;

#define BTL_FLAG_ACTIVE      (1 << 0)  // 0x1. Currently in a battle. Destroy 'battle' task if not set
#define BTL_FLAG_IS_BOSS     (1 << 15) // 0x8000. Battle is a boss battle
#define BTL_FLAG_MULTI_ENEMY (1 << 16) // 0x10000. More than one enemy in the battle

typedef struct BtlAction BtlAction;
typedef struct KwlnTask KwlnTask;

// 3440 bytes
typedef struct Battle
{
    u8 unkData1[0x0c];
    u32 flags;                    // 0x0c
    u8 unkData2[0x138];
    BtlAction* unk_148;           // 0x148
    BtlAction* prevActionCreated; // 0x14c
    u8 unkData3[0x100];
    BtlAction* prevActionPlaying; // 0x250. The actor who played before current actor
    BtlAction* currActionPlaying; // 0x254. The actor who's currently playing
    BtlAction* nextActionPlaying; // 0x258. The actor who will play next
    BtlAction* unk_25c;           // 0x25c
    u8 unkData4[0x24];
    BtlAction* unk_284;           // 0x284
    u8 unkData5[0x2c];
    BtlStateWork stateWork;       // 0x2b4
    u8 unkData6[0xa58];
    KwlnTask* btlTask;            // 0xd18
    u8 unkData7[0x10];
    KwlnTask* btlPanelTask;       // 0xd2c
    u8 unkData8[0x40];
} Battle;

extern Battle* gBtl;

KwlnTask* btlGetTask();
void btlSetIsBoss();

#endif