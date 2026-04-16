#include "kwln/kwlnTask.h"
#include "kwln/kwln.h"
#include "Kosaka/k_assert.h"
#include "g_data.h"
#include "h_malloc.h"
#include "h_pad.h"
#include "temporary.h"

static KwlnTask* sTaskUpdating; // 007ce088. Current task updating

static u32 sNumTaskRunning;          // 007ce084. Total number of task in 'KWLNTASK_STATE_RUNNING' state
static KwlnTask* sRunningTaskTail;   // 007ce080. Tail of tasks in 'KWLNTASK_STATE_RUNNING' state
static KwlnTask* sRunningTaskHead;   // 007ce07c. Head of tasks in 'KWLNTASK_STATE_RUNNING' state

static u32 sNumTaskDestroy;          // 007ce078. Total number of task in 'KWLNTASK_STATE_DESTROY' state
static KwlnTask* sDestroyTaskTail;   // 007ce074. Tail of tasks in 'KWLNTASK_STATE_DESTROY' state
static KwlnTask* sDestroyTaskHead;   // 007ce070. Head of tasks in 'KWLNTASK_STATE_DESTROY' state

static u32 sNumTaskStaged;           // 007ce06c. Total number of task in 'KWLNTASK_STATE_STAGED' state
static KwlnTask* sStagedTaskTail;    // 007ce068. Tail of tasks in 'KWLNTASK_STATE_STAGED' state
static KwlnTask* sStagedTaskHead;    // 007ce064. Head of tasks in 'KWLNTASK_STATE_STAGED' state

void kwlnTaskDestroy(KwlnTask* task);
void kwlnTaskDetachAllChildren(KwlnTask* task);
void kwlnTaskDestroyHierarchy(KwlnTask* task);

// FUN_001939d0. Remove a task from a list by its current state
void kwlnTaskRemoveFromList(KwlnTask* task)
{
    KwlnTask* next;
    KwlnTask* prev;
    u32 taskState;
    
    taskState = KWLNTASK_GET_STATE(task);
    if (taskState == KWLNTASK_STATE_NULL ||
       (taskState != KWLNTASK_STATE_DESTROY) &&
       (taskState != KWLNTASK_STATE_RUNNING) &&
       (taskState != KWLNTASK_STATE_STAGED))
    {
        K_Abort("Process stat Invalid!!", "kwlnTask.c", 70);
        return;
    }

    if (task->prev != NULL)
    {
        task->prev->next = task->next;
    }
    else 
    {
        switch (taskState)
        {
            case KWLNTASK_STATE_STAGED:  sStagedTaskHead  = task->next; break;
            case KWLNTASK_STATE_RUNNING: sRunningTaskHead = task->next; break;
            case KWLNTASK_STATE_DESTROY: sDestroyTaskHead = task->next; break;
        }
    }

    if (task->next != NULL)
    {
        prev = task->prev;
        task->next->unk_48 = prev;
        
        next = task->next;
        next->prev = prev;
    }
    else
    {
        taskState = KWLNTASK_GET_STATE(task);
        switch (taskState)
        {
            case KWLNTASK_STATE_STAGED:  sStagedTaskTail  = task->prev; break;
            case KWLNTASK_STATE_RUNNING: sRunningTaskTail = task->prev; break;
            case KWLNTASK_STATE_DESTROY: sDestroyTaskTail = task->prev; break;
        }
    }

    task->next = NULL;
    task->prev = NULL;
    
    taskState = KWLNTASK_GET_STATE(task);
    switch (taskState)
    {
        case KWLNTASK_STATE_STAGED:  sNumTaskStaged--;  break;
        case KWLNTASK_STATE_RUNNING: sNumTaskRunning--; break;
        case KWLNTASK_STATE_DESTROY: sNumTaskDestroy--; break;
    }
}

