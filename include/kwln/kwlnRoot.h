#ifndef KWLNROOT_H
#define KWLNROOT_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;
typedef struct RwCamera RwCamera;
typedef struct RwRGBA RwRGBA;

// 8 bytes
typedef struct KwlnRootWork
{
    u32 state;
    u32 unk_04;
} KwlnRootWork;

void kwlnRootFUN_00198610(u32 flags, u8 enabled);
KwlnTask* kwlnRootCreateRootProcTask();

#endif