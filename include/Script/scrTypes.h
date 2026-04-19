#ifndef SCRTYPES_H
#define SCRTYPES_H

typedef enum
{
    SCR_STACK_TYPE_INTEGER,   // signed short or int
    SCR_STACK_TYPE_FLOAT,
    SCR_STACK_TYPE_STRING = 5
} ScrStackType;

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
    SCR_CODEFUNC_PUSHI,       // push int 
    SCR_CODEFUNC_PUSHF,       // push float
    SCR_CODEFUNC_PUSHREG = 4, // push return value
    SCR_CODEFUNC_PROC = 7,  // start procedure
    SCR_CODEFUNC_COMM,      // common command
    SCR_CODEFUNC_JMP = 10,
    SCR_CODEFUNC_GOTO = 14,
    SCR_CODEFUNC_PUSHS = 29,  // push short

    SCR_CODEFUNC_MAX = 35
} ScrOpCode;

#endif