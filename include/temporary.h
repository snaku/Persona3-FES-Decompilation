/**
* This file contains functions, structs, enums and macros that have been identified,
* but i don't have enough informations to put them in their proper files yet.
*/

#ifndef TEMPORARY_H
#define TEMPORARY_H

#include "Utils.h"
#include "mathTypes.h"
#include "Battle/btlActor.h"

extern const f32 PI; // 007cae58

#define QUARTER_PI ((PI) / 4)
#define DEG_TO_RAD(deg) (PI * (deg) / 180.0f)
#define RAD_TO_DEG(rad) ((rad) * 180.0f / PI)

typedef struct BattleCtx BattleCtx;
typedef struct KwlnTask KwlnTask;

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
    u8 unkData1[0x124];
    u32 scenarioMode;       // 007cdfa4. See enum GameScenario
    u8 unkData2[0x448];
    KwlnTask* unkTask1;     // 007ce064
    KwlnTask* unkTask2;     // 007ce070
    KwlnTask* unkTask3;     // 007ce074
    KwlnTask* rootProcTask; // 007ce07c. Task name = "root proc"
    KwlnTask* dungeonTask;  // 007ce268. NULL when not in tartarus. Task name = "automatic dungeon"
    BattleCtx* btlCtx;      // 007ce3ec. NULL when not in a battle
} GlobalCtx;

extern GlobalCtx ctx; // 007cde80

void* P3FES_Memset(void* dst, u8 value, u32 size);

#endif