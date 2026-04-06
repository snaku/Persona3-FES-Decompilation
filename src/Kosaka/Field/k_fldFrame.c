#include "Kosaka/Field/k_fldFrame.h"
#include "Model/mdlManager.h"
#include "kwln/kwlnTask.h"

// FUN_001ad8b0
f32 K_FldFrame_GetSphereCollisRadius(KwlnTask* collisCtlTask)
{
    return FLDFRAME_GET(collisCtlTask)->sphereCollisRadius;
}

// FUN_001ad8c0
void K_FldFrame_SetSphereCollisRadius(KwlnTask* collisCtlTask, f32 radius)
{
    FldFrame* fldFrame;

    fldFrame = FLDFRAME_GET(collisCtlTask);
    fldFrame->sphereCollisRadius = radius;

    if (radius == 0.0f)
    {
        fldFrame->flags |= FLDFRAME_FLAG_NOCOLLIS;
        return;
    }

    fldFrame->flags &= ~FLDFRAME_FLAG_NOCOLLIS;
}

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
void K_FldFrame_MoveInDir(f32 speed, KwlnTask* collisCtlTask, const RwV3d* normalizedDir)
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

// FUN_001adec0
void K_FldFrame_MoveForward(f32 speed, KwlnTask* collisCtlTask)
{
    FldFrame* fldFrame = FLDFRAME_GET(collisCtlTask);
    RwV3d velocity = {0};

    if (fldFrame->state == FLDFRAME_STATE_NOTDIRTY)
    {
        velocity = Mdl_GetMatrix(fldFrame->mdl)->at;
        RwV3dNormalize(&velocity, &velocity);
        
        velocity.x *= speed;
        velocity.y *= speed;
        velocity.z *= speed;

        fldFrame->totalDist += (u32)speed;
        fldFrame->velocity = velocity;

        fldFrame->state = FLDFRAME_STATE_DIRTY;
    }
}

// FUN_001adff0
void K_FldFrame_Rotate(KwlnTask* collisCtlTask, const RwV3d* axis, f32 angle)
{
    FldFrame* fldFrame;
    RwV3d originalPos;
    RwV3d negPos;

    fldFrame = FLDFRAME_GET(collisCtlTask);

    if (fldFrame->mdl != NULL)
    {
        originalPos = Mdl_GetMatrix(fldFrame->mdl)->pos;

        negPos.x = originalPos.x * -1.0f;
        negPos.y = originalPos.y * -1.0f;
        negPos.z = originalPos.z * -1.0f;

        Mdl_Translate(fldFrame->mdl, &negPos, rwCOMBINEPOSTCONCAT); // basically just do pos + (-pos) = (0, 0, 0)
        Mdl_Rotate(fldFrame->mdl, axis, angle, rwCOMBINEPOSTCONCAT);
        Mdl_Translate(fldFrame->mdl, &originalPos, rwCOMBINEPOSTCONCAT);
    }
}