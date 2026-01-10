#ifndef KWLNTASK_H
#define KWLNTASK_H

#include "Utils.h"

struct KwlnTask;

typedef s32 (*KwlnTask_Update)(struct KwlnTask* task);
typedef void (*KwlnTask_Destroy)(struct KwlnTask* task);

// 104 bytes (not sure)
typedef struct KwlnTask
{
    u8 taskName[24];
    u8 unkData1[0x08];
    u32 unk_20;
    u32 taskTimer;
    u8 unkData2[0x10];
    KwlnTask_Update update;   // maybe return 0 = continue task and return -1 = destroy task
    KwlnTask_Destroy destroy;
    void* taskData;           // Pointer to data specific to the curr task (like a Camera struct)
    u8 unkData3[0x24];
} KwlnTask;

KwlnTask* KwlnTask_Init(u8* taskName, u32 param_2, KwlnTask_Update update, KwlnTask_Destroy destroy, void* taskData);

#endif