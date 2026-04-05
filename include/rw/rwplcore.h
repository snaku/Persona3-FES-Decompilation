#ifndef RWPLCORE_H
#define RWPLCORE_H

#include "Utils.h"

// RENDERWARE TYPES
typedef int RwFixed;
typedef int RwInt32;
typedef unsigned int RwUInt32;
typedef short RwInt16;
typedef unsigned short RwUInt16;
typedef unsigned char RwUInt8;
typedef signed char RwInt8;
typedef char RwChar;
typedef long RwInt64;
typedef unsigned long RwUInt64;
typedef float RwReal;
typedef RwInt32 RwBool;

// persona 3 uses renderware 3.7.0.2
#define RW_LIB_VERSION 0x37002

// pack RGBA components into an unsigned int (ARGB)
#define PACK_RWRGBA(r,g,b,a) ((RwUInt32)(((a) << 24) | ((r) << 16) | ((g) << 8) | (b)))

// current camera and world
#define RW_CURRCAMERA rwGlobals.currCamera
#define RW_CURRWORLD  rwGlobals.currWorld

// macros to call 'RwGlobals' func ptr
// memFuncs
#define RW_MALLOC(size, param_3)          rwGlobals.memFuncs.RwMalloc((size), (param_3))
#define RW_FREE(ptr)                      rwGlobals.memFuncs.RwFree((ptr))
#define RW_REALLOC(ptr, newSize, param_3) rwGlobals.memFuncs.RwRealloc((ptr), (newSize), (param_3))
#define RW_CALLOC(count, size, param_3)   rwGlobals.memFuncs.RwCalloc((count), (size), (param_3))

// device
#define RWRENDERSTATE_SET(state, val) rwGlobals.device.setRenderState((state), (void*)(val))
#define RWRENDERSTATE_GET(state, val) rwGlobals.device.getRenderState((state), (void*)(val))

// std func
#define RWSTDFUNC(type) (rwGlobals.stdFunc[(type)])

// 4 bytes. Values from 0 to 255
typedef struct RwRGBA
{
    RwUInt8 r;
    RwUInt8 g;
    RwUInt8 b;
    RwUInt8 a;
} RwRGBA;

// 16 bytes. Values from 0.0f to 1.0f
typedef struct RwRGBAReal
{
    RwReal r;
    RwReal g;
    RwReal b;
    RwReal a;
} RwRGBAReal;

// 8 bytes
typedef struct RwV2d
{
    RwReal x; // 0x00
    RwReal y; // 0x04
} RwV2d;

// 12 bytes
typedef struct RwV3d
{
    RwReal x; // 0x00
    RwReal y; // 0x04
    RwReal z; // 0x08
} RwV3d;

// 16 bytes
typedef struct RwV4dTag
{
    RwReal x; // 0x00
    RwReal y; // 0x04
    RwReal z; // 0x08
    RwReal w; // 0x0c
} RwV4d;

typedef enum
{
    rwMATRIXTYPENORMAL = 0x00000001,
    rwMATRIXTYPEORTHOGONAL = 0x00000002,
    rwMATRIXTYPEORTHONORMAL = 0x00000003,
    rwMATRIXTYPEMASK = 0x00000003
} RwMatrixType;

typedef enum
{
    rwMATRIXINTERNALIDENTITY = 0x00020000
} RwMatrixFlag;

// 64 bytes
typedef struct RwMatrixTag
{
    RwV3d right;    // 0x00
    RwUInt32 flags; // 0x0c

    RwV3d up;       // 0x10
    RwUInt32 pad1;  // 0x1c

    RwV3d at;       // 0x20
    RwUInt32 pad2;  // 0x2c
    
    RwV3d pos;      // 0x30
    RwUInt32 pad3;  // 0x3c
} RwMatrix;

typedef enum
{
    rwCOMBINEREPLACE = 0,
    rwCOMBINEPRECONCAT,
    rwCOMBINEPOSTCONCAT,
} RwOpCombineType;

#define rwMatrixSetFlags(m, flagsbit) ((m)->flags = (flagsbit))
#define rwMatrixGetFlags(m)           ((m)->flags)

#define RwMatrixSetIdentity(m)                                  \
do                                                              \
{                                                               \
    (m)->right.x = (m)->up.y    = (m)->at.z  = (RwReal)((1.0)); \
    (m)->right.y = (m)->right.z = (m)->up.x  = (RwReal)((0.0)); \
    (m)->up.z    = (m)->at.x    = (m)->at.y  = (RwReal)((0.0)); \
    (m)->pos.x   = (m)->pos.y   = (m)->pos.z = (RwReal)((0.0)); \
    rwMatrixSetFlags((m),                                       \
                     rwMatrixGetFlags(m) |                      \
                     (rwMATRIXINTERNALIDENTITY |                \
                      rwMATRIXTYPEORTHONORMAL));                \
} while(0)

