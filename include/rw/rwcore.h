#ifndef RWCORE_H
#define RWCORE_H

#include "rw/rwplcore.h"

struct RwCamera;

typedef struct RwCamera* (*RwCamera_BeginUpdateFunc)(struct RwCamera* camera);
typedef struct RwCamera* (*RwCamera_EndUpdateFunc)(struct RwCamera* camera);

// TODO
typedef struct RwCamera
{
    u8 unkData1[0x18];
    RwCamera_BeginUpdateFunc beginUpdate; // 0x18
    RwCamera_EndUpdateFunc endUpdate;     // 0x1c
} RwCamera;

typedef enum
{
    // TODO: names
    RW_CAMERA_CLEAR_MODE_0,
    RW_CAMERA_CLEAR_MODE_1,
    RW_CAMERA_CLEAR_MODE_ZBUFFER // clear Z buffer
} RwCameraClearMode;

RwCamera* RwCamera_BeginUpdate(RwCamera* camera);
RwCamera* RwCamera_EndUpdate(RwCamera* camera);
RwCamera* RwCamera_Clear(RwCamera* camera, RwRGBA* colors, RwCameraClearMode clearMode);

#endif