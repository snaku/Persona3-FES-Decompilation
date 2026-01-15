#ifndef SCRSCRIPTPROCESS_H
#define SCRSCRIPTPROCESS_H

#include "Script/scr.h"

ProcedureData* Scr_StartScript(ScrHeader* header, ScrContentEntry* entries, uintptr_t prdcAddr, uintptr_t labelsAddr, uintptr_t instrAddr, uintptr_t msgAddr, uintptr_t stringsAddr, void* unkStruct);
ProcedureData* Scr_StartScript2(ScrHeader* header, void* unkStruct);

#endif