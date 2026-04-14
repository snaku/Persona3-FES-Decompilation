#ifndef H_PAD_H
#define H_PAD_H

#include "Utils.h"

#define HPAD_PORT1   HPAD_PROCESSED_PORT1
#define HPAD_PORT2   HPAD_PROCESSED_PORT2 // Debug only
#define HPAD_MAXPORT 2

#define HPAD_BTN_L2       (1 << 0)  // 0x01
#define HPAD_BTN_R2       (1 << 1)  // 0x02
#define HPAD_BTN_L1       (1 << 2)  // 0x04
#define HPAD_BTN_R1       (1 << 3)  // 0x08
#define HPAD_BTN_TRIANGLE (1 << 4)  // 0x10
#define HPAD_BTN_CIRCLE   (1 << 5)  // 0x20
#define HPAD_BTN_CROSS    (1 << 6)  // 0x40
#define HPAD_BTN_SQUARE   (1 << 7)  // 0x80
#define HPAD_BTN_SELECT   (1 << 8)  // 0x100
#define HPAD_BTN_L3       (1 << 9)  // 0x200
#define HPAD_BTN_R3       (1 << 10) // 0x400
#define HPAD_BTN_START    (1 << 11) // 0x800
#define HPAD_BTN_UP       (1 << 12) // 0x1000
#define HPAD_BTN_RIGHT    (1 << 13) // 0x2000
#define HPAD_BTN_DOWN     (1 << 14) // 0x4000
#define HPAD_BTN_LEFT     (1 << 15) // 0x8000

#define HPAD_CHKBTN_PRESSED(port, btns)     ((gPads[(port)].btn[0].pressed & (btns)) != 0)
#define HPAD_CHKBTN_JUSTPRESSED(port, btns) ((gPads[(port)].btn[0].justPressed & (btns)) != 0)
#define HPAD_CHKBTN_RELEASED(port, btns)    ((gPads[(port)].btn[0].released & (btns)) != 0)

typedef enum
{
    HPAD_PROCESSED_PORT1,
    HPAD_PROCESSED_PORT2,

    HPAD_WORK_PORT1,
    HPAD_WORK_PORT2,

    HPAD_INDEX_MAX
} HPadIndex;

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

extern HPad gPads[HPAD_INDEX_MAX];

void H_Pad_Init();

#endif