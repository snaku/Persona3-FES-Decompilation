#include "kwln/kwlnTask.h"
#include "rw/rwplcore.h"
#include "Battle/btlMain.h"
#include "admini.h"
#include "g_data.h"
#include "temporary.h"

typedef struct
{
    void (*Admini_Call)(u8 isRestored, void* taskData);
    s32 (*Admini_Exit)();
    u8 (*Admini_Check)();
} AdminiTaskEntry;

void Admini_TestCall(u8 isRestored, void* taskData);
s32 Admini_TestExit();
u8 Admini_TestCheck();
s32 Admini_BtlBossExit();
u8 Admini_BtlBossCheck();

// 0068f020
static const AdminiTaskEntry gAdminiTasksTable[ADMINI_TASK_ID_MAX] = 
{
    {NULL, NULL, NULL},                                   // ADMINI_TASK_ID_NULL
    {Admini_TestCall, Admini_TestExit, Admini_TestCheck}, // ADMINI_TASK_ID_TEST
    {NULL, NULL, NULL},                                   // ADMINI_TASK_ID_FIELD_ROOT. TODO
    {NULL, NULL, NULL},                                   // ADMINI_TASK_ID_FIELD_ROOT2. TODO
    {NULL, NULL, NULL},                                   // ADMINI_TASK_ID_MAP. TODO
    {NULL, NULL, NULL},                                   // ADMINI_TASK_ID_DUNGEON. TODO
    {NULL, Admini_BtlBossExit, Admini_BtlBossCheck},      // ADMINI_TASK_ID_BATTLE_BOSS. TODO
    {NULL, NULL, NULL},                                   // ADMINI_TASK_ID_FACILITY. TODO
};

void* Admini_UpdateTask_Check(KwlnTask* adminiTask);

// FUN_0027c080
void Admini_ChangeTask(s8 taskId, void* taskData, u8 taskDataSize, u8 isNotRestorable)
{
    KwlnTask* adminiTask;
    Admini* admini;

    adminiTask = KwlnTask_GetTaskByName("admini");
    if (adminiTask == NULL)
    {
        P3FES_ASSERT("admini.c", 46);
    }

    admini = (Admini*)KwlnTask_GetTaskData(adminiTask);
    if (admini == NULL)
    {
        P3FES_ASSERT("admini.c", 48);
    }

    ADMINI_SET_FLAGS(admini, ADMINI_FLAG_CHANGING_TASK);
    ADMINI_SET_RESET_FLAGS(admini, ADMINI_FLAG_UNK08, ADMINI_FLAG_CHANGING_TASK);
    ADMINI_SET_RESET_FLAGS(admini, ADMINI_FLAG_UNK08 | ADMINI_FLAG_RESTORE_PREV, ADMINI_FLAG_CHANGING_TASK);

    admini->taskIdToSet = taskId;
    admini->taskChangeDelay = 1;

    if (admini->taskData != NULL)
    {
        RW_FREE(admini->taskData);
        admini->taskData = NULL;
        admini->taskDataSize = 0;
    }

    if (taskData == NULL)
    {
        admini->taskData = NULL;
        admini->taskDataSize = 0;
    }
    else
    {
        admini->taskData = RW_MALLOC(taskDataSize, 0x40000);
        if (admini->taskData == NULL)
        {
            P3FES_ASSERT("admini.c", 93);
        }

        memcpy(admini->taskData, taskData, taskDataSize);
        admini->taskDataSize = taskDataSize;
    }

    if (!isNotRestorable)
    {
        ADMINI_SET_FLAGS(admini, ADMINI_FLAG_RESTORABLE);
        return;
    }

    ADMINI_RESET_FLAGS(admini, ADMINI_FLAG_RESTORABLE);
}

// FUN_0027c220. Set flag 'ADMINI_FLAG_PASSED_CHECK'
void Admini_ForcePassedCheck()
{
    KwlnTask* adminiTask;
    Admini* admini;

    adminiTask = KwlnTask_GetTaskByName("admini");
    if (adminiTask == NULL)
    {
        P3FES_ASSERT("admini.c", 46);
    }

    admini = (Admini*)KwlnTask_GetTaskData(adminiTask);
    if (admini == NULL)
    {
        P3FES_ASSERT("admini.c", 48);
    }

    ADMINI_SET_FLAGS(admini, ADMINI_FLAG_PASSED_CHECK);
}

// FUN_0027c2b0
s8 Admini_GetTaskId()
{
    KwlnTask* adminiTask;
    Admini* admini;

    adminiTask = KwlnTask_GetTaskByName("admini");
    if (adminiTask == NULL)
    {
        P3FES_ASSERT("admini.c", 46);
    }

    admini = (Admini*)KwlnTask_GetTaskData(adminiTask);
    if (admini == NULL)
    {
        P3FES_ASSERT("admini.c", 48);
    }

    return admini->taskId;
}

