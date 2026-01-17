#include "Script/scr.h"
#include "Script/scrTraceCode.h"
#include "g_data.h"

u32 Scr_ExecOpCodePushi(ScrData* scr);
u32 Scr_ExecOpCodePushf(ScrData* scr);
u32 Scr_ExecOpCodePushRet(ScrData* scr);

typedef u32 (*Scr_ExecOpCode)(ScrData* scr);

// 0069d3e0
static const Scr_ExecOpCode opCodeFuncTable[] =
{
    // NULL func are unknown for now
    Scr_ExecOpCodePushi, Scr_ExecOpCodePushf, NULL, NULL,
    Scr_ExecOpCodePushRet
};

// FUN_0035c300. Push int 
u32 Scr_ExecOpCodePushi(ScrData* scr)
{
    s32 operand;

    scr->instrIdx++;

    operand = scr->instrContent[scr->instrIdx].iOperand;

    if (scr->stackIdx >= SCR_MAX_STACK_SIZE)
    {
        P3FES_ASSERT("scrTraceCode.c", 43);
    }

    scr->stackTypes[scr->stackIdx] = SCR_VALUE_TYPE_INT;
    scr->stackValues[scr->stackIdx].iVal = operand;

    scr->stackIdx++;
    scr->instrIdx++;

    return 1;
}

// FUN_0035c450. Push float
u32 Scr_ExecOpCodePushf(ScrData* scr)
{
    f32 operand;

    scr->instrIdx++;

    operand = scr->instrContent[scr->instrIdx].fOperand;

    if (scr->stackIdx >= SCR_MAX_STACK_SIZE)
    {
        P3FES_ASSERT("scrTraceCode.c", 55);
    }

    scr->stackTypes[scr->stackIdx] = SCR_VALUE_TYPE_FLOAT;
    scr->stackValues[scr->stackIdx].fVal = operand;

    scr->stackIdx++;
    scr->instrIdx++;

    return 1;
}

// FUN_0035c870. Push return value
u32 Scr_ExecOpCodePushRet(ScrData* scr)
{
    if (scr->stackIdx >= SCR_MAX_STACK_SIZE)
    {
        P3FES_ASSERT("scrTraceCode.c", 268);
    }

    scr->stackTypes[scr->stackIdx] = scr->retType;
    scr->stackValues[scr->stackIdx] = scr->retValue;

    scr->stackIdx++;
    scr->instrIdx++;

    return 1;
}