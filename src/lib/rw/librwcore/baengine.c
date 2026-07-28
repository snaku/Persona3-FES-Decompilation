#include "rw/rwplcore.h"

// 00960070
RwGlobals rwGlobals;

// FUN_004ca510
RwUInt32 RwEngineGetVersion()
{
    return RW_LIB_VERSION;
}

// FUN_004ca850
RwBool RwEngineInit(const RwMemoryFunctions* memFuncs, RwUInt32 flags, RwUInt32 resArenaSize)
{
    // TODO

    return true;
}
