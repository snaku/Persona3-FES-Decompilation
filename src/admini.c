#include "kwln/kwlnTask.h"
#include "rw/rwplcore.h"
#include "Battle/btlMain.h"
#include "Kosaka/k_assert.h"
#include "admini.h"
#include "temporary.h"

typedef struct
{
    void (*adminiCallFunc)(u8 isRestored, void* seqData);
    s32 (*adminiExitFunc)();
    u8 (*adminiCheckFunc)();
} AdminiSeqEntry;

void adminiSeqTestCall(u8 isRestored, void* seqData);
s32 adminiSeqTestExit();
u8 adminiSeqTestCheck();
s32 adminiSeqBtlBossExit();
u8 adminiSeqBtlBossCheck();

// 0068f020
static const AdminiSeqEntry gAdminiSeqTable[ADMINI_SEQ_MAX] = 
{
    {NULL, NULL, NULL},                                        // ADMINI_SEQ_NULL
    {adminiSeqTestCall, adminiSeqTestCall, adminiSeqTestCall}, // ADMINI_SEQ_TEST
    {NULL, NULL, NULL},                                        // ADMINI_SEQ_FIELD_ROOT. TODO
    {NULL, NULL, NULL},                                        // ADMINI_SEQ_FIELD_ROOT2. TODO
    {NULL, NULL, NULL},                                        // ADMINI_SEQ_MAP. TODO
    {NULL, NULL, NULL},                                        // ADMINI_SEQ_DUNGEON. TODO
    {NULL, adminiSeqBtlBossExit, adminiSeqBtlBossCheck},       // ADMINI_SEQ_BATTLE_BOSS. TODO
    {NULL, NULL, NULL},                                        // ADMINI_SEQ_FACILITY. TODO
};

void* adminiUpdateTask_Check(KwlnTask* adminiTask);

// FUN_0027c080
void adminiChangeTask(s8 seqId, void* seqData, u8 seqDataSize, u8 isNotRestorable)
{
    KwlnTask* adminiTask;
    AdminiWork* admini;

    adminiTask = kwlnTaskGetTaskByName("admini");
    K_ASSERT(adminiTask != NULL, 46);

    admini = (AdminiWork*)kwlnTaskGetWorkData(adminiTask);
    K_ASSERT(admini != NULL, 46);

    ADMINI_SET_FLAGS(admini, ADMINI_FLAG_CHANGING_SEQ);
    ADMINI_SET_RESET_FLAGS(admini, ADMINI_FLAG_UNK08, ADMINI_FLAG_CHANGING_SEQ);
    ADMINI_SET_RESET_FLAGS(admini, ADMINI_FLAG_UNK08 | ADMINI_FLAG_RESTORE_PREV, ADMINI_FLAG_CHANGING_SEQ);

    admini->seqIdToSet = seqId;
    admini->seqChangeDelay = 1;

    if (admini->seqData != NULL)
    {
        RW_FREE(admini->seqData);
        admini->seqData = NULL;
        admini->seqDataSize = 0;
    }

    if (seqData == NULL)
    {
        admini->seqData = NULL;
        admini->seqDataSize = 0;
    }
    else
    {
        admini->seqData = RW_MALLOC(seqDataSize, 0x40000);
        K_ASSERT(admini->seqData != NULL, 93);

        memcpy(admini->seqData, seqData, seqDataSize);
        admini->seqDataSize = seqDataSize;
    }

    if (!isNotRestorable)
    {
        ADMINI_SET_FLAGS(admini, ADMINI_FLAG_RESTORABLE);
        return;
    }

    ADMINI_RESET_FLAGS(admini, ADMINI_FLAG_RESTORABLE);
}

// FUN_0027c220. Set flag 'ADMINI_FLAG_PASSED_CHECK'
void adminiForcePassedCheck()
{
    KwlnTask* adminiTask;
    AdminiWork* admini;

    adminiTask = kwlnTaskGetTaskByName("admini");
    K_ASSERT(adminiTask != NULL, 46);

    admini = (AdminiWork*)kwlnTaskGetWorkDataData(adminiTask);
    K_ASSERT(admini != NULL, 48);

    ADMINI_SET_FLAGS(admini, ADMINI_FLAG_PASSED_CHECK);
}

// FUN_0027c2b0
s8 adminiGetNowSeqId()
{
    KwlnTask* adminiTask;
    AdminiWork* admini;

    adminiTask = kwlnTaskGetTaskByName("admini");
    K_ASSERT(adminiTask != NULL, 46);

    admini = (AdminiWork*)kwlnTaskGetWorkData(adminiTask);
    K_ASSERT(admini != NULL, 48);

    return admini->nowSeqId;
}

