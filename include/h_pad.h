#ifndef H_PAD_H
#define H_PAD_H

#include "Utils.h"
#include "sce/libpad.h"

#define HPAD_BTN_L2       SCE_PADL2     // 0x01
#define HPAD_BTN_R2       SCE_PADR2     // 0x02
#define HPAD_BTN_L1       SCE_PADL1     // 0x04
#define HPAD_BTN_R1       SCE_PADR1     // 0x08
#define HPAD_BTN_TRIANGLE SCE_PADRup    // 0x10
#define HPAD_BTN_CIRCLE   SCE_PADRright // 0x20
#define HPAD_BTN_CROSS    SCE_PADRdown  // 0x40
#define HPAD_BTN_SQUARE   SCE_PADRleft  // 0x80
#define HPAD_BTN_SELECT   SCE_PADselect // 0x100
#define HPAD_BTN_L3       SCE_PADi      // 0x200
#define HPAD_BTN_R3       SCE_PADj      // 0x400
#define HPAD_BTN_START    SCE_PADstart  // 0x800
#define HPAD_BTN_UP       SCE_PADLup    // 0x1000
#define HPAD_BTN_RIGHT    SCE_PADLright // 0x2000
#define HPAD_BTN_DOWN     SCE_PADLdown  // 0x4000
#define HPAD_BTN_LEFT     SCE_PADLleft  // 0x8000

#define HPAD_CHKBTN_PRESSED(port, btns)     ((gPads[(port)].btn[0].pressed & (btns)) != 0)
#define HPAD_CHKBTN_JUSTPRESSED(port, btns) ((gPads[(port)].btn[0].justPressed & (btns)) != 0)
#define HPAD_CHKBTN_RELEASED(port, btns)    ((gPads[(port)].btn[0].released & (btns)) != 0)

typedef enum
{
    HPAD_PORT_1,
    HPAD_PORT_2,
    HPAD_PORT_MAX
} HPadPort;

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

extern HPad gWorkPads[HPAD_PORT_MAX];
extern HPad gPads[HPAD_PORT_MAX];

void H_Pad_Init();

#endif