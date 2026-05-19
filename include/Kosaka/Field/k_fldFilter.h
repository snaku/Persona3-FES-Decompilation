#ifndef K_FLDFILTER_H
#define K_FLDFILTER_H

#include "Utils.h"

// 20 bytes
typedef struct FldFilterWork
{
    u8 unkData1[0x08];
    s32 unk_08;        // 0x08
    s32 unk_0c;        // 0x0c
    s32 unk_10;        // 0x10
} FldFilterWork;

void K_FldFilter_Init();
void K_FldFilter_Main();

#endif