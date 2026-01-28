/**
* This file contains functions, structs, enums and macros that have been identified,
* but i don't have enough informations to put them in their proper files yet.
*/

#ifndef TEMPORARY_H
#define TEMPORARY_H

#include "Utils.h"
#include "Battle/btlActor.h"
#include "rw/rwcore.h"

extern const f32 PI; // 007cae58

#define QUARTER_PI ((PI) / 4)
#define DEG_TO_RAD(deg) (PI * (deg) / 180.0f)
#define RAD_TO_DEG(rad) ((rad) * 180.0f / PI)

typedef struct BattleCtx BattleCtx;
typedef struct KwlnTask KwlnTask;
typedef struct RwCamera RwCamera;

typedef struct
{
    u32 fogEnabled;
    u8 r;              // red component
    u8 unkData1[0x03];
    u8 g;              // green component
    u8 unkData2[0x03];
    u8 b;              // blue component
    u8 unkData3[0x03];
    u8 a;              // alpha component
} FogParameter;

// TODO
typedef struct
{
    u8 unkData1[0x124];
    u32 scenarioMode;            // 007cdfa4. See enum GameScenario
    u8 unkData2[0x448];
    KwlnTask* stagedTaskHead;    // 007ce064. Head of tasks in 'KWLN_TASK_STATE_CREATED' state
    KwlnTask* stagedTaskTail;    // 007ce068. Tail of tasks in 'KWLN_TASK_STATE_CREATED' state
    u32 numTaskStaged;           // 007ce06c. Total number of task in 'KWLN_TASK_STATE_CREATED' state
    KwlnTask* destroyTaskHead;   // 007ce070. Head of tasks in 'KWLN_TASK_STATE_DESTROY' state
    KwlnTask* destroyTaskTail;   // 007ce074. Tail of tasks in 'KWLN_TASK_STATE_DESTROY' state
    u32 numTaskDestroy;          // 007ce078. Total number of task in 'KWLN_TASK_STATE_DESTROY' state
    KwlnTask* runningTaskHead;   // 007ce07c. Head of tasks in 'KWLN_TASK_STATE_RUNNING' state
    KwlnTask* runningTaskTail;   // 007ce080. Tail of tasks in 'KWLN_TASK_STATE_RUNNING' state
    u32 numTaskRunning;          // 007ce084. Total number of task in 'KWLN_TASK_STATE_RUNNING' state
    RwCamera* mainCamera;        // 007ce0c0
    KwlnTask* rootProcTask;      // 007ce0d0. Task name = "root proc"
    FogParameter fogParameter;   // 007ce0d4
    RwRGBA clearColor;           // 007ce128
    KwlnTask* draw3DTask;        // 007ce134. Task name = "3D Draw"
    KwlnTask* dungeonTask;       // 007ce268. NULL when not in tartarus. Task name = "automatic dungeon"
    BattleCtx* btlCtx;           // 007ce3ec. NULL when not in a battle
} GlobalCtx;

extern GlobalCtx ctx; // 007cde80

void* P3FES_Memset(void* dst, u8 value, u32 size);

#endif