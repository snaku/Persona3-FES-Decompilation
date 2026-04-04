#ifndef K_COLLIS_H
#define K_COLLIS_H

#include "Utils.h"
#include "rw/rwplcore.h"

#define COLLISCTL_FLAG_DEBUGDRAW (1 << 31) // 0x80000000. Draw collisions

typedef struct Model Model;

// 52 bytes. Task data for a "collision controler" task
// Contains some info for the collisions, but also for characters movements (kinda weird ngl)
typedef struct K_CollisCtl
{
    s32 unk_00;        // 0x00
    u32 flags;         // 0x04
    s16 resTypeId;     // 0x08. Typeid of the resrc owning the task
    void* unk_0c;      // 0x0c
    Model* mdl;        // 0x10
    RwV3d velocity;    // 0x14. XYZ velocity of the model
    f32 sphereRadius;  // 0x20. Radius of the sphere collision
    u8 unkData1[0x10];
} K_CollisCtl;

#endif