// FUN_0027c330
s8 Admini_GetTaskIdToSet()
{
    KwlnTask* adminiTask;
    Admini* admini;

    adminiTask = KwlnTask_GetTaskByName("admini");
    if (adminiTask == NULL)
    {
        P3FES_ASSERT("admini.c", 46);
    }

    admini = (Admini*)KwlnTask_GetTaskData(adminiTask);
    if (admini == NULL)
    {
        P3FES_ASSERT("admini.c", 48);
    }

    return admini->taskIdToSet;
}

// FUN_0027c3b0
void* Admini_UpdateTask_Call(KwlnTask* adminiTask)
{
    Admini* admini;
    u8 isRestored;

    admini = (Admini*)KwlnTask_GetTaskData(adminiTask);
    if (admini == NULL)
    {
        P3FES_ASSERT("admini.c", 217);
    }

    if (!(admini->flags & ADMINI_FLAG_CHANGING_TASK) ||
         (admini->taskIdToSet < ADMINI_TASK_ID_NULL))
    {
        return Admini_UpdateTask_Check;
    }

    if (admini->taskChangeDelay == 0)
    {
        admini->timer = 0;
        admini->taskId = admini->taskIdToSet;
        admini->taskIdToSet = ADMINI_TASK_ID_INVALID;

        ADMINI_RESET_FLAGS(admini, ADMINI_FLAG_CHANGING_TASK);
        ADMINI_RESET_FLAGS(admini, ADMINI_FLAG_CHANGING_TASK | ADMINI_FLAG_PASSED_CHECK);

        if (admini->flags & ADMINI_FLAG_RESTORABLE)
        {
            admini->oldTasksFlags[admini->oldTaskIdx] |= ADMINI_FLAG_CHANGING_TASK;
            ADMINI_RESET_FLAGS(admini, ADMINI_FLAG_RESTORABLE);
        }

        if (!(admini->flags & ADMINI_FLAG_RESTORE_PREV))
        {
            isRestored = false;
            if (!(admini->flags & ADMINI_FLAG_UNK08))
            {
                admini->oldTaskIdx = (admini->oldTaskIdx + 1) % ADMINI_TASK_ID_MAX;
            }
            else
            {
                ADMINI_RESET_FLAGS(admini, ADMINI_FLAG_UNK08);
            }
        }
        else
        {
            isRestored = true;
            admini->oldTaskIdx = (admini->oldTaskIdx + (ADMINI_TASK_ID_MAX - 1)) % ADMINI_TASK_ID_MAX;
            ADMINI_RESET_FLAGS(admini, ADMINI_FLAG_RESTORE_PREV);
        }

        admini->oldTaskIds[admini->oldTaskIdx] = admini->taskId;
        admini->oldTasksFlags[admini->oldTaskIdx] = 0;

        if (gAdminiTasksTable[admini->taskId].Admini_Call != NULL)
        {
            gAdminiTasksTable[admini->taskId].Admini_Call(isRestored, admini->taskData);
        }

        return Admini_UpdateTask_Check;
    }

    admini->taskChangeDelay--;
    return KWLN_TASK_CONTINUE;
}

// FUN_0027c5a0
void* Admini_UpdateTask_Exit(KwlnTask* adminiTask)
{
    Admini* admini;
    s32 taskChangeDelay;

    admini = (Admini*)KwlnTask_GetTaskData(adminiTask);
    if (admini == NULL)
    {
        P3FES_ASSERT("admini.c", 296);
    }

    if (admini->taskId >= ADMINI_TASK_ID_NULL &&
       (gAdminiTasksTable[admini->taskId].Admini_Exit != NULL))
    {
        taskChangeDelay = gAdminiTasksTable[admini->taskId].Admini_Exit();
        if (taskChangeDelay < 0)
        {
            return KWLN_TASK_CONTINUE;
        }

        admini->taskChangeDelay = taskChangeDelay + 1;
        admini->taskId = ADMINI_TASK_ID_INVALID;
    }

    return Admini_UpdateTask_Call;
}

