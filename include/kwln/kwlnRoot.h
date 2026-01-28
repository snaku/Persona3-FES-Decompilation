#ifndef KWLNROOT_H
#define KWLNROOT_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;
typedef struct RwCamera RwCamera;
typedef struct RwRGBA RwRGBA;

// 8 bytes
typedef struct KwlnRoot
{
    u32 state;
    u32 unk_04;
} KwlnRoot;

RwCamera* KwlnRoot_GetMainCamera();
RwRGBA* KwlnRoot_GetClearColor();
void KwlnRoot_SetClearColor(u8 r, u8 g, u8 b, u8 a);
KwlnTask* KwlnRoot_CreateRootProcTask();

#endif