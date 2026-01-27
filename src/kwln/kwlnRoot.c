#include "kwln/kwlnRoot.h"
#include "kwln/kwlnTask.h"
#include "rw/rwplcore.h"
#include "h_snd.h"

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

    rootProcTask = KwlnTask_Init("rootProc", 0, NULL, NULL, root);
    H_Snd_FUN_00109ca0(0, 1);
    H_Snd_FUN_00109ca0(1, 2);

    return rootProcTask;
}