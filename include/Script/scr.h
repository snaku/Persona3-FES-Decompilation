#ifndef SCR_H
#define SCR_H

#include "Utils.h"

#define SCR_MAX_STACK_SIZE 28

typedef struct KwlnTask KwlnTask;

typedef enum
{
    SCR_VALUE_TYPE_INT,
    SCR_VALUE_TYPE_FLOAT
} ScrValueType;

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
    u32 contentType;  // 0x00. See enum 'ScrContentType'
    u32 unk_04;
    u32 elementCount; // 0x08
    u32 offset;       // 0x0c. To get the addr of the content: addr = header + header->entry[type].offset
} ScrContentEntry;

// 112 bytes
typedef struct ScrHeader
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

// 252 bytes
typedef struct ScrData
{
    u8 scrName[24];                            // Name of the current procedure (same as task->taskName)
    u32 unk_18;
    u32 stackIdx;                              // 0x1c
    u8 stackTypes[SCR_MAX_STACK_SIZE];         // 0x20. Types of each variables in the stack. See enum 'ScrValueType'
    ScrValues stackValues[SCR_MAX_STACK_SIZE]; // 0x3c. Values of each variables in the stack
    ScrHeader* scrHeader;                      // 0xac
    ScrContentEntry* entries;                  // 0xb0
    void* proceduresContent;                   // 0xb4
    void* labelsContent;                       // 0xb8
    void* instrContent;                        // 0xbc
    void* msgContent;                          // 0xc0
    void* stringsContent;                      // 0xc4
    u32 prcdIdx;                               // 0xc8. Procedure position in the .BF file
    u8 unkData1[0x18];
    KwlnTask* task;                            // 0xe4
    u8 unkData2[0x14];
} ScrData;

#endif