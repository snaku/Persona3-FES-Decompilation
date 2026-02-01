#ifndef ADMINI_H
#define ADMINI_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;

typedef enum
{
    // TODO
    ADMINI_TASK_ID_MAX = 8,
} AdminiTaskId;

// 36 bytes
typedef struct Admini
{
    u32 flags;                         // 0x00
    u32 timer;                         // 0x04
    s8 taskId;                         // 0x08. Current task id. See enum 'AdminiTaskId'
    s8 taskIdToSet;                    // 0x09. See enum 'AdminiTaskId'
    u8 oldTaskIdIdx;                   // 0x0a. Idx to access 'oldTaskIds'
    u8 unk_0b;                         // 0x0b
    s8 oldTaskIds[ADMINI_TASK_ID_MAX]; // 0x0c
    s8 unk_14[ADMINI_TASK_ID_MAX];     // 0x14
    void* taskData;                    // 0x1c. Current task data
    u8 taskDataSize;                   // 0x20. Current task data size in bytes
    u8 unk_21;
    u8 unk_22;
    u8 unk_23;
} Admini;

#endif