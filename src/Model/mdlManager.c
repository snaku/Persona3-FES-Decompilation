#include "Model/mdlManager.h"
#include "rw/rpworld.h"
#include "rw/rphanim.h"

const f32 gFrameDuration = (1.0f / 30.0f); // 007cadd4. 33.3ms. Not sure where to place this

// FUN_00316690. TODO
Model* MdlManager_InitMdl(u32 type, u32 id)
{
    // TODO

    return NULL;
}

// FUN_00316e00. TODO
Model* MdlManager_CreateMdl(u32 type, u32 id, u32 flags)
{
    // TODO

    return NULL;
}

// FUN_00318870
f32 MdlAnim_GetDurationInFrame(Model* mdl, u16 slotIdx)
{
    f32 duration;

    if (mdl->animSlots[slotIdx].anim.id < 0)
    {
        duration = 0.0f;
    }
    else
    {
        if (mdl->animSlots[slotIdx].anim.hierarchy == NULL ||
           (mdl->animSlots[slotIdx].anim.hierarchy->currentAnim == NULL))
        {
            duration = 0.0f;
        }
        else
        {
            if (mdl->animSlots[slotIdx].anim.hierarchy->currentAnim->pCurrentAnim == NULL)
            {
                duration = 0.0f;
            }
            else
            {
                duration = mdl->animSlots[slotIdx].anim.hierarchy->currentAnim->pCurrentAnim->duration;
            }
        }
    }

    return duration / gFrameDuration;
}

// FUN_00318910
f32 MdlAnim_GetDurationInFrameById(Model* mdl, u16 slotIdx, s16 animId)
{
    f32 duration;

    if (mdl->animSlots[slotIdx].anim.hierarchy == NULL)
    {
        duration = 0.0f;
    }
    else
    {
        duration = mdl->animSlots[slotIdx].anim.table->entries[animId].rtAnim->duration;
    }

    return duration / gFrameDuration;
}

// FUN_00318990
f32 MdlAnim_GetCurrentFrame(Model* mdl, u16 slotIdx)
{
    f32 currTime;

    if (mdl->animSlots[slotIdx].anim.id < 0)
    {
        currTime = 0.0f;
    }
    else
    {
        currTime = mdl->animSlots[slotIdx].anim.currTime;
    }

    return currTime / gFrameDuration;
}

// FUN_00318ad0
void Mdl_SetColor(Model* mdl, RwRGBA* color)
{
    mdl->color = *color;
}

// FUN_00318b00
RwRGBA* Mdl_GetColor(Model* mdl)
{
    return &mdl->color;
}

// FUN_00318b60
RwMatrix* Mdl_GetMatrix(Model* mdl)
{
    return &mdl->mat;
}

// FUN_00318b70
RwFrame* Mdl_GetClumpFrame(Model* mdl)
{
    return (RwFrame*)mdl->clump->object.parent;
}

// FUN_00318b80
RpClump* Mdl_GetClump(Model* mdl)
{
    return mdl->clump;
}

// FUN_00319010
void Mdl_EnableFullShadow(Model* mdl)
{
    mdl->flags |= MDL_FLAG_FULLSHADOW;
}

// FUN_00319030
void Mdl_DisableFullShadow(Model* mdl)
{
    mdl->flags &= ~MDL_FLAG_FULLSHADOW;
}

// FUN_00319090
void MdlLookAt_SetBlendRotFactor(Model* mdl, f32 blendRotFactor)
{
    mdl->animSlots[0].lookAt.blendRotFactor = blendRotFactor;
}

// FUN_003190a0
void MdlLookAt_SetMaxAngles(Model* mdl, f32 maxPitchAngle, f32 maxYawAngle)
{
    mdl->animSlots[0].lookAt.maxPitchAngle = maxPitchAngle;
    mdl->animSlots[0].lookAt.maxYawAngle = maxYawAngle;
}

// FUN_003190b0
void MdlLookAt_SetTargetPosXYZ(Model* mdl, RwV3d* target)
{
    mdl->animSlots[0].lookAt.flags |= MDL_LOOKAT_FLAG_XYZ;
    mdl->animSlots[0].lookAt.flags &= ~(MDL_LOOKAT_FLAG_XYZCS | MDL_LOOKAT_FLAG_XY);
    mdl->animSlots[0].lookAt.flags &= ~MDL_LOOKAT_FLAG_NOTARGET;

    mdl->animSlots[0].lookAt.targetPos = *target;
}

// FUN_00319100
void MdlLookAt_SetTargetPosXYZCS(Model* mdl, RwV3d* target)
{
    mdl->animSlots[0].lookAt.flags |= MDL_LOOKAT_FLAG_XYZCS;
    mdl->animSlots[0].lookAt.flags &= ~(MDL_LOOKAT_FLAG_XYZ | MDL_LOOKAT_FLAG_XY);
    mdl->animSlots[0].lookAt.flags &= ~MDL_LOOKAT_FLAG_NOTARGET;

    mdl->animSlots[0].lookAt.targetPos = *target;
}

// FUN_00319150
void MdlLookAt_SetTargetPosXY(Model* mdl, f32 xTarget, f32 yTarget)
{
    mdl->animSlots[0].lookAt.flags |= MDL_LOOKAT_FLAG_XY;
    mdl->animSlots[0].lookAt.flags &= ~(MDL_LOOKAT_FLAG_XYZCS | MDL_LOOKAT_FLAG_XYZ);
    mdl->animSlots[0].lookAt.flags &= ~MDL_LOOKAT_FLAG_NOTARGET;

    mdl->animSlots[0].lookAt.targetPos.x = xTarget;
    mdl->animSlots[0].lookAt.targetPos.y = yTarget;
}

// FUN_00319190
void MdlLookAt_DisableTarget(Model* mdl)
{
    mdl->animSlots[0].lookAt.flags |= MDL_LOOKAT_FLAG_NOTARGET;
}

// FUN_003191d0
u8 MdlLookAt_IsActive(Model* mdl)
{
    return (mdl->animSlots[0].lookAt.flags & (MDL_LOOKAT_FLAG_XYZCS |
                                              MDL_LOOKAT_FLAG_XYZ   |
                                              MDL_LOOKAT_FLAG_XY    | 
                                              MDL_LOOKAT_FLAG_NOTARGET)) != 0;
}

// FUN_00319210
void MdlLookAt_SetTargetScale(Model* mdl, RwV3d* scale)
{
    mdl->animSlots[0].lookAt.targetScale = *scale;
}