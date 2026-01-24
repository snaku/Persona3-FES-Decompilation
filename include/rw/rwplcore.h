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

typedef struct RwMemoryFunctions
{
    void* (*Rw_Malloc)(RwUInt32 size, RwUInt32 param_3);
    void  (*Rw_Free)(void* ptr);
    void* (*Rw_Realloc)(void* ptr, RwUInt32 newSize, RwUInt32 param_3);
    void* (*Rw_Calloc)(RwUInt32 elemCount, RwUInt32 elemSize, RwUInt32 param_3);
} RwMemoryFunctions;

typedef struct
{
    u8 unkData1[0x108];
    RwMemoryFunctions memFuncs; // 0x108
} RwGlobals;

extern RwGlobals rwGlobals; // not sure where to place this

#endif