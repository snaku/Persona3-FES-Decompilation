#ifndef SCRTASKHELPER_H
#define SCRTASKHELPER_H

#include "kwln/kwlnTask.h"

typedef struct ScrData ScrData;

KwlnTask* ScrTask_Init(const char* name, u32 priority, s32 unused1, s32 unused2, KwlnTask_UpdateFunc update, KwlnTask_DestroyFunc destroy, ScrData* scr);
ScrData* ScrTask_GetData(KwlnTask* scrTask);

#endif