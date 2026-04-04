#ifndef K_SHADOW_H
#define K_SHADOW_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;

// 8 bytes
typedef struct FldShadowMap
{
    s32 state; // 0x00
    u8 unkData[0x04];
} FldShadowMap;

KwlnTask* K_FldShadow_CreateShadowMapTask(KwlnTask* fldSceneDrawTask);

#endif