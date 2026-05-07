#ifndef SCRTRACECODE_H
#define SCRTRACECODE_H

#include "Utils.h"

typedef struct ScrData ScrData;

typedef enum
{
    CODEFUNC_STOP,      // stop script
    CODEFUNC_NEXTINSTR, // fetch next instruction
    CODEFUNC_YIELD,
} CodeFuncRet;

typedef enum
{
    SCRTRACE_ERROR,
    SCRTRACE_YIELD,
    SCRTRACE_STOP
} ScrTraceRet;

typedef enum
{
    // TODO
    SCR_OPERATION_ADD,
    SCR_OPERATION_SUB,
    SCR_OPERATION_MUL,
    SCR_OPERATION_DIV,
    SCR_OPERATION_OR,
    SCR_OPERATION_AND,
    SCR_OPERATION_EQ,
    SCR_OPERATION_NEQ,
    SCR_OPERATION_S,
    SCR_OPERATION_L,
    SCR_OPERATION_SE,
    SCR_OPERATION_LE
} ScrOperationType;

// 2048 bytes
typedef struct
{
    s32 i[256]; // 0x00
    f32 f[256]; // 0x400
} ScrMemory;

extern ScrMemory* gScrMemory;

u32 scrTraceCode(ScrData* scr);

s32 scrGetIntPara(s32 paramIdx);
f32 scrGetFloatPara(s32 paramIdx);
char* scrGetStrPara(s32 paramIdx);
void scrSetIntReturnVal(s32 retVal);
void scrSetFloatReturnVal(f32 retVal);
u32 scrGetLabelAddr(s32 lblIdx);
void scrSetPC(u32 pc);
u32 scrGetCmdTimer();
ScrData* scrGetCurrent();

#endif