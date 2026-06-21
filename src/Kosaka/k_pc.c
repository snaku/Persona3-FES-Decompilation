#include "Kosaka/k_pc.h"
#include "Kosaka/Field/k_fldFrame.h"
#include "Kosaka/Field/k_field.h"
#include "Kosaka/Field/k_event.h"
#include "kwln/kwlnTask.h"

// FUN_001e13f0
void* K_Pc_UpdateRotateTask(KwlnTask* rotatePcTask)
{
    static const RwV3d sAxis = { 0.0f, 1.0f, 0.0f }; // 00683da0
    PcRotateWork* work;
    RwV3d axis;

    work = (PcRotateWork*)rotatePcTask->workData;
    axis = sAxis;

    switch (work->state)
    {
        case PCROTATE_STATE_IDLE: break;

        case PCROTATE_STATE_ROTATING:
            work->steps++;

            K_FldFrame_CtlRotate(work->collisCtlTask, &axis, work->angle);

            if (work->steps >= work->maxSteps)
            {
                K_FldFrame_CtlUpdateMdlMat(work->collisCtlTask, &work->mat);
                K_FldEvent_001cd650(K_Field_Get()->eventTask, false);
                work->state = PCROTATE_STATE_IDLE;
            }
    }

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