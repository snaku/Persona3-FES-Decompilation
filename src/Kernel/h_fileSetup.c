#include "Kernel/h_fileSetup.h"
#include "Kernel/Kwln/kwlnTask.h"
#include "Main/g_data.h"
#include "rw/rwplcore.h"

// FUN_001927b0
void* H_FileSetup_UpdateHonpenTask(KwlnTask* honpenTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_001928a0
void H_FileSetup_DestroyHonpenTask(KwlnTask* honpenTask)
{
    RwFree(honpenTask->workData);
}

// FUN_001928d0
KwlnTask* H_FileSetup_CreateHonpenTask()
{
    HFileSetupWork* work;
    KwlnTask* task;

    work = RwCalloc(1, sizeof(HFileSetupWork), rwMEMHINTDUR_GLOBAL);
    if (work == NULL)
    {
        return NULL;
    }

    task = kwlnTaskCreateWithAutoPriority(NULL,
                                          4207,
                                          "HonpenFileSetup",
                                          H_FileSetup_UpdateHonpenTask,
                                          H_FileSetup_DestroyHonpenTask,
                                          work);
    if (task == NULL)
    {
        return NULL;
    }

    datSetScenarioMode(SCENARIO_MODE_JOURNEY);

    return task;
}