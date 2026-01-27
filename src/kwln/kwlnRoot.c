#include "kwln/kwlnRoot.h"
#include "kwln/kwlnTask.h"
#include "rw/rwplcore.h"
#include "temporary.h"
#include "h_snd.h"

KwlnTask* KwlnRoot_Create2DDrawBeginTask();
KwlnTask* KwlnRoot_Create2DDrawBeginPreEndTask();

// FUN_00198590. Not sure if it's in this file or in 'kwln.c' ?
RwCamera* KwlnRoot_GetMainCamera()
{
    return ctx.mainCamera;
}

// FUN_00198650
s32 KwlnRoot_UpdateRootProcTask(KwlnTask* rootProcTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_001988f0
void KwlnRoot_DestroyRootProcTask(KwlnTask* rootProcTask)
{
    // TODO

    rwGlobals.memFuncs.Rw_Free(rootProcTask->taskData);
}

// FUN_00198940
KwlnTask* KwlnRoot_CreateRootProcTask()
{
    KwlnTask* rootProcTask;
    KwlnRoot* root;

    root = rwGlobals.memFuncs.Rw_Calloc(1, sizeof(KwlnRoot), 0x40000);
    if (root == NULL)
    {
        return NULL;
    }

    rootProcTask = KwlnTask_Init("rootProc", 0, KwlnRoot_UpdateRootProcTask, KwlnRoot_DestroyRootProcTask, root);
    H_Snd_FUN_00109ca0(0, 1);
    H_Snd_FUN_00109ca0(1, 2);

    return rootProcTask;
}

// FUN_001989e0
s32 KwlnRoot_Update2DDrawBeginTask(KwlnTask* drawBegin2dTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_00198b10
s32 KwlnRoot_Update2DDrawPreEndTask(KwlnTask* drawBegin2dPETask)
{
    return KWLN_TASK_CONTINUE;
}

// FUN_00198b50
KwlnTask* KwlnRoot_Create2DDrawBeginTask()
{
    return KwlnTask_Init("2D Draw Begin", 4196, KwlnRoot_Update2DDrawBeginTask, NULL, NULL);
}

// FUN_00198b90
KwlnTask* KwlnRoot_Create2DDrawBeginPreEndTask()
{
    return KwlnTask_Init("2D Draw Begin Pre End", 5231, KwlnRoot_Update2DDrawPreEndTask, NULL, NULL);
}