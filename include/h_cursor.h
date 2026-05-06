#ifndef H_CURSOR_H
#define H_CURSOR_H

#include "Utils.h"
#include "rw/rwcore.h"

typedef struct KwlnTask KwlnTask;

// 336 bytes
typedef struct HCursorWork
{
    RwIm2DVertex vertices[4]; // 0x00
    u8 unkData[0x10];
    u16 state;                // 0x110
    RwV2d pos;                // 0x114
    RwRect rect;              // 0x11c
    f32 zOffset;              // 0x12c
    RwRGBA colors[4];         // 0x130
    u32 shouldDraw;           // 0x140
    s16 unk_144;              // 0x144
} HCursorWork;

KwlnTask* H_Cursor_CreateTask(KwlnTask* parent, f32 zOffset, RwV2d pos, RwRect rect, RwRGBA color);
u32 H_Cursor_GetShouldDraw(KwlnTask* hcursorTask);

#endif