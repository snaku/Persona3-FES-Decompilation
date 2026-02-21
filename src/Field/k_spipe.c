#include "kwln/kwlnTask.h"
#include "kwln/kwln.h"
#include "Field/k_spipe.h"
#include "rw/rwcore.h"
#include "temporary.h"
#include "g_data.h"

static KwlnTask* sDraw3DTask; // 007ce134. Task name = "3D Draw"

// FUN_00199520
void* FldSPipe_Update3DDrwBeginTask(KwlnTask* draw3DBeginTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_001995f0
void* FldSPipe_Update3DDrwEndTask(KwlnTask* draw3DEndTask)
{
    RwCamera* camera;

    RWRENDERSTATE_SET(RW_RENDER_STATE_FOG_ENABLE, false);
    RWRENDERSTATE_SET(RW_RENDER_STATE_FOG_ENABLE, true); // ??
    RWRENDERSTATE_SET(RW_RENDER_STATE_FOG_COLOR, PACK_RWRGBA(gFogRed, gFogGreen, gFogBlue, gFogAlpha));
    RWRENDERSTATE_SET(RW_RENDER_STATE_FOG_TYPE, RW_FOG_TYPE_1);

    camera = Kwln_GetMainCamera();
    RwCamera_EndUpdate(camera);
    
    KwlnRoot_FUN_00198610(3, 0);

    return KWLN_TASK_CONTINUE;
}

// FUN_001996c0
KwlnTask* FldSPipe_Create3DDrwBeginTask(KwlnTask* draw3DTask)
{
    return KwlnTask_Create(draw3DTask, "3D Draw Begin", 2098, FldSPipe_Update3DDrwBeginTask, NULL, NULL);
}

// FUN_00199700
KwlnTask* FldSPipe_Create3DDrwEndTask(KwlnTask* draw3DTask)
{
    return KwlnTask_Create(draw3DTask, "3D Draw End", 4167, FldSPipe_Update3DDrwEndTask, NULL, NULL);
}

// FUN_00199740
void* FldSPipe_UpdateShadowNodeTask(KwlnTask* shadowNodeTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_001997a0
KwlnTask* FldSPipe_CreateShadowNodeTask(KwlnTask* draw3DTask)
{
    return KwlnTask_Create(draw3DTask, "shadow node(camera all clear)", 2069, FldSPipe_UpdateShadowNodeTask, NULL, NULL);
}