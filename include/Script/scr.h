#ifndef SCR_H
#define SCR_H

#include "Utils.h"
#include "Script/scrTypes.h"

#define SCR_MAX_STACK_SIZE 27

#define SCR_MSG_HEADER_MAGIC0 0x3047534d // in little endian: "MSG0"
#define SCR_MSG_HEADER_MAGIC1 0x3147534d // in little endian: "MSG1"

typedef struct KwlnTask KwlnTask;
typedef struct ItfMes ItfMes;

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

// 4 bytes
typedef union 
{
    s32 iVal;
    f32 fVal;
    char* strVal;
} ScrValues;

// 32 bytes. Label or procedure (this name is horrible)
typedef struct
{
    char name[24]; // 0x00
    u32 offset;    // 0x18. Offset in bytes from which the label/procedure starts by instructions base address
    s32 unk_1c;    // 0x1c
} ScrLblPrcd;

// 4 bytes
typedef union
{
    struct
    {
        u16 opCode;
        s16 sOperand;
    } opOperand16;
    
    s32 iOperand;
    f32 fOperand;
} ScrInstruction;

// ?? bytes
typedef struct ScrMsgHeader
{
    u8 unkData1[0x08];
    u32 magic;         // See 'SCR_MSG_HEADER_MAGIC0' and 'SCR_MSG_HEADER_MAGIC1'
} ScrMsgHeader;

// 252 bytes
typedef struct ScrData
{
    char scrName[24];                          // 0x00. Name of the current procedure (same as task->taskName)
    u32 instrIdx;                              // 0x18. Index of the curr instruction
    s32 stackIdx;                              // 0x1c
    s8 stackTypes[SCR_MAX_STACK_SIZE];         // 0x20. Types of each variables in the stack. See enum 'ScrValueType'
    u8 retType;                                // 0x3b. Type of the return value
    ScrValues stackValues[SCR_MAX_STACK_SIZE]; // 0x3c. Values of each variables in the stack
    ScrValues retValue;                        // 0xa8. Value of the return value
    ScrHeader* scrHeader;                      // 0xac
    ScrContentEntry* entries;                  // 0xb0
    ScrLblPrcd* proceduresContent;             // 0xb4
    ScrLblPrcd* labelsContent;                 // 0xb8
    ScrInstruction* instrContent;              // 0xbc
    ScrMsgHeader* msgContentHeader;            // 0xc0
    void* stringsContent;                      // 0xc4
    u32 prcdIdx;                               // 0xc8. Procedure position in the .BF file
    ItfMes* itfMes;                            // 0xcc
    u8 unkData1[0x14];
    KwlnTask* task;                            // 0xe4
    struct ScrData* prev;                      // 0xe8
    struct ScrData* next;                      // 0xec
    u8 unkData2[0x0c];
} ScrData;

#endif