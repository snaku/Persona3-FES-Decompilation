#ifndef KWLNTASK_H
#define KWLNTASK_H

#include "Utils.h"

// 104 bytes (not sure)
typedef struct KwlnTask
{
    u8 taskName[24];
    u8 unkData1[0x08];
    u32 unk_20;
    u8 unkData2[0x14];
    s32 (*Update)(struct KwlnTask* task);   // maybe return 0 = continue task and return -1 = destroy task
    void (*Destroy)(struct KwlnTask* task);
    void* taskData;                         // Pointer to data specific to the curr task (like a Camera struct)
    u8 unkData3[0x24];
} KwlnTask;

#endif