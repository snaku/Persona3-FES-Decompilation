#ifndef BTLCTX_H
#define BTLCTX_H

#include "Battle/btlState.h"
#include "cameraStruct.h"

#define BATTLE_FLAG_BTL_ACTIVE  (1 << 0)  // 0x1. Currently in a battle. Destroy 'battle' task if not set
#define BATTLE_FLAG_IS_BOSS_BTL (1 << 15) // 0x8000. Battle is a boss battle
#define BATTLE_FLAG_MULTI_ENEMY (1 << 16) // 0x10000. More than one enemy in the battle

typedef struct BattleActor BattleActor;
typedef struct KwlnTask KwlnTask;

// 3440 bytes. TODO
typedef struct BattleCtx
{
    u8 unkData1[0x0c];
    u32 flags;                     // 0x0c
    Camera camera;                 
    BattleActor* unkBtlActor_148;  // 0x148
    BattleActor* prevActorCreated; // 0x14c
    // Data inbetween...
    BattleActor* prevActorPlaying; // 0x250. The actor who played before current actor
    BattleActor* currActorPlaying; // 0x254. The actor who's currently playing
    BattleActor* nextActorPlaying; // 0x258. The actor who will play next
    BattleActor* unkBtlActor_25c;  // 0x25c
    // Data inbetween...
    BattleActor* unkBtlActor_284;  // 0x284
    // Data inbetween...
    BattleStateCtx btlStateCtx;    // 0x2b4
    // Data inbetween...
    KwlnTask* btlTask;             // 0xd18
    u8 unkData2[0x10];
    KwlnTask* btlPanelTask;        // 0xd2c
} BattleCtx;

#endif