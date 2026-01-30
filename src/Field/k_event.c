#include "kwln/kwlnTask.h"
#include "Field/k_event.h"
#include "rw/rwplcore.h"

KwlnTask* FldEvent_CreateDrawCmdTask(KwlnTask* fldEventTask);

// FUN_001c8620
u32 FldEvent_UpdateFldEventTask(KwlnTask* fldEventTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_001cd570
void FldEvent_DestroyFldEventTask(KwlnTask* fldEventTask)
{
    RW_FREE(fldEventTask->taskData);
}

// FUN_001cd5a0. Create 'field event' and 'draw command' tasks
KwlnTask* FldEvent_CreateTasks(KwlnTask* fldRootTask)
{
    FieldEvent* fldEvent;
    KwlnTask* fldEventTask;

    fldEvent = RW_CALLOC(1, sizeof(FieldEvent), 0x40000);
    if (fldEvent == NULL)
    {
        return NULL;
    }

    fldEventTask = KwlnTask_CreateWithAutoPriority(fldRootTask, 10, "field event", FldEvent_UpdateFldEventTask, FldEvent_DestroyFldEventTask, fldEvent);
    
    fldEvent->drawCmdTask = FldEvent_CreateDrawCmdTask(fldEventTask);

    return fldEventTask;
}

// FUN_001cd690
u32 FldEvent_UpdateDrawCmdTask(KwlnTask* drawCmdTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_001cd6e0
void FldEvent_DestroyDrawCmdTask(KwlnTask* drawCmdTask)
{
    RW_FREE(drawCmdTask->taskData);
}

// FUN_001cd710
KwlnTask* FldEvent_CreateDrawCmdTask(KwlnTask* fldEventTask)
{
    FieldDrawCmd* drawCmd;

    drawCmd = RW_CALLOC(1, sizeof(FieldDrawCmd), 0x40000);
    if (drawCmd == NULL)
    {
        return NULL;
    }

    return KwlnTask_CreateWithAutoPriority(fldEventTask, 4207, "draw command", FldEvent_UpdateDrawCmdTask, FldEvent_DestroyDrawCmdTask, drawCmd);
}