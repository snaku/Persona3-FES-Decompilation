#ifndef K_FIELD_H
#define K_FIELD_H

#include "Utils.h"

typedef struct Kwlntask KwlnTask;

// 4424 bytes
typedef struct K_Field
{
    KwlnTask* rootTask;      // 0x00
    KwlnTask* cameraCtlTask; // 0x04
    KwlnTask* eventTask;     // 0x08
    KwlnTask* playerPadTask; // 0x0c
    u8 unkData[0x1138];
} K_Field;

#endif