#ifndef RWCORE_H
#define RWCORE_H

#include "rw/rwplcore.h"

struct RwCamera;

typedef struct RwCamera* (*RwCameraBeginUpdateFunc)(struct RwCamera* camera);
typedef struct RwCamera* (*RwCameraEndUpdateFunc)(struct RwCamera* camera);

typedef enum
{
    RW_PROJ_TYPE_0,
    RW_PROJ_TYPE_PERSPECTIVE
} RwCameraProjectionType;

// TODO
typedef struct RwCamera
{
    u8 unkData1[0x14];
    RwCameraProjectionType projType;      // 0x14
    RwCameraBeginUpdateFunc beginUpdate; // 0x18
    RwCameraEndUpdateFunc endUpdate;     // 0x1c
} RwCamera;

typedef enum
{
    // TODO: names
    RW_CAMERA_CLEAR_MODE_0,
    RW_CAMERA_CLEAR_MODE_1,
    RW_CAMERA_CLEAR_MODE_ZBUFFER // clear Z buffer
} RwCameraClearMode;

RwCamera* RwCameraBeginUpdate(RwCamera* camera);
RwCamera* RwCameraEndUpdate(RwCamera* camera);
RwCamera* RwCameraClear(RwCamera* camera, RwRGBA* colors, RwCameraClearMode clearMode);
RwCamera* RwCameraSetProjectionType(RwCamera* camera, RwCameraProjectionType projType);

#endif