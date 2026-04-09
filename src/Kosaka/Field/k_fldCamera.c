#include "Kosaka/Field/k_fldCamera.h"
#include "Kosaka/k_assert.h"
#include "kwln/kwlnTask.h"

// FUN_001d5c00
u32 K_FldCamera_GetType(KwlnTask* fldCameraTask)
{
    return ((FldCamera*)fldCameraTask->workData)->type;
}

// FUN_001d5e10
RwV3d* K_FldCamera_GetPos(KwlnTask* fldCameraTask)
{
    return &((FldCamera*)fldCameraTask->workData)->frame->modelling.pos;
}