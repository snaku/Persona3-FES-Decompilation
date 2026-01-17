#ifndef SCRTYPES_H
#define SCRTYPES_H

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

// TODO
typedef enum
{
    SCR_OP_CODE_PUSHI,       // push int 
    SCR_OP_CODE_PUSHF,       // push float
    SCR_OP_CODE_PUSHRET = 4, // push return value
    SCR_OP_CODE_MAX = 35
} ScrOpCode;

#endif