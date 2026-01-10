#ifndef K_DUNGEON_H
#define K_DUNGEON_H

#include "Utils.h"

// TODO
typedef struct DungeonData
{
    u16 state;
    u32 currFloor;
} DungeonData;

u32 Dungeon_GetCurrentFloor();

#endif