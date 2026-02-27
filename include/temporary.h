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

void FUN_0019d400(const char* param_1, const char* file, u32 line);
void* memcpy(void* dst, void* src, u32 size);
void* memset(void* dst, u8 value, u32 size);

#endif