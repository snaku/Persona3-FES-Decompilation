#ifndef K_VIEW_H
#define K_VIEW_H

#include "Utils.h"

typedef struct RwCamera RwCamera;

void K_View_SetFov(RwCamera* camera, f32 fov);
f32 K_View_GetFov(RwCamera* camera);

#endif