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