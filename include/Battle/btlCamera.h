#ifndef BTLCAMERA_H
#define BTLCAMERA_H

#include "Utils.h"
#include "Battle/btlPacket.h"
#include "rw/rtquat.h"

typedef struct BtlAction BtlAction;

// at least 256 bytes
typedef struct BtlCamera
{
    u8 unkData1[0x9c];
    RwV3d pos;         // 0x9c
    RtQuat rot;        // 0xa8
    f32 fovRad;        // 0xb8
    u8 unkData2[0x44];
} BtlCamera;

typedef enum
{
    BTLCAMERA_PACKET_SETSTATE = BTLPACKET_MAKE_ID(BTLPACKET_MODULE_CAMERA, 0),
} BtlCameraPacket;

// 8 bytes
typedef struct BtlCameraPacketSetState
{
    BtlAction* action; // 0x00
    u16 state;         // 0x04
} BtlCameraPacketSetState;

BtlPacket* btlCameraCreateSetStatePacket(BtlAction* action, u16 state);

#endif