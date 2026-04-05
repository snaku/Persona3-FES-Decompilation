#include "Kosaka/Field/k_fldFrame.h"
#include "Model/mdlManager.h"
#include "kwln/kwlnTask.h"

// FUN_001ad940
void K_FldFrame_CopyPos(RwV3d* dst, const KwlnTask* collisCtlTask)
{
    FldFrame* fldFrame = FLDFRAME_GET(collisCtlTask);
    RwV3d vec = {0};

    if (fldFrame->mdl != NULL)
    {
        vec = Mdl_GetMatrix(fldFrame->mdl)->pos;
    }

    *dst = vec;
}