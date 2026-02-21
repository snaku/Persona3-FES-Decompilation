#include "kwln/kwlnTask.h"
#include "g_data.h"
#include "h_malloc.h"
#include "temporary.h"

static KwlnTask* sStagedTaskHead;    // 007ce064. Head of tasks in 'KWLN_TASK_STATE_CREATED' state
static KwlnTask* sStagedTaskTail;    // 007ce068. Tail of tasks in 'KWLN_TASK_STATE_CREATED' state
static u32 sNumTaskStaged;           // 007ce06c. Total number of task in 'KWLN_TASK_STATE_CREATED' state

static KwlnTask* sDestroyTaskHead;   // 007ce070. Head of tasks in 'KWLN_TASK_STATE_DESTROY' state
static KwlnTask* sDestroyTaskTail;   // 007ce074. Tail of tasks in 'KWLN_TASK_STATE_DESTROY' state
static u32 sNumTaskDestroy;          // 007ce078. Total number of task in 'KWLN_TASK_STATE_DESTROY' state

static KwlnTask* sRunningTaskHead;   // 007ce07c. Head of tasks in 'KWLN_TASK_STATE_RUNNING' state
static KwlnTask* sRunningTaskTail;   // 007ce080. Tail of tasks in 'KWLN_TASK_STATE_RUNNING' state
static u32 sNumTaskRunning;          // 007ce084. Total number of task in 'KWLN_TASK_STATE_RUNNING' state

void KwlnTask_Destroy(KwlnTask* task);
void KwlnTask_DetachAllChildren(KwlnTask* task);

// FUN_001939d0. Remove a task from a list by its current state
void KwlnTask_RemoveFromList(KwlnTask* task)
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
            sDestroyTaskHead = task->next;
        }
        else if (taskState == KWLN_TASK_STATE_RUNNING)
        {
            sRunningTaskHead = task->next;
        }
        else if (taskState == KWLN_TASK_STATE_CREATED)
        {
            sStagedTaskHead = task->next;
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
            sDestroyTaskTail = task->prev;
        }
        else if (taskState == KWLN_TASK_STATE_RUNNING)
        {
            sRunningTaskTail = task->prev;
        }
        else if (taskState == KWLN_TASK_STATE_CREATED)
        {
            sStagedTaskTail = task->prev;
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
        sNumTaskDestroy--;
    }
    else if (taskState == KWLN_TASK_STATE_RUNNING)
    {
        sNumTaskRunning--;
    }
    else if (taskState == KWLN_TASK_STATE_CREATED)
    {
        sNumTaskStaged--;
    }
}

// FUN_00193ba0. Add a task from a list by its current state
void KwlnTask_AddToList(KwlnTask* task)
{
    KwlnTask* list;
    u32 taskState = KWLN_TASK_GET_STATE(task);

    switch (taskState)
    {
        case KWLN_TASK_STATE_CREATED: list = sStagedTaskHead;  break;
        case KWLN_TASK_STATE_RUNNING: list = sRunningTaskHead; break;
        case KWLN_TASK_STATE_DESTROY: list = sDestroyTaskHead; break;
        case KWLN_TASK_STATE_NULL: // fallthrough
        default: FUN_0019d400("Process stat Invalid!!", "kwlnTask.c", 143); return;
    }

    if (list == NULL)
    {
        switch (taskState)
        {
            case KWLN_TASK_STATE_CREATED:
                sStagedTaskHead = task;
                sStagedTaskTail = task;
                break;
            case KWLN_TASK_STATE_RUNNING:
                sRunningTaskHead = task;
                sRunningTaskTail = task;
                break;
            case KWLN_TASK_STATE_DESTROY:
                sDestroyTaskHead = task;
                sDestroyTaskTail = task;
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
                        case KWLN_TASK_STATE_CREATED: sStagedTaskHead = task;  break;
                        case KWLN_TASK_STATE_RUNNING: sRunningTaskHead = task; break;
                        case KWLN_TASK_STATE_DESTROY: sDestroyTaskHead = task; break;
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
                    sStagedTaskTail->next = task;
                    task->unk_48 = sStagedTaskTail;
                    task->prev = sStagedTaskTail;
                    sStagedTaskTail = task;
                    break;
                case KWLN_TASK_STATE_RUNNING: 
                    sRunningTaskTail->next = task;
                    task->unk_48 = sRunningTaskTail;
                    task->prev = sRunningTaskTail;
                    sRunningTaskTail = task;
                    break;
                case KWLN_TASK_STATE_DESTROY: 
                    sDestroyTaskTail->next = task;
                    task->unk_48 = sDestroyTaskTail;
                    task->prev = sDestroyTaskTail;
                    sDestroyTaskTail = task;
                    break;
            }

            task->next = NULL;
        }
    }

    taskState = KWLN_TASK_GET_STATE(task); // again
    switch (taskState)
    {
        case KWLN_TASK_STATE_CREATED:
            sNumTaskStaged++;
            if (sNumTaskStaged > 10000)
            {
                P3FES_ASSERT("kwlnTask.c", 226);
            }
            break;
        case KWLN_TASK_STATE_RUNNING:
            sNumTaskRunning++;
            if (sNumTaskRunning > 10000)
            {
                P3FES_ASSERT("kwlnTask.c", 230);
            }
            break;
        case KWLN_TASK_STATE_DESTROY:
            sNumTaskDestroy++;
            if (sNumTaskDestroy > 10000)
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
    KwlnTask* currTask = sRunningTaskHead;
    KwlnTask* cursor;
    KwlnTask* prevTask;
    u8 updateRes;

    if (sRunningTaskHead != NULL)
    {
        while (currTask != NULL)
        {
            prevTask = currTask->prev;
            updateRes = KwlnTask_Update(currTask);

            if (!updateRes)
            {
                currTask = sRunningTaskHead;

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

// FUN_001941f0. Destroy every task in the hierarchy
void KwlnTask_DestroyHierarchy(KwlnTask* task)
{
    KwlnTask* currTask;
    KwlnTask* currChild;
    
    if (task != NULL)
    {
        currTask = task;
        while (currTask != NULL)
        {
            currChild = currTask->child;
            if (currChild != NULL)
            {
                while (currChild != NULL)
                {
                    KwlnTask_DestroyHierarchy(currChild->child);
                    KwlnTask_Destroy(currChild);

                    currChild = currChild->sibling;
                }
            }

            KwlnTask_Destroy(currTask);
            currTask = currTask->sibling;
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
            KwlnTask_RemoveFromList(task);
            KWLN_TASK_SET_STATE(task, KWLN_TASK_STATE_DESTROY);
            KwlnTask_AddToList(task);

            if (task->destroyDelay == 0)
            {
                KwlnTask_RemoveFromList(task);
                if (task->destroy != NULL)
                {
                    task->destroy(task);
                }

                KWLN_TASK_RESET_STATE(task);

                KwlnTask_DetachParent(task);
                KwlnTask_DetachAllChildren(task);
                H_Free((uintptr_t)task);
            }
            break;
    }
}

// FUN_001949e0. Called every frame in the game main loop
u8 KwlnTask_Main()
{
    KwlnTask* nextTask;
    KwlnTask* currTask;

    nextTask = sStagedTaskHead;
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
            KwlnTask_RemoveFromList(currTask);
            KWLN_TASK_SET_STATE(currTask, KWLN_TASK_STATE_RUNNING);
            KwlnTask_AddToList(currTask);

            currTask->unk_24 = 0;
            currTask->taskTimer = 0;
        }
    }

    KwlnTask_UpdateAll();

    nextTask = sDestroyTaskHead;
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
            KwlnTask_RemoveFromList(currTask);
            
            if (currTask->destroy != NULL)
            {
                currTask->destroy(currTask);
            }

            KWLN_TASK_RESET_STATE(currTask);
            KwlnTask_DetachParent(currTask);
            KwlnTask_DetachAllChildren(currTask);

            H_Free((uintptr_t)currTask);
        }
    }

    return true;
}

// FUN_00194b20. Create a new task. 'parentTask' can be NULL
KwlnTask* KwlnTask_Create(KwlnTask* parentTask,
                          const char* taskName,
                          u32 priority,
                          KwlnTask_UpdateFunc update,
                          KwlnTask_DestroyFunc destroy,
                          void* taskData)
{
    KwlnTask* task = KwlnTask_Init(taskName, priority, update, destroy, taskData);
    KwlnTask_AddChild(parentTask, task);

    return task;
}

// FUN_00194b80. Create a new task and adjust priority by the parent hierarchy. 'parentTask' can be NULL
KwlnTask* KwlnTask_CreateWithAutoPriority(KwlnTask* parentTask, 
                                          u32 priority, 
                                          const char* name, 
                                          KwlnTask_UpdateFunc update, 
                                          KwlnTask_DestroyFunc destroy, 
                                          void* taskData)
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
    char currChar;
    s32 i;
    u32 state;

    if (taskName[0] == '\0')
    {
        P3FES_ASSERT("kwlnTask.c", 1022);
    }

    task = (KwlnTask*)H_Malloc(sizeof(KwlnTask));
    if (task == NULL)
    {
        P3FES_ASSERT("kwlnTask.c", 1032);
    }
    if (task == NULL)
    {
        return NULL;
    }
    
    task->nameChkSum = 0;
    i = 0;
    goto nameLoop;
copyName:
    currChar = taskName[i];
    task->nameChkSum += currChar;
    i++;
    
nameLoop:
    currChar = taskName[i];
    task->taskName[i] = currChar;
    if (currChar == '\0')
        goto continueInit;
    if (i < 24)
        goto copyName;
    
continueInit:
    task->taskName[23] = '\0';
    state = task->stateAndFlags = KWLN_TASK_STATE_NULL;
    task->stateAndFlags = (state | KWLN_TASK_STATE_CREATED);
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
        KwlnTask_RemoveFromList(task);
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
    char currChar;
    u32 i;
    u32 state;

    if (taskName[0] == '\0')
    {
        P3FES_ASSERT("kwlnTask.c", 1101);
    }

    task = (KwlnTask*)H_Malloc(sizeof(KwlnTask));
    if (task == NULL)
    {
        P3FES_ASSERT("kwlnTask.c", 1109);
    }
    if (task == NULL)
    {
        return NULL;
    }

    task->nameChkSum = 0;
    i = 0;
    goto nameLoop;

copyName:
    currChar = taskName[i];
    task->nameChkSum += currChar;
    i++;
    
nameLoop:
    currChar = taskName[i];
    task->taskName[i] = currChar;
    if (currChar == '\0')
        goto continueInit;
    if (i < 24)
        goto copyName;
    
continueInit:
    task->taskName[23] = '\0';
    state = task->stateAndFlags = KWLN_TASK_STATE_NULL;
    task->stateAndFlags = (state | KWLN_TASK_STATE_CREATED);
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
        KwlnTask_RemoveFromList(task);
        KWLN_TASK_SET_STATE(task, KWLN_TASK_STATE_RUNNING);
        KwlnTask_AddToList(task);

        task->unk_24 = 0;
        task->taskTimer = 0;
    }

    return task;
}

// FUN_00194fe0
u8 KwlnTask_DeleteWithHierarchyByName(const char* name)
{
    KwlnTask* task;

    task = KwlnTask_GetTaskByName(name);
    if (task == NULL)
    {
        return false;
    }

    return KwlnTask_DeleteWithHierarchy(task);
}

// FUN_00195020. Destroy a task and its hierarchy
u8 KwlnTask_DeleteWithHierarchy(KwlnTask* task)
{
    u32 state;

    if (task == NULL || task == (KwlnTask*)0xFFFFFFFF)
    {
        FUN_0019d400("ProcessID invalid!!\n", "kwlnTask.c", 1181);
        return false;
    }

    state = KWLN_TASK_GET_STATE(task);
    switch (state)
    {
        case KWLN_TASK_STATE_CREATED: // fallthrough
        case KWLN_TASK_STATE_RUNNING: 
            task->destroyDelay = 2;

            state = KWLN_TASK_GET_STATE(task);
            switch (state)
            {
                case KWLN_TASK_STATE_CREATED: // fallthrough
                case KWLN_TASK_STATE_RUNNING:
                    KwlnTask_RemoveFromList(task);
                    KWLN_TASK_SET_STATE(task, KWLN_TASK_STATE_DESTROY);
                    KwlnTask_AddToList(task);

                    // never true
                    if (task->destroyDelay == 0)
                    {
                        KwlnTask_RemoveFromList(task);
                        if (task->destroy != NULL)
                        {
                            task->destroy(task);
                        }

                        KWLN_TASK_RESET_STATE(task);

                        KwlnTask_DetachParent(task);
                        KwlnTask_DetachAllChildren(task);
                        H_Free((uintptr_t)task);
                    }
                    break;
                case KWLN_TASK_STATE_DESTROY: break;
                case KWLN_TASK_STATE_NULL: // fallthrough
                default: 
                    P3FES_LOG3("Process stat Invalid!!\n");
                    P3FES_ASSERT("kwlnTask.c", 574);
                    break;
            }

            task = task->child;
            if (task != NULL)
            {
                while (task != NULL)
                {
                    KwlnTask_DestroyHierarchy(task->child);
                    KwlnTask_Destroy(task);

                    task = task->sibling;
                }
            }
            break;
        case KWLN_TASK_STATE_DESTROY: 
            task->destroyDelay = 2; 
            break;
        case KWLN_TASK_STATE_NULL: // fallthrough
        default:
            FUN_0019d400("ProcessID invalid!!\n", "kwlnTask.c", 1204);
            return false;
    }

    return true;
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
    switch (state)
    {
        case KWLN_TASK_STATE_CREATED: // fallthrough
        case KWLN_TASK_STATE_RUNNING: // fallthrough
        case KWLN_TASK_STATE_DESTROY: // fallthrough
        case KWLN_TASK_STATE_NULL:    return state;
    }

    P3FES_LOG3("Process stat Invalid!!\n");
    P3FES_ASSERT("kwlnTask.c", 1286);
    return KWLN_TASK_STATE_NULL;
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
            case 0: list = sStagedTaskHead;  break;
            case 1: list = sRunningTaskHead; break;
            case 2: list = sDestroyTaskHead; break;
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
                case 0: list = sStagedTaskHead;  break;
                case 1: list = sRunningTaskHead; break;
                case 2: list = sDestroyTaskHead; break;
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
    KwlnTask* lastChild;

    if (parentTask != NULL)
    {
        if (childTask->parent != NULL)
        {
            KwlnTask_DetachParent(childTask);
        }

        lastChild = parentTask->child;
        if (parentTask->child != NULL)
        {
            while (lastChild->sibling != NULL)
            {
                lastChild = lastChild->sibling;
            }

            lastChild->sibling = childTask;
            
        }
        else
        {
            parentTask->child = childTask;
        }

        childTask->parent = parentTask;
    }
}

// FUN_001955f0
void KwlnTask_DetachParent(KwlnTask* childTask) 
{
    KwlnTask* parentTask;
    KwlnTask* currSibling;
    KwlnTask* prevSibling;
    KwlnTask** childPtr;

    parentTask = childTask->parent;
    if (parentTask == NULL) 
    {
        if (childTask->sibling != NULL) 
        {
            P3FES_ASSERT("kwlnTask.c", 1519);
        }

        return;
    } 

    childPtr = &parentTask->child;
    currSibling = *childPtr;
    if (currSibling == childTask) 
    {
        *childPtr = childTask->sibling;
    } 
    else 
    {
        while (currSibling != childTask)
        {
            prevSibling = currSibling;
            currSibling = prevSibling->sibling;
        }

        prevSibling->sibling = childTask->sibling;
    }

    childTask->parent = NULL;
    childTask->sibling = NULL;
}

// FUN_00195690
void KwlnTask_DetachAllChildren(KwlnTask* parentTask)
{
    KwlnTask* next;
    KwlnTask* currTask;

    next = parentTask->child;
    while (next != NULL)
    {
        if (next->parent == parentTask)
        {
            currTask = next;
        }

        next = next->sibling;
        currTask->parent = NULL;
        currTask->sibling = NULL;
    }
}