#include "Kosaka/k_misc.h"
#include "kwln/kwlnTask.h"
#include "Model/mdlManager.h"
#include "rw/rwplcore.h"

// FUN_001a5de0
void* K_Misc_UpdateDelayMdlFreeTask(KwlnTask* delayMdlFreeTask)
{
    DelayMdlFreeWork* work;

    work = (DelayMdlFreeWork*)delayMdlFreeTask->workData;

    switch (work->state)
    {
        case DELAYMDLFREE_STATE_WAITSTREAM:
            if (mdlStreamRead(work->mdlToDestroy))
            {
                work->state++;
            }
            break;

        case DELAYMDLFREE_STATE_DESTROYING:
            mdlDestroy(work->mdlToDestroy);
            return KWLNTASK_STOP;
    }

    return KWLNTASK_CONTINUE;
}

// FUN_001a5e70
void K_Misc_DestroyDelayMdlFreeTask(KwlnTask* delayMdlFreeTask)
{
    RW_FREE(delayMdlFreeTask->workData);
}

// FUN_001a5ea0
KwlnTask* K_Misc_CreateDelayMdlFreeTask(Model* mdlToDestroy)
{
    DelayMdlFreeWork* work;
    KwlnTask* task;

    work = RW_CALLOC(1, sizeof(DelayMdlFreeWork), 0x40000);
    if (work == NULL)
    {
        return NULL;
    }

    task = kwlnTaskCreateWithAutoPriority(NULL,
                                          10,
                                          "delay model free",
                                          K_Misc_UpdateDelayMdlFreeTask,
                                          K_Misc_DestroyDelayMdlFreeTask,
                                          work);

    work->mdlToDestroy = mdlToDestroy;

    return task;
}

// FUN_001a6260
void* K_Misc_UpdateScrShutdownTask(KwlnTask* scrShutdownTask)
{
    kwlnTaskDestroyWithHierarchy(((ScrShutdownWork*)scrShutdownTask->workData)->scrTask);

    return KWLNTASK_STOP;
}

// FUN_001a6290
void K_Misc_DestroyScrShutdownTask(KwlnTask* scrShutdownTask)
{
    RW_FREE(scrShutdownTask->workData);
}

// FUN_001a62c0
KwlnTask* K_Misc_CreateScrShutdownTask(KwlnTask* scrTask)
{
    ScrShutdownWork* work;
    KwlnTask* task;

    work = RW_CALLOC(1, sizeof(ScrShutdownWork), 0x40000);
    if (work == NULL)
    {
        return NULL;
    }

    task = kwlnTaskCreateWithAutoPriority(NULL, 
                                          10,
                                          "script shutdown(kosaka)",
                                          K_Misc_UpdateScrShutdownTask,
                                          K_Misc_DestroyScrShutdownTask,
                                          work);

    work->scrTask = scrTask;

    return task;
}