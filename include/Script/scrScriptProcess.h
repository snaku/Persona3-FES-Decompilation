#ifndef SCRSCRIPTPROCESS_H
#define SCRSCRIPTPROCESS_H

#include "Script/scr.h"

ScrData* Scr_StartScript(ScrHeader* header, ScrContentEntry* entries, void* prcdAddr, void* labelsAddr, ScrInstructionContent* instrAddr, void* msgAddr, void* stringsAddr, u32 prcdIdx);
ScrData* Scr_StartScript2(ScrHeader* header, u32 prcdIdx);

#endif