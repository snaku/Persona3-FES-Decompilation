#include "Kosaka/k_view.h"
#include "Kernel/Kwln/kwln.h"
#include "temporary.h"

// FUN_001a4580
void K_View_SetFov(RwCamera* camera, f32 fov)
{
    RwV2d viewWindow;

    viewWindow.y = tanf(DEG_TO_RAD(fov) / 2.0f);
    viewWindow.x = gAspectRatio * viewWindow.y;

    RwCameraSetViewWindow(camera, &viewWindow);
}

// FUN_001a4600
f32 K_View_GetFov(RwCamera* camera)
{
    f32 x;
    RwV2d* viewWindow;

    viewWindow = &camera->viewWindow;

    atanf(viewWindow->x);
    x = atanf(viewWindow->y) * 2.0f;

    return RAD_TO_DEG(x);
}