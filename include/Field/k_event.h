#ifndef K_EVENT_H
#define K_EVENT_H

#include "Utils.h"

// 4 bytes
typedef struct FieldDrawCmd
{
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} FieldDrawCmd;

// 288 bytes
typedef struct FieldEvent
{
    u32 eventType;         // 0x00
    u8 unkData1[0x58];
    KwlnTask* drawCmdTask; // 0x5c
    u8 unkData2[0xc0];
} FieldEvent;

#endif