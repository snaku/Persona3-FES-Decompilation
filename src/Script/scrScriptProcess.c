#include "Script/scrScriptProcess.h"
#include "Script/scrTaskHelper.h"
#include "Script/scrTraceCode.h"
#include "g_data.h"

ScrData* gCurrScript; // 007ce5a8. Current script being executed

void Scr_DestroyTask(KwlnTask* scrTask);
void* Scr_UpdateTask(KwlnTask* scrTask);

// FUN_0035b570
ScrData* Scr_StartScript(ScrHeader* header, ScrContentEntry* entries,
                         ScrLblPrcd* prcd, ScrLblPrcd* labels, 
                         ScrInstruction* instr, ScrMsgHeader* msg, 
                         void* strings, u32 prcdIdx)
{
    ScrData* scrData;

    // !!! TODO !!!

    return scrData;
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

        return Scr_StartScript(header, header->entries,
                              (ScrLblPrcd*)prcdAddr, (ScrLblPrcd*)labelsAddr, 
                              (ScrInstruction*)instrAddr, (ScrMsgHeader*)msgAddr,
                              (void*)stringsAddr, prcdIdx);
    }

    FUN_0019d400("invalid script data!!\n", "scrScriptProcess.c", 280);

    return NULL;
}

// FUN_0035bb40
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