#ifndef SCRTRACECODE_H
#define SCRTRACECODE_H

#include "Utils.h"

typedef struct ScrData ScrData;

u32 scrTraceCode(ScrData* scr);
s32 scrGetIntPara(s32 paramIdx);
f32 scrGetFloatPara(s32 paramIdx);
char* scrGetStrPara(s32 paramIdx);
void scrSetIntReturnVal(s32 retVal);
void scrSetFloatReturnVal(f32 retVal);
u32 scrGetCurrScriptLabelOffset(s32 lblIdx);

#endif