#include "Script/scrScriptProcess.h"
#include "Script/scrTraceCode.h"
#include "Kosaka/k_assert.h"
#include "itfMesManager.h"
#include "dds3Process.h"
#include "h_dbprt.h"
#include "h_malloc.h"
#include "datScript.h"
#include "temporary.h"

#define SCR_LOCALINT_MAX   256
#define SCR_LOCALFLOAT_MAX 128

static ScrData* sScrTail; // 007ce584
static ScrData* sScrHead; // 007ce580
static u32 sScrNo;        // 007ce57c

void scrDestroyTask(KwlnTask* scrTask);
void* scrScriptProcess(KwlnTask* scrTask);

// FUN_0035b570
ScrData* scrStartScript(ScrHeader* header,
                        ScrContentEntry* entries,
                        ScrLblPrcd* prcd,
                        ScrLblPrcd* labels,
                        ScrInstruction* instr,
                        BmdHeader* msg,
                        char* strings,
                        s32 prcdIdx)
{
    ScrData* scr;
    s32 mesHandleIdx;
    s32 i;
    char* prcdName;
    s32 j;
    s8* stackType;
    ScrValues* stackValue;
    s32 k;

    if (header == NULL || entries == NULL || prcd == NULL || instr == NULL)
    {
        K_Abort("scrStartScript(..) invalid script!!\n", "scrScriptProcess.c", 155);
        return NULL;
    }

    if (prcdIdx < 0 || prcdIdx >= entries[SCR_CONTENT_TYPE_PROCEDURE].elementCount)
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

    i = 0;
    prcdName = prcd[prcdIdx].name;
    while ((scr->scrName[i] = prcdName[i]) != '\0')
    {
        i++;
    }

    scr->pc = prcd[prcdIdx].addr;
    scr->sp = 0;
    for (j = 0; j < SCR_STACK_MAX; j++)
    {
        stackType = &scr->stackTypes[j];
        stackValue = &scr->stackValues[j];

        *stackType = 0;
        stackValue->iVal = 0;
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
    scr->timer = 0;
    scr->cmdTimer = 0;
    scr->scriptMemory = NULL;
    scr->localInt = NULL;
    scr->localFloat = NULL;
    scr->task = NULL;
    scr->prev = NULL;
    scr->next = NULL;
    scr->unk_f0 = 0;

    if (header->localIntNum > 0)
    {
        K_ASSERT(header->localIntNum < SCR_LOCALINT_MAX, 202);

        scr->localInt = (s32*)H_Malloc(header->localIntNum * sizeof(s32));
        for (k = 0; k < header->localIntNum; k++)
        {
            scr->localInt[k] = 0;
        }
    }
    else
    {
        scr->localInt = NULL;
    }

    if (header->localFloatNum > 0)
    {
        K_ASSERT(header->localFloatNum < SCR_LOCALFLOAT_MAX, 214);

        scr->localFloat = (f32*)H_Malloc(header->localFloatNum * sizeof(f32));
        for (k = 0; k < header->localFloatNum; k++)
        {
            scr->localFloat[k] = 0.0f;
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

    if (sScrTail == NULL)
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
    sScrNo++;

    printf("procedure start <%s>\n", prcd[prcdIdx].name);
    printf("start <%s>\n", prcd[prcdIdx].name);
    H_Dbprt_FmtLog("procedure start <%s>\n", prcd[prcdIdx].name);

    return scr;
}

// FUN_0035b930
ScrData* scrStartScript2(ScrHeader* header, u32 prcdIdx)
{
    ScrLblPrcd* prcd;
    ScrLblPrcd* labels;
    ScrInstruction* instr;
    BmdHeader* msgs;
    char* strings;
    ScrContentEntry* entries;
    s32 totalEntries;
    s32 i;
    ScrContentEntry* currEntry;

    prcd = NULL;
    labels = NULL;
    instr = NULL;
    msgs = NULL;
    strings = NULL;

    K_ASSERT(header != NULL, 271);

    entries = header->entries;

    if (header->magic[0] != 'F' || header->magic[1] != 'L' ||
        header->magic[2] != 'W' || header->magic[3] != '0')
    {
        K_Abort("invalid script data!!\n", "scrScriptProcess.c", 280);
        return NULL;
    }

    i = 0;
    totalEntries = header->totalEntries;
    // TODO: load 1, 2, 3 and 4 in a2, a3, t0 and t1 before the loop
    for (; i < totalEntries; i++)
    {
        currEntry = &entries[i];

        switch (currEntry->contentType)
        {
            case SCR_CONTENT_TYPE_PROCEDURE:
                prcd = (ScrLblPrcd*)((uintptr_t)header + currEntry->offset);
                break;
            case SCR_CONTENT_TYPE_LABEL:
                labels = (ScrLblPrcd*)((uintptr_t)header + currEntry->offset);
                break;
            case SCR_CONTENT_TYPE_INSTR:
                instr = (ScrInstruction*)((uintptr_t)header + currEntry->offset);
                break;
            case SCR_CONTENT_TYPE_MSG:
                if (currEntry->elementCount != 0)
                {
                    msgs = (BmdHeader*)((uintptr_t)header + currEntry->offset);
                }
                break;
            case SCR_CONTENT_TYPE_STRINGS:
                strings = (char*)((uintptr_t)header + currEntry->offset);
                break;
            
            default: 
                K_Abort("scrStartScript2(..) Invalid type!!\n", "scrScriptProcess.c", 306);
                return NULL;
        }
    }

    return scrStartScript(header,
                          entries,
                          prcd,
                          labels,
                          instr,
                          msgs,
                          strings,
                          prcdIdx);
}

// FUN_0035bb40. Create a script task by a script header
KwlnTask* scrCreateTaskFromHeader(u32 priority, ScrHeader* header, u32 prcdIdx)
{
    ScrData* scr;
    KwlnTask* scrTask;

    scr = scrStartScript2(header, prcdIdx);
    K_ASSERT(scr != NULL, 666);

    scrTask = dds3InitProcess(scr->proceduresContent[scr->prcdIdx].name,
                              priority, 
                              1, 
                              1,
                              scrScriptProcess, 
                              scrDestroyTask, 
                              scr);
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

    scrTask = dds3InitProcess(scr->proceduresContent[scr->prcdIdx].name,
                              priority, 
                              1, 
                              1,
                              scrScriptProcess, 
                              scrDestroyTask, 
                              scr);
    K_ASSERT(scrTask != NULL, 395);

    scr->task = scrTask;

    return scrTask;
}

// FUN_0035bd20
ScrData* scrStartScriptFirstPrcd(ScrHeader* header)
{
    return scrStartScript2(header, 0);
}

// FUN_0035bd50
KwlnTask* scrCreateTask(u32 priority, ScrHeader* header, ScrContentEntry* entries,
                        ScrLblPrcd* prcd, ScrLblPrcd* labels, 
                        ScrInstruction* instr, BmdHeader* msg, 
                        void* strings, s32 prcdIdx)
{
    ScrData* scr;
    KwlnTask* scrTask;

    scr = scrStartScript(header, entries, prcd, labels, instr, msg, strings, prcdIdx);
    K_ASSERT(scr != NULL, 784);

    scrTask = dds3InitProcess(scr->proceduresContent[scr->prcdIdx].name,
                              priority,
                              1,
                              1,
                              scrScriptProcess,
                              scrDestroyTask,
                              scr);
    K_ASSERT(scrTask != NULL, 395);

    scr->task = scrTask;

    return scrTask;
}

// FUN_0035be30
void scrReleaseScript(ScrData* scr)
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
    sScrNo--;

    H_Free(scr);
}

// FUN_0035bfb0
void scrAllReleaseScript()
{
    ScrData* curr;
    ScrData* next;

    printf("before = %d\n", sScrNo);

    curr = sScrHead;
    while (curr != NULL)
    {
        printf(curr->scrName);

        next = curr->next;

        if (!datScript003112c0(curr)) // ?
        {
            if (curr->task != NULL)
            {
                printf("dds3KillProcess\n");
                dds3KillProcess(curr->task, 0);
            }
            else
            {
                printf("scrReleaseScript\n");
                scrReleaseScript(curr);
            }
        }

        curr = next;
    }

    printf("after = %d\n", sScrNo);
}

// FUN_0035c090
s32 scrFindPrcdIdxByName(ScrHeader* header, const char* name)
{
    ScrContentEntry* entries;
    s32 totalEntries;
    s32 i;
    ScrContentEntry* currEntry;
    ScrLblPrcd* prcd;
    s32 j;
    s32 elementCount;

    prcd = NULL;
    if (header == NULL)
    {
        return -1;
    }

    entries = header->entries;
    i = 0;
    totalEntries = header->totalEntries;
    for (; i < totalEntries; i++)
    {
        currEntry = &entries[i];

        if (currEntry->contentType == SCR_CONTENT_TYPE_PROCEDURE)
        {
            prcd = (ScrLblPrcd*)((uintptr_t)header + currEntry->offset);
            break;
        }
    }

    if (prcd == NULL)
    {
        return -1;
    }

    j = 0;
    currEntry = &entries[i];
    for (; j < currEntry->elementCount; j++)
    {
        if (strcmp(prcd[j].name, name) == 0)
        {
            return j;
        }
    }

    return -1;
}

// FUN_0035c200
void scrDestroyTask(KwlnTask* scrTask)
{
    ScrData* scr;

    scr = (ScrData*)dds3GetProcessWorkData(scrTask);
    if (scr != NULL)
    {
        scrReleaseScript(scr);
    }

    dds3SetProcessWorkData(scrTask, NULL);
}

// FUN_0035c250
void scrForceTraceCode(ScrData* scr)
{
    scrTraceCode(scr);
}

// FUN_0035c270
void* scrScriptProcess(KwlnTask* scrTask)
{
    ScrData* scr;

    scr = (ScrData*)dds3GetProcessWorkData(scrTask);

    switch (scrTraceCode(scr))
    {
        case SCRTRACE_ERROR:
            K_Abort("scrScriptProcess(..) error script!\n", "scrScriptProcess.c", 1120);
            return KWLNTASK_STOP;

        case SCRTRACE_YIELD:  // fallthrough
        default:              break;

        case SCRTRACE_STOP: return KWLNTASK_STOP;
    }

    return KWLNTASK_CONTINUE;
}