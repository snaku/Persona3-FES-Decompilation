#ifndef K_CLUMP_H
#define K_CLUMP_H

#include "Utils.h"

typedef struct RpMaterial RpMaterial;

s32 K_Clump_MatUsrDataGetInt(const RpMaterial* material, const char* name);
u32 K_Clump_MatUsrDataHasData(const RpMaterial* material, const char* name);

#endif