#ifndef K_DRAW_H
#define K_DRAW_H

#include "Utils.h"
#include "rw/rwcore.h"

typedef struct KwlnTask KwlnTask;

// 24 bytes
typedef struct CylinderDrawWork
{
    u32 drawEnabled; // 0x00
    RwV3d center;    // 0x04
    f32 radius;      // 0x10
    f32 height;      // 0x14
} CylinderDrawWork;

KwlnTask* K_Draw_CreateCylinderTask(KwlnTask* parent);
void K_Draw_SetCylinderDrawEnabled(KwlnTask* cylinderTask, u32 drawEnabled);
void K_Draw_SetCylinderCenter(KwlnTask* cylinderTask, const RwV3d* center);
void K_Draw_SetCylinderRadius(KwlnTask* cylinderTask, f32 radius);
void K_Draw_SetCylinderHeight(KwlnTask* cylinderTask, f32 height);

#endif