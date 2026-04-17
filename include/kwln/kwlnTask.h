#ifndef KWLNTASK_H
#define KWLNTASK_H

#include "Utils.h"

#define KWLNTASK_STATE_MASK 0xF

#define KWLNTASK_GET_STATE(task)        ((task)->stateAndFlags & KWLNTASK_STATE_MASK)
#define KWLNTASK_SET_STATE(task, state) \
        ((task)->stateAndFlags = ((task)->stateAndFlags & ~KWLNTASK_STATE_MASK) | (state))
#define KWLNTASK_RESET_STATE(task) \
        ((task)->stateAndFlags = ((task)->stateAndFlags) & ~KWLNTASK_STATE_MASK)

#define KWLNTASK_CONTINUE ((void*)0)
#define KWLNTASK_STOP     ((void*)0xFFFFFFFF)

typedef enum
{
    KWLNTASK_STATE_NULL,
    KWLNTASK_STATE_STAGED,
    KWLNTASK_STATE_RUNNING,
    KWLNTASK_STATE_DESTROY
} KwlnTaskState;

typedef struct KwlnTask KwlnTask;

typedef void* (*KwlnTaskUpdateFunc)(KwlnTask* task);
typedef void  (*KwlnTaskDestroyFunc)(KwlnTask* task);

// 104 bytes
struct KwlnTask
{
    char name[24];                // 0x00
    u32 nameHash;                 // 0x18. Sum of each char of the name
    u32 stateAndFlags;            // 0x1c. bits 0 to 3 are for state, bits 4 to 31 are maybe for flags. See enum 'KwlnTaskState'
    u32 priority;                 // 0x20
    u32 unk_24;                   // 0x24
    u32 timer;                    // 0x28. Number of frames since the creation of the task
    s32 runningDelay;             // 0x2c. Number of frames until the task can transition from state 'CREATED' to 'RUNNING'
    s32 destroyDelay;             // 0x30. Number of frames until task can be destroyed
    KwlnTaskUpdateFunc update;    // 0x34. return KWLN_TASK_CONTINUE to continue, return KWLN_TASK_STOP to destroy
    KwlnTaskDestroyFunc destroy;  // 0x38
    void* workData;               // 0x3c. Pointer to data specific to the current task
    KwlnTask* next;               // 0x40
    KwlnTask* prev;               // 0x44
    KwlnTask* unk_48;             // 0x48
    KwlnTask* parent;             // 0x4c
    KwlnTask* child;              // 0x50. First child of the task
    KwlnTask* sibling;            // 0x54. Next task sharing the same parent
    s32 unk_58;                   // 0x58
    s32 unk_5c;                   // 0x5c
    s32 unk_60;                   // 0x60
    s32 unk_64;                   // 0x64
};

void kwlnTaskUpdateAll();
u8 kwlnTaskMain();
KwlnTask* kwlnTaskCreate(KwlnTask* parentTask, const char* name, u32 priority, KwlnTaskUpdateFunc update, KwlnTaskDestroyFunc destroy, void* workData);
KwlnTask* kwlnTaskCreateWithAutoPriority(KwlnTask* parentTask, u32 priority, const char* name, KwlnTaskUpdateFunc update, KwlnTaskDestroyFunc destroy, void* workData);
KwlnTask* kwlnTaskInit(const char* name, u32 priority, KwlnTaskUpdateFunc update, KwlnTaskDestroyFunc destroy, void* workData);
KwlnTask* kwlnTaskInitEx(const char* name, u32 priority, s32 runningDelay, s32 destroyDelay, KwlnTaskUpdateFunc update, KwlnTaskDestroyFunc destroy, void* workData);
u8 kwlnTaskDestroyWithHierarchyByName(const char* name);
u8 kwlnTaskDestroyWithHierarchy(KwlnTask* task);
u32 kwlnTaskGetState(KwlnTask* task);
KwlnTask* kwlnTaskGetTaskByName(const char* name);
KwlnTask* kwlnTaskGetUpdating();
u8 kwlnTaskExists(KwlnTask* task);
u32 kwlnTaskGetTimer(KwlnTask* task);
void kwlnTaskSetWorkData(KwlnTask* task, void* workData);
void* kwlnTaskGetWorkData(KwlnTask* task);
void kwlnTaskAddChild(KwlnTask* parentTask, KwlnTask* childTask);
void kwlnTaskDetachParent(KwlnTask* childTask);

#endif