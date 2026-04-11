#include "Kosaka/k_spipe.h"
#include "kwln/kwlnTask.h"
#include "kwln/kwln.h"
#include "rw/rwcore.h"
#include "temporary.h"
#include "g_data.h"

static KwlnTask* sDraw3DTask; // 007ce134. Task name = "3D Draw"

// FUN_00199520
void* K_SPipe_Update3DDrwBeginTask(KwlnTask* draw3DBeginTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_001995f0
void* K_SPipe_Update3DDrwEndTask(KwlnTask* draw3DEndTask)
{
    RWRENDERSTATE_SET(rwRENDERSTATEFOGENABLE, false);
    RWRENDERSTATE_SET(rwRENDERSTATEFOGENABLE, true);  // ??
    RWRENDERSTATE_SET(rwRENDERSTATEFOGCOLOR, PACK_RWRGBA(gFogRed, gFogGreen, gFogBlue, gFogAlpha));
    RWRENDERSTATE_SET(rwRENDERSTATEFOGTYPE, rwFOGTYPE1);

    kwlnCameraEndUpdate();
    
    KwlnRoot_FUN_00198610(3, 0);

    return KWLNTASK_CONTINUE;
}

// FUN_001996c0
KwlnTask* K_SPipe_Create3DDrwBeginTask(KwlnTask* draw3DTask)
{
    return kwlnTaskCreate(draw3DTask, "3D Draw Begin", 2098, K_SPipe_Update3DDrwBeginTask, NULL, NULL);
}

// FUN_00199700
KwlnTask* K_SPipe_Create3DDrwEndTask(KwlnTask* draw3DTask)
{
    return kwlnTaskCreate(draw3DTask, "3D Draw End", 4167, K_SPipe_Update3DDrwEndTask, NULL, NULL);
}

// FUN_00199740
void* K_SPipe_UpdateShadowNodeTask(KwlnTask* shadowNodeTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_001997a0
KwlnTask* K_SPipe_CreateShadowNodeTask(KwlnTask* draw3DTask)
{
    return kwlnTaskCreate(draw3DTask, "shadow node(camera all clear)", 2069, K_SPipe_UpdateShadowNodeTask, NULL, NULL);
}