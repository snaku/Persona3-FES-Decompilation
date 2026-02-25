#include "Script/scrScriptProcess.h"
#include "Script/scrTaskHelper.h"
#include "Script/scrTraceCode.h"
#include "itfMesManager.h"
#include "h_malloc.h"
#include "g_data.h"
#include "temporary.h"

static u32 sScrNum;       // 007ce57c
static ScrData* sScrHead; // 007ce580
static ScrData* sScrTail; // 007ce584
ScrData* gCurrScript;     // 007ce5a8. Current script being executed

void Scr_DestroyTask(KwlnTask* scrTask);
void* Scr_UpdateTask(KwlnTask* scrTask);

// FUN_0035b570
ScrData* Scr_StartScript(ScrHeader* header, ScrContentEntry* prcdEntry,
                         ScrLblPrcd* prcd, ScrLblPrcd* labels, 
                         ScrInstruction* instr, BmdHeader* msg, 
                         void* strings, s32 prcdIdx)
{
    ScrData* scr;
    ItfMes* itfMes;
    s32 i;
    char* prcdName;

    if (header == NULL || prcdEntry == NULL || prcd == NULL || instr == NULL)
    {
        FUN_0019d400("scrStartScript(..) invalid script!!\n", "scrScriptProcess.c", 155);
        return NULL;
    }

    if (prcdIdx < 0 || prcdEntry->elementCount <= prcdIdx)
    {
        FUN_0019d400("scrStartScript(..) invalid start procedure!!\n", "scrScriptProcess.c", 159);
        return NULL;
    }

    scr = (ScrData*)H_Malloc(sizeof(ScrData));
    if (scr == NULL)
    {
        FUN_0019d400("scrStartScript(..) chip memory allock error!\n", "scrScriptProcess.c", 169);
        return NULL;
    }

    for (i = 0; prcd->name[i] != '\0'; i++)
    {
        scr->scrName[i] = prcd->name[i];
    }

    scr->instrIdx = prcd[prcdIdx].offset;
    scr->stackIdx = 0;
    for (i = 0; i < SCR_MAX_STACK_SIZE; i++)
    {
        scr->stackTypes[i] = 0;
        scr->stackValues[i].iVal = 0;
    }

    scr->scrHeader = header;
    scr->prcdEntry = prcdEntry;
    scr->proceduresContent = prcd;
    scr->labelsContent = labels;
    scr->instrContent = instr;
    scr->msgContentHeader = msg;
    scr->stringsContent = strings;
    scr->prcdIdx = prcdIdx;
    scr->itfMes = (ItfMes*)-1;
    scr->unk_d0 = 0;
    scr->unk_d4 = 0;
    scr->scriptMemory = NULL;
    scr->localInt = NULL;
    scr->localFloat = NULL;
    scr->task = NULL;
    scr->prev = NULL;
    scr->next = NULL;
    scr->unk_f0 = 0;

    if (header->localIntNum > 0)
    {
        if (header->localIntNum >= 256)
        {
            P3FES_ASSERT("scrScriptProcess.c", 202);
        }

        scr->localInt = (s32*)H_Malloc(header->localIntNum * sizeof(s32));
        for (i = 0; i < header->localIntNum; i++)
        {
            scr->localInt[i] = 0;
        }
    }
    else
    {
        scr->localInt = NULL;
    }

    if (header->localFloatNum > 0)
    {
        if (header->localFloatNum >= 128)
        {
            P3FES_ASSERT("scrScriptProcess.c", 214);
        }

        scr->localFloat = (f32*)H_Malloc(header->localFloatNum * sizeof(f32));
        for (i = 0; i < header->localFloatNum; i++)
        {
            scr->localFloat[i] = 0.0f;
        }
    }
    else
    {
        scr->localFloat = NULL;
    }

    if (msg != NULL)
    {
        itfMes = ItfMesMng_Initialize(msg);
        scr->itfMes = itfMes;

        ItfMesMng_ChangeWindowType(itfMes, 4, 0);
    }

    if (sScrHead == NULL)
    {
        sScrHead = scr;
        sScrTail = scr;
        scr->prev = NULL;
        scr->next = NULL;
    }
    else
    {
        scr->prev = sScrTail;
        sScrTail->next = scr;
        scr->next = NULL;
        sScrTail = scr;
    }
    sScrNum++;

    prcdName = prcd->name;
    P3FES_LOG3("procedure start <%s>\n", prcdName);
    P3FES_LOG3("start <%s>\n", prcdName);
    P3FES_LOG1("procedure start <%s>\n", prcdName);

    return scr;
}

