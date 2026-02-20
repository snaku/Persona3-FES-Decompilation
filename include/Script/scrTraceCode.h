#ifndef SCRTRACECODE_H
#define SCRTRACECODE_H

#include "Utils.h"

s32 Scr_GetIntParam(s32 paramIdx);
f32 Scr_GetFloatParam(s32 paramIdx);
char* Scr_GetStrParam(s32 paramIdx);
void Scr_SetCurrScriptIntRetVal(s32 retVal);
void Scr_SetCurrScriptFloatRetVal(f32 retVal);

#endif