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

// pack RGBA components into an unsigned int
#define PACK_RWRGBA(r,g,b,a) ((RwUInt32)(((a) << 24) | ((r) << 16) | ((g) << 8) | (b)))

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

// 16 bytes
typedef struct RwMemoryFunctions
{
    void* (*Rw_Malloc)(RwUInt32 size, RwUInt32 param_3);
    void  (*Rw_Free)(void* ptr);
    void* (*Rw_Realloc)(void* ptr, RwUInt32 newSize, RwUInt32 param_3);
    void* (*Rw_Calloc)(RwUInt32 elemCount, RwUInt32 elemSize, RwUInt32 param_3);
} RwMemoryFunctions;

// 308 bytes
typedef struct
{
    u8 unkData1[0x108];
    RwMemoryFunctions memFuncs; // 0x108
    u8 unkData2[0x18];
    RwUInt32 resArenaSize;      // 0x130
} RwGlobals;

extern RwGlobals rwGlobals; // not sure where to place this

RwBool RwEngine_Init(const RwMemoryFunctions* memFuncs, RwUInt32 flags, RwUInt32 resArenaSize);

#endif