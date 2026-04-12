#ifndef K_DRAW_H
#define K_DRAW_H

#include "Utils.h"
#include "rw/rwcore.h"

typedef struct KwlnTask KwlnTask;

// 20 bytes
typedef struct PointDrawWork
{
    u32 drawEnabled; // 0x00
    RwV3d center;    // 0x04
    RwRGBA color;    // 0x10
} PointDrawWork;

// 24 bytes
typedef struct CylinderDrawWork
{
    u32 drawEnabled; // 0x00
    RwV3d center;    // 0x04
    f32 radius;      // 0x10
    f32 height;      // 0x14
} CylinderDrawWork;

// 80 bytes
typedef struct PositionDrawWork
{
    RwMatrix mat;     // 0x00
    RwRGBA color;     // 0x44
    u8 unkData[0x0c];
} PositionDrawWork;

KwlnTask* K_Draw_CreatePointTask(KwlnTask* parent);
void K_Draw_SetPointDrawEnabled(KwlnTask* pointTask, u32 drawEnabled);
void K_Draw_SetPointCenter(KwlnTask* pointTask, const RwV3d* center);
void K_Draw_SetPointColor(KwlnTask* pointTask, const RwRGBA* color);

KwlnTask* K_Draw_CreateCylinderTask(KwlnTask* parent);
void K_Draw_SetCylinderDrawEnabled(KwlnTask* cylinderTask, u32 drawEnabled);
void K_Draw_SetCylinderCenter(KwlnTask* cylinderTask, const RwV3d* center);
void K_Draw_SetCylinderRadius(KwlnTask* cylinderTask, f32 radius);
void K_Draw_SetCylinderHeight(KwlnTask* cylinderTask, f32 height);

KwlnTask* K_Draw_CreatePositionTask(KwlnTask* parent);
void K_Draw_SetPositionColor(KwlnTask* positionTask, const RwRGBA* color);
void K_Draw_CopyPositionCenter(RwV3d* dst, KwlnTask* positionTask);
RwMatrix* K_Draw_GetPositionMatrix(KwlnTask* positionTask);
void K_Draw_MovePositionInDir(f32 dist, KwlnTask* positionTask, const RwV3d* dir);
void K_Draw_RotatePosition(f32 angle, KwlnTask* positionTask, const RwV3d* axis);

#endif