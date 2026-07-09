#ifndef BP_RES_H
#define BP_RES_H

#include "Utils.h"

#define BPRES_FLAG_BPALL (1 << 0) // 0x01

typedef struct HCdvd HCdvd;

// at least 84 bytes
typedef struct BpResWork
{
    u32 requestFlags; // 0x00
    u32 destroyFlags; // 0x04
    HCdvd* bpAllCdvd; // 0x08
    u8 unkData1[0x20];
    s32 unk_2c[3];    // 0x2c
    u8 unkData[0x0c];
    s32 partyIdx;     // 0x44
    s32 partyIds[3];  // 0x48
} BpResWork;

void bpResRequestBpAll();
u32 bpResCheckRequestBpAll();

#endif