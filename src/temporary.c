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