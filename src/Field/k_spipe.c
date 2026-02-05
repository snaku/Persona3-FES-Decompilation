#include "kwln/kwlnTask.h"
#include "Field/k_spipe.h"
#include "rw/rwcore.h"
#include "temporary.h"
#include "g_data.h"

// FUN_00199520
void* FldSPipe_Update3DDrwBeginTask(KwlnTask* draw3DBeginTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_001995f0
void* FldSPipe_Update3DDrwEndTask(KwlnTask* draw3DEndTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_001996c0
KwlnTask* FldSPipe_Create3DDrwBeginTask(KwlnTask* draw3DTask)
{
    return KwlnTask_Create(draw3DTask, "3D Draw Begin", 2098, FldSPipe_Update3DDrwBeginTask, NULL, NULL);
}

// FUN_00199700
KwlnTask* FldSPipe_Create3DDrwEndTask(KwlnTask* draw3DTask)
{
    return KwlnTask_Create(draw3DTask, "3D Draw End", 4167, FldSPipe_Update3DDrwEndTask, NULL, NULL);
}