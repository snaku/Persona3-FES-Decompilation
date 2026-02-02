#ifndef ADMINI_H
#define ADMINI_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;

#define ADMINI_FLAG_CHANGING_TASK (1 << 0)  // 0x1
#define ADMINI_FLAG_UNK02         (1 << 1)  // 0x2
#define ADMINI_FLAG_UNK04         (1 << 2)  // 0x4
#define ADMINI_FLAG_UNK08         (1 << 3)  // 0x8
#define ADMINI_FLAG_UNK10000      (1 << 16) // 0x10000

#define ADMINI_RESET_FLAGS(admini, flagsToReset) ((admini)->flags &= ~(flagsToReset))
#define ADMINI_SET_FLAGS(admini, flagsToSet)     ((admini)->flags |= (flagsToSet))
#define ADMINI_SET_RESET_FLAGS(admini, flagsToReset, flagsToSet) \
        ((admini)->flags = ((admini)->flags & ~(flagsToReset)) | (flagsToSet))

typedef enum
{
    ADMINI_TASK_ID_NULL,
    ADMINI_TASK_ID_TEST,
    ADMINI_TASK_ID_FIELD_ROOT,
    ADMINI_TASK_ID_FIELD_ROOT2,
    ADMINI_TASK_ID_MAP,
    ADMINI_TASK_ID_DUNGEON,
    ADMINI_TASK_ID_BATTLE_BOSS,
    ADMINI_TASK_ID_FACILITY,
    ADMINI_TASK_ID_MAX,

    ADMINI_TASK_ID_INVALID = -1
} AdminiTaskId;

// 36 bytes
typedef struct Admini
{
    u32 flags;                            // 0x00
    u32 timer;                            // 0x04. Increments every frame while 'taskId' doesn't change
    s8 taskId;                            // 0x08. Current task id. See enum 'AdminiTaskId'
    s8 taskIdToSet;                       // 0x09. See enum 'AdminiTaskId'
    u8 oldTaskIdx;                        // 0x0a. Idx to access 'oldTaskIds'
    u8 unk_0b;                            // 0x0b
    s8 oldTaskIds[ADMINI_TASK_ID_MAX];    // 0x0c. History of task ids
    s8 oldTasksFlags[ADMINI_TASK_ID_MAX]; // 0x14. History of admini flags
    void* taskData;                       // 0x1c. Current task data
    u8 taskDataSize;                      // 0x20. Current task data size in bytes
    u8 unk_21;                            // 0x21
    u8 unk_22;                            // 0x22
    u8 unk_23;                            // 0x23
} Admini;

void Admini_ChangeTask(s8 taskId, void* taskData, u8 taskDataSize, u8 param_4);
KwlnTask* Admini_CreateTask();

#endif