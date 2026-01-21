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
    u32 scenarioMode;            // 007cdfa4. See enum GameScenario
    u8 unkData2[0x448];
    KwlnTask* createTaskList;    // 007ce064. List of every task created, but not running
    KwlnTask* destroyTaskList;   // 007ce070. List of every task to be destroyed
    KwlnTask* prevDestroyedTask; // 007ce074
    KwlnTask* runningTaskList;   // 007ce07c. List of every task currently running
    KwlnTask* rootProcTask;      // 007ce0d0. Task name = "root proc"
    KwlnTask* dungeonTask;       // 007ce268. NULL when not in tartarus. Task name = "automatic dungeon"
    BattleCtx* btlCtx;           // 007ce3ec. NULL when not in a battle
} GlobalCtx;

extern GlobalCtx ctx; // 007cde80

void* P3FES_Memset(void* dst, u8 value, u32 size);

#endif