#ifndef RWCORE_H
#define RWCORE_H

#include "rw/rwplcore.h"
#include "sce/eetypes.h"

// 4 bytes
typedef union
{
    RwRGBA preLitColor;
    RwRGBA color;
} RxColorUnion;

// 36 bytes
typedef struct RxObjSpace3DVertex
{
    RwV3d objVertex; // 0x00
    RxColorUnion c;  // 0x0c
    RwV3d objNormal; // 0x10
    RwReal u;        // 0x1c
    RwReal v;        // 0x20
} RxObjSpace3DVertex;

typedef RxObjSpace3DVertex RxObjSpace3DLitVertex;
typedef RxObjSpace3DLitVertex RwIm3DVertex;

#define RxV3dAssign(_target, _source) (*(_target) = *(_source))

#define RxObjSpace3DVertexSetPos(_vert, _pos) RxV3dAssign(&(_vert)->objVertex, _pos)

#define RwIm3DVertexSetPos(_vert, _imx, _imy, _imz) \
    do                                              \
    {                                               \
        RwV3d _packed;                              \
        _packed.x = _imx;                           \
        _packed.y = _imy;                           \
        _packed.z = _imz;                           \
        RxObjSpace3DVertexSetPos(_vert, &_packed);  \
    } while (0)
    
#define RwIm3DVertexSetRGBA(_vert, _r, _g, _b, _a) \
    do                                             \
    {                                              \
        RwRGBA * const _col = &(_vert)->c.color;   \
        _col->r = (_r);                            \
        _col->g = (_g);                            \
        _col->b = (_b);                            \
        _col->a = (_a);                            \
    } while(0)                                     \

typedef enum
{
    rwIM3D_VERTEXUV = 1,
    rwIM3D_ALLOPAQUE = 2,
    rwIM3D_NOCLIP = 4,
    rwIM3D_VERTEXXYZ = 8,
    rwIM3D_VERTEXRGBA = 16
} RwIm3DTransformFlags;



typedef struct RwObjectHasFrame RwObjectHasFrame;

typedef RwObjectHasFrame* (*RwObjectHasFrameSyncFunction)(RwObjectHasFrame* object);

// 20 bytes
struct RwObjectHasFrame
{
    RwObject object;                   // 0x00
    RwLLLink lFrame;                   // 0x08
    RwObjectHasFrameSyncFunction sync; // 0x10
};


typedef enum
{
    rwRASTERTYPENORMAL = 0x00,
    rwRASTERTYPEZBUFFER = 0x01,
    rwRASTERTYPECAMERA = 0x02,
    rwRASTERTYPETEXTURE = 0x04,
    rwRASTERTYPECAMERATEXTURE = 0x05,
    rwRASTERTYPEMASK = 0x07,

    rwRASTERPALETTEVOLATILE = 0x40,
    rwRASTERDONTALLOCATE = 0x80
} RwRasterType;

typedef enum
{
    rwRASTERFORMATDEFAULT = 0x0000,

    rwRASTERFORMAT1555 = 0x0100,
    rwRASTERFORMAT565 = 0x0200,
    rwRASTERFORMAT4444 = 0x0300,
    rwRASTERFORMATLUM8 = 0x0400,
    rwRASTERFORMAT8888 = 0x0500,
    rwRASTERFORMAT888 = 0x0600,
    rwRASTERFORMAT16 = 0x0700,
    rwRASTERFORMAT24 = 0x0800,
    rwRASTERFORMAT32 = 0x0900,
    rwRASTERFORMAT555 = 0x0a00,

    rwRASTERFORMATAUTOMIPMAP = 0x1000,

    rwRASTERFORMATPAL8 = 0x2000,
    rwRASTERFORMATPAL4 = 0x4000,

    rwRASTERFORMATMIPMAP = 0x8000,  /**<Mip mapping on */

    rwRASTERFORMATPIXELFORMATMASK = 0x0f00,
    rwRASTERFORMATMASK = 0xff00
} RwRasterFormat;

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
    RwInt32 originalWidth;    // 0x28
    RwInt32 originalHeight;  // 0x2c
    RwInt32 originalStride;  // 0x30
};

