#ifndef RWCORE_H
#define RWCORE_H

#include "rw/rwplcore.h"

struct RwCamera;

typedef struct RwCamera* (*RwCameraBeginUpdateFunc)(struct RwCamera* camera);
typedef struct RwCamera* (*RwCameraEndUpdateFunc)(struct RwCamera* camera);

// TODO
typedef struct RwCamera
{
    u8 unkData1[0x18];
    RwCameraBeginUpdateFunc beginUpdate; // 0x18
    RwCameraEndUpdateFunc endUpdate;     // 0x1c
} RwCamera;

RwCamera* RwCamera_BeginUpdate(RwCamera* camera);
RwCamera* RwCamera_EndUpdate(RwCamera* camera);

#endif