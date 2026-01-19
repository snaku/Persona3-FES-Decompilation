#ifndef KWLNTASK_H
#define KWLNTASK_H

#include "Utils.h"

#define KWLN_TASK_CONTINUE 0
#define KWLN_TASK_STOP    -1

struct KwlnTask;

typedef s32 (*KwlnTask_Update)(struct KwlnTask* task);
typedef void (*KwlnTask_Destroy)(struct KwlnTask* task);

// 104 bytes
typedef struct KwlnTask
{
    u8 taskName[24];            // 0x00
    u32 unk_18;                 // 0x18
    u32 unk_1c;                 // 0x1c
    u32 unk_20;                 // 0x20
    u32 unk_24;                 // 0x24
    u32 taskTimer;              // 0x28
    u8 unkData2[0x08];
    KwlnTask_Update update;     // 0x34. return KWLN_TASK_CONTINUE to continue, return KWLN_TASK_STOP to destroy
    KwlnTask_Destroy destroy;   // 0x38
    void* taskData;             // 0x3c. Pointer to data specific to the curr task (like a Camera struct)
    struct KwlnTask* next;      // 0x40
    struct KwlnTask* prev;      // 0x44
    struct KwlnTask* unk_48;    // 0x48
    struct KwlnTask* parent;    // 0x4c
    struct KwlnTask* child;     // 0x50. first child of the task
    struct KwlnTask* nextChild; // 0x54. if current task has a parent, points to the next child of the parent
    u8 unkData3[0x0c];
} KwlnTask;

u8 KwlnTask_UpdateTask(KwlnTask* task);
void KwlnTask_UpdateAll();
KwlnTask* KwlnTask_Create(KwlnTask* parentTask, u8* taskName, u32 param_3, KwlnTask_Update update, KwlnTask_Destroy destroy, void* taskData);
KwlnTask* KwlnTask_Init(u8* taskName, u32 param_2, KwlnTask_Update update, KwlnTask_Destroy destroy, void* taskData);
u32 KwlnTask_GetTaskTimer(KwlnTask* task);
void* KwlnTask_GetTaskData(KwlnTask* task);
void KwlnTask_AddChild(KwlnTask* parentTask, KwlnTask* childTask);
void KwlnTask_RemoveParent(KwlnTask* childTask);

#endif