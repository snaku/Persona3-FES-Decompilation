#ifndef K_EVENT_H
#define K_EVENT_H

#include "Utils.h"

typedef enum
{
    // TODO
    FIELD_EVENT_TYPE_OBJ_INTERACT = 2, // Player is interacting with an object
    FIELD_EVENT_TYPE_DESTROY = 32      // destroy 'field event' task
} FieldEventType;

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
    KwlnTask* objScrTask;  // 0x60. Ptr to the script's task of the object the player is currently interacting
    u8 unkData2[0xbc];
} FieldEvent;

KwlnTask* FldEvent_CreateTasks(KwlnTask* fldRootTask);

#endif