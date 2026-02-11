#include "Script/scr.h"
#include "Script/scrTraceCode.h"
#include "g_data.h"
#include "temporary.h"

u32 Scr_ExecOpCodePushi(ScrData* scr);
u32 Scr_ExecOpCodePushf(ScrData* scr);
u32 Scr_ExecOpCodePushRet(ScrData* scr);
u32 Scr_ExecOpCodeJmp(ScrData* scr);
u32 Scr_ExecOpCodeGoto(ScrData* scr);
u32 Scr_ExecOpCodeStPrcd(ScrData* scr);

typedef u32 (*Scr_ExecOpCode)(ScrData* scr);

// 0069d3e0
static const Scr_ExecOpCode opCodeFuncTable[] =
{
    // NULL func are unknown for now
    Scr_ExecOpCodePushi, Scr_ExecOpCodePushf,
    NULL, NULL,
    Scr_ExecOpCodePushRet, NULL,
    NULL, Scr_ExecOpCodeStPrcd,
    NULL, NULL,
    Scr_ExecOpCodeJmp, NULL,
    NULL, NULL,
    Scr_ExecOpCodeGoto, NULL
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
    scr->stackValues[scr->stackIdx].fVal = scr->retValue.fVal;

    scr->stackIdx++;
    scr->instrIdx++;

    return 1;
}

// FUN_0035d1d0. Jump to a procedure
u32 Scr_ExecOpCodeJmp(ScrData* scr)
{
    s16 prcdIdx;

    prcdIdx = scr->instrContent[scr->instrIdx].opOperand16.sOperand;
    scr->instrIdx = scr->proceduresContent[prcdIdx].offset;

    return 1;
}

// FUN_0035d310. Jump to a label
u32 Scr_ExecOpCodeGoto(ScrData* scr)
{
    s16 lblIdx;

    lblIdx = scr->instrContent[scr->instrIdx].opOperand16.sOperand;
    scr->instrIdx = scr->labelsContent[lblIdx].offset;

    return 1;
}

// FUN_0035cf00. Start procedure
u32 Scr_ExecOpCodeStPrcd(ScrData* scr)
{
    scr->instrIdx++;

    return 1;
}

// FUN_0035f060. Set 'retType' of the current script to int and set 'iVal' to 'retVal'
void Scr_SetCurrScriptIntRetVal(s32 retVal)
{
    ctx.currScr->retType = SCR_VALUE_TYPE_INT;
    ctx.currScr->retValue.iVal = retVal;
}

// FUN_0035f080. Set 'retType' of the current script to float and set 'fVal' to 'retVal'
void Scr_SetCurrScriptFloatRetVal(f32 retVal)
{
    ctx.currScr->retType = SCR_VALUE_TYPE_FLOAT;
    ctx.currScr->retValue.fVal = retVal;
}