#include "rw/rwplcore.h"

// 00960070
RwGlobals rwGlobals;

// FUN_004ca510
RwUInt32 RwEngine_GetVersion()
{
    return RW_LIB_VERSION;
}

// FUN_004ca850
RwBool RwEngine_Init(const RwMemoryFunctions* memFuncs, RwUInt32 flags, RwUInt32 resArenaSize)
{
    // TODO

    return true;
}