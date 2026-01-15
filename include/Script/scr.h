#ifndef SCR_H
#define SCR_H

#include "Utils.h"

#define SCR_MAX_ARGS 28

typedef struct KwlnTask KwlnTask;

typedef enum
{
    SCR_TYPE_INT,
    SCR_TYPE_FLOAT
} ScrTypes;

typedef enum
{
    SCR_CONTENT_TYPE_PROCEDURE,
    SCR_CONTENT_TYPE_LABEL,
    SCR_CONTENT_TYPE_INSTR,
    SCR_CONTENT_TYPE_MSG,
    SCR_CONTENT_TYPE_STRINGS,
    SCR_CONTENT_TYPE_MAX
} ScrContentType;

// 16 bytes
typedef struct
{
    u32 contentType; // See enum 'ScrContentType'
    u32 unk_04;
    u32 unk_08;
    u32 offset;      // To get the addr of the content: addr = &header + header->entry[type].offset
} ScrContentEntry;

// 112 bytes
typedef struct
{
    u8 unkData1[0x04];
    u32 scrSize;       // 0x04. size of the .BF file (in bytes)
    u8 magic[4];       // 0x08. "FLW0"
    u32 unk_0c;
    u32 totalEntries;  // 0x10
    u8 unkData2[0x0c];
    ScrContentEntry entries[SCR_CONTENT_TYPE_MAX];
} ScrHeader;

typedef union 
{
    s32 iVal;
    f32 fVal;
} ScrValues;

// 252 bytes. Data of a function
typedef struct ProcedureData
{
    u8 prcdName[24];                                  // same as prcdTask->taskName
    u32 unk_18;
    u32 argCount;                                     // 0x1c
    u8 argTypes[SCR_MAX_ARGS];                        // 0x20. See enum 'ScrTypes'
    ScrValues argValues[SCR_MAX_ARGS];                // 0x3c
    ScrHeader* scrHeader;                             // 0xac
    ScrContentEntry (*entries)[SCR_CONTENT_TYPE_MAX]; // 0xb0
    void* proceduresContent;                          // 0xb4
    void* labelsContent;                              // 0xb8
    void* instrContent;                               // 0xbc
    void* msgContent;                                 // 0xc0
    void* stringsContent;                             // 0xc4
    u8 unkData1[0x1c];
    KwlnTask* prcdTask;                               // 0xe4
    u8 unkData2[0x14];
} ProcedureData;

#endif