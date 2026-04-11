#include "kwln/kwlnRoot.h"
#include "kwln/kwlnTask.h"
#include "kwln/kwln.h"
#include "rw/rwcore.h"
#include "temporary.h"
#include "h_snd.h"

KwlnTask* kwlnRootCreate2DDrawBeginTask();
KwlnTask* kwlnRootCreate2DDrawBeginPreEndTask();
KwlnTask* kwlnRootCreate2DDrawEndTask();
KwlnTask* kwlnRootCreate3DOn2DZClearTask();
KwlnTask* kwlnRootCreate3DOn2DDrawEndTask();

// FUN_00198610
void kwlnRootFUN_00198610(u32 flags, u8 enabled)
{
    // TODO
}

// FUN_00198650
void* kwlnRootUpdateRootProcTask(KwlnTask* rootProcTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_001988f0
void kwlnRootDestroyRootProcTask(KwlnTask* rootProcTask)
{
    // TODO

    RW_FREE(rootProcTask->workData);
}

// FUN_00198940
KwlnTask* kwlnRootCreateRootProcTask()
{
    KwlnTask* rootProcTask;
    KwlnRootWork* root;

    root = RW_CALLOC(1, sizeof(KwlnRootWork), 0x40000);
    if (root == NULL)
    {
        return NULL;
    }

    rootProcTask = kwlnTaskInit("rootProc", 0, kwlnRootUpdateRootProcTask, kwlnRootDestroyRootProcTask, root);
    H_Snd_FUN_00109ca0(0, 1);
    H_Snd_FUN_00109ca0(1, 2);

    return rootProcTask;
}

// FUN_001989e0
void* kwlnRootUpdate2DDrawBeginTask(KwlnTask* drawBegin2dTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_00198b10
void* kwlnRootUpdate2DDrawPreEndTask(KwlnTask* drawBegin2dPETask)
{
    return KWLNTASK_CONTINUE;
}

// FUN_00198b20
void* kwlnRootUpdate2DDrawEndTask(KwlnTask* drawEnd2dTask)
{
    kwlnCameraEndUpdate();

    return KWLNTASK_CONTINUE;
}

// FUN_00198b50
KwlnTask* kwlnRootCreate2DDrawBeginTask()
{
    return kwlnTaskInit("2D Draw Begin", 4196, kwlnRootUpdate2DDrawBeginTask, NULL, NULL);
}

// FUN_00198b90
KwlnTask* kwlnRootCreate2DDrawBeginPreEndTask()
{
    return kwlnTaskInit("2D Draw Begin Pre End", 5231, kwlnRootUpdate2DDrawPreEndTask, NULL, NULL);
}

// FUN_00198bd0
KwlnTask* kwlnRootCreate2DDrawEndTask()
{
    return kwlnTaskInit("2D Draw End", 5241, kwlnRootUpdate2DDrawEndTask, NULL, NULL);
}

// FUN_00198c10
void* kwlnRootUpdate3DOn2DZClearTask(KwlnTask* zclear2D3DTask)
{
    RwCamera* camera = kwlnGetMainCamera();
    RwRGBA* clearColor = kwlnGetClearColor();

    RwCameraClear(camera, clearColor, rwCAMERACLEARZ);

    return KWLNTASK_CONTINUE;
}

// FUN_00198d20
void* kwlnRootUpdate3DOn2DDrawEndTask(KwlnTask* drawEnd3d2dTask)
{
    if (gFogEnabled)
    {
        RWRENDERSTATE_SET(rwRENDERSTATEFOGENABLE, true);
        RWRENDERSTATE_SET(rwRENDERSTATEFOGCOLOR, PACK_RWRGBA(gFogRed, gFogGreen, gFogBlue, gFogAlpha));
        RWRENDERSTATE_SET(rwRENDERSTATEFOGTYPE, rwFOGTYPE1);
    }

    kwlnCameraEndUpdate();

    return KWLNTASK_CONTINUE;
}

// FUN_00198dd0
KwlnTask* kwlnRootCreate3DOn2DZClearTask()
{
    return kwlnTaskInit("3D on 2D Zclear", 5243, kwlnRootUpdate3DOn2DZClearTask, NULL, NULL);
}

// FUN_00198e50
KwlnTask* kwlnRootCreate3DOn2DDrawEndTask()
{
    return kwlnTaskInit("3D on 2D Draw End", 6320, kwlnRootUpdate3DOn2DDrawEndTask, NULL, NULL);
}