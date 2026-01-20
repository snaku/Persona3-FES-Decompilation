#ifndef KWLNTASK_H
#define KWLNTASK_H

#include "Utils.h"

#define KWLN_TASK_GET_STATE(task)        ((task)->stateAndFlags & 0xF)
#define KWLN_TASK_SET_STATE(task, state) ((task)->stateAndFlags = ((task)->stateAndFlags & 0xFFFFFFF0) | (state))
#define KWLN_TASK_RESET_STATE(task)      ((task)->stateAndFlags = ((task)->stateAndFlags) & 0xFFFFFFF0)

#define KWLN_TASK_CONTINUE 0
#define KWLN_TASK_STOP    -1

struct KwlnTask;

typedef s32 (*KwlnTask_Update)(struct KwlnTask* task);
typedef void (*KwlnTask_Destroy)(struct KwlnTask* task);

typedef enum
{
    KWLN_TASK_STATE_0,
    KWLN_TASK_STATE_CREATED,
    KWLN_TASK_STATE_RUNNING,
    KWLN_TASK_STATE_DESTROY
} KwlnTaskState;

// 104 bytes
typedef struct KwlnTask
{
    u8 taskName[24];            // 0x00
    u32 nameChkSum;             // 0x18. Sum of each char in 'taskName'
    u32 stateAndFlags;          // 0x1c. bits 0 to 3 are for state, bits 4 to 31 are maybe for flags
    u32 unk_20;                 // 0x20
    u32 unk_24;                 // 0x24
    u32 taskTimer;              // 0x28. Number of frames since the creation of the task
    s32 unkTimer;               // 0x2c
    s32 destroyTimer;           // 0x30. Number of frames until task can be destroyed
    KwlnTask_Update update;     // 0x34. return KWLN_TASK_CONTINUE to continue, return KWLN_TASK_STOP to destroy
    KwlnTask_Destroy destroy;   // 0x38
    void* taskData;             // 0x3c. Pointer to data specific to the curr task (like a Camera struct)
    struct KwlnTask* next;      // 0x40
    struct KwlnTask* prev;      // 0x44
    struct KwlnTask* unk_48;    // 0x48
    struct KwlnTask* parent;    // 0x4c
    struct KwlnTask* child;     // 0x50. first child of the task
    struct KwlnTask* nextChild; // 0x54. if current task has a parent, points to the next child of the parent
    s32 unk_58;                 // 0x58
    s32 unk_5c;                 // 0x5c
    s32 unk_60;                 // 0x60
    s32 unk_64;                 // 0x64
} KwlnTask;

u8 KwlnTask_UpdateTask(KwlnTask* task);
void KwlnTask_UpdateAll();
u8 KwlnTask_Main();
KwlnTask* KwlnTask_Create(KwlnTask* parentTask, u8* taskName, u32 param_3, KwlnTask_Update update, KwlnTask_Destroy destroy, void* taskData);
KwlnTask* KwlnTask_Init(u8* taskName, u32 param_2, KwlnTask_Update update, KwlnTask_Destroy destroy, void* taskData);
u32 KwlnTask_GetTaskTimer(KwlnTask* task);
void* KwlnTask_GetTaskData(KwlnTask* task);
void KwlnTask_AddChild(KwlnTask* parentTask, KwlnTask* childTask);
void KwlnTask_RemoveParent(KwlnTask* childTask);

#endif