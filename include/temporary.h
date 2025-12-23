/**
* This file contains functions, structs, enums and macros that have been identified,
* but i don't have enough informations to put them in their proper files yet.
*/

#ifndef TEMPORARY_H
#define TEMPORARY_H

#include "Utils.h"
#include "mathTypes.h"

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
} BattleData;

// 4 bytes
typedef struct
{
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} RGBA;

#endif