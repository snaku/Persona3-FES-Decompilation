#ifndef RWPLCORE_H
#define RWPLCORE_H

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
    void* (*rwMalloc)(RwUInt32 size, RwUInt32 param_3);
    void  (*rwFree)(void *ptr);
    void* (*rwRealloc)(void *ptr, RwUInt32 newSize, RwUInt32 param_3);
    void* (*rwCalloc)(RwUInt32 elemCount, RwUInt32 elemSize, RwUInt32 param_3);
} RwMemoryFunctions;

#endif