#include "Model/mdlManager.h"

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
void MdlManager_SetMdlColor(Model* mdl, RwRGBA* color)
{
    mdl->color = *color;
}

// FUN_00318b00
RwRGBA* MdlManager_GetMdlColor(Model* mdl)
{
    return &mdl->color;
}

// FUN_00318b60
RwMatrix* MdlManager_GetMdlMatrix(Model* mdl)
{
    return &mdl->mat;
}

// FUN_00318b70
RwFrame* MdlManager_GetMdlClumpFrame(Model* mdl)
{
    return (RwFrame*)mdl->clump->object.parent;
}

// FUN_00318b80
RpClump* MdlManager_GetMdlClump(Model* mdl)
{
    return mdl->clump;
}