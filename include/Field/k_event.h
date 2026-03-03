#ifndef K_EVENT_H
#define K_EVENT_H

#include "Utils.h"

typedef struct ResourceNpc ResourceNpc;

typedef enum
{
    // TODO
    FIELD_EVENT_TYPE_OBJ_INTERACT = 2,  // Player is interacting with an object
    FIELD_EVENT_TYPE_NPC_INTERACT = 21, // Player is interacting with an NPC
    FIELD_EVENT_TYPE_DESTROY = 32       // destroy 'field event' task
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
    u32 eventType;                // 0x00
    u8 unkData1[0x18];
    ResourceNpc* interactableNpc; // 0x1c. Npc the player can currently interact with (in FOV and nearby)
    u8 unkData2[0x3c];
    KwlnTask* drawCmdTask;        // 0x5c
    KwlnTask* objScrTask;         // 0x60. Script task of the object the player is currently interacting
    u8 unkData3[0xbc];
} FieldEvent;

KwlnTask* FldEvent_CreateTasks(KwlnTask* fldRootTask);

#endif