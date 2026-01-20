#ifndef H_MALLOC_H
#define H_MALLOC_H

#include "Utils.h"

void H_Free(uintptr_t addr);
uintptr_t H_Malloc(u32 size);

#endif