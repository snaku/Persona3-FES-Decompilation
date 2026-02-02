#include "temporary.h"

const f32 PI = 3.141592f;
GlobalCtx ctx;

// FUN_00521250
void* P3FES_Memcpy(void* dst, void* src, u32 size)
{
    // TODO

    return dst;
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