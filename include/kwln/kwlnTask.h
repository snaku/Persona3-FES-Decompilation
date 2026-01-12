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
    u8 taskName[24];
    u32 unk_18;
    u32 unk_1c;
    u32 unk_20;
    u32 unk_24;
    u32 taskTimer;
    u8 unkData2[0x0c];
    KwlnTask_Update update;     // return KWLN_TASK_CONTINUE to continue, return KWLN_TASK_STOP to destroy
    KwlnTask_Destroy destroy;
    void* taskData;             // Pointer to data specific to the curr task (like a Camera struct)
    struct KwlnTask* next;
    struct KwlnTask* prev;
    struct KwlnTask* unk_48;
    struct KwlnTask* parent;
    struct KwlnTask* child;     // first child of the task
    struct KwlnTask* nextChild; // if current task has a parent, points to the next child of the parent
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