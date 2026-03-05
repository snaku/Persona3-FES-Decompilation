#include "Model/mdlManager.h"

// FUN_00318b60
RwMatrix* MdlManager_GetMdlMatrix(Model* mdl)
{
    return &mdl->mat;
}