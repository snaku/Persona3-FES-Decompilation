#include "kwln/kwlnTask.h"
#include "g_data.h"

// FUN_00194c50
KwlnTask* KwlnTask_Init(u8* taskName, u32 param_2, KwlnTask_Update update, KwlnTask_Destroy destroy, void* taskData)
{
    // TODO !!

    KwlnTask* task;

    if (taskName[0] == '\0')
    {
        P3FES_ASSERT("kwlnTask.c", 1022);
    }

    // !! ALLOC !!
    // task = FUN_00191af0(sizeof(KwlnTask)); 

    if (task == NULL)
    {
        P3FES_ASSERT("kwlnTask.c", 1032);
        return NULL;
    }

    task->unk_20 = param_2;
    task->unk_24 = 0;
    task->taskTimer = 0;
    task->update = update;
    task->destroy = destroy;
    task->taskData = taskData;
    task->next = NULL;
    task->prev = NULL;
    task->unk_48 = NULL;

    return task;
}