#ifndef SCRSCRIPTPROCESS_H
#define SCRSCRIPTPROCESS_H

#include "Script/scr.h"

typedef struct KwlnTask KwlnTask;

extern ScrData* gCurrScript;

ScrData* Scr_StartScript(ScrHeader* header, ScrContentEntry* prcdEntry, ScrLblPrcd* prcd, ScrLblPrcd* labels, ScrInstruction* instr, BmdHeader* msg, void* strings, s32 prcdIdx);
ScrData* Scr_StartScript2(ScrHeader* header, u32 prcdIdx);
KwlnTask* Scr_CreateTask(u32 priority, ScrHeader* header, u32 prcdIdx);
KwlnTask* Scr_CreateTaskFromScriptCopy(u32 priority, void* baseScript, u32 scriptSize, u32 prcdIdx);
void Scr_Destroy(ScrData* scr);

#endif