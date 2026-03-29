#ifndef K_FIELD_H
#define K_FIELD_H

#include "Utils.h"

typedef struct Kwlntask KwlnTask;

// 4636 bytes
typedef struct K_Field
{
    KwlnTask* rootTask;      // 0x00
    KwlnTask* cameraCtlTask; // 0x04
    KwlnTask* eventTask;     // 0x08
    KwlnTask* playerPadTask; // 0x0c
    u8 unkData[0x120c];
} K_Field;

void K_Field_Init();
K_Field* K_Field_Get();

#endif