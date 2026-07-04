#ifndef GM_ROOT_H
#define GM_ROOT_H

#include "Utils.h"

#define GMROOT_FLAG_ACTIVE (1 << 0) // 0x01

typedef struct KwlnTask KwlnTask;

// 44 bytes
typedef struct GmRootWork
{
    u32 flags;                // 0x00
    s32 unk_04;               // 0x04
    KwlnTask* task;           // 0x08
    u8 unkData[0x1c];
    KwlnTask* chkMemcardTask; // 0x28
} GmRootWork;

KwlnTask* gmRootCreateTask(KwlnTask* parent);

#endif