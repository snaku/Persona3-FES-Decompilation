#ifndef K_VPAD_H
#define K_VPAD_H

#include "Utils.h"
#include "rw/rwplcore.h"

typedef struct KwlnTask KwlnTask;
typedef struct Model Model;

// 144 bytes
typedef struct VPadWork
{
    u8 unkData1[0x50];
    KwlnTask* rotateTask;    // 0x50
    KwlnTask* collisCtlTask; // 0x54
    Model* mdl;              // 0x58
    u8 unkData2[0x34];
} VPadWork;

typedef enum
{
    PCROTATE_STATE_IDLE,
    PCROTATE_STATE_ROTATING
} PcRotateState;

// 96 bytes
typedef struct PcRotateWork
{
    RwMatrix mat;            // 0x00
    u32 state;               // 0x40. See enum 'PcRotateState'
    KwlnTask* collisCtlTask; // 0x44
    Model* mdl;              // 0x48
    u8 unkData[0x08];
    f32 angle;               // 0x54
    s32 steps;               // 0x58
    s32 maxSteps;            // 0x5c
} PcRotateWork;

KwlnTask* K_VPad_CreateTask(KwlnTask* parent, KwlnTask* collisCtlTask, Model* mdl);

KwlnTask* K_VPad_CreateRotateTask(KwlnTask* parent, KwlnTask* collisCtlTask, Model* mdl);
u32 K_VPad_IsRotating(KwlnTask* rotatePcTask);

#endif