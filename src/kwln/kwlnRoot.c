#include "kwln/kwlnRoot.h"
#include "kwln/kwlnTask.h"
#include "rw/rwcore.h"
#include "temporary.h"
#include "h_snd.h"

KwlnTask* KwlnRoot_Create2DDrawBeginTask();
KwlnTask* KwlnRoot_Create2DDrawBeginPreEndTask();
KwlnTask* KwlnRoot_Create2DDrawEndTask();
KwlnTask* KwlnRoot_Create3DOn2DDrawEndTask();

// FUN_00198590. Not sure if it's in this file or in 'kwln.c' ?
RwCamera* KwlnRoot_GetMainCamera()
{
    return ctx.mainCamera;
}

// FUN_001985b0. Not sure if it's in this file or in 'kwln.c' ?
void KwlnRoot_SetClearColor(u8 r, u8 g, u8 b, u8 a)
{
    ctx.clearColor.r = r;
    ctx.clearColor.g = g;
    ctx.clearColor.b = b;
    ctx.clearColor.a = a;
}

// FUN_00198650
s32 KwlnRoot_UpdateRootProcTask(KwlnTask* rootProcTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_001988f0
void KwlnRoot_DestroyRootProcTask(KwlnTask* rootProcTask)
{
    // TODO

    RW_FREE(rootProcTask->taskData);
}

// FUN_00198940
KwlnTask* KwlnRoot_CreateRootProcTask()
{
    KwlnTask* rootProcTask;
    KwlnRoot* root;

    root = RW_CALLOC(1, sizeof(KwlnRoot), 0x40000);
    if (root == NULL)
    {
        return NULL;
    }

    rootProcTask = KwlnTask_Init("rootProc", 0, KwlnRoot_UpdateRootProcTask, KwlnRoot_DestroyRootProcTask, root);
    H_Snd_FUN_00109ca0(0, 1);
    H_Snd_FUN_00109ca0(1, 2);

    return rootProcTask;
}

// FUN_001989e0
s32 KwlnRoot_Update2DDrawBeginTask(KwlnTask* drawBegin2dTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_00198b10
s32 KwlnRoot_Update2DDrawPreEndTask(KwlnTask* drawBegin2dPETask)
{
    return KWLN_TASK_CONTINUE;
}

// FUN_00198b20
s32 KwlnRoot_Update2DDrawEndTask(KwlnTask* drawEnd2dTask)
{
    RwCamera* camera = KwlnRoot_GetMainCamera();
    RwCamera_EndUpdate(camera);

    return KWLN_TASK_CONTINUE;
}

// FUN_00198b50
KwlnTask* KwlnRoot_Create2DDrawBeginTask()
{
    return KwlnTask_Init("2D Draw Begin", 4196, KwlnRoot_Update2DDrawBeginTask, NULL, NULL);
}

// FUN_00198b90
KwlnTask* KwlnRoot_Create2DDrawBeginPreEndTask()
{
    return KwlnTask_Init("2D Draw Begin Pre End", 5231, KwlnRoot_Update2DDrawPreEndTask, NULL, NULL);
}

// FUN_00198bd0
KwlnTask* KwlnRoot_Create2DDrawEndTask()
{
    return KwlnTask_Init("2D Draw End", 5241, KwlnRoot_Update2DDrawEndTask, NULL, NULL);
}

// FUN_00198d20
s32 KwlnRoot_Update3DOn2DDrawEndTask(KwlnTask* drawEnd3d2dTask)
{
    RwCamera* camera;

    if (ctx.fogParameter.fogEnabled)
    {
        RWRENDERSTATE_SET(RW_RENDER_STATE_FOG_ENABLE, true);
        RWRENDERSTATE_SET(RW_RENDER_STATE_FOG_COLOR, PACK_RWRGBA(ctx.fogParameter.r, ctx.fogParameter.g, ctx.fogParameter.b, ctx.fogParameter.a));
        RWRENDERSTATE_SET(RW_RENDER_STATE_FOG_TYPE, RW_FOG_TYPE_1);
    }

    camera = KwlnRoot_GetMainCamera();
    RwCamera_EndUpdate(camera);

    return KWLN_TASK_CONTINUE;
}

// FUN_00198e50
KwlnTask* KwlnRoot_Create3DOn2DDrawEndTask()
{
    return KwlnTask_Init("3D on 2D Draw End", 6320, KwlnRoot_Update3DOn2DDrawEndTask, NULL, NULL);
}