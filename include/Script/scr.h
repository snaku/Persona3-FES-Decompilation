#ifndef SCR_H
#define SCR_H

#include "Utils.h"

#define SCR_MAX_ARGS 26

typedef struct KwlnTask KwlnTask;

typedef enum
{
    SCR_TYPE_INT,
    SCR_TYPE_FLOAT
} ScrTypes;

typedef union 
{
    s32 iVal;
    f32 fVal;
} ScrValues;

// 252 bytes
typedef struct ScriptData
{
    u8 scrName[24];                    // same as scrTask->taskName
    u32 unk_18;
    u32 argCount;                      // 0x1c
    u8 argTypes[SCR_MAX_ARGS];         // 0x20. See enum 'ScrTypes'
    ScrValues argValues[SCR_MAX_ARGS]; // 0x3c
    u8 unkData1[0x7c];
    KwlnTask* scrTask;                 // 0xe4
    u8 unkData2[0x14];
} ScriptData;

#endif