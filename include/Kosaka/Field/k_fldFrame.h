#ifndef K_FLDFRAME_H
#define K_FLDFRAME_H

#include "Utils.h"
#include "rw/rwplcore.h"

typedef struct Model Model;
typedef struct KwlnTask KwlnTask;

#define FLDFRAME_FLAG_NOCOLLIS  (1 << 28) // 0x10000000. Disable collisions
#define FLDFRAME_FLAG_DEBUGDRAW (1 << 31) // 0x80000000. Draw collisions

#define FLDFRAME_GET(collisCtlTask) ((FldFrame*)collisCtlTask->taskData)

typedef enum
{
    FLDFRAME_STATE_DIRTY,
    FLDFRAME_STATE_NOTDIRTY
} FldFrameState;

// 52 bytes. Task data for a "collision controler" task
// You can see this struct as an entity
typedef struct FldFrame
{
    u32 state;              // 0x00. See 'FldFrameState' enum
    u32 flags;              // 0x04. See 'FLDFRAME_FLAG_*'
    s16 resTypeId;          // 0x08. Typeid of the resrc owning the frame
    void* unk_0c;           // 0x0c
    Model* mdl;             // 0x10
    RwV3d velocity;         // 0x14
    f32 sphereCollisRadius; // 0x20. Radius of the sphere collision
    s32 unk_24;             // 0x24
    u32 totalDist;          // 0x28. Total distance travelled (weirdly it's not a float)
    u8 unkData1[0x08];
} FldFrame;

// 4 bytes. Task data for a 'collis sphere' task
typedef struct CollisSphereDebug
{
    u32 debugDraw; // 0x00
} CollisSphereDebug;

f32 K_FldFrame_GetSphereCollisRadius(KwlnTask* collisCtlTask);
void K_FldFrame_CopyPos(RwV3d* dst, KwlnTask* collisCtlTask);
void K_FldFrame_MoveInDir(f32 speed, KwlnTask* collisCtlTask, const RwV3d* normalizedDir);
void K_FldFrame_MoveForward(f32 speed, KwlnTask* collisCtlTask);
void K_FldFrame_Rotate(KwlnTask* collisCtlTask, const RwV3d* axis, f32 angle);

#endif