#include "Script/scrTaskHelper.h"

// FUN_0035ad80.
// 'unused1' and 'unused2' were probably 'runningDelay' and 'destroyDelay',
// but instead of using 'kwlnTaskInitEx' they used the normal one for some reason
KwlnTask* ScrTask_Init(const char* name, u32 priority, s32 unused1, s32 unused2, KwlnTaskUpdateFunc update, KwlnTaskDestroyFunc destroy, ScrData* scr)
{
    return kwlnTaskInit(name, priority, update, destroy, (void*)scr);
}

// FUN_0035ae10
ScrData* ScrTask_GetData(KwlnTask* scrTask)
{
    return (ScrData*)kwlnTaskGetWorkData(scrTask);
}

// FUN_0035ae30
void ScrTask_SetData(KwlnTask* scrTask, ScrData* scr)
{
    kwlnTaskSetWorkData(scrTask, (void*)scr);
}