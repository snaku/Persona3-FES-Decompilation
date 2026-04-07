#ifndef SCRSCRIPTPROCESS_H
#define SCRSCRIPTPROCESS_H

#include "Script/scr.h"

typedef struct KwlnTask KwlnTask;

extern ScrData* gCurrScript;

ScrData* scrStartScript(ScrHeader* header, ScrContentEntry* entries, ScrLblPrcd* prcd, ScrLblPrcd* labels, ScrInstruction* instr, BmdHeader* msg, void* strings, s32 prcdIdx);
ScrData* scrStartScript2(ScrHeader* header, u32 prcdIdx);
KwlnTask* scrCreateTask(u32 priority, ScrHeader* header, u32 prcdIdx);
KwlnTask* scrCreateTaskFromScriptMemory(u32 priority, void* scrMemory, u32 scriptSize, u32 prcdIdx);
void scrDestroy(ScrData* scr);

#endif