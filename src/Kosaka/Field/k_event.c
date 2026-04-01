#include "Kosaka/Field/k_event.h"
#include "kwln/kwlnTask.h"

KwlnTask* K_FldEvent_CreateDrawCmdTask(KwlnTask* fldEventTask);

// FUN_001c71f0
RwBool K_FldEvent_IsWithinDistance(f32 maxDist, RwV3d* posA, RwV3d* posB)
{
    RwV3d diff;
    RwBool withinDist;

    withinDist = false;

    diff.x = posA->x - posB->x;
    diff.y = posA->y - posB->y;
    diff.z = posA->z - posB->z;

    if (RwV3dLength(&diff) < maxDist)
    {
        withinDist = true;
    }

    return withinDist;
}

// FUN_001c8620
void* K_FldEvent_UpdateFldEventTask(KwlnTask* fldEventTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_001cd570
void K_FldEvent_DestroyFldEventTask(KwlnTask* fldEventTask)
{
    RW_FREE(fldEventTask->taskData);
}

// FUN_001cd5a0. Create 'field event' and 'draw command' tasks
KwlnTask* K_FldEvent_CreateTasks(KwlnTask* fldRootTask)
{
    K_FieldEvent* fldEvent;
    KwlnTask* fldEventTask;

    fldEvent = RW_CALLOC(1, sizeof(K_FieldEvent), 0x40000);
    if (fldEvent == NULL)
    {
        return NULL;
    }

    fldEventTask = KwlnTask_CreateWithAutoPriority(fldRootTask, 10, "field event", K_FldEvent_UpdateFldEventTask, K_FldEvent_DestroyFldEventTask, fldEvent);
    
    fldEvent->drawCmdTask = K_FldEvent_CreateDrawCmdTask(fldEventTask);

    return fldEventTask;
}

// FUN_001cd690
void* K_FldEvent_UpdateDrawCmdTask(KwlnTask* drawCmdTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_001cd6e0
void K_FldEvent_DestroyDrawCmdTask(KwlnTask* drawCmdTask)
{
    RW_FREE(drawCmdTask->taskData);
}

// FUN_001cd710
KwlnTask* K_FldEvent_CreateDrawCmdTask(KwlnTask* fldEventTask)
{
    K_FieldDrawCmd* drawCmd;

    drawCmd = RW_CALLOC(1, sizeof(K_FieldDrawCmd), 0x40000);
    if (drawCmd == NULL)
    {
        return NULL;
    }

    return KwlnTask_CreateWithAutoPriority(fldEventTask, 4207, "draw command", K_FldEvent_UpdateDrawCmdTask, K_FldEvent_DestroyDrawCmdTask, drawCmd);
}