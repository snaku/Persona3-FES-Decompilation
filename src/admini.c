#include "kwln/kwlnTask.h"
#include "rw/rwplcore.h"
#include "admini.h"
#include "g_data.h"

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
static const AdminiTaskEntry gAdminiTasksTable[] = 
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

// FUN_0027c650
KwlnTask_Update Admini_UpdateTask(KwlnTask* adminiTask)
{
    // TODO

    return NULL;
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

    return KwlnTask_Create(NULL, "admini", 1, Admini_UpdateTask, Admini_DestroyTask, admini);
}