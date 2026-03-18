#include "temporary.h"

const f32 PI = 3.141592f;

// FUN_00521250
void* memcpy(void* dst, void* src, u32 size)
{
    // TODO

    return dst;
}

// FUN_00521408
void* memset(void* dst, u8 value, u32 size)
{
    // TODO

    for (u32 i = 0; i < size; i++)
    {
        ((u8*)dst)[i] = value;
    }

    return dst;
}

// FUN_00523ac8
void sprintf(char* buffer, const char* fmt, ...)
{
    // TODO
}

// FUN_00524270
char* strcpy(char* dst, const char* src)
{
    // TODO

    return dst;
}

// FUN_00524388
size_t strlen(const char* str)
{
    // TODO

    return 0;
}