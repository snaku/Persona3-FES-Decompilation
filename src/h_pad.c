#include "h_pad.h"
#include "temporary.h"

static HPad sWorkPads[HPAD_PORT_MAX]; // 007e09b0
HPad gPads[HPAD_PORT_MAX];            // 007e0940

static u_long128 sAddrPort1[scePadDmaBufferMax] __attribute__((aligned(64))); // 007e0840
static u_long128 sAddrPort2[scePadDmaBufferMax] __attribute__((aligned(64))); // 007e0740
static u8 sRDataPort2[32]; // 007e0720. unused
static u8 sRDataPort1[32]; // 007e0700

// FUN_00103000
void H_Pad_Init()
{
    s32 i;
    HPad* workPads;

    memset(&sWorkPads[HPAD_PORT_1], 0, sizeof(HPad));
    memset(&sWorkPads[HPAD_PORT_2], 0, sizeof(HPad));

    memset(&gPads[HPAD_PORT_1], 0, sizeof(HPad));
    memset(&gPads[HPAD_PORT_2], 0, sizeof(HPad));

    scePadInit(0);
    scePadPortOpen(HPAD_PORT_1, 0, sAddrPort1);
    scePadPortOpen(HPAD_PORT_2, 0, sAddrPort2);
    
    // TODO: Find a way to force i in a3 reg and 3 in a0 reg
    i = 0;
    workPads = sWorkPads;
    for (; i < HPAD_PORT_MAX; i++)
    {
        workPads[i].port = i;
        workPads[i].unk_00 = workPads[i].state = workPads[i].slot = 0;
        workPads[i].unk_04 = 3;
    }
}