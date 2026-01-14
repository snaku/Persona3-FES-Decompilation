#ifndef SCR_H
#define SCR_H

#include "Utils.h"

#define SCR_MAX_ARGS 28

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

typedef struct
{
    u8 unkData1[0x08];
    u8 magic[4];       // "FLW0"
    // other unkdata after
} ScrHeader;

// 252 bytes. Data of a function
typedef struct ProcedureData
{
    u8 prcdName[24];                   // same as prcdTask->taskName
    u32 unk_18;
    u32 argCount;                      // 0x1c
    u8 argTypes[SCR_MAX_ARGS];         // 0x20. See enum 'ScrTypes'
    ScrValues argValues[SCR_MAX_ARGS]; // 0x3c
    ScrHeader* scrHeader;              // 0xac
    u8 unkData1[0x7c];
    KwlnTask* prcdTask;                // 0xe4
    u8 unkData2[0x14];
} ProcedureData;

#endif