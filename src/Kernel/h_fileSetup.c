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

// FUN_00192980
void* H_FileSetup_UpdateGojitudanTask(KwlnTask* gojitudanTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_00192a70
void H_FileSetup_DestroyGojituanTask(KwlnTask* gojitudanTask)
{
    RwFree(gojitudanTask->workData);
}

// FUN_00192aa0
KwlnTask* H_FileSetup_CreateGojitudanTask()
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
                                          "GojitudanFileSetup",
                                          H_FileSetup_UpdateGojitudanTask,
                                          H_FileSetup_DestroyGojituanTask,
                                          work);
    if (task == NULL)
    {
        return NULL;
    }

    datSetScenarioMode(SCENARIO_MODE_ANSWER);

    return task;
}