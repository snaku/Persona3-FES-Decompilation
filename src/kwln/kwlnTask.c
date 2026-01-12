#include "kwln/kwlnTask.h"
#include "g_data.h"
#include "temporary.h"

// FUN_00193ec0
u8 KwlnTask_UpdateTask(KwlnTask* task)
{
    // !! TODO !!

    return true;
}

// FUN_00194100
void KwlnTask_UpdateAll()
{
    KwlnTask* currTask = ctx.rootProcTask;
    KwlnTask* cursor;
    KwlnTask* prevTask;
    u8 updateRes;

    if (ctx.rootProcTask != NULL)
    {
        while (currTask != NULL)
        {
            prevTask = currTask->prev;
            updateRes = KwlnTask_UpdateTask(currTask);

            if (!updateRes)
            {
                currTask = ctx.rootProcTask;

                if (prevTask != NULL)
                {
                    cursor = prevTask;

                    while (cursor != NULL && (cursor->unk_1c & 0xF) == 3)
                    {
                        prevTask = cursor->prev;
                        if (prevTask == NULL)
                        {
                            cursor = cursor->unk_48;
                            break;
                        }

                        cursor = cursor->prev;
                    }

                    if (cursor != NULL)
                    {
                        currTask = cursor->next;
                    }
                }
            }
            else
            {
                currTask = currTask->next;
            }
        }
    }
}

// FUN_00194b20
KwlnTask* KwlnTask_Create(KwlnTask* parentTask, u8* taskName, u32 param_3, KwlnTask_Update update, KwlnTask_Destroy destroy, void* taskData)
{
    KwlnTask* task = KwlnTask_Init(taskName, param_3, update, destroy, taskData);
    KwlnTask_AddChild(parentTask, task);

    return task;
}

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
    task->parent = NULL;
    task->child = NULL;
    task->nextChild = NULL;
    
    return task;
}

// FUN_00195520
u32 KwlnTask_GetTaskTimer(KwlnTask* task)
{
    return task->taskTimer;
}

// FUN_00195540
void* KwlnTask_GetTaskData(KwlnTask* task)
{
    return task->taskData;
}

// FUN_00195550
void KwlnTask_AddChild(KwlnTask* parentTask, KwlnTask* childTask)
{
    KwlnTask* parent;
    KwlnTask* child;
    KwlnTask* currChild; // current child of the parent
    KwlnTask* lastChild; // last child of the parent

    if (parentTask != NULL)
    {
        child = childTask;
        if (child->parent != NULL)
        {
            KwlnTask_RemoveParent(childTask);
        }

        parent = parentTask;
        currChild = parent->child;

        if (parent->child == NULL)
        {
            parent->child = child;
        }
        else
        {
            while (currChild != NULL)
            {
                lastChild = currChild;
                currChild = lastChild->nextChild;
            }

            lastChild->nextChild = child;
        }

        child->parent = parent;
    }
}

// FUN_001955f0
void KwlnTask_RemoveParent(KwlnTask* childTask)
{
    KwlnTask* parent = childTask->parent;
    KwlnTask* currChild;
    KwlnTask* lastChild;

    if (parent == NULL)
    {
        if (childTask->nextChild != NULL)
        {
            P3FES_ASSERT("kwlnTask.c", 1519);
        }

        return;
    }

    currChild = parent->child;
    if (parent->child == childTask)
    {
        parent->child = childTask->nextChild;
    }
    else
    {
        while (currChild != childTask)
        {
            lastChild = currChild;
            currChild = lastChild->nextChild;
        }

        lastChild->nextChild = childTask->nextChild;
    }

    childTask->parent = NULL;
    childTask->nextChild = NULL;
}