// FUN_0027c330
s8 adminiGetSeqIdToSet()
{
    KwlnTask* adminiTask;
    AdminiWork* admini;

    adminiTask = kwlnTaskGetTaskByName("admini");
    K_ASSERT(adminiTask != NULL, 46);

    admini = (AdminiWork*)kwlnTaskGetWorkData(adminiTask);
    K_ASSERT(admini != NULL, 48);

    return admini->seqIdToSet;
}

// FUN_0027c3b0
void* adminiUpdateTask_Call(KwlnTask* adminiTask)
{
    AdminiWork* admini;
    u8 isRestored;

    admini = (AdminiWork*)kwlnTaskGetWorkData(adminiTask);
    K_ASSERT(admini != NULL, 217);

    if (!(admini->flags & ADMINI_FLAG_CHANGING_SEQ) ||
         (admini->seqIdToSet < ADMINI_SEQ_NULL))
    {
        return adminiUpdateTask_Check;
    }

    if (admini->seqChangeDelay == 0)
    {
        admini->timer = 0;
        admini->nowSeqId = admini->seqIdToSet;
        admini->seqIdToSet = ADMINI_SEQ_INVALID;

        ADMINI_RESET_FLAGS(admini, ADMINI_FLAG_CHANGING_SEQ);
        ADMINI_RESET_FLAGS(admini, ADMINI_FLAG_CHANGING_SEQ | ADMINI_FLAG_PASSED_CHECK);

        if (admini->flags & ADMINI_FLAG_RESTORABLE)
        {
            admini->oldSeqFlags[admini->oldSeqIdx] |= ADMINI_FLAG_CHANGING_SEQ;
            ADMINI_RESET_FLAGS(admini, ADMINI_FLAG_RESTORABLE);
        }

        if (!(admini->flags & ADMINI_FLAG_RESTORE_PREV))
        {
            isRestored = false;
            if (!(admini->flags & ADMINI_FLAG_UNK08))
            {
                admini->oldSeqIdx = (admini->oldSeqIdx + 1) % ADMINI_SEQ_MAX;
            }
            else
            {
                ADMINI_RESET_FLAGS(admini, ADMINI_FLAG_UNK08);
            }
        }
        else
        {
            isRestored = true;
            admini->oldSeqIdx = (admini->oldSeqIdx + (ADMINI_SEQ_MAX - 1)) % ADMINI_SEQ_MAX;
            ADMINI_RESET_FLAGS(admini, ADMINI_FLAG_RESTORE_PREV);
        }

        admini->oldSeqIds[admini->oldSeqIdx] = admini->nowSeqId;
        admini->oldSeqFlags[admini->oldSeqIdx] = 0;

        if (gAdminiSeqTable[admini->nowSeqId].adminiCallFunc != NULL)
        {
            gAdminiSeqTable[admini->nowSeqId].adminiCallFunc(isRestored, admini->seqData);
        }

        return adminiUpdateTask_Check;
    }

    admini->seqChangeDelay--;
    return KWLNTASK_CONTINUE;
}

// FUN_0027c5a0
void* adminiUpdateTask_Exit(KwlnTask* adminiTask)
{
    AdminiWork* admini;
    s32 seqChangeDelay;

    admini = (AdminiWork*)kwlnTaskGetWorkData(adminiTask);
    K_ASSERT(admini != NULL, 296);

    if (admini->nowSeqId >= ADMINI_SEQ_NULL &&
       (gAdminiSeqTable[admini->nowSeqId].adminiExitFunc != NULL))
    {
        seqChangeDelay = gAdminiSeqTable[admini->nowSeqId].adminiExitFunc();
        if (seqChangeDelay < 0)
        {
            return KWLNTASK_CONTINUE;
        }

        admini->seqChangeDelay = seqChangeDelay + 1;
        admini->nowSeqId = ADMINI_SEQ_INVALID;
    }

    return adminiUpdateTask_Call;
}

