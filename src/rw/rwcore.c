#include "rw/rwcore.h"

// FUN_004c9b40
static RwCamera* Camera_EndUpdate(RwCamera* camera)
{
    RwStandardFunc cameraEndUpdateFunc;

    cameraEndUpdateFunc = RWSTDFUNC(RW_STD_FUNC_CAMERA_END_UPDATE);
    if (cameraEndUpdateFunc(NULL, camera, 0))
    {
        RW_CURRCAMERA = NULL;
        return camera;
    }

    return NULL;
}

// FUN_004c9d00
RwCamera* RwCamera_EndUpdate(RwCamera* camera)
{
    return camera->endUpdate(camera);
}

// FUN_004c9d10
RwCamera* RwCamera_BeginUpdate(RwCamera* camera)
{
    return camera->beginUpdate(camera);
}

// FUN_004c9e90
RwCamera* RwCamera_Clear(RwCamera* camera, RwRGBA* colors, RwCameraClearMode clearMode)
{
    RwStandardFunc cameraClearFunc;

    cameraClearFunc = RWSTDFUNC(RW_STD_FUNC_CAMERA_CLEAR);
    if (cameraClearFunc(camera, colors, clearMode))
    {
        return camera;
    }

    return NULL;
}

// FUN_004c9f00
RwCamera* RwCamera_SetProjectionType(RwCamera* camera, RwCameraProjectionType projType)
{
    // TODO

    return camera;
}