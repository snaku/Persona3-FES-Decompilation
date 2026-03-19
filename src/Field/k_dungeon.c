#include "Field/k_dungeon.h"
#include "Field/k_data.h"
#include "kwln/kwlnTask.h"
#include "Model/mdlManager.h"
#include "rw/rwplcore.h"
#include "temporary.h"
#include "h_cdvd.h"
#include "g_data.h"

static KwlnTask* sDungeonTask; // 007ce268. NULL when not in tartarus. Task name = "automatic dungeon"
Model* gDungeonTpMdl;          // 007ce280. FOBJ000.RMD, model for the teleport pad. Maybe a cache ?

#define DUNGEON_TASK_DATA ((FieldDungeon*)sDungeonTask->taskData)

H_Cdvd* FldDungeon_RequestScript();

void FldDungeon_FUN_001c03f0();

// FUN_001bf570
void* FldDungeon_UpdateTask(KwlnTask* dungeonTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

void FldDungeon_DestroyTask(KwlnTask* dungeonTask)
{
    // TODO
}

// FUN_001bfbc0
KwlnTask* FldDungeon_CreateTask(KwlnTask* parentTask, u32 floor, u32 param_3)
{
    FieldDungeon* dungeon;
    KwlnTask* dungeonTask;

    dungeon = RW_CALLOC(1, sizeof(FieldDungeon), 0x40000);
    if (dungeon == NULL)
    {
        return NULL;
    }

    dungeonTask = KwlnTask_CreateWithAutoPriority(parentTask, 10, "automatic dungeon ", FldDungeon_UpdateTask, FldDungeon_DestroyTask, dungeon);
    sDungeonTask = dungeonTask;

    dungeon->currFloor = floor;
    dungeon->unk_08 = param_3;

    if (floor > 1)
    {
        gDungeonTpMdl = MdlManager_CreateMdl(4, 0xffff, "field/grmd/fobj000.RMD", 0);

        dungeon->scrCdvd = FldDungeon_RequestScript();

        FldDungeon_FUN_001c03f0();
    }

    return dungeonTask;
}

// FUN_001bff00
void FldDungeon_RequestShutdown()
{
    if (sDungeonTask != NULL)
    {
        DUNGEON_TASK_DATA->shouldShutdown = true;
    }
}

// FUN_001bff20
u32 FldDungeon_GetCurrentFloor()
{
    if (sDungeonTask == NULL)
    {
        return 0;
    }

    return DUNGEON_TASK_DATA->currFloor;
}

// FUN_001bff50
u8 FldDungeon_IsCurrentFloorExplorable()
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

// FUN_001bffa0
u16 FldDungeon_GetCurrentFloorMajorId()
{
    if (sDungeonTask == NULL)
    {
        return 0;
    }

    return DUNGEON_TASK_DATA->floorsData[DUNGEON_TASK_DATA->currFloor].majorId;
}

// FUN_001bffe0
void* FldDungeon_GetScrMemory()
{
    if (sDungeonTask == NULL)
    {
        return NULL;
    }

    return DUNGEON_TASK_DATA->scrMemory;
}

// FUN_001c0010
u32 FldDungeon_GetScrSize()
{
    if (sDungeonTask == NULL)
    {
        return 0;
    }

    return DUNGEON_TASK_DATA->scrSize;
}

// FUN_001c0190
H_Cdvd* FldDungeon_RequestScript()
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

void FldDungeon_FUN_001c03f0()
{
    // TODO
}