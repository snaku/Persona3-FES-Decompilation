#ifndef SCRSCRIPTPROCESS_H
#define SCRSCRIPTPROCESS_H

#include "Script/scr.h"

ProcedureData* Scr_StartScript(ScrHeader* header, ScrContentEntry* entries, void* prcdAddr, void* labelsAddr, void* instrAddr, void* msgAddr, void* stringsAddr, u32 prcdIdx);
ProcedureData* Scr_StartScript2(ScrHeader* header, u32 prcdIdx);

#endif