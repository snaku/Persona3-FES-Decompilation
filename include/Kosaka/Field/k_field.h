#ifndef K_FIELD_H
#define K_FIELD_H

#include "Utils.h"

typedef struct Kwlntask KwlnTask;

// 4636 bytes
typedef struct Field
{
    KwlnTask* rootTask;      // 0x00
    KwlnTask* cameraCtlTask; // 0x04
    KwlnTask* eventTask;     // 0x08
    KwlnTask* playerPadTask; // 0x0c
    u8 unkData[0x120c];
} Field;

// 104 bytes. Task data for "field root" task
typedef struct FldRoot
{
    u8 unkData1[0x10];
    s16 majorId;       // 0x10
    s16 minorId;       // 0x12
    u8 unkData2[0x54];
} FldRoot;

void K_Field_Init();
Field* K_Field_Get();

s16 K_Field_GetMajorId(KwlnTask* fldRootTask);
s16 K_Field_GetMinorId(KwlnTask* fldRootTask);

#endif