#include "Model/mdlManager.h"
#include "rw/rpworld.h"

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

// FUN_003190b0
void MdlLookAt_SetTargetXYZ(Model* mdl, RwV3d* target)
{
    mdl->lookAt.flags |= MDL_LOOKAT_FLAG_XYZ;
    mdl->lookAt.flags &= ~(MDL_LOOKAT_FLAG_XYZCS | MDL_LOOKAT_FLAG_XY);
    mdl->lookAt.flags &= ~MDL_LOOKAT_FLAG_NOTARGET;

    mdl->lookAt.target = *target;
}

// FUN_00319190
void MdlLookAt_DisableTarget(Model* mdl)
{
    mdl->lookAt.flags |= MDL_LOOKAT_FLAG_NOTARGET;
}

// FUN_003191d0
u8 MdlLookAt_IsActive(Model* mdl)
{
    return (mdl->lookAt.flags & (MDL_LOOKAT_FLAG_XYZCS |
                                 MDL_LOOKAT_FLAG_XYZ   |
                                 MDL_LOOKAT_FLAG_XY    | 
                                 MDL_LOOKAT_FLAG_NOTARGET)) != 0;
}