// FUN_00193ba0. Add a task from a list by its current state
void kwlnTaskAddToList(KwlnTask* task)
{
    KwlnTask* list;
    u32 taskState = KWLNTASK_GET_STATE(task);

    switch (taskState)
    {
        case KWLNTASK_STATE_STAGED:  list = sStagedTaskHead;  break;
        case KWLNTASK_STATE_RUNNING: list = sRunningTaskHead; break;
        case KWLNTASK_STATE_DESTROY: list = sDestroyTaskHead; break;

        case KWLNTASK_STATE_NULL: // fallthrough
        default: K_Abort("Process stat Invalid!!", "kwlnTask.c", 143); return;
    }

    if (list == NULL)
    {
        switch (taskState)
        {
            case KWLNTASK_STATE_STAGED:
                sStagedTaskHead = task;
                sStagedTaskTail = task;
                break;
            case KWLNTASK_STATE_RUNNING:
                sRunningTaskHead = task;
                sRunningTaskTail = task;
                break;
            case KWLNTASK_STATE_DESTROY:
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
                        case KWLNTASK_STATE_STAGED:  sStagedTaskHead = task;  break;
                        case KWLNTASK_STATE_RUNNING: sRunningTaskHead = task; break;
                        case KWLNTASK_STATE_DESTROY: sDestroyTaskHead = task; break;
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
            taskState = KWLNTASK_GET_STATE(task); // again
            switch (taskState)
            {
                case KWLNTASK_STATE_STAGED: 
                    sStagedTaskTail->next = task;
                    task->unk_48 = sStagedTaskTail;
                    task->prev = sStagedTaskTail;
                    sStagedTaskTail = task;
                    break;
                case KWLNTASK_STATE_RUNNING: 
                    sRunningTaskTail->next = task;
                    task->unk_48 = sRunningTaskTail;
                    task->prev = sRunningTaskTail;
                    sRunningTaskTail = task;
                    break;
                case KWLNTASK_STATE_DESTROY: 
                    sDestroyTaskTail->next = task;
                    task->unk_48 = sDestroyTaskTail;
                    task->prev = sDestroyTaskTail;
                    sDestroyTaskTail = task;
                    break;
            }

            task->next = NULL;
        }
    }

    taskState = KWLNTASK_GET_STATE(task); // again
    switch (taskState)
    {
        case KWLNTASK_STATE_STAGED:
            sNumTaskStaged++;
            K_ASSERT(sNumTaskStaged < 10000, 226);
            break;

        case KWLNTASK_STATE_RUNNING:
            sNumTaskRunning++;
            K_ASSERT(sNumTaskRunning < 10000, 230);
            break;

        case KWLNTASK_STATE_DESTROY:
            sNumTaskDestroy++;
            K_ASSERT(sNumTaskDestroy < 10000, 234);
            break;
    }
}

// FUN_00193ec0
u8 kwlnTaskUpdate(KwlnTask* task)
{
    s32 i;
    HPad* pad;
    KwlnTaskUpdateFunc updateFunc;
    void* updateRes;

    // WIP: Need to do the first if

    sTaskUpdating = task;

    if (task->stateAndFlags & (1 << 4))
    {
        memset(gPads, 0, HPAD_PORT_MAX * sizeof(HPad));

        i = 0;
        pad = gPads;
        // ???
        for (; i < HPAD_PORT_MAX; i++)
        {
            pad[i].btn[1].justPressed = HPAD_BTN_SQUARE;
            pad[i].btn[1].released = HPAD_BTN_SQUARE;
            pad[i].btn[1].justReleased = HPAD_BTN_SQUARE;

            pad[i].lstickX = 128;
            pad[i].lstickY = 128;
            pad[i].rstickX = 128;
            pad[i].rstickY = 128;
        }
    }
    else
    {
        memcpy(gPads, &gWorkPads, HPAD_PORT_MAX * sizeof(HPad));
    }

    updateFunc = task->update;
    // i don't think 0xFFFFFFFF is KWLNTASK_STOP here
    if (updateFunc != NULL && updateFunc != (KwlnTaskUpdateFunc)0xFFFFFFFF) 
    {
        updateRes = updateFunc(task);
        if (updateRes != KWLNTASK_CONTINUE)
        {
            task->update = updateRes;
        }

        if (updateRes == KWLNTASK_STOP && 
           (KWLNTASK_GET_STATE(task) == KWLNTASK_STATE_RUNNING))
        {
            kwlnTaskDestroy(task);
            kwlnTaskDestroyHierarchy(task->child);
            sTaskUpdating = NULL;

            return false;
        }

        // no it doesn't use KWLNTASK_GET_STATE here
        if (task->stateAndFlags == KWLNTASK_STATE_DESTROY)
        {
            sTaskUpdating = NULL;
            
            return false;
        }
    }

    task->taskTimer++;
    sTaskUpdating = NULL;

    return true;
}