// FUN_0027c650
void* Admini_UpdateTask_Check(KwlnTask* adminiTask)
{
    Admini* admini;

    admini = (Admini*)KwlnTask_GetTaskData(adminiTask);
    if (admini == NULL)
    {
        P3FES_ASSERT("admini.c", 333);
    }

    if (!(admini->flags & ADMINI_FLAG_PASSED_CHECK) &&
         (admini->taskId >= ADMINI_TASK_ID_NULL))
    {
        if (gAdminiTasksTable[admini->taskId].Admini_Check != NULL)
        {
            if (gAdminiTasksTable[admini->taskId].Admini_Check())
            {
                ADMINI_SET_FLAGS(admini, ADMINI_FLAG_PASSED_CHECK);
            }
        }

        admini->timer++;
    }

    if (admini->flags & ADMINI_FLAG_PASSED_CHECK &&
       (admini->taskId >= ADMINI_TASK_ID_NULL))
    {
        admini->oldTaskIdx = (admini->oldTaskIdx + (ADMINI_TASK_ID_MAX - 1)) % ADMINI_TASK_ID_MAX;

        if (admini->oldTaskIds[admini->oldTaskIdx] >= ADMINI_TASK_ID_NULL &&
           (admini->oldTasksFlags[admini->oldTaskIdx] & ADMINI_FLAG_CHANGING_TASK))
        {
            FUN_005225a8("restore sequence!!\n");

            ADMINI_SET_FLAGS(admini, ADMINI_FLAG_CHANGING_TASK);
            ADMINI_SET_FLAGS(admini, ADMINI_FLAG_CHANGING_TASK | ADMINI_FLAG_RESTORE_PREV);

            admini->taskIdToSet = admini->oldTaskIds[admini->oldTaskIdx];
            admini->taskChangeDelay = 1;

            ADMINI_RESET_FLAGS(admini, ADMINI_FLAG_RESTORABLE);

            if (admini->taskData != NULL)
            {
                RW_FREE(admini->taskData);
                admini->taskData = NULL;
                admini->taskDataSize = 0;
            }
        }

        if (!(admini->flags & ADMINI_FLAG_CHANGING_TASK))
        {
            Admini_ChangeTask(ADMINI_TASK_ID_NULL, NULL, 0, false);
        }

        ADMINI_RESET_FLAGS(admini, ADMINI_FLAG_PASSED_CHECK);
    }

    if (!(admini->flags & ADMINI_FLAG_CHANGING_TASK) ||
         (admini->taskIdToSet < ADMINI_TASK_ID_NULL))
    {
        return KWLN_TASK_CONTINUE;
    }

    return Admini_UpdateTask_Exit;
}

// FUN_0027c840
void Admini_DestroyTask(KwlnTask* adminiTask)
{
    Admini* admini;

    admini = (Admini*)KwlnTask_GetTaskData(adminiTask);
    
    if (admini->taskId >= ADMINI_TASK_ID_NULL &&
       (gAdminiTasksTable[admini->taskId].Admini_Exit != NULL))
    {
        gAdminiTasksTable[admini->taskId].Admini_Exit();
    }

    if (admini->taskData != NULL)
    {
        RW_FREE(admini->taskData);
    }

    admini = (Admini*)KwlnTask_GetTaskData(adminiTask);
    RW_FREE(admini);
}

// FUN_0027c8f0
KwlnTask* Admini_CreateTask()
{
    Admini* admini;
    u32 i;

    if (KwlnTask_GetTaskByName("admini") != NULL)
    {
        return NULL;
    }

    admini = RW_MALLOC(sizeof(Admini), 0x40000);
    if (admini == NULL)
    {
        P3FES_ASSERT("admini.c", 435);
    }

    admini->flags = 0;
    admini->timer = 0;
    admini->taskId = ADMINI_TASK_ID_INVALID;
    admini->taskIdToSet = ADMINI_TASK_ID_INVALID;
    admini->oldTaskIdx = 0;
    for (i = 0; i < ADMINI_TASK_ID_MAX; i++)
    {
        admini->oldTaskIds[i] = ADMINI_TASK_ID_INVALID;
        admini->oldTasksFlags[i] = 0;
    }
    admini->taskData = NULL;
    admini->taskDataSize = 0;

    return KwlnTask_Create(NULL, "admini", 1, Admini_UpdateTask_Check, Admini_DestroyTask, admini);
}

// FUN_0027c9e0
void Admini_TestCall(u8 isRestored, void* taskData)
{
    FUN_005225a8("+++ call\n");
}

// FUN_0027ca10
s32 Admini_TestExit()
{
    FUN_005225a8("+++ exit\n");

    return 0;
}

// FUN_0027ca40
u8 Admini_TestCheck()
{
    FUN_005225a8("+++ check\n");

    return true;
}

// FUN_0027caa0
s32 Admini_BtlBossExit()
{
    KwlnTask* btlTask;

    btlTask = BtlMain_GetBtlTask();
    if (btlTask != NULL)
    {
        KwlnTask_DeleteWithHierarchy(btlTask);
    }

    return 0;
}

// FUN_0027cae0
u8 Admini_BtlBossCheck()
{
    return BtlMain_GetBtlTask() == NULL;
}