#ifndef RPWORLD_H
#define RPWORLD_H

#include "rw/rwcore.h"

typedef struct RpWorld RpWorld; // TODO

#define rpCLUMP 2

typedef struct RpClump RpClump;

typedef RpClump* (*RpClumpCallBack)(RpClump* clump, void* data);

// 44 bytes
struct RpClump
{
    RwObject object;          // 0x00
    RwLinkList atomicList;    // 0x08
    RwLinkList lightList;     // 0x10
    RwLinkList cameraList;    // 0x18
    RwLLLink inWorldLink;     // 0x20
    RpClumpCallBack callback; // 0x28
};

// 60 bytes
typedef struct RpLight
{
    RwObjectHasFrame object;  // 0x00
    RwReal radius;            // 0x14
    RwRGBAReal color;         // 0x18
    RwLinkList minusCosAngle; // 0x28
    RwLLLink inWorld;         // 0x30
    RwUInt16 lightFrame;      // 0x38
    RwUInt16 pad;             // 0x3a
} RpLight;

#endif