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

    RW_CURRCAMERA = NULL;
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

// FUN_004c9f00
RwCamera* RwCameraSetProjectionType(RwCamera* camera, RwCameraProjection projType)
{
    // TODO

    return camera;
}