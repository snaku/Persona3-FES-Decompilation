#include "kwln/kwlnTask.h"
#include "rw/rwplcore.h"
#include "admini.h"
#include "g_data.h"
#include "temporary.h"

typedef struct
{
    void (*Admini_Call)(Admini* admini, void* taskData);
    u32 (*Admini_Exit)();
    u8 (*Admini_Check)();
} AdminiTaskEntry;

void Admini_TestCall(Admini* admini, void* taskData);
u32 Admini_TestExit();
u8 Admini_TestCheck();

// 0068f020
static const AdminiTaskEntry gAdminiTasksTable[ADMINI_TASK_ID_MAX] = 
{
    {NULL, NULL, NULL},                                   // ADMINI_TASK_ID_NULL
    {Admini_TestCall, Admini_TestExit, Admini_TestCheck}, // ADMINI_TASK_ID_TEST
    {NULL, NULL, NULL},                                   // ADMINI_TASK_ID_FIELD_ROOT. TODO
    {NULL, NULL, NULL},                                   // ADMINI_TASK_ID_FIELD_ROOT2. TODO
    {NULL, NULL, NULL},                                   // ADMINI_TASK_ID_MAP. TODO
    {NULL, NULL, NULL},                                   // ADMINI_TASK_ID_DUNGEON. TODO
    {NULL, NULL, NULL},                                   // ADMINI_TASK_ID_BATTLE_BOSS. TODO
    {NULL, NULL, NULL},                                   // ADMINI_TASK_ID_FACILITY. TODO
};

// FUN_0027c080
void Admini_ChangeTask(s8 taskId, void* taskData, u8 taskDataSize, u8 param_4)
{
    KwlnTask* adminiTask;
    Admini* admini;

    adminiTask = KwlnTask_GetTaskByName("admini");
    if (adminiTask == NULL)
    {
        P3FES_ASSERT("admini.c", 46);
    }

    admini = KwlnTask_GetTaskData(adminiTask);
    if (admini == NULL)
    {
        P3FES_ASSERT("admini.c", 48);
    }

    ADMINI_SET_FLAGS(admini, ADMINI_FLAG_CHANGING_TASK);
    ADMINI_SET_RESET_FLAGS(admini, ADMINI_FLAG_UNK08, ADMINI_FLAG_CHANGING_TASK);
    ADMINI_SET_RESET_FLAGS(admini, ADMINI_FLAG_UNK08 | ADMINI_FLAG_UNK10000, ADMINI_FLAG_CHANGING_TASK);

    admini->taskIdToSet = taskId;
    admini->unk_21 = 1;

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

        P3FES_Memcpy(admini->taskData, taskData, taskDataSize);
        admini->taskDataSize = taskDataSize;
    }

    if (!param_4)
    {
        ADMINI_SET_FLAGS(admini, ADMINI_FLAG_UNK04);
        return;
    }

    ADMINI_RESET_FLAGS(admini, ADMINI_FLAG_UNK04);
}

// FUN_0027c3b0
void* Admini_UpdateTask_Call(KwlnTask* adminiTask)
{
    // TODO

    return NULL;
}

// FUN_0027c5a0
void* Admini_UpdateTask_Exit(KwlnTask* adminiTask)
{
    Admini* admini;
    s32 exitVal;

    admini = (Admini*)KwlnTask_GetTaskData(adminiTask);
    if (admini == NULL)
    {
        P3FES_ASSERT("admini.c", 296);
    }

    if (admini->taskId >= ADMINI_TASK_ID_NULL &&
       (gAdminiTasksTable[admini->taskId].Admini_Exit != NULL))
    {
        exitVal = gAdminiTasksTable[admini->taskId].Admini_Exit();
        if (exitVal < 0)
        {
            return NULL;
        }

        admini->unk_21 = exitVal + 1;
        admini->taskId = ADMINI_TASK_ID_INVALID;
    }

    return Admini_UpdateTask_Call;
}

// FUN_0027c650
void* Admini_UpdateTask_Check(KwlnTask* adminiTask)
{
    Admini* admini;

    admini = KwlnTask_GetTaskData(adminiTask);
    if (admini == NULL)
    {
        P3FES_ASSERT("admini.c", 333);
    }

    if (!(admini->flags & ADMINI_FLAG_UNK02) &&
         (admini->taskId >= ADMINI_TASK_ID_NULL))
    {
        if (gAdminiTasksTable[admini->taskId].Admini_Check != NULL)
        {
            if (gAdminiTasksTable[admini->taskId].Admini_Check())
            {
                admini->flags |= ADMINI_FLAG_UNK02;
            }
        }

        admini->timer++;
    }

    if (admini->flags & ADMINI_FLAG_UNK02 &&
       (admini->taskId >= ADMINI_TASK_ID_NULL))
    {
        admini->oldTaskIdIdx = (admini->oldTaskIdIdx + (ADMINI_TASK_ID_MAX - 1)) % ADMINI_TASK_ID_MAX;

        if (admini->oldTaskIds[admini->oldTaskIdIdx] >= ADMINI_TASK_ID_NULL &&
           (admini->unk_14[admini->oldTaskIdIdx] & ADMINI_FLAG_CHANGING_TASK))
        {
            P3FES_LOG3("restore sequence!!\n");

            ADMINI_SET_FLAGS(admini, ADMINI_FLAG_CHANGING_TASK);
            ADMINI_SET_FLAGS(admini, ADMINI_FLAG_CHANGING_TASK | ADMINI_FLAG_UNK10000);

            admini->taskIdToSet = admini->oldTaskIds[admini->oldTaskIdIdx];
            admini->unk_21 = true;

            ADMINI_RESET_FLAGS(admini, ADMINI_FLAG_UNK04);

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

        ADMINI_RESET_FLAGS(admini, ADMINI_FLAG_UNK02);
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
    // TODO
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
    admini->oldTaskIdIdx = 0;
    for (i = 0; i < ADMINI_TASK_ID_MAX; i++)
    {
        admini->oldTaskIds[i] = ADMINI_TASK_ID_INVALID;
        admini->unk_14[i] = 0;
    }
    admini->taskData = NULL;
    admini->taskDataSize = 0;

    return KwlnTask_Create(NULL, "admini", 1, Admini_UpdateTask_Check, Admini_DestroyTask, admini);
}

// FUN_0027c9e0
void Admini_TestCall(Admini* admini, void* taskData)
{
    P3FES_LOG3("+++ call\n");
}

// FUN_0027ca10
u32 Admini_TestExit()
{
    P3FES_LOG3("+++ exit\n");

    return 0;
}

// FUN_0027ca40
u8 Admini_TestCheck()
{
    P3FES_LOG3("+++ check\n");

    return true;
}