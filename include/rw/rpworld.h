#ifndef RPWORLD_H
#define RPWORLD_H

#include "rw/rwcore.h"

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

#endif