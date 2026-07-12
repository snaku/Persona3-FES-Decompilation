#include "Script/scr.h"
#include "Script/scrTraceCode.h"
#include "Script/scrScriptProcess.h"
#include "Script/scrCommonCommand.h"
#include "Kosaka/k_assert.h"
#include "Kosaka/k_data.h"
#include "Tohyama/h_dbprt.h"
#include "temporary.h"

static ScrMemory sMemory;         // 00957c00
ScrMemory* gScrMemory = &sMemory; // 007cca5c

static ScrData* sCurrScript; // 007ce5a8. Current script being executed

static s32 sOpRightType; // 007ce5a4
static s32 sOpLeftType;  // 007ce5a0
static f32 sOpFRes;      // 007ce59c
static f32 sOpRightFVal; // 007ce598
static f32 sOpLeftFVal;  // 007ce594
static s32 sOpIRes;      // 007ce590
static s32 sOpRightIVal; // 007ce58c
static s32 sOpLeftIVal;  // 007ce588

static u32 CodeFunc_PushI(ScrData* scr);
static u32 CodeFunc_PushS(ScrData* scr);
static u32 CodeFunc_PushF(ScrData* scr);
static u32 CodeFunc_PushIX(ScrData* scr);
static u32 CodeFunc_PushIF(ScrData* scr);
static u32 CodeFunc_PushLIX(ScrData* scr);
static u32 CodeFunc_PushLFX(ScrData* scr);
static u32 CodeFunc_PushSTR(ScrData* scr);
static u32 CodeFunc_PushREG(ScrData* scr);
static u32 CodeFunc_PopIX(ScrData* scr);
static u32 CodeFunc_PopFX(ScrData* scr);
static u32 CodeFunc_PopLIX(ScrData* scr);
static u32 CodeFunc_PopLFX(ScrData* scr);
static u32 CodeFunc_Proc(ScrData* scr);
static u32 CodeFunc_Comm(ScrData* scr);
static u32 CodeFunc_End(ScrData* scr);
static u32 CodeFunc_Jmp(ScrData* scr);
static u32 CodeFunc_Call(ScrData* scr);
static u32 CodeFunc_Run(ScrData* scr);
static u32 CodeFunc_Goto(ScrData* scr);
static u32 CodeFunc_Add(ScrData* scr);
static u32 CodeFunc_Sub(ScrData* scr);
static u32 CodeFunc_Mul(ScrData* scr);
static u32 CodeFunc_Div(ScrData* scr);
static u32 CodeFunc_Minus(ScrData* scr);
static u32 CodeFunc_Not(ScrData* scr);
static u32 CodeFunc_Or(ScrData* scr);
static u32 CodeFunc_And(ScrData* scr);
static u32 CodeFunc_Eq(ScrData* scr);
static u32 CodeFunc_Neq(ScrData* scr);
static u32 CodeFunc_S(ScrData* scr);
static u32 CodeFunc_L(ScrData* scr);
static u32 CodeFunc_SE(ScrData* scr);
static u32 CodeFunc_LE(ScrData* scr);
static u32 CodeFunc_IF(ScrData* scr);

typedef u32 (*CodeFunc)(ScrData* scr);

// 0069d3e0
static const CodeFunc sCodeFuncTable[SCR_CODEFUNC_MAX] =
{
    CodeFunc_PushI, CodeFunc_PushF, CodeFunc_PushIX, CodeFunc_PushIF, CodeFunc_PushREG,
    CodeFunc_PopIX, CodeFunc_PopFX, CodeFunc_Proc, CodeFunc_Comm, CodeFunc_End,
    CodeFunc_Jmp, CodeFunc_Call, CodeFunc_Run, CodeFunc_Goto, CodeFunc_Add,
    CodeFunc_Sub, CodeFunc_Mul, CodeFunc_Div, CodeFunc_Minus, CodeFunc_Not,
    CodeFunc_Or, CodeFunc_And, CodeFunc_Eq, CodeFunc_Neq, CodeFunc_S,
    CodeFunc_L, CodeFunc_SE, CodeFunc_LE, CodeFunc_IF, CodeFunc_PushS,
    CodeFunc_PushLIX, CodeFunc_PushLFX, CodeFunc_PopLIX, CodeFunc_PopLFX, CodeFunc_PushSTR
};

static inline void PushInt(ScrData* scr, s32 val)
{
    K_ASSERT(scr->sp < SCR_STACK_RET, 43);

    scr->stackTypes[scr->sp] = SCR_STACK_TYPE_INTEGER;
    scr->stackValues[scr->sp].iVal = val;
    scr->sp++;
}

static inline void PushFloat(ScrData* scr, f32 val)
{
    K_ASSERT(scr->sp < SCR_STACK_RET, 55);

    scr->stackTypes[scr->sp] = SCR_STACK_TYPE_FLOAT;
    scr->stackValues[scr->sp].fVal = val;
    scr->sp++;
}

static inline void PushString(ScrData* scr, char* str)
{
    K_ASSERT(scr->sp < SCR_STACK_RET, 69);

    scr->stackTypes[scr->sp] = SCR_STACK_TYPE_STRING;
    scr->stackValues[scr->sp].strVal = str;
    scr->sp++;
}

static inline void PushPC(ScrData* scr, s32 val)
{
    K_ASSERT(scr->sp < SCR_STACK_RET, 111);

    scr->stackTypes[scr->sp] = SCR_STACK_TYPE_ADDR;
    scr->stackValues[scr->sp].iVal = val;
    scr->sp++;
}

static inline s32 PopInt(ScrData* scr)
{
    s32 sp;
    f32* f;

    K_ASSERT(scr->sp > 0, 122);

    sp = --scr->sp;

    switch (scr->stackTypes[sp])
    {
        case SCR_STACK_TYPE_INTEGER: // fallthrough
        case SCR_STACK_TYPE_ADDR:    return scr->stackValues[sp].iVal;
        case SCR_STACK_TYPE_FLOAT:   return (s32)scr->stackValues[sp].fVal;

        case 2: return gScrMemory->i[scr->stackValues[sp].iVal];
        case 3:
            f = &gScrMemory->f[scr->stackValues[sp].iVal];
            return (s32)*f;
    }

    K_ABORT("PopInt(..) invalid stack type!!\n", 135);

    return 0;
}

static inline f32 PopFloat(ScrData* scr)
{
    s32 sp;
    f32* f;

    K_ASSERT(scr->sp > 0, 146);

    sp = --scr->sp;

    switch (scr->stackTypes[sp])
    {
        case SCR_STACK_TYPE_INTEGER: return (f32)scr->stackValues[sp].iVal;

        case SCR_STACK_TYPE_ADDR:
            K_ABORT("PopFloat(..) invalid stack type(RET)!!\n", 152);
            return 0.0f;

        case SCR_STACK_TYPE_FLOAT: return scr->stackValues[sp].fVal;

        case 2: return (f32)gScrMemory->i[scr->stackValues[sp].iVal];
        case 3:
            f = &gScrMemory->f[scr->stackValues[sp].iVal];
            return *f;
    }

    K_ABORT("PopFloat(..) invalid stack type(?)!!\n", 161);

    return 0.0f;
}

// FUN_0035c300. Push an immediate int value 
static u32 CodeFunc_PushI(ScrData* scr)
{
    PushInt(scr, scr->instrContent[++scr->pc].iOperand);
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035c3b0. Push an immediate short value
static u32 CodeFunc_PushS(ScrData* scr)
{
    PushInt(scr, scr->instrContent[scr->pc].opOperand16.sOperand);
    scr->pc++;
    
    return CODEFUNC_NEXTINSTR;
}

// FUN_0035c450. Push an immediate float value
static u32 CodeFunc_PushF(ScrData* scr)
{
    PushFloat(scr, scr->instrContent[++scr->pc].fOperand);
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035c500. Push an int from the VM memory
static u32 CodeFunc_PushIX(ScrData* scr)
{
    PushInt(scr, gScrMemory->i[scr->instrContent[scr->pc].opOperand16.sOperand]);
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035c5b0. Push a float from the VM memory
static u32 CodeFunc_PushIF(ScrData* scr)
{
    f32* f;

    f = &gScrMemory->f[scr->instrContent[scr->pc].opOperand16.sOperand];
    PushFloat(scr, *f);
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035c660
static u32 CodeFunc_PushLIX(ScrData* scr)
{
    PushInt(scr, scr->localInt[scr->instrContent[scr->pc].opOperand16.sOperand]);
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035c710
static u32 CodeFunc_PushLFX(ScrData* scr)
{
    PushFloat(scr, scr->localFloat[scr->instrContent[scr->pc].opOperand16.sOperand]);
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035c7c0
static u32 CodeFunc_PushSTR(ScrData* scr)
{
    PushString(scr, scr->stringsContent + scr->instrContent[scr->pc].opOperand16.sOperand); // TODO: fix load order
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035c870. Push return value
static u32 CodeFunc_PushREG(ScrData* scr)
{
    K_ASSERT(scr->sp < SCR_STACK_RET, 268);

    scr->stackTypes[scr->sp] = scr->stackTypes[SCR_STACK_RET];
    scr->stackValues[scr->sp] = scr->stackValues[SCR_STACK_RET];
    scr->sp++;

    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035c900
static u32 CodeFunc_PopIX(ScrData* scr)
{
    gScrMemory->i[scr->instrContent[scr->pc].opOperand16.sOperand] = PopInt(scr);
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035ca70
static u32 CodeFunc_PopFX(ScrData* scr)
{
    f32 val;
    f32* f;

    val = PopFloat(scr);
    f = &gScrMemory->f[scr->instrContent[scr->pc].opOperand16.sOperand];
    *f = val;

    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035cc00
static u32 CodeFunc_PopLIX(ScrData* scr)
{
    scr->localInt[scr->instrContent[scr->pc].opOperand16.sOperand] = PopInt(scr);
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035cd70
static u32 CodeFunc_PopLFX(ScrData* scr)
{
    scr->localFloat[scr->instrContent[scr->pc].opOperand16.sOperand] = PopFloat(scr);
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035cf00. Start procedure
static u32 CodeFunc_Proc(ScrData* scr)
{
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035cf20. Call a native function
static u32 CodeFunc_Comm(ScrData* scr)
{
    ScrCmdFunc cmdFunc;
    u32 savedPc;
    u32 cmdFuncRes;
    s32 cmdIdx;

    cmdIdx = scr->instrContent[scr->pc].opOperand16.sOperand;
    K_ASSERT(cmdIdx >= 0, 342);
    K_ASSERT(cmdIdx < gScrCmdTable.count, 343);
    K_ASSERT((cmdFunc = gScrCmdTable.cmds[cmdIdx].func) != NULL, 344);

    savedPc = scr->pc;
    sCurrScript = scr;

    if (!cmdFunc())
    {
        return CODEFUNC_YIELD;
    }

    scr->sp -= gScrCmdTable.cmds[cmdIdx].paramCount;

    if (savedPc == scr->pc)
    {
        scr->pc++;
    }

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035d040
static u32 CodeFunc_End(ScrData* scr)
{
    if (scr->sp == 0)
    {
        return CODEFUNC_STOP;
    }
    
    K_ASSERT(scr->stackTypes[scr->sp - 1] == SCR_STACK_TYPE_ADDR, 383);

    scr->pc = PopInt(scr);
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035d1d0. Jump to a procedure
static u32 CodeFunc_Jmp(ScrData* scr)
{
    s16 prcdIdx;

    prcdIdx = scr->instrContent[scr->pc].opOperand16.sOperand;
    scr->pc = scr->proceduresContent[prcdIdx].addr;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035d210. Call a procedure + push PC
static u32 CodeFunc_Call(ScrData* scr)
{
    PushPC(scr, scr->pc);
    scr->pc = scr->proceduresContent[scr->instrContent[scr->pc].opOperand16.sOperand].addr;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035d2c0
static u32 CodeFunc_Run(ScrData* scr)
{
    K_ABORT("CodeFunc_Run(..) Can't running command!!\n", 416);

    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035d310. Jump to a label
static u32 CodeFunc_Goto(ScrData* scr)
{
    s16 lblIdx;

    lblIdx = scr->instrContent[scr->pc].opOperand16.sOperand;
    scr->pc = scr->labelsContent[lblIdx].addr;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035d350
static void scrOperation(ScrData* scr, u32 type)
{
    K_ASSERT(scr->sp >= 2, 441);

    sOpLeftType = scr->stackTypes[scr->sp - 1];
    sOpRightType = scr->stackTypes[scr->sp - 2];

    // int
    if ((sOpLeftType == SCR_STACK_TYPE_INTEGER || sOpLeftType == 2) &&
       ((sOpRightType == SCR_STACK_TYPE_INTEGER || sOpRightType == 2)))
    {
        sOpLeftIVal = PopInt(scr);
        sOpRightIVal = PopInt(scr);

        switch (type)
        {
            case SCR_OPERATION_ADD: sOpIRes = sOpLeftIVal + sOpRightIVal; break;
            case SCR_OPERATION_SUB: sOpIRes = sOpLeftIVal - sOpRightIVal; break;
            case SCR_OPERATION_MUL: sOpIRes = sOpLeftIVal * sOpRightIVal; break;
            case SCR_OPERATION_DIV:
                K_ASSERT(sOpRightIVal != 0, 460);
                sOpIRes = sOpLeftIVal / sOpRightIVal; 
                break;

            case SCR_OPERATION_OR:
                if (sOpLeftIVal != 0 || sOpRightIVal != 0)
                {
                    sOpIRes = true;
                }
                else
                {
                    sOpIRes = false;
                }
                break;
            
            case SCR_OPERATION_AND:
                if (sOpLeftIVal != 0 && sOpRightIVal != 0)
                {
                    sOpIRes = true;
                }
                else
                {
                    sOpIRes = false;
                }
                break;
            
            case SCR_OPERATION_EQ:
                if (sOpLeftIVal == sOpRightIVal)
                {
                    sOpIRes = true;
                }
                else
                {
                    sOpIRes = false;
                }
                break;

            case SCR_OPERATION_NEQ:
                if (sOpLeftIVal != sOpRightIVal)
                {
                    sOpIRes = true;
                }
                else
                {
                    sOpIRes = false;
                }
                break;
            
            case SCR_OPERATION_S:
                if (sOpLeftIVal < sOpRightIVal)
                {
                    sOpIRes = true;
                }
                else
                {
                    sOpIRes = false;
                }
                break;
            
            case SCR_OPERATION_L:
                if (sOpLeftIVal > sOpRightIVal)
                {
                    sOpIRes = true;
                }
                else
                {
                    sOpIRes = false;
                }
                break;

            case SCR_OPERATION_SE:
                if (sOpLeftIVal <= sOpRightIVal)
                {
                    sOpIRes = true;
                }
                else
                {
                    sOpIRes = false;
                }
                break;

            case SCR_OPERATION_LE:
                if (sOpLeftIVal >= sOpRightIVal)
                {
                    sOpIRes = true;
                }
                else
                {
                    sOpIRes = false;
                }
        }

        PushInt(scr, sOpIRes);
        return;
    }

    // float

    sOpLeftFVal = PopFloat(scr);
    sOpRightFVal = PopFloat(scr);

    switch (type)
    {
        case SCR_OPERATION_ADD: sOpFRes = sOpLeftFVal + sOpRightFVal; break; // PushFloat
        case SCR_OPERATION_SUB: sOpFRes = sOpLeftFVal - sOpRightFVal; break; // PushFloat
        case SCR_OPERATION_MUL: sOpFRes = sOpLeftFVal * sOpRightFVal; break; // PushFloat
        case SCR_OPERATION_DIV:
            K_ASSERT(sOpRightFVal != 0.0f, 527);
            sOpFRes = sOpLeftFVal / sOpRightFVal; 
            break; // PushFloat

        case SCR_OPERATION_OR:
            if (sOpLeftFVal != 0.0f || sOpRightFVal != 0.0f)
            {
                sOpIRes = true;
            }
            else
            {
                sOpIRes = false;
            }

            PushInt(scr, sOpIRes);
            return;
        
        case SCR_OPERATION_AND:
            if (sOpLeftFVal != 0.0f && sOpRightFVal != 0.0f)
            {
                sOpIRes = true;
            }
            else
            {
                sOpIRes = false;
            }

            PushInt(scr, sOpIRes);
            return;

        case SCR_OPERATION_EQ:
            if (sOpLeftFVal == sOpRightFVal)
            {
                sOpIRes = true;
            }
            else
            {
                sOpIRes = false;
            }

            PushInt(scr, sOpIRes);
            return;

        case SCR_OPERATION_NEQ:
            if (sOpLeftFVal != sOpRightFVal)
            {
                sOpIRes = true;
            }
            else
            {
                sOpIRes = false;
            }

            PushInt(scr, sOpIRes);
            return;

        case SCR_OPERATION_S:
            if (sOpLeftFVal < sOpRightFVal)
            {
                sOpIRes = true;
            }
            else
            {
                sOpIRes = false;
            }

            PushInt(scr, sOpIRes);
            return;

        case SCR_OPERATION_L:
            if (sOpLeftFVal > sOpRightFVal)
            {
                sOpIRes = true;
            }
            else
            {
                sOpIRes = false;
            }

            PushInt(scr, sOpIRes);
            return;

        case SCR_OPERATION_SE:
            if (sOpLeftFVal <= sOpRightFVal)
            {
                sOpIRes = true;
            }
            else
            {
                sOpIRes = false;
            }

            PushInt(scr, sOpIRes);
            return;

        case SCR_OPERATION_LE:
            if (sOpLeftFVal >= sOpRightFVal)
            {
                sOpIRes = true;
            }
            else
            {
                sOpIRes = false;
            }

            PushInt(scr, sOpIRes);
            return;
    }

    PushFloat(scr, sOpFRes);
}

// FUN_0035dfe0
static u32 CodeFunc_Add(ScrData* scr)
{
    scrOperation(scr, SCR_OPERATION_ADD);
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035e020
static u32 CodeFunc_Sub(ScrData* scr)
{
    scrOperation(scr, SCR_OPERATION_SUB);
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035e60
static u32 CodeFunc_Mul(ScrData* scr)
{
    scrOperation(scr, SCR_OPERATION_MUL);
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035e0a0
static u32 CodeFunc_Div(ScrData* scr)
{
    scrOperation(scr, SCR_OPERATION_DIV);
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035e0e0
static u32 CodeFunc_Minus(ScrData* scr)
{
    s32 sp;
    f32* f;

    K_ASSERT(scr->sp > 0, 642);

    sp = scr->sp;
    switch (scr->stackTypes[sp - 1])
    {
        case SCR_STACK_TYPE_INTEGER:
            scr->stackValues[sp - 1].iVal = -scr->stackValues[sp - 1].iVal;
            break;

        case SCR_STACK_TYPE_ADDR:
            K_ABORT("CodeFunc_Minus(..) invalid stack type(RET)!!\n", 648); 
            break;

        case SCR_STACK_TYPE_FLOAT:
            scr->stackValues[sp - 1].fVal = -scr->stackValues[sp - 1].fVal;
            break;

        case 2:
            gScrMemory->i[scr->stackValues[sp - 1].iVal] = -gScrMemory->i[scr->stackValues[sp - 1].iVal];
            break;
            
        case 3:
            f = &gScrMemory->f[scr->stackValues[sp - 1].iVal];
            *f = -(*f);
            break;
        
        default: K_ABORT("CodeFunc_Minus(..) invalid stack type(?)!!\n", 648);
    }

    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035e250
static u32 CodeFunc_Not(ScrData* scr)
{
    u32 res;

    K_ASSERT(scr->sp > 0, 677);

    switch (scr->stackTypes[scr->sp - 1])
    {
        case SCR_STACK_TYPE_INTEGER: // fallthrough
        case 2:
            res = PopInt(scr) == 0;
            PushInt(scr, res);
            break;

        case SCR_STACK_TYPE_FLOAT: // fallthrough
        case 3:
            res = PopFloat(scr) == 0.0f;
            PushInt(scr, res);
            break;

        case SCR_STACK_TYPE_ADDR:
            K_ABORT("CodeFunc_Not(..) invalid stack type(RET)!!\n", 696);
            break;
        
        default:
            K_ABORT("CodeFunc_Not(..) invalid stack type(?)!!\n", 699);
    }

    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035e650
static u32 CodeFunc_Or(ScrData* scr)
{
    scrOperation(scr, SCR_OPERATION_OR);
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035e650
static u32 CodeFunc_And(ScrData* scr)
{
    scrOperation(scr, SCR_OPERATION_AND);
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035e6d0. Equal
static u32 CodeFunc_Eq(ScrData* scr)
{
    scrOperation(scr, SCR_OPERATION_EQ);
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035e710. Not equal
static u32 CodeFunc_Neq(ScrData* scr)
{
    scrOperation(scr, SCR_OPERATION_NEQ);
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035e750. Smaller
static u32 CodeFunc_S(ScrData* scr)
{
    scrOperation(scr, SCR_OPERATION_S);
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035e790. Larger
static u32 CodeFunc_L(ScrData* scr)
{
    scrOperation(scr, SCR_OPERATION_L);
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035e7d0. Smaller equal
static u32 CodeFunc_SE(ScrData* scr)
{
    scrOperation(scr, SCR_OPERATION_SE);
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035e810. Larger equal
static u32 CodeFunc_LE(ScrData* scr)
{
    scrOperation(scr, SCR_OPERATION_LE);
    scr->pc++;

    return CODEFUNC_NEXTINSTR;
}

// FUN_0035e850
static u32 CodeFunc_IF(ScrData* scr)
{
    u32 res;

    K_ASSERT(scr->sp > 0, 804);

    switch (scr->stackTypes[scr->sp - 1])
    {
        case SCR_STACK_TYPE_INTEGER: // fallthrough
        case 2:
            res = PopInt(scr);
            break;

        case SCR_STACK_TYPE_FLOAT: // fallthrough
        case 3:
            if (PopFloat(scr) == 0.0f)
            {
                res = false;
            }
            else
            {
                res = true;
            }
            break;

        case SCR_STACK_TYPE_ADDR:
            K_ABORT("CodeFunc_IF(..) invalid stack type(RET)!!\n", 818);
            res = false;
            break;
        
        default:
            K_ABORT("CodeFunc_IF(..) invalid stack type(?)!!\n", 822);
            res = false;
    }

    if (res)
    {
        scr->pc++;
    }
    else
    {
        scr->pc = scr->labelsContent[scr->instrContent[scr->pc].opOperand16.sOperand].addr;
    }

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
            scr->cmdTimer = 0;

            return SCRTRACE_STOP;
        }

        if (codeFuncRet != CODEFUNC_YIELD)
        {
            if (codeFuncRet == CODEFUNC_NEXTINSTR)
            {
                scr->cmdTimer = 0;
                continue;
            }
        }
        else
        {
            scr->cmdTimer++;
            scr->timer++;

            return SCRTRACE_YIELD;
        }
    }
}

// FUN_0035ed20
s32 scrGetIntPara(s32 paramIdx)
{
    s32 paramSP;
    s32 varIdx;
    f32* f;

    paramSP = sCurrScript->sp - (paramIdx + 1);
    K_ASSERT((paramIdx + 1) <= sCurrScript->sp, 943);

    switch (sCurrScript->stackTypes[paramSP])
    {
        case SCR_STACK_TYPE_INTEGER: // fallthrough
        case SCR_STACK_TYPE_ADDR:    return sCurrScript->stackValues[paramSP].iVal;
        case SCR_STACK_TYPE_FLOAT:   return (s32)sCurrScript->stackValues[paramSP].fVal;

        case 2: return gScrMemory->i[sCurrScript->stackValues[paramSP].iVal];
        case 3:
            f = &gScrMemory->f[sCurrScript->stackValues[paramSP].iVal];
            return (s32)*f;
    }

    K_ABORT("scrGetIntPara(..) invalid stack type!!\n", 956);

    return 0;
}

// FUN_0035ee60
f32 scrGetFloatPara(s32 paramIdx)
{
    s32 paramSP;
    f32* f;

    paramSP = sCurrScript->sp - (paramIdx + 1);
    K_ASSERT((paramIdx + 1) <= sCurrScript->sp, 975);

    switch (sCurrScript->stackTypes[paramSP])
    {
        case SCR_STACK_TYPE_INTEGER: // fallthrough
        case SCR_STACK_TYPE_ADDR:    return (f32)sCurrScript->stackValues[paramSP].iVal;
        case SCR_STACK_TYPE_FLOAT:   return sCurrScript->stackValues[paramSP].fVal;

        case 2: return (f32)gScrMemory->i[sCurrScript->stackValues[paramSP].iVal];
        case 3:
            f = &gScrMemory->f[sCurrScript->stackValues[paramSP].iVal];
            return *f;
    }

    K_ABORT("scrGetFloatPara(..) invalid stack type!!\n", 988);

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
            K_ABORT("scrGetStrPara(..) invalid stack type!!\n", 1016);
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

// FUN_0035f130
u32 scrGetCmdTimer()
{
    return sCurrScript->cmdTimer;
}

// FUN_0035f140
s32 scrGetMesHandleIdx()
{
    return sCurrScript->mesHandleIdx;
}

// FUN_0035f150
ScrData* scrGetCurrent()
{
    return sCurrScript;
}