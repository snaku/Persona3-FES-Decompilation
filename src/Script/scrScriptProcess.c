#include "Script/scrScriptProcess.h"
#include "g_data.h"

// FUN_0035b570
ScrData* Scr_StartScript(ScrHeader* header, ScrContentEntry* entries,
                               void* prcd, void* labels, ScrInstruction* instr,
                               void* msg, void* strings, u32 prcdIdx)
{
    ScrData* scrData;

    // !!! TODO !!!

    return scrData;
}

// FUN_0035b930
ScrData* Scr_StartScript2(ScrHeader* header, u32 prcdIdx)
{
    // Need to rework a little bit

    u32 i;
    uintptr_t prcdAddr = 0;
    uintptr_t labelsAddr = 0;
    uintptr_t instrAddr = 0;
    uintptr_t msgAddr = 0;
    uintptr_t stringsAddr = 0;

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
                    // !! LOG !!
                    // FUN_0019d400("scrStartScript2(..) Invalid type!!\n","scrScriptProcess.c", 306);
                    return NULL;
                }
                prcdAddr = (uintptr_t)header + currEntry->offset;
            }
        }

        return Scr_StartScript(header, header->entries, (void*)prcdAddr, (void*)labelsAddr, (ScrInstruction*)instrAddr, (void*)msgAddr, (void*)stringsAddr, prcdIdx);
    }

    // !! LOG !!
    // FUN_0019d400("invalid script data!!\n", "scrScriptProcess.c", 280);

    return NULL;
}