// FUN_0027c650
void* adminiUpdateTask_Check(KwlnTask* adminiTask)
{
    AdminiWork* admini;

    admini = (AdminiWork*)kwlnTaskGetWorkData(adminiTask);
    K_ASSERT(admini != NULL, 333);

    if (!(admini->flags & ADMINI_FLAG_PASSED_CHECK) &&
         (admini->nowSeqId >= ADMINI_SEQ_NULL))
    {
        if (gAdminiSeqTable[admini->nowSeqId].adminiCheckFunc != NULL)
        {
            if (gAdminiSeqTable[admini->nowSeqId].adminiCheckFunc())
            {
                ADMINI_SET_FLAGS(admini, ADMINI_FLAG_PASSED_CHECK);
            }
        }

        admini->timer++;
    }

    if (admini->flags & ADMINI_FLAG_PASSED_CHECK &&
       (admini->nowSeqId >= ADMINI_SEQ_NULL))
    {
        admini->oldSeqIdx = (admini->oldSeqIdx + (ADMINI_SEQ_MAX - 1)) % ADMINI_SEQ_MAX;

        if (admini->oldSeqIds[admini->oldSeqIdx] >= ADMINI_SEQ_NULL &&
           (admini->oldSeqFlags[admini->oldSeqIdx] & ADMINI_FLAG_CHANGING_SEQ))
        {
            printf("restore sequence!!\n");

            ADMINI_SET_FLAGS(admini, ADMINI_FLAG_CHANGING_SEQ);
            ADMINI_SET_FLAGS(admini, ADMINI_FLAG_CHANGING_SEQ | ADMINI_FLAG_RESTORE_PREV);

            admini->seqIdToSet = admini->oldSeqIds[admini->oldSeqIdx];
            admini->seqChangeDelay = 1;

            ADMINI_RESET_FLAGS(admini, ADMINI_FLAG_RESTORABLE);

            if (admini->seqData != NULL)
            {
                RW_FREE(admini->seqData);
                admini->seqData = NULL;
                admini->seqDataSize = 0;
            }
        }

        if (!(admini->flags & ADMINI_FLAG_CHANGING_SEQ))
        {
            adminiChangeTask(ADMINI_SEQ_NULL, NULL, 0, false);
        }

        ADMINI_RESET_FLAGS(admini, ADMINI_FLAG_PASSED_CHECK);
    }

    if (!(admini->flags & ADMINI_FLAG_CHANGING_SEQ) ||
         (admini->seqIdToSet < ADMINI_SEQ_NULL))
    {
        return KWLNTASK_CONTINUE;
    }

    return adminiUpdateTask_Exit;
}

// FUN_0027c840
void adminiDestroyTask(KwlnTask* adminiTask)
{
    AdminiWork* admini;

    admini = (AdminiWork*)kwlnTaskGetWorkData(adminiTask);
    
    if (admini->nowSeqId >= ADMINI_SEQ_NULL &&
       (gAdminiSeqTable[admini->nowSeqId].adminiExitFunc != NULL))
    {
        gAdminiSeqTable[admini->nowSeqId].adminiExitFunc();
    }

    if (admini->seqData != NULL)
    {
        RW_FREE(admini->seqData);
    }

    admini = (AdminiWork*)kwlnTaskGetWorkData(adminiTask);
    RW_FREE(admini);
}

// FUN_0027c8f0
KwlnTask* adminiCreateTask()
{
    AdminiWork* admini;
    u32 i;

    if (kwlnTaskGetTaskByName("admini") != NULL)
    {
        return NULL;
    }

    admini = RW_MALLOC(sizeof(AdminiWork), 0x40000);
    K_ASSERT(admini != NULL, 435);

    admini->flags = 0;
    admini->timer = 0;
    admini->nowSeqId = ADMINI_SEQ_INVALID;
    admini->seqIdToSet = ADMINI_SEQ_INVALID;
    admini->oldSeqIdx = 0;
    for (i = 0; i < ADMINI_SEQ_MAX; i++)
    {
        admini->oldSeqIds[i] = ADMINI_SEQ_INVALID;
        admini->oldSeqFlags[i] = 0;
    }
    admini->seqData = NULL;
    admini->seqDataSize = 0;

    return kwlnTaskCreate(NULL, "admini", 1, adminiUpdateTask_Check, adminiDestroyTask, admini);
}

// FUN_0027c9e0
void adminiSeqTestCall(u8 isRestored, void* seqData)
{
    printf("+++ call\n");
}

// FUN_0027ca10
s32 adminiSeqTestExit()
{
    printf("+++ exit\n");

    return 0;
}

// FUN_0027ca40
u8 adminiSeqTestCheck()
{
    printf("+++ check\n");

    return true;
}

// FUN_0027caa0
s32 adminiSeqBtlBossExit()
{
    KwlnTask* btlTask;

    btlTask = BtlMain_GetBtlTask();
    if (btlTask != NULL)
    {
        kwlnTaskDestroyWithHierarchy(btlTask);
    }

    return 0;
}

// FUN_0027cae0
u8 adminiSeqBtlBossCheck()
{
    return BtlMain_GetBtlTask() == NULL;
}