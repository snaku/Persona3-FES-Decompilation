#include "Kosaka/k_misc.h"
#include "kwln/kwlnTask.h"
#include "rw/rwplcore.h"

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