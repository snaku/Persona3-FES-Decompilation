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
        FUN_0019d400("Process stat Invalid!!", "kwlnTask.c", 70);
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

// FUN_00193ba0. Add a task from a list by its current state
void KwlnTask_AddToList(KwlnTask* task)
{
    KwlnTask* list;
    u32 taskState = KWLN_TASK_GET_STATE(task);

    switch (taskState)
    {
        case KWLN_TASK_STATE_CREATED: list = ctx.stagedTaskHead;  break;
        case KWLN_TASK_STATE_RUNNING: list = ctx.runningTaskHead; break;
        case KWLN_TASK_STATE_DESTROY: list = ctx.destroyTaskHead; break;
        case KWLN_TASK_STATE_NULL: // fallthrough
        default: FUN_0019d400("Process stat Invalid!!", "kwlnTask.c", 143); return;
    }

    if (list == NULL)
    {
        switch (taskState)
        {
            case KWLN_TASK_STATE_CREATED:
                ctx.stagedTaskHead = task;
                ctx.stagedTaskTail = task;
                break;
            case KWLN_TASK_STATE_RUNNING:
                ctx.runningTaskHead = task;
                ctx.runningTaskTail = task;
                break;
            case KWLN_TASK_STATE_DESTROY:
                ctx.destroyTaskHead = task;
                ctx.destroyTaskTail = task;
                break;
        }

        task->unk_48 = NULL;
        task->prev = NULL;
        task->next = NULL;
    }
    else
    {
        while (list != NULL)
        {
            if (task->priority < list->priority)
            {
                if (list->prev == NULL)
                {
                    switch (taskState)
                    {
                        case KWLN_TASK_STATE_CREATED: ctx.stagedTaskHead = task;  break;
                        case KWLN_TASK_STATE_RUNNING: ctx.runningTaskHead = task; break;
                        case KWLN_TASK_STATE_DESTROY: ctx.destroyTaskHead = task; break;
                    }

                    task->prev = NULL;
                    task->next = list;
                    list->unk_48 = task;
                    list->prev = task;
                }
                else
                {
                    list->prev->next = task;
                    task->unk_48 = list->prev;
                    task->prev = list->prev;
                    task->next = list;
                    list->unk_48 = task;
                    list->prev = task;
                }

                break;
            }

            list = list->next;
        }

        if (list == NULL)
        {
            taskState = KWLN_TASK_GET_STATE(task); // again
            switch (taskState)
            {
                case KWLN_TASK_STATE_CREATED: 
                    ctx.stagedTaskTail->next = task;
                    task->unk_48 = ctx.stagedTaskTail;
                    task->prev = ctx.stagedTaskTail;
                    ctx.stagedTaskTail = task;
                    break;
                case KWLN_TASK_STATE_RUNNING: 
                    ctx.runningTaskTail->next = task;
                    task->unk_48 = ctx.runningTaskTail;
                    task->prev = ctx.runningTaskTail;
                    ctx.runningTaskTail = task;
                    break;
                case KWLN_TASK_STATE_DESTROY: 
                    ctx.destroyTaskTail->next = task;
                    task->unk_48 = ctx.destroyTaskTail;
                    task->prev = ctx.destroyTaskTail;
                    ctx.destroyTaskTail = task;
                    break;
            }

            task->next = NULL;
        }
    }

    taskState = KWLN_TASK_GET_STATE(task); // again
    switch (taskState)
    {
        case KWLN_TASK_STATE_CREATED:
            ctx.numTaskStaged++;
            if (ctx.numTaskStaged > 10000)
            {
                P3FES_ASSERT("kwlnTask.c", 226);
            }
            break;
        case KWLN_TASK_STATE_RUNNING:
            ctx.numTaskRunning++;
            if (ctx.numTaskRunning > 10000)
            {
                P3FES_ASSERT("kwlnTask.c", 230);
            }
            break;
        case KWLN_TASK_STATE_DESTROY:
            ctx.numTaskDestroy++;
            if (ctx.numTaskDestroy > 10000)
            {
                P3FES_ASSERT("kwlnTask.c", 234);
            }
            break;
    }
}

// FUN_00193ec0
u8 KwlnTask_Update(KwlnTask* task)
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
            updateRes = KwlnTask_Update(currTask);

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

// FUN_00194280. Change a task state to 'KWLN_TASK_STATE_DESTROY'. If 'destroyTask' is 0, destroy the task immediately
void KwlnTask_Destroy(KwlnTask* task)
{
    u32 state;

    state = KWLN_TASK_GET_STATE(task);

    switch (state)
    {
        case KWLN_TASK_STATE_DESTROY: return;
        case KWLN_TASK_STATE_NULL: 
            P3FES_LOG3("Process stat Invalid!!\n");
            P3FES_ASSERT("kwlnTask.c", 574);
            break;
        case KWLN_TASK_STATE_CREATED: // fallthrough
        case KWLN_TASK_STATE_RUNNING:
            KwlnTask_RemoveTaskFromList(task);
            KWLN_TASK_SET_STATE(task, KWLN_TASK_STATE_DESTROY);
            KwlnTask_AddToList(task);

            if (task->destroyDelay == 0)
            {
                KwlnTask_RemoveTaskFromList(task);
                if (task->destroy != NULL)
                {
                    task->destroy(task);
                }

                KWLN_TASK_RESET_STATE(task);

                KwlnTask_RemoveParent(task);
                KwlnTask_DetachParent(task);
                H_Free((uintptr_t)task);
            }
            break;
    }
}

// FUN_001949e0. Called every frame in the game main loop
u8 KwlnTask_Main()
{
    KwlnTask* currTask;
    KwlnTask* nextTask;

    nextTask = ctx.stagedTaskHead;

    while (nextTask != NULL)
    {
        if (nextTask->runningDelay > 0)
        {
            nextTask->runningDelay--;
        }

        currTask = nextTask;
        nextTask = nextTask->next;
        if (currTask->runningDelay == 0)
        {
            KwlnTask_RemoveTaskFromList(currTask);
            KWLN_TASK_SET_STATE(currTask, KWLN_TASK_STATE_RUNNING);
            KwlnTask_AddToList(currTask);

            currTask->unk_24 = 0;
            currTask->taskTimer = 0;
        }
    }

    KwlnTask_UpdateAll();

    nextTask = ctx.destroyTaskHead;
    while (nextTask != NULL)
    {
        if (nextTask->destroyDelay > 0)
        {
            nextTask->destroyDelay--;
        }

        currTask = nextTask;
        nextTask = nextTask->next;
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

// FUN_00194b20. Create a new task. 'parentTask' can be NULL
KwlnTask* KwlnTask_Create(KwlnTask* parentTask, const char* taskName, u32 priority, KwlnTask_UpdateFunc update, KwlnTask_DestroyFunc destroy, void* taskData)
{
    KwlnTask* task = KwlnTask_Init(taskName, priority, update, destroy, taskData);
    KwlnTask_AddChild(parentTask, task);

    return task;
}

// FUN_00194b80. Create a new task and adjust priority by the parent hierarchy. 'parentTask' can be NULL
KwlnTask* KwlnTask_CreateWithAutoPriority(KwlnTask* parentTask, u32 priority, const char* name, KwlnTask_UpdateFunc update, KwlnTask_DestroyFunc destroy, void* taskData)
{
    KwlnTask* task;
    KwlnTask* currParent;
    u32 maxPriority;

    if (parentTask != NULL)
    {
        maxPriority = 0;
        currParent = parentTask;

        while (currParent != NULL)
        {
            if (priority <= currParent->priority &&
               (currParent->priority < priority + 1024) &&
               (maxPriority < currParent->priority))
            {
                maxPriority = currParent->priority;
            }

            currParent = currParent->parent;
        }

        if (maxPriority != 0)
        {
            priority = maxPriority + 1;
        }
    }

    task = KwlnTask_Init(name, priority, update, destroy, taskData);
    KwlnTask_AddChild(parentTask, task);

    return task;
}

// FUN_00194c50. Init a new task. See 'KwlnTask_InitEx' for adjustable 'runningDelay' and 'destroyDelay'
KwlnTask* KwlnTask_Init(const char* taskName,
                        u32 priority,
                        KwlnTask_UpdateFunc update,
                        KwlnTask_DestroyFunc destroy,
                        void* taskData)
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
    task->priority = priority;
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
    task->sibling = NULL;
    task->unk_58 = 0;
    task->unk_5c = 0;
    task->unk_60 = 0;
    task->unk_64 = 0;
    
    KwlnTask_AddToList(task);

    if (task->runningDelay == 0)
    {
        KwlnTask_RemoveTaskFromList(task);
        KWLN_TASK_SET_STATE(task, KWLN_TASK_STATE_RUNNING);
        KwlnTask_AddToList(task);

        task->unk_24 = 0;
        task->taskTimer = 0;
    }

    return task;
}

// FUN_00194e10. Init a new task with adjustable 'runningDelay' and 'destroyDelay'
KwlnTask* KwlnTask_InitEx(const char* taskName,
                          u32 priority,
                          s32 runningDelay,
                          s32 destroyDelay,
                          KwlnTask_UpdateFunc update,
                          KwlnTask_DestroyFunc destroy,
                          void* taskData)
{
    KwlnTask* task;
    u8 currChar;
    u32 i;

    if (taskName[0] == '\0')
    {
        P3FES_ASSERT("kwlnTask.c", 1101);
    }

    task = (KwlnTask*)H_Malloc(sizeof(KwlnTask));
    if (task == NULL)
    {
        P3FES_ASSERT("kwlnTask.c", 1109);
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
    task->priority = priority;
    task->unk_24 = 0;
    task->taskTimer = 0;
    task->runningDelay = runningDelay;
    task->destroyDelay = destroyDelay;
    task->update = update;
    task->destroy = destroy;
    task->taskData = taskData;
    task->next = NULL;
    task->prev = NULL;
    task->unk_48 = NULL;
    task->parent = NULL;
    task->child = NULL;
    task->sibling = NULL;
    task->unk_58 = 0;
    task->unk_5c = 0;
    task->unk_60 = 0;
    task->unk_64 = 0;
    
    KwlnTask_AddToList(task);

    if (task->runningDelay == 0)
    {
        KwlnTask_RemoveTaskFromList(task);
        KWLN_TASK_SET_STATE(task, KWLN_TASK_STATE_RUNNING);
        KwlnTask_AddToList(task);

        task->unk_24 = 0;
        task->taskTimer = 0;
    }

    return task;
}

// FUN_00195290
u32 KwlnTask_GetTaskState(KwlnTask* task)
{
    u32 state;

    if (!KwlnTask_Exists(task))
    {
        return KWLN_TASK_STATE_NULL;
    }

    state = KWLN_TASK_GET_STATE(task);
    if (state != KWLN_TASK_STATE_NULL &&
       (state != KWLN_TASK_STATE_DESTROY) &&
       (state != KWLN_TASK_STATE_RUNNING) &&
       (state != KWLN_TASK_STATE_CREATED))
    {
        P3FES_LOG3("Process stat Invalid!!\n");
        P3FES_ASSERT("kwlnTask.c", 1286);

        return KWLN_TASK_STATE_NULL;
    }

    return state;
}

// FUN_00195340
KwlnTask* KwlnTask_GetTaskByName(const char* name)
{
    KwlnTask* list;
    u32 i;
    u32 j;
    u32 k;
    u32 nameChkSum = 0;
    
    for (i = 0; name[i] != '\0'; i++)
    {
        nameChkSum += name[i];
    }

    for (j = 0; j < 3; j++)
    {
        switch (j)
        {
            case 0: list = ctx.stagedTaskHead;  break;
            case 1: list = ctx.runningTaskHead; break;
            case 2: list = ctx.destroyTaskHead; break;
        }

        while (list != NULL)
        {
            k = i;

            if (list->nameChkSum == nameChkSum)
            {
                while (k > 0 && name[k-1] == list->taskName[k-1])
                {
                    k--;
                }

                if (k == 0)
                {
                    return list;
                }
            }

            list = list->next;
        }
    }

    return NULL;
}

// FUN_00195460. Return true if 'task' is in a list
u8 KwlnTask_Exists(KwlnTask* task)
{
    // need to rework a little bit

    KwlnTask* list;
    u32 i;

    if (task != NULL)
    {
        for (i = 0; i < 3; i++)
        {
            switch (i)
            {
                case 0: list = ctx.stagedTaskHead;  break;
                case 1: list = ctx.runningTaskHead; break;
                case 2: list = ctx.destroyTaskHead; break;
            }

            while (list != NULL)
            {
                if (list == task)
                {
                    return true;
                }

                list = list->next;
            }
        }
    }

    return false;
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
                currChild = lastChild->sibling;
            }

            lastChild->sibling = child;
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
        if (childTask->sibling != NULL)
        {
            P3FES_ASSERT("kwlnTask.c", 1519);
        }

        return;
    }

    currChild = parent->child;
    if (parent->child == childTask)
    {
        parent->child = childTask->sibling;
    }
    else
    {
        while (currChild != childTask)
        {
            lastChild = currChild;
            currChild = lastChild->sibling;
        }

        lastChild->sibling = childTask->sibling;
    }

    childTask->parent = NULL;
    childTask->sibling = NULL;
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

        next = next->sibling;
        currTask->parent = NULL;
        currTask->sibling = NULL;
    } 
}