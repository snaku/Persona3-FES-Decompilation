#include "kwln/kwlnTask.h"
#include "rw/rwplcore.h"
#include "h_sfdply.h"
#include "temporary.h"

// FUN_0010a860
void* H_SfdPlay_UpdateTask(KwlnTask* sfdPlayTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_0010bb00
void H_SfdPlay_DestroyTask(KwlnTask* sfdPlayTask)
{
    // TODO
}

// FUN_0010bda0
KwlnTask* H_SfdPlay_CreateTask(KwlnTask* calendarTask)
{
    KwlnTask* sfdPlayTask;
    SfdPlay* sfdPlay;

    sfdPlay = RW_CALLOC(1, sizeof(SfdPlay), 0x40000);
    if (sfdPlay == NULL)
    {
        return NULL;
    }

    sfdPlayTask = KwlnTask_Create(calendarTask, "H_SfdPlay", 7383, H_SfdPlay_UpdateTask, H_SfdPlay_DestroyTask, sfdPlay);
    if (sfdPlayTask == NULL)
    {
        return NULL;
    }

    sfdPlay->unk_1ea = 7;
    sfdPlay->unk_1f4 = 0;
    sfdPlay->unk_1fc = 0;

    ctx.sfdPlayTask = sfdPlayTask;

    return sfdPlayTask;
}