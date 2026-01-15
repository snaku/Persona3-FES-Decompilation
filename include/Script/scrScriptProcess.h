#ifndef SCRSCRIPTPROCESS_H
#define SCRSCRIPTPROCESS_H

#include "Script/scr.h"

ProcedureData* Scr_StartScript(ScrHeader* header, ScrContentEntry* entries, uintptr_t prcdAddr, uintptr_t labelsAddr, uintptr_t instrAddr, uintptr_t msgAddr, uintptr_t stringsAddr, u32 prcdIdx);
ProcedureData* Scr_StartScript2(ScrHeader* header, u32 prcdIdx);

#endif