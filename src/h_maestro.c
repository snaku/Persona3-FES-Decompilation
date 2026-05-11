#include "h_maestro.h"
#include "kwln/kwlnTask.h"
#include "rw/rt2danim.h"
#include "h_cdvd.h"
#include "temporary.h"

// FUN_00111610
void* H_Maestro_UpdateTask(KwlnTask* hmaestroTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_00111d60
void H_Maestro_DestroyTask(KwlnTask* hmaestroTask)
{
    // TODO
}

// FUN_00111dd0
KwlnTask* H_Maestro_CreateTask(KwlnTask* parent, u32 priority, const char* path)
{
    HMaestro* work;
    KwlnTask* task;

    work = RwCalloc(1, sizeof(HMaestro), rwMEMHINTDUR_GLOBAL);
    if (work == NULL)
    {
        return NULL;
    }

    task = kwlnTaskCreate(parent,
                          "H_DrawMaestro",
                          priority,
                          H_Maestro_UpdateTask,
                          H_Maestro_DestroyTask,
                          work);
    if (task == NULL)
    {
        return NULL;
    }

    strcpy(work->path, path);
    work->noDeltaTime = false;
    work->shouldLoop = false;
    work->alphaMult = 1.0f;
    work->useCdvd = false;

    return task;
}