#ifndef K_FLDFRAME_H
#define K_FLDFRAME_H

#include "Utils.h"
#include "rw/rwplcore.h"

typedef struct Model Model;
typedef struct KwlnTask KwlnTask;
typedef struct FldUnit FldUnit;

#define COLLISCTL_FLAG_NOCOLLIS  (1 << 28) // 0x10000000. Disable collisions
#define COLLISCTL_FLAG_DEBUGDRAW (1 << 31) // 0x80000000. Draw collisions

typedef enum
{
    COLLISCTL_STATE_DIRTY,
    COLLISCTL_STATE_NOTDIRTY
} CollisCtlState;

// 52 bytes. Task data for a "collision controler" task
typedef struct CollisCtl
{
    u32 state;              // 0x00. See 'CollisCtlState' enum
    u32 flags;              // 0x04. See 'COLLISCTL_FLAG_*'
    u16 resTypeId;          // 0x08. Typeid of the resrc owning the CollisCtl
    u16 charId;             // 0x0a
    FldUnit* fldUnit;       // 0x0c
    Model* mdl;             // 0x10
    RwV3d velocity;         // 0x14
    f32 sphereCollisRadius; // 0x20. Radius of the sphere collision
    s32 unk_24;             // 0x24
    u32 totalDist;          // 0x28. Total distance travelled (weirdly it's not a float)
    s32 xGrid;              // 0x2c. Current X grid
    s32 zGrid;              // 0x30. Current Z grid
} CollisCtl;

// 4 bytes. Task data for a 'collis sphere' task
typedef struct CollisSphereDebug
{
    u32 drawEnabled; // 0x00
} CollisSphereDebug;

u32 K_FldFrame_IsPointInTriangle(const RwV3d* point, const RwV3d** tri, const RwV3d* normal);

// collis ctl
KwlnTask* K_FldFrame_CreateCtlTask(KwlnTask* parent, u32 resTypeId, s32 unused, f32 sphereCollisRadius);
f32 K_FldFrame_CtlGetSphereCollisRadius(KwlnTask* collisCtlTask);
void K_FldFrame_CtlSetSphereCollisRadius(KwlnTask* collisCtlTask, f32 radius);
s32 K_FldFrame_CtlGetXGrid(KwlnTask* collisCtlTask);
s32 K_FldFrame_CtlGetZGrid(KwlnTask* collisCtlTask);
void K_FldFrame_CtlCopyPos(RwV3d* dst, KwlnTask* collisCtlTask);
void K_FldFrame_CtlMoveInDir(f32 dist, KwlnTask* collisCtlTask, const RwV3d* normalizedDir);
void K_FldFrame_CtlMoveForward(f32 dist, KwlnTask* collisCtlTask);
void K_FldFrame_CtlRotate(KwlnTask* collisCtlTask, const RwV3d* axis, f32 angle);

#endif