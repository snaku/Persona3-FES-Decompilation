#ifndef BTLUNIT_H
#define BTLUNIT_H

#include "Utils.h"
#include "rw/rwplcore.h"

#define BTLUNIT_FLAG2_DEAD   (1 << 0) // 0x01
#define BTLUNIT_FLAG2_ENDURE (1 << 4) // 0x10
#define BTLUNIT_FLAG2_UNK40  (1 << 6) // 0x40

typedef struct DatUnit DatUnit;
typedef struct Model Model;

typedef struct BtlUnit BtlUnit;

// 2616 bytes
struct BtlUnit
{
    u32 flags;          // 0x00
    RwV3d pos1;         // 0x04
    RwV3d pos2;         // 0x10
    u8 unkData1[0x80];
    u32 flags2;         // 0x9c. Temp name
    u8 unkData2[0x02];
    u8 genus;           // 0xa2. See enum 'UnitGenus'
    s32 unk_a4;         // 0xa4
    u32 id;             // 0xa8
    u8 unkData3[0x94f];
    u16 resTypeId;      // 0x9f2
    Model* mdl;         // 0x9f4
    u8 unkData4[0x34];
    DatUnit* datUnit;   // 0xa2c
    BtlUnit* next;      // 0xa30
    BtlUnit* prev;      // 0xa34
};

#endif