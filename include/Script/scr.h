#ifndef SCR_H
#define SCR_H

#include "Utils.h"
#include "Script/scrTypes.h"

#define SCR_MAX_STACK_SIZE 28 // idx 27 is reserved for return value !!
#define SCR_STACK_RET_IDX  27

typedef struct KwlnTask KwlnTask;
typedef struct BmdHeader BmdHeader;

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
    s32 unk_00;                                    // 0x00
    u32 scrSize;                                   // 0x04. size of the .BF file (in bytes)
    u8 magic[4];                                   // 0x08. "FLW0"
    u32 unk_0c;
    u32 totalEntries;                              // 0x10
    u16 localIntNum;                               // 0x14
    u16 localFloatNum;                             // 0x16
    s32 unk_18;                                    // 0x18
    s32 unk_1c;                                    // 0x1c
    ScrContentEntry entries[SCR_CONTENT_TYPE_MAX]; // 0x20
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

// 252 bytes
typedef struct ScrData
{
    char scrName[24];                          // 0x00. Name of the current procedure (same as task->taskName)
    u32 instrIdx;                              // 0x18. Index of the curr instruction
    s32 stackIdx;                              // 0x1c
    s8 stackTypes[SCR_MAX_STACK_SIZE];         // 0x20. Types of each variables in the stack. See enum 'ScrValueType'
    ScrValues stackValues[SCR_MAX_STACK_SIZE]; // 0x3c. Values of each variables in the stack
    ScrHeader* scrHeader;                      // 0xac
    ScrContentEntry* prcdEntry;                // 0xb0
    ScrLblPrcd* proceduresContent;             // 0xb4
    ScrLblPrcd* labelsContent;                 // 0xb8
    ScrInstruction* instrContent;              // 0xbc
    BmdHeader* msgContentHeader;               // 0xc0
    void* stringsContent;                      // 0xc4
    u32 prcdIdx;                               // 0xc8. Procedure position in the .BF file
    s32 mesHandleIdx;                          // 0xcc
    s32 unk_d0;                                // 0xd0
    s32 unk_d4;                                // 0xd4
    void* scriptMemory;                        // 0xd8
    s32* localInt;                             // 0xdc
    f32* localFloat;                           // 0xe0
    KwlnTask* task;                            // 0xe4
    struct ScrData* prev;                      // 0xe8
    struct ScrData* next;                      // 0xec
    s32 unk_f0;                                // 0xf0
    u8 unkData1[0x08];
} ScrData;

#endif