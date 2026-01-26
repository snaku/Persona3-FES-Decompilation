#ifndef K_SHADOW_H
#define K_SHADOW_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;

// 8 bytes
typedef struct
{
    s32 state; // 0x00
    u8 unkData[0x04];
} FieldShadowMap;

KwlnTask* FldShadow_CreateShadowMapTask(KwlnTask* fldSceneDrawTask);

#endif