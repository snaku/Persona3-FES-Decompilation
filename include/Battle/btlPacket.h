#ifndef BTLPACKET_H
#define BTLPACKET_H

#include "Utils.h"

#define BTLPACKET_MAKE_ID(moduleId, _id) (((moduleId) << 8) | ((_id)))

// TODO
typedef enum
{
    BTLPACKET_MODULE_NULL,
    BTLPACKET_MODULE_UNIT,
    BTLPACKET_MODULE_SOUND = 9,
    BTLPACKET_MODULE_BATTLE = 255
} BtlPacketModule;

// TODO: names
typedef enum
{
    BTLPACKET_TYPE_0,
    BTLPACKET_TYPE_1,
    BTLPACKET_TYPE_3D,
    BTLPACKET_TYPE_2D,

    BTLPACKET_TYPE_MAX
} BtlPacketType;

typedef struct BtlPacket BtlPacket;

// 144 bytes. Base struct for a packet
struct BtlPacket
{
    u8 unkData1[0x40];
    u32 id;                          // 0x40. See macro 'BTLPACKET_MAKE_ID' and enum 'BtlPacketModule'
    s8 type;                         // 0x44. See enum 'BtlPacketType'
    s8 unk_45;                       // 0x45
    s8 unk_46;                       // 0x46
    u8 unk_47;                       // 0x47
    u8 unkData2[0x04];
    s32 unk_4c;                      // 0x4c
    s32 unk_50;                      // 0x50
    s32 unk_54;                      // 0x54
    u64 uid;                         // 0x58
    u64 actionUID;                   // 0x60
    void (*initFunc)(void* work);    // 0x68
    u32 (*updateFunc)(void* work);   // 0x6c
    void (*destroyFunc)(void* work); // 0x70
    void (*unk_74)(void* work);      // 0x74
    void* workData;                  // 0x78
    BtlPacket* next;                 // 0x7c
    BtlPacket* prev;                 // 0x80
    u8 unkData3[0x0c];
};

BtlPacket* btlPacketFindFirstByActionUID(u64 actionUID, u64 mask);
u32 btlPacketCount();
u32 btlPacketCountById(u16 id);
void btlPacket0027e4d0();
BtlPacket* btlPacketCreate(u32 id, u32 workDataSize);
u64 btlPacketRegister(BtlPacket* packet, u8 type);

#endif