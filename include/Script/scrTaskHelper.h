#ifndef SCRTASKHELPER_H
#define SCRTASKHELPER_H

#include "kwln/kwlnTask.h"

typedef struct ScrData ScrData;

KwlnTask* scrTaskInit(const char* name, u32 priority, s32 unused1, s32 unused2, KwlnTaskUpdateFunc update, KwlnTaskDestroyFunc destroy, ScrData* scr);
ScrData* scrTaskGetData(KwlnTask* scrTask);
void scrTaskSetData(KwlnTask* scrTask, ScrData* scr);

#endif