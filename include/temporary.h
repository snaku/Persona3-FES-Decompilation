/**
* This file contains functions, structs, enums and macros that have been identified,
* but i don't have enough informations to put them in their proper files yet.
*/

#ifndef TEMPORARY_H
#define TEMPORARY_H

#include "Utils.h"
#include "mathTypes.h"
#include "Battle/btlActor.h"

const f32 PI = 3.141592f; // 007cae58

#define QUARTER_PI ((PI) / 4)
#define DEG_TO_RAD(deg) (PI * (deg) / 180.0f)
#define RAD_TO_DEG(rad) ((rad) * 180.0f / PI)

typedef struct
{
    // TODO
    Vec3f pos;
    Vec3f rot;
    f32 fov;
} Camera;

typedef struct
{
    // TODO
    u32 flags;
    Camera camera;
    BattleActor* unkBtlActor_148;  // 0x148
    BattleActor* prevActorCreated; // 0x14c
    // Data inbetween...
    BattleActor* prevActorPlaying; // 0x250. The actor who played before current actor
    BattleActor* currActorPlaying; // 0x254. The actor who's currently playing
    BattleActor* nextActorPlaying; // 0x258. The actor who will play next
    BattleActor* unkBtlActor_25c;  // 0x25c
    // Data inbetween...
    BattleActor* unkBtlActor_284;   // 0x284
} BattleCtx;

// 4 bytes
typedef struct
{
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} RGBA;

// TODO
typedef struct
{
    u16 flags;
    u32 currFloor;
} TartarusData;

// TODO
typedef struct
{
    TartarusData* tartarus; // 0x3c
} UnkStruct1;

// TODO
typedef struct
{
    u8 unkData1[0x124];
    u32 scenarioMode;       // 007cdfa4. See enum GameScenario
    u8 unkData2[0x448];
    BattleCtx* btlCtx;     // 007ce3ec. NULL when not in a battle
    UnkStruct1* unkStruct1; // 007ce268. NULL when not in tartarus
} GlobalCtx;

GlobalCtx ctx; // 007cde80

u32 GlobalCtx_GetCurrentTartarusFloor();
void* P3FES_Memset(void* dst, u8 value, u32 size);

#endif