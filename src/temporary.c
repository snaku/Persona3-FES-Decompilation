#include "temporary.h"

#include <stdlib.h>

// FUN_001bff20
u32 GlobalCtx_GetCurrentTartarusFloor()
{
    if (ctx.unkStruct1 == NULL)
    {
        return 0;
    }

    return ctx.unkStruct1->tartarus->currFloor;
}

// FUN_00521408
void* P3FES_Memset(void* dst, u8 value, u32 size)
{
    // TODO

    for (u32 i = 0; i < size; i++)
    {
        ((u8*)dst)[i] = value;
    }

    return dst;
}