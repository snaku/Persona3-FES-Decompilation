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

// 324 bytes
typedef struct H_Cursor_Work
{
    RwIm2DVertex verts[4]; // 0x00
    INSERT_PADDING(0x10);  // 0x100
    RwInt16 state;         // 0x110
    RwInt16 pad112;        // 0x112
    RwReal posX;           // 0x114
    RwReal posY;           // 0x118
    RwUInt32 unk11C;       // 0x11c
    RwUInt32 unk120;       // 0x120
    RwInt32 width;         // 0x124
    RwInt32 height;        // 0x128
    RwReal zBias;          // 0x12c
    RwRGBA colors[4];      // 0x130
    RwUInt32 active;       // 0x140
} H_Cursor_Work;

KwlnTask* H_Cursor_CreateTask(KwlnTask* parent, f32 zOffset, RwV2d pos, RwRect rect, RwRGBA color);
u32 H_Cursor_GetShouldDraw(KwlnTask* hcursorTask);
void H_Cursor_SetPos(KwlnTask* hcursorTask, RwV2d pos);
void H_Cursor_SetRect(KwlnTask* hcursorTask, RwRect rect);
void H_Cursor_SetZOffset(KwlnTask* hcursorTask, f32 zOffset);
void H_Cursor_SetColor(KwlnTask* hcursorTask, RwRGBA color);

#endif