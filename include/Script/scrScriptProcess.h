#ifndef SCRSCRIPTPROCESS_H
#define SCRSCRIPTPROCESS_H

#include "Script/scr.h"

typedef struct KwlnTask KwlnTask;

ScrData* scrStartScript(ScrHeader* header, ScrContentEntry* entries, ScrLblPrcd* prcd, ScrLblPrcd* labels, ScrInstruction* instr, BmdHeader* msg, char* strings, s32 prcdIdx);
ScrData* scrStartScript2(ScrHeader* header, u32 prcdIdx);
KwlnTask* scrCreateTaskFromHeader(u32 priority, ScrHeader* header, u32 prcdIdx);
KwlnTask* scrCreateTaskFromScriptMemory(u32 priority, void* scrMemory, u32 scriptSize, u32 prcdIdx);
ScrData* scrStartScriptFirstPrcd(ScrHeader* header);
KwlnTask* scrCreateTask(u32 priority, ScrHeader* header, ScrContentEntry* entries, ScrLblPrcd* prcd, ScrLblPrcd* labels,  ScrInstruction* instr, BmdHeader* msg,  void* strings, s32 prcdIdx);
void scrReleaseScript(ScrData* scr);
void scrAllReleaseScript();
s32 scrFindPrcdIdxByName(ScrHeader* header, const char* name);
void scrForceTraceCode(ScrData* scr);

#endif