#ifndef BTLCAMERA_H
#define BTLCAMERA_H

#include "Utils.h"
#include "rw/rtquat.h"

// at least 256 bytes
typedef struct BtlCamera
{
    u8 unkData1[0x9c];
    RwV3d pos;         // 0x9c
    RtQuat rot;        // 0xa8
    f32 fovRad;        // 0xb8
    u8 unkData2[0x44];
} BtlCamera;

#endif