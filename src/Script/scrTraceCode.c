#include "Script/scr.h"
#include "Script/scrTraceCode.h"
#include "Script/scrScriptProcess.h"
#include "Script/scrCommonCommand.h"
#include "Kosaka/k_assert.h"
#include "g_data.h"
#include "temporary.h"

u32 scrExecOpCodePushi(ScrData* scr);
u32 scrExecOpCodePushs(ScrData* scr);
u32 scrExecOpCodePushf(ScrData* scr);
u32 scrExecOpCodePushRet(ScrData* scr);
u32 scrExecOpCodeStPrcd(ScrData* scr);
u32 scrExecOpCodeCmnCmd(ScrData* scr);
u32 scrExecOpCodeJmp(ScrData* scr);
u32 scrExecOpCodeGoto(ScrData* scr);

typedef u32 (*ScrExecOpCodeFunc)(ScrData* scr);

// 0069d3e0
static const ScrExecOpCodeFunc opCodeFuncTable[] =
{
    // NULL func are unknown for now
    scrExecOpCodePushi, scrExecOpCodePushf,
    NULL, NULL,
    scrExecOpCodePushRet, NULL,
    NULL, scrExecOpCodeStPrcd,
    scrExecOpCodeCmnCmd, NULL,
    scrExecOpCodeJmp, NULL,
    NULL, NULL,
    scrExecOpCodeGoto, NULL,
    NULL, NULL,
    NULL, NULL,
    NULL, NULL,
    NULL, NULL,
    NULL, NULL,
    NULL, NULL,
    scrExecOpCodePushs, NULL
};

u32 scrExecOpCode1(ScrData* scr);

// FUN_0035c300. Push int 
u32 scrExecOpCodePushi(ScrData* scr)
{
    s32 operand;

    operand = scr->instrContent[++scr->instrIdx].iOperand;

    K_ASSERT(scr->stackIdx <= SCR_STACK_USE, 43);

    scr->stackTypes[scr->stackIdx] = SCR_VALUE_TYPE_INTEGER;
    scr->stackValues[scr->stackIdx].iVal = operand;

    scr->stackIdx++;
    scr->instrIdx++;

    return 1;
}

// FUN_0035c3b0. Push short
u32 scrExecOpCodePushs(ScrData* scr)
{
    s32 operand;

    operand = scr->instrContent[scr->instrIdx].opOperand16.sOperand;

    K_ASSERT(scr->stackIdx <= SCR_STACK_USE, 43);

    scr->stackTypes[scr->stackIdx] = SCR_VALUE_TYPE_INTEGER;
    scr->stackValues[scr->stackIdx].iVal = operand;
    
    scr->stackIdx++;
    scr->instrIdx++;
    
    return 1;
}

// FUN_0035c450. Push float
u32 scrExecOpCodePushf(ScrData* scr)
{
    f32 operand;

    operand = scr->instrContent[++scr->instrIdx].fOperand;

    K_ASSERT(scr->stackIdx <= SCR_STACK_USE, 55);

    scr->stackTypes[scr->stackIdx] = SCR_VALUE_TYPE_FLOAT;
    scr->stackValues[scr->stackIdx].fVal = operand;

    scr->stackIdx++;
    scr->instrIdx++;

    return 1;
}

// FUN_0035c870. Push return value
u32 scrExecOpCodePushRet(ScrData* scr)
{
    K_ASSERT(scr->stackIdx <= SCR_STACK_USE, 268);

    scr->stackTypes[scr->stackIdx] = scr->stackTypes[SCR_STACK_RET_IDX];
    scr->stackValues[scr->stackIdx].fVal = scr->stackValues[SCR_STACK_RET_IDX].fVal;

    scr->stackIdx++;
    scr->instrIdx++;

    return 1;
}

// FUN_0035cf00. Start procedure
u32 scrExecOpCodeStPrcd(ScrData* scr)
{
    scr->instrIdx++;

    return 1;
}

// FUN_0035cf20. Call a common command (functions that are in the game executable) by index
u32 scrExecOpCodeCmnCmd(ScrData* scr)
{
    ScrCmdFunc cmdFunc;
    u32 savedInstrIdx;
    u32 cmdFuncRes;
    s32 cmdIdx;

    cmdIdx = scr->instrContent[scr->instrIdx].opOperand16.sOperand;
    K_ASSERT(cmdIdx > 0, 342);
    K_ASSERT(gScrCmdData.total > cmdIdx, 343);

    cmdFunc = gScrCmdData.table[cmdIdx].cmdFunc;
    K_ASSERT(cmdFunc != NULL, 344);

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
u32 scrExecOpCodeJmp(ScrData* scr)
{
    s16 prcdIdx;

    prcdIdx = scr->instrContent[scr->instrIdx].opOperand16.sOperand;
    scr->instrIdx = scr->proceduresContent[prcdIdx].offset;

    return 1;
}

// FUN_0035d310. Jump to a label
u32 scrExecOpCodeGoto(ScrData* scr)
{
    s16 lblIdx;

    lblIdx = scr->instrContent[scr->instrIdx].opOperand16.sOperand;
    scr->instrIdx = scr->labelsContent[lblIdx].offset;

    return 1;
}

// FUN_0035ebf0
u32 scrExecOpCode(ScrData* scr)
{
    // TODO

    return 0;
}

// FUN_0035ed20
s32 scrGetIntPara(s32 paramIdx)
{
    // TODO

    return 0;
}

// FUN_0035ee60
f32 scrGetFloatPara(s32 paramIdx)
{
    // TODO

    return 0.0f;
}

// FUN_0035efa0
char* scrGetStrPara(s32 paramIdx)
{
    s32 paramStackIdx;

    paramStackIdx = gCurrScript->stackIdx - (paramIdx + 1);
    K_ASSERT(gCurrScript->stackIdx > (paramIdx + 1), 1005);

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
            K_Abort("scrGetStrPara(..) invalid stack type!!\n", "scrTraceCode.c", 1016);
            return NULL;
    }
}

// FUN_0035f060. Set 'retType' of the current script to int and set 'iVal' to 'retVal'
void scrSetIntReturnVal(s32 retVal)
{
    gCurrScript->stackTypes[SCR_STACK_RET_IDX] = SCR_VALUE_TYPE_INTEGER;
    gCurrScript->stackValues[SCR_STACK_RET_IDX].iVal = retVal;
}

// FUN_0035f080. Set 'retType' of the current script to float and set 'fVal' to 'retVal'
void scrSetFloatReturnVal(f32 retVal)
{
    gCurrScript->stackTypes[SCR_STACK_RET_IDX] = SCR_VALUE_TYPE_FLOAT;
    gCurrScript->stackValues[SCR_STACK_RET_IDX].fVal = retVal;
}

// FUN_0035f0a0
u32 scrGetCurrScriptLabelOffset(s32 lblIdx)
{
    K_ASSERT(lblIdx > 0, 1067);
    K_ASSERT(gCurrScript->entries[SCR_CONTENT_TYPE_LABEL].elementCount > lblIdx, 1068);

    return gCurrScript->labelsContent[lblIdx].offset;
}