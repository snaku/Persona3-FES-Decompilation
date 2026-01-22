#include "kwln/kwlnTask.h"
#include "g_data.h"
#include "h_malloc.h"
#include "temporary.h"

void KwlnTask_DetachParent(KwlnTask* task);

// FUN_001939d0. Remove a task from a list by its current state
void KwlnTask_RemoveTaskFromList(KwlnTask* task)
{
    u32 taskState = KWLN_TASK_GET_STATE(task);

    if (taskState == KWLN_TASK_STATE_NULL ||
       (taskState != KWLN_TASK_STATE_DESTROY) &&
       (taskState != KWLN_TASK_STATE_RUNNING) &&
       (taskState != KWLN_TASK_STATE_CREATED))
    {
        // !! LOG !!
        // FUN_0019d400("Process state Invalid!!", "kwlnTask.c", 70);
        return;
    }

    if (task->prev == NULL)
    {
        if (taskState == KWLN_TASK_STATE_DESTROY)
        {
            ctx.destroyTaskHead = task->next;
        }
        else if (taskState == KWLN_TASK_STATE_RUNNING)
        {
            ctx.runningTaskHead = task->next;
        }
        else if (taskState == KWLN_TASK_STATE_CREATED)
        {
            ctx.stagedTaskHead = task->next;
        }
    }
    else 
    {
        task->prev->next = task->next;
    }

    if (task->next == NULL)
    {
        taskState = KWLN_TASK_GET_STATE(task);

        if (taskState == KWLN_TASK_STATE_DESTROY)
        {
            ctx.destroyTaskTail = task->prev;
        }
        else if (taskState == KWLN_TASK_STATE_RUNNING)
        {
            ctx.runningTaskTail = task->prev;
        }
        else if (taskState == KWLN_TASK_STATE_CREATED)
        {
            ctx.stagedTaskTail = task->prev;
        }
    }
    else
    {
        task->next->unk_48 = task->prev;
        task->next->prev = task->prev;
    }

    task->next = NULL;
    task->prev = NULL;

    taskState = KWLN_TASK_GET_STATE(task);
    if (taskState == KWLN_TASK_STATE_DESTROY)
    {
        ctx.numTaskDestroy--;
    }
    else if (taskState == KWLN_TASK_STATE_RUNNING)
    {
        ctx.numTaskRunning--;
    }
    else if (taskState == KWLN_TASK_STATE_CREATED)
    {
        ctx.numTaskStaged--;
    }
}

void KwlnTask_FUN_00193ba0(KwlnTask* task)
{
    // TODO
}

// FUN_00193ec0
u8 KwlnTask_UpdateTask(KwlnTask* task)
{
    // !! TODO !!

    return true;
}

// FUN_00194100
void KwlnTask_UpdateAll()
{
    KwlnTask* currTask = ctx.runningTaskHead;
    KwlnTask* cursor;
    KwlnTask* prevTask;
    u8 updateRes;

    if (ctx.runningTaskHead != NULL)
    {
        while (currTask != NULL)
        {
            prevTask = currTask->prev;
            updateRes = KwlnTask_UpdateTask(currTask);

            if (!updateRes)
            {
                currTask = ctx.runningTaskHead;

                if (prevTask != NULL)
                {
                    cursor = prevTask;

                    while (cursor != NULL && 
                          (KWLN_TASK_GET_STATE(cursor) == KWLN_TASK_STATE_DESTROY))
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

// FUN_001949e0. Called every frame in the game main loop
u8 KwlnTask_Main()
{
    KwlnTask* currTask;
    KwlnTask* nextTask = ctx.stagedTaskHead;

    while (currTask != NULL)
    {
        currTask = nextTask;

        if (nextTask->runningDelay > 0)
        {
            nextTask->runningDelay--;
        }

        nextTask = currTask->next;
        if (nextTask->runningDelay == 0)
        {
            KwlnTask_RemoveTaskFromList(currTask);
            KWLN_TASK_SET_STATE(currTask, KWLN_TASK_STATE_RUNNING);
            KwlnTask_FUN_00193ba0(currTask);

            currTask->unk_24 = 0;
            currTask->taskTimer = 0;
        }
    }

    KwlnTask_UpdateAll();

    nextTask = ctx.destroyTaskHead;
    while (currTask != NULL)
    {
        currTask = nextTask;

        if (currTask->destroyDelay > 0)
        {
            currTask->destroyDelay--;
        }

        nextTask = currTask->next;
        if (currTask->destroyDelay == 0)
        {
            KwlnTask_RemoveTaskFromList(currTask);
            
            if (currTask->destroy != NULL)
            {
                currTask->destroy(currTask);
            }

            KWLN_TASK_RESET_STATE(currTask);
            KwlnTask_RemoveParent(currTask);
            KwlnTask_DetachParent(currTask);

            H_Free((uintptr_t)currTask);
        }
    }

    return true;
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
    KwlnTask* task;
    u8 currChar;
    u32 i;

    if (taskName[0] == '\0')
    {
        P3FES_ASSERT("kwlnTask.c", 1022);
    }

    task = (KwlnTask*)H_Malloc(sizeof(KwlnTask));
    if (task == NULL)
    {
        P3FES_ASSERT("kwlnTask.c", 1032);
        return NULL;
    }

    task->nameChkSum = 0;
    i = 0;
    do
    {
        currChar = taskName[i];
        task->taskName[i] = currChar;
        task->nameChkSum += taskName[i];

        i++;
    } while (currChar != '\0' && i < 23);

    task->taskName[23] = '\0';
    task->stateAndFlags = KWLN_TASK_STATE_NULL;
    task->stateAndFlags = KWLN_TASK_STATE_CREATED;
    task->unk_20 = param_2;
    task->unk_24 = 0;
    task->taskTimer = 0;
    task->runningDelay = 0;
    task->destroyDelay = 2;
    task->update = update;
    task->destroy = destroy;
    task->taskData = taskData;
    task->next = NULL;
    task->prev = NULL;
    task->unk_48 = NULL;
    task->parent = NULL;
    task->child = NULL;
    task->nextChild = NULL;
    task->unk_58 = 0;
    task->unk_5c = 0;
    task->unk_60 = 0;
    task->unk_64 = 0;
    
    KwlnTask_FUN_00193ba0(task);

    if (task->runningDelay == 0)
    {
        KwlnTask_RemoveTaskFromList(task);
        KWLN_TASK_SET_STATE(task, KWLN_TASK_STATE_RUNNING);
        KwlnTask_FUN_00193ba0(task);

        task->unk_24 = 0;
        task->taskTimer = 0;
    }

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

// FUN_00195690
void KwlnTask_DetachParent(KwlnTask* task)
{
    KwlnTask* currTask;
    KwlnTask* next = task->child;

    while (next != NULL)
    {
        if (next->parent == task)
        {
            currTask = next;
        }

        next = next->nextChild;
        currTask->parent = NULL;
        currTask->nextChild = NULL;
    } 
}