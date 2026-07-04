#include "Kernel/Kwln/kwlnTask.h"
#include "Script/scrTraceCode.h"
#include "rw/rwplcore.h"
#include "h_sfdply.h"
#include "temporary.h"

static KwlnTask* sSfdPlayTask; // 007cdf14. Task name = "H_SfdPlay"

// FUN_0010a860
void* H_SfdPlay_UpdateTask(KwlnTask* sfdPlayTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_0010bb00
void H_SfdPlay_DestroyTask(KwlnTask* sfdPlayTask)
{
    // TODO
}

// FUN_0010bda0
KwlnTask* H_SfdPlay_CreateTaskIdle(KwlnTask* parent)
{
    KwlnTask* task;
    HSfd* work;

    work = RwCalloc(1, sizeof(HSfd), rwMEMHINTDUR_GLOBAL);
    if (work == NULL)
    {
        return NULL;
    }

    task = kwlnTaskCreate(parent,
                          "H_SfdPlay",
                          7383,
                          H_SfdPlay_UpdateTask,
                          H_SfdPlay_DestroyTask,
                          work);
    if (task == NULL)
    {
        return NULL;
    }

    work->id = HSFD_ORPHEUSAWAKENING;
    work->isStart = false;
    work->unk_1fc = 0;

    sSfdPlayTask = task;

    return task;
}

// FUN_0010be60
u32 H_SfdPlayCmd_CALL_MOVIE()
{
    HSfd* work;
    KwlnTask* task;
    s32 id;

    id = scrGetIntPara(0);

    if (sSfdPlayTask == NULL)
    {
        work = RwCalloc(1, sizeof(HSfd), rwMEMHINTDUR_GLOBAL);
        if (work != NULL)
        {
            task = kwlnTaskCreate(NULL,
                                  "H_SfdPlay",
                                  7383,
                                  H_SfdPlay_UpdateTask,
                                  H_SfdPlay_DestroyTask,
                                  work);

            if (task != NULL)
            {
                work->id = HSFD_ORPHEUSAWAKENING;
                work->isStart = false;
                work->unk_1fc = 0;

                sSfdPlayTask = task;
            }
        }
    }

    work = (HSfd*)sSfdPlayTask->workData;
    work->id = id;
    work->unk_1ee = 0;
    work->unk_204 = 0;
    work->unk_208 = 0;
    work->state = HSFD_STATE_INIT;
    work->unk_20c = 0;

    return true;
}

// FUN_0010bf40
u32 H_SfdPlayCmd_MOVIE_SYNC()
{
    if (sSfdPlayTask == NULL)
    {
        return true;
    }

    return ((HSfd*)sSfdPlayTask->workData)->state == HSFD_STATE_IDLE;
}