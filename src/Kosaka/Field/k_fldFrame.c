#include "Kosaka/Field/k_fldFrame.h"
#include "Model/mdlManager.h"
#include "kwln/kwlnTask.h"

// FUN_001ad940
void K_FldFrame_CopyPos(RwV3d* dst, KwlnTask* collisCtlTask)
{
    FldFrame* fldFrame = FLDFRAME_GET(collisCtlTask);
    RwV3d vec = {0};

    if (fldFrame->mdl != NULL)
    {
        vec = Mdl_GetMatrix(fldFrame->mdl)->pos;
    }

    *dst = vec;
}

// FUN_001addf0
void K_FldFrame_SetVelocityFromSpeedAndDir(f32 speed, KwlnTask* collisCtlTask, const RwV3d* normalizedDir)
{
    FldFrame* fldFrame;
    RwV3d velocity;

    fldFrame = FLDFRAME_GET(collisCtlTask);
    velocity = *normalizedDir;

    if (fldFrame->state == FLDFRAME_STATE_NOTDIRTY)
    {
        velocity.x *= speed;
        velocity.y *= speed;
        velocity.z *= speed;
        
        fldFrame->totalDist += (u32)speed;
        fldFrame->velocity = velocity;

        fldFrame->state = FLDFRAME_STATE_DIRTY;
    }
}