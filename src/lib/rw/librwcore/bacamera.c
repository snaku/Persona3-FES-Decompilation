#include "rw/rwcore.h"

// FUN_004c9b40
static RwCamera* CameraEndUpdate(RwCamera* camera)
{
    RwStandardFunc cameraEndUpdateFunc;

    cameraEndUpdateFunc = RWSTDFUNC(rwSTANDARDCAMERAENDUPDATE);
    if (!cameraEndUpdateFunc(NULL, camera, 0))
    {
        return NULL;
    }

    RwCameraGetCurrentCamera() = NULL;
    return camera;
}

// FUN_004c9d00
RwCamera* RwCameraEndUpdate(RwCamera* camera)
{
    return camera->endUpdate(camera);
}

// FUN_004c9d10
RwCamera* RwCameraBeginUpdate(RwCamera* camera)
{
    return camera->beginUpdate(camera);
}

// FUN_004c9e90
RwCamera* RwCameraClear(RwCamera* camera, RwRGBA* colors, RwCameraClearMode clearMode)
{
    RwStandardFunc cameraClearFunc;

    cameraClearFunc = RWSTDFUNC(rwSTANDARDCAMERACLEAR);
    if (cameraClearFunc(camera, colors, clearMode))
    {
        return camera;
    }

    return NULL;
}

// FUN_004c9df0
RwFrustumTestResult RwCameraFrustumTestSphere(const RwCamera* camera, const RwSphere* sphere)
{
    const RwFrustumPlane *frustumPlane;
    RwInt32 planeCount;
    RwFrustumTestResult result;
    RwReal dot;

    result = rwSPHEREINSIDE;
    frustumPlane = camera->frustumPlanes;
    planeCount = 6;
    while (planeCount--)
    {
        dot = sphere->center.x * frustumPlane->plane.normal.x
            + sphere->center.y * frustumPlane->plane.normal.y
            + sphere->center.z * frustumPlane->plane.normal.z;
        dot -= frustumPlane->plane.distance;
        if (dot > sphere->radius)
        {
            return rwSPHEREOUTSIDE;
        }
        else if (dot > -sphere->radius)
        {
            result = rwSPHEREBOUNDARY;
        }
        frustumPlane++;
    }
    return result;
}

// FUN_004c9f00
RwCamera* RwCameraSetProjection(RwCamera* camera, RwCameraProjection projType)
{
    // TODO

    return camera;
}

// FUN_004c9f90
RwCamera* RwCameraSetViewWindow(RwCamera* camera, const RwV2d* viewWindow)
{
    // TODO

    return camera;
}
