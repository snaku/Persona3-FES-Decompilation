#include "Kosaka/Field/k_fldFrame.h"
#include "Model/mdlManager.h"
#include "kwln/kwlnTask.h"
#include "kwln/kwln.h"
#include "Primitive/primitive.h"

static RwRGBA sDebugSphereColor = {0, 168, 168, 168};

// FUN_001ad8b0
f32 K_FldFrame_CtlGetSphereCollisRadius(KwlnTask* collisCtlTask)
{
    return ((CollisCtl*)collisCtlTask->workData)->sphereCollisRadius;
}

// FUN_001ad8c0
void K_FldFrame_CtlSetSphereCollisRadius(KwlnTask* collisCtlTask, f32 radius)
{
    CollisCtl* ctl;

    ctl = (CollisCtl*)collisCtlTask->workData;
    ctl->sphereCollisRadius = radius;

    if (radius == 0.0f)
    {
        ctl->flags |= COLLISCTL_FLAG_NOCOLLIS;
        return;
    }

    ctl->flags &= ~COLLISCTL_FLAG_NOCOLLIS;
}

// FUN_001ad910
s32 K_FldFrame_CtlGetXGrid(KwlnTask* collisCtlTask)
{
    return ((CollisCtl*)collisCtlTask->workData)->xGrid;
}

// FUN_001ad920
s32 K_FldFrame_CtlGetZGrid(KwlnTask* collisCtlTask)
{
    return ((CollisCtl*)collisCtlTask->workData)->zGrid;
}

// FUN_001ad940
void K_FldFrame_CtlCopyPos(RwV3d* dst, KwlnTask* collisCtlTask)
{
    CollisCtl* ctl = (CollisCtl*)collisCtlTask->workData;
    RwV3d vec = {0};

    if (ctl->mdl != NULL)
    {
        vec = mdlGetMatrix(ctl->mdl)->pos;
    }

    *dst = vec;
}

// FUN_001addf0
void K_FldFrame_CtlMoveInDir(f32 dist, KwlnTask* collisCtlTask, const RwV3d* normalizedDir)
{
    CollisCtl* ctl;
    RwV3d velocity;

    ctl = (CollisCtl*)collisCtlTask->workData;
    velocity = *normalizedDir;

    if (ctl->state == COLLISCTL_STATE_NOTDIRTY)
    {
        velocity.x *= dist;
        velocity.y *= dist;
        velocity.z *= dist;
        
        ctl->totalDist += (u32)dist;
        ctl->velocity = velocity;

        ctl->state = COLLISCTL_STATE_DIRTY;
    }
}

// FUN_001adec0
void K_FldFrame_CtlMoveForward(f32 dist, KwlnTask* collisCtlTask)
{
    CollisCtl* ctl = (CollisCtl*)collisCtlTask->workData;
    RwV3d velocity = {0};

    if (ctl->state == COLLISCTL_STATE_NOTDIRTY)
    {
        velocity = mdlGetMatrix(ctl->mdl)->at;
        RwV3dNormalize(&velocity, &velocity);
        
        velocity.x *= dist;
        velocity.y *= dist;
        velocity.z *= dist;

        ctl->totalDist += (u32)dist;
        ctl->velocity = velocity;

        ctl->state = COLLISCTL_STATE_DIRTY;
    }
}

// FUN_001adff0
void K_FldFrame_CtlRotate(KwlnTask* collisCtlTask, const RwV3d* axis, f32 angle)
{
    CollisCtl* ctl;
    RwV3d originalPos;
    RwV3d negPos;

    ctl = (CollisCtl*)collisCtlTask->workData;

    if (ctl->mdl != NULL)
    {
        originalPos = mdlGetMatrix(ctl->mdl)->pos;

        negPos.x = originalPos.x * -1.0f;
        negPos.y = originalPos.y * -1.0f;
        negPos.z = originalPos.z * -1.0f;

        mdlTranslate(ctl->mdl, &negPos, rwCOMBINEPOSTCONCAT); // basically just do pos + (-pos) = (0, 0, 0)
        mdlRotate(ctl->mdl, axis, angle, rwCOMBINEPOSTCONCAT);
        mdlTranslate(ctl->mdl, &originalPos, rwCOMBINEPOSTCONCAT);
    }
}