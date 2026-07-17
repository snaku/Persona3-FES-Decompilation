#ifndef H_FILESETUP_H
#define H_FILESETUP_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;

// 12 bytes
typedef struct HFileSetupWork
{
    s32 state;          // 0x00
    u32 funcIdx;        // 0x04
    KwlnTask* currTask; // 0x08
} HFileSetupWork;

KwlnTask* H_FileSetup_CreateHonpenTask();
KwlnTask* H_FileSetup_CreateGojitudanTask();

#endif