#ifndef K_MISC_H
#define K_MISC_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;
typedef struct Model Model;

typedef enum
{
    DELAYMDLFREE_STATE_WAITSTREAM,
    DELAYMDLFREE_STATE_DESTROYING
} DelayMdlFreeState;

// 8 bytes
typedef struct DelayMdlFreeWork
{
    u32 state;           // 0x00
    Model* mdlToDestroy; // 0x04
} DelayMdlFreeWork;

// 4 bytes
typedef struct ScrShutdownWork
{
    KwlnTask* scrTask; // 0x00
} ScrShutdownWork;

KwlnTask* K_Misc_CreateDelayMdlFreeTask(Model* mdlToDestroy);
KwlnTask* K_Misc_CreateScrShutdownTask(KwlnTask* scrTask);

#endif