#define RwMatrixMultiplyVUMacro(_matrix, _matrixIn1, _matrixIn2)    \
do                                                                  \
{                                                                   \
    int __tmp1, __tmp2;                                             \
                                                                    \
    asm __volatile__ (".set noreorder ;                             \
        lqc2        vf1,  0x00(%2) ;                                \
        lqc2        vf2,  0x10(%2) ;                                \
        lqc2        vf3,  0x20(%2) ;                                \
        lqc2        vf4,  0x30(%2) ;                                \
        lwu         %0,   0x0C(%2) ;                                \
        lqc2        vf5,  0x00(%3) ;                                \
        lqc2        vf6,  0x10(%3) ;                                \
        lqc2        vf7,  0x20(%3) ;                                \
        lqc2        vf8,  0x30(%3) ;                                \
        lwu         %1,   0x0C(%3) ;                                \
        vmulax.xyz  ACC,  vf5, vf1 ;                                \
        vmadday.xyz ACC,  vf6, vf1 ;                                \
        vmaddz.xyz  vf9,  vf7, vf1 ;                                \
        vmulax.xyz  ACC,  vf5, vf2 ;                                \
        vmadday.xyz ACC,  vf6, vf2 ;                                \
        vmaddz.xyz  vf10, vf7, vf2 ;                                \
        vmulax.xyz  ACC,  vf5, vf3 ;                                \
        vmadday.xyz ACC,  vf6, vf3 ;                                \
        vmaddz.xyz  vf11, vf7, vf3 ;                                \
        vmulax.xyz  ACC,  vf5, vf4 ;                                \
        vmadday.xyz ACC,  vf6, vf4 ;                                \
        vmaddaz.xyz ACC,  vf7, vf4 ;                                \
        vmaddw.xyz  vf12, vf8, vf0 ;                                \
        and         %1, %1, %0     ;                                \
        sqc2        vf9,  0x00(%4) ;                                \
        sqc2        vf10, 0x10(%4) ;                                \
        sqc2        vf11, 0x20(%4) ;                                \
        sqc2        vf12, 0x30(%4) ;                                \
        sw          %1, 0x0C(%4)   ;                                \
        .set reorder "                                              \
         : "=r&" (__tmp1), "=r&" (__tmp2) : "r" (_matrixIn1),       \
           "r" (_matrixIn2), "r" (_matrix) : "cc",  "memory");      \
} while(0)

typedef struct RwLLLink RwLLLink;

// 8 bytes
struct RwLLLink
{
    RwLLLink* next; // 0x00
    RwLLLink* prev; // 0x04
};

// 8 bytes
typedef struct RwLinkList
{
    RwLLLink link; // 0x00
} RwLinkList;

// 8 bytes
typedef struct RwObject
{
    RwUInt8 type;         // 0x00
    RwUInt8 subType;      // 0x01
    RwUInt8 flags;        // 0x02
    RwUInt8 privateFlags; // 0x03
    void* parent;         // 0x04
} RwObject;

typedef struct RwStream RwStream; // TODO

typedef enum
{
    // TODO
    rwRENDERSTATE0,
    rwRENDERSTATEFOGENABLE = 14,
    rwRENDERSTATEFOGCOLOR,
    rwRENDERSTATEFOGTYPE,
} RwRenderState;

typedef enum
{
    // TODO
    rwFOGTYPE0,
    rwFOGTYPE1
} RwFogType;

typedef enum
{
    rwSTANDARDCAMERAENDUPDATE = 10,
    rwSTANDARDCAMERACLEAR = 21,
    rwSTANDARDMAX = 29
} RwStdFunc;

typedef RwBool (*RwStandardFunc)(void* out, void* inOut, RwInt32 nI);

// See enmu 'RwRenderState'
typedef RwBool (*RwRenderStateSetFunc)(RwRenderState renderState, void* val);
typedef RwBool (*RwRenderStateGetFunc)(RwRenderState renderState, void* val);

// 56 bytes
typedef struct RwDevice
{
    u8 unkData1[0x10];
    RwRenderStateSetFunc setRenderState; // 0x10
    RwRenderStateGetFunc getRenderState; // 0x14
    u8 unkData2[0x20];
} RwDevice;

// 16 bytes
typedef struct RwMemoryFunctions
{
    void* (*RwMalloc)(RwUInt32 size, RwUInt32 param_3);
    void  (*RwFree)(void* ptr);
    void* (*RwRealloc)(void* ptr, RwUInt32 newSize, RwUInt32 param_3);
    void* (*RwCalloc)(RwUInt32 elemCount, RwUInt32 elemSize, RwUInt32 param_3);
} RwMemoryFunctions;

// 300 bytes
typedef struct
{
    void* currCamera;                      // 0x00
    void* currWorld;                       // 0x04
    u8 unkData1[0x08];
    RwDevice device;                       // 0x10
    RwStandardFunc stdFunc[rwSTANDARDMAX]; // 0x48
    u8 unkData2[0x4c];
    RwMemoryFunctions memFuncs;            // 0x108
    u8 unkData3[0x10];
    RwUInt32 resArenaSize;                 // 0x128
} RwGlobals;

extern RwGlobals rwGlobals; // not sure where to place this

RwMatrix* RwMatrixMultiply(RwMatrix* matrixOut, const RwMatrix* matrixIn1, const RwMatrix* matrixIn2);
RwMatrix* RwMatrixRotate(RwMatrix* matrix, const RwV3d* axis, RwReal angle, RwOpCombineType combineOp);
RwMatrix* RwMatrixTranslate(RwMatrix* matrix, const RwV3d* translation, RwOpCombineType combineOp);

RwReal RwV3dNormalize(RwV3d* out, const RwV3d* in);
RwReal RwV3dLength(const RwV3d* in);
RwReal RwV2dLength(const RwV2d* in);

RwUInt32 RwEngineGetVersion();
RwBool RwEngineInit(const RwMemoryFunctions* memFuncs, RwUInt32 flags, RwUInt32 resArenaSize);

#endif