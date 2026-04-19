#include "Script/scrScriptProcess.h"
#include "Script/scrTaskHelper.h"
#include "Script/scrTraceCode.h"
#include "Kosaka/k_assert.h"
#include "itfMesManager.h"
#include "h_dbprt.h"
#include "h_malloc.h"
#include "temporary.h"

static u32 sScrNum;       // 007ce57c
static ScrData* sScrHead; // 007ce580
static ScrData* sScrTail; // 007ce584
ScrData* gCurrScript;     // 007ce5a8. Current script being executed

void scrDestroyTask(KwlnTask* scrTask);
void* scrScriptProcess(KwlnTask* scrTask);

// FUN_0035b570
ScrData* scrStartScript(ScrHeader* header, ScrContentEntry* entries,
                         ScrLblPrcd* prcd, ScrLblPrcd* labels, 
                         ScrInstruction* instr, BmdHeader* msg, 
                         void* strings, s32 prcdIdx)
{
    ScrData* scr;
    s32 mesHandleIdx;
    s32 i;
    char* prcdName;

    if (header == NULL || entries == NULL || prcd == NULL || instr == NULL)
    {
        K_Abort("scrStartScript(..) invalid script!!\n", "scrScriptProcess.c", 155);
        return NULL;
    }

    if (prcdIdx < 0 || entries[SCR_CONTENT_TYPE_PROCEDURE].elementCount <= prcdIdx)
    {
        K_Abort("scrStartScript(..) invalid start procedure!!\n", "scrScriptProcess.c", 159);
        return NULL;
    }

    scr = (ScrData*)H_Malloc(sizeof(ScrData));
    if (scr == NULL)
    {
        K_Abort("scrStartScript(..) chip memory allock error!\n", "scrScriptProcess.c", 169);
        return NULL;
    }

    for (i = 0; prcd->name[i] != '\0'; i++)
    {
        scr->scrName[i] = prcd->name[i];
    }

    scr->instrIdx = prcd[prcdIdx].offset;
    scr->stackIdx = 0;
    for (i = 0; i < SCR_STACK_MAX; i++)
    {
        scr->stackTypes[i] = 0;
        scr->stackValues[i].iVal = 0;
    }

    scr->scrHeader = header;
    scr->entries = entries;
    scr->proceduresContent = prcd;
    scr->labelsContent = labels;
    scr->instrContent = instr;
    scr->msgContentHeader = msg;
    scr->stringsContent = strings;
    scr->prcdIdx = prcdIdx;
    scr->mesHandleIdx = -1;
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
        K_ASSERT(header->localIntNum < 256, 202);

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
        K_ASSERT(header->localFloatNum < 128, 214);

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
        mesHandleIdx = itfMesMngInitialize(msg);
        scr->mesHandleIdx = mesHandleIdx;

        itfMesMngChangeWindowType(mesHandleIdx, 4, 0);
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
    printf("procedure start <%s>\n", prcdName);
    printf("start <%s>\n", prcdName);
    H_Dbprt_FmtLog("procedure start <%s>\n", prcdName);

    return scr;
}

// FUN_0035b930. (Need to rework a little bit)
ScrData* scrStartScript2(ScrHeader* header, u32 prcdIdx)
{
    uintptr_t prcdAddr = 0;
    uintptr_t labelsAddr = 0;
    uintptr_t instrAddr = 0;
    uintptr_t msgAddr = 0;
    uintptr_t stringsAddr = 0;
    u32 i;

    K_ASSERT(header != NULL, 271);

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
                    K_Abort("scrStartScript2(..) Invalid type!!\n", "scrScriptProcess.c", 306);
                    return NULL;
                }
                prcdAddr = (uintptr_t)header + currEntry->offset;
            }
        }

        return scrStartScript(header, header->entries,
                              (ScrLblPrcd*)prcdAddr, (ScrLblPrcd*)labelsAddr, 
                              (ScrInstruction*)instrAddr, (BmdHeader*)msgAddr,
                              (void*)stringsAddr, prcdIdx);
    }

    K_Abort("invalid script data!!\n", "scrScriptProcess.c", 280);

    return NULL;
}

