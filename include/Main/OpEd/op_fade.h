#ifndef OP_FADE_H
#define OP_FADE_H

#include "Utils.h"
#include "rw/rwplcore.h"

typedef enum
{
    OPFADE_STATE_START,
    OPFADE_STATE_IN,
    OPFADE_STATE_OUT
} OpFadeState;

// 276 bytes
typedef struct OpFadeWork
{
    u32 flags;                // 0x00
    s32 state;                // 0x04. See enum 'OpFadeState'
    u32 duration;             // 0x08
    u32 timer;                // 0x0c
    RwIm2DVertex vertices[4]; // 0x10
    RwRGBA color;             // 0x110
} OpFadeWork;

void opFadeStart(u32 duration);
void opFadeSetColor(const RwRGBA* color);
void opFadeIn();
void opFadeOut();

#endif