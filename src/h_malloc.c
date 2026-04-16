#include "h_malloc.h"
#include "temporary.h"

// FUN_00191a10
void H_Free(void* memory)
{
    // TODO
}

// FUN_00191af0
void* H_Malloc(size_t size)
{
    // TODO

    return NULL;
}

// FUN_00191d10
void* H_Calloc(u32 count, size_t size)
{
    void* memory;

    memory = H_Malloc(size * count);
    memset(memory, 0, size * count);

    return memory;
}