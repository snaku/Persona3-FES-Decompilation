#include "kwln/kwlnTask.h"
#include "Field/k_event.h"
#include "rw/rwplcore.h"

KwlnTask* FldEvent_CreateDrawCmdTask(KwlnTask* fldEventTask);

// FUN_001cd690
s32 FldEvent_UpdateDrawCmdTask(KwlnTask* drawCmdTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_001cd6e0
void FldEvent_DestroyDrawCmdTask(KwlnTask* drawCmdTask)
{
    rwGlobals.memFuncs.Rw_Free(drawCmdTask->taskData);
}

// FUN_001cd710
KwlnTask* FldEvent_CreateDrawCmdTask(KwlnTask* fldEventTask)
{
    FieldDrawCmd* drawCmd;

    drawCmd = rwGlobals.memFuncs.Rw_Calloc(1, sizeof(FieldDrawCmd), 0x40000);
    if (drawCmd == NULL)
    {
        return NULL;
    }

    return KwlnTask_CreateWithAutoPriority(fldEventTask, 4207, "draw command", FldEvent_UpdateDrawCmdTask, FldEvent_DestroyDrawCmdTask, drawCmd);
}