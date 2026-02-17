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
#define RW_MALLOC(size, param_3)          rwGlobals.memFuncs.Rw_Malloc((size), (param_3))
#define RW_FREE(ptr)                      rwGlobals.memFuncs.Rw_Free((ptr))
#define RW_REALLOC(ptr, newSize, param_3) rwGlobals.memFuncs.Rw_Realloc((ptr), (newSize), (param_3))
#define RW_CALLOC(count, size, param_3)   rwGlobals.memFuncs.Rw_Calloc((count), (size), (param_3))

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

typedef enum
{
    // TODO
    RW_RENDER_STATE_0,
    RW_RENDER_STATE_FOG_ENABLE = 14,
    RW_RENDER_STATE_FOG_COLOR,
    RW_RENDER_STATE_FOG_TYPE,
} RwRenderState;

typedef enum
{
    // TODO
    RW_FOG_TYPE_0,
    RW_FOG_TYPE_1
} RwFogType;

typedef enum
{
    RW_STD_FUNC_CAMERA_END_UPDATE = 10,
    RW_STD_FUNC_CAMERA_CLEAR = 21,
    RW_STD_FUNC_MAX = 29
} RwStdFunc;

typedef RwBool (*RwStandardFunc)(void* out, void* inOut, RwInt32 nI);

// See enmu 'RwRenderState'
typedef RwBool (*RwRenderState_SetFunc)(RwRenderState renderState, void* val);
typedef RwBool (*RwRenderState_GetFunc)(RwRenderState renderState, void* val);

// 56 bytes
typedef struct RwDevice
{
    u8 unkData1[0x10];
    RwRenderState_SetFunc setRenderState; // 0x10
    RwRenderState_GetFunc getRenderState; // 0x14
    u8 unkData2[0x20];
} RwDevice;

// 16 bytes
typedef struct RwMemoryFunctions
{
    void* (*Rw_Malloc)(RwUInt32 size, RwUInt32 param_3);
    void  (*Rw_Free)(void* ptr);
    void* (*Rw_Realloc)(void* ptr, RwUInt32 newSize, RwUInt32 param_3);
    void* (*Rw_Calloc)(RwUInt32 elemCount, RwUInt32 elemSize, RwUInt32 param_3);
} RwMemoryFunctions;

// 300 bytes
typedef struct
{
    void* currCamera;                        // 0x00
    void* currWorld;                         // 0x04
    u8 unkData1[0x08];
    RwDevice device;                         // 0x10
    RwStandardFunc stdFunc[RW_STD_FUNC_MAX]; // 0x48
    u8 unkData2[0x4c];
    RwMemoryFunctions memFuncs;              // 0x108
    u8 unkData3[0x10];
    RwUInt32 resArenaSize;                   // 0x128
} RwGlobals;

extern RwGlobals rwGlobals; // not sure where to place this

RwUInt32 RwEngine_GetVersion();
RwBool RwEngine_Init(const RwMemoryFunctions* memFuncs, RwUInt32 flags, RwUInt32 resArenaSize);

#endif