// FUN_0035bb40. Create a script task by a script header
KwlnTask* scrCreateTask(u32 priority, ScrHeader* header, u32 prcdIdx)
{
    ScrData* scr;
    KwlnTask* scrTask;

    scr = scrStartScript2(header, prcdIdx);
    K_ASSERT(scr != NULL, 666);

    scrTask = scrTaskInit(scr->proceduresContent[scr->prcdIdx].name, priority, 1, 1,
                           scrScriptProcess, scrDestroyTask, scr);
    K_ASSERT(scrTask != NULL, 395);

    scr->task = scrTask;

    return scrTask;
}

// FUN_0035bc00. Create a script task by an already loaded '.BF' file in memory and copy it
KwlnTask* scrCreateTaskFromScriptMemory(u32 priority, void* scrMemory, u32 scriptSize, u32 prcdIdx)
{
    void* script;
    ScrData* scr;
    KwlnTask* scrTask;

    script = H_Malloc(scriptSize);
    memset(script, 0, scriptSize);
    memcpy(script, scrMemory, scriptSize);

    scr = scrStartScript2((ScrHeader*)script, prcdIdx);
    K_ASSERT(scr != NULL, 704);

    scr->scriptMemory = script;

    scrTask = scrTaskInit(scr->proceduresContent[scr->prcdIdx].name, priority, 1, 1,
                           scrScriptProcess, scrDestroyTask, scr);
    K_ASSERT(scrTask != NULL, 395);

    scr->task = scrTask;

    return scrTask;
}

// FUN_0035be30
void scrDestroy(ScrData* scr)
{
    printf(scr->proceduresContent[scr->prcdIdx].name);
    printf("end <%s>\n", scr->proceduresContent[scr->prcdIdx].name);
    H_Dbprt_FmtLog("procedure end <%s>\n", scr->proceduresContent[scr->prcdIdx].name);

    if (scr->localInt != NULL)
    {
        H_Free(scr->localInt);
        printf("free local int  memory\n");
    }

    if (scr->localFloat != NULL)
    {
        H_Free(scr->localFloat);
        printf("free local float  memory\n");
    }

    if (scr->mesHandleIdx >= 0)
    {
        itfMesMngDestroyHandle(scr->mesHandleIdx);
        printf("free message handle\n");
    }

    if (scr->scriptMemory != NULL)
    {
        H_Free(scr->scriptMemory);
        printf("free script memory\n");
    }

    if (sScrHead == scr)
    {
        sScrHead = scr->next;
    }
    else 
    {
        scr->prev->next = scr->next;
    }

    if (sScrTail == scr)
    {
        sScrTail = scr->prev;
    }
    else
    {
        scr->next->prev = scr->prev;
    }

    scr->prev = NULL;
    scr->next = NULL;
    sScrNum--;

    H_Free(scr);
}

// FUN_0035c200
void scrDestroyTask(KwlnTask* scrTask)
{
    ScrData* scr;

    scr = scrTaskGetData(scrTask);
    if (scr != NULL)
    {
        scrDestroy(scr);
    }

    scrTaskSetData(scrTask, NULL);
}

// FUN_0035c270
void* scrScriptProcess(KwlnTask* scrTask)
{
    ScrData* scr;

    scr = scrTaskGetData(scrTask);

    switch (scrTraceCode(scr))
    {
        case SCRTRACE_ERROR:
            K_Abort("scrScriptProcess(..) error script!\n", "scrScriptProcess.c", 1120);
            return KWLNTASK_STOP;

        case SCRTRACE_YIELD:  // fallthrough
        default: break;

        case SCRTRACE_STOP:  return KWLNTASK_STOP;
    }

    return KWLNTASK_CONTINUE;
}