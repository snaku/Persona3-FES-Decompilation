#ifndef RWCORE_H
#define RWCORE_H

#include "rw/rwplcore.h"

typedef struct RwObjectHasFrame RwObjectHasFrame;

typedef RwObjectHasFrame* (*RwObjectHasFrameSyncFunction)(RwObjectHasFrame* object);

// 20 bytes
struct RwObjectHasFrame
{
    RwObject object;                   // 0x00
    RwLLLink lFrame;                   // 0x08
    RwObjectHasFrameSyncFunction sync; // 0x10
};

typedef struct RwRaster RwRaster;

// 52 bytes
struct RwRaster
{
    RwRaster* parent;        // 0x00
    RwUInt8* cpPixels;       // 0x04
    RwUInt8* palette;        // 0x08
    RwInt32 width;           // 0x0c
    RwInt32 height;          // 0x10
    RwInt32 depth;           // 0x14
    RwInt32 stride;          // 0x18
    RwInt16 nOffsetX;        // 0x1c
    RwInt16 nOffsetY;        // 0x1e
    RwUInt8 cType;           // 0x20
    RwUInt8 cFlags;          // 0x21
    RwUInt8 privateFlags;    // 0x22
    RwUInt8 cFormat;         // 0x23
    RwUInt8* originalPixels; // 0x24
    RwInt32 originalWith;    // 0x28
    RwInt32 originalHeight;  // 0x2c
    RwInt32 originalStride;  // 0x30
};

#define rwFRAME 0
typedef struct RwFrame RwFrame;

// 160 bytes
struct RwFrame
{
    RwObject object;          // 0x00
    RwLLLink inDirtyListLink; // 0x08
    RwMatrix modelling;       // 0x10
    RwMatrix ltm;             // 0x50
    RwLinkList objectList;    // 0x90
    RwFrame* child;           // 0x98
    RwFrame* next;            // 0x9c
    RwFrame* root;            // 0xa0
};

#define rwCAMERA 4

struct RwCamera;

typedef struct RwCamera* (*RwCameraBeginUpdateFunc)(struct RwCamera* camera);
typedef struct RwCamera* (*RwCameraEndUpdateFunc)(struct RwCamera* camera);

typedef enum
{
    rwPROJECTION0,
    rwPERSPECTIVE
} RwCameraProjection;

// TODO
typedef struct RwCamera
{
    RwObjectHasFrame object;             // 0x00
    RwCameraProjection projType;         // 0x14
    RwCameraBeginUpdateFunc beginUpdate; // 0x18
    RwCameraEndUpdateFunc endUpdate;     // 0x1c
    RwMatrix viewMatrix;                 // 0x20
    RwRaster* frameBuffer;               // 0x60
    RwRaster* zBuffer;                   // 0x64
} RwCamera;

typedef enum
{
    // TODO: names
    rwCAMERACLEAR0,
    rwCAMERACLEAR1,
    rwCAMERACLEARZ  // clear Z buffer
} RwCameraClearMode;

RwCamera* RwCameraBeginUpdate(RwCamera* camera);
RwCamera* RwCameraEndUpdate(RwCamera* camera);
RwCamera* RwCameraClear(RwCamera* camera, RwRGBA* colors, RwCameraClearMode clearMode);
RwCamera* RwCameraSetProjectionType(RwCamera* camera, RwCameraProjection projType);

#endif