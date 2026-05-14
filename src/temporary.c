#include "temporary.h"

// FUN_00521250
void* memcpy(void* dst, const void* src, u32 size)
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

// FUN_005225a8
int printf(const char* fmt, ...)
{

}

// FUN_00523ac8
int sprintf(char* buffer, const char* fmt, ...)
{
    // TODO
}

// FUN_00523e68
char* strcat(char* str1, char* str2)
{
    return str1;
}

// FUN_00524128
int strcmp(const char* str1, const char* str2)
{
    // TODO

    return 0;
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

// FUN_0052e408
float atanf(float x)
{
    return 0.0f;
}

// FUN_0052e6d8
float cosf(float x)
{
    return 0.0f;
}

// FUN_0052e878
float sinf(float x)
{
    return 0.0f;
}

// FUN_0052e930
float tanf(float x)
{
    return 0.0f;
}