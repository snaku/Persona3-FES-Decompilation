#ifndef BTLPACKET_H
#define BTLPACKET_H

#include "Utils.h"

typedef struct BtlPacket BtlPacket;

// TODO: names
typedef enum
{
    BTLPACKET_TYPE_0,
    BTLPACKET_TYPE_1,
    BTLPACKET_TYPE_3D,
    BTLPACKET_TYPE_2D,

    BTLPACKET_TYPE_MAX
} BtlPacketType;

// 144 bytes. Base struct for a packet
struct BtlPacket
{
    u8 unkData1[0x40];
    u32 id;                          // 0x40
    s8 type;                         // 0x44. See enum 'BtlPacketType'
    u8 unkData2[0x13];
    u64 uid;                         // 0x58
    u64 actionUID;                   // 0x60
    void (*initFunc)(void* work);    // 0x68
    u32 (*updateFunc)(void* work);   // 0x6c
    void (*destroyFunc)(void* work); // 0x70
    void (*unk_74)(void* work);      // 0x74
    void* workData;                  // 0x78
    BtlPacket* next;                 // 0x7c
    BtlPacket* prev;                 // 0x80
    u8 unkData4[0x0c];
};

BtlPacket* btlPacketFindFirstByActionUID(u64 actionUID, u64 mask);
BtlPacket* btlPacketCreate(u32 id, u32 workDataSize);
u64 btlPacketRegister(BtlPacket* packet, s32 slot);

#endif