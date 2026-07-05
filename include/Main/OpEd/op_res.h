#ifndef OP_RES_H
#define OP_RES_H

#include "Utils.h"

#define OPRES_FLAG_TITLE (1 << 0) // 0x01
#define OPRES_FLAG_LOGO (1 << 1)  // 0x02

typedef struct HCdvd HCdvd;
typedef struct RwRaster RwRaster;

// at least 84 bytes
typedef struct OpResWork
{
    u32 requestFlags;           // 0x00
    u32 destroyFlags;           // 0x04
    HCdvd* titleCdvd;           // 0x08
    RwRaster* titleRasters[14]; // 0x0c
    void* unk_44[1];            // 0x44
    HCdvd* logoCdvd;            // 0x48
    RwRaster* logoRasters[2];   // 0x4c
} OpResWork;

void opResRequestTitle();
u32 opResCheckRequestTitle();
RwRaster* opResGetTitleRaster(u32 id);

#endif