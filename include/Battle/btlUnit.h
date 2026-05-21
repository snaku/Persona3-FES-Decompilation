#ifndef BTLUNIT_H
#define BTLUNIT_H

#include "Utils.h"
#include "rw/rwplcore.h"

typedef struct DatUnit DatUnit;

// 2616 bytes
typedef struct BtlUnit
{
    u32 flags;          // 0x00
    RwV3d pos1;         // 0x04
    RwV3d pos2;         // 0x10
    u8 unkData1[0x80];
    u32 unk_9c;         // 0x9c
    u8 unkData2[0x98c];
    DatUnit* datUnit;   // 0xa2c
    u8 unkData3[0x08];
} BtlUnit;

#endif