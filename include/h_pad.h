#ifndef H_PAD_H
#define H_PAD_H

#include "Utils.h"

typedef enum
{
    // TODO
    HPAD_STATE_READY = 5,
} HPadState;

// 8 bytes
typedef struct HPadButtons
{
    u16 pressed;      // 0x00
    u16 justPressed;  // 0x02
    u16 released;     // 0x04
    u16 justReleased; // 0x06
} HPadButtons;

// 54 bytes
typedef struct HPad
{
    s16 unk_00;         // 0x00
    u16 state;          // 0x02. See 'HPadState' enum
    s16 unk_04;         // 0x04
    s16 unk_06;         // 0x06
    u16 port;           // 0x08
    u16 slot;           // 0x0a
    HPadButtons btn[2]; // 0x0c. Second index is the same as the first one, but ignoring dpad
    u8 unkData2[0x04];
    s8 lstickX;         // 0x20
    s8 lstickY;         // 0x21
    s8 rstickX;         // 0x22
    s8 rstickY;         // 0x23
    u8 unkData3[0x12];
} HPad;

extern HPad gPads[4];

#endif