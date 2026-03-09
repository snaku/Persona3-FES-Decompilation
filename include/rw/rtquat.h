#ifndef RTQUAT_H
#define RTQUAT_H

#include "rw/rwplcore.h"

// 16 bytes
typedef struct RtQuat
{
    RwV3d imag;  // 0x00 
    RwReal real; // 0x0c
} RtQuat;

#endif