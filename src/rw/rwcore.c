#include "rw/rwcore.h"

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
    // TODO

    return camera;
}