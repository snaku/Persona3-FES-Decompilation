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
typedef struct ScrData ScrData;
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

// FAKE STRUCT. These are just .sbss variables,
// but i just put them here until i know where they are supposed to be
typedef struct
{
    // data before
    KwlnTask* sfdPlayTask;       // 007cdf14. Task name = "H_SfdPlay"
    // data after
    u32 scenarioMode;            // 007cdfa4. See enum GameScenario
    KwlnTask* clndTask;          // 007cdfec. Task name = "CalenderDraw"
    // data after
    FogParameter fogParameter;   // 007ce0d4
    KwlnTask* draw3DTask;        // 007ce134. Task name = "3D Draw"
    KwlnTask* dungeonTask;       // 007ce268. NULL when not in tartarus. Task name = "automatic dungeon"
    BattleCtx* btlCtx;           // 007ce3ec. NULL when not in a battle
    // data after
    ScrData* currScr;            // 007ce5a8. Current script being executed
    // data after
} GlobalCtx;

extern GlobalCtx ctx; // 007cde80

void FUN_0019d400(const char* param_1, const char* file, u32 line);
void* P3FES_Memcpy(void* dst, void* src, u32 size);
void* P3FES_Memset(void* dst, u8 value, u32 size);

#endif