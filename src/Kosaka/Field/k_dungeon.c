#include "Kosaka/Field/k_dungeon.h"
#include "Kosaka/k_data.h"
#include "kwln/kwlnTask.h"
#include "Model/mdlManager.h"
#include "rw/rwplcore.h"
#include "temporary.h"
#include "h_cdvd.h"
#include "g_data.h"

static KwlnTask* sDungeonTask; // 007ce268. NULL when not in tartarus. Task name = "automatic dungeon"
Model* gDungeonTpMdl;          // 007ce280. FOBJ000.RMD, model for the teleport pad. Maybe a cache ?

#define DUNGEON_TASK_DATA ((K_FieldDungeon*)sDungeonTask->taskData)

H_Cdvd* K_FldDungeon_RequestScript();
void K_FldDungeon_DestroyScrMemory();
u8 K_FldDungeon_CreateScrMemory(H_Cdvd* scrCdvd);

void K_FldDungeon_FUN_001c03f0();

// FUN_001bf570
void* K_FldDungeon_UpdateTask(KwlnTask* dungeonTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

void K_FldDungeon_DestroyTask(KwlnTask* dungeonTask)
{
    // TODO
}

// FUN_001bfbc0
KwlnTask* K_FldDungeon_CreateTask(KwlnTask* parentTask, u32 floor, u32 param_3)
{
    K_FieldDungeon* dungeon;
    KwlnTask* dungeonTask;

    dungeon = (K_FieldDungeon*)RW_CALLOC(1, sizeof(K_FieldDungeon), 0x40000);
    if (dungeon == NULL)
    {
        return NULL;
    }

    dungeonTask = KwlnTask_CreateWithAutoPriority(parentTask,
                                                  10,
                                                  "automatic dungeon ",
                                                  K_FldDungeon_UpdateTask,
                                                  K_FldDungeon_DestroyTask,
                                                  dungeon);
    sDungeonTask = dungeonTask;

    dungeon->currFloor = floor;
    dungeon->unk_08 = param_3;

    if (floor > 1)
    {
        gDungeonTpMdl = MdlManager_CreateMdlFromPath(MODEL_TYPE_FLDOBJ,
                                                     0xffff,
                                                     "field/grmd/fobj000.RMD",
                                                     MDL_CDVDREAD_ASYNC);

        dungeon->scrCdvd = K_FldDungeon_RequestScript();

        K_FldDungeon_FUN_001c03f0();
    }

    return dungeonTask;
}

// FUN_001bff00
void K_FldDungeon_RequestShutdown()
{
    if (sDungeonTask != NULL)
    {
        DUNGEON_TASK_DATA->shouldShutdown = true;
    }
}

// FUN_001bff20
u32 K_FldDungeon_GetCurrentFloor()
{
    if (sDungeonTask == NULL)
    {
        return 0;
    }

    return DUNGEON_TASK_DATA->currFloor;
}

// FUN_001bff50
u8 K_FldDungeon_IsCurrentFloorExplorable()
{
    u32 currFloor;

    if (sDungeonTask == NULL)
    {
        currFloor = 0;
    }
    else 
    {
        currFloor = DUNGEON_TASK_DATA->currFloor;
    }

    if (currFloor < 2 || currFloor >= 400)
    {
        return false;
    }

    return true;
}

// FUN_001bffa0. DONT FORGET
K_FieldDungeonFloorData* K_FldDungeon_GetCurrentFloorData()
{
    if (sDungeonTask == NULL)
    {
        return 0;
    }

    return &DUNGEON_TASK_DATA->floorsData[DUNGEON_TASK_DATA->currFloor];
}

// FUN_001bffe0
void* K_FldDungeon_GetScrMemory()
{
    if (sDungeonTask == NULL)
    {
        return NULL;
    }

    return DUNGEON_TASK_DATA->scrMemory;
}

// FUN_001c0010
u32 K_FldDungeon_GetScrSize()
{
    if (sDungeonTask == NULL)
    {
        return 0;
    }

    return DUNGEON_TASK_DATA->scrSize;
}

// FUN_001c0190. Request a cdvd stream to load main tartarus script
H_Cdvd* K_FldDungeon_RequestScript()
{
    H_Cdvd* cdvd;

    cdvd = NULL;
    if (sDungeonTask == NULL)
    {
        return NULL;
    }

    if (DUNGEON_TASK_DATA->scrMemory == NULL)
    {
        if (Global_GetScenarioMode() == SCENARIO_MODE_JOURNEY)
        {
            cdvd = H_Cdvd_Request("field/script/dungeonat.bf", 0);
        }
        else
        {
            cdvd = H_Cdvd_Request("field/script/dungeonat_aegis.bf", 0);
        }
    }

    return cdvd;
}

// FUN_001c0210. Allocate a new memory block to store tartarus main script by copying H_Cdvd's 'fileMemory'
u8 K_FldDungeon_CreateScrMemory(H_Cdvd* scrCdvd)
{
    K_FieldDungeon* dungeon;

    if (sDungeonTask == NULL)
    {
        return true;
    }

    dungeon = DUNGEON_TASK_DATA;
    if (scrCdvd == NULL)
    {
        return true;
    }

    if (H_Cdvd_IsFileLoaded(scrCdvd))
    {
        dungeon->scrMemory = RW_CALLOC(1, scrCdvd->fileSize, 0x40000);
        dungeon->scrSize = scrCdvd->fileSize;
        memcpy(dungeon->scrMemory, scrCdvd->fileMemory, scrCdvd->fileSize);

        H_Cdvd_Destroy(scrCdvd);

        return true;
    }

    return false;
}

// FUN_001c02e0
void K_FldDungeon_DestroyScrMemory()
{
    K_FieldDungeon* dungeon;

    if (sDungeonTask != NULL)
    {
        dungeon = DUNGEON_TASK_DATA;
        if (dungeon->scrMemory != NULL)
        {
            RW_FREE(dungeon->scrMemory);
            dungeon->scrMemory = NULL;
        }
    }
}

// FUN_001c0330. Request a cdvd stream to load tartarus block specific script (thebel, arqa, etc...)
H_Cdvd* K_FldDungeon_RequestBlockScript(u32 blockId)
{
    char buffer[128];

    if (Global_GetScenarioMode() == SCENARIO_MODE_JOURNEY)
    {
        sprintf(buffer, "field/script/dungeonat%02d.bf", blockId);
    }
    else
    {
        sprintf(buffer, "field/script/dungeonat%02d_aegis.bf", blockId);
    }

    return H_Cdvd_Request(buffer, 0);
}

// FUN_001c03f0
void K_FldDungeon_FUN_001c03f0()
{
    // TODO
}