// 28 bytes
typedef struct RwImage
{
    RwInt32 flags;     // 0x00
    RwInt32 width;     // 0x04
    RwInt32 height;    // 0x08
    RwInt32 depth;     // 0x0c
    RwInt32 stride;    // 0x10
    RwUInt8* cpPixels; // 0x14
    RwRGBA* palette;   // 0x18
} RwImage;

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



typedef enum
{
    rpSKYRENDERSTATENARENDERSTATE = 0,
    rpSKYRENDERSTATEDITHER,
    rpSKYRENDERSTATEALPHA_1,
    rpSKYRENDERSTATEATEST_1,
    rpSKYRENDERSTATEFARFOGPLANE,
    rpSKYRENDERSTATEMAXMIPLEVELS
} RpSkyRenderState;



#define rwCAMERA 4

typedef struct RwCamera RwCamera;

#define RwCameraGetCurrentCamera() (rwGlobals.currCamera)

typedef struct RwCamera* (*RwCameraBeginUpdateFunc)(struct RwCamera* camera);
typedef struct RwCamera* (*RwCameraEndUpdateFunc)(struct RwCamera* camera);

typedef enum
{
    rwPROJECTION0,
    rwPERSPECTIVE
} RwCameraProjection;

// TODO
struct RwCamera
{
    RwObjectHasFrame object;             // 0x00
    RwCameraProjection projType;         // 0x14
    RwCameraBeginUpdateFunc beginUpdate; // 0x18
    RwCameraEndUpdateFunc endUpdate;     // 0x1c
    RwMatrix viewMatrix;                 // 0x20
    RwRaster* frameBuffer;               // 0x60
    RwRaster* zBuffer;                   // 0x64
    RwV2d viewWindow;                    // 0x68
    RwV2d recipViewWindow;               // 0x70
    RwV2d viewOffset;                    // 0x78
    RwReal nearPlane;                    // 0x80
    RwReal farPlane;                     // 0x84
    RwReal fogPlane;                     // 0x88
    RwReal zScale;                       // 0x8c
    RwReal zShift;                       // 0x90
};

typedef enum
{
    // TODO: names
    rwCAMERACLEAR0,
    rwCAMERACLEAR1,
    rwCAMERACLEARZ  // clear Z buffer
} RwCameraClearMode;

typedef enum
{
    rwSPHEREOUTSIDE,
    rwSPHEREBOUNDARY,
    rwSPHEREINSIDE,
} RwFrustumTestResult;

RwBool RwImageDestroy(RwImage* image);
RwImage* RwImageRead(const RwChar* imageName);

RwRaster* RwRasterCreate(RwInt32 width, RwInt32 height, RwInt32 depth, RwInt32 flags);;
RwRaster* RwRasterSetFromImage(RwRaster* raster, RwImage* image);

RwFrame* RwFrameTransform(RwFrame* frame, const RwMatrix* m, RwOpCombineType combine);
RwMatrix* RwFrameGetLTM(RwFrame* frame);

RwCamera* RwCameraBeginUpdate(RwCamera* camera);
RwCamera* RwCameraEndUpdate(RwCamera* camera);
RwCamera* RwCameraClear(RwCamera* camera, RwRGBA* colors, RwCameraClearMode clearMode);
RwFrustumTestResult RwCameraFrustumTestSphere(const RwCamera* camera, const RwSphere* sphere);
RwCamera* RwCameraSetProjectionType(RwCamera* camera, RwCameraProjection projType);
RwCamera* RwCameraSetViewWindow(RwCamera* camera, const RwV2d* viewWindow);

RwBool RpSkyRenderStateSet(RpSkyRenderState nState, void *pParam);

void RwIm3DTransform(RwIm3DVertex* pVerts, RwUInt32 numVerts, RwMatrix* ltm, RwUInt32 flags);
RwBool RwIm3DRenderLine(RwInt32 vert1, RwInt32 vert2);

#endif