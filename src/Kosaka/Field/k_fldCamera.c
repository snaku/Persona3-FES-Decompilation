#include "Kosaka/Field/k_fldCamera.h"
#include "Kosaka/k_assert.h"
#include "kwln/kwlnTask.h"
#include "Scene/mt_scene.h"
#include "Scene/resrcManager.h"

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

// FUN_001d5f30
void K_FldCamera_SetPlayerResrcByTypeid(KwlnTask* fldCameraTask, u16 resTypeId)
{
    FldCamera* fldCam;

    fldCam = (FldCamera*)fldCameraTask->workData;

    if (RESRC_GET_TYPE(resTypeId) == RESRC_TYPE_MODELPARTY)
    {
        fldCam->playerResrc = (ResrcModelParty*)MT_Scene_GetRes(resTypeId);
    }
}