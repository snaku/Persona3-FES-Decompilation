#ifndef MATHTYPE_H
#define MATHTYPE_H

#include "Utils.h"

// 36 bytes
typedef struct
{
    f32 m[9];
} Mat3x3;

// 64 bytes
typedef struct
{
    f32 m[16];
} Mat4x4;

// 8 bytes
typedef struct
{
    f32 x;
    f32 y;
} Vec2f;

// 4 bytes
typedef struct
{
    s16 x;
    s16 y;
} Vec2s;

// 12 bytes
typedef struct
{
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

// 6 bytes
typedef struct
{
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

// 16 bytes
typedef struct
{
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Quat;

#endif