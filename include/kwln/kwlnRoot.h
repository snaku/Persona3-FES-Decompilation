#ifndef KWLNROOT_H
#define KWLNROOT_H

#include "Utils.h"

// 8 bytes
typedef struct KwlnRoot
{
    u32 state;
    u32 unk_04;
} KwlnRoot;

RwCamera* KwlnRoot_GetMainCamera();
KwlnTask* KwlnRoot_CreateRootProcTask();

#endif