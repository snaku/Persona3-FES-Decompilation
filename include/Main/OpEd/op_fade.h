#ifndef OP_FADE_H
#define OP_FADE_H

#include "Utils.h"
#include "rw/rwplcore.h"

// 276 bytes
typedef struct OpFadeWork
{
    u32 flags;                // 0x00
    s32 state;                // 0x0
    u32 duration;             // 0x08
    u32 timer;                // 0x0c
    RwIm2DVertex vertices[4]; // 0x10
    RwRGBA color;             // 0x110
} OpFadeWork;

void opFadeStart(u32 duration);
void opFadeSetColor(const RwRGBA* color);

#endif