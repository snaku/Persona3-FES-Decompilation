#include "kwln/kwlnTask.h"
#include "kwln/kwlnRoot.h"
#include "Field/k_spipe.h"
#include "rw/rwcore.h"
#include "temporary.h"
#include "g_data.h"

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
    RWRENDERSTATE_SET(RW_RENDER_STATE_FOG_COLOR, PACK_RWRGBA(ctx.fogParameter.r, ctx.fogParameter.g, ctx.fogParameter.b, ctx.fogParameter.a));
    RWRENDERSTATE_SET(RW_RENDER_STATE_FOG_TYPE, RW_FOG_TYPE_1);

    camera = KwlnRoot_GetMainCamera();
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