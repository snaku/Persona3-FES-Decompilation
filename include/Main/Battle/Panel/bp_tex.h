#ifndef BP_TEX_H
#define BP_TEX_H

#include "Utils.h"

typedef struct RwRaster RwRaster;

void* bpTexCreateSpr(void* sprMemory);
void bpTexDestroySpr(void* spr);

RwRaster* bpTexCreateTmxRaster(void* tmxMemory);

#endif