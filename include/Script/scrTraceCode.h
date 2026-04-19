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

u32 scrTraceCode(ScrData* scr);

s32 scrGetIntPara(s32 paramIdx);
f32 scrGetFloatPara(s32 paramIdx);
char* scrGetStrPara(s32 paramIdx);
void scrSetIntReturnVal(s32 retVal);
void scrSetFloatReturnVal(f32 retVal);
u32 scrGetCurrScriptLabelOffset(s32 lblIdx);

#endif