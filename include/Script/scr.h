#ifndef SCR_H
#define SCR_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;

// 252 bytes
typedef struct ScriptData
{
    u8 scrName[24];    // same as scrTask->taskName
    u8 unkData1[0xcc];
    KwlnTask* scrTask; // 0xe4
    u8 unkData2[0x14];
} ScriptData;

#endif