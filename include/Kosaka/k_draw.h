#ifndef K_DRAW_H
#define K_DRAW_H

#include "Utils.h"
#include "rw/rwplcore.h"

typedef struct KwlnTask KwlnTask;

// 24 bytes
typedef struct CylinderDrawWork
{
    u32 shouldDraw; // 0x00
    RwV3d pos;      // 0x04
    f32 radius;     // 0x10
    f32 height;     // 0x14
} CylinderDrawWork;

#endif