#include "Kosaka/k_vpad.h"
#include "Kosaka/Field/k_fldFrame.h"
#include "Kosaka/Field/k_field.h"
#include "Kosaka/Field/k_event.h"
#include "kwln/kwlnTask.h"

// FUN_001e05b0
void* K_VPad_UpdateTask(KwlnTask* rotatePcTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_001e1200
void K_VPad_DestroyTask(KwlnTask* rotatePcTask)
{
    RwFree(rotatePcTask->workData);
}

// FUN_001e1230
KwlnTask* K_VPad_CreateTask(KwlnTask* parent, KwlnTask* collisCtlTask, Model* mdl)
{
    KwlnTask* task;
    VPadWork* work;

    work = RwCalloc(1, sizeof(VPadWork), rwMEMHINTDUR_GLOBAL);
    if (work == NULL)
    {
        return NULL;
    }

    task = kwlnTaskCreateWithAutoPriority(parent,
                                          10,
                                          "player pad proc",
                                          K_VPad_UpdateTask,
                                          K_VPad_DestroyTask,
                                          work);

    work->collisCtlTask = collisCtlTask;
    work->mdl = mdl;
    work->rotateTask = K_VPad_CreateRotateTask(task, collisCtlTask, mdl);

    return task;
}

// FUN_001e13f0
void* K_VPad_UpdateRotateTask(KwlnTask* rotatePcTask)
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
void K_VPad_DestroyRotateTask(KwlnTask* rotatePcTask)
{
    RwFree(rotatePcTask->workData);
}

// FUN_001e14e0
KwlnTask* K_VPad_CreateRotateTask(KwlnTask* parent, KwlnTask* collisCtlTask, Model* mdl)
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
                                          K_VPad_UpdateRotateTask,
                                          K_VPad_DestroyRotateTask,
                                          work);

    work->collisCtlTask = collisCtlTask;
    work->mdl = mdl;

    return task;
}

// FUN_001e1820
u32 K_VPad_IsRotating(KwlnTask* rotatePcTask)
{
    return ((PcRotateWork*)rotatePcTask->workData)->state == PCROTATE_STATE_ROTATING;
}