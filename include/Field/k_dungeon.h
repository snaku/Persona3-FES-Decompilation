#ifndef K_DUNGEON_H
#define K_DUNGEON_H

#include "Utils.h"

typedef enum
{
    // TODO
    DUNGEON_STATE_STOP = 9
} DungeonState;

// TODO
typedef struct DungeonData
{
    u16 state;
    u32 currFloor;
} DungeonData;

u32 Dungeon_GetCurrentFloor();
u8 Dungeon_IsCurrentFloorExplorable();

#endif