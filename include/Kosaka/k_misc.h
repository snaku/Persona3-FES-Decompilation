#ifndef K_MISC_H
#define K_MISC_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;

// 4 bytes
typedef struct ScrShutdownWork
{
    KwlnTask* scrTask; // 0x00
} ScrShutdownWork;

KwlnTask* K_Misc_CreateScrShutdownTask(KwlnTask* scrTask);

#endif