#include "Field/k_dungeon.h"
#include "kwln/kwlnTask.h"
#include "temporary.h"

// FUN_001bff20
u32 Dungeon_GetCurrentFloor()
{
    if (ctx.dungeonTask == NULL)
    {
        return 0;
    }

    return ((DungeonData*)ctx.dungeonTask->taskData)->currFloor;
}

// FUN_001bff50
u8 Dungeon_IsCurrentFloorExplorable()
{
    u32 currFloor;

    if (ctx.dungeonTask == NULL)
    {
        currFloor = 0;
    }
    else 
    {
        currFloor = ((DungeonData*)ctx.dungeonTask->taskData)->currFloor;
    }

    // seems like tartarus was supposed to have 399 floors
    if (currFloor < 2 || currFloor >= 400)
    {
        return false;
    }

    return true;
}