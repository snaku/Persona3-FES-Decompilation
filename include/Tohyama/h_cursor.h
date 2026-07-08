#ifndef H_CURSOR_H
#define H_CURSOR_H

#include "Utils.h"
#include "rw/rwcore.h"

typedef struct KwlnTask KwlnTask;

typedef enum
{
    HCURSOR_STATE_INIT,
    HCURSOR_STATE_UPDATE,
    HCURSOR_STATE_STOP
} HCursorState;

// 336 bytes
typedef struct HCursorWork
{
    RwIm2DVertex vertices[4]; // 0x00
    u8 unusedData[0x10];
    s16 state;                // 0x110. See enum 'HCursorState'
    RwV2d pos;                // 0x114
    RwRect rect;              // 0x11c
    f32 zOffset;              // 0x12c
    RwRGBA colors[4];         // 0x130
    u32 shouldDraw;           // 0x140
    s16 unused_144;           // 0x144
} HCursorWork;

KwlnTask* H_Cursor_CreateTask(KwlnTask* parent, f32 zOffset, RwV2d pos, RwRect rect, RwRGBA color);
u32 H_Cursor_GetShouldDraw(KwlnTask* hcursorTask);
void H_Cursor_SetPos(KwlnTask* hcursorTask, RwV2d pos);
void H_Cursor_SetRect(KwlnTask* hcursorTask, RwRect rect);
void H_Cursor_SetZOffset(KwlnTask* hcursorTask, f32 zOffset);
void H_Cursor_SetColor(KwlnTask* hcursorTask, RwRGBA color);

#endif