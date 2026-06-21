#ifndef K_PC_H
#define K_PC_H

#include "Utils.h"
#include "rw/rwplcore.h"

typedef struct KwlnTask KwlnTask;
typedef struct Model Model;

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

KwlnTask* K_Pc_CreateRotateTask(KwlnTask* parent, KwlnTask* collisCtlTask, Model* mdl);

#endif