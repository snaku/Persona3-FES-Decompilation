#include "kwln/kwlnRoot.h"
#include "kwln/kwlnTask.h"
#include "kwln/kwln.h"
#include "rw/rwcore.h"
#include "temporary.h"
#include "h_snd.h"
#include "h_fade.h"
#include "h_dbprt.h"

KwlnTask* kwlnRootCreate2DDrawBeginTask();
KwlnTask* kwlnRootCreate2DDrawBeginPreEndTask();
KwlnTask* kwlnRootCreate2DDrawEndTask();
KwlnTask* kwlnRootCreate3DOn2DZClearTask();
KwlnTask* kwlnRootCreate3DOn2DDrawBeginTask();
KwlnTask* kwlnRootCreate3DOn2DDrawEndTask();
KwlnTask* kwlnRootCreateEtcDrawTask();

// FUN_00198650
void* kwlnRootUpdateTask(KwlnTask* rootTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_001988f0
void kwlnRootDestroyTask(KwlnTask* rootTask)
{
    // TODO

    RwFree(rootTask->workData);
}

// FUN_00198940
KwlnTask* kwlnRootCreateTask()
{
    KwlnTask* rootTask;
    KwlnRootWork* work;

    work = RwCalloc(1, sizeof(KwlnRootWork), rwMEMHINTDUR_GLOBAL);
    if (work == NULL)
    {
        return NULL;
    }

    rootTask = kwlnTaskInit("rootProc", 0, kwlnRootUpdateTask, kwlnRootDestroyTask, work);
    H_Snd_FUN_00109ca0(0, 1);
    H_Snd_FUN_00109ca0(1, 2);

    return rootTask;
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
    RwCameraClear(kwlnGetMainCamera(), kwlnGetClearColor(), rwCAMERACLEARZ);

    return KWLNTASK_CONTINUE;
}

// FUN_00198c60
void* kwlnRootUpdate3DOn2DDrawBeginTask()
{
    if (kwlnCameraBeginUpdate() != NULL)
    {
        kwlnSetFlags(KWLN_FLAG_ERR | KWLN_FLAG_3DDRAW, false);
        kwlnSetFlags(KWLN_FLAG_3DDRAW, true);

        RwRenderStateSet(rwRENDERSTATEZTESTENABLE, true);
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, true);
    }
    else
    {
        K_ASSERT(false, 719);
        kwlnSetFlags(KWLN_FLAG_ERR, true);
    }

    return KWLNTASK_CONTINUE;
}

// FUN_00198d20
void* kwlnRootUpdate3DOn2DDrawEndTask(KwlnTask* drawEnd3d2dTask)
{
    if (gFogEnabled == true)
    {
        RwRenderStateSet(rwRENDERSTATEFOGENABLE, true);
        RwRenderStateSet(rwRENDERSTATEFOGCOLOR, PACK_RWRGBA(gFogRed, gFogGreen, gFogBlue, gFogAlpha));
        RwRenderStateSet(rwRENDERSTATEFOGTYPE, rwFOGTYPELINEAR);
    }

    kwlnCameraEndUpdate();

    return KWLNTASK_CONTINUE;
}

// FUN_00198dd0
KwlnTask* kwlnRootCreate3DOn2DZClearTask()
{
    return kwlnTaskInit("3D on 2D Zclear", 5243, kwlnRootUpdate3DOn2DZClearTask, NULL, NULL);
}

// FUN_00198e10
KwlnTask* kwlnRootCreate3DOn2DDrawBeginTask()
{
    return kwlnTaskInit("3D on 2D Draw Begin", 5245, kwlnRootUpdate3DOn2DDrawBeginTask, NULL, NULL);
}

// FUN_00198e50
KwlnTask* kwlnRootCreate3DOn2DDrawEndTask()
{
    return kwlnTaskInit("3D on 2D Draw End", 6320, kwlnRootUpdate3DOn2DDrawEndTask, NULL, NULL);
}

// FUN_00198f90
void* kwlnRootUpdateEtcDrawTask(KwlnTask* etcDrawTask)
{
    H_Fade_Main();

    H_Dbprt_Main();
    H_Dbprt_Flush();

    return KWLNTASK_CONTINUE;
}

// FUN_001990c0
KwlnTask* kwlnRootCreateEtcDrawTask()
{
    return kwlnTaskInit("etc Draw", 6335, kwlnRootUpdateEtcDrawTask, NULL, NULL);
}