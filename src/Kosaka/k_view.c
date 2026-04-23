#include "Kosaka/k_view.h"
#include "kwln/kwln.h"
#include "temporary.h"

// FUN_001a4580
void K_View_SetFov(RwCamera* camera, f32 fov)
{
    RwV2d viewWindow;

    viewWindow.y = tanf(DEG_TO_RAD(fov) / 2.0f);
    viewWindow.x = gAspectRatio * viewWindow.y;

    RwCameraSetViewWindow(camera, &viewWindow);
}