// FUN_0035b930. (Need to rework a little bit)
ScrData* Scr_StartScript2(ScrHeader* header, u32 prcdIdx)
{
    uintptr_t prcdAddr = 0;
    uintptr_t labelsAddr = 0;
    uintptr_t instrAddr = 0;
    uintptr_t msgAddr = 0;
    uintptr_t stringsAddr = 0;
    u32 i;

    if (header == NULL)
    {
        P3FES_ASSERT("scrScripProcess.c", 271);
    }

    if (header->magic[0] == 'F' && header->magic[1] == 'L' &&
        header->magic[2] == 'W' && header->magic[3] == '0')
    {
        for (i = 0; i < header->totalEntries; i++)
        {
            ScrContentEntry* currEntry = &header->entries[i];

            if (currEntry->contentType == SCR_CONTENT_TYPE_STRINGS)
            {
                stringsAddr = (uintptr_t)header + currEntry->offset;
            }
            else if (currEntry->contentType == SCR_CONTENT_TYPE_MSG)
            {
                if (currEntry->elementCount != 0)
                {
                    msgAddr = (uintptr_t)header + currEntry->offset;
                }
            }
            else if (currEntry->contentType == SCR_CONTENT_TYPE_INSTR)
            {
                instrAddr = (uintptr_t)header + currEntry->offset;
            }
            else if (currEntry->contentType == SCR_CONTENT_TYPE_LABEL)
            {
                labelsAddr = (uintptr_t)header + currEntry->offset;
            }
            else
            {
                if (currEntry->contentType != SCR_CONTENT_TYPE_PROCEDURE)
                {
                    FUN_0019d400("scrStartScript2(..) Invalid type!!\n", "scrScriptProcess.c", 306);
                    return NULL;
                }
                prcdAddr = (uintptr_t)header + currEntry->offset;
            }
        }

        return Scr_StartScript(header, &header->entries[SCR_CONTENT_TYPE_PROCEDURE],
                              (ScrLblPrcd*)prcdAddr, (ScrLblPrcd*)labelsAddr, 
                              (ScrInstruction*)instrAddr, (BmdHeader*)msgAddr,
                              (void*)stringsAddr, prcdIdx);
    }

    FUN_0019d400("invalid script data!!\n", "scrScriptProcess.c", 280);

    return NULL;
}

// FUN_0035bb40. Create a script task by a script header
KwlnTask* Scr_CreateTask(u32 priority, ScrHeader* header, u32 prcdIdx)
{
    ScrData* scr;
    KwlnTask* scrTask;

    scr = Scr_StartScript2(header, prcdIdx);
    if (scr == NULL)
    {
        P3FES_ASSERT("scrScriptProcess.c", 666);
    }

    scrTask = ScrTask_Init(scr->proceduresContent[scr->prcdIdx].name, priority, 1, 1,
                           Scr_UpdateTask, Scr_DestroyTask, scr);
    
    if (scrTask == NULL)
    {
        P3FES_ASSERT("scrScriptProcess.c", 395);
    }

    scr->task = scrTask;

    return scrTask;
}

// FUN_0035bc00. Create a script task by an already loaded '.BF' file in memory and copy it
KwlnTask* Scr_CreateTaskFromScriptCopy(u32 priority, void* baseScript, u32 scriptSize, u32 prcdIdx)
{
    void* script;
    ScrData* scr;
    KwlnTask* scrTask;

    script = (void*)H_Malloc(scriptSize);
    P3FES_Memset(script, 0, scriptSize);
    P3FES_Memcpy(script, baseScript, scriptSize);

    scr = Scr_StartScript2((ScrHeader*)script, prcdIdx);
    if (scr == NULL)
    {
        P3FES_ASSERT("scrScriptProcess.c", 704);
    }

    scr->scriptMemory = script;

    scrTask = ScrTask_Init(scr->proceduresContent[scr->prcdIdx].name, priority, 1, 1,
                           Scr_UpdateTask, Scr_DestroyTask, scr);
    
    if (scrTask == NULL)
    {
        P3FES_ASSERT("scrScriptProcess.c", 395);
    }

    scr->task = scrTask;

    return scrTask;
}

// FUN_0035c200
void Scr_DestroyTask(KwlnTask* scrTask)
{
    // TODO
}

// FUN_0035c270
void* Scr_UpdateTask(KwlnTask* scrTask)
{
    ScrData* scr;
    u32 execOpCodeRes;

    scr = ScrTask_GetData(scrTask);
    execOpCodeRes = Scr_ExecOpCode(scr);

    switch (execOpCodeRes)
    {
        case 0:
            FUN_0019d400("scrScriptProcess(..) error script!\n", "scrScriptProcess.c", 1120);
            return KWLN_TASK_STOP;
        case 1:  // fallthrough
        default: break;
        case 2:  return KWLN_TASK_STOP;
    }

    return KWLN_TASK_CONTINUE;
}