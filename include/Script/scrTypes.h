#ifndef SCRTYPES_H
#define SCRTYPES_H

typedef enum
{
    SCR_VALUE_TYPE_INTEGER,   // signed short or int
    SCR_VALUE_TYPE_FLOAT,
    SCR_VALUE_TYPE_STRING = 5
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

// TODO
typedef enum
{
    SCR_OP_CODE_PUSHI,       // push int 
    SCR_OP_CODE_PUSHF,       // push float
    SCR_OP_CODE_PUSHRET = 4, // push return value
    SCR_OP_CODE_STPRCD = 7,  // start procedure
    SCR_OP_CODE_CMNCMD,      // common command
    SCR_OP_CODE_JMP = 10,
    SCR_OP_CODE_GOTO = 14,
    SCR_OP_CODE_PUSHS = 29,  // push short
    SCR_OP_CODE_MAX = 35
} ScrOpCode;

#endif