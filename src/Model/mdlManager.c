#include "Model/mdlManager.h"

#define MODEL_PATH "model/"

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

// FUN_00318b60
RwMatrix* MdlManager_GetMdlMatrix(Model* mdl)
{
    return &mdl->mat;
}