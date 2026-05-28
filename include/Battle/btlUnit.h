#ifndef BTLUNIT_H
#define BTLUNIT_H

#include "Utils.h"
#include "Battle/btlPacket.h"
#include "rw/rwplcore.h"

#define BTLUNIT_FLAG2_DEAD   (1 << 0) // 0x01
#define BTLUNIT_FLAG2_ENDURE (1 << 4) // 0x10
#define BTLUNIT_FLAG2_UNK40  (1 << 6) // 0x40

typedef struct DatUnit DatUnit;
typedef struct Model Model;
typedef struct BtlPacket BtlPacket;

// TODO
typedef enum
{
    BTLUNIT_PACKET_ROTATE = BTLPACKET_MAKE_ID(BTLPACKET_MODULE_UNIT, 13)
} BtlUnitPacket;

typedef struct BtlUnit BtlUnit;

// 2616 bytes
struct BtlUnit
{
    u32 flags;          // 0x00
    RwV3d pos1;         // 0x04
    RwV3d pos2;         // 0x10
    u8 unkData1[0x80];
    u32 flags2;         // 0x9c. Temp name
    u16 packetCount;    // 0xa0
    u8 genus;           // 0xa2. See enum 'UnitGenus'
    s32 unk_a4;         // 0xa4
    u32 id;             // 0xa8
    u8 unkData2[0x94f];
    u16 resTypeId;      // 0x9f2
    Model* mdl;         // 0x9f4
    u8 unkData3[0x34];
    DatUnit* datUnit;   // 0xa2c
    BtlUnit* next;      // 0xa30
    BtlUnit* prev;      // 0xa34
};

// 24 bytes
typedef struct BtlUnitPacketRotate
{
    BtlUnit* unit; // 0x00
    RwV3d rot;     // 0x04
    s32 unk_10;    // 0x10
    s32 unk_14;    // 0x14
} BtlUnitPacketRotate;

extern RwV3d gUnk_00957188;

BtlPacket* btlUnitCreateRotatePacket(BtlUnit* unit, const RwV3d* rot, s32 param_3);

#endif