#include "type.h"

// FUN_00521408
void* memset(void* dst, u8 value, u32 size)
{
    // TODO
    u32 i;

    for (i = 0; i < size; i++)
    {
        ((u8*)dst)[i] = value;
    }

    return dst;
}
