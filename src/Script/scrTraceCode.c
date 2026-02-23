#include "Script/scr.h"
#include "Script/scrTraceCode.h"
#include "Script/scrScriptProcess.h"
#include "Script/scrCommonCommand.h"
#include "g_data.h"
#include "temporary.h"

u32 Scr_ExecOpCodePushi(ScrData* scr);
u32 Scr_ExecOpCodePushs(ScrData* scr);
u32 Scr_ExecOpCodePushf(ScrData* scr);
u32 Scr_ExecOpCodePushRet(ScrData* scr);
u32 Scr_ExecOpCodeStPrcd(ScrData* scr);
u32 Scr_ExecOpCodeCmnCmd(ScrData* scr);
u32 Scr_ExecOpCodeJmp(ScrData* scr);
u32 Scr_ExecOpCodeGoto(ScrData* scr);

typedef u32 (*Scr_ExecOpCodeFunc)(ScrData* scr);

// 0069d3e0
static const Scr_ExecOpCodeFunc opCodeFuncTable[] =
{
    // NULL func are unknown for now
    Scr_ExecOpCodePushi, Scr_ExecOpCodePushf,
    NULL, NULL,
    Scr_ExecOpCodePushRet, NULL,
    NULL, Scr_ExecOpCodeStPrcd,
    Scr_ExecOpCodeCmnCmd, NULL,
    Scr_ExecOpCodeJmp, NULL,
    NULL, NULL,
    Scr_ExecOpCodeGoto, NULL,
    NULL, NULL,
    NULL, NULL,
    NULL, NULL,
    NULL, NULL,
    NULL, NULL,
    NULL, NULL,
    Scr_ExecOpCodePushs, NULL
};

u32 Scr_ExecOpCode1(ScrData* scr);

// FUN_0035c300. Push int 
u32 Scr_ExecOpCodePushi(ScrData* scr)
{
    s32 operand;

    operand = scr->instrContent[++scr->instrIdx].iOperand;

    if (scr->stackIdx >= SCR_MAX_STACK_SIZE - 1)
    {
        P3FES_ASSERT("scrTraceCode.c", 43);
    }

    scr->stackTypes[scr->stackIdx] = SCR_VALUE_TYPE_INTEGER;
    scr->stackValues[scr->stackIdx].iVal = operand;

    scr->stackIdx++;
    scr->instrIdx++;

    return 1;
}

// FUN_0035c3b0. Push short
u32 Scr_ExecOpCodePushs(ScrData* scr)
{
    s32 operand;

    operand = scr->instrContent[scr->instrIdx].opOperand16.sOperand;

    if (scr->stackIdx >= SCR_MAX_STACK_SIZE - 1)
    {
        P3FES_ASSERT("scrTraceCode.c", 43);
    }

    scr->stackTypes[scr->stackIdx] = SCR_VALUE_TYPE_INTEGER;
    scr->stackValues[scr->stackIdx].iVal = operand;
    
    scr->stackIdx++;
    scr->instrIdx++;
    
    return 1;
}

// FUN_0035c450. Push float
u32 Scr_ExecOpCodePushf(ScrData* scr)
{
    f32 operand;

    operand = scr->instrContent[++scr->instrIdx].fOperand;

    if (scr->stackIdx >= SCR_MAX_STACK_SIZE - 1)
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
    if (scr->stackIdx >= SCR_MAX_STACK_SIZE - 1)
    {
        P3FES_ASSERT("scrTraceCode.c", 268);
    }

    scr->stackTypes[scr->stackIdx] = scr->stackTypes[SCR_STACK_RET_IDX];
    scr->stackValues[scr->stackIdx].fVal = scr->stackValues[SCR_STACK_RET_IDX].fVal;

    scr->stackIdx++;
    scr->instrIdx++;

    return 1;
}

// FUN_0035cf00. Start procedure
u32 Scr_ExecOpCodeStPrcd(ScrData* scr)
{
    scr->instrIdx++;

    return 1;
}

// FUN_0035cf20. Call a common command (functions that are in the game executable) by index
u32 Scr_ExecOpCodeCmnCmd(ScrData* scr)
{
    Scr_CmdFunc cmdFunc;
    u32 savedInstrIdx;
    u32 cmdFuncRes;
    s32 cmdIdx;

    cmdIdx = scr->instrContent[scr->instrIdx].opOperand16.sOperand;
    if (cmdIdx < 0)
    {
        P3FES_ASSERT("scrTraceCode.c", 342);
    }
    if (gScrCmdData.total <= cmdIdx)
    {
        P3FES_ASSERT("scrTraceCode.c", 343);
    }

    cmdFunc = gScrCmdData.table[cmdIdx].cmdFunc;
    if (cmdFunc == NULL)
    {
        P3FES_ASSERT("scrTraceCode.c", 344);
    }

    savedInstrIdx = scr->instrIdx;
    gCurrScript = scr;

    if (!cmdFunc())
    {
        return 2;
    }

    scr->stackIdx -= gScrCmdData.table[cmdIdx].totalParam;

    if (savedInstrIdx  == scr->instrIdx)
    {
        scr->instrIdx++;
    }

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

// FUN_0035ebf0
u32 Scr_ExecOpCode(ScrData* scr)
{
    // TODO

    return 0;
}

// FUN_0035ed20
s32 Scr_GetIntParam(s32 paramIdx)
{
    // TODO

    return 0;
}

// FUN_0035ee60
f32 Scr_GetFloatParam(s32 paramIdx)
{
    // TODO

    return 0.0f;
}

// FUN_0035efa0
char* Scr_GetStrParam(s32 paramIdx)
{
    s32 paramStackIdx;

    paramStackIdx = gCurrScript->stackIdx - (paramIdx + 1);
    if (gCurrScript->stackIdx < (paramIdx + 1))
    {
        P3FES_ASSERT("scrTraceCode.c", 1005);
    }

    switch (gCurrScript->stackTypes[paramStackIdx])
    {
        case SCR_VALUE_TYPE_STRING:
            return gCurrScript->stackValues[paramStackIdx].strVal;

        case SCR_VALUE_TYPE_INTEGER: // fallthrough
        case SCR_VALUE_TYPE_FLOAT:   // fallthrough
        case 2:                      // fallthrough
        case 3:                      // fallthrough
        case 4:                      // fallthrough
        default:
            FUN_0019d400("scrGetStrPara(..) invalid stack type!!\n", "scrTraceCode.c", 1016);
            return NULL;
    }
}

// FUN_0035f060. Set 'retType' of the current script to int and set 'iVal' to 'retVal'
void Scr_SetCurrScriptIntRetVal(s32 retVal)
{
    gCurrScript->stackTypes[SCR_STACK_RET_IDX] = SCR_VALUE_TYPE_INTEGER;
    gCurrScript->stackValues[SCR_STACK_RET_IDX].iVal = retVal;
}

// FUN_0035f080. Set 'retType' of the current script to float and set 'fVal' to 'retVal'
void Scr_SetCurrScriptFloatRetVal(f32 retVal)
{
    gCurrScript->stackTypes[SCR_STACK_RET_IDX] = SCR_VALUE_TYPE_FLOAT;
    gCurrScript->stackValues[SCR_STACK_RET_IDX].fVal = retVal;
}