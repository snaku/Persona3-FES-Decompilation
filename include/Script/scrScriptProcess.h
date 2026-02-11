#ifndef SCRSCRIPTPROCESS_H
#define SCRSCRIPTPROCESS_H

#include "Script/scr.h"

typedef struct KwlnTask KwlnTask;

ScrData* Scr_StartScript(ScrHeader* header, ScrContentEntry* entries, ScrLblPrcd* prcd, ScrLblPrcd* labels, ScrInstruction* instr, void* msg, void* strings, u32 prcdIdx);
ScrData* Scr_StartScript2(ScrHeader* header, u32 prcdIdx);
KwlnTask* Scr_CreateTask(u32 priority, ScrHeader* header, u32 prcdIdx);

#endif