// FUN_00194100
void kwlnTaskUpdateAll()
{
    KwlnTask* currTask = sRunningTaskHead;
    KwlnTask* cursor;
    KwlnTask* prevTask;

    if (sRunningTaskHead != NULL)
    {
        while (currTask != NULL)
        {
            prevTask = currTask->prev;

            if (!kwlnTaskUpdate(currTask))
            {
                currTask = sRunningTaskHead;

                if (prevTask != NULL)
                {
                    cursor = prevTask;

                    while (cursor != NULL && 
                          (KWLNTASK_GET_STATE(cursor) == KWLNTASK_STATE_DESTROY))
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
void kwlnTaskDestroyHierarchy(KwlnTask* task)
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
                    kwlnTaskDestroyHierarchy(currChild->child);
                    kwlnTaskDestroy(currChild);

                    currChild = currChild->sibling;
                }
            }

            kwlnTaskDestroy(currTask);
            currTask = currTask->sibling;
        }
    }
}

// FUN_00194280. Change a task state to 'KWLNTASK_STATE_DESTROY'. If 'destroyTask' is 0, destroy the task immediately
void kwlnTaskDestroy(KwlnTask* task)
{
    u32 state;

    state = KWLNTASK_GET_STATE(task);

    switch (state)
    {
        case KWLNTASK_STATE_DESTROY: return;
        case KWLNTASK_STATE_NULL: 
            FUN_005225a8("Process stat Invalid!!\n");
            K_Assert("kwlnTask.c", 574);
            break;

        case KWLNTASK_STATE_STAGED:  // fallthrough
        case KWLNTASK_STATE_RUNNING:
            kwlnTaskRemoveFromList(task);
            KWLNTASK_SET_STATE(task, KWLNTASK_STATE_DESTROY);
            kwlnTaskAddToList(task);

            if (task->destroyDelay == 0)
            {
                kwlnTaskRemoveFromList(task);
                if (task->destroy != NULL)
                {
                    task->destroy(task);
                }

                KWLNTASK_RESET_STATE(task);

                kwlnTaskDetachParent(task);
                kwlnTaskDetachAllChildren(task);
                H_Free((uintptr_t)task);
            }
            break;
    }
}

// FUN_001949e0. Called every frame in the game main loop
u8 kwlnTaskMain()
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
            kwlnTaskRemoveFromList(currTask);
            KWLNTASK_SET_STATE(currTask, KWLNTASK_STATE_RUNNING);
            kwlnTaskAddToList(currTask);

            currTask->unk_24 = 0;
            currTask->taskTimer = 0;
        }
    }

    kwlnTaskUpdateAll();

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
            kwlnTaskRemoveFromList(currTask);
            
            if (currTask->destroy != NULL)
            {
                currTask->destroy(currTask);
            }

            KWLNTASK_RESET_STATE(currTask);
            kwlnTaskDetachParent(currTask);
            kwlnTaskDetachAllChildren(currTask);

            H_Free((uintptr_t)currTask);
        }
    }

    return true;
}

// FUN_00194b20. Create a new task. 'parentTask' can be NULL
KwlnTask* kwlnTaskCreate(KwlnTask* parentTask,
                          const char* taskName,
                          u32 priority,
                          KwlnTaskUpdateFunc update,
                          KwlnTaskDestroyFunc destroy,
                          void* workData)
{
    KwlnTask* task = kwlnTaskInit(taskName, priority, update, destroy, workData);
    kwlnTaskAddChild(parentTask, task);

    return task;
}

// FUN_00194b80. Create a new task and adjust priority by the parent hierarchy. 'parentTask' can be NULL
KwlnTask* kwlnTaskCreateWithAutoPriority(KwlnTask* parentTask, 
                                         u32 priority, 
                                         const char* name, 
                                         KwlnTaskUpdateFunc update, 
                                         KwlnTaskDestroyFunc destroy, 
                                         void* workData)
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

    task = kwlnTaskInit(name, priority, update, destroy, workData);
    kwlnTaskAddChild(parentTask, task);

    return task;
}

// FUN_00194c50. Init a new task. See 'kwlnTaskInitEx' for adjustable 'runningDelay' and 'destroyDelay'
KwlnTask* kwlnTaskInit(const char* taskName,
                       u32 priority,
                       KwlnTaskUpdateFunc update,
                       KwlnTaskDestroyFunc destroy,
                       void* workData)
{
    KwlnTask* task;
    char currChar;
    s32 i;

    K_ASSERT(taskName[0] != '\0', 1022);

    task = (KwlnTask*)H_Malloc(sizeof(KwlnTask));
    K_ASSERT(task != NULL, 1032);

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
    task->stateAndFlags = KWLNTASK_STATE_NULL;
    task->stateAndFlags |= KWLNTASK_STATE_STAGED;
    task->priority = priority;
    task->unk_24 = 0;
    task->taskTimer = 0;
    task->runningDelay = 0;
    task->destroyDelay = 2;
    task->update = update;
    task->destroy = destroy;
    task->workData = workData;
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
    
    kwlnTaskAddToList(task);

    if (task->runningDelay == 0)
    {
        kwlnTaskRemoveFromList(task);
        KWLNTASK_SET_STATE(task, KWLNTASK_STATE_RUNNING);
        kwlnTaskAddToList(task);

        task->unk_24 = 0;
        task->taskTimer = 0;
    }

    return task;
}

// FUN_00194e10. Init a new task with adjustable 'runningDelay' and 'destroyDelay'
KwlnTask* kwlnTaskInitEx(const char* taskName,
                         u32 priority,
                         s32 runningDelay,
                         s32 destroyDelay,
                         KwlnTaskUpdateFunc update,
                         KwlnTaskDestroyFunc destroy,
                         void* workData)
{
    KwlnTask* task;
    char currChar;
    u32 i;

    K_ASSERT(taskName[0] != '\0', 1101);

    task = (KwlnTask*)H_Malloc(sizeof(KwlnTask));
    K_ASSERT(task != NULL, 1109);

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
    task->stateAndFlags = KWLNTASK_STATE_NULL;
    task->stateAndFlags |= KWLNTASK_STATE_STAGED;
    task->priority = priority;
    task->unk_24 = 0;
    task->taskTimer = 0;
    task->runningDelay = runningDelay;
    task->destroyDelay = destroyDelay;
    task->update = update;
    task->destroy = destroy;
    task->workData = workData;
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
    
    kwlnTaskAddToList(task);

    if (task->runningDelay == 0)
    {
        kwlnTaskRemoveFromList(task);
        KWLNTASK_SET_STATE(task, KWLNTASK_STATE_RUNNING);
        kwlnTaskAddToList(task);

        task->unk_24 = 0;
        task->taskTimer = 0;
    }

    return task;
}

// FUN_00194fe0
u8 kwlnTaskDestroyWithHierarchyByName(const char* name)
{
    KwlnTask* task;

    task = kwlnTaskGetTaskByName(name);
    if (task == NULL)
    {
        return false;
    }

    return kwlnTaskDestroyWithHierarchy(task);
}

// FUN_00195020. Destroy a task and its hierarchy
u8 kwlnTaskDestroyWithHierarchy(KwlnTask* task)
{
    u32 state;

    if (task == NULL || task == (KwlnTask*)0xFFFFFFFF)
    {
        K_Abort("ProcessID invalid!!\n", "kwlnTask.c", 1181);
        return false;
    }

    state = KWLNTASK_GET_STATE(task);
    switch (state)
    {
        case KWLNTASK_STATE_STAGED:  // fallthrough
        case KWLNTASK_STATE_RUNNING: 
            task->destroyDelay = 2;

            state = KWLNTASK_GET_STATE(task);
            switch (state)
            {
                case KWLNTASK_STATE_STAGED:  // fallthrough
                case KWLNTASK_STATE_RUNNING:
                    kwlnTaskRemoveFromList(task);
                    KWLNTASK_SET_STATE(task, KWLNTASK_STATE_DESTROY);
                    kwlnTaskAddToList(task);

                    // never true
                    if (task->destroyDelay == 0)
                    {
                        kwlnTaskRemoveFromList(task);
                        if (task->destroy != NULL)
                        {
                            task->destroy(task);
                        }

                        KWLNTASK_RESET_STATE(task);

                        kwlnTaskDetachParent(task);
                        kwlnTaskDetachAllChildren(task);
                        H_Free((uintptr_t)task);
                    }
                    break;
                case KWLNTASK_STATE_DESTROY: break;
                case KWLNTASK_STATE_NULL:    // fallthrough
                default: 
                    FUN_005225a8("Process stat Invalid!!\n");
                    K_Assert("kwlnTask.c", 574);
                    break;
            }

            task = task->child;
            if (task != NULL)
            {
                while (task != NULL)
                {
                    kwlnTaskDestroyHierarchy(task->child);
                    kwlnTaskDestroy(task);

                    task = task->sibling;
                }
            }
            break;
        case KWLNTASK_STATE_DESTROY: 
            task->destroyDelay = 2; 
            break;
        case KWLNTASK_STATE_NULL: // fallthrough
        default:
            K_Abort("ProcessID invalid!!\n", "kwlnTask.c", 1204);
            return false;
    }

    return true;
}

// FUN_00195290
u32 kwlnTaskGetState(KwlnTask* task)
{
    u32 state;

    if (!kwlnTaskExists(task))
    {
        return KWLNTASK_STATE_NULL;
    }

    state = KWLNTASK_GET_STATE(task);
    switch (state)
    {
        case KWLNTASK_STATE_STAGED:  // fallthrough
        case KWLNTASK_STATE_RUNNING: // fallthrough
        case KWLNTASK_STATE_DESTROY: // fallthrough
        case KWLNTASK_STATE_NULL:    return state;
    }

    FUN_005225a8("Process stat Invalid!!\n");
    K_Assert("kwlnTask.c", 1286);
    return KWLNTASK_STATE_NULL;
}

// FUN_00195340
KwlnTask* kwlnTaskGetTaskByName(const char* name)
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
u8 kwlnTaskExists(KwlnTask* task)
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
u32 kwlnTaskGetTimer(KwlnTask* task)
{
    return task->taskTimer;
}

// FUN_00195530
void kwlnTaskSetWorkData(KwlnTask* task, void* workData)
{
    task->workData = workData;
}

// FUN_00195540
void* kwlnTaskGetWorkData(KwlnTask* task)
{
    return task->workData;
}

// FUN_00195550
void kwlnTaskAddChild(KwlnTask* parentTask, KwlnTask* childTask)
{
    KwlnTask* lastChild;

    if (parentTask != NULL)
    {
        if (childTask->parent != NULL)
        {
            kwlnTaskDetachParent(childTask);
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
void kwlnTaskDetachParent(KwlnTask* childTask) 
{
    KwlnTask* parentTask;
    KwlnTask* currSibling;
    KwlnTask* prevSibling;
    KwlnTask** childPtr;

    parentTask = childTask->parent;
    if (parentTask == NULL) 
    {
        K_ASSERT(childTask->sibling == NULL, 1519);
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
void kwlnTaskDetachAllChildren(KwlnTask* parentTask)
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