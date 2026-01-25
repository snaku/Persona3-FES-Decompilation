#ifndef K_EVENT_H
#define K_EVENT_H

#include "Utils.h"

// 288 bytes
typedef struct FieldEvent
{
    u32 eventType;         // 0x00
    u8 unkData1[0x58];
    KwlnTask* drawCmdTask; // 0x5c
    u8 unkData2[0xc0];
} FieldEvent;

#endif