#include "Tohyama/h_maestro.h"
#include "Kernel/Kwln/kwlnTask.h"
#include "rw/rt2danim.h"
#include "h_cdvd.h"
#include "temporary.h"

// FUN_00111610
void* H_Maestro_UpdateTask(KwlnTask* hmaestroTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_00111d50
void H_Maestro_SetAlphaMult(KwlnTask* hmaestroTask, f32 alphaMult)
{
    ((HMaestro*)hmaestroTask->workData)->alphaMult = alphaMult;
}

// FUN_00111d60
void H_Maestro_DestroyTask(KwlnTask* hmaestroTask)
{
    HMaestro* work;

    work = (HMaestro*)hmaestroTask->workData;

    if (work->cdvd != NULL)
    {
        H_Cdvd_Destroy(work->cdvd);
        work->cdvd = NULL;
    }

    if (work->maestro != NULL)
    {
        Rt2dMaestroDestroy(work->maestro);
        work->maestro = NULL;
    }

    RwFree(work);
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

// FUN_00111cb0
u32 H_Maestro_00111cb0(KwlnTask* hmaestroTask)
{
    // TODO

    return 0;
}

// FUN_00111ec0
u32 H_Maestro_FinishedInit(KwlnTask* hmaestroTask)
{
    return ((HMaestro*)hmaestroTask->workData)->state > HMAESTRO_STATE_INITSCENE;
}

// FUN_00111ee0
void H_Maestro_RequestDraw(KwlnTask* hmaestroTask)
{
    ((HMaestro*)hmaestroTask->workData)->state = HMAESTRO_STATE_DRAW;
}

// FUN_00111f00
void H_Maestro_SetShouldLoop(KwlnTask* hmaestroTask, u32 shouldLoop)
{
    ((HMaestro*)hmaestroTask->workData)->shouldLoop = shouldLoop;
}

// FUN_00111f20
void H_Maestro_00111f20(KwlnTask* hmaestroTask, u32 param_2)
{
    // TODO
}