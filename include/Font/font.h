#ifndef H_FONT_H
#define H_FONT_H

#include "Utils.h"
#include "rw/rwcore.h"

// 32 bytes
typedef struct frFontRasterGlyph
{
    u16 code;            // 0x00
    u16 drawCount;       // 0x02
    s32 offsetX;         // 0x04
    s32 offsetY;         // 0x08
    s32 advance;         // 0x0c
    u32 color;           // 0x10
    u8 renderFlag;       // 0x14
    u8 fontId;           // 0x15
    u8 flag2;            // 0x16
    u8 state;            // 0x17
    u8 cellW;            // 0x18
    u8 cellH;            // 0x19
    INSERT_PADDING(0x6); // 0x1a
} frFontRasterGlyph;

#endif