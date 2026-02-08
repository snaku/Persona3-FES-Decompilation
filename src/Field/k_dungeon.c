#include "Field/k_dungeon.h"
#include "Field/k_data.h"
#include "kwln/kwlnTask.h"
#include "temporary.h"

#define DUNGEON_TASK_DATA ((FieldDungeon*)ctx.dungeonTask->taskData)

// FUN_001bff20
u32 FldDungeon_GetCurrentFloor()
{
    if (ctx.dungeonTask == NULL)
    {
        return 0;
    }

    return DUNGEON_TASK_DATA->currFloor;
}

// FUN_001bff50
u8 FldDungeon_IsCurrentFloorExplorable()
{
    u32 currFloor;

    if (ctx.dungeonTask == NULL)
    {
        currFloor = 0;
    }
    else 
    {
        currFloor = DUNGEON_TASK_DATA->currFloor;
    }

    // seems like tartarus was supposed to have 399 floors
    if (currFloor < 2 || currFloor >= 400)
    {
        return false;
    }

    return true;
}

// FUN_001bffa0
u16 FldDungeon_GetCurrentFloorMajorId()
{
    if (ctx.dungeonTask == NULL)
    {
        return 0;
    }

    return DUNGEON_TASK_DATA->floorsData[DUNGEON_TASK_DATA->currFloor].majorId;
}