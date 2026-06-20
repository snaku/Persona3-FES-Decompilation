#include "dds3Process.h"

// FUN_0035ad80.
// 'unused1' and 'unused2' were probably 'runningDelay' and 'destroyDelay',
// but instead of using 'kwlnTaskInitEx' they used the normal one for some reason
KwlnTask* dds3InitProcess(const char* name,
                          u32 priority,
                          s32 unused1,
                          s32 unused2,
                          KwlnTaskUpdateFunc update,
                          KwlnTaskDestroyFunc destroy,
                          void* workData)
{
    return kwlnTaskInit(name, priority, update, destroy, workData);
}

// FUN_0035adb0
void dds3KillProcess(KwlnTask* task, s32 unused)
{
    kwlnTaskDestroyWithHierarchy(task);
}

// FUN_0035add0
u32 dds3ProcessExists(KwlnTask* task)
{
    return kwlnTaskExists(task);
}

// FUN_0035adf0
u32 dds3GetProcessTimer(KwlnTask* task)
{
    return kwlnTaskGetTimer(task);
}

// FUN_0035ae10
void* dds3GetProcessWorkData(KwlnTask* task)
{
    return kwlnTaskGetWorkData(task);
}

// FUN_0035ae30
void dds3SetProcessWorkData(KwlnTask* task, void* workData)
{
    kwlnTaskSetWorkData(task, workData);
}