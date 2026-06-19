#ifndef DDS3PROCESS_H
#define DDS3PROCESS_H

#include "kwln/kwlnTask.h"

KwlnTask* dds3InitProcess(const char* name, u32 priority, s32 unused1, s32 unused2, KwlnTaskUpdateFunc update, KwlnTaskDestroyFunc destroy, void* workData);
void dds3KillProcess(KwlnTask* task, s32 unused);
void* dds3GetProcessWorkData(KwlnTask* task);
void dds3SetProcessWorkData(KwlnTask* task, void* workData);

#endif