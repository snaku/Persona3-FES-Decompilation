#include "Kosaka/k_pc.h"
#include "kwln/kwlnTask.h"

// FUN_001e13f0
void* K_Pc_UpdateRotateTask(KwlnTask* rotatePcTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_001e14b0
void K_Pc_DestroyRotateTask(KwlnTask* rotatePcTask)
{
    RwFree(rotatePcTask->workData);
}

// FUN_001e14e0
KwlnTask* K_Pc_CreateRotateTask(KwlnTask* parent, KwlnTask* collisCtlTask, Model* mdl)
{
    PcRotateWork* work;
    KwlnTask* task;

    work = RwCalloc(1, sizeof(PcRotateWork), rwMEMHINTDUR_GLOBAL);
    if (work == NULL)
    {
        return NULL;
    }

    task = kwlnTaskCreateWithAutoPriority(parent,
                                          10,
                                          "rotate pc",
                                          K_Pc_UpdateRotateTask,
                                          K_Pc_DestroyRotateTask,
                                          work);

    work->collisCtlTask = collisCtlTask;
    work->mdl = mdl;

    return task;
}