#include "Script/scr.h"
#include "Script/scrTraceCode.h"
#include "Script/scrScriptProcess.h"
#include "Script/scrCommonCommand.h"
#include "Kosaka/k_assert.h"
#include "Kosaka/k_data.h"
#include "h_dbprt.h"
#include "temporary.h"

static ScrMemory sMemory;         // 00957c00
ScrMemory* gScrMemory = &sMemory; // 007cca5c

static ScrData* sCurrScript; // 007ce5a8. Current script being executed

u32 CodeFunc_PushI(ScrData* scr);
u32 CodeFunc_PushS(ScrData* scr);
u32 CodeFunc_PushF(ScrData* scr);
u32 CodeFunc_PushIX(ScrData* scr);
u32 CodeFunc_PushIF(ScrData* scr);
u32 CodeFunc_PushREG(ScrData* scr);
u32 CodeFunc_Proc(ScrData* scr);
u32 CodeFunc_Comm(ScrData* scr);
u32 CodeFunc_Jmp(ScrData* scr);
u32 CodeFunc_Call(ScrData* scr);
u32 CodeFunc_Run(ScrData* scr);
u32 CodeFunc_Goto(ScrData* scr);

typedef u32 (*CodeFunc)(ScrData* scr);

// 0069d3e0
static const CodeFunc sCodeFuncTable[SCR_CODEFUNC_MAX] =
{
    CodeFunc_PushI, CodeFunc_PushF, CodeFunc_PushIX, CodeFunc_PushIF, CodeFunc_PushREG,
    NULL, NULL, CodeFunc_Proc, CodeFunc_Comm, NULL,
    CodeFunc_Jmp, CodeFunc_Call, CodeFunc_Run, CodeFunc_Goto, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, CodeFunc_PushS,
    NULL, NULL, NULL, NULL, NULL
};

// FUN_0035c300. Push an immediate int value 
u32 CodeFunc_PushI(ScrData* scr)
{
    s32 operand;

    operand = scr->instrContent[++scr->pc].iOperand;

    K_ASSERT(scr->sp < SCR_STACK_RET, 43);

    scr->stackTypes[scr->sp] = SCR_STACK_TYPE_INTEGER;
    scr->stackValues[scr->sp].iVal = operand;

    scr->sp++;
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035c3b0. Push an immediate short value
u32 CodeFunc_PushS(ScrData* scr)
{
    s32 operand;

    operand = scr->instrContent[scr->pc].opOperand16.sOperand;

    K_ASSERT(scr->sp < SCR_STACK_RET, 43);

    scr->stackTypes[scr->sp] = SCR_STACK_TYPE_INTEGER;
    scr->stackValues[scr->sp].iVal = operand;
    
    scr->sp++;
    scr->pc++;
    
    return CODEFUNC_NEXTINSTR;
}

// FUN_0035c450. Push an immediate float value
u32 CodeFunc_PushF(ScrData* scr)
{
    f32 operand;

    operand = scr->instrContent[++scr->pc].fOperand;

    K_ASSERT(scr->sp < SCR_STACK_RET, 55);

    scr->stackTypes[scr->sp] = SCR_STACK_TYPE_FLOAT;
    scr->stackValues[scr->sp].fVal = operand;

    scr->sp++;
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035c500. Push an int from the VM memory
u32 CodeFunc_PushIX(ScrData* scr)
{
    s32 var;

    var = gScrMemory->i[scr->instrContent[scr->pc].opOperand16.sOperand];

    K_ASSERT(scr->sp < SCR_STACK_RET, 43);

    scr->stackTypes[scr->sp] = SCR_STACK_TYPE_INTEGER;
    scr->stackValues[scr->sp].iVal = var;

    scr->sp++;
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035c5b0. Push a float from the VM memory
u32 CodeFunc_PushIF(ScrData* scr)
{
    f32 var;

    var = gScrMemory->f[scr->instrContent[scr->pc].opOperand16.sOperand]; // TODO: addu v0, v0, v1 instead of addu v0, v1, v0

    K_ASSERT(scr->sp < SCR_STACK_RET, 55);

    scr->stackTypes[scr->sp] = SCR_STACK_TYPE_FLOAT;
    scr->stackValues[scr->sp].fVal = var;

    scr->sp++;
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035c870. Push return value
u32 CodeFunc_PushREG(ScrData* scr)
{
    K_ASSERT(scr->sp < SCR_STACK_RET, 268);

    scr->stackTypes[scr->sp] = scr->stackTypes[SCR_STACK_RET];
    scr->stackValues[scr->sp] = scr->stackValues[SCR_STACK_RET];

    scr->sp++;
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035cf00. Start procedure
u32 CodeFunc_Proc(ScrData* scr)
{
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035cf20. Call a native function
u32 CodeFunc_Comm(ScrData* scr)
{
    ScrCmdFunc cmdFunc;
    u32 savedPc;
    u32 cmdFuncRes;
    s32 cmdIdx;

    cmdIdx = scr->instrContent[scr->pc].opOperand16.sOperand;
    K_ASSERT(cmdIdx >= 0, 342);
    K_ASSERT(cmdIdx < gScrCmdTable.cmdNo, 343);

    cmdFunc = gScrCmdTable.cmds[cmdIdx].func;
    K_ASSERT(cmdFunc != NULL, 344);

    savedPc = scr->pc;
    sCurrScript = scr;

    if (!cmdFunc())
    {
        return CODEFUNC_YIELD;
    }

    scr->sp -= gScrCmdTable.cmds[cmdIdx].paramNo;

    if (savedPc == scr->pc)
    {
        scr->pc++;
    }

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035d1d0. Jump to a procedure
u32 CodeFunc_Jmp(ScrData* scr)
{
    s16 prcdIdx;

    prcdIdx = scr->instrContent[scr->pc].opOperand16.sOperand;
    scr->pc = scr->proceduresContent[prcdIdx].addr;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035d210. Call a procedure + push PC
u32 CodeFunc_Call(ScrData* scr)
{
    u32 savedPC;

    savedPC = scr->pc;
    K_ASSERT(scr->sp < SCR_STACK_RET, 111);

    scr->stackTypes[scr->sp] = SCR_STACK_TYPE_ADDR;
    scr->stackValues[scr->sp].iVal = savedPC;
    scr->sp++;

    scr->pc = scr->proceduresContent[scr->instrContent[scr->pc].opOperand16.sOperand].addr;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035d2c0
u32 CodeFunc_Run(ScrData* scr)
{
    K_Abort("CodeFunc_Run(..) Can't running command!!\n", "scrTraceCode.c", 416);

    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035d310. Jump to a label
u32 CodeFunc_Goto(ScrData* scr)
{
    s16 lblIdx;

    lblIdx = scr->instrContent[scr->pc].opOperand16.sOperand;
    scr->pc = scr->labelsContent[lblIdx].addr;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035ebf0
u32 scrTraceCode(ScrData* scr)
{
    s16 opCode;
    u32 codeFuncRet;

    while (true)
    {
        opCode = scr->instrContent[scr->pc].opOperand16.opCode;
        K_ASSERT(opCode >= SCR_CODEFUNC_PUSHI, 895);
        K_ASSERT(opCode < SCR_CODEFUNC_MAX, 896);

        if (gTraceCode == true)
        {
            H_Dbprt_FmtLog(">>>SCRIPT TRACE <0x%X>\n", scr->instrContent[scr->pc].opOperand16.sOperand);
        }

        codeFuncRet = sCodeFuncTable[opCode](scr);

        if (codeFuncRet == CODEFUNC_STOP)
        {
            scr->unk_d4 = 0;

            return SCRTRACE_STOP;
        }

        if (codeFuncRet != CODEFUNC_YIELD)
        {
            if (codeFuncRet == CODEFUNC_NEXTINSTR)
            {
                scr->unk_d4 = 0;
                continue;
            }
        }
        else
        {
            scr->unk_d4++;
            scr->unk_d0++;

            return SCRTRACE_YIELD;
        }
    }
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
    s32 paramSP;

    paramSP = sCurrScript->sp - (paramIdx + 1);
    K_ASSERT((paramIdx + 1) <= sCurrScript->sp, 1005);

    switch (sCurrScript->stackTypes[paramSP])
    {
        case SCR_STACK_TYPE_STRING:
            return sCurrScript->stackValues[paramSP].strVal;

        case SCR_STACK_TYPE_INTEGER: // fallthrough
        case SCR_STACK_TYPE_FLOAT:   // fallthrough
        case 2:                      // fallthrough
        case 3:                      // fallthrough
        case SCR_STACK_TYPE_ADDR:    // fallthrough
        default:
            K_Abort("scrGetStrPara(..) invalid stack type!!\n", "scrTraceCode.c", 1016);
            return NULL;
    }
}

// FUN_0035f060. Set 'retType' of the current script to int and set 'iVal' to 'retVal'
void scrSetIntReturnVal(s32 retVal)
{
    sCurrScript->stackTypes[SCR_STACK_RET] = SCR_STACK_TYPE_INTEGER;
    sCurrScript->stackValues[SCR_STACK_RET].iVal = retVal;
}

// FUN_0035f080. Set 'retType' of the current script to float and set 'fVal' to 'retVal'
void scrSetFloatReturnVal(f32 retVal)
{
    sCurrScript->stackTypes[SCR_STACK_RET] = SCR_STACK_TYPE_FLOAT;
    sCurrScript->stackValues[SCR_STACK_RET].fVal = retVal;
}

// FUN_0035f0a0
u32 scrGetLabelAddr(s32 lblIdx)
{
    K_ASSERT(lblIdx >= 0, 1067);
    K_ASSERT(lblIdx < sCurrScript->entries[SCR_CONTENT_TYPE_LABEL].elementCount, 1068);

    return sCurrScript->labelsContent[lblIdx].addr;
}

// FUN_0035f120
void scrSetPC(u32 pc)
{
    sCurrScript->pc = pc;
}

// FUN_0035f150
ScrData* scrGetCurrent()
{
    return sCurrScript;
}