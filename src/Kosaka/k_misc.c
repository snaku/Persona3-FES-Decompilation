#include "Kosaka/k_misc.h"
#include "kwln/kwlnTask.h"
#include "Model/mdlManager.h"
#include "Scene/mt_scene.h"
#include "Scene/resrcManager.h"
#include "rw/rwplcore.h"

// FUN_001a5c50
u32 K_Misc_FindNextFreeResId(u16 resType)
{
    u32 currId;
    Resrc* res;

    currId = 0;
    res = MT_Scene_GetResListHead(resType);
    while (res != NULL)
    {
        if (RESRC_GET_ID(res->resTypeId) == currId)
        {
            currId++;
            res = MT_Scene_GetResListHead(resType);
        }
        else
        {
            res = res->next;
        }
    }

    return currId;
}

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
    RwFree(delayMdlFreeTask->workData);
}

// FUN_001a5ea0
KwlnTask* K_Misc_CreateDelayMdlFreeTask(Model* mdlToDestroy)
{
    DelayMdlFreeWork* work;
    KwlnTask* task;

    work = RwCalloc(1, sizeof(DelayMdlFreeWork), rwMEMHINTDUR_GLOBAL);
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
    RwFree(scrShutdownTask->workData);
}

// FUN_001a62c0
KwlnTask* K_Misc_CreateScrShutdownTask(KwlnTask* scrTask)
{
    ScrShutdownWork* work;
    KwlnTask* task;

    work = RwCalloc(1, sizeof(ScrShutdownWork), rwMEMHINTDUR_